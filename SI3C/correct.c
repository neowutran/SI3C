
/*
 * correct.c	-- Correction d'un mot
 *
 * Copyright © 2013 Erick Gallesio - Polytech'Nice-Sophia <eg@unice.fr>
 *
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date:  6-Jan-2013 07:28 (eg)
 * Last file update:  8-Jan-2013 23:19 (eg)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <malloc.h>
#include "correct.h"
#include "hash.h"
#include <ctype.h>

char ** allocate_possibles(int n) {
    int max_possible = 54 * n + 25; //Nombres de possibilitées
    char **p = (char**) malloc(sizeof (char*) * max_possible);
    for (int i = 0; i < max_possible; i++) {
        p[i] = (char*) malloc(sizeof (char) * (n + 1));
    }
    return p;
}

int deletions(char* word, char** posibles, int index) {

    int k = 0;
    for (int i = 0; i < strlen(word); i++) {
        k = 0;
        int j;
        char * new_word = malloc(strlen(word));
        for (j = 0; j < i; j++) {
            *(new_word + j) = word[k];
            k++;
        }
        k++;
        for (; j < (strlen(word) - 1); j++) {
            *(new_word + j) = word[k];
            k++;
        }
        *(posibles + index) = new_word;
        index++;
    }
    return index;
}

int alterations(char* word, char** posibles, int index) {

    int j, k = 0;
    char alphabet[26] = ALPHABET;

    for (int i = 26; i < (strlen(word) + 1)*26; i++) {
        k = 0;
        char * new_word = malloc(strlen(word) + 1);

        for (j = 0; j < i / 26; j++) {
            *(new_word + j) = word[k];
            k++;
        }
        *(new_word + j - 1) = alphabet[i % 26];

        for (; j < (strlen(word) + 1); j++) {
            *(new_word + j) = word[k];
            k++;
        }
        *(posibles + index) = new_word;
        index++;
    }
    return index;
}

int inserts(char* word, char** posibles, int index) {

    int j, k = 0;
    char alphabet[26] = ALPHABET;

    for (int i = 0; i < (strlen(word) + 1)*26; i++) {

        k = 0;
        char * new_word = malloc(strlen(word) + 2);

        for (j = 0; j < i / 26; j++) {
            *(new_word + j) = word[k];
            k++;
        }
        *(new_word + j) = alphabet[i % 26];
        j++;

        for (; j < (strlen(word) + 1); j++) {
            *(new_word + j) = word[k];
            k++;
        }
        *(posibles + index) = new_word;
        index++;
    }
    return index;
}

void destroy_possibles(char **possibles, int index) {

    for (int i = 0; i < index; i++) {
        free(possibles[i]);
    }
    free(possibles);
}

int transpositions(char* word, char** posibles, int index) {

    for (int i = 0; i < (strlen(word) - 1); i++) {
        char * new_word = malloc(sizeof (char) * (strlen(word) + 1));
        for (int j = 0; j < (strlen(word)); j++) {
            *(new_word + j) = word[j];
        }
        char new_last = word[i];
        char new_first = word[i + 1];
        new_word[i] = new_first;
        new_word[i + 1] = new_last;
        *(posibles + index) = new_word;
        index++;
    }

    return index;
}

char* better_candidate(char* word, char** possibles, int index) {
    if (hash_table_is_present(word)) {
        return word;
    }
    int max_occurence = 0;
    int occurence = 0;
    int index_corr_word = -1;

    for (int i = 0; i < index; i++) {
        occurence = hash_table_search(*(possibles + i));
        if (occurence > max_occurence) {
            index_corr_word = i;
            max_occurence = occurence;
        }
    }
    if (index_corr_word == -1)
        return word;
    char * corr = malloc(sizeof (char) * (strlen(word) + 2));
    return strcpy(corr, *(possibles + index_corr_word));
}

static char *find_corrections(char *word) {
    char **possibles = allocate_possibles(strlen(word));
    char *result;
    int index = 0;
    if (possibles == NULL) {
        fprintf(stderr, "cannot allocate the array of possibles");
        exit(EXIT_FAILURE);
    }
    /* construires une liste de mots possibles */
    index = deletions(word, possibles, index);
    index = transpositions(word, possibles, index);
    index = alterations(word, possibles, index);
    index = inserts(word, possibles, index);
    /*choisir le meilleur candidat entre word et les mots possibles */
    result = better_candidate(word, possibles, index);
    /* un peu de ménage avant de renvoyer le meilleur candidat */
    destroy_possibles(possibles, index);
    return result;
}

char *correct_word(char *word) {
    return find_corrections(word);
}