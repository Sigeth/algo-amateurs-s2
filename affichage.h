#include <stdio.h>
#include "GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique

#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include "moteur.h"

typedef enum {MenuPrincipal, Simulation, MenuSauvegardes, MenuSimu}
        StateAffichage;

void afficheSimu(int argc, char **argv);
#endif