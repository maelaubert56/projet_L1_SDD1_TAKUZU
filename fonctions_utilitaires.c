/* ----------------------------------   fonctions_utilitaires.c   ----------------------------------
 *
 *      ==> fonctions diverses utilisées dans de nombreux endroits du code
 *          tels que la gestion des entrées utilisateurs.
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  ------------------------------------------------------------------------------------------------
 */

#include "fonctions_utilitaires.h"
#include <stdio.h>
#include <stdlib.h>

void wait_for_enter() {
    printf("Appuyez sur entrer pour continuer...");
    getchar(); // permet de mettre une pause jusqu'à l'appui sur "entrer" (comme une saisie sans recupere la valeur)
}

int saisieint() {
    char *str = (char *) malloc(10 * sizeof(char));
    fgets(str, 10, stdin); //recuperation de la chaine
    int result = 0;
    int puiss = 1;
    int no_digit = 1;

    while (('-' == (*str)) || ((*str) == '+')) {
        if (*str == '-')
            puiss = puiss * -1;
        str++;
    }

    while ((*str >= '0') && (*str <= '9')) {
        no_digit = 0;
        result = (result * 10) + ((*str) - '0');
        str++;
    }

    if (no_digit == 1) return -100;
    else return (result * puiss);
}

int **remplir_matrice(int size) {

    int **mat = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        mat[i] = malloc(sizeof(int) * size);
    }

    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            do {
                printf("\nEntrez la valeur pour l'indice %d-%d : ", i, j);
                mat[i][j] = saisieint();
            }while (mat[i][j] != 1 && mat[i][j] != 0);
        }
    }
    printf("\n");
    return mat;
}
