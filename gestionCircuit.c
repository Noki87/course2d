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
	char chemin[50];
	
	//initialisation des voitures 
	for (i=0; i<nbrDeJoueurs; i++) 
		initialisationVoitures (&voitures[i], partie, i+1);
	
	
	//initialisation du circuit
	if(partie.circuit==0){
		circuit->totalCheckpoints=16;
		circuit->nbrImageX=2;
		circuit->nbrImageY=2;
		circuit->largeurImage=1500;
		circuit->hauteurImage=1000;
	}
	if(partie.circuit==1){
		circuit->totalCheckpoints=10;
		circuit->nbrImageX=2;
		circuit->nbrImageY=2;
		circuit->largeurImage=1024;
		circuit->hauteurImage=768;
	}
	if(partie.circuit==2){
		circuit->totalCheckpoints=10;
		circuit->nbrImageX=2;
		circuit->nbrImageY=2;
		circuit->largeurImage=1024;
		circuit->hauteurImage=768;
	}

	sscanf (partie.nomsCircuits[partie.circuit],"%s",circuit->nomCircuit);
	
	tab=(char ***)calloc(circuit->nbrImageX,sizeof(char**)); 

	for(i=0;i<circuit->nbrImageX;i++)  {
		tab[i]=(char **) calloc( circuit->nbrImageY ,sizeof(char*));
		for(j=0;j<circuit->nbrImageY;j++) {
			tab[i][j]=(char *) calloc( 1024 ,sizeof(char));
			sprintf(chemin,"Circuit/%s%d%d.bmp",circuit->nomCircuit,i,j);
			strcpy(tab[i][j],chemin);
		}
	}
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
	camera->nbrTour = 3;
	camera->tourActuel = 0;
	camera->temps = 0;
	camera->points = 0;
	
	//allocation des voitures	
	camera->spriteVoiture = malloc(nbrDeJoueurs * sizeof(SDL_Surface **));
	
	for (i=0; i<nbrDeJoueurs; i++) {
		camera->spriteVoiture[i] = malloc(32 * sizeof(SDL_Surface *));
		allocationVoiture(&(camera->spriteVoiture[i]), &voitures[i]);
	}

	//chargement du masque
	sprintf(chemin,"Circuit/%s_masque.bmp",circuit->nomCircuit);
	surfaceMasque = SDL_LoadBMP(chemin);

	circuit->tabMasque=malloc(circuit->largeurImage*circuit->nbrImageX*sizeof(int *));
	if(circuit->tabMasque==NULL)return 4;
	for(i=0; i< circuit->largeurImage * circuit->nbrImageX; i++) {
		circuit->tabMasque[i] = calloc(circuit->hauteurImage*circuit->nbrImageY,sizeof(int));
		if(circuit->tabMasque[i]==NULL)return 4;
	}
	chargerMasque(circuit->tabMasque, circuit->largeurImage * circuit->nbrImageX, circuit->hauteurImage * circuit->nbrImageY, surfaceMasque);
	//chargement du masque checkpoints
	sprintf(chemin,"Circuit/%s_checkpoints.bmp",circuit->nomCircuit);
	surfaceMasque = SDL_LoadBMP(chemin);
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

void repositionnerVoitures (int voitureEnTete, Voiture * voitures) {
	voitures[0].position = voitures[voitureEnTete].position;
	voitures[1].position = voitures[voitureEnTete].position;
	voitures[0].checkpoints = voitures[voitureEnTete].checkpoints;
	voitures[1].checkpoints = voitures[voitureEnTete].checkpoints;
}

void gestion2j (Voiture * voitures, Camera * camera, int *compt, Partie * partie, int *done) {
	if(abs(voitures[0].position.y - voitures[1].position.y)>=600 || abs(voitures[0].position.x - voitures[1].position.x)>=800) {
		if(voitures[0].checkpoints < voitures[1].checkpoints) {
			camera->points--;
			repositionnerVoitures(1, voitures);
		}
		else {
			camera->points++;
			repositionnerVoitures(0, voitures);
		}
		*compt = 2;
	}
	if(abs(camera->points) == 3) {
		partie->menu = MenuFinA;
		*done = 1;
	}
}

void gestion1j (Voiture *voitures, Camera * camera, Circuit circuit, Partie *partie, int *done) {
	if(voitures[0].checkpoints == circuit.totalCheckpoints) {
		camera->tourActuel++;
		voitures[0].checkpoints = 1;
	}
	if(camera->tourActuel == camera->nbrTour) {
		*done = 1;
		partie->menu =MenuFinA;
	}
}

