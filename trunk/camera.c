#include <stdio.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "gestionCircuit.h"
#include "camera.h"
#include "math.h"

void positionnerCamera (SDL_Surface *ecran, Circuit circuit, Voiture voiture, Camera * camera) {
	SDL_Rect position_00, position_01, position_10 , position_11;
	int i, j, positionRelativeX, positionRelativeY, positionCameraX, positionCameraY;
	
	//détermination du numero de l'image ou la voiture se trouve
	i = voiture.position.x / circuit.largeurImage;
	j = voiture.position.y / circuit.hauteurImage;
	
	//calcul de la position de la voiture sur  cette image 
	positionRelativeX = voiture.position.x % circuit.largeurImage;
	positionRelativeY = voiture.position.y % circuit.hauteurImage;
	
	
	camera->positionVoitures[0].x= 400;
	camera->positionVoitures[0].y= 300;
	
	//Gestion de l'axe horizontale
	if(positionRelativeX > circuit.largeurImage - 400 || (i == 0 && positionRelativeX > 400)) {
		if(i == circuit.nbrImageX - 1) {
			camera->positionVoitures[0].x= positionRelativeX - (circuit.largeurImage - 800);
			positionCameraX = 800 - circuit.largeurImage;
		}
		else {
			positionCameraX =  circuit.largeurImage + 400 - positionRelativeX;
			camera->coin[1]=i+1;
		}
	}
	else {
		if(i == 0) {
			camera->positionVoitures[0].x= positionRelativeX;
			positionCameraX = circuit.largeurImage;
		}
		else {
			positionCameraX = 400 - positionRelativeX;
			camera->coin[1]=i;
		}
	}
	
	//Gestion de l'axe verticale
	if(positionRelativeY > circuit.hauteurImage - 300 || (j == 0 && positionRelativeY > 300)) {
		if(j == circuit.nbrImageY - 1) {
			camera->positionVoitures[0].y= positionRelativeY - (circuit.hauteurImage - 600);
			positionCameraY = 600 - circuit.hauteurImage;
		}
		else {
			positionCameraY =  circuit.hauteurImage + 300 - positionRelativeY;
			camera->coin[0]=j+1;
		}
	}
	else {
		if(j == 0) {
			camera->positionVoitures[0].y= positionRelativeY;
			positionCameraY = circuit.hauteurImage;
		}
		else {
			positionCameraY = 300 - positionRelativeY;
			camera->coin[0]=j;
		}
	}
	
	

	//Mise à jour des images
	if (camera->coin[0] != camera->coinprec[0] || camera->coin[1] != camera->coinprec[1]) {
		for(i=0; i<4;i++)
			SDL_FreeSurface(camera->fond[i]);
		camera->fond[0] = SDL_LoadBMP(circuit.image[camera->coin[0]-1][camera->coin[1]-1]);
		camera->fond[1] = SDL_LoadBMP(circuit.image[camera->coin[0]-1][camera->coin[1]]);
		camera->fond[2] = SDL_LoadBMP(circuit.image[camera->coin[0]][camera->coin[1]-1]);
		camera->fond[3] = SDL_LoadBMP(circuit.image[camera->coin[0]][camera->coin[1]]);
		camera->coinprec[0] = camera->coin[0];
		camera->coinprec[1] = camera->coin[1];
	}
	
	//Cacul des postions de chaque image
	position_00.x = positionCameraX - circuit.largeurImage;
	position_00.y = positionCameraY - circuit.hauteurImage;
	position_01.x = positionCameraX;
	position_01.y = positionCameraY - circuit.hauteurImage;
	position_10.x = positionCameraX - circuit.largeurImage;
	position_10.y = positionCameraY;
	position_11.x = positionCameraX;
	position_11.y = positionCameraY;
	
	//Blit des images
	SDL_BlitSurface(camera->fond[0], NULL, ecran, &position_00);
	SDL_BlitSurface(camera->fond[1], NULL, ecran, &position_01);
	SDL_BlitSurface(camera->fond[2], NULL, ecran, &position_10);
	SDL_BlitSurface(camera->fond[3], NULL, ecran, &position_11);
	
}


