#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "affichage.h"

void liste_options(void)
{
	char* options[5];
	strcpy(options[0],"lancer simulation");
	strcpy(options[1],"reprendre simulation");
	strcpy(options[2],"sauvegarder la simulation");
	strcpy(options[3],"charger une sauvegarde");
	strcpy(options[4],"quitter le programme");
	strcpy(options[5],"retour menu principal");
}

int nombre_options(void)
{
	return 5;
}


void menu(int choix) 
{
	switch(choix)
	{
		case 1:
			lancer_simulation();
			break;

		case 4:
			charger();
			break;

		case 5:
			quitter();
			break;
	}
}


StateAffichage lancer_simulation(){
	return Simulation;
}

void reprendre() {
    printf("Reprendre la dernière simulation");
}

void sauvegarde(){
    printf("Sauvegarder la simulation actuelle");
}

void charger() {
    printf("Charger une simulation passée");
}

void quitter() {
    printf("Quitter le programme...");
}
