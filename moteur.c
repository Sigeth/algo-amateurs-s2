#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include <string.h>


int cpt = 0;

int mainMoteur(int argc, char **argv) {
    //PLanete Test
    Astre Planete;
    Astre *PtPlanete = &Planete;
    Init_Astre(PtPlanete);
    Planete.T = 88;
    Planete.rayon = 20000;
    Planete.x = 20000;
    Planete.y = 0.0;
    for (int i = 0; i < 200; i++) {

        UpdateObjet(PtPlanete);

    }

    Astre **TabAstre = (Astre **) malloc(50 * sizeof(Astre **));

    ListrePlanete(TabAstre);

    printf("%f\n", TabAstre[0]->rayon);
    printf("%f\n", TabAstre[1]->rayon);
    printf("%f\n", TabAstre[2]->rayon);

    //CreerTab(TabAstre);

    //free(TabAstre);

    return 0;
}


void ListrePlanete(Astre **TabAstre) {

    Astre Planete;
    Astre *PtPlanete = &Planete;
    Init_Astre(PtPlanete);
    Planete.T = 88;
    Planete.rayon = 20000;
    Planete.x = 20000;
    Planete.y = 0.0;

    //printf("%ld",PtPlanete->T);
    //Terre à mettre dans le tableau un de ces 4

    Astre Terre;
    Astre *ptTerre = &Terre;
    Init_Astre(ptTerre);
    strcpy(Terre.nom, "La Terre");
    strcpy(Terre.type, "Planète");
    strcpy(Terre.couleur, "cyan");
    Terre.rayon = 150000000;
    Terre.x = 150000000;
    Terre.y = 0;
    //
    Astre Soleil;
    Astre *ptSoleil = &Soleil;
    Init_Astre(ptSoleil);
    strcpy(Soleil.nom, "Le Soleil");
    strcpy(Soleil.type, "Étoile");
    strcpy(Soleil.couleur, "jaune");
    Soleil.x = 0;
    Soleil.y = 0;
    //Quand on changera de focus mettre distance Soleil->Focus en rayon;

    //Lune
    Astre Lune;
    Astre *ptLune = &Lune;
    Init_Astre(ptLune);
    strcpy(Lune.nom, "La Lune");
    strcpy(Lune.type, "Satellite naturel");
    strcpy(Lune.couleur, "gris");
    Lune.rayon = 384467;
    Lune.x = 1884467;
    Lune.y = 0;
    //Lignes à mettre dans la boucle pour les positions
    Lune.xGravitation = Terre.x;
    Lune.yGravitation = Terre.y;

    TabAstre[0] = ptTerre;
    TabAstre[1] = ptSoleil;
    TabAstre[2] = ptLune;


}


/* Fonction Init_Astre
 * Fonction qui initialise la structure Astre
 *@param ptAstre
 */

void Init_Astre(Astre *ptAstre) {
    ptAstre->nom = malloc(10 * sizeof(char));
    ptAstre->type = malloc(15 * sizeof(char));
    ptAstre->couleur = malloc(15 * sizeof(char));
    ptAstre->rayon = 0;
    ptAstre->masse = 0;
    ptAstre->x = 0;
    ptAstre->y = 0;
    ptAstre->vx = 0;
    ptAstre->vy = 0;
    ptAstre->T = 0;
    ptAstre->distanceCentreGravitation = 0;
    ptAstre->xGravitation = 0;
    ptAstre->yGravitation = 0;
}


void modif_poss_astre(Astre *ptAstre, int x, int y) {
    ptAstre->x = x;
    ptAstre->y = y;
}

void modif_Temps(Astre *ptAstre, long int T) {
    ptAstre->T = T;
}

void modif_poss_Gravitation(Astre *ptAstre, int x, int y) {
    ptAstre->xGravitation = x;
    ptAstre->yGravitation = y;
}

void CreerTab(Astre **TabAstre) {
    TabAstre = (Astre **) malloc(50 * sizeof(Astre **));

}

void AjouteElmTab(Astre **TabAstre, Astre *NewAstre) {
    int cpt = 0;
    Astre AstreNull;
    Astre *ptNull = &AstreNull;
    for (int i = 0; i < sizeof(TabAstre); i++) {
        if (TabAstre[i]->nom == NULL) {
            TabAstre[i] = NewAstre;
            cpt++;
            break;
        }
    }
    if (cpt == 0) {
        TabAstre = (Astre **) realloc(TabAstre, sizeof(TabAstre + 1) * sizeof(int));
        TabAstre[sizeof(TabAstre - 1)] = NewAstre;
    }

}


/*
 * Fonction UpdateObjet
 * Permet de renvoyer la position d'un objet à un temps t=0
 * @param Plaete
 * @prama t =>temps écoulé depuis le début de la simiulation
 */

/*sert à faire une trajectoire circulaire*/
/*fait une trajectoire réaliste*/

void UpdateObjet(Astre *Planete) {
    double alpha = acos((Planete->x / Planete->rayon));
    if (alpha >= 3.14) {
        alpha -= 2 * (2 * 3.14) / Planete->T;
        cpt = 1;
    }
    if (alpha <= 0) {
        alpha += 2 * (2 * 3.14) / Planete->T;
        cpt = 0;
    }
    if (cpt == 0) {
        alpha += (2 * 3.14) / Planete->T;
    }
    if (cpt == 1) {
        alpha -= (2 * 3.14) / Planete->T;
    }
    printf("%lf", alpha);
    Planete->x = Planete->rayon * cos(alpha);
    Planete->y = Planete->rayon * sin(alpha);
    printf("*******************************");
    printf("\nNouveau x :%f", Planete->x);
    printf("Nouveau y :%f \n", Planete->y);
    printf("*******************************\n");

}








