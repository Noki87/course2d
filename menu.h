#ifndef MENU_H
#define MENU_H
#include <SDL/SDL.h>
#ifdef __APPLE__
#include <SDL_ttf/SDL_ttf.h>
#else
#include <SDL/SDL_ttf.h>
#endif
typedef enum {
	//associe à chaque menu un numéro, pour une utlisation plus facile de l'information dans partis->menu.
	MenuAccueil = 0,
	MenuScores = 1,
	MenuJouer1 = 2,
	MenuJouer2 = 3,
	MenuJouer3 = 4,
	MenuJouer4 = 5,
	MenuOptions = 6,
	MenuPause = 7,
	MenuFinA = 8,
	MenuFinB = 9,
	MenuJeu = 10,
	MenuBateau = 15, // menu qui ne sert ‡ rien equivallent ‡ NULL 		
	MenuQuitter = 16
} Menu;

typedef struct touche{
	// sauvegarde des touches directionnelles de chaque joueur
	SDLKey gJoueur1; // direction gauche joueur 1
	SDLKey dJoueur1; // direction droit joueur 1
	SDLKey hJoueur1; // direction haut joueur 1
	SDLKey bJoueur1; // direction bas joueur 1
	SDLKey gJoueur2; // direction gauche joueur 2
	SDLKey dJoueur2; // direction droit joueur 2
	SDLKey hJoueur2; // direction haut joueur 2
	SDLKey bJoueur2; // direction bas joueur 2
} Touche;

typedef struct partie{
	// variable global pour la gestion de la parti existante. gère toutes les données des joueurs et de la configuration demandée.
	char nomJoueur1[20];
	int voiture1;
	int nbrDeJoueur;
	char nomJoueur2[20];
	int voiture2;
	Touche clavier;
	int circuit;
	Menu menu;
	int saisieAutorisee;
	int pause;
	int affichage;
	int musique;
	int timer;
	char nomsCircuits[3][10];
} Partie;

typedef struct scores{
	char nomJoueur1[5][20];
	int temps[5];
} Scores;

void chargerFond(SDL_Surface *ecran,Partie partie, SDL_Rect positionFond, Menu * menuPrecedent, Scores *scores); 
// affiche l'image de fond correspondant au menu et gère les cas particuliers des menus avec affichage ou saisie de texte
void gestionMenu (SDL_Surface *ecran, Partie *partie, Scores *scores);
// organise les différents menus entre eux (switch... case). C'est l'unique fonction avec boucle évenementielle (événements types clavier ou souris).
void menuScores (SDL_Surface *ecran, SDL_Event event, Partie *partie, Scores *scores);
// gère le menu Meilleur scores : boutons retour, quitter, et circuits 1, 2, 3 pour afficher les scores (grâce au module gestionFichier).
//(tous les menus ayant des boutons retour et quitter je ne les mentionnerai dorénavant plus...)
void menuAccueil(SDL_Event event, Partie *partie);
// gère le menu Accueil : boutons jouer, options, scores, quitter.
void menuJouer1(SDL_Event event, Partie *partie);
// gère le menu jouer1 (choix du mode) : boutons solo ou 2 joueurs
void menuJouer2(SDL_Surface *ecran,SDL_Event event, Partie *partie);
// gère le menu jouer 2 (caractéristiques joueur 1) : un clic de la souris dans la zone de texte met la variable saisieAutorisée à 1
// la foncion appelle alors la fonction saisirtexte. Un autre clic de la souris hors de la zone de saisie met la variable saisieAutorisée à 0
// un clic sur une voiture sauvegarde le choix de la voiture, son nom, et appelle le menu suivant
void menuJouer3(SDL_Surface *ecran, SDL_Event event, Partie *partie);
// gère le menu jouer 3 (caractéristiques joueur 2) : même fonctionnement que menuJouer2
void menuJouer4(SDL_Event event, Partie *partie);
// gère le menu jouer 4 (choix circuit) : gestionMenu affiche les miniatures dans les cases. 3 boutons, chacun pour un circuit. Un clic démarre le jeu avec le circuit choisi.
void menuOptions(SDL_Surface *ecran, SDL_Event event, Partie *partie);
// gère le menu Options : boutons musique on/off, boutons affichage plein écran/fenêtre, saisie et affichage des touches directionnelles.
//un clic de la souris dans une des zones de texte met la variable saisieAutorisée à 1
// la foncion appelle alors la fonction saisirToucheAfficherLettre. Un autre clic de la souris hors de la zone de saisie met la variable saisieAutorisée à 0
void menuPause(SDL_Event event, Partie *partie);
// gère le menu pause : 3 boutons : quitter (qui revient au menu accueil), options et retour partie.
void menuFinA(SDL_Event event, Partie *partie, SDL_Surface *ecran, Scores *scores);
// gère le menu Fin game over. Affichage des scores grâce à des fonctions du module gestionFichier. Bouttons nouvelle partie ou quitter.
void menuFinB(SDL_Event event, Partie *partie, SDL_Surface *ecran, Scores *scores);
// gère le menu Fin félicitations. Affichage des scores grâce à des fonctions du module gestionFichier. Bouttons nouvelle partie ou quitter.
int initialiserPartie(Partie *partie);
// initialise la variable partie
int initialiserTouche(Touche *touche);
// initialise la variable touche (existance de touches par défaut)
int initialiserScores(Scores *scores);
// initialise la variable touche (scores initialisés absurdes, c'est juste pour initialiser)
void saisirTexte (SDL_Event event, char mot[], SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Color couleur, int longMaxMot, int numeroSaisie, int saisieAutorisee);
// fait correspondre à un événement appui d'une touche sur le clavier, l'affichage de cette touche rajoutée à la chaine de caractères existante, et la sauvegarde de la chaine dans le parametre mot.
// existance d'une taille maximale de saisie
// ne fonctionne que tant que saisiautorisée==1
void saisirToucheAfficherLettre (SDL_Event event, SDL_Surface *zone, TTF_Font *police, SDL_Surface *ecran, SDL_Rect position, SDL_Color couleur, SDLKey *touche, int numeroSaisie, int saisieAutorisee);
// fait correspondre à un événement appui d'une touche sur le clavier, l'affichage et la sauvegarde de cette touche.
// taille maximale de saisie==1
// ne fonctionne que tant que saisiautorisée==1

#endif
