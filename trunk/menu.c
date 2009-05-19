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





void chargerFond(SDL_Surface *ecran,Partie partie, SDL_Rect positionFond, Menu * menuPrecedent, Scores *scores) {
	SDL_Event event;
	char fond[50];
	int i;
	SDL_Surface *imageDeFond = NULL;

	SDL_Rect positionMini;
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

	sprintf(fond, "bitmaps/%s.bmp", tabMenu[partie.menu]);
	imageDeFond = SDL_LoadBMP(fond);
	SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
	if(partie.menu==MenuJouer4){
		for(i=0;i<3;i++){
			sprintf(fond, "Circuit/%s_mini.bmp", partie.nomsCircuits[i]);
			imageDeFond = SDL_LoadBMP(fond);
			positionMini.x=75+227*i;
			positionMini.y=260;
			SDL_BlitSurface(imageDeFond, NULL, ecran, &positionMini);
		}
	}
	if(partie.menu==MenuOptions)
		menuOptions(ecran, event, &partie);
	if(partie.menu==MenuJouer3)
		menuJouer3(ecran, event, &partie);
	if(partie.menu==MenuJouer2)
		menuJouer2(ecran, event, &partie);
	if(partie.menu==MenuScores)
		menuScores(ecran, event, &partie, scores);
	*menuPrecedent = partie.menu;
	SDL_FreeSurface(imageDeFond);
	
}

void gestionMenu (SDL_Surface *ecran, Partie *partie, Scores *scores) {
	int continuer = 1;
	SDL_Event event;
	
	Menu menuPrecedent = MenuBateau;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	
	
	SDL_EnableKeyRepeat(300, 80);

	while (continuer)
	{
		chargerFond(ecran, *partie, positionFond, &menuPrecedent, scores);
		SDL_Flip(ecran);
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				partie->menu = MenuQuitter;
				break;
			case SDL_MOUSEBUTTONUP:
			case SDL_KEYDOWN:
				if(event.key.keysym.sym==SDLK_RETURN)
					partie->saisieAutorisee=0;
				switch (partie->menu) {
					case MenuAccueil:
						menuAccueil(event, partie);
						break;
					case MenuScores:
						menuScores(ecran, event, partie, scores);
						break;
					case MenuJouer1:
						menuJouer1(event, partie);
						break;
					case MenuJouer2:
						menuJouer2(ecran, event, partie);
						break;
					case MenuJouer3:
						menuJouer3(ecran, event, partie);
						break;
					case MenuJouer4:
						menuJouer4(event, partie);
						break;
					case MenuOptions:
						menuOptions(ecran, event, partie);
						break;
					case MenuPause:
						menuPause(event, partie);
						break;
					case MenuFinA:
						menuFinA(event, partie, ecran, scores);
						break;
					case MenuFinB:
						menuFinB(event, partie, ecran, scores);
						break;
					default:
						break;
				}
				if(partie->menu == MenuJeu || partie->menu == MenuQuitter || (partie->menu == MenuJouer4 && partie->pause == 1))
					continuer = 0;
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
		partie->menu = MenuQuitter;

}

void menuScores (SDL_Surface *ecran, SDL_Event event, Partie *partie, Scores *scores){
	int i;
	char mot[20];
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *texte = NULL, *rectangle = NULL;
	SDL_Rect positionTexte;

	police = TTF_OpenFont("Prototype.ttf", 18);
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 230, 30, 32, 0, 0, 0, 0);
	rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 400, 200, 32, 0, 0, 0, 0);
	
	positionTexte.y = 200;
	positionTexte.x = 200;

	if (event.type == SDL_MOUSEBUTTONUP) {
		if ((event.button.x <=130)&(event.button.x >=25)&(event.button.y <=260)&(event.button.y >=178)){
			partie->circuit = 0;
			SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
			SDL_BlitSurface(rectangle, NULL, ecran, &positionTexte); 
		}
		if ((event.button.x <=134)&(event.button.x >=29)&(event.button.y <=365)&(event.button.y >=280)){
			partie->circuit = 1;
			SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
			SDL_BlitSurface(rectangle, NULL, ecran, &positionTexte); 
		}
		if ((event.button.x <=133)&(event.button.x >=28)&(event.button.y <=475)&(event.button.y >=385)){
			partie->circuit = 2;
			SDL_FillRect(rectangle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255)); 
			SDL_BlitSurface(rectangle, NULL, ecran, &positionTexte); 
		}
	}

	lireScores(partie, scores);

	positionTexte.x = 200;
	positionTexte.y = 200;

	for (i=0; i<5;i++){
		strcpy(mot,scores->nomJoueur1[i]);
		texte = TTF_RenderText_Blended(police, mot, couleurNoire);			
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		positionTexte.y += 40;
	}

	positionTexte.y = 200;
	positionTexte.x = 470;

	for (i=0; i<5;i++){
		sprintf(mot, "%d:%02d:%02d",scores->temps[i]/60000,scores->temps[i]/1000 % 60, scores->temps[i]/10 % 100);
		texte = TTF_RenderText_Blended(police, mot, couleurNoire);			
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		positionTexte.y += 40;
	}	

	
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuAccueil;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=577)&(event.button.y >=528))
		partie->menu = MenuQuitter;

	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);
	SDL_FreeSurface(rectangle);
}

