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
			fgets(buffer[i],sizeof(buffer[i]),fp);
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
	fscanf (file, "%d", &circuit->posDepart1.x);
	fscanf (file, "%d", &circuit->posDepart1.y);
	fscanf (file, "%d", &circuit->posDepart2.x);
	fscanf (file, "%d", &circuit->posDepart2.y);
	fscanf (file, "%d", &circuit->nbTours);

	return EXIT_SUCCESS;
}