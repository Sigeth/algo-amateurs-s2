#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "affichage.h"
#include "sauvegarde.h"

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


int menu(int choix)
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

int mini_menu(int choix, ElementAstre *ptElementAstreInitial, time_t t)
{
	switch(choix)
	{
		case 2:
			reprendre();
			break;
		
		case 3:
			sauvegarde(ptElementAstreInitial, t);
			break;

		case 6:
			retour();
			break;
	}
}


StateAffichage lancer_simulation(){
	return Simulation;
}

StateAffichage reprendre() {
    return Simulation;
}

void sauvegarde(ElementAstre *ptElementAstreInitial, time_t t){
    printf("sauvegarde\n");
    nomdesauvegarde(ptElementAstreInitial, t);
}

StateAffichage charger() {
    return MenuSauvegardes;
}

void quitter() {
	termineBoucleEvenements();
    printf("Quitter le programme...");
}

StateAffichage retour(){
	return MenuPrincipal;
}