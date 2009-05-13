#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "gestionCircuit.h"
#include "affichage.h"
#include "camera.h"
#include "menu.h"


void affichage(SDL_Surface *ecran, Voiture *voiture, Circuit circuit, Camera *camera, int nbrDeJoueurs){
	
	int i;
	char phrase[15];
	
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Rect positionTexte;
	SDL_Surface *texte;
	TTF_Font *police = TTF_OpenFont("Prototype.ttf", 20);

	
	//Affichage voiture et fond
	if(nbrDeJoueurs == 1)
		positionnerCamera (ecran, circuit, voiture[0], camera);
	else
		positionnerCamera2j (ecran, circuit, voiture, camera);
	
	for(i=0; i<nbrDeJoueurs; i++) {
		voiture[i].image=camera->spriteVoiture[i][(voiture[i].angle)];  
		SDL_BlitSurface(voiture[i].image, NULL, ecran, &(camera->positionVoitures[i]));
	}
    
	
	//Affichage du temps
	
	positionTexte.x = 30;
	positionTexte.y = 30;
	
	sprintf(phrase, "%d:%02d:%02d",camera->temps/60000,camera->temps/1000 % 60, camera->temps/10 % 100);
	texte = TTF_RenderText_Blended(police, phrase, couleurBlanc);
	SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
	
	//Affichage nombre de tour
	positionTexte.x = 30;
	positionTexte.y = 50;
	
	sprintf(phrase,"%d/%d",camera->tourActuel,camera->nbrTour);
	texte = TTF_RenderText_Blended(police, phrase, couleurBlanc);
	SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
	
	
	//Affichage du nombre de points en mode multi-joueurs
	if(nbrDeJoueurs == 2) {
		positionTexte.x = 30;
		positionTexte.y = 70;
		
		sprintf(phrase,"points : %d",camera->points);
		texte = TTF_RenderText_Blended(police, phrase, couleurBlanc);
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
	}

	SDL_Flip(ecran);
	
	TTF_CloseFont(police); // Fermeture de la police 

}



int ecranChargement (SDL_Surface * ecran) {
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Rect position;
	char phrase[] ="Chargement";
	SDL_Surface * fond, * texte;
	TTF_Font *police = TTF_OpenFont("Prototype.ttf", 50);
	
	//Positionnement du fond
	position.x = 0;
	position.y = 0;
	
	//Création et affichage d'un fond noir
	fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 800, 600, 32, 0, 0, 0, 0);
	SDL_FillRect(fond, NULL, SDL_MapRGB(fond->format, 0, 0, 0));
	SDL_BlitSurface(fond, NULL, ecran, &position);
	
	
	
	//Création du texte
	texte = TTF_RenderText_Blended(police, phrase, couleurBlanc);
	
	//Positionnement du texte
	position.x = 400 - texte->w /2;
	position.y = 300 - texte->h /2;
	
	SDL_BlitSurface(texte, NULL, ecran, &position);
	
	SDL_Flip(ecran);
	
	TTF_CloseFont(police);
	SDL_FreeSurface(texte);
	SDL_FreeSurface(fond);
	
	return 0;
}

int affichageDecompte(SDL_Surface *ecran, Voiture *voiture, Circuit circuit, Camera *camera, int nbrDeJoueurs, int *compteur, int *tempsPrec, int tempsPause) {	
	int i;
	int tempsActuel = 0;
	char phrase[10];
	
	SDL_Color couleurBlanc = {255, 255, 255};
	SDL_Rect positionTexte;
	SDL_Surface *texte = NULL;
	TTF_Font *police = TTF_OpenFont("Prototype.ttf", 50);
	
	positionTexte.x = 400;
	positionTexte.y = 200;
	
	
	tempsActuel = SDL_GetTicks();
	if(tempsActuel - *tempsPrec - tempsPause > 1000) {	//Attente d'1 seconde entre chaque affichage
		//Affichage de la voiture et du fond
		affichage(ecran, voiture, circuit, camera, nbrDeJoueurs);

		//Affichage du decompte
		sprintf(phrase, "%d",*compteur);
		texte = TTF_RenderText_Blended(police, phrase, couleurBlanc);
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		SDL_Flip(ecran);
		
		//decrementation du compteur
		(*compteur)--;
		*tempsPrec = SDL_GetTicks() - tempsPause;
	}
	
	
	
	TTF_CloseFont(police);
	SDL_FreeSurface(texte);
	
	return 0;
}
