#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "collisions.h"
#include "physique.h"

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
	positionPixel += 1 * ((height-position.y) * width + position.x);

	fseek(f,positionPixel,SEEK_SET);
	fread( pixel , 3 * sizeof(unsigned char), 1, f);

	fclose(f);
	return 0;
}



int testerCollision(SDL_Rect position,int angle){
	//char text[33];
	unsigned char pixel[3];
	char cheminMasque[] = "Circuit/test_masque.bmp";
	char cheminVoiture[]="bitmaps/car000.bmp";
	int collision=0;
	SDL_Rect place,placeVoiture;

	if(angle<10)sprintf(cheminVoiture,"bitmaps/car00%d.bmp",angle);
	if(angle>=10)sprintf(cheminVoiture,"bitmaps/car0%d.bmp",angle);
	position.x-=100;
	place.x=position.x;
	place.y=position.y;

	//fonction qui teste l'existence de collision et renvoie 0 ou 1
	while ( collision == 0 && place.x < (position.x+96)){
		place.y=position.y;
		while ( collision == 0 && place.y < (position.y+96)){
			lectureCouleur (cheminMasque, place, pixel);
			if (pixel[0]==0 && pixel[1]==0 && pixel[2]==0){
				placeVoiture.x=place.x-position.x;
				placeVoiture.y=place.y-position.y;
				lectureCouleur (cheminVoiture, placeVoiture, pixel);
				if (pixel[0]!=68 && pixel[1]!=68 && pixel[2]!=68)
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