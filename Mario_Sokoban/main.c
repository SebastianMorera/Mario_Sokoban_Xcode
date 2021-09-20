//
//  main.c
//  Mario_Sokoban
//
//  Created by Sebastian Morera on 2021-08-31.
//  Jeu de Mario Sokoban


#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "constantes.h"
#include "jeu.h"
#include "editeur.h"

#define WINDOW_WIDTH (800)
#define WINDOW_HEIGHT (600)

void SDL_ExitWithDestruction(SDL_Renderer *renderer, SDL_Window *window, const char *message);
void SDL_ExitWithError(const char *message);

#define TAILLE_MAX 1000

int main()
{
    char *title = "Mario Sokoban";
    int continuer = 1;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *menu = NULL;
    SDL_Texture *textureMenu = NULL;
    SDL_Event event;

    SDL_Rect positionMenu;
    positionMenu.x = 0;
    positionMenu.y = 0;

    // Initialisation SDL + affichage fênetre avec une image + une icone de fênetre
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Lancement SDL, chargement de tous les systemes
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_ExitWithError("Initialisation de la SDL");

    // Création fenêtre + rendu
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
    SDL_RenderClear(renderer); // Clear the entire screen to our selected color.

    // Création de l'icone pour la fênetre
    SDL_Surface *icone = IMG_Load("caisse.jpg");
    SDL_SetWindowIcon(window, icone);
    SDL_FreeSurface(icone);

    /* Chargement et blittage du menu sur la scène */
    menu = IMG_Load("menu.jpg");
    if (menu == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger image");

    textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
    SDL_FreeSurface(menu);

    if (textureMenu == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de creer la texture");

    if(SDL_QueryTexture(textureMenu, NULL, NULL, &positionMenu.w, &positionMenu.h) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger la texture");

    if(SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible d afficher la texture");

    SDL_RenderPresent(renderer); // Afficher l'image de fond
    
    // Events (ce que le programme doit faire)
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    while(continuer)
        {
            SDL_WaitEvent(&event);
            switch (event.type)
            {
                case SDL_QUIT:
                    continuer = 0;
                    break;
                    
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                            continuer = 0;
                            break;
                          
                        case SDLK_KP_1: // Demande à jouer
                            jouer(renderer);
                            
                            SDL_QueryTexture(textureMenu, NULL, NULL, &positionMenu.w, &positionMenu.h);
                            SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu);
                            SDL_RenderPresent(renderer); // Afficher l'image de fond
                            break;
                            
                        case SDLK_KP_2: // Demande l'éditeur de niveaux
                            editeur(renderer);
                            
                            SDL_QueryTexture(textureMenu, NULL, NULL, &positionMenu.w, &positionMenu.h);
                            SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu);
                            SDL_RenderPresent(renderer); // Afficher l'image de fond
                            break;
                            
                        default:
                            break;
                    }
                    break;
                    
                default:
                    break;
            }
        }

    // Destruction de tous les élements crées
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void SDL_ExitWithDestruction(SDL_Renderer *renderer, SDL_Window *window, const char *message)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur: %s > %s \n", message ,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}
