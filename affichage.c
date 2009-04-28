#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
//#include <SDL/SDL_ttf.h>
#include "gestionCircuit.h"
#include "affichage.h"
#include "camera.h"
#include "menu.h"


void affichage(SDL_Surface *ecran, Voiture voiture, SDL_Surface **sprite, Circuit circuit,int coin[],int coinprec[], SDL_Rect *position, SDL_Surface *fond[]){
        voiture.image=sprite[(voiture.angle)];  
        camera (ecran, circuit, voiture, fond, coin, coinprec, position);
        SDL_BlitSurface(voiture.image, NULL, ecran, position);
       // SDL_Flip(ecran);

}

