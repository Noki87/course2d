#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include <math.h>
#include "menu.h"
#include "gestionCircuit.h"
#include "physique.h"
#include "collisions.h"


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
int initialisationVoitures (Voiture *voiture, Partie partie, Circuit *circuit, int numeroJoueur) {
	if (numeroJoueur == 1)
		strcpy(voiture->nom, partie.nomJoueur1);
	else
		strcpy(voiture->nom, partie.nomJoueur2);
	strcpy(voiture->cheminImage,"bitmaps/car000.bmp");
	voiture->image=NULL;
	voiture->masse=1;
	
	if(numeroJoueur == 1){
		voiture->position.x = circuit->posDepart1.x;
		voiture->position.y = circuit->posDepart1.y;
	}
	else{
		voiture->position.x = circuit->posDepart2.x;
		voiture->position.y = circuit->posDepart2.y;
	}
	initVecteur(&voiture->vitesse);
	initVecteur(&voiture->fFrot);
	initVecteur(&voiture->acceleration);
	initVecteur(&voiture->frottements);
	voiture->angle=0;
	voiture->angleD=0;
	voiture->angleR=0;
	voiture->haut=voiture->bas=voiture->gauche=voiture->droite=0;
	voiture->vitessemax=20;
	voiture->checkpoints=0;
	voiture->couleurPrec=3;
	voiture->couleurPrecPrec=2;
	voiture->moyCol.x=0;
	voiture->moyCol.y=0;
	return 0;
}
void projeter(Vecteur *vecteur, int choix){
	if(choix==0){//polaire->cartÈsien
		vecteur->x=(vecteur->val*cos((vecteur->alpha)*6.2831/360));
		vecteur->y=(vecteur->val*sin((vecteur->alpha)*6.2831/360));
	}
	if(choix==1){//cartÈsien->polaire
		vecteur->val=(sqrt((vecteur->x)*(vecteur->x)+(vecteur->y)*(vecteur->y)));
		vecteur->alpha=(atan(vecteur->y/vecteur->x));
	}
}
void deplacer(Voiture *car, Circuit circuit, SDL_Surface **sprite){
	char text[33];
	int x,y,n,i,j,k;
	unsigned char pixel[3];
	SDL_Rect pos;
	sprintf(text,"%d Prec:%d Avant;%d",car->checkpoints,car->couleurPrec,car->couleurPrecPrec);//moyCol.x,car->moyCol.y);
	//sprintf(text,"%d",circuit.tabCheckpoints[car->position.x][car->position.y]);
	SDL_WM_SetCaption(text, NULL);
	//Etat des touches
	if(car->haut==1)car->fMoteur.val=2;
	if(car->bas==1)car->fMoteur.val=-1;
	if(car->haut==0 && car->bas==0)car->fMoteur.val=0;
	if(car->vitesse.val!=0||car->fMoteur.val!=0){
		if(car->fMoteur.val>0||(car->fMoteur.val==0&&car->vitesse.val>0))
			k=1;
		else
			k=-1;
		if(car->gauche==1)
			car->angleD-=k*car->vitesse.val/3;
		if(car->droite==1)
			car->angleD+=k*car->vitesse.val/3;
	}
	car->fMoteur.alpha=car->angleD;
	projeter(&car->fMoteur,0);
	//Calcul des frottements
	car->fFrot.x=-0.1*car->vitesse.x;
	car->fFrot.y=-0.1*car->vitesse.y;
	//Calcul de l'acceleration, principe fondamental de la dynamique
	car->acceleration.x=((car->fMoteur.x)+(car->fFrot.x))/car->masse;
	car->acceleration.y=((car->fMoteur.y)+(car->fFrot.y))/car->masse;
	//Vitesse(n)=Vitesse(n-1)+AccÈlÈration(n)
	car->vitesse.x+=car->acceleration.x;
	car->vitesse.y+=car->acceleration.y;
	//sauvegarde ancienne position
	pos.x=x=car->position.x;
	pos.y=y=car->position.y;
	//Position(n)=Position(n-1)+Vitesse(n)
	car->position.x+=(int)(car->vitesse.x);
	car->position.y+=(int)(car->vitesse.y);

	testerCollision(car->position,car,circuit)==1;

	//Conversion du vecteur vitesse en coordonnÈes polaires (norme utilisÈe pour la rotation du vÈhicule)
	projeter(&car->vitesse,1);
	if(car->angleD>=360)car->angleD-=360;
	if(car->angleD<0)car->angleD+=360;
	//Angle en degrÈ compris entre 0 et 360
	car->angle =(int)((car->angleD)*32/360);
	//collisions avec le bord de l'écran
	
	if(car->position.y>circuit.nbrImageY*circuit.hauteurImage-100)car->position.y=circuit.nbrImageY*circuit.hauteurImage-100;
	if(car->position.x>circuit.nbrImageX*circuit.largeurImage-100)car->position.x=circuit.nbrImageX*circuit.largeurImage-100;
	if(car->position.y<30)car->position.y=30;
	if(car->position.x<30)car->position.x=30;
	
	//Calcul checkpoints
	car->checkpoints=testerCheckpoints (circuit.tabCheckpoints, car->checkpoints,pos,car);
}
