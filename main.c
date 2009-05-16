#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "menu.h"
#include "gestionCircuit.h"
#include "gestionFichiers.h"


int main(int argc, char *argv[]) {
	Uint32 initflags = SDL_INIT_VIDEO;  //See documentation for details
	SDL_Surface *ecran;
	Partie *partie;
	Scores *scores;

	Uint8  video_bpp = 32;
	Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	
	partie=malloc(sizeof(Partie));
	
	//lecture du fichiers texte
	lireCircuits(partie->nomsCircuits);
	
	
	// Initialize the SDL library
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	//Initialize the SDL_ttf library
	if(TTF_Init() < 0 ){
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", 
				TTF_GetError());
		exit(1);
	}
	
	
	
	// Set 640x480 video mode 
	ecran=SDL_SetVideoMode(800,600, video_bpp, videoflags);
    if (ecran == NULL) {
		fprintf(stderr, "Couldn't set 640x480x%d video mode: %s\n",
				video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	SDL_WM_SetCaption("Jeu de course de voitures en 2D !", NULL);
	
	initialiserPartie(partie);
	initialiserTouche(&(partie->clavier));
	initialiserScores(scores);

	while(partie->menu != MenuQuitter) {
		gestionMenu(ecran, partie, scores);
		if(partie->menu == MenuJeu)
			gestionCircuit(ecran, partie);
	}
	
	SDL_FreeSurface(ecran);
	
	
	// Clean up the SDL library 
	TTF_Quit();
	SDL_Quit();
	return(0);
}
