#include "Routes.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned long hash(char* key){
    unsigned long i = 0;
    for(int j = 0; key[j]; j++){
        i += key[j] << 5;
    }
    return i % CAPACITY;
}

Route_LList* allocate_LList(){
    Route_LList* list = (Route_LList*) malloc(sizeof(Route_LList));
    return list;
}

Route_LList* insert_LList(Route_LList* list, Route* item){
    if(!list){  // if empty list
        Route_LList* head = allocate_LList();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    }else if(list->next == NULL){   // else if list has 1 node
        Route_LList* node = allocate_LList();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    // else if list has 2 or more nodes
    Route_LList* temp = list;
    while (temp->next)
    {
        temp = temp->next;
    }
    Route_LList* node = allocate_LList();
    node->item = item;
    node->next = NULL;
    temp->next = node;

    return list;
}

Route_LList* removeHead_LList(Route_LList* list){
    if(!list){  // if empty list
        return list;
    }else if(list->next == NULL){   // else if list has 1 node
        Route_LList* node = list;
        list = NULL;
        printf("Deleting\tKey: %s\tValue:%s",node->item->key, node->item->value);
        free(node->item->key);
        free(node->item->value);
        free(node->item);
        free(node);
        return list;
    }

    // else if list has 2 or more nodes
    Route_LList* node = list->next;
    Route_LList* temp = list;
    temp->next = NULL;
    list = node;
    printf("Deleting\tKey: %s\tValue:%s",temp->item->key, temp->item->value);
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return list;
}
void free_LList(Route_LList* list){
    Route_LList* temp = list;
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
    
}

Route* search_LList(Route_LList* list, char* key){
    Route_LList* temp = list;
    while (temp)
    {
        if(strcmp(temp->item->key, key) == 0) return temp->item;
        temp = temp->next;
    }
    return NULL;
}

void print_LList(Route_LList* list){
    Route_LList* temp = list;
    while (temp)
    {
        printf("\t\t\tKey:%s, Value:%s\n", temp->item->key, temp->item->value);
        temp= temp->next;
    }
    
}

Route_LList** create_overflow_buckets(RoutesHashTable* table){
    Route_LList** buckets = (Route_LList **)calloc(table->size, sizeof(Route_LList *));

    // all of elements in bucket are NULL
    for (int i = 0; i < table->size; i++){
        buckets[i] = NULL;
    }

    return buckets;
}

void free_overflow_buckets(RoutesHashTable* table){
    Route_LList** buckets = table->overflow_buckets;

    for (int i = 0; i < table->size; i++){
        free_LList(table->overflow_buckets[i]);
    }

    free(buckets);
}

Route* create_Route(char* key, char* value){
    Route* route = (Route*) malloc (sizeof(Route));
    route->key = (char *)malloc(strlen(key) + 1);
    route->value = (char *)malloc(strlen(value) + 1);
    strcpy(route->key, key);
    strcpy(route->value, value);
    return route;
}

void free_Route(Route *route){
    // free key
    free(route->key);
    // free value
    free(route->value);
    // finally, free route
    free(route);
}

RoutesHashTable* create_HashTable(int size){
    RoutesHashTable* table = (RoutesHashTable *) malloc (sizeof(RoutesHashTable));
    table->size = size;
    table->count = 0;
    table->items = (Route **)calloc(table->size, sizeof(Route *));
    table->overflow_buckets = create_overflow_buckets(table);

    for (int i = 0; i < size; ++i)
    {
       table->items[i] = NULL;
    }

    return table;
}

void free_HashTable(RoutesHashTable *table){
    for (int i = 0; i < table->size; ++i)
    {
        Route *item = table->items[i];
        if (item != NULL)
            free_Route(item);
    }
    
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void insert_HashTable(RoutesHashTable* table, char* key, char* value){
    Route *route = create_Route(key, value);

    unsigned long index = hash(key);

    Route *current_route = table->items[index];

    if (!current_route){
        // if full
        if(table->count == table->size){
            printf("Insert Error: Hash Table is full\n");
            free_Route(route);
            return;
        }
        // else
        table->items[index] = route;
        table->count++;
    }else{
        // if key = key and value != value then update value
        if (strcmp(current_route->key, key) == 0)
        {
            strcpy(table->items[index]->value, value);
            return;
        }else{
            handle_Collision_HashTable(table, index, route);
            return;
        }
        
    }
}

void deleteElement_HashTable(RoutesHashTable* table, char* key){
    unsigned long index = hash(key);
    Route* route = table->items[index];
    Route_LList *overflow = table->overflow_buckets[index];

    if (route==NULL)
    {
        return;
    }
    else{
        if (overflow == NULL && strcmp(route->key, key) == 0)
        {
            table->items[index] = NULL;
            free_Route(route);
            table->count -= 1;
            return;
        }else if (overflow != NULL)
        {
            if (strcmp(route->key, key) == 0)
            {
                free_Route(route);
                Route_LList* node = overflow;
                overflow = overflow->next;
                node->next = NULL;
                table->items[index] = create_Route(node->item->key, node->item->value);
                free_LList(node);
                table->overflow_buckets[index] = overflow;
            }

            Route_LList* cur = overflow;
            Route_LList* prev = NULL;

            while (cur)
            {
                if(strcmp(cur->item->key, key) == 0){
                    if(prev == NULL){
                        overflow = overflow->next;
                        cur->next = NULL;
                        free_LList(cur);
                        table->overflow_buckets[index] = overflow;
                        return;
                    }else{
                        prev->next = cur->next;
                        cur->next = NULL;
                        free_LList(cur);
                        table->overflow_buckets[index] = overflow;
                        return;
                    }
                }
                cur = cur->next;
                prev = cur;
            }  
        }  
    }
}

void handle_Collision_HashTable(RoutesHashTable* table, unsigned long index, Route *item){
    Route_LList *list = table->overflow_buckets[index];

    if (!list)
    {
        list = allocate_LList();
        list->item = item;
        table->overflow_buckets[index] = list;
        return;
    }else{
        table->overflow_buckets[index] = insert_LList(list, item);
        return;
    }
    
}

char* search_HashTable(RoutesHashTable* table, char* key){
    unsigned long index = hash(key);
    Route* route = table->items[index];
    Route_LList *overflow = table->overflow_buckets[index];

    if (route)
    {
        // if same key, return value
        if (strcmp(route->key, key) == 0)
        {
            return route->value;
        }
        // else if bucket none then return NULL
        if (overflow == NULL){
            return NULL;
        }

        // else if bucket not NULL
        if (overflow != NULL){
            route = search_LList(overflow, key);
            printf("\nColision...KEY: %s\n", route->key);
            return route->value;
        }
    }
    return NULL;
    
}

void print_search(RoutesHashTable *table, char *key)
{
    char *val;

    if ((val = search_HashTable(table, key)) == NULL)
    {
        printf("Key:%s does not exist\n", key);
        return;
    }
    else
    {
        printf("Key:%s, Value:%s\n", key, val);
    }
}

void print_HashTable(RoutesHashTable* table){
    printf("\nHash Table\n-------------------\n");

    for (int i = 0; i < table -> size; i++)
    {
        if (table -> items[i])
        {
            printf("\tIndex:%d, \tKey:%s, Value:%s\n", i, table -> items[i] -> key, table -> items[i] -> value);
        }
        if (table -> overflow_buckets[i])
        {
            print_LList(table -> overflow_buckets[i]);
        }

    }

    printf("-------------------\n\n");
}

char* routing(char* key){
    if(strcmp(key, "/index.html") == 0 || strcmp(key, "/index") == 0) return "/";
    if(strcmp(key, "/about.html") == 0 ) return "/about";
    return key;
}