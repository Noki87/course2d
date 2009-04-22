#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include "gestionCircuit.h"
#include "physique.h"
#include "affichage.h"

int allocationVoiture (SDL_Surface ***surface, char nomVoiture[]) {
	int i;
	for (i=0;i<32;i++){
		nomVoiture[13]=i-(i/10)*10+48;
		nomVoiture[12]=(i/10)+48;
		(*surface)[i] = SDL_LoadBMP(nomVoiture);
		if ((*surface)[i] == NULL) {
			printf("Unable to load bitmap: %s\n", SDL_GetError());
			return 1;
		}
		SDL_SetColorKey((*surface)[i], SDL_SRCCOLORKEY, SDL_MapRGB((*surface)[i]->format, 97, 68, 43));
	}
	
	return 0;
}


int initialisation (SDL_Surface ***spriteVoitures, Voiture voitures[], Circuit * circuit, int nbrDeJoueurs, int coin[], int coinprec[]) {
	int i,j;
	char ***tab;	
	
	//initialisation des voitures 
	for (i=0; i<nbrDeJoueurs; i++) 
		initialisationVoitures (&voitures[i]);
	
	//allocation des voitures	
	for (i=0; i<nbrDeJoueurs; i++) {
		spriteVoitures[i] = malloc(32 * sizeof(SDL_Surface *));
		allocationVoiture(&spriteVoitures[i], voitures[i].cheminImage);
	}
	
	//initialisation du circuit

	circuit->nbrImageX=2;
	circuit->nbrImageY=2;
	circuit->largeurImage=1024;
	circuit->hauteurImage=768;
	
	tab=(char ***)calloc(2,sizeof(char**)); 

	for(i=0;i<2;i++)  {
		tab[i]=(char **) calloc( 2 ,sizeof(char*));
		for(j=0;j<2;j++) {
			tab[i][j]=(char *) calloc( 1024 ,sizeof(char));
			strcpy_s(tab[i][j],14,"Circuit\\1.bmp");
		}
	}
	circuit->image=tab;
	
	
	
	//initialisation camera
	coin[0] =  coin[1] = 1;
	coinprec[0] = coinprec[1] = 0;
	
	
	return 0;
}


int main(int argc, char *argv[]) {
	Uint32 initflags = SDL_INIT_VIDEO;  //See documentation for details
	SDL_Surface *ecran;
	Uint8  video_bpp = 32;
	Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	int done,i;
	int tempsPrecedent = 0, tempsActuel = 0;
	int nbrDeJoueurs = 1;

	SDL_Event event;
	SDL_Rect position;
	
	SDL_Surface ***sprite;// ={NULL} ;
	SDL_Surface * fond[4];

	Voiture voitures[1];
	Circuit circuit;
	int coin[2];
	int coinprec[2];

	
	if((sprite=malloc(nbrDeJoueurs * sizeof(SDL_Surface **)))==NULL){
	return 1;
	}

	// Initialize the SDL library
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	// Set 800x600 video mode 
	ecran=SDL_SetVideoMode(800,600, video_bpp, videoflags);
    if (ecran == NULL) {
		fprintf(stderr, "Couldn't set 800x600 video mode: %s\n",
				video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	SDL_WM_SetCaption("Jeu de course de voitures en 2D !", NULL);
	
	
	
	position.x = 280;
	position.y = 280;
	
	
	
	
	if(initialisation(sprite, voitures, &circuit, nbrDeJoueurs, coin, coinprec)==1){
		return 4;
	}
	
	SDL_EnableKeyRepeat(10, 10);
	done = 0;
	while ( !done ) {
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 30){
			tempsPrecedent = tempsActuel;
			deplacer(voitures);
			affichage(ecran,voitures[0],sprite[0],circuit.image,coin,coinprec,&position,fond);
			SDL_PollEvent(&event);
			if(event.type==SDL_KEYDOWN){
				if((event.key.keysym.sym)==SDLK_UP) voitures[0].haut=1;
				if((event.key.keysym.sym)==SDLK_DOWN) voitures[0].bas=1;
				if((event.key.keysym.sym)==SDLK_LEFT) voitures[0].gauche=1;
				if((event.key.keysym.sym)==SDLK_RIGHT) voitures[0].droite=1;
				if((event.key.keysym.sym)==SDLK_ESCAPE)done = 1;
			}
			if(event.type==SDL_KEYUP){
				if((event.key.keysym.sym)==SDLK_UP)voitures[0].haut=0;
				if((event.key.keysym.sym)==SDLK_DOWN)voitures[0].bas=0;
				if((event.key.keysym.sym)==SDLK_LEFT)voitures[0].gauche=0;
				if((event.key.keysym.sym)==SDLK_RIGHT)voitures[0].droite=0;
			}
			if(event.type==SDL_QUIT)
				done = 1;
		}
		else // Si ça fait moins de 30ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut
		{
			SDL_Delay(30 - (tempsActuel - tempsPrecedent));
		}
	}
	
	SDL_FreeSurface(ecran);
	
//	for(i=0; i<33;i++)
//		SDL_FreeSurface(sprite[0][i]);
	 
	for(i=0; i<4;i++)
		SDL_FreeSurface(fond[i]);
	// Clean up the SDL library */
	SDL_Quit();
	return(0);
}

