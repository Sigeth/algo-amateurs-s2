#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "affichage.h"
#include "sauvegarde.h"

void liste_options(void)
{
	char** options = malloc(sizeof(char*) * 5);
    for (int i=0;i<5;i++) {
        options[i] = malloc(sizeof(char) * 25);
    }
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
			return lancer_simulation();

		case 4:
			return charger();

		case 5:
			quitter();
            break;
	}
    return 0;
}

int mini_menu(int choix, ElementAstre *ptElementAstreInitial, time_t t)
{
	switch(choix)
	{
		case 2:
			return reprendre();
		
		case 3:
			sauvegarde(ptElementAstreInitial, t);
            break;

		case 6:
			return retour();
	}
    return 0;
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