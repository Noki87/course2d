
/* Simple program:  Create a blank window, wait for keypress, quit.
 
 Please see the SDL documentation for details on using the SDL API:
 /Developer/Documentation/SDL/docs.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL/SDL.h>

int lectureCouleur (char cheminImage[], SDL_Rect position,  unsigned char pixel[3]) {
	FILE * f;
	
	f = fopen(cheminImage, "rb");
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
	positionPixel += 4 * ((height - position.y - 1) * width + position.x);
	
	fseek(f,positionPixel,SEEK_SET);
	fread( pixel , 3 * sizeof(unsigned char), 1, f);
	
	fclose(f);
	return 0;
}

int main (int argc, char *argv[]) {
	unsigned char pixel[3];
	char cheminImage[] = "3.bmp";
	SDL_Rect position;
	
	position.x=200;
	position.y=200;
	
	lectureCouleur (cheminImage, position, pixel);
	printf("%d ",(int)pixel[0]);
	printf("%d ",(int)pixel[1]);
	printf("%d\n",(int)pixel[2]);
	
	
	return 0;
}
