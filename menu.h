#include <stdio.h>
#include <stdlib.h>

#ifndef MENU_H
#define MENU_H
#include "affichage.h"

void liste_options(void);
int nombre_options(void);
void menu(int);
StateAffichage lancer_simulation();
void reprendre();
void sauvegarde();
void charger();
void quitter();

#endif