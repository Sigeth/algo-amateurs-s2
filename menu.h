#include <stdio.h>
#include <stdlib.h>

#ifndef MENU_H
#define MENU_H
#include "affichage.h"

void liste_options(void);
int nombre_options(void);
int menu(int choix);
int mini_menu(int choix, ElementAstre *ptElementAstreInitial, time_t t);
StateAffichage lancer_simulation();
StateAffichage reprendre();
void sauvegarde(ElementAstre *ptElementAstreInitial, time_t t);
StateAffichage charger();
void quitter();
StateAffichage retour();

#endif