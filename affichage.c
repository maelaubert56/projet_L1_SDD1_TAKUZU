/* ----------------------------------   affichage.c   ----------------------------------
 *
 *      ==> regroupe les fonctions d'affichages du programme tel que la gestion des couleurs de la console,
 *          l'effacement de l'écran.
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  ------------------------------------------------------------------------------------
 */


#include <stdlib.h>
#include <stdio.h>
#include "affichage.h"
#include <windows.h>

void color(int t, int f) {
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, f * 16 + t);
}

void clear_screen() {
    for (int i = 0; i < 40; i++) { printf("\n"); }
}


void afficher_matrice(int **tab, int size) {
    int i, j, k;

    color(15, 0); // couleur par defaut, fond par defaut
    printf("\n    ");
    for (i = 0; i < size; i++) {

        printf("|");
        color(9, 0); // couleur bleu, fond par defaut
        if (i < 10) printf(" %d ", i);
        else printf("%d ", i);
        color(15, 0);
    }
    printf("|\n----");

    for (k = 0; k < size; k++) {
        printf("+---");
    }
    printf("|\n");

    for (i = 0; i < size; i++) {
        color(9, 0);
        printf("  %c ", 65 + i);
        color(15, 0);

        for (j = 0; j < size; j++) {
            if (tab[i][j] == -1) printf("|   ");
            else printf("| %d ", tab[i][j]);
        }
        if (i < size - 1) {
            printf("|\n----");
            for (k = 0; k < size; k++) {
                printf("+---");
            }
            printf("|\n");
        }
    }
    printf("|\n\n");
}


int **appliquer_masque(int **solution, int **masque, int size) {
    int **grille_jeu = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++) {
        grille_jeu[i] = malloc(sizeof(int) * size);
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (masque[i][j] == 1) grille_jeu[i][j] = solution[i][j];
            else grille_jeu[i][j] = -1;
        }
    }
    return grille_jeu;
}


