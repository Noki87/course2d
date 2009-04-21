/* gestionCircuit.h */

typedef struct vecteur{
	double x;
	double y;
	double val;
	double alpha;
} Vecteur;
typedef struct voiture{
	SDL_Surface	*image;
	SDL_Rect position;
	double angleR;
	int angleD;
	int vitessemax,masse;
	Vecteur vitesse,acceleration;
	Vecteur fMoteur,fFrot;
	int haut,bas,gauche,droite;
	int angle;
	char nom[20];
	char cheminImage[25]; 
} Voiture;
typedef struct circuit {
	int nbrImageX;
	int nbrImageY;
	int largeurImage;
	int hauteurImage;
	char ***image;
} Circuit;