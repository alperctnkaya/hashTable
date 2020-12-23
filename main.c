#include "hashTable.h"
#include <stdio.h>

int main(){
    
    hashTable* ht = newHashTable(10);
    insertKey(ht, "ABC", "CDE");
    printf("%s\n", getValue(ht, "ABC"));

    resizeTable(ht, 20);
    
    printf("%s\n", getValue(ht, "ABC"));
    updateValue(ht, "ABC", "FGH");
    printf("%s\n", getValue(ht, "ABC"));
    delKey(ht, "ABC");
    printf("%s\n", getValue(ht, "ABC"));
    return 0;
}