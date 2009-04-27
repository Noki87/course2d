#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "gestionCircuit.h"
#include "affichage.h"
#include "camera.h"


void affichage(SDL_Surface *ecran, Voiture voiture, SDL_Surface **sprite, Circuit circuit,int coin[],int coinprec[], SDL_Rect *position, SDL_Surface *fond[]){
        voiture.image=sprite[(voiture.angle)];
        camera (ecran, circuit, position, 0, 0, coin, coinprec, fond);
        if(voiture.position.y>=600-100)
                camera (ecran, circuit, position, 0, -(int)(voiture.vitesse.y), coin, coinprec, fond);
        if(voiture.position.x>=800-100)
                camera (ecran, circuit, position, -(int)(voiture.vitesse.x), 0, coin, coinprec, fond);
        if(voiture.position.y<=100)
                camera (ecran, circuit, position, 0, (int)(voiture.vitesse.y), coin, coinprec, fond);
        if(voiture.position.x<=100)
                camera (ecran, circuit, position, (int)(voiture.vitesse.x), 0, coin, coinprec, fond);
        SDL_BlitSurface(voiture.image, NULL, ecran, &voiture.position);
        SDL_Flip(ecran);
}