void menuJouer1 (SDL_Event event, Partie *partie){
	if ((event.button.x <=565)&(event.button.x >=250)&(event.button.y <=300)&(event.button.y >=230)) {
		partie->nbrDeJoueur=1; 
		partie->menu = MenuJouer2;
	}
	if ((event.button.x <=565)&(event.button.x >=250)&(event.button.y <=425)&(event.button.y >=350)) {
		partie->nbrDeJoueur=2; 
		partie->menu = MenuJouer2;
	}
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuAccueil;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=577)&(event.button.y >=528))
		partie->menu = MenuQuitter;
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
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 230, 30, 32, 0, 0, 0, 0);
	
	if (event.type == SDL_MOUSEBUTTONUP && (event.button.x <=510)&(event.button.x >=264)&(event.button.y <=240)&(event.button.y >=200)) {
		partie->saisieAutorisee = 1;
	}
	
	if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350)) {	
		partie->voiture1=1;
		if (partie->nbrDeJoueur==2) 
			partie->menu =  MenuJouer3;
		else 
			partie->menu = MenuJouer4;
	}
	if ((event.button.x <=530)&(event.button.x >=390)&(event.button.y <=460)&(event.button.y >=350)) { 
		partie->voiture1=2;
		if (partie->nbrDeJoueur==2)
			partie->menu = MenuJouer3;
		else 
			partie->menu = MenuJouer4;
	}
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuJouer1;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=575)&(event.button.y >=528))
		partie->menu = MenuQuitter;
	
		
	positionTexte.x = 270;
	positionTexte.y = 207;
	
	saisirTexte (event, mot, texte, police, ecran, positionTexte, couleurNoire, 20-1, 1, partie->saisieAutorisee);
	strcpy(partie->nomJoueur1,mot);
	
	
	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);
}

void menuJouer3 (SDL_Surface *ecran, SDL_Event event, Partie *partie){
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *texte = NULL;
	SDL_Rect positionTexte;
	
	char mot[20];
	strcpy(mot,partie->nomJoueur2);
	// Chargement de la police 
	police = TTF_OpenFont("Prototype.ttf", 18);
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 230, 30, 32, 0, 0, 0, 0);
	

	if (event.type == SDL_MOUSEBUTTONUP && (event.button.x <=510)&(event.button.x >=264)&(event.button.y <=240)&(event.button.y >=200)) {
		partie->saisieAutorisee = 1;
	}

	if ((event.button.x <=320)&(event.button.x >=180)&(event.button.y <=460)&(event.button.y >=350)) {
		if (partie->voiture1!=1){
		partie->voiture2=1; 
		partie->menu = MenuJouer4;
		}
	}
	if ((event.button.x <=530)&(event.button.x >=390)&(event.button.y <=460)&(event.button.y >=350)) {
		if (partie->voiture1!=2){
		partie->voiture2=2;
		partie->menu = MenuJouer4;
		}
	}
	if ((event.button.x <=165)&(event.button.x >=34)&(event.button.y <=580)&(event.button.y >=530))
		partie->menu = MenuJouer2;
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=575)&(event.button.y >=528))
		partie->menu = MenuQuitter;

	positionTexte.x = 270;
	positionTexte.y = 207;
	saisirTexte (event, mot, texte, police, ecran, positionTexte, couleurNoire, 19, 1, partie->saisieAutorisee);
	strcpy(partie->nomJoueur2,mot);
	
	
	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);
}

