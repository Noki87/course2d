#include <stdio.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "gestionCircuit.h"
#include "camera.h"

void camera (SDL_Surface *ecran, Circuit circuit, Voiture voiture, SDL_Surface *fond[], int coin[],int coinprec[], SDL_Rect *position) {
	SDL_Rect position_00, position_01, position_10 , position_11;
	int i, j, positionRelativeX, positionRelativeY, positionCameraX, positionCameraY;
	
	//position->x=400;
	//position->y=300;
	
	i = voiture.position.x / circuit.largeurImage;
	j = voiture.position.y / circuit.hauteurImage;
	positionRelativeX = voiture.position.x % circuit.largeurImage;
	positionRelativeY = voiture.position.y % circuit.hauteurImage;
	
	
	if(positionRelativeX > circuit.largeurImage - 400 || (i == 0 && positionRelativeX > 400)) {
		if(i == circuit.nbrImageX - 1) {
			position->x= positionRelativeX - (circuit.largeurImage - 800);
			positionCameraX = 800 - circuit.largeurImage;
		}
		else {
			positionCameraX =  circuit.largeurImage + 400 - positionRelativeX;
			coin[0]=i+1;
		}
	}
	else {
		if(i == 0) {
			position->x= positionRelativeX;
			positionCameraX = circuit.largeurImage;
		}
		else {
			positionCameraX = 400 - positionRelativeX;
			coin[0]=i;
		}
	}
	
	
	if(positionRelativeY > circuit.hauteurImage - 300 || (j == 0 && positionRelativeY > 300)) {
		if(j == circuit.nbrImageY - 1) {
			position->y= positionRelativeY - (circuit.hauteurImage - 600);
			positionCameraY = 600 - circuit.hauteurImage;
		}
		else {
			positionCameraY =  circuit.hauteurImage + 300 - positionRelativeY;
			coin[1]=j+1;
		}
	}
	else {
		if(j == 0) {
			position->y= positionRelativeY;
			positionCameraY = circuit.hauteurImage;
		}
		else {
			positionCameraY = 300 - positionRelativeY;
			coin[1]=j;
		}
	}
	
	
	
	if (coin[0] != coinprec[0] && coin[1] != coinprec[1]) {
		for(i=0; i<4;i++)
			SDL_FreeSurface(fond[i]);
		fond[0] = SDL_LoadBMP(circuit.image[coin[0]-1][coin[1]-1]);
		fond[1] = SDL_LoadBMP(circuit.image[coin[0]-1][coin[1]]);
		fond[2] = SDL_LoadBMP(circuit.image[coin[0]][coin[1]-1]);
		fond[3] = SDL_LoadBMP(circuit.image[coin[0]][coin[1]]);
		coinprec[0] = coin[0];
		coinprec[1] = coin[1];
	}
	
	
	printf ("positionRelativeX : %d\n",positionRelativeX);
	printf ("positionCameraX : %d\n",positionCameraX);
	printf ("coin[0] : %d\n",coin[0]);
	printf ("coin[1] : %d\n",coin[1]);
	printf ("positionRelativeY : %d\n",positionRelativeY);
	printf ("positionCameraY : %d\n",positionCameraY);
	
	
	position_00.x = positionCameraX - circuit.largeurImage;
	position_00.y = positionCameraY - circuit.hauteurImage;
	position_01.x = positionCameraX;
	position_01.y = positionCameraY - circuit.hauteurImage;
	position_10.x = positionCameraX - circuit.largeurImage;
	position_10.y = positionCameraY;
	position_11.x = positionCameraX;
	position_11.y = positionCameraY;
	
	SDL_BlitSurface(fond[0], NULL, ecran, &position_00);
	SDL_BlitSurface(fond[1], NULL, ecran, &position_01);
	SDL_BlitSurface(fond[2], NULL, ecran, &position_10);
	SDL_BlitSurface(fond[3], NULL, ecran, &position_11);
	
}
