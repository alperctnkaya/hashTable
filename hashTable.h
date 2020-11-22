#include <stdint.h>

typedef struct 
{
    char* key;
    char* value;
}item;

typedef struct 
{
    int size;
    int itemCount;
    item** items;
}   hashTable;
