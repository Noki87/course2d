#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "gestionCircuit.h"

#define NB_LIGNES 2
#define NB_COLONNES 26

void menuAccueil(SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuAccueil.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=230)&(event.button.y >=170))
					menuJouer1(ecran, partie);
				if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=324)&(event.button.y >=262))
					menuOptions(ecran, partie);
				if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=415)&(event.button.y >=355))
					menuScores(ecran, partie);
				if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=512)&(event.button.y >=452))
					SDL_Quit();
				break;
		}
		
	}
}

void menuScores (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuScores.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
					menuAccueil(ecran, partie);
				if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=577)&(event.button.y >=528))
					SDL_Quit();
				break;
		}
	}
}

void menuJouer1 (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuJouer1.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=565)&(event.button.x >=250)&(event.button.y <=300)&(event.button.y >=230))
				{partie->joueur2=0; menuJouer2(ecran, partie);}
				if ((event.button.x <=565)&(event.button.x >=250)&(event.button.y <=425)&(event.button.y >=350))
				{partie->joueur2=1; menuJouer2(ecran, partie);}
				if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
					menuAccueil(ecran, partie);
				if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=577)&(event.button.y >=528))
					SDL_Quit();
				break;
		}
	}
}


void menuJouer2 (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *imageDeFond = NULL, *texte = {NULL};
	SDL_Rect positionFond, position;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuJouer2.bmp");
	texte = SDL_LoadBMP("bitmaps/menuJouer2.bmp");
	
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	/* Chargement de la police */
	police = TTF_OpenFont("Prototype.ttf", 18);
	
	/* Position texte */
	texte->w = 230;
	texte->h = 30;
	
	position.x = 270;
	position.y = 207;
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=510)&(event.button.x >=264)&(event.button.y <=240)&(event.button.y >=200))
				{SDL_FillRect(texte, NULL, SDL_MapRGB(texte->format, 214, 222, 226));
					SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit de la couleur par-dessus */
					SDL_Flip(ecran);
					
					saisir (partie->nomJoueur1, texte, police, ecran, position, imageDeFond);
					
					SDL_FillRect(texte, NULL, SDL_MapRGB(texte->format, 255, 255, 255));
					SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte par-dessus */
				SDL_Flip(ecran);								}
				
				if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350))
				{partie->voiture1=1;
					if (partie->joueur2==1) menuJouer3(ecran, partie);
				else menuJouer4(ecran, partie);}
				if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350))
				{partie->voiture1=2;
					if (partie->joueur2==1) menuJouer3(ecran, partie);
				else menuJouer4(ecran, partie);}
				if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
					menuJouer1(ecran, partie);
				if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=575)&(event.button.y >=528))
					SDL_Quit();
				break;
		}
	}
	TTF_CloseFont(police); /* Fermeture de la police */
	SDL_FreeSurface(texte);
	
}

void menuJouer3 (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuJouer3.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350))
				{partie->voiture2=1; menuJouer4(ecran, partie);}
				if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350))
				{partie->voiture2=2; menuJouer4(ecran, partie);}
				if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
					menuJouer2(ecran, partie);
				if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=575)&(event.button.y >=528))
					SDL_Quit();
				break;
		}
	}
}

void menuJouer4 (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuJouer4.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=257)&(event.button.x >=70)&(event.button.y <=420)&(event.button.y >=242))
				{partie->circuit=1; partie->menu=0;}
				if ((event.button.x <=485)&(event.button.x >=275)&(event.button.y <=420)&(event.button.y >=242))
				{partie->circuit=2; partie->menu=0;}
				if ((event.button.x <=705)&(event.button.x >=520)&(event.button.y <=420)&(event.button.y >=242))
				{partie->circuit=3; partie->menu=0;}
				if ((event.button.x <=165)&(event.button.x >=35)&(event.button.y <=576)&(event.button.y >=526))
				{if (partie->joueur2==1) menuJouer3(ecran, partie);
				else menuJouer2(ecran, partie);}
				if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
					SDL_Quit();
				break;
		}
	}
}


