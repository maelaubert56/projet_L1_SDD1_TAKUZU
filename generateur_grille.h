/* ----------------------------------   generateur_grille.h   ----------------------------------
 *
 *      ==> header de generateur_grille.c
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  --------------------------------------------------------------------------------------------
 */

#ifndef PROJET_SDD1_TAKUZU_GENERATEUR_GRILLE_H
#define PROJET_SDD1_TAKUZU_GENERATEUR_GRILLE_H

int **generer_grille(int);

void afficher_lignes_valides(int);

int gen_grid(int **grille, int pos, int size);

#endif //PROJET_SDD1_TAKUZU_GENERATEUR_GRILLE_H
