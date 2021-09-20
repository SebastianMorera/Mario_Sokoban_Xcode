//
//  constantes.h
//  Mario_Sokoban
//
//  Created by Sebastian Morera on 2021-09-01.
//  Rôle: définit des constantes pour tout le programme (taille de la fenêtre...)

#ifndef constantes_h
#define constantes_h

#include <stdio.h>

#define TAILLE_BLOC         34 // Taille d'un bloc (carré) en pixels
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum {HAUT, BAS, GAUCHE, DROITE};
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif /* constantes_h */
