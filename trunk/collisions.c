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

int lectureCouleur (char cheminImage[], SDL_Rect position,  unsigned char pixel[3]){
	FILE *f;
	char file_type[3];
	long int file_size, reserved;
	long int bitmap_offset;
	long int header_size;
	long int width, height;
	short int planes; 
	short int bits_per_pixel; 
	long int compression ,size_bitmap, horiz_resolution, vert_resolution;
	long int colors_used, colors_important;
	long int positionPixel=0;

	f = fopen(cheminImage, "rb");
	file_type[2] = 0;

	if (fread( file_type, 2* sizeof(char),1, f) == 0) {
		perror("erreur lecture file_type");
		return 2;
	}
	if (strcmp("BM",file_type))
		return 1;
	fread( &file_size, sizeof(long int), 1, f) ;
	fread( &reserved, sizeof(long int), 1, f) ;
	fread( &bitmap_offset, sizeof(long int), 1, f); 
	fread( &header_size, sizeof(long int), 1, f) ;
	fread( &width, sizeof(long int), 1, f) ;
	fread( &height, sizeof(long int), 1, f) ;
	fread( &planes, sizeof(short int), 1, f) ;
	fread( &bits_per_pixel, sizeof(short int), 1, f);
	fread( &compression, sizeof(long int), 1, f) ;
	fread( &size_bitmap, sizeof(long int), 1, f) ;
	fread( &horiz_resolution, sizeof(long int), 1, f) ;
	fread( &vert_resolution, sizeof(long int), 1, f) ;
	fread( &colors_used, sizeof(long int), 1, f) ;
	fread( &colors_important, sizeof(long int), 1, f) ;

	fseek(f,bitmap_offset,SEEK_SET);


	positionPixel = bitmap_offset;
	positionPixel += 1 * ((height-position.y-1)*width + position.x);

	fseek(f,positionPixel,SEEK_SET);
	fread( pixel , 3 * sizeof(unsigned char), 1, f);

	fclose(f);
	return 0;
}

int chargerMasque(int **tabMasque,int largeur, int hauteur){
	unsigned char r,g,b;
	char cheminMasque[] = "Circuit/test_masque.bmp";
	unsigned int x,y,pix;
	SDL_Rect position;
	SDL_Surface *surface;
	surface = SDL_LoadBMP("Circuit/test_masque.bmp");
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
	SDL_FreeSurface(surface);
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
			place.y+=20;
		}
		place.x+=20;
	}
	//sprintf(text,"%d",placeVoiture.y);
	//SDL_WM_SetCaption(text, NULL);
	return collision;
}