#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "collisions.h"
#include "physique.h"

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
	case 1:
		return *p;

	case 2:
		return *(Uint16 *)p;

	case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;

	case 4:
		return *(Uint32 *)p;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

int chargerMasque(int **tabMasque,int largeur, int hauteur, SDL_Surface *surface){
	unsigned char r,g,b;
	char cheminMasque[] = "Circuit/test_masque.bmp";
	unsigned int x,y,pix;
	SDL_Rect position;
	//hauteur=(insigned int)(hauteur);
	//SDL_Surface *surface;
	//surface = SDL_LoadBMP("Circuit/test_masque.bmp");
	SDL_LockSurface(surface);
	x=y=0;
	for(y=0;y<(hauteur);y++){
		for(x=0;x<(largeur);x++){
			SDL_GetRGB(getpixel(surface,x,y),surface->format, &r, &g, &b);
			if(r==255 && g==255 && b==255)
				tabMasque[x][y]=1;
			if(r==0 && g==0 && b==255)
				tabMasque[x][y]=2;
			if(r==255 && g==0 && b==0)
				tabMasque[x][y]=3;
			if(r==97 && g==68 && b==43)
				tabMasque[x][y]=4;
		}
	}
	SDL_UnlockSurface(surface);
	//	SDL_FreeSurface(surface);
	return 0;
}

int testerCollision(SDL_Rect position,Voiture *voiture,Circuit circuit){
	//char text[33];
	unsigned char r,g,b;
	SDL_Surface *sVoiture;
	int collision=0;
	SDL_Rect place,placeVoiture;
	place.x=position.x;
	place.y=position.y;
	//fonction qui teste l'existence de collision et renvoie 0 ou 1
	while ( collision == 0 && place.x < (position.x+96)){
		place.y=position.y;
		while ( collision == 0 && place.y < (position.y+96)){
			if (circuit.tabMasque[place.x][place.y]==0){
				placeVoiture.x=place.x-position.x;
				placeVoiture.y=place.y-position.y;
				if (voiture->tabVoiture[voiture->angle][placeVoiture.x][placeVoiture.y]!=4)
					collision=1;
			}
			place.y++;
		}
		place.x++;
	}
	//sprintf(text,"%d",placeVoiture.y);
	//SDL_WM_SetCaption(text, NULL);
	return collision;
}
/*int couleurCheckpoints_prec (int nCheckpoints){
int couleurPrec;
switch (nCheckpoints%3){
case 0: 
couleurPrec = 3; //couleur rouge
case 1: 
couleurPrec = 0; //couleur noir
case 2: 
couleurPrec = 2; //couleur bleu
}
return couleurPrec;
}*/

int testerCheckpoints ( int **tabCheckpoints, int nCheckpoints, SDL_Rect posPrec, SDL_Rect posSuiv){
	int x, y,couleurPrec,pasX,pasY,i,j,checkPrec,n;
	//tabCheckpoints[x][y];
	/*retourne 0 si pixel en x,y est noir, 1 si pixel en x,y est blanc, 2 si pixel en x,y est bleu
	3 si pixel en x,y est rouge */

	int nx = posSuiv.x - posPrec.x; // distance suivant l'axe des abscisses entre posSuiv et posPrec
	int ny = posSuiv.y - posPrec.y; // distance suivant l'axe des ordonnées entre posSuiv et posPrec

	switch (nCheckpoints%3){
		case 0: 
			couleurPrec = 3; //couleur rouge
		case 1: 
			couleurPrec = 0; //couleur noir
		case 2: 
			couleurPrec = 2; //couleur bleue
		default :
			couleurPrec = 0;
	}

	x= i = posPrec.x;
	y= j = posPrec.y;

	if(nx>=0)pasX=1;
	if(nx<0)pasX=-1;
	if(ny>=0)pasY=1;
	if(ny<0)pasY=-1;
	n=0;
	do{
		switch (nCheckpoints%3){
		case 0: 
			couleurPrec = 3; //couleur rouge
			break;
		case 1: 
			couleurPrec = 0; //couleur noir
			break;
		case 2: 
			couleurPrec = 2; //couleur bleue
			break;
		}
		if ( tabCheckpoints[i][j] == 0 && couleurPrec == 3)
			nCheckpoints ++;
		if ( tabCheckpoints[i][j] == 0 && couleurPrec == 2)
			nCheckpoints --;
		if ( tabCheckpoints[i][j] == 2 && couleurPrec == 0)
			nCheckpoints ++;
		if ( tabCheckpoints[i][j] == 2 && couleurPrec == 3)
			nCheckpoints --;
		if ( tabCheckpoints[i][j] == 3 && couleurPrec == 2)
			nCheckpoints ++;
		if ( tabCheckpoints[i][j] == 3 && couleurPrec == 0)
			nCheckpoints --;
		if(j!=y+ny && n==0)
			j+=(int)(pasY);
		if(i!=x+nx && n==1)
			i+=(int)(pasX);
		n++;
		if(n==2)n=0;
	}while(i!=x+nx || j!=y+ny);

	return nCheckpoints;
}