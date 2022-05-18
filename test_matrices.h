/* ----------------------------------   test_matrices.h   ----------------------------------
 *
 *      ==> header de test_matrices.c
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  ------------------------------------------------------------------------------------------
 */

#ifndef PROJET_SDD1_TAKUZU_TEST_MATRICES_H
#define PROJET_SDD1_TAKUZU_TEST_MATRICES_H

typedef struct {
    int i;
    int j;
} COORDS;


int ligne_remplie(int y, int **tab, int size);

int colonne_remplie(int x, int **tab, int size);

int test_suite(int y, int x, int **tab, int size);

int test_autour(int y, int x, int **tab, int size);

int test_case(int y, int x, int **tab, int size);

int test_remplissage(int **tab, int size);

int verif_grille(int **grille_jeu, int **grille_soluc, int size);

int verif_valide(int **grille_jeu, COORDS coords, int size, int val);

int verif_valide_gen(int **grille_jeu, int i, int j, int size, int val);

//int grille_valide(int** grille, int size);
int verif_tab_id(int *tab1, int *tab2, int size);

//int verif_all_lignes_idd(int** tab,int size);
int test_lignes_id(int i, int **grille, int size);

#endif //PROJET_SDD1_TAKUZU_TEST_MATRICES_H
