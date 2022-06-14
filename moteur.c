#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include <string.h>


//int cpt = 0;

int mainMoteur(int argc, char **argv) {
    ElementAstre *ptElementAstreSoleil = InitElementAstre();
    /*
     for (int i = 0; i < 2; i++) {

          printf("\n %p \n",ParcourListeElementAstre(ptElementAstreSoleil,1));
          UpdateObjet(ParcourListeElementAstre(ptElementAstreSoleil,1));

     }
 */
//    Astre **TabAstre = (Astre**)malloc(50 * sizeof(Astre*)); 

    // Initial -> Terre
    // Affiche les astres

    ListeElementAstre(InitElementAstre());
    ParcourListeElementAstre(ptElementAstreSoleil, 1);

/*
    ListrePlanete(TabAstre);

    printf("%f\n", TabAstre[0]->rayon);
    printf("%f\n", TabAstre[1]->rayon);
    printf("%f\n", TabAstre[2]->rayon);

    //CreerTab(TabAstre);

    free(TabAstre);
*/
    return 0;

}


ElementAstre *InitElementAstre() {

    ElementAstre *ptElementAstreSoleil = malloc(sizeof(ElementAstre));
    ptElementAstreSoleil->ptElementAstrePrecedent = NULL;
    ptElementAstreSoleil->ptElementAstreSuivant = NULL;
    ptElementAstreSoleil->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreSoleil->ptAstre);
    Init_AstreSoleil(ptElementAstreSoleil->ptAstre);



    ElementAstre *ptElementAstreTerre = malloc(sizeof(ElementAstre));
    ptElementAstreTerre->ptElementAstrePrecedent = ptElementAstreSoleil;
    ptElementAstreTerre->ptElementAstreSuivant = NULL;
    ptElementAstreTerre->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreTerre->ptAstre);
    Init_AstreTerre(ptElementAstreTerre->ptAstre);

    ptElementAstreSoleil->ptElementAstreSuivant = ptElementAstreTerre;


    ElementAstre *ptElementAstreLune = malloc(sizeof(ElementAstre));
    ptElementAstreLune->ptElementAstrePrecedent = ptElementAstreTerre;
    ptElementAstreLune->ptElementAstreSuivant = NULL;
    ptElementAstreLune->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreLune->ptAstre);
    Init_AstreLune(ptElementAstreLune->ptAstre);
    ptElementAstreLune->ptAstre->xGravitation = ptElementAstreTerre->ptAstre->x;
    ptElementAstreLune->ptAstre->yGravitation = ptElementAstreTerre->ptAstre->y;

    ptElementAstreTerre->ptElementAstreSuivant = ptElementAstreLune;

    ElementAstre *ptElementAstreMercure = malloc(sizeof(ElementAstre));
    ptElementAstreMercure->ptElementAstrePrecedent = ptElementAstreLune;
    ptElementAstreMercure->ptElementAstreSuivant = NULL;
    ptElementAstreMercure->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreMercure->ptAstre);
    Init_AstreMercure(ptElementAstreMercure->ptAstre);

    ptElementAstreLune->ptElementAstreSuivant = ptElementAstreMercure;


    ElementAstre *ptElementAstreVenus = malloc(sizeof(ElementAstre));
    ptElementAstreVenus->ptElementAstrePrecedent = ptElementAstreMercure;
    ptElementAstreVenus->ptElementAstreSuivant = NULL;
    ptElementAstreVenus->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreVenus->ptAstre);
    Init_AstreVenus(ptElementAstreVenus->ptAstre);

    ptElementAstreMercure->ptElementAstreSuivant = ptElementAstreVenus;
    
    
    ElementAstre *ptElementAstreMars = malloc(sizeof(ElementAstre));
    ptElementAstreMars->ptElementAstrePrecedent = ptElementAstreVenus;
    ptElementAstreMars->ptElementAstreSuivant = NULL;
    ptElementAstreMars->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreMars->ptAstre);
    Init_AstreMars(ptElementAstreMars->ptAstre);

    ptElementAstreVenus->ptElementAstreSuivant = ptElementAstreMars;
    
    
    ElementAstre *ptElementAstreJupiter = malloc(sizeof(ElementAstre));
    ptElementAstreJupiter->ptElementAstrePrecedent = ptElementAstreMars;
    ptElementAstreJupiter->ptElementAstreSuivant = NULL;
    ptElementAstreJupiter->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreJupiter->ptAstre);
    Init_AstreJupiter(ptElementAstreJupiter->ptAstre);

    ptElementAstreMars->ptElementAstreSuivant = ptElementAstreJupiter;
    
    ElementAstre *ptElementAstreSaturne = malloc(sizeof(ElementAstre));
    ptElementAstreSaturne->ptElementAstrePrecedent = ptElementAstreJupiter;
    ptElementAstreSaturne->ptElementAstreSuivant = NULL;
    ptElementAstreSaturne->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreSaturne->ptAstre);
    Init_AstreSaturne(ptElementAstreSaturne->ptAstre);

    ptElementAstreJupiter->ptElementAstreSuivant = ptElementAstreSaturne;
    
    
    ElementAstre *ptElementAstreNeptune = malloc(sizeof(ElementAstre));
    ptElementAstreNeptune->ptElementAstrePrecedent = ptElementAstreSaturne;
    ptElementAstreNeptune->ptElementAstreSuivant = NULL;
    ptElementAstreNeptune->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreNeptune->ptAstre);
    Init_AstreNeptune(ptElementAstreNeptune->ptAstre);

    ptElementAstreSaturne->ptElementAstreSuivant = ptElementAstreNeptune;
    
    ElementAstre *ptElementAstreUranus = malloc(sizeof(ElementAstre));
    ptElementAstreUranus->ptElementAstrePrecedent = ptElementAstreSaturne;
    ptElementAstreUranus->ptElementAstreSuivant = NULL;
    ptElementAstreUranus->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreUranus->ptAstre);
    Init_AstreUranus(ptElementAstreUranus->ptAstre);

    ptElementAstreNeptune->ptElementAstreSuivant = ptElementAstreUranus;
    


    return ptElementAstreSoleil;

}

