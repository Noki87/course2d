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
	Uint32 initflags = SDL_INIT_VIDEO;
	SDL_Surface *ecran;
	Partie *partie;
	Scores *scores;

	Uint8  video_bpp = 32;
	Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	
	scores=malloc(sizeof(Scores));
	if(scores==NULL)return 4;
	partie=malloc(sizeof(Partie));
	if(partie==NULL)return 4;

	//lecture du fichiers texte
	lireCircuits(partie->nomsCircuits);
	
	
	// Initilisation de la SDL
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Erreur d'initialisation de SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	//Initilisation de la SDL_TTF
	if(TTF_Init() < 0 ){
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", 
				TTF_GetError());
		exit(1);
	}
	
	
	
	// Afficgahe en 800x600 
	ecran=SDL_SetVideoMode(800,600, video_bpp, videoflags);
    if (ecran == NULL) {
		fprintf(stderr, "Mise en 800x600x%d de la video impossible: %s\n",
				video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	SDL_WM_SetCaption("Jeu de course de voitures en 2D !", NULL);
	
	//Initialisation des parametres de la partie
	initialiserPartie(partie);
	initialiserTouche(&(partie->clavier));
	initialiserScores(scores);

	//Boucle du jeu
	while(partie->menu != MenuQuitter) {
		gestionMenu(ecran, partie, scores);
		if(partie->menu == MenuJeu)
			gestionCircuit(ecran, partie, scores);
	}
	
	SDL_FreeSurface(ecran);
	
	free(scores);
	free(partie);
	
	// Clean up the SDL library 
	TTF_Quit();
	SDL_Quit();
	return(0);
}
