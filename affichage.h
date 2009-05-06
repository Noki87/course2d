#ifndef AFFICHAGE_H
#define AFFICHAGE_H
void affichage(SDL_Surface *ecran, Voiture voiture, Circuit circuit, Camera *camera);
int affichageDecompte(SDL_Surface *ecran, Voiture voiture, Circuit circuit, Camera *camera);
int ecranChargement (SDL_Surface * ecran);

#endif