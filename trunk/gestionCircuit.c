#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "menu.h"
#include "gestionCircuit.h"
#include "physique.h"
#include "affichage.h"



int allocationVoiture (SDL_Surface ***surface,  Voiture *voiture) {
	int i,n;
	int nbImages=32;
	int largeur=96,hauteur=96;
	for (i=0;i<32;i++){
		voiture->cheminImage[13]=i-(i/10)*10+48;
		voiture->cheminImage[12]=(i/10)+48;
		(*surface)[i] = SDL_LoadBMP(voiture->cheminImage);
		if ((*surface)[i] == NULL) {
			printf("Unable to load bitmap: %s\n", SDL_GetError());
			return 1;
		}
		SDL_SetColorKey((*surface)[i], SDL_SRCCOLORKEY, SDL_MapRGB((*surface)[i]->format, 97, 68, 43));
	}
	voiture->tabVoiture=malloc(nbImages*sizeof(int **));
	if(voiture->tabVoiture==NULL)return 4;
	for(n=0;n<nbImages;n++){
		voiture->tabVoiture[n]=malloc(largeur*sizeof(int *));
		if(voiture->tabVoiture[n]==NULL)return 4;
		for(i=0; i< largeur; i++) {
			voiture->tabVoiture[n][i] = calloc(hauteur,sizeof(int));
			if(voiture->tabVoiture[n][i]==NULL)return 4;
		}
		chargerMasque(voiture->tabVoiture[n], largeur,hauteur, (*surface)[n]);
	}
	return 0;
}


int initialisation (Camera *camera, Voiture voitures[], Circuit * circuit, int nbrDeJoueurs, Partie partie) {
	int i,j;
	char *** tab;	
	SDL_Surface *surfaceMasque;
	
	//initialisation des voitures 
	for (i=0; i<nbrDeJoueurs; i++) 
		initialisationVoitures (&voitures[i], partie, i+1);
	
	
	//initialisation du circuit

	circuit->nbrImageX=2;
	circuit->nbrImageY=2;
	circuit->largeurImage=1500;
	circuit->hauteurImage=1000;
	
	tab=(char ***)calloc(circuit->nbrImageX,sizeof(char**)); 

	for(i=0;i<circuit->nbrImageX;i++)  {
		tab[i]=(char **) calloc( circuit->nbrImageY ,sizeof(char*));
		for(j=0;j<circuit->nbrImageY;j++) {
			tab[i][j]=(char *) calloc( 1024 ,sizeof(char));
		}
	}
	strcpy(tab[0][0],"Circuit/test00.bmp");
	strcpy(tab[0][1],"Circuit/test01.bmp");
	strcpy(tab[1][0],"Circuit/test10.bmp");
	strcpy(tab[1][1],"Circuit/test11.bmp");
	circuit->image=tab;
	
	
	
	//initialisation camera
	for (i=0; i<4; i++)
		camera->fond[i] = NULL; 
	for (i=0; i<nbrDeJoueurs; i++) {
		
		if(i == 0) 
			camera->positionVoitures[i].y = 300;
		else
			camera->positionVoitures[i].y = 350;
		
		camera->positionVoitures[i].x = 400;
	}
	camera->coin[0] =  camera->coin[1] = 1;
	camera->coinprec[0] = camera->coinprec[1] = 0;
	
	//allocation des voitures	
	camera->spriteVoiture = malloc(nbrDeJoueurs * sizeof(SDL_Surface **));
	
	for (i=0; i<nbrDeJoueurs; i++) {
		camera->spriteVoiture[i] = malloc(32 * sizeof(SDL_Surface *));
		allocationVoiture(&(camera->spriteVoiture[i]), &voitures[i]);
	}

	//chargement du masque
	
	surfaceMasque = SDL_LoadBMP("Circuit/test_masque.bmp");

	circuit->tabMasque=malloc(circuit->largeurImage*circuit->nbrImageX*sizeof(int *));
	if(circuit->tabMasque==NULL)return 4;
	for(i=0; i< circuit->largeurImage * circuit->nbrImageX; i++) {
		circuit->tabMasque[i] = calloc(circuit->hauteurImage*circuit->nbrImageY,sizeof(int));
		if(circuit->tabMasque[i]==NULL)return 4;
	}
	chargerMasque(circuit->tabMasque, circuit->largeurImage * circuit->nbrImageX, circuit->hauteurImage * circuit->nbrImageY, surfaceMasque);
	//chargement du masque checkpoints
	surfaceMasque = SDL_LoadBMP("Circuit/test_checkpoints.bmp");
	circuit->tabCheckpoints=malloc(circuit->largeurImage*circuit->nbrImageX*sizeof(int *));
	if(circuit->tabCheckpoints==NULL)return 4;
	for(i=0; i < circuit->largeurImage * circuit->nbrImageX; i++) {
		circuit->tabCheckpoints[i]=calloc(circuit->hauteurImage*circuit->nbrImageY,sizeof(int));
		if(circuit->tabCheckpoints[i]==NULL)return 4;
	}
	chargerMasque(circuit->tabCheckpoints,circuit->largeurImage*circuit->nbrImageX,circuit->hauteurImage*circuit->nbrImageY, surfaceMasque);
	return 0;
}


