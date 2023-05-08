#ifndef ROUTES_H
#define ROUTES_H

#include <stdlib.h>
#include <string.h>

// TODO: define a Route
#define CAPACITY 100

typedef struct Route
{
	char* key;
	char* value;
} Route;

typedef struct Route_LList
{
	Route *item;
	struct Route_LList *next;
} Route_LList;


typedef struct RoutesHashTable
{
	Route** items;
	Route_LList** overflow_buckets;
	int size;
	int count;
} RoutesHashTable;

unsigned long hash(char* key);
Route_LList* allocate_LList();
Route_LList* insert_LList(Route_LList* list, Route* item);
Route_LList* removeHead_LList(Route_LList* list);
void free_LList(Route_LList* list);
Route_LList create_overflow_buckets(RoutesHashTable* table);
void free_overflow_buckets(RoutesHashTable* table);
void create_Route(char* key, char* value);
void free_Route(Route *route);
RoutesHashTable* create_HashTable(int size);
void free_HashTable(RoutesHashTable *table);
void insert_HashTable(RoutesHashTable* table, char* key, char* value);
void deleteElement_HashTable(RoutesHashTable* table, char* key);
void handle_Collision_HashTable(RoutesHashTable* table, unsigned long index, Route *item);
char* search_HashTable(RoutesHashTable* table, char* key);
void print_HashTable(RoutesHashTable* table);

#endif