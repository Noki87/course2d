#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/*
	La fonction affichage prend en paramètre le SDL_surface qui gère l'écran, le tableau des voitures, les données du circuit et de la caméra ainsi que le nombre de joueurs
	Elle blit sur l'écran le fond, les voitures, le temps depuis le début de la course, le nombre de tour en mode 1J et le nombre de points en mode 2J. 
*/
void affichage(SDL_Surface *ecran, Voiture *voiture, Circuit circuit, Camera *camera, int nbrDeJoueurs);

/*
	La fonction affichageDecompte prend en paramètre le SDL_surface qui gère l'écran, les données de la caméra, un compteur qui est décrémenter toute les secondes, 
	le tempsPrécédent et le tempsPause qui serve à savoir si une seconde s'est écoulée
	Elle blit sur l'ecran le décompte.
*/ 
int affichageDecompte(SDL_Surface *ecran, Camera *camera, int *compteur, int *tempsPrecedent, int tempsPause);

/*
	Affiche un écran de chargement : fond noir avec écris chargement en blanc
 */
int ecranChargement (SDL_Surface * ecran);

#endif