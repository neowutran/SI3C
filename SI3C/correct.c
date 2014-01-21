
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
#include <malloc.h>
#include "correct.h"
#include "hash.h"
/*
static char *find_corrections(char *word) {
    char **possibles = allocate_possibles(strlen(word));
    char *result;
    int index = 0;

    if (possibles == NULL) {
        fprintf(stderr, "cannot allocate the array of possibles");
        exit(EXIT_FAILURE);
    }
 */
/* construires une liste de mots possibles */
/*
    index = deletions(word, possibles, index);
    index = transpositions(word, possibles, index);
    index = alterations(word, possibles, index);
    index = inserts(word, possibles, index);
 */
/*choisir le meilleur candidat entre word et les mots possibles */
/*
result = better_candidate(word, possibles, index);
 */
/* un peu de ménage avant de renvoyer le meilleur candidat */
/*
destroy_possibles(possibles, index);
    return result;
}

char *correct_word(char *word) {
    return hash_table_is_present(word) ? word : find_corrections(word);
}
 */