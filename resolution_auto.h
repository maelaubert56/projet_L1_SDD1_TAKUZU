/* ----------------------------------   resolution_auto.h   ----------------------------------
 *
 *      ==> header de resolution_auto.c
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  ------------------------------------------------------------------------------------------
 */  #ifndef PROJET_SDD1_TAKUZU_RESOLUTION_AUTO_H
#define PROJET_SDD1_TAKUZU_RESOLUTION_AUTO_H

typedef struct {
    int i;
    int j;
} COORDONNE;

void resolve_auto();

COORDONNE modif_mat_bloquee();

#endif //PROJET_SDD1_TAKUZU_RESOLUTION_AUTO_H
