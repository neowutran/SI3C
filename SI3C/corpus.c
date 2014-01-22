#include <stdio.h>
#include <stdlib.h>
#include "corpus.h"
#include "hash.h"
#include <ctype.h>
#include <stdint.h>

int init_corpus_from_file(char *filename) {
    char ch;
    char chaine[100];

    FILE *fp;
    fp = fopen(filename, "r"); // read mode

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    while ((ch = fgetc(fp)) != EOF) {
        int separator = 0;
        for (int j = 0; SEPARATORS[j] != '\0'; j++) {
            if (SEPARATORS[j] == ch) {
                separator = 1;
                break;
            }
        }

        if (!separator) {

            chaine[i] = ch;
            i++;
            continue;
        }

        if (!i)continue;
        chaine[i] = '\0';
        i = 0;
        hash_table_add(chaine);

    }

    fclose(fp);
    return 1;
}