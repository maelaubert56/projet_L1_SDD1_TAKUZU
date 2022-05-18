/* ----------------------------------   main.c   ----------------------------------
 *
 *      ==> lance le programme via la fonction main().
 *      ==> lance le menu permettant l'appel des différentes fonctionalitées du programme.
 *
 *  Auteurs : Maël Aubert, Marius Chevailler
 *  --------------------------------------------------------------------------------
 */

#include <stdio.h>
#include "resolution_auto.h"
#include <stdlib.h>
#include "affichage.h"
#include "resolution.h"
#include "generateur_grille.h"
#include <math.h>
#include "time.h"

#include "fonctions_utilitaires.h"

#ifdef _WIN32
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

//prototypes:
int menu_resoudre_manuel();
int menu_generer_grille();


int main() {
    srand(time(NULL)); // initialise le random
    int choix, continuer = 1;
    color(15, 0);
    while (continuer == 1) {
        clear_screen();
        printf("----------------- BIENVENUE SUR NOTRE TAKUZU ! ---------------\n");
        printf("Veuillez choisir une option : \n");
        printf("\t1 - R%csoudre une grille \n", 130);
        printf("\t2 - R%csoudre une grille automatiquement \n", 130);
        printf("\t3 - G%cn%crer une grille de Takuzu\n", 130, 130);
        printf("\t4 - Quitter le jeu\n");
        printf("==>");

        choix = saisieint();

        switch (choix) {
            case 1: {
                menu_resoudre_manuel();
                break;
            }
            case 2: {
                resolve_auto();
                break;
            }
            case 3: {
                menu_generer_grille();
                break;
            }
            case 4: {
                continuer = 0;
                break;
            }
            default : {
                printf("Vous devez entrer une valeur entre 1 et 5...\n");
                Sleep(2000);
                break;
            }
        }
    }
    return 0;
}


