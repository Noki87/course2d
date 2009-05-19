#ifndef CAMERA_H
#define CAMERA_H
#include <SDL/SDL.h>
/*
	La fonction positioonerCamera prend en paramètre le SDL_surface qui gère l'écran, les données du circuit, de la voiture et de la caméra
	Elle blit le fond sur l'écran. La position du fond est calculée pour centrer la voiture au milieu de l'écran sauf lorsqu'on se trouve sur les bords du circuit. 
	A ce moment là, la voiture bouge sur l'écran alors que le fond reste collé sur le bord.
*/
void positionnerCamera (SDL_Surface *ecran, Circuit circuit, Voiture voiture, Camera * camera);

/*
 La fonction positionnerCamera prend en paramètre le SDL_surface qui gère l'écran, les données du circuit, de la voiture et de la caméra
 Elle blit le fond sur l'écran. La position du fond est calculée pour que le baricentre entre les deux voitures soit centré au milieu de l'écran sauf lorsqu'on se trouve sur les bords du circuit. 
 A ce moment là, les voiture bouge sur l'écran alors que le fond reste collé sur le bord.
 Le barycentre se raproche de la voiture de tête lorsque la distance entre les voitures augmentent.
 */
void positionnerCamera2j (SDL_Surface *ecran, Circuit circuit, Voiture *voiture, Camera * camera);
#endif
