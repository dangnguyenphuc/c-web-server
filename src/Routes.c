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

}

void insert_HashTable(RoutesHashTable* table, char* key, char* value){

}

void deleteElement_HashTable(RoutesHashTable* table, char* key){

}

void handle_Collision_HashTable(RoutesHashTable* table, unsigned long index, Route *item){

}

char* search_HashTable(RoutesHashTable* table, char* key){

}

void print_HashTable(RoutesHashTable* table){

}