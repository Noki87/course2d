#ifndef GESTIONCIRCUIT_H
#define GESTIONCIRCUIT_H

#include <SDL/SDL.H>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "menu.h"

typedef struct vecteur{
        double x;
        double y;
        double val;
        double alpha;
} Vecteur;

typedef struct voiture{
        SDL_Surface     *image;
        SDL_Rect position;
        double angleR;
        int angleD;
        int vitessemax,masse;
        Vecteur vitesse,acceleration;
        Vecteur fMoteur,fFrot,frottements;
        int haut,bas,gauche,droite;
        int angle;
        char nom[20];
        char cheminImage[25];
		int checkpoints;
		int ***tabVoiture;
} Voiture;

typedef struct circuit {
        int nbrImageX;
        int nbrImageY;
        int largeurImage;
        int hauteurImage;
        char ***image;
		int **tabMasque;
		int **tabCheckpoints;
} Circuit;

typedef struct  camera {
	SDL_Surface *fond[4];
	int coin[2];
	int coinprec[2];
	SDL_Rect *positionVoitures;
	SDL_Surface *** spriteVoiture;
	int temps;
	int nbrTour;
	int tourActuel;
} Camera;


int gestionCircuit( SDL_Surface *ecran, Partie *partie) ;

#endif
