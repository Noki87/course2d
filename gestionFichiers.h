#ifndef GESTIONFICHIERS_H
#define GESTIONFICHIERS_H
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "gestionCircuit.h"

/*lit le fichier circuits.txt contenant les noms des 3 circuits*/
int lireCircuits(char buffer[3][10]);

/*lit les variable de la structure circuit dans le fichier texte associé*/
int lireVariables(Circuit *circuit);

/*lit les scores dans les fichiers score1.txt, score2.txt, score3.txt*/
int lireScores(Partie *partie, Scores *scores);

/*lit les scores dans les fichiers score1.txt, score2.txt, score3.txt*/
int insererScore(Partie *partie, Scores *scores);

#endif


