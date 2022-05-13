cmake_minimum_required(VERSION 3.21)
project(projet_SDD1_TAKUZU C)

set(CMAKE_C_STANDARD 99)

add_executable(projet_SDD1_TAKUZU main.c resolution_auto.c resolution_auto.h affichage.c affichage.h resolution.c resolution.h test_matrices.c test_matrices.h generateur_grille.c generateur_grille.h fonctions_utilitaires.c fonctions_utilitaires.h)
