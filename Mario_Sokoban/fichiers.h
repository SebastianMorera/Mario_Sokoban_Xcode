//
//  fichiers.h
//  Mario_Sokoban
//
//  Created by Sebastian Morera on 2021-09-01.
//

#ifndef fichiers_h
#define fichiers_h

#include <stdio.h>
#include "constantes.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR]);
int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]);

#endif /* fichiers_h */
