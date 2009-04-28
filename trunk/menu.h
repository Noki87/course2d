#ifndef MENU_H
#define MENU_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
typedef struct partie{
        char nomJoueur1[20];
        int voiture1;
        int joueur2;
        char nomJoueur2[20];
        int voiture2;
        int circuit;
        int menu;
        int pause;
        int affichage;
        int musique;
        int bruitage;
} Partie;

void menuScores (SDL_Surface *ecran, Partie *partie);
void menuAccueil(SDL_Surface *ecran, Partie *partie);
void menuJouer1(SDL_Surface *ecran, Partie *partie);
void menuJouer2(SDL_Surface *ecran, Partie *partie);
void menuJouer3(SDL_Surface *ecran, Partie *partie);
void menuJouer4(SDL_Surface *ecran, Partie *partie);
void menuOptions(SDL_Surface *ecran, Partie *partie);
void menuPause(SDL_Surface *ecran, Partie *partie);
void menuFinA(SDL_Surface *ecran, Partie *partie);
void menuFinB(SDL_Surface *ecran, Partie *partie);
int initialiserPartie(Partie *partie);
char saisir (char mot[], SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Surface *imageDeFond);

#endif
