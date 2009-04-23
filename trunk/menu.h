#ifndef MENU_H
#define MENU_H

typedef struct partie{
	char nomJoueur1;
	int voiture1;
	int joueur2;
	char nomJoueur2;
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
int initialiserPartie(Partie *partie);

#endif