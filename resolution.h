/* ----------------------------------   resolution.h   ----------------------------------
 *
 *      ==> header de resolution.c
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  -------------------------------------------------------------------------------------
 */
#ifndef PROJET_SDD1_TAKUZU_RESOLUTION_H
#define PROJET_SDD1_TAKUZU_RESOLUTION_H


#include "test_matrices.h"

void resoudre(int **masque, int **solution, int size);

int **generer_masque(int size, int niveau);

COORDS choisir_case(int **tab, int size);

#endif //PROJET_SDD1_TAKUZU_RESOLUTION_H