// fonctions des menus
int menu_resoudre_manuel() {

    // valeurs par default si le joueur veut lancer directement
    int choice, continuer = 1, size = 4, num_niveau = 1;
    char *mode = "auto", *niveau = "facile";

    printf("------------ Choisisez entre 4x4 ou 8x8 ------------\n");
    printf("\t1 -> 4x4\n\t2 -> 8x8\n\t3 -> 16x16\n==>");
    do {
        size = saisieint();
    } while (size != 1 && size != 2 && size != 3);
    size = (int) pow(2, size + 1);

    int **masque = generer_masque(size, num_niveau); // genere un masque pour eviter un conflit entre la taille de la solution et la taille du masque

    int soluc4[4][4] = {{1, 0, 0, 1},
                        {1, 0, 1, 0},
                        {0, 1, 1, 0},
                        {0, 1, 0, 1}};


    int soluc8[8][8] = {{0, 1, 0, 1, 1, 0, 0, 1},
                        {1, 0, 0, 1, 0, 0, 1, 1},
                        {0, 1, 1, 0, 0, 1, 1, 0},
                        {1, 1, 0, 0, 1, 1, 0, 0},
                        {0, 0, 1, 1, 0, 0, 1, 1},
                        {0, 1, 0, 1, 1, 0, 1, 0},
                        {1, 0, 1, 0, 1, 1, 0, 0},
                        {1, 0, 1, 0, 0, 1, 0, 1}};

    int soluc16[16][16] = {
            {1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1},
            {0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1},
            {0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0},
            {0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1},
            {0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0},
            {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
            {1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0},
            {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1},
            {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0},
            {0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1},
            {1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0},
            {0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
            {1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0}};


    int **soluc = malloc(sizeof(int *) * size);

    if (size == 4) {
        for (int i = 0; i < size; i++) {
            soluc[i] = malloc(sizeof(int) * size);
            for (int j = 0; j < size; j++) {
                soluc[i][j] = soluc4[i][j];

            }
        }
    }
    if (size == 8) {
        for (int i = 0; i < size; i++) {
            soluc[i] = malloc(sizeof(int) * size);
            for (int j = 0; j < size; j++) {
                soluc[i][j] = soluc8[i][j];

            }
        }
    }

    if (size == 16) {
        for (int i = 0; i < size; i++) {
            soluc[i] = malloc(sizeof(int) * size);
            for (int j = 0; j < size; j++) {
                soluc[i][j] = soluc16[i][j];
            }
        }
    }

    while (continuer == 1) {
        printf("----------------- Resoudre une grille ---------------\n");
        printf("   Taille : %dx%d\t\tMasque : %s\t\tNiveau : %s\n", size, size, mode, niveau);
        printf("Veuillez choisir une option : \n");
        printf("\t1 - Saisir un masque manuellement \n");
        printf("\t2 - G%cn%crer un masque automatiquement\n", 130, 130);
        printf("\t3 - Jouer \n");
        printf("\t4 - Retour\n");
        printf("==>");
        choice = saisieint();
        switch (choice) {

            case 1: {
                mode = "personnalise";
                printf("------------ Entrez le masque ------------\n");
                masque = remplir_matrice(size);
                printf("Votre masque est :\n");
                afficher_matrice(masque, size);
                printf("\n");
                break;
            }

            case 2: {
                mode = "auto";
                printf("------------ Generation automatique du masque ------------\n");
                int continuer_menu = 1;
                while (continuer_menu == 1) {
                    printf("Entrez le niveau de difficulte : \n\t1 - facile\n\t2 - moyen\n\t3 - difficile\n==>");
                    num_niveau = saisieint();
                    switch (num_niveau) {
                        case 1:
                            niveau = "facile";
                            continuer_menu = 0;
                            break;
                        case 2:
                            niveau = "moyen";
                            continuer_menu = 0;
                            break;
                        case 3:
                            niveau = "difficile";
                            continuer_menu = 0;
                            break;
                        default:
                            printf("Vous devez entre un chiffre entre 1 et 3...");
                            break;
                    }
                }

                printf("Masque genere automatiquement ...\n");
                masque = generer_masque(size, num_niveau);
                printf("Votre masque est :\n");
                afficher_matrice(masque, size);
                printf("\n");
                wait_for_enter();
                break;
            }
            case 3: {
                resoudre(masque, soluc, size);
                continuer = 0;
                break;
            }
            case 4: {
                continuer = 0;
                break;
            }
            default : {
                printf("Vous devez entrer une valeur entre 1 et 4...\n");
                break;
            }
        }
    }
    return 0;
}

int menu_generer_grille() {
    int size, choice, continuer = 1;
    while (continuer == 1) {
        clear_screen();
        printf("Choisir la taille de la matrice\n\t1 - matrice 4x4\n\t2 - matrice 8x8\n\t3 - matrice 16x16\n==>");
        size = saisieint();
        while (size != 1 && size != 2 && size != 3) {
            printf("\nVous devez saisir un entier entre 1 et 3:\n");
            size = saisieint();
        }
        size = (int) pow(2, size + 1);
        printf("Veuillez choisir une option : \n");
        printf("\t1 - Afficher l'ensemble des lignes et colonnes valides \n");
        printf("\t2 - G%cn%crer une grille de Takuzu\n", 130, 130);
        printf("\t3 - Retour\n");
        printf("==>");
        choice = saisieint();
        switch (choice) {
            case 1: {
                afficher_lignes_valides(size);
                wait_for_enter();
                break;
            }
            case 2: {
                int **grid = generer_grille(size);
                printf("Matrice %dx%d generee:\n", size, size);
                afficher_matrice(grid, size);
                wait_for_enter();
                continuer = 0;
            }
                break;
            case 3: {
                continuer = 0;
                break;
            }
            default : {
                printf("Vous devez entrer une valeur entre 1 et 3...\n");
                break;
            }
        }
    }
    return 0;
}
