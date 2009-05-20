course2d : main.o affichage.o camera.o gestionCircuit.o menu.o physique.o musique.o collisions.o gestionFichiers.o
	gcc -Wall -lSDL -lm main.o affichage.o camera.o gestionCircuit.o musique.o collisions.o gestionFichiers.o menu.o physique.o -o Jeu

main.o : 
	gcc -Wall -c -lSDL -lSDL_ttf -lm main.c

affichage.o : 
	gcc -Wall -c -lSDL affichage.c

camera.o : 
	gcc -Wall -c -lSDL camera.c

gestionCircuit.o : 
	gcc -Wall -c -lSDL gestionCircuit.c

menu.o : 
	gcc -Wall -c -lSDl -lSDlmenu.c

physique.o :
	gcc -Wall -c -lSDl physique.c

gestionFichiers.o:
	gcc -Wall -c -lSDl gestionFichiers.c

collisions.o:
	gcc -Wall -c -lSDl collisions.c

musique.o :
	gcc -Wall -c -lSDl musique.c
