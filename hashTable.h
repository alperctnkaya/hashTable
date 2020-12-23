#include <stdint.h>
#include <stddef.h>

typedef struct 
{
    char* key;
    char* value;
    struct item* next;
}item;

typedef struct 
{
    int size;
    int itemCount;
    item** items;
}   hashTable;


item* newItem(const char* key, const char* value);

hashTable* newHashTable();

void freeItem(item* item);

void delHashTable(hashTable* hashTable);

size_t hashFunc(const char* str, size_t size);

void insertKey(hashTable* ht, char* key, char* value);

const char* getValue(hashTable* ht, char* key);

int delKey(hashTable* ht, const char* key);

int updateValue(hashTable* ht,const char* key, const char* value);

void resizeTable(hashTable* ht, const int size);