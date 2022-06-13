#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void liste_options(void)
{
	char options[5];
	options[0]="lancer simulation";
	options[1]="reprendre simulation";
	options[2]="sauvegarder la simulation";
	options[3]="charger une sauvegarde";
	options[4]="quitter le programme";
	
}

int nombre_options(void)
{
	return 5;
}


int menu(int choix) 
{
	switch(choix)
	{
		case 1:
			lancer_simulation();
			break;

		case 2:
			reprendre();
			break;

		case 3:
			sauvegarde();
			break;

		case 4:
			charger();
			break;

		case 5:
			quitter();
			break;
	}
	return 0;
}


void lancer_simulation(){
    printf("Lancer une nouvelle simulation");
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
