#ifndef AFFICHAGE_H
#define AFFICHAGE_H
void affichage(SDL_Surface *ecran, Voiture *voiture, Circuit circuit, Camera *camera, int nbrDeJoueurs);
int affichageDecompte(SDL_Surface *ecran, Voiture *voiture, Circuit circuit, Camera *camera, int nbrDeJoueurs, int *compteur, int *tempsPrec, int tempsPause);
int ecranChargement (SDL_Surface * ecran);

#endif