Jeu : main.o affichage.o camera.o gestionCircuit.o menu.o physique.o
	gcc -Wall -lSDL -lm main.o affichage.o camera.o gestionCircuit.o menu.o physique.o -o Jeu

main.o : 
	gcc -Wall -c -lSDL -lm main.c

affichage.o : 
	gcc -Wall -c -lSDL affichage.c

camera.o : 
	gcc -Wall -c -lSDL camera.c

gestionCircuit.o : 
	gcc -Wall -c -lSDL gestionCircuit.c

menu.o : 
	gcc -Wall -c -lSDl menu.c

physique.p :
	gcc -Wall -c -lSDl physique.c