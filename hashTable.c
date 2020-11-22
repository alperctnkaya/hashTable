#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashTable.h"

item* newItem(const char* key, const char* value){
    item* newItem = malloc(sizeof(item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);

    return newItem;
}

hashTable* newHashTable(){
    hashTable* newHashTable = malloc(sizeof(hashTable));
    
    newHashTable->size = 10;
    newHashTable->itemCount = 0;
    
    newHashTable->items = malloc((size_t)newHashTable->size);
    for(int i=0; i<newHashTable->size;i++)
        newHashTable->items[i] = malloc(sizeof(item*)); 
    
    return newHashTable;
}

void delItem(item* item){
    
    free(item->key);
    free(item->value);
    free(item);
    item = NULL;
}

void delHashTable(hashTable* hashTable){
    
    for(int i=0; i<hashTable->size; i++){
    item* item = hashTable->items[i];
        if(item != NULL) free(item);
        item = NULL;
    }
   

    free(hashTable->items);
    free(hashTable);
    hashTable->items=NULL;
    hashTable=NULL;
}

size_t hashFunc(const char* str, size_t size){
    size_t hash = 1331;
    for (int i =0; i<strlen(str);i ++){
        hash = ((hash<<4) + (int)(*str)) % size;
    }

    return hash % size;
}

int main(){
    item* item1;
    item1 = newItem("ALPER","161201035");
    
    hashTable* hashTable1 = newHashTable();
    
    delHashTable(hashTable1);   
    size_t hash = hashFunc("affsa",25);
    printf("%d", (int)hash);   
    
    
    
    return 0;
}