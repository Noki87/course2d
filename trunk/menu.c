#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "menu.h"
#include "gestionCircuit.h"

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
	
	while (continuer)
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
	
	while (continuer)
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
	
	while (continuer)
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
					menuJouer1(ecran, partie);
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
	
	SDL_Surface *imageDeFond = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	imageDeFond = SDL_LoadBMP("bitmaps/menuJouer2.bmp");
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
	
	while (continuer)
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
	
	while (continuer)
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
					menuAccueil(ecran, partie);
				if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
					SDL_Quit();
				break;
		}
	}
}

int initialiserPartie(Partie *partie){
	partie->nomJoueur1="Joueur1";
	partie->voiture1=1;
	partie->joueur2=0;
	partie->nomJoueur2="Joueur2";
	partie->voiture2=1;
	partie->circuit=1;
	partie->menu=0;
	partie->pause=0;
	partie->affichage=0;
	partie->musique=0;
	partie->bruitage=0;
	return 0;
}