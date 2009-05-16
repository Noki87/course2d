#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include "gestionCircuit.h"

int lireCircuits(char buffer[3][10]) {

	FILE *fp;
	int i;


	fp = fopen("Circuit/circuits.txt","r");
	if (fp==NULL) {
		fputs("erreur d'ouverture\n",stderr);
		return 0;
	}
	else {
		for (i = 0; i < 3; i++) {
			fscanf (fp, "%s", &buffer[i]);
		}
	}
	fclose(fp);

	for (i = 0; i < 3; i++) {
		printf("%s", buffer[i]);
	}

	return EXIT_SUCCESS;
} 

int lireVariables(Circuit *circuit){
	FILE *file;
	char chemin[30];

	sprintf(chemin,"Circuit/%s.txt",circuit->nomCircuit);
	file = fopen(chemin,"r");
	if (file==NULL) {
		fputs("Fichier de configuration circuit absent\n",stderr);
		return 0;
	}
	fscanf (file, "%d", &circuit->nbrImageX);
	fscanf (file, "%d", &circuit->nbrImageY);
	fscanf (file, "%d", &circuit->largeurImage);
	fscanf (file, "%d", &circuit->hauteurImage);
	fscanf (file, "%d", &circuit->totalCheckpoints);
	circuit->totalCheckpoints++;
	fscanf (file, "%d", &circuit->posDepart1.x);
	fscanf (file, "%d", &circuit->posDepart1.y);
	fscanf (file, "%d", &circuit->posDepart2.x);
	fscanf (file, "%d", &circuit->posDepart2.y);
	fscanf (file, "%d", &circuit->nbTours);

	return EXIT_SUCCESS;
}

int lireScores(Partie *partie, Scores *scores) {

	FILE *fp;
	int i;

	if (partie->circuit==0)
	fp = fopen("Circuit/scores0.txt","r");

	if (partie->circuit==1)
	fp = fopen("Circuit/scores1.txt","r");
	
	if (partie->circuit==2)
	fp = fopen("Circuit/scores2.txt","r");

	if (fp==NULL) {
		fputs("erreur d'ouverture\n",stderr);
		return 0;
	}
	else {
		for (i = 0; i < 5; i++)
			fscanf (fp, "%s%d", scores->nomJoueur1[i], scores->temps[i]);
	}
	fclose(fp);

	return EXIT_SUCCESS;
} 

int insererScore(Partie *partie, Scores *scores) {
	int i=3;
	FILE *fp;

	while ((partie->timer < scores->temps[i])&&(i>-1)){
		scores->temps[i+1]= scores->temps[i];
		strcpy(scores->nomJoueur1[i+1],scores->nomJoueur1[i]);
		i--;
	}
	scores->temps[i+1]=partie->timer;
	strcpy(scores->nomJoueur1[i+1],partie->nomJoueur1);

	if (partie->circuit==0)
	fp = fopen("Circuit/scores0.txt","w");

	if (partie->circuit==1)
	fp = fopen("Circuit/scores1.txt","w");
	
	if (partie->circuit==2)
	fp = fopen("Circuit/scores2.txt","w");

	if (fp==NULL) {
		fputs("erreur d'ouverture\n",stderr);
		return 0;
	}
	else {
		for (i = 0; i < 5; i++)
			fprintf (fp, "%s%d", scores->nomJoueur1[i], scores->temps[i]);
	}
	fclose(fp);

	return EXIT_SUCCESS;
} 