void menuJouer4 (SDL_Event event, Partie *partie){
	if ((event.button.x <=257)&(event.button.x >=70)&(event.button.y <=420)&(event.button.y >=242)){
		partie->circuit=0; 
	partie->menu = MenuJeu;}
	if ((event.button.x <=485)&(event.button.x >=275)&(event.button.y <=420)&(event.button.y >=242)) {
		partie->circuit=1; 
		partie->menu = MenuJeu;
	}
	if ((event.button.x <=705)&(event.button.x >=520)&(event.button.y <=420)&(event.button.y >=242)) {
		partie->circuit=2; 
		partie->menu = MenuJeu;
	}
	if ((event.button.x <=165)&(event.button.x >=35)&(event.button.y <=576)&(event.button.y >=526)) {
		if (partie->nbrDeJoueur==2) 
			partie->menu = MenuJouer3;
		else 
			partie->menu = MenuJouer2;
	}
	if ((event.button.x <=767)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		partie->menu = MenuQuitter;
	
}


void menuOptions (SDL_Surface *ecran, SDL_Event event, Partie *partie){
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *texte = NULL;
	SDL_Rect positionTexte;
	
	// Chargement de la police 
	police = TTF_OpenFont("Prototype.ttf", 18);
	
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 30, 30, 32, 0, 0, 0, 0);
	
	if(event.type == SDL_MOUSEBUTTONUP) {
		
		if ((event.button.x <=424)&(event.button.x >=247)&(event.button.y <=197)&(event.button.y >=158)) {
			Uint8  video_bpp = 32;
			Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN;
			ecran=SDL_SetVideoMode(800,600, video_bpp, videoflags);
		}
		if ((event.button.x <=630)&(event.button.x >=454)&(event.button.y <=197)&(event.button.y >=158)) {
			Uint8  video_bpp = 32;
			Uint32 videoflags = SDL_HWSURFACE | SDL_DOUBLEBUF;
			ecran=SDL_SetVideoMode(800,600, video_bpp, videoflags);
		}
		if ((event.button.x <=287)&(event.button.x >=247)&(event.button.y <=253)&(event.button.y >=217))
			partie->musique=1;
		if ((event.button.x <=357)&(event.button.x >=317)&(event.button.y <=253)&(event.button.y >=217))
			partie->musique=0;
		
		if ((event.button.x <=290)&(event.button.x >=250)&(event.button.y <=400)&(event.button.y >=360))
			partie->saisieAutorisee = 1;
		if ((event.button.x <=240)&(event.button.x >=200)&(event.button.y <=450)&(event.button.y >=410))
			partie->saisieAutorisee = 2;
		if ((event.button.x <=335)&(event.button.x >=295)&(event.button.y <=450)&(event.button.y >=410))
			partie->saisieAutorisee = 3;
		if ((event.button.x <=288)&(event.button.x >=250)&(event.button.y <=490)&(event.button.y >=455))
			partie->saisieAutorisee = 4;
		if ((event.button.x <=535)&(event.button.x >=495)&(event.button.y <=400)&(event.button.y >=360))
			partie->saisieAutorisee = 5;
		if ((event.button.x <=485)&(event.button.x >=445)&(event.button.y <=450)&(event.button.y >=410))
			partie->saisieAutorisee = 6;
		if ((event.button.x <=585)&(event.button.x >=545)&(event.button.y <=450)&(event.button.y >=410))
			partie->saisieAutorisee = 7;
		if ((event.button.x <=535)&(event.button.x >=495)&(event.button.y <=490)&(event.button.y >=455))
			partie->saisieAutorisee = 8;
	}
	
	if ((event.button.x <=167)&(event.button.x >=37)&(event.button.y <=576)&(event.button.y >=526)) {
		if (partie->pause == 0) 
			partie->menu = MenuAccueil;
		else 
			partie->menu = MenuPause;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526)) {
		if (partie->pause == 0) 
			partie->menu = MenuJouer1;
		else 
			partie->menu = MenuJouer4;
	}
	
	if(event.key.keysym.sym == SDLK_ESCAPE)
		partie->menu = MenuJeu;
	
	positionTexte.x = 254;
	positionTexte.y = 364;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.hJoueur1), 1, partie->saisieAutorisee);
	
	positionTexte.x = 204;
	positionTexte.y = 414;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.gJoueur1), 2, partie->saisieAutorisee);
	
	positionTexte.x = 299;
	positionTexte.y = 414;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.dJoueur1), 3, partie->saisieAutorisee);
	
	positionTexte.x = 254;
	positionTexte.y = 459;			
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.bJoueur1), 4, partie->saisieAutorisee);
	
	positionTexte.x = 499;
	positionTexte.y = 364;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.hJoueur2), 5, partie->saisieAutorisee);
	
	positionTexte.x = 449;
	positionTexte.y = 414;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.gJoueur2), 6, partie->saisieAutorisee);
	
	positionTexte.x = 549;
	positionTexte.y = 414;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.dJoueur2), 7, partie->saisieAutorisee);
	
	positionTexte.x = 499;
	positionTexte.y = 459;
	saisirToucheAfficherLettre(event, texte, police, ecran, positionTexte, couleurNoire, &(partie->clavier.bJoueur2), 8, partie->saisieAutorisee);
	
	
	
	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);

}

