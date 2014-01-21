
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <ctype.h>
#include <stdint.h>
#include <string.h>

/* creation de destruction de la table */
void hash_table_create() {
    hcreate(HASH_TABLE_SIZE);
}

void hash_table_destroy() {
    hdestroy();
}

/* renvoie 1 si word est dans la table, 0 sinon */
int hash_table_is_present(char *word) {
    ENTRY search;
    search.key = word;
    if (NULL == hsearch(search, FIND)) return 0;
    return 1;
}

/* renvoie le nombre d'occurences de word dans la table (0 si absent) */
int hash_table_search(char *word) {
    ENTRY *entry, search;
    search.key = word;
    entry = hsearch(search, FIND);
    if (NULL == entry) return 0;
    return (intptr_t) entry->data;

}

/* ajoute word dans la table */
void hash_table_add(char *word) {

    const int length = strlen(word); // get the length of the text
    char* lower = (char*) malloc(length + 1); // allocate 'length' bytes + 1 (for null terminator) and cast to char*
    lower[ length ] = 0; // set the last byte to a null terminator

    // copy all character bytes to the new buffer using tolower
    for (int i = 0; i < length; i++) {
        lower[ i ] = tolower(word[ i ]);
    }

    ENTRY *entry, insert;
    insert.key = lower;
    entry = hsearch(insert, FIND);

    if (entry == NULL) {
        insert.data = (void *) (intptr_t) 1;
        if (hsearch(insert, ENTER) == NULL) {
            fprintf(stderr, "entry failed\n");
        }
        return;
    }
    entry->data = entry->data + 1;

}
