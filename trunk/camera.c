#include <stdio.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "gestionCircuit.h"
#include "camera.h"

void positionnerCamera (SDL_Surface *ecran, Circuit circuit, Voiture voiture, Camera * camera) {
        SDL_Rect position_00, position_01, position_10 , position_11;
        int i, j, positionRelativeX, positionRelativeY, positionCameraX, positionCameraY;

        i = voiture.position.x / circuit.largeurImage;
        j = voiture.position.y / circuit.hauteurImage;
        positionRelativeX = voiture.position.x % circuit.largeurImage;
        positionRelativeY = voiture.position.y % circuit.hauteurImage;
       
       
        if(positionRelativeX > circuit.largeurImage - 400 || (i == 0 && positionRelativeX > 400)) {
                if(i == circuit.nbrImageX - 1) {
                        camera->positionVoitures[0].x= positionRelativeX - (circuit.largeurImage - 800);
                        positionCameraX = 800 - circuit.largeurImage;
                }
                else {
                        positionCameraX =  circuit.largeurImage + 400 - positionRelativeX;
                        camera->coin[0]=i+1;
                }
        }
        else {
                if(i == 0) {
                        camera->positionVoitures[0].x= positionRelativeX;
                        positionCameraX = circuit.largeurImage;
                }
                else {
                        positionCameraX = 400 - positionRelativeX;
                        camera->coin[0]=i;
                }
        }
       
       
        if(positionRelativeY > circuit.hauteurImage - 300 || (j == 0 && positionRelativeY > 300)) {
                if(j == circuit.nbrImageY - 1) {
                        camera->positionVoitures[0].y= positionRelativeY - (circuit.hauteurImage - 600);
                        positionCameraY = 600 - circuit.hauteurImage;
                }
                else {
                        positionCameraY =  circuit.hauteurImage + 300 - positionRelativeY;
                        camera->coin[1]=j+1;
                }
        }
        else {
                if(j == 0) {
                        camera->positionVoitures[0].y= positionRelativeY;
                        positionCameraY = circuit.hauteurImage;
                }
                else {
                        positionCameraY = 300 - positionRelativeY;
                        camera->coin[1]=j;
                }
        }
       
       
       
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
       
       
        position_00.x = positionCameraX - circuit.largeurImage;
        position_00.y = positionCameraY - circuit.hauteurImage;
        position_01.x = positionCameraX;
        position_01.y = positionCameraY - circuit.hauteurImage;
        position_10.x = positionCameraX - circuit.largeurImage;
        position_10.y = positionCameraY;
        position_11.x = positionCameraX;
        position_11.y = positionCameraY;
       
        SDL_BlitSurface(camera->fond[0], NULL, ecran, &position_00);
        SDL_BlitSurface(camera->fond[1], NULL, ecran, &position_01);
        SDL_BlitSurface(camera->fond[2], NULL, ecran, &position_10);
        SDL_BlitSurface(camera->fond[3], NULL, ecran, &position_11);
       
}

