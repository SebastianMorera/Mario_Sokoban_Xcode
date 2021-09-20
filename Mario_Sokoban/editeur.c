//
//  editeur.c
//  Mario_Sokoban
//
//  Created by Sebastian Morera on 2021-09-01.
//

#include "editeur.h"
#include "fichiers.h"
#include "constantes.h"
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

void editeur(SDL_Renderer *renderer)
{
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL;
    SDL_Rect position;
    SDL_Event event;
    
    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    
    // Chargement des objets et du niveau
    mur = IMG_Load("mur.jpg");
    SDL_Texture *textureMur = SDL_CreateTextureFromSurface(renderer, mur);
    SDL_FreeSurface(mur);
    
    caisse = IMG_Load("caisse.jpg");
    SDL_Texture *textureCaisse = SDL_CreateTextureFromSurface(renderer, caisse);
    SDL_FreeSurface(caisse);
    
    objectif = IMG_Load("objectif.png");
    SDL_Texture *textureObjectif = SDL_CreateTextureFromSurface(renderer, objectif);
    SDL_FreeSurface(objectif);
    
    mario = IMG_Load("mario_bas.gif");
    SDL_Texture *textureMario = SDL_CreateTextureFromSurface(renderer, mario);
    SDL_FreeSurface(mario);

    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);
    
    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                    clicGaucheEnCours = 1; // On retient qu'un bouton est enfoncé
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) // Clic droit pour effacer
                {
                    carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
                
            case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            
            case SDL_MOUSEMOTION:
                if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                }
                else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
                
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                        
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                        
                    case SDLK_c:
                        chargerNiveau(carte);
                        break;
                        
                    case SDLK_KP_1:
                        objetActuel = MUR;
                        break;
                        
                    case SDLK_KP_2:
                        objetActuel = CAISSE;
                        break;
                        
                    case SDLK_KP_3:
                        objetActuel = OBJECTIF;
                        break;
                        
                    case SDLK_KP_4:
                        objetActuel = MARIO;
                        break;
                }
                break;
        }
        
        /* On efface l'écran */
        SDL_RenderClear(renderer); // Clear the entire screen to our selected color.

        // Placement des objets à l'écran
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_QueryTexture(textureMur, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureMur, NULL, &position);
                        break;
                    case CAISSE:
                        SDL_QueryTexture(textureCaisse, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureCaisse, NULL, &position);
                        break;
                    case OBJECTIF:
                        SDL_QueryTexture(textureObjectif, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureObjectif, NULL, &position);
                        break;
                    case MARIO:
                        SDL_QueryTexture(textureMario, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureMario, NULL, &position);
                        break;
                }
            }
        }
        
        // Mise à jour de l'écran
        SDL_RenderPresent(renderer);
        
    } // Fin du while

}
