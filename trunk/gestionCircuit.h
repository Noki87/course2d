#ifndef GESTIONCIRCUIT_H
#define GESTIONCIRCUIT_H

#include <SDL/SDL.H>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
#include "menu.h"

typedef struct vecteur{
        double x;
        double y;
        double val;
        double alpha;
} Vecteur;

typedef struct voiture{
        SDL_Surface     *image;
        SDL_Rect position,moyCol;
        double angleR;
        int angleD;
        int vitessemax,masse;
        Vecteur vitesse,acceleration;
        Vecteur fMoteur,fFrot,frottements;
        int haut,bas,gauche,droite;
        int angle;
        char nom[20];
        char cheminImage[25];
		int checkpoints,couleurPrec,couleurPrecPrec;
		int ***tabVoiture;
} Voiture;

typedef struct circuit {
	char nomCircuit[10]; //Le nom du circuit
	int nbrImageX; //Le nombre de colonne qui constitue la matrice des images du circuit
	int nbrImageY; //Le nombre de ligne qui constitue la matrice des images du circuit 
	int largeurImage; //La largeur des images
	int hauteurImage; //La hauteur des images
	char ***image;  //image de la voiture en cour
	int **tabMasque;  //La matrice de détection des collisions
	int **tabCheckpoints; //La matrice de détection des checkpoints
	int totalCheckpoints; //Le nombre total de checkpoints
	SDL_Rect posDepart1;  //La positon de départ sur le circuit pour le J1
	SDL_Rect posDepart2;  //La positon de départ sur le circuit pour le J2
	int nbTours; //Le nombre de tours total
} Circuit;

typedef struct  camera {
	SDL_Surface *fond[4]; //Correspond aux 4 images de fond le plus proches de la voiture
	int coin[2]; //Correspond à lindice i,j du fond en bas à droite.
	int coinprec[2]; //Correspond à l'indice précendant.
	SDL_Rect *positionVoitures; //tableau de position des voitures
	SDL_Surface *** spriteVoiture; //tableau où sont chargé pour chaque voitures (1er indice), les 32 images (2ème indice) des différents angles des voitures.  
	int temps; //Temps depuis le début de la course
	int nbrTour; //nombre de tours total
	int tourActuel; //nombre de tours actuel
	int points; //nombre de points en multi de -3 (J2) à +3 (J1)
} Camera;


/*
 chargement des 32 images des angles de la voiture dans surface et chargement du masque des colision pour la voiture dans voiture->tabVoiture
 retourne 4 en cas de mauvaise allocation
*/
int allocationVoiture (SDL_Surface ***surface,  Voiture *voiture);

/*
	initialisation des données du circuit, des voitures, de la caméra en fonction des paramètre de partie et du nombre de joueur
	retourne 4 en cas de mauvaise allocation
*/
int initialisation (Camera *camera, Voiture voitures[], Circuit * circuit, int nbrDeJoueurs, Partie partie);

/*
	libération des différentes allocations dinamiques
*/
int liberation(Voiture *voiture, Circuit *circuit, Camera * camera, int nbrDeJoueurs);

/*
	repositionne les voitures sur la position de la voiture en tête en mode multi
*/
void repositionnerVoitures (int voitureEnTete, Voiture * voitures);

/*
	Permet la gestion du mode 2J.
	Ordonne le repositioonement des voitures lorsque la distance entre la voiture de tête et la 2ème voiture est supérieur à un écran.
	Augmente ou diminue le nombre de points.
	Si le nombre de points depasse un seuil on arrête la gestionCircuit
*/
void gestion2j (Voiture * voitures, Camera * camera, int *compt, Partie * partie, int *done);

/*	
	Permet la gestion du mode 1J.
	Augmente le nombre de tour.
	Si le nombre de tour est égal au nombre de tour total on redirectionne vers les différent menu, on arrête la fonction GestionCircuit
 
*/
void gestion1j (Voiture *voitures, Camera * camera, Circuit circuit, Partie *partie, int *done, Scores *scores);

/*
	Permet la gestion de la pause.
	Appel le menu pause.
	Calcul le temps de pause.
*/
void gestionPause(SDL_Event *event, Partie *partie, SDL_Surface * ecran, int *done, int *tempsPause, Scores *scores);

/*
	Gestion et sauvegarde des différent événement du circuit.
*/
void gestionEvent(SDL_Event event, Voiture * voitures, Partie *partie, int nbrDeJoueurs, int *done) ;

/*
	Appel la fonction d'initialisation et la fonction ecranChargment
	Gère la boucle de temps du circuit pour afficher 33 images/seconde.
	Appel les fonction de dépalcement des voitures et d'affichage.
	Appel les différentes fonction de gestion.
*/
int gestionCircuit( SDL_Surface *ecran, Partie *partie, Scores *scores);
#endif
