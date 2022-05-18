/* ----------------------------------   generateur_grille.c   ----------------------------------
 *
 *      ==> fonctions de generation de grilles de Takuzu:
 *          - affichage des lignes valides pour différentes tailles de matrice
 *          - création d'une matrice de taille 4, 8 ou 16 (la matrice de taille 16 est très longue à générer)
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  --------------------------------------------------------------------------------------------
 */


#include "generateur_grille.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "test_matrices.h"
#include "affichage.h"
int *int_to_bin(int nombre, int size) {
    int *code_binaire = (int *) malloc(sizeof(int) * size);
    int i;
    for (i = 0; i <= size - 1; i++) {
        if ((int) pow(2, size - 1 - i) <= nombre) {
            code_binaire[i] = 1;
            nombre -= (int) pow(2, size - 1 - i);
        } else code_binaire[i] = 0;
    }
    return code_binaire;
}


int verif_ligne(int *code_binaire, int size) {
    int cpt = 0, i;
    for (i = 0; i < size; i++) {
        if (code_binaire[i] == 0) {
            cpt++;
        }
        if ((i < size - 3) && (code_binaire[i] == code_binaire[i + 1] && code_binaire[i] == code_binaire[i + 2]))
            return 0;
        if ((i > size - 3) && (code_binaire[i] == code_binaire[i - 1] && code_binaire[i] == code_binaire[i - 2]))
            return 0;
    }
    if (cpt == size / 2) return 1;
    else return 0;
}

int **lignes_valides(int size, int *cpt) {
    int **tab = (int **) malloc(sizeof(int *) * (int) pow(2, size));
    int j = 0;
    for (int i = 0; i < (int) pow(2, size); i++) {
        tab[j] = (int *) malloc(sizeof(int) * size);
        tab[j] = int_to_bin(i, size);
        if (verif_ligne(tab[j], size) == 1) j++;
    }
    *cpt = j;

    return tab;
}

void afficher_lignes_valides(size) {
    printf("Lignes valides :\n");
    int cpt;
    int **tab_lignes_valides = lignes_valides(size, &cpt);
    for (int i = 0; i < cpt; i++) {
        printf("\n\t->  ");
        for (int j = 0; j < size; j++) {
            printf("%d ", tab_lignes_valides[i][j]);
        }
    }
    printf("\n");
}

int **generer_grille(int size){
    int i, j;
    int **grid = malloc(sizeof(int *) * size);
    for (i = 0; i < size; i++) {
        grid[i] = malloc(sizeof(int) * size);
        for (j = 0; j < size; j++) {
            grid[i][j] = -1;
        }
    }

    // on place quelques valeurs de facon random dans la grille afin d'obtenir des grilles différentes a chaque génération

    for (i = 0; i < 3; i++) {
        int x = rand() % size;
        int y = rand() % size;
        int val = rand() % 2;
        if (verif_valide_gen(grid, y,x, size, val) == 1){
            grid[y][x] = val;
        }
    }
    gen_grid(grid, 0, size); // génére la grille au moyen de la fonction récursive gen_grid()

    return grid;
}


int gen_grid(int **grille, int pos, int size) {
    //afficher_matrice(grille,size);
    if (pos == size * size)
        return 1;

    int i = pos / size, j = pos % size;
    if (grille[i][j] != -1)
        return gen_grid(grille, pos + 1, size);

    for (int k = 0; k <= 1; k++) {
        if (verif_valide_gen(grille, i, j, size, k) == 1) {
            grille[i][j] = k;
            if (gen_grid(grille, pos + 1, size) == 1)
                return 1;
        }
    }
    grille[i][j] = -1;
    return 0;
}

