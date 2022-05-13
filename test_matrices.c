/* ----------------------------------   test_matrices.c   ----------------------------------
 *
 *      ==> contient tous les tests qui vérifiernt la validité d'une position, d'un grille entiere, d'une ligne, etc...
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  ------------------------------------------------------------------------------------------
 */

#include "test_matrices.h"


int verif_valide_gen(int **grille_jeu, COORDS coords, int size, int val) {
    int temp;

    temp = ligne_remplie(coords.i, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -1;

    temp = colonne_remplie(coords.j, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -2;

    temp = test_suite(coords.i, coords.j, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -3;

    temp = test_autour(coords.i, coords.j, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -4;

    if (test_lignes_id(coords.i, grille_jeu, size) != -1) return -5;

    return 1;
}


int verif_valide(int **grille_jeu, COORDS coords, int size, int val) {
    int temp;

    temp = ligne_remplie(coords.i, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -1;

    temp = colonne_remplie(coords.j, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -2;

    temp = test_suite(coords.i, coords.j, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -3;

    temp = test_autour(coords.i, coords.j, grille_jeu, size);
    if ((temp != -1) && ((temp + 1) % 2 != val)) return -4;

    return 1;
}

// tests
int ligne_remplie(int y, int **tab, int size) { // renvoit -1 si pas remplie, renvoie 0 ou 1 si on a le max de 0 ou de 1
    int i;
    int tabsomme[2] = {0, 0}; // nombre de cases à 0, 1
    for (i = 0; i < size; i++) {
        if (tab[y][i] == 0) tabsomme[0]++;
        else if (tab[y][i] == 1) tabsomme[1]++;
    }
    if (tabsomme[0] == size / 2) return 0;
    if (tabsomme[1] == size / 2) return 1;
    return -1;
}

int
colonne_remplie(int x, int **tab, int size) { // renvoit -1 si pas remplie, renvoie 0 ou 1 si on a le max de 0 ou de 1
    int i;
    int tabsomme[2] = {0, 0}; // nombre de cases à 0, 1
    for (i = 0; i < size; i++) {
        if (tab[i][x] == 0) tabsomme[0]++;
        else if (tab[i][x] == 1) tabsomme[1]++;
    }
    if (tabsomme[0] == size / 2) return 0;
    if (tabsomme[1] == size / 2) return 1;
    return -1;
}

int test_suite(int y, int x, int **tab, int size) { // renvoie -1 si pas de suite, 0 si suite de 0, 1 si suite de 1
    if ((x > 1) && (tab[y][x - 1] == tab[y][x - 2] && tab[y][x - 1] != -1))
        return tab[y][x - 1]; // on test a gauche de la case
    if ((x < size - 2) && (tab[y][x + 1] == tab[y][x + 2]) && tab[y][x + 1] != -1)
        return tab[y][x + 1]; // on test a droite de la case
    if ((y > 1) && (tab[y - 1][x] == tab[y - 2][x]) && tab[y - 1][x] != -1)
        return tab[y - 1][x]; // on test au dessus de la case
    if ((y < size - 2) && (tab[y + 1][x] == tab[y + 2][x]) && tab[y + 1][x] != -1)
        return tab[y + 1][x]; // on test en dessous de la case
    return -1;
}

int test_autour(int y, int x, int **tab, int size) { // renvoie -1 si pas entouré, 0 si entouré de 0, 1 si entouré de 1
    if ((x > 0) && (x < size - 1) && (tab[y][x - 1] == tab[y][x + 1])) return tab[y][x - 1]; // on test a l'horizontale
    if ((y > 0) && (y < size - 1) && (tab[y - 1][x] == tab[y + 1][x])) return tab[y - 1][x]; // on test a la verticale
    return -1;
}


int test_case(int y, int x, int **tab, int size) {
    int temp;

    temp = ligne_remplie(y, tab, size);
    if (temp != -1) return (temp + 1) % 2;

    temp = colonne_remplie(x, tab, size);
    if (temp != -1) return (temp + 1) % 2;

    temp = test_suite(y, x, tab, size);
    if (temp != -1) return (temp + 1) % 2;

    temp = test_autour(y, x, tab, size);
    if (temp != -1) return (temp + 1) % 2;

    return -1;
}


int verif_grille(int **grille_jeu, int **grille_soluc, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (grille_jeu[i][j] != grille_soluc[i][j]) return 0;
        }
    }
    return 1;
}

int test_remplissage(int **tab, int size) {
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (tab[i][j] == -1) return 0;
        }
    }
    return 1;
}

int verif_tab_id(int *tab1, int *tab2, int size) {
    for (int i = 0; i < size; i++) {
        if (tab1[i] != tab2[i])return 0;
    }
    return 1;
}

int test_lignes_id(int i, int **grille, int size) {
    for (int k = 1; k < i; k++) {
        for (int z = k - 1; z >= 0; z--) {
            if (verif_tab_id(grille[k], grille[z], size)) return 2;
        }
    }

    return -1;
}