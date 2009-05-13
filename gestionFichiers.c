#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>

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
