#include <stdio.h>
#include "GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "moteur.h"

typedef enum {MenuPrincipal, Simulation, MenuSauvegardes}
        StateAffichage;

void afficheSimu(int argc, char **argv);