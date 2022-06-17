#include <stdio.h>
#include <stdlib.h>

#ifndef MENU_H
#define MENU_H
#include "affichage.h"

void liste_options(void);
int nombre_options(void);
void menu(int);
void mini_menu(int);
StateAffichage lancer_simulation();
StateAffichage reprendre();
void sauvegarde();
void charger();
void quitter();
StateAffichage retour();

#endif