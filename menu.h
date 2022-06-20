#include <stdio.h>
#include <stdlib.h>

#ifndef MENU_H
#define MENU_H
#include "affichage.h"

void liste_options(void);
int nombre_options(void);
int menu(int);
int mini_menu(int);
StateAffichage lancer_simulation();
StateAffichage reprendre();
void sauvegarde();
StateAffichage charger();
void quitter();
StateAffichage retour();

#endif