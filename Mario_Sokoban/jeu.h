//
//  jeu.h
//  Mario_Sokoban
//
//  Created by Sebastian Morera on 2021-09-01.
//  Rôle: prototypes des fonctions du jeu.

#ifndef jeu_h
#define jeu_h

#include <SDL2/SDL.h>
#include "constantes.h"

void jouer(SDL_Renderer *renderer);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);


#endif /* jeu_h */