Astre *ParcourListeElementAstre(ElementAstre *ptElementAstreInitial, int nb) {
    int compteur = 0;
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL && compteur != nb) {
        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
        compteur++;
    }
    return ptElementAstreCourant->ptAstre;

}


Astre *RechercheParNom(ElementAstre *ptElementAstreInitial, char *nom_Recherche) {
    //printf("%s",nom_Recherche);
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        //printf("Nom de l'astre : %s\n",ptElementAstreCourant -> ptAstre -> nom);
        if (!strcmp(ptElementAstreCourant->ptAstre->nom, nom_Recherche)) {

            return ptElementAstreCourant->ptAstre;
        }
        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    return NULL;
}


void ListeElementAstre(ElementAstre *ptElementAstreInitial) {
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("\n%s :\n", ptAstre->nom);
            printf(" \n rayon : %f", ptAstre->rayon);
            printf(" \n T : %ld \n", ptAstre->T);
        }

        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
}

/*
void AjouteElementAstre(ElementAstre *ptElementAstreInitial, Astre* NewAstre) {
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    ElementAstre* NewElement ->ptAstre=NewAstre;
    while (ptElementAstreCourant->ptElementAstreSuivant != NULL) {
         ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    ptElementAstreCourant->ptElementAstreSuivant=NewElement;
    NewElement ->ptElementAstrePrecedent=ptElementAstreCourant;
    
}

*/
/* Fonction Init_Astre
 * Fonction qui initialise la structure Astre
 *@param ptAstre
 */

void Init_Astre(Astre *ptAstre) {
    ptAstre->nom = malloc(50 * sizeof(char));
    ptAstre->type = malloc(50 * sizeof(char));
    ptAstre->rayon = 0;
    ptAstre->masse = 0;
    ptAstre->x = 0;
    ptAstre->y = 0;
    ptAstre->previousX = 0;
    ptAstre->previousY = 0;
    ptAstre->vx = 0;
    ptAstre->vy = 0;
    ptAstre->T = 0;
    ptAstre->distanceCentreGravitation = 0;
    ptAstre->nomGravitation = malloc(50 * sizeof(char));
    ptAstre->xGravitation = 0;
    ptAstre->yGravitation = 0;
}

void Init_AstreTerre(Astre *ptTerre) {
    strcpy(ptTerre->nom, "La Terre");
    strcpy(ptTerre->type, "Planète");
    ptTerre->couleur = Cyan;
    ptTerre->rayon = 6371;
    strcpy(ptTerre->nomGravitation, "Le Soleil");
    ptTerre->distanceCentreGravitation = 150000000;
    ptTerre->T = 365;
    ptTerre->x = 150000000;
    ptTerre->y = 0;
}

void Init_AstreLune(Astre *ptLune) {
    strcpy(ptLune->nom, "La Lune");
    strcpy(ptLune->type, "Satellite naturel");
    ptLune->couleur = GrisFonce;
    ptLune->rayon = 1737.0;
    strcpy(ptLune->nomGravitation, "La Terre");
    ptLune->distanceCentreGravitation = 384467;
    ptLune->T = 28;
    ptLune->x = 384467 + 150000000.f;
    ptLune->y = 0;
}

void Init_AstreSoleil(Astre *ptSoleil) {
    strcpy(ptSoleil->nom, "Le Soleil");
    strcpy(ptSoleil->type, "Étoile");
    ptSoleil->couleur = Jaune;
    ptSoleil->rayon = 696340;
    strcpy(ptSoleil->nomGravitation, "Le Soleil");
    ptSoleil->x = 0;
    ptSoleil->y = 0;
}


