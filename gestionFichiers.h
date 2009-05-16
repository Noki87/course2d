#ifndef GESTIONFICHIERS_H
#define GESTIONFICHIERS_H
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "gestionCircuit.h"

int lireCircuits(char buffer[3][10]);
int lireVariables(Circuit *circuit);
int lireScores(Partie *partie, Scores *scores);
int insererScore(Partie *partie, Scores *scores);

#endif


