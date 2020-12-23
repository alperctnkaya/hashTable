#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hashTable.h"

item* newItem(const char* key, const char* value){
    item* newItem = malloc(sizeof(item));
    newItem->key = strdup(key);
    newItem->value = strdup(value);
    newItem->next = NULL;
    return newItem;
}

hashTable* newHashTable(size_t size){
    hashTable* newHashTable = malloc(sizeof(hashTable));
    
    newHashTable->size = size;
    newHashTable->itemCount = 0;
    
    newHashTable->items = malloc((size_t)newHashTable->size);
    for(int i=0; i<newHashTable->size;i++){
        newHashTable->items[i] = malloc(sizeof(item*));
        newHashTable->items[i] = NULL;
    } 
    
    return newHashTable;
}

void freeItem(item* item){
    
    free(item->key);
    free(item->value);
    free(item);
    item = NULL;
}

void delHashTable(hashTable* hashTable){
    
    for(int i=0; i<hashTable->size; i++){
    item* item = hashTable->items[i];
        if(item != NULL)    free(item);
     
    }
   

    free(hashTable->items);
    free(hashTable);
}

size_t hashFunc(const char* str, size_t size){
    size_t hash = 1331;
    for (int i =0; i<(int)strlen(str);i ++){
        hash = ((hash<<4) + (int)(*str)) % size;
    }

    return hash % size;
}

void insertKey(hashTable* ht, char* key, char* value){
    
    size_t hash = hashFunc(key, ht->size);
    item *i;
    i = newItem(key, value);
    
    if(ht->items[hash] == NULL){
        ht->items[hash] = i;
        
    }
    else{
        item *temp= ht->items[hash];
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = i;
    }
    
    ht->itemCount++;
    return;
}

const char* getValue(hashTable* ht, char*key){
    size_t hash = hashFunc(key, ht->size); 
    item* i;
    
    if(ht->items[hash] != NULL) 
        i = ht->items[hash];
    else return "KEY NOT IN THE TABLE";
    
    while(strcmp(i->key, key)){
        i = i->next;
        
        if ( i == NULL){
            return "KEY NOT IN THE TABLE";
        }
    }

    return i->value;
    
}

int delKey(hashTable* ht, const char* key){
    size_t hash = hashFunc(key, ht->size);

    item *i, *prev;
    int flag = 0;

    if(ht->items[hash] != NULL) 
        i = ht->items[hash];
    else return -1; // KEY NOT FOUND IN THE TABLE  
    
    while(strcmp(i->key, key)){
        flag = 1;
        prev = i;
        i = i->next;
        
        if ( i == NULL){
            return -1; // KEY NOT FOUND IN THE TABLE  
        }
    }

    if ( flag == 1 ){
        prev->next = i->next;
    }
    else{
        ht->items[hash] = i->next;       
    }

    ht->itemCount--;
    return 1;
}

int updateValue(hashTable* ht, const char* key, const char* value){
    
    size_t hash = hashFunc(key, ht->size); 
    item* i;
    
    if(ht->items[hash] != NULL) 
        i = ht->items[hash];
    else return -1; //"KEY NOT IN THE TABLE"
    
    while(strcmp(i->key, key)){
        i = i->next;
        
        if ( i == NULL){
            return -1 ;// "KEY NOT IN THE TABLE";
        }
    }

    i->value = value;
    return 1;
}


void resizeTable(hashTable* ht, const int size){
    
    item *items[ht->itemCount];
    int index = 0;
    item *it;
    
    for(int i = 0 ; i<ht->size ; i++){
        it=ht->items[i];
        if ( it == NULL ) continue;
        while(it){
            items[index] = it;
            index++;
            it = it->next;
        }
        ht->items[i]=NULL;
    }
    
    
    ht->size = size;
    ht->itemCount = 0;
    for(int i = 0; i<index; i++){
     
        insertKey(ht, items[i]->key, items[i]->value);
        
    }

       
    return;
}