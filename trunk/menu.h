#ifndef MENU_H
#define MENU_H
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
typedef enum {
	MenuAccueil = 0,
	MenuScores = 1,
	MenuJouer1 = 2,
	MenuJouer2 = 3,
	MenuJouer3 = 4,
	MenuJouer4 = 5,
	MenuOptions = 6,
	MenuPause = 7,
	MenuFinA = 8,
	MenuFinB = 9,
	MenuJeu = 10
} Menu;

typedef struct partie{
	char nomJoueur1[20];
	int voiture1;
	int joueur2;
	char nomJoueur2[20];
	int voiture2;
	int circuit;
	Menu menu;
	int saisieAutorisee;
	int pause;
	int affichage;
	int musique;
	int bruitage;
} Partie;

void chargerFond(SDL_Surface *ecran,Partie partie, SDL_Rect positionFond, Menu * menuPrecedent);
void gestionMenu (SDL_Surface *ecran, Partie *partie);
void menuScores (SDL_Event event, Partie *partie);
void menuAccueil(SDL_Event event, Partie *partie);
void menuJouer1(SDL_Event event, Partie *partie);
void menuJouer2(SDL_Surface *ecran,SDL_Event event, Partie *partie);
void menuJouer3(SDL_Event event, Partie *partie);
void menuJouer4(SDL_Event event, Partie *partie);
void menuOptions(SDL_Event event, Partie *partie);
void menuPause(SDL_Event event, Partie *partie);
void menuFinA(SDL_Event event, Partie *partie);
void menuFinB(SDL_Event event, Partie *partie);
int initialiserPartie(Partie *partie);
void saisirTexte (SDL_Event event, char mot[], SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Color couleur);

#endif
