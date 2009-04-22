#include <stdio.h>
#include <SDL/SDL.h>
#include "camera.h"
#include "gestionCircuit.h"

void camera (SDL_Surface *ecran, char ***circuit1, SDL_Rect *position, int x, int y, int coin[],int coinprec[], SDL_Surface *fond[]) {
	SDL_Rect position_00, position_01, position_10 , position_11;	
	
	int largeurI = 1024;
	int hauteurI = 768;
	int largeurS = 800;
	int hauteurS = 600;
	
	position->x += x;
	position->y += y;
	
	
	if(position->x < largeurS - largeurI) { 
		if(coin[1] == 1) {
			position->x = largeurS - largeurI;
		}
		else {
			coin[1]++;
			position->x =  position->x + largeurI;
		}
	}
	if(position->x > largeurI) {
		if(coin[1]-1 == 0) {
			position->x = largeurI;
		}
		else {
			coin[1]--;
			position->x = position->x - largeurI;
		}
	}
	if(position->y < hauteurS - hauteurI) { 
		if(coin[0] == 1) {
			position->y = hauteurS - hauteurI;
		}
		else {
			coin[0]++;
			position->y = position->y + hauteurI;
		}
	}
	if(position->y > hauteurI) {
		if(coin[0]-1 == 0) {
			position->y = hauteurI;
		}
		else {
			coin[0]--;
			position->y = position->y - hauteurI;
		}
	}
	
	if (coin[0] != coinprec[0] && coin[1] != coinprec[1]) {
		fond[0] = SDL_LoadBMP(circuit1[coin[0]-1][coin[1]-1]);
		fond[1] = SDL_LoadBMP(circuit1[coin[0]-1][coin[1]]);
		fond[2] = SDL_LoadBMP(circuit1[coin[0]][coin[1]-1]);
		fond[3] = SDL_LoadBMP(circuit1[coin[0]][coin[1]]);
		coinprec[0] = coin[0];
		coinprec[1] = coin[1];
	}
	
	position_00.x = position->x - largeurI;
	position_00.y = position->y - hauteurI;
	position_01.x = position->x;
	position_01.y = position->y - hauteurI;
	position_10.x = position->x - largeurI;
	position_10.y = position->y;
	position_11.x = position->x;
	position_11.y = position->y;
	
	SDL_BlitSurface(fond[0], NULL, ecran, &position_00);
	SDL_BlitSurface(fond[1], NULL, ecran, &position_01);
	SDL_BlitSurface(fond[2], NULL, ecran, &position_10);
	SDL_BlitSurface(fond[3], NULL, ecran, &position_11);
	 
}
