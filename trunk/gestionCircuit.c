#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "menu.h"
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


int initialisation (SDL_Surface *** spriteVoitures, Voiture voitures[], Circuit * circuit, int nbrDeJoueurs, int coin[], int coinprec[]) {
	int i,j;
	char *** tab;	
	
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
	
	tab=(char ***)calloc(circuit->nbrImageX,sizeof(char**)); 

	for(i=0;i<circuit->nbrImageX;i++)  {
		tab[i]=(char **) calloc( circuit->nbrImageY ,sizeof(char*));
		for(j=0;j<circuit->nbrImageY;j++) {
			tab[i][j]=(char *) calloc( 1024 ,sizeof(char));
			strcpy(tab[i][j],"Circuit/3.bmp");
		}
	}
	circuit->image=tab;
	
	
	
	//initialisation camera
	coin[0] =  coin[1] = 1;
	coinprec[0] = coinprec[1] = 0;
	
	
	return 0;
}

int gestionCircuit( SDL_Surface *ecran, Partie *partie) {
	
	SDL_Rect position;
	int    done,i;
	int tempsPrecedent = 0, tempsActuel = 0;
	
	SDL_Event event;

	int nbrDeJoueurs = 1;
	SDL_Surface * fond[4];
	SDL_Surface *** sprite = malloc(nbrDeJoueurs * sizeof(SDL_Surface **));
	Voiture voitures[1];
	Circuit circuit;
	int coin[2];
	int coinprec[2];
	
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
			affichage(ecran,voitures[0],sprite[0],circuit,coin,coinprec,&position,fond);
			SDL_PollEvent(&event);
			if(event.type==SDL_KEYDOWN){
				if((event.key.keysym.sym)==SDLK_UP) voitures[0].haut=1;
				if((event.key.keysym.sym)==SDLK_DOWN) voitures[0].bas=1;
				if((event.key.keysym.sym)==SDLK_LEFT) voitures[0].gauche=1;
				if((event.key.keysym.sym)==SDLK_RIGHT) voitures[0].droite=1;
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
	
	for(i=0; i<32;i++)
		SDL_FreeSurface(sprite[0][i]);
	
	for(i=0; i<4;i++)
		SDL_FreeSurface(fond[i]);
	
	return 0;
}
