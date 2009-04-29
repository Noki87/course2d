#ifndef GESTIONCIRCUIT_H
#define GESTIONCIRCUIT_H

#include <SDL/SDL.H>
#include <SDL/SDL_ttf.h>
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
} Voiture;

typedef struct circuit {
        int nbrImageX;
        int nbrImageY;
        int largeurImage;
        int hauteurImage;
        char ***image;
		int **tabMasque;
} Circuit;

int gestionCircuit( SDL_Surface *ecran, Partie *partie) ;

#endif