void Init_AstreMercure(Astre *ptMercure) {
    	strcpy(ptMercure->nom, "Mercure");
	strcpy(ptMercure->type, "Planète");
	ptMercure->couleur = GrisClair;
	ptMercure->rayon = 2439;
	strcpy(ptMercure->nomGravitation, "Le Soleil");
	ptMercure->distanceCentreGravitation = 58000000;
	ptMercure->T = 88;
	ptMercure->x = 58000000;
	ptMercure->y = 0;
}

void Init_AstreVenus(Astre *ptVenus) {
    	strcpy(ptVenus->nom, "Venus");
	strcpy(ptVenus->type, "Planète");
	ptVenus->couleur = Orange;
	ptVenus->rayon = 6051;
	strcpy(ptVenus->nomGravitation, "Le Soleil");
	ptVenus->distanceCentreGravitation = 108000000;
	ptVenus->T = 224;
	ptVenus->x = 108000000;
	ptVenus->y = 0;
}

void Init_AstreMars(Astre *ptMars) {
    	strcpy(ptMars->nom, "Mars");
	strcpy(ptMars->type, "Planète");
	ptMars->couleur = Rouge;
	ptMars->rayon = 3396;
	strcpy(ptMars->nomGravitation, "Le Soleil");
	ptMars->distanceCentreGravitation = 228000000;
	ptMars->T = 687;
	ptMars->x = 228000000;
	ptMars->y = 0;
}

void Init_AstreJupiter(Astre* ptJupiter) {
	strcpy(ptJupiter->nom, "Jupiter");
	strcpy(ptJupiter->type, "Planète");
	ptJupiter->couleur = Creme;
	ptJupiter->rayon = 69911;
	strcpy(ptJupiter->nomGravitation, "Le Soleil");
	ptJupiter->distanceCentreGravitation = 779000000;
	ptJupiter->T = 4332;
	ptJupiter->x = 779000000;
	ptJupiter->y = 0;

}

void Init_AstreSaturne(Astre* ptSaturne) {
	strcpy(ptSaturne->nom, "Saturne");
	strcpy(ptSaturne->type, "Planète");
	ptSaturne->couleur = Cafe;
	ptSaturne->rayon = 58232;
	strcpy(ptSaturne->nomGravitation, "Le Soleil");
	ptSaturne->distanceCentreGravitation = 1400000000;
	ptSaturne->T = 10757;
	ptSaturne->x = 1400000000;
	ptSaturne->y = 0;
}

void Init_AstreUranus(Astre* ptUranus) {
	strcpy(ptUranus->nom, "Uranus");
	strcpy(ptUranus->type, "Planète");
	ptUranus->couleur = BleuCiel;
	ptUranus->rayon = 25559;
	strcpy(ptUranus->nomGravitation, "Le Soleil");
	ptUranus->distanceCentreGravitation = 2870000000;
	ptUranus->T = 30681;
	ptUranus->x = 2870000000;
	ptUranus->y = 0;
}

void Init_AstreNeptune(Astre* ptNeptune) {
	strcpy(ptNeptune->nom, "Neptune");
	strcpy(ptNeptune->type, "Planète");
	ptNeptune->couleur = Bleu;
	ptNeptune->rayon = 24764;
	strcpy(ptNeptune->nomGravitation, "Le Soleil");
	ptNeptune->distanceCentreGravitation = 4500000000;
	ptNeptune->T = 60197;
	ptNeptune->x = 4500000000;
	ptNeptune->y = 0;
}




/*
 * Fonction UpdateObjet
 * Permet de renvoyer la position d'un objet à un temps t=0
 * @param Plaete
 * @prama t =>temps écoulé depuis le début de la simiulation
 */

/*sert à faire une trajectoire circulaire*/
/*fait une trajectoire réaliste*/



void UpdateObjet(Astre *Planete, Astre *Gravitation) {

    printf("\n%f\n", Planete->x);
    printf("%f\n", Planete->y);

    if (Planete->distanceCentreGravitation != 0) {

        Planete->previousX = Planete->x;
        Planete->previousY = Planete->y;

        printf("Mon centre de gravitation : %s\n", Gravitation->nom);
        printf("Ses coordonées :\nx : %f\ny : %f\n", Gravitation->previousX, Gravitation->previousY);

        printf("%f\n", Planete->distanceCentreGravitation);
        printf("%f\n", (Planete->x - Gravitation->previousX));
        double alpha = acos(((Planete->x - Gravitation->previousX) / Planete->distanceCentreGravitation));
        printf("%f\n", alpha);

        if (Gravitation->previousY - 0.1 < Planete->y < Gravitation->previousY + 0.1) {
            alpha = -alpha;
        }

        alpha += (2 * 3.14) / Planete->T;

        printf("%lf", alpha);

        Planete->x = Planete->distanceCentreGravitation * cos(alpha) + Gravitation->x;
        Planete->y = Planete->distanceCentreGravitation * sin(alpha) + Gravitation->y;
    }


    printf("*******************************");
    printf("\nNouveau x :%f", Planete->x);
    printf("Nouveau y :%f \n", Planete->y);
    printf("*******************************\n");

}







