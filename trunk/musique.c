#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL/SDL.h>
#include <FMOD/fmod.h>
#include "musique.h"


int lireMusique(FSOUND_STREAM *son){

	son = NULL;

	/* Initialisation de FMOD */
	FSOUND_Init(44100, 32, 0);

	/* Chargement du son et vérification du chargement */
	son = FSOUND_Stream_Open("music.mp3", 0, 0, 0);
	if (son == NULL)
	{
		fprintf(stderr, "Impossible de lire music.mp3\n");
		exit(EXIT_FAILURE);
	}

	FSOUND_Stream_Play(FSOUND_FREE, son);
	FSOUND_SetVolume(FSOUND_ALL, 30);



	return EXIT_SUCCESS;
} 

int arreterMusique(FSOUND_STREAM *son){
	/* On libère le son et on ferme FMOD */
	FSOUND_Stream_Close(son);
	FSOUND_Close();
}