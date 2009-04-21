/*
 *  physique.c
 *  Micromachine
 *
 *  Created by Pablo on 27/03/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <math.h>
#include "gestionCircuit.h"
#include "physique.h"


void initVecteur(Vecteur *vecteur){
	vecteur->x=0;
	vecteur->y=0;
	vecteur->alpha=0;
	vecteur->val=0;
}

Vecteur somme(Vecteur a,Vecteur b,Vecteur c){
	c.x=a.x+b.x;
	c.y=a.y+b.y;
	return c;
}
int initialisationVoitures (Voiture *voiture) {
	strcpy_s(voiture->nom,11,"Voitures 1");
	strcpy_s(voiture->cheminImage,19,"bitmaps\\car000.bmp");
	voiture->image=NULL;
	voiture->masse=1;
	voiture->position.x = 400;
	voiture->position.y = 300;
	initVecteur(&voiture->vitesse);
	initVecteur(&voiture->fFrot);
	initVecteur(&voiture->acceleration);
	voiture->angle=0;
	voiture->angleD=0;
	voiture->angleR=0;
	voiture->haut=voiture->bas=voiture->gauche=voiture->droite=0;
	voiture->vitessemax=20;
	return 0;
}
void projeter(Vecteur *vecteur, int choix){
	if(choix==0){//polaire->cart�sien
		vecteur->x=(vecteur->val*cos((vecteur->alpha)*6.2831/360));
		vecteur->y=(vecteur->val*sin((vecteur->alpha)*6.2831/360));
	}
	if(choix==1){//cart�sien->polaire
		vecteur->val=(sqrt((vecteur->x)*(vecteur->x)+(vecteur->y)*(vecteur->y)));
		vecteur->alpha=(atan(vecteur->y/vecteur->x));
	}
}

void deplacer(Voiture *car){
	//tests
	char text[33];
	itoa((int)(car->vitesse.val), text, 10);
	SDL_WM_SetCaption(text, NULL);
	if(car->haut==1)car->fMoteur.val=2;
	if(car->bas==1)car->fMoteur.val=-1;
	if(car->haut==0 && car->bas==0)car->fMoteur.val=0;
	if(car->gauche==1)car->angleD-=car->vitesse.val/3;
	if(car->droite==1)car->angleD+=car->vitesse.val/3;
	car->fMoteur.alpha=car->angleD;
	projeter(&car->fMoteur,0);
	//Calcul des frottements
	car->fFrot.x=-0.1*car->vitesse.x;
	car->fFrot.y=-0.1*car->vitesse.y;
	//Calcul de l'acc�l�ration, principe fondamental de la dynamique
	car->acceleration.x=((car->fMoteur.x)+(car->fFrot.x))/car->masse;
	car->acceleration.y=((car->fMoteur.y)+(car->fFrot.y))/car->masse;
	//Vitesse(n)=Vitesse(n-1)+Acc�l�ration(n)
	car->vitesse.x+=car->acceleration.x;
	car->vitesse.y+=car->acceleration.y;
	//Position(n)=Position(n-1)+Vitesse(n)
	car->position.x+=(int)(car->vitesse.x);
	car->position.y+=(int)(car->vitesse.y);
	//Conversion du vecteur vitesse en coordonn�es polaires (norme utilis�e pour la rotation du v�hicule)
	projeter(&car->vitesse,1);
	if(car->angleD>=360)car->angleD-=360;
	if(car->angleD<0)car->angleD+=360;
	//if(car->vitesse>20)car->vitesse=20;//limite la vitesse
	//Angle en degr� compris entre 0 et 360
	car->angle =(int)((car->angleD)*32/360);
	//la suite est temporaire, sera g�r� par collisions.c	
	/*if(car->position.y>600-100) car->position.y=600-100;
	if(car->position.x>800-100)car->position.x=800-100;
	if(car->position.y<30)car->position.y=30;
	if(car->position.x<30)car->position.x=30;*/
}