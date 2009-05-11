#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "gestionCircuit.h"
//fonction qui teste l'existence de collision et renvoie 0 ou 1
int testerCollision(SDL_Rect position,Voiture *voiture,Circuit circuit);
int lectureCouleur (char cheminImage[], SDL_Rect position,  unsigned char pixel[3]);
int chargerMasque(int **tabMasque,int largeur, int hauteur, SDL_Surface *surface);

#endif
 
