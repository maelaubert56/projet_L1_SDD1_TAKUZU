/* ----------------------------------   resolution.c   ----------------------------------
 *
 *      ==> contient les fonctions de résolution manuelle d'une grille de Takuzu
 *      ==> permet de générer un masque automatiquement
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  -------------------------------------------------------------------------------------
 */

#import "affichage.h"
#include "resolution.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "test_matrices.h"
#include "fonctions_utilitaires.h"
#include <windows.h>


int **generer_masque(int size, int niveau) {
    int i, j;
    int **masque = malloc(sizeof(int *) * size);
    for (i = 0; i < size; i++) {
        masque[i] = malloc(sizeof(int) * size);
        for (j = 0; j < size; j++) { masque[i][j] = 0; }
    }

    srand(time(NULL));
    int nb_case;
    switch (niveau) {
        case 1:
            nb_case = (int) (size * size * 0.6);
            break;
        case 2:
            nb_case = (int) (size * size * 0.5);
            break;
        case 3:
            nb_case = (int) (size * size * 0.4);
            break;
        default :
            nb_case = (int) (size * size * 0.6);
            break;
    }
    while (nb_case != 0) {
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                if ((rand() % size == 1) && (masque[i][j] != 1) && nb_case != 0) {
                    masque[i][j] = 1;
                    nb_case--;
                }
            }
        }
    }
    return masque;
}





void resoudre(int **masque, int **solution, int size) {

    int **grille_jeu = appliquer_masque(solution, masque, size);

    int gagne = 0, val, vies = 3, valide;
    COORDS coords;
    while (gagne != 1 && vies != 0) {

        printf("------------------------------------------\nVies restantes : %d\n", vies);
        // on choisis une case et une valeur
        coords = choisir_case(grille_jeu, size);
        fflush(stdin);
        printf("\nEntrez la valeur de cette case (0 ou 1):\n");
        val = saisieint();
        while (val != 1 && val != 0) {
            printf("\nEntrez la valeur de cette case (0 ou 1):\n");
            val = saisieint();
        }

        //on verifie la validité du coup
        valide = verif_valide(grille_jeu, coords, size, val);
        if (valide == 1) {
            //on vérifie que cette valeur corresponds à la solution
            if (val != solution[coords.i][coords.j]) {
                printf("Coup valide mais incorrect !\n");
            } else {
                printf("Coup valide.\n");
                Sleep(500);
                grille_jeu[coords.i][coords.j] = val;
                //on regarde si la grille est résolue
                if (verif_grille(grille_jeu, solution, size) == 1) gagne = 1;
            }
        } else {
            vies--;
            printf("Coup invalide...\nIl vous reste %d vies.\n", vies);
            switch (valide) {
                case -1:
                    printf("La ligne %d contient deja %d fois la valeur %d...", coords.i, size / 2, val);
                    break;
                case -2:
                    printf("La colonne %d contient deja %d fois la valeur %d...", coords.j, size / 2, val);
                    break;
                case -3:
                    printf("Placer un %d ici provoquerai une suite de plus de 2 fois la valeur %d...", val, val);
                    break;
                case -4:
                    printf("Placer un %d ici provoquerai une suite de plus de 2 fois la valeur %d...", val, val);
                    break;
            }
        }
        printf("\n");
    }
    clear_screen();
    if (vies != 0) {
        afficher_matrice(grille_jeu, size);
        printf("Bravo, vous avez resolu la grille !\n");
    } else {
        afficher_matrice(solution, size);
        printf("Vous avez epuisé vos 3 vies...\nFin de la partie\n\n");
    }
    wait_for_enter();
}


COORDS choisir_case(int **tab, int size) {
    COORDS coords = {-1, -1};
    char i;
    int j;
    printf("\n");
    do {
        if (coords.i == 1 || coords.i == 0) printf("\n Cette case est deja remplie\n");
        Sleep(500);
        afficher_matrice(tab, size);
        printf("Choisissez la case grace aux indices affiches (ex:A2) :");
        scanf(" %c%d", &i, &j);

        while ((j < 0) || (j > (size - 1)) || (((int) i) < ((int) 'A')) || (((int) i) > (((int) 'A') + size - 1))) {
            printf("\nErreur...\nVous devez choisir la case grace aux indices affiches (ex:A2) :\n");
            scanf(" %c%d", &i, &j);
        }

        coords.i = (int) (i) - 65;
        coords.j = j;
    } while (tab[coords.i][coords.j] != -1);

    printf("\n");
    return coords;
}