void menuPause (SDL_Event event, Partie *partie){
	if ((event.button.x <=465)&(event.button.x >=335)&(event.button.y <=576)&(event.button.y >=526))
		partie->menu = MenuOptions;
	if ((event.button.x <=165)&(event.button.x >=35)&(event.button.y <=576)&(event.button.y >=526) || event.key.keysym.sym == SDLK_ESCAPE) {
		partie->menu = MenuJeu;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		partie->menu = MenuJouer4;
}

void menuFinA (SDL_Event event, Partie *partie, SDL_Surface *ecran, Scores *scores){
	int i;
	char mot[20];
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *texte = NULL;
	SDL_Rect positionTexte;

	police = TTF_OpenFont("Prototype.ttf", 18);
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 230, 30, 32, 0, 0, 0, 0);
	
	positionTexte.y = 260;
	positionTexte.x = 45;

	for (i=0; i<5;i++){
		strcpy(mot,scores->nomJoueur1[i]);
		texte = TTF_RenderText_Blended(police, mot, couleurNoire);			
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		positionTexte.y += 40;
	}

	positionTexte.y = 200;
	positionTexte.x = 470;

	for (i=0; i<5;i++){
		sprintf(mot, "%d:%02d:%02d",scores->temps[i]/60000,scores->temps[i]/1000 % 60, scores->temps[i]/10 % 100);
		texte = TTF_RenderText_Blended(police, mot, couleurNoire);			
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		positionTexte.y += 40;
	}

	
	if ((event.button.x <=282)&(event.button.x >=26)&(event.button.y <=576)&(event.button.y >=526)) {
		initialiserPartie(partie); 
		partie->menu = MenuAccueil;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		partie->menu = MenuQuitter;

	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);
}

void menuFinB (SDL_Event event, Partie *partie, SDL_Surface *ecran, Scores *scores){                              
	int i;
	char mot[20];
	TTF_Font *police = NULL;
	SDL_Color couleurNoire = {0, 0, 0};
	
	SDL_Surface *texte = NULL;
	SDL_Rect positionTexte;

	police = TTF_OpenFont("Prototype.ttf", 18);
	texte = SDL_CreateRGBSurface(SDL_HWSURFACE, 230, 30, 32, 0, 0, 0, 0);
	
	positionTexte.y = 260;
	positionTexte.x = 45;

	for (i=0; i<5;i++){
		strcpy(mot,scores->nomJoueur1[i]);
		texte = TTF_RenderText_Blended(police, mot, couleurNoire);			
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		positionTexte.y += 40;
	}

	positionTexte.y = 200;
	positionTexte.x = 470;

	for (i=0; i<5;i++){
		sprintf(mot, "%d:%02d:%02d",scores->temps[i]/60000,scores->temps[i]/1000 % 60, scores->temps[i]/10 % 100);
		texte = TTF_RenderText_Blended(police, mot, couleurNoire);			
		SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
		positionTexte.y += 40;
	}

	
	if ((event.button.x <=282)&(event.button.x >=26)&(event.button.y <=576)&(event.button.y >=526)){
		initialiserPartie(partie); 
		partie->menu = MenuAccueil;
	}
	if ((event.button.x <=765)&(event.button.x >=635)&(event.button.y <=576)&(event.button.y >=526))
		partie->menu = MenuQuitter;
	
	TTF_CloseFont(police); // Fermeture de la police 
	SDL_FreeSurface(texte);
}

int initialiserPartie(Partie *partie){
	strcpy(partie->nomJoueur1,"joueur1");
	partie->voiture1=1;
	partie->nbrDeJoueur=1;
	strcpy(partie->nomJoueur2,"joueur2");
	partie->voiture2=1;
	partie->circuit=1;
	partie->menu=MenuAccueil;
	partie->saisieAutorisee=0;
	partie->pause=0;
	partie->affichage=0;
	partie->musique=0;
	return 0;
}

