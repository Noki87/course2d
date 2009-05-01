#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "menu.h"
#include "gestionCircuit.h"

#define NB_LIGNES 2
#define NB_COLONNES 26





void chargerFond(SDL_Surface *ecran,Partie partie, SDL_Rect positionFond, Menu * menuPrecedent) {
	char fond[50];
	SDL_Surface *imageDeFond = NULL;
	char *tabMenu[] = {
		"menuAccueil", //0
		"menuScores",  //1
		"menuJouer1",  //2
		"menuJouer2",  //3
		"menuJouer3",  //4
		"menuJouer4",  //5
		"menuOptions", //6
		"menuPause",   //7
		"menuFinA",    //8
		"menuFinB",    //9
	};
	if(partie.menu != *menuPrecedent) {
		sprintf(fond, "bitmaps/%s.bmp", tabMenu[partie.menu]);
		imageDeFond = SDL_LoadBMP(fond);
		SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);	
		SDL_Flip(ecran);
		*menuPrecedent = partie.menu;
	}
	SDL_FreeSurface(imageDeFond);

}
 

void gestionMenu (SDL_Surface *ecran, Partie *partie) {
	int continuer = 1;
	SDL_Event event;
	
	Menu menuPrecedent = -1;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	
	SDL_EnableKeyRepeat(300, 80);

	while (continuer)
	{
		chargerFond(ecran, *partie, positionFond, &menuPrecedent);
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
			case SDL_MOUSEBUTTONUP:
				switch (partie->menu) {
					case MenuAccueil:
						menuAccueil(event, partie);
						break;
					case MenuJouer1:
						menuJouer1(event, partie);
						break;
					case MenuJouer2:
						menuJouer2(ecran, event, partie);
						break;
					case MenuJouer3:
						menuJouer3(event, partie);
						break;
					case MenuJouer4:
						menuJouer4(event, partie);
						break;
					case MenuOptions:
						menuOptions(event, partie);
						break;
					case MenuPause:
						menuPause(event, partie);
						break;
					case MenuFinA:
						menuFinA(event, partie);
						break;
					case MenuFinB:
						menuFinB(event, partie);
						break;
					default:
						break;
				}
				if(partie->menu == MenuJeu)
					continuer = 0;
				break;
			case SDL_KEYDOWN:
				switch (partie->menu) {
					case MenuJouer2:
						menuJouer2(ecran, event, partie);
						break;
				}
				break;
		}
		
	}
	
}

void menuAccueil (SDL_Event event, Partie *partie){
	if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=230)&(event.button.y >=170))
		partie->menu = MenuJouer1;
	if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=324)&(event.button.y >=262))
		partie->menu = MenuOptions;
	if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=415)&(event.button.y >=355))
		partie->menu = MenuScores;
	if ((event.button.x <=510)&(event.button.x >=260)&(event.button.y <=512)&(event.button.y >=452))
		SDL_Quit();

}

void menuScores (SDL_Event event, Partie *partie){
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuAccueil;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=577)&(event.button.y >=528))
		SDL_Quit();
}

void menuJouer1 (SDL_Event event, Partie *partie){
	if ((event.button.x <=565)&(event.button.x >=250)&(event.button.y <=300)&(event.button.y >=230)) {
		partie->joueur2=0; 
		partie->menu = MenuJouer2;
	}
	if ((event.button.x <=565)&(event.button.x >=250)&(event.button.y <=425)&(event.button.y >=350)) {
		partie->joueur2=1; 
		partie->menu = MenuJouer2;
	}
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuAccueil;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=577)&(event.button.y >=528))
		SDL_Quit();
}


void menuJouer2 (SDL_Surface *ecran, SDL_Event event, Partie *partie){
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *texte = NULL;
	SDL_Rect positionTexte;
	
	char mot[20];
	strcpy(mot,partie->nomJoueur1);
	// Chargement de la police 
	police = TTF_OpenFont("Prototype.ttf", 18);
	
	positionTexte.x = 270;
	positionTexte.y = 207;
	
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 230, 30, 32, 0, 0, 0, 0);
	SDL_FillRect(texte, NULL, SDL_MapRGB(texte->format, 214, 222, 226));
	
	if ((event.button.x <=510)&(event.button.x >=264)&(event.button.y <=240)&(event.button.y >=200)) {
		partie->saisieAutorisee = 1;
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte); // Blit de la couleur par-dessus 
		SDL_Flip(ecran);
	}
	
	if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350)) {	
		partie->voiture1=1;
		if (partie->joueur2==1) 
			partie->menu =  MenuJouer3;
		else 
			partie->menu = MenuJouer4;
	}
	if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350)) { 
		partie->voiture1=2;
		if (partie->joueur2==1)
			partie->menu = MenuJouer3;
		else 
			partie->menu = MenuJouer4;
	}
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuJouer1;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=575)&(event.button.y >=528))
		SDL_Quit();	
	
	if(partie->saisieAutorisee) {
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		saisirTexte (event, mot, texte, police, ecran, positionTexte, couleurNoire);
		strcpy(partie->nomJoueur1,mot);
	}

	
	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);
}