void menuOptions (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuOptions.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=424)&(event.button.x >=247)&(event.button.y <=197)&(event.button.y >=158))
					partie->affichage=1;
				if ((event.button.x <=630)&(event.button.x >=454)&(event.button.y <=197)&(event.button.y >=158))
					partie->affichage=0;
				if ((event.button.x <=287)&(event.button.x >=247)&(event.button.y <=253)&(event.button.y >=217))
					partie->musique=1;
				if ((event.button.x <=357)&(event.button.x >=317)&(event.button.y <=253)&(event.button.y >=217))
					partie->musique=0;
				if ((event.button.x <=490)&(event.button.x >=570)&(event.button.y <=253)&(event.button.y >=217))
					partie->bruitage=0;
				if ((event.button.x <=600)&(event.button.x >=640)&(event.button.y <=253)&(event.button.y >=217))
					partie->bruitage=1;
				
				if ((event.button.x <=167)&(event.button.x >=37)&(event.button.y <=576)&(event.button.y >=526))
				{if (partie->pause==0) menuAccueil(ecran, partie);
				else menuPause(ecran, partie);}
				if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
					SDL_Quit();
				break;
		}
	}
}

void menuPause (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuPause.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->pause))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				if ((event.button.x <=465)&(event.button.x >=335)&(event.button.y <=576)&(event.button.y >=526))
					menuOptions(ecran, partie);
				
				if ((event.button.x <=165)&(event.button.x >=35)&(event.button.y <=576)&(event.button.y >=526))
					partie->pause=0;
				if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
					SDL_Quit();
				break;
		}
	}
}

void menuFinA (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuFinA.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:                               
				if ((event.button.x <=282)&(event.button.x >=26)&(event.button.y <=576)&(event.button.y >=526))
				{initialiserPartie(partie); menuAccueil(ecran, partie);}
				if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
					SDL_Quit();
				break;
		}
	}
}
void menuFinB (SDL_Surface *ecran, Partie *partie){
	int continuer = 1;
	SDL_Event event;
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuFinB.bmp");
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	
	SDL_Flip(ecran);
	
	while ((continuer)&&(partie->menu))
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:                               
				if ((event.button.x <=282)&(event.button.x >=26)&(event.button.y <=576)&(event.button.y >=526))
				{initialiserPartie(partie); menuAccueil(ecran, partie);}
				if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
					SDL_Quit();
				break;
		}
	}
}
int initialiserPartie(Partie *partie){
	strcpy(partie->nomJoueur1,"Joueur1");
	partie->voiture1=1;
	partie->joueur2=0;
	strcpy(partie->nomJoueur2,"Joueur2");
	partie->voiture2=1;
	partie->circuit=1;
	partie->menu=1;
	partie->pause=0;
	partie->affichage=0;
	partie->musique=0;
	partie->bruitage=0;
	return 0;
}



char saisir (char mot[], SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Surface *imageDeFond){
	
	SDLKey tabKey[]= {SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j, SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_u, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z};
	char tabLettre[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char touche;
	int i;
	
	int continuer = 1;
	SDL_Event event;
	
	SDL_Color couleurNoire = {0, 0, 0};
	
	while (continuer){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                continuer = 0;
				break;
				
            case SDL_MOUSEMOTION:
				if  ((event.motion.x >500)&(event.motion.x <271)&(event.motion.y >237)&(event.motion.y <207))
					continuer = 0;
				break;
				
			case SDL_KEYDOWN:
				for (i=0; i<26; i++){
					if(event.key.keysym.sym==tabKey[i]){
						touche=tabLettre[i];
						sprintf(mot,"%s%c",mot,touche);
						zone = TTF_RenderText_Blended(police, mot, couleurNoire);
						//	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
						
						SDL_BlitSurface(zone, NULL, ecran, &position);
						SDL_Flip(ecran);
						SDL_Delay(100);
					}
				}
				
				/*if(event.key.keysym.sym==SDLK_a){ 
				 zone = TTF_RenderText_Blended(police, "a", couleurNoire);
				 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
				 
				 SDL_BlitSurface(zone, NULL, ecran, &position);
				 SDL_Flip(ecran);
				 }*/
				
				
				break;
		}
	}
}