int initialiserTouche(Touche *touche){
	touche->gJoueur1 = SDLK_LEFT;
	touche->dJoueur1 = SDLK_RIGHT;
	touche->hJoueur1 = SDLK_UP;
	touche->bJoueur1 = SDLK_DOWN;
	touche->gJoueur2 = SDLK_q;
	touche->dJoueur2 = SDLK_d;
	touche->hJoueur2 = SDLK_z;
	touche->bJoueur2 = SDLK_s;
	return 0;
}
int initialiserScores(Scores *scores){
	int i;
	for (i=0; i<5; i++){
		strcpy(scores->nomJoueur1[i],"J");
		scores->temps[i]=1111111111;
	}
	return 0;
}
void saisirTexte (SDL_Event event, char mot[], SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Color couleur, int longMaxMot, int numeroSaisie, int saisieAutorisee){
	
	SDLKey tabKey[]= {SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j, SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_u, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z, SDLK_0, SDLK_1, SDLK_2, SDLK_3};
	char tabLettre[] = {'q','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','a','r','s','t','u','v','z','x','y','w','0','1','2','3'};
	char touche;
	int i;
	
	if(numeroSaisie == saisieAutorisee)
		SDL_FillRect(zone, NULL, SDL_MapRGB(zone->format, 214, 222, 226));
	else
		SDL_FillRect(zone, NULL, SDL_MapRGB(zone->format, 255, 255, 255));
	SDL_BlitSurface(zone, NULL, ecran, &position);
	
	if(numeroSaisie == saisieAutorisee && event.type == SDL_KEYDOWN) {
		if(event.key.keysym.sym==SDLK_BACKSPACE) {
			i = strlen(mot);
			if(i) 
				mot[i-1]=0;
		}
		else {
			for (i=0; i<30; i++){
				if(event.key.keysym.sym==tabKey[i]){
					if(strlen(mot) < longMaxMot) {
						touche=tabLettre[i];
						sprintf(mot,"%s%c",mot,touche);
					}
				}
			}
		}
	}

	zone = TTF_RenderText_Blended(police, mot, couleur);			
	SDL_BlitSurface(zone, NULL, ecran, &position);
	
}

void saisirToucheAfficherLettre (SDL_Event event, SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Color couleur, SDLKey *touche, int numeroSaisie, int saisieAutorisee){
	
	SDLKey tabKey[]= {SDLK_a, SDLK_b, SDLK_c, SDLK_d, SDLK_e, SDLK_f, SDLK_g, SDLK_h, SDLK_i, SDLK_j, SDLK_k, SDLK_l, SDLK_m, SDLK_n, SDLK_o, SDLK_p, SDLK_q, SDLK_r, SDLK_s, SDLK_t, SDLK_u, SDLK_v, SDLK_w, SDLK_x, SDLK_y, SDLK_z, SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_UP, SDLK_DOWN, SDLK_RIGHT, SDLK_LEFT};
	char tabLettre[] = {'q','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','a','r','s','t','u','v','z','x','y','w','0','1','2','3', 'H', 'B', 'D', 'G'};
	char lettre;
	int i;
	char mot[2] = {0,0};

	if(numeroSaisie == saisieAutorisee)
		SDL_FillRect(zone, NULL, SDL_MapRGB(zone->format, 214, 222, 226));
	else
		SDL_FillRect(zone, NULL, SDL_MapRGB(zone->format, 255, 255, 255));
	SDL_BlitSurface(zone, NULL, ecran, &position);
	
	
	
	if(numeroSaisie == saisieAutorisee && event.type == SDL_KEYDOWN) {
		if(event.key.keysym.sym==SDLK_BACKSPACE) {
			lettre=' ';
		}
		else {
			for (i=0; i<34; i++){
				if(event.key.keysym.sym==tabKey[i]){
					lettre=tabLettre[i];
					mot[0]=lettre;
					*touche=tabKey[i];
				}
			}
		}
	}
	else {
		for (i=0; i<34; i++){
			if(*touche==tabKey[i]){
				lettre=tabLettre[i];
				mot[0]=lettre;
			}
		}
	}
		
	zone = TTF_RenderText_Blended(police, mot, couleur);			
	SDL_BlitSurface(zone, NULL, ecran, &position);
	
}