void positionnerCamera2j (SDL_Surface *ecran, Circuit circuit, Voiture *voiture, Camera * camera) {
	SDL_Rect position_00, position_01, position_10 , position_11;
	int i, j, positionRelativeX, positionRelativeY, positionCameraX, positionCameraY, positionCentralX, positionCentralY;
	float a,b;
	
	//Calcul du baricentre des voitures
	if(abs(voiture[0].position.x - voiture[1].position.x) < 600 &&  abs(voiture[0].position.y - voiture[1].position.y)<400) {
		positionCentralX =  (voiture[0].position.x + voiture[1].position.x) /2;
		positionCentralY =  (voiture[0].position.y + voiture[1].position.y) /2;
	}
	else {
		if(abs(voiture[0].position.x - voiture[1].position.x) >= 600)
			a = 1 + (abs(voiture[0].position.x - voiture[1].position.x) - 600) / (800.0 - 600.0);
		else
			a=1;
		if(abs(voiture[0].position.y - voiture[1].position.y)>=400)
			b = 1 + (abs(voiture[0].position.y - voiture[1].position.y) - 400) / (600.0 - 500.0);
		else
			b=1;
		if(voiture[0].checkpoints < voiture[1].checkpoints) {
			positionCentralX =  (voiture[0].position.x + a*voiture[1].position.x) / (1+a);
			positionCentralY =  (voiture[0].position.y + b*voiture[1].position.y) / (1+b);
		}
		else {
			positionCentralX =  (a * voiture[0].position.x + voiture[1].position.x) / (1+a);
			positionCentralY =  (b * voiture[0].position.y + voiture[1].position.y) / (1+b);
		}
	}
	
	//Calcul de l'indice des voitures dans la matrice
	i = positionCentralX / circuit.largeurImage;
	j = positionCentralY / circuit.hauteurImage;
	
	//Calcul de la position relative à une image
	positionRelativeX = positionCentralX % circuit.largeurImage;
	positionRelativeY = positionCentralY % circuit.hauteurImage;
	
	
	//Gestion de l'axe horizontale
	if(positionRelativeX > circuit.largeurImage - 400 || (i == 0 && positionRelativeX > 400)) {
		if(i == circuit.nbrImageX - 1) { //Bord droit de la matrice
			camera->positionVoitures[0].x= (voiture[0].position.x % circuit.largeurImage) - (circuit.largeurImage - 800);
			camera->positionVoitures[1].x= (voiture[1].position.x % circuit.largeurImage) - (circuit.largeurImage - 800);
			positionCameraX = 800 - circuit.largeurImage;
		}
		else {
			camera->positionVoitures[0].x = 400 - (positionCentralX - voiture[0].position.x);
			camera->positionVoitures[1].x = 400 - (positionCentralX - voiture[1].position.x);
			positionCameraX =  circuit.largeurImage + 400 - positionRelativeX;
			camera->coin[0]=i+1;
		}
	}
	else {
		if(i == 0) { //Bord gauche de la matrice
			camera->positionVoitures[0].x= (voiture[0].position.x % circuit.largeurImage);
			camera->positionVoitures[1].x= (voiture[1].position.x % circuit.largeurImage);
			positionCameraX = circuit.largeurImage;
		}
		else {
			camera->positionVoitures[0].x = 400 - (positionCentralX - voiture[0].position.x);
			camera->positionVoitures[1].x = 400 - (positionCentralX - voiture[1].position.x);
			positionCameraX = 400 - positionRelativeX;
			camera->coin[0]=i;
		}
	}
	
	//Gestion de l'axe verticale
	if(positionRelativeY > circuit.hauteurImage - 300 || (j == 0 && positionRelativeY > 300)) {
		if(j == circuit.nbrImageY - 1) { //Bord bas de la matrice
			camera->positionVoitures[0].y= (voiture[0].position.y % circuit.hauteurImage) - (circuit.hauteurImage - 600);
			camera->positionVoitures[1].y= (voiture[1].position.y % circuit.hauteurImage) - (circuit.hauteurImage - 600);
			positionCameraY = 600 - circuit.hauteurImage;
		}
		else {
			camera->positionVoitures[0].y = 300 - (positionCentralY - voiture[0].position.y);
			camera->positionVoitures[1].y = 300 - (positionCentralY - voiture[1].position.y);
			positionCameraY =  circuit.hauteurImage + 300 - positionRelativeY;
			camera->coin[1]=j+1;
		}
	}
	else {
		if(j == 0) { //Bord haut de la matrice
			camera->positionVoitures[0].y= voiture[0].position.y % circuit.hauteurImage;
			camera->positionVoitures[1].y= voiture[1].position.y % circuit.hauteurImage;
			positionCameraY = circuit.hauteurImage;
		}
		else {
			camera->positionVoitures[0].y = 300 - (positionCentralY - voiture[0].position.y);
			camera->positionVoitures[1].y = 300 - (positionCentralY - voiture[1].position.y);
			positionCameraY = 300 - positionRelativeY;
			camera->coin[1]=j;
		}
	}
	
	
	
	
	
	
	//Mise à jour des images
	if (camera->coin[0] != camera->coinprec[0] && camera->coin[1] != camera->coinprec[1]) {
		for(i=0; i<4;i++)
			SDL_FreeSurface(camera->fond[i]);
		camera->fond[0] = SDL_LoadBMP(circuit.image[camera->coin[0]-1][camera->coin[1]-1]);
		camera->fond[1] = SDL_LoadBMP(circuit.image[camera->coin[0]-1][camera->coin[1]]);
		camera->fond[2] = SDL_LoadBMP(circuit.image[camera->coin[0]][camera->coin[1]-1]);
		camera->fond[3] = SDL_LoadBMP(circuit.image[camera->coin[0]][camera->coin[1]]);
		camera->coinprec[0] = camera->coin[0];
		camera->coinprec[1] = camera->coin[1];
	}
	
	//Cacul des postions de chaque image
	position_00.x = positionCameraX - circuit.largeurImage;
	position_00.y = positionCameraY - circuit.hauteurImage;
	position_01.x = positionCameraX;
	position_01.y = positionCameraY - circuit.hauteurImage;
	position_10.x = positionCameraX - circuit.largeurImage;
	position_10.y = positionCameraY;
	position_11.x = positionCameraX;
	position_11.y = positionCameraY;
	
	//Blit des images
	SDL_BlitSurface(camera->fond[0], NULL, ecran, &position_00);
	SDL_BlitSurface(camera->fond[1], NULL, ecran, &position_01);
	SDL_BlitSurface(camera->fond[2], NULL, ecran, &position_10);
	SDL_BlitSurface(camera->fond[3], NULL, ecran, &position_11);
	
}
