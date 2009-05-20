#ifndef COLLISIONS_H
#define COLLISIONS_H
#include "gestionCircuit.h"

/*teste les collisions, retourne 1 s'il y a collision 
et déplace la voiture de façon à ce qu'il n'y ait plus collision*/
int testerCollision(SDL_Rect position,Voiture *voiture,Circuit circuit);

/*remplit un tableau en donnant une valeur à chaque case en fonction de la couleur du pixel
correspondant dans l'image *surface*/
int chargerMasque(int **tabMasque,int largeur, int hauteur, SDL_Surface *surface);

/*teste la présence de checkpoint entre la position précédente et la position actuelle de la voiture*/
int testerCheckpoints ( int **tabCheckpoints, int nCheckpoints, SDL_Rect posPrec, Voiture *car);

#endif
 
