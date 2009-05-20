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

//calcule la position exacte d'un pixel dans un fichier image
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

/*remplit un tableau en donnant une valeur à chaque case en fonction de la couleur du pixel
correspondant dans l'image *surface*/
int chargerMasque(int **tabMasque,int largeur, int hauteur, SDL_Surface *surface){
	unsigned char r,g,b;//valeurs des couleurs
	unsigned int x,y;//position du pixel
	SDL_LockSurface(surface);//verrouille la surface, nécessaire pour utiliser DSL_GetRGB et getpixel
	for(y=0;y<(hauteur);y++){
		for(x=0;x<(largeur);x++){
			SDL_GetRGB(getpixel(surface,x,y),surface->format, &r, &g, &b);
			//récupère la valeur RGB du pixel et la place dans les variables r,g,b
			if(r==255){
				if(g==255 && b==255)
					tabMasque[x][y]=1;//blanc
				if(g==0 && b==0)
					tabMasque[x][y]=3;//rouge
			}
			if(r==0 && g==0 && b==255)
				tabMasque[x][y]=2;//bleu
			if(r==97 && g==68 && b==43)
				tabMasque[x][y]=4;//marron (couleur de fond des voitures)
		}
	}
	SDL_UnlockSurface(surface);//déverrouille la surface
	return 0;
}

/*teste les collisions, retourne 1 s'il y a collision 
et déplace la voiture de façon à ce qu'il n'y ait plus collision*/
int testerCollision(SDL_Rect position,Voiture *voiture,Circuit circuit){
	int collision=0;
	int nbCol=0;//nombre total de pixels en collision
	int nbX=0;//nombre de pixels en collisions : largeur
	int nbY=0;//nombre de pixels en collisions : hauteur
	//ces variables permettent de calculer la position moyenne de l'impact
	SDL_Rect place;//position du test par rapport au fond
	SDL_Rect placeVoiture;//position du test parr rapport à l'image de la voiture
	SDL_Rect minCol,maxCol;/*positions extrêmes des pixels en collision qui permet ensuite de 
							calculer le déplacement nécessaire de la voiture 
							pour éviter la collision*/
	place.x=position.x;
	place.y=position.y;
	minCol.x=96;//initialisation à la largeur de l'image
	minCol.y=96;
	maxCol.x=0;
	maxCol.y=0;
	while (place.x < (position.x+96)){
		place.y=position.y;
		while (place.y < (position.y+96)){
			if (circuit.tabMasque[place.x][place.y]==0){
				placeVoiture.x=place.x-position.x;
				placeVoiture.y=place.y-position.y;
				if (voiture->tabVoiture[voiture->angle][placeVoiture.x][placeVoiture.y]!=4){
					collision=1;
					nbCol++;
					nbX+=placeVoiture.x;
					nbY+=placeVoiture.y;
					if(placeVoiture.x<minCol.x)minCol.x=placeVoiture.x;
					if(placeVoiture.y<minCol.y)minCol.y=placeVoiture.y;
					if(placeVoiture.x>maxCol.x)maxCol.x=placeVoiture.x;
					if(placeVoiture.y>maxCol.y)maxCol.y=placeVoiture.y;
				}
			}
			place.y+=2;
		}
		place.x+=2;
	}
	if(collision==1){
		voiture->moyCol.x=nbX/nbCol;//calcul de la position moyennede la collision
		voiture->moyCol.y=nbY/nbCol;
		if(voiture->moyCol.x<=(96/2)){
			voiture->position.x+=(maxCol.x-minCol.x+2);
		}
		if(voiture->moyCol.x>(96/2)){
			voiture->position.x-=(maxCol.x-minCol.x+2);
		}
		if(voiture->moyCol.y<=(96/2)){
			voiture->position.y+=(maxCol.y-minCol.y+2);

		}
		if(voiture->moyCol.y>(96/2)){
			voiture->position.y-=(maxCol.y-minCol.y+2);
		}
		voiture->vitesse.x=0;
		voiture->vitesse.y=0;
		voiture->acceleration.x=0;
		voiture->acceleration.y=0;
	}
	return collision;
}

/*teste la présence de checkpoint entre la position précédente et la position actuelle de la voiture*/
int testerCheckpoints ( int **tabCheckpoints, int nCheckpoints, SDL_Rect posPrec, Voiture *car){
	int x=posPrec.x,y=posPrec.y;//position précédente
	int pasX,pasY;
	int i,j;
	int checkPrec;
	int n;
	SDL_Rect posSuiv=car->position;
	int nx = posSuiv.x - posPrec.x; // distance suivant l'axe des abscisses entre posSuiv et posPrec
	int ny = posSuiv.y - posPrec.y; // distance suivant l'axe des ordonnées entre posSuiv et posPrec
	int couleurPrec=car->couleurPrec;
	int couleurPrecPrec=car->couleurPrecPrec;
	i=x;
	j=y;
	if(nx>=0)pasX=1;
	if(nx<0)pasX=-1;
	if(ny>=0)pasY=1;
	if(ny<0)pasY=-1;
	n=0;
	checkPrec=nCheckpoints;
	do{
		switch (tabCheckpoints[i][j]){
		case 0: //on traverse un checkpoint noir
			switch (couleurPrec){
			case 0: 
				switch (couleurPrecPrec){
					case 2: 
						nCheckpoints++;
						couleurPrec=0;
						couleurPrecPrec=3;
						break;
					case 3: 
						nCheckpoints--;
						couleurPrec=0;
						couleurPrecPrec=2;
						break;
				}
				break;
			case 2: 
				nCheckpoints--;
				couleurPrec=0;
				couleurPrecPrec=2;
				break;
			case 3: 
				nCheckpoints++;
				couleurPrec=0;
				couleurPrecPrec=3;
				break;
			}
			break;
		case 2: //on traverse un checkpoint bleu
			switch (couleurPrec){
				case 0: 
					nCheckpoints++;
					couleurPrec=2;
					couleurPrecPrec=0;
					break;
				case 2: 
					switch (couleurPrecPrec){
					case 0: 
						nCheckpoints--;
						couleurPrec=2;
						couleurPrecPrec=3;
						break;
					case 3: 
						nCheckpoints++;
						couleurPrec=2;
						couleurPrecPrec=2;
						break;
					}
					break;
				case 3: 
					nCheckpoints--;
					couleurPrec=2;
					couleurPrecPrec=3;
					break;
				}
			break;
		case 3: //on traverse un checkpoint rouge
			switch (couleurPrec){
				case 0: 
					nCheckpoints--;
					couleurPrec=3;
					couleurPrecPrec=0;
					break;
				case 2: 
					nCheckpoints++;
					couleurPrec=3;
					couleurPrecPrec=2;
					break;
				case 3: 
					switch (couleurPrecPrec){
					case 0: 
						nCheckpoints++;
						couleurPrec=3;
						couleurPrecPrec=2;
						break;
					case 2: 
						nCheckpoints--;
						couleurPrec=3;
						couleurPrecPrec=0;
						break;
					}
					break;
			}
		break;
		}

		if(j!=y+ny && n==0)
			j+=(int)(pasY);
		if(i!=x+nx && n==1)
			i+=(int)(pasX);
		n++;
		if(n==2)n=0;
	}while(checkPrec==nCheckpoints && (i!=x+nx || j!=y+ny));

	car->couleurPrec=couleurPrec;
	car->couleurPrecPrec=couleurPrecPrec;

	return nCheckpoints;
}