void gestionPause(SDL_Event *event, Partie *partie, SDL_Surface * ecran, int *done, int *tempsPause) {
	int boucle, tempsAvantPause;
	
	tempsAvantPause = SDL_GetTicks();
	boucle = 1;
	while (boucle) {
		SDL_PollEvent(event);
		if(event->type == SDL_KEYUP && event->key.keysym.sym == SDLK_ESCAPE)
			boucle= 0;
	}
	partie->menu = MenuPause;				
	gestionMenu (ecran, partie);
	if(partie->menu == MenuQuitter) {
		*done =1;
	}
	*tempsPause += SDL_GetTicks() - tempsAvantPause;
	
}


void gestionEvent(SDL_Event event, Voiture * voitures, Partie *partie, int nbrDeJoueurs, int *done) {
	if(event.type==SDL_KEYDOWN){
		if((event.key.keysym.sym)==partie->clavier.hJoueur1) voitures[0].haut=1;
		if((event.key.keysym.sym)==partie->clavier.bJoueur1) voitures[0].bas=1;
		if((event.key.keysym.sym)==partie->clavier.gJoueur1) voitures[0].gauche=1;
		if((event.key.keysym.sym)==partie->clavier.dJoueur1) voitures[0].droite=1;
		if(nbrDeJoueurs == 2) {
			if((event.key.keysym.sym)==partie->clavier.hJoueur2) voitures[1].haut=1;
			if((event.key.keysym.sym)==partie->clavier.bJoueur2) voitures[1].bas=1;
			if((event.key.keysym.sym)==partie->clavier.gJoueur2) voitures[1].gauche=1;
			if((event.key.keysym.sym)==partie->clavier.dJoueur2) voitures[1].droite=1;
		}
		if((event.key.keysym.sym)==SDLK_ESCAPE) partie->pause = 1;
	}
	if(event.type==SDL_KEYUP){
		if((event.key.keysym.sym)==partie->clavier.hJoueur1) voitures[0].haut=0;
		if((event.key.keysym.sym)==partie->clavier.bJoueur1) voitures[0].bas=0;
		if((event.key.keysym.sym)==partie->clavier.gJoueur1) voitures[0].gauche=0;
		if((event.key.keysym.sym)==partie->clavier.dJoueur1) voitures[0].droite=0;
		if((event.key.keysym.sym)==SDLK_ESCAPE) partie->pause = 0;
		if(nbrDeJoueurs == 2) {
			if((event.key.keysym.sym)==partie->clavier.hJoueur2) voitures[1].haut=0;
			if((event.key.keysym.sym)==partie->clavier.bJoueur2) voitures[1].bas=0;
			if((event.key.keysym.sym)==partie->clavier.gJoueur2) voitures[1].gauche=0;
			if((event.key.keysym.sym)==partie->clavier.dJoueur2) voitures[1].droite=0;
		}
	}
	if(event.type==SDL_QUIT) {
		partie->menu = MenuQuitter;
		*done = 1;
	}		
	
}

int gestionCircuit( SDL_Surface *ecran, Partie *partie) {
	
	int done,i, compt;
	int tempsPrecedent = 0, tempsActuel = 0, tempsDebutCourse, tempsPause = 0;
	int nbrDeJoueurs;

	SDL_Event event;

	Voiture * voitures;
	Circuit circuit;
	Camera camera;
	
	
	nbrDeJoueurs = partie->nbrDeJoueur;

	

	voitures = malloc(nbrDeJoueurs * sizeof(Voiture));
	camera.positionVoitures = malloc(nbrDeJoueurs * sizeof(SDL_Rect));
	
	ecranChargement (ecran);
	
	if(initialisation(&camera, voitures, &circuit, nbrDeJoueurs, *partie)==1){
		return 4;
	}
	
	tempsDebutCourse = SDL_GetTicks();
	compt = 3;
	
	SDL_EnableKeyRepeat(10, 10);
	done = 0;
	while ( !done ) {
		tempsActuel = SDL_GetTicks();
		if (tempsActuel - tempsPrecedent > 30){
			tempsPrecedent = tempsActuel;
			if(compt != -1) {
				affichageDecompte(ecran,voitures, circuit, &camera,nbrDeJoueurs, &compt, &tempsDebutCourse,tempsPause);
			}
			else {
				for(i=0; i<nbrDeJoueurs; i ++)
					deplacer(&voitures[i],circuit,camera.spriteVoiture[i]);
				camera.temps = tempsActuel - tempsDebutCourse - tempsPause;
				if(nbrDeJoueurs == 1)
					gestion1j (voitures, &camera, circuit, partie, &done);
				else
					gestion2j(voitures, &camera, &compt, partie, &done);
				affichage(ecran,voitures,circuit,&camera,nbrDeJoueurs);
			}
			if(partie->pause == 1)
				gestionPause(&event, partie, ecran, &done, &tempsPause);
			
			SDL_PollEvent(&event);
			gestionEvent(event, voitures, partie, nbrDeJoueurs, &done);
		}
		else // Si ça fait moins de 30ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut
		{
			SDL_Delay(30 - (tempsActuel - tempsPrecedent));
		}
	}
	
	//liberation(&sprite, fond, &circuit);	

	return 0;
}