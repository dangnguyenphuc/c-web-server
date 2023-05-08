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
    while (temp->next->next)
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

}
void free_LList(Route_LList* list){

}

Route_LList create_overflow_buckets(RoutesHashTable* table){

}

void free_overflow_buckets(RoutesHashTable* table){

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