void menuJouer3 (SDL_Event event, Partie *partie){
	if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350)) {
		partie->voiture2=1; 
		partie->menu = MenuJouer4;
	}
	if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350)) {
		partie->voiture2=2;
		partie->menu = MenuJouer4;
	}
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuJouer2;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=575)&(event.button.y >=528))
		SDL_Quit();
}

void menuJouer4 (SDL_Event event, Partie *partie){
	if ((event.button.x <=257)&(event.button.x >=70)&(event.button.y <=420)&(event.button.y >=242)){
		partie->circuit=1; 
	partie->menu = MenuJeu;}
	if ((event.button.x <=485)&(event.button.x >=275)&(event.button.y <=420)&(event.button.y >=242)) {
		partie->circuit=2; 
		partie->menu = MenuJeu;
	}
	if ((event.button.x <=705)&(event.button.x >=520)&(event.button.y <=420)&(event.button.y >=242)) {
		partie->circuit=3; 
		partie->menu = MenuJeu;
	}
	if ((event.button.x <=165)&(event.button.x >=35)&(event.button.y <=576)&(event.button.y >=526)) {
		if (partie->joueur2==1) 
			partie->menu = MenuJouer3;
		else 
			partie->menu = MenuJouer2;
	}
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		SDL_Quit();
}


void menuOptions (SDL_Event event, Partie *partie){
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
	
	if ((event.button.x <=167)&(event.button.x >=37)&(event.button.y <=576)&(event.button.y >=526)) {
		if (partie->pause == 0) 
			partie->menu = MenuAccueil;
		else 
			partie->menu = MenuPause;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		SDL_Quit();
	
}

void menuPause (SDL_Event event, Partie *partie){
	if ((event.button.x <=465)&(event.button.x >=335)&(event.button.y <=576)&(event.button.y >=526))
		partie->menu = MenuOptions;
	if ((event.button.x <=165)&(event.button.x >=35)&(event.button.y <=576)&(event.button.y >=526))
		partie->pause=0;
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		SDL_Quit();
}

void menuFinA (SDL_Event event, Partie *partie){
	if ((event.button.x <=282)&(event.button.x >=26)&(event.button.y <=576)&(event.button.y >=526)) {
		initialiserPartie(partie); 
		partie->menu = MenuAccueil;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		SDL_Quit();
}

void menuFinB (SDL_Event event, Partie *partie){                              
	if ((event.button.x <=282)&(event.button.x >=26)&(event.button.y <=576)&(event.button.y >=526)){
		initialiserPartie(partie); 
		partie->menu = MenuAccueil;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		SDL_Quit();
	
}

int initialiserPartie(Partie *partie){
	strcpy(partie->nomJoueur1,"Joueur1");
	partie->voiture1=1;
	partie->joueur2=0;
	strcpy(partie->nomJoueur2,"Joueur2");
	partie->voiture2=1;
	partie->circuit=1;
	partie->menu=MenuAccueil;
	partie->saisieAutorisee=0;
	partie->pause=0;
	partie->affichage=0;
	partie->musique=0;
	partie->bruitage=0;
	return 0;
}



void saisirTexte (SDL_Event event, char mot[], SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Color couleur){
	
	SDLKey tabKey[]= {SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j, SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_u, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z};
	char tabLettre[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char touche;
	int i;
	
	if(event.key.keysym.sym==SDLK_BACKSPACE) {
		i = strlen(mot);
		if(i) 
			mot[i-1]=0;
	}
	else {
		for (i=0; i<26; i++){
			if(event.key.keysym.sym==tabKey[i]){
				if(strlen(mot) < 20) {
					touche=tabLettre[i];
					sprintf(mot,"%s%c",mot,touche);
				}
			}
		}
	}
	zone = TTF_RenderText_Blended(police, mot, couleur);			
	SDL_BlitSurface(zone, NULL, ecran, &position);
	SDL_Flip(ecran);
	
}