int liberation(SDL_Surface **** sprite, SDL_Surface * fond[4], Circuit *circuit) {
	int i;
	
	for(i=0; i<32;i++)
		SDL_FreeSurface((*sprite)[0][i]);
	
	for(i=0; i<4;i++)
		SDL_FreeSurface(fond[i]);
	
	
	for(i=0; i < circuit->largeurImage * circuit->nbrImageX; i++) {
		free(circuit->tabCheckpoints[i]) ;
	}
	free (circuit->tabCheckpoints);
	
	for(i=0; i < circuit->largeurImage * circuit->nbrImageX; i++) {
		free(circuit->tabMasque[i]) ;
	}
	free (circuit->tabMasque);
	
	return 0;
}
 

int gestionCircuit( SDL_Surface *ecran, Partie *partie) {
	
	int done,i,boucle;
	int tempsPrecedent = 0, tempsActuel = 0, tempsDebutCourse, tempsAvantPause = 0, tempsPause = 0;
	int nbrDeJoueurs;

	SDL_Event event;

	Voiture * voitures;
	Circuit circuit;
	Camera camera;
	
	
	if(partie->joueur2 == 0)
		nbrDeJoueurs = 1;
	else
		nbrDeJoueurs = 2;
	
	

	voitures = malloc(nbrDeJoueurs * sizeof(Voiture));
	camera.positionVoitures = malloc(nbrDeJoueurs * sizeof(SDL_Rect));
	
	ecranChargement (ecran);
	
	if(initialisation(&camera, voitures, &circuit, nbrDeJoueurs, *partie)==1){
		return 4;
	}
	
	
	affichageDecompte(ecran,voitures, circuit, &camera,nbrDeJoueurs);

	
	tempsDebutCourse = SDL_GetTicks();

	
	SDL_EnableKeyRepeat(10, 10);
	done = 0;
	while ( !done ) {
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 30){
			tempsPrecedent = tempsActuel;
			for(i=0; i<nbrDeJoueurs; i ++)
				deplacer(&voitures[i],circuit,camera.spriteVoiture[i]);
			camera.temps = tempsActuel - tempsDebutCourse - tempsPause;
			affichage(ecran,voitures,circuit,&camera,nbrDeJoueurs);
			if(partie->pause == 1) {
				tempsAvantPause = SDL_GetTicks();
				boucle = 1;
				while (boucle) {
					SDL_PollEvent(&event);
					if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
					   boucle= 0;
				}
				partie->menu = MenuPause;				
				gestionMenu (ecran, partie);
				tempsPause += SDL_GetTicks() - tempsAvantPause;
			}
			SDL_PollEvent(&event);
			if(event.type==SDL_KEYDOWN){
				if((event.key.keysym.sym)==SDLK_UP) voitures[0].haut=1;
				if((event.key.keysym.sym)==SDLK_DOWN) voitures[0].bas=1;
				if((event.key.keysym.sym)==SDLK_LEFT) voitures[0].gauche=1;
				if((event.key.keysym.sym)==SDLK_RIGHT) voitures[0].droite=1;
				if(nbrDeJoueurs == 2) {
					if((event.key.keysym.sym)==SDLK_e) voitures[1].haut=1;
					if((event.key.keysym.sym)==SDLK_d) voitures[1].bas=1;
					if((event.key.keysym.sym)==SDLK_s) voitures[1].gauche=1;
					if((event.key.keysym.sym)==SDLK_f) voitures[1].droite=1;
				}
				if((event.key.keysym.sym)==SDLK_ESCAPE) partie->pause = 1;
			}
			if(event.type==SDL_KEYUP){
				if((event.key.keysym.sym)==SDLK_UP)voitures[0].haut=0;
				if((event.key.keysym.sym)==SDLK_DOWN)voitures[0].bas=0;
				if((event.key.keysym.sym)==SDLK_LEFT)voitures[0].gauche=0;
				if((event.key.keysym.sym)==SDLK_RIGHT)voitures[0].droite=0;
				if((event.key.keysym.sym)==SDLK_ESCAPE) partie->pause = 0;
				if(nbrDeJoueurs == 2) {
					if((event.key.keysym.sym)==SDLK_e) voitures[1].haut=0;
					if((event.key.keysym.sym)==SDLK_d) voitures[1].bas=0;
					if((event.key.keysym.sym)==SDLK_s) voitures[1].gauche=0;
					if((event.key.keysym.sym)==SDLK_f) voitures[1].droite=0;
				}
			}
			if(event.type==SDL_QUIT)
				done = 1;
			
		}
		else // Si ça fait moins de 30ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut
		{
			SDL_Delay(30 - (tempsActuel - tempsPrecedent));
		}
	}
	
	//liberation(&sprite, fond, &circuit);	

	return 0;
}