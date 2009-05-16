#ifndef PHYSIQUE_H
#define PHYSIQUE_H
#include <SDL/SDL.H>
#include "gestionCircuit.h"
void deplacer(Voiture *car, Circuit circuit,SDL_Surface **sprite);
void projeter(Vecteur *vecteur, int choix);
void initVecteur(Vecteur *vecteur);
int initialisationVoitures (Voiture *voiture, Partie partie, Circuit *circuit, int numeroJoueur);
#endif