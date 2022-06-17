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
	//premier élément //
    ElementAstre *ptElementAstreSoleil = malloc(sizeof(ElementAstre));
    ptElementAstreSoleil->ptElementAstrePrecedent = NULL;
    ptElementAstreSoleil->ptElementAstreSuivant = NULL;
    ptElementAstreSoleil->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreSoleil->ptAstre);
    Init_AstreSoleil(ptElementAstreSoleil->ptAstre);
     //



    Astre* ptAstre=malloc(sizeof(Astre));
    Astre* ptAstreLune=malloc(sizeof(Astre));
    Astre* ptAstreMercure=malloc(sizeof(Astre));
    Astre* ptAstreVenus=malloc(sizeof(Astre));
    Astre* ptAstreMars=malloc(sizeof(Astre));
    Astre* ptAstreJupiter=malloc(sizeof(Astre));
    Astre* ptAstreSaturne=malloc(sizeof(Astre));
    Astre* ptAstreUranus=malloc(sizeof(Astre));
    Astre* ptAstreNeptune=malloc(sizeof(Astre));
    Astre* ptAstreISS=malloc(sizeof(Astre));
   
   Init_Astre(ptAstre);
   Init_Astre(ptAstreLune);
   Init_Astre(ptAstreMercure);
   Init_Astre(ptAstreVenus);
   Init_Astre(ptAstreMars);
   Init_Astre(ptAstreJupiter);
   Init_Astre(ptAstreSaturne);
   Init_Astre(ptAstreUranus);
   Init_Astre(ptAstreNeptune);
   Init_Astre(ptAstreISS);
    
    Init_AstreTerre(ptAstre);
    Init_AstreLune(ptAstreLune);
    Init_AstreMercure(ptAstreMercure);
    Init_AstreVenus(ptAstreVenus);
    Init_AstreMars(ptAstreMars);
    Init_AstreJupiter(ptAstreJupiter);
    Init_AstreSaturne(ptAstreSaturne);
    Init_AstreUranus(ptAstreUranus);
    Init_AstreNeptune(ptAstreNeptune);
    Init_AstreISS(ptAstreNeptune);
    
    ptAstreLune->x=384467+ptAstre->x;
    ptAstreLune->xGravitation=ptAstre->x;
    ptAstreLune->yGravitation=ptAstre->y;
    
    
    AjouteElementAstre(ptElementAstreSoleil,ptAstre);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreLune);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreMercure);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreVenus);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreMars);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreJupiter);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreSaturne);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreUranus);
    AjouteElementAstre(ptElementAstreSoleil,ptAstreNeptune);

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

        }

        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
}



int CompteElementAstre(ElementAstre *ptElementAstreInitial) {
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    int cpt=0;
    while (ptElementAstreCourant != NULL) {
        cpt++;
        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    return cpt;
}



void AjouteElementAstre(ElementAstre *ptElementAstreInitial, Astre* NewAstre) {

    
    ElementAstre* NewElement = malloc(sizeof(ElementAstre*));
    NewElement->ptAstre=NewAstre;
    NewElement->ptElementAstreSuivant=NULL;
    
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    
    
    while (ptElementAstreCourant->ptElementAstreSuivant != NULL) {
         ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    
    
    ptElementAstreCourant->ptElementAstreSuivant=NewElement;
    NewElement ->ptElementAstrePrecedent=ptElementAstreCourant;
    //free(NewElement);
    
}



void FreeTab(ElementAstre *ptElementAstreInitial) {

    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    ElementAstre* Prec = malloc(sizeof(ElementAstre));
    
    while (ptElementAstreCourant != NULL) {
         ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    Prec=ptElementAstreCourant;
    
    while(Prec != NULL) {
    	
    	Prec = Prec->ptElementAstrePrecedent;
    	ptElementAstreCourant= ptElementAstreCourant ->ptElementAstrePrecedent;
    	free(ptElementAstreCourant);
    	
    }
    //free(NewElement);
    
}



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
    ptAstre->vt= 0;
    ptAstre->deltaV=0;
    ptAstre->distanceCentreGravitation = 0;
    ptAstre->nomGravitation = malloc(50 * sizeof(char));
    ptAstre->xGravitation = 0;
    ptAstre->yGravitation = 0;
}

void Init_AstreTerre(Astre *ptTerre) {
    strcpy(ptTerre->nom, "La Terre");
    strcpy(ptTerre->type, "Planete");
    ptTerre->couleur = Cyan;
    ptTerre->rayon = 6371;
    strcpy(ptTerre->nomGravitation, "Le Soleil");
    ptTerre->distanceCentreGravitation = 150000000;
    ptTerre->x = 150000000;
    ptTerre->previousX = 150000000;
    ptTerre->y = 0;
    ptTerre->masse=5.9736*pow(10,24);
    ptTerre->vt=29.8;
    
}

void Init_AstreLune(Astre *ptLune) {
    strcpy(ptLune->nom, "La Lune");
    strcpy(ptLune->type, "Satellite naturel");
    ptLune->couleur = GrisFonce;
    ptLune->rayon = 1737.0;
    strcpy(ptLune->nomGravitation, "La Terre");
    ptLune->distanceCentreGravitation = 384470;
    //ptLune->T =28;
    ptLune->x = 384467 + 150000000.f;
    ptLune->y = 0;
    ptLune->masse=7.346*pow(10,22);
    ptLune->vt=1.02;
    
}

void Init_AstreSoleil(Astre *ptSoleil) {
    strcpy(ptSoleil->nom, "Le Soleil");
    strcpy(ptSoleil->type, "Etoile"); //Dans la culture comme le soleil (la petite vanne)
    ptSoleil->couleur = Jaune;
    ptSoleil->rayon = 696340;
    strcpy(ptSoleil->nomGravitation, "Le Soleil");
    ptSoleil->x = 0;
    ptSoleil->y = 0;
    ptSoleil->masse=1.988*pow(10,30);
}


void Init_AstreMercure(Astre *ptMercure) {
    	strcpy(ptMercure->nom, "Mercure");
	strcpy(ptMercure->type, "Planete");
	ptMercure->couleur = GrisClair;
	ptMercure->rayon = 2439;
	strcpy(ptMercure->nomGravitation, "Le Soleil");
	ptMercure->distanceCentreGravitation = 58000000;
	ptMercure->x = 58000000;
	ptMercure->y = 0;
	ptMercure->vt=48.8;
	ptMercure->masse=3.3*pow(10,23);

}

void Init_AstreVenus(Astre *ptVenus) {
    	strcpy(ptVenus->nom, "Venus");
	strcpy(ptVenus->type, "Planete");
	ptVenus->couleur = Orange;
	ptVenus->rayon = 6051;
	strcpy(ptVenus->nomGravitation, "Le Soleil");
	ptVenus->distanceCentreGravitation = 108000000;
	ptVenus->x = 108000000;
	ptVenus->y = 0;
	ptVenus->masse=4.87*pow(10,24);
	ptVenus->vt=35.01;
}

void Init_AstreMars(Astre *ptMars) {
    	strcpy(ptMars->nom, "Mars");
	strcpy(ptMars->type, "Planete");
	ptMars->couleur = Rouge;
	ptMars->rayon = 3396;
	strcpy(ptMars->nomGravitation, "Le Soleil");
	ptMars->distanceCentreGravitation = 228000000;
	ptMars->masse=6.417*pow(10,23);
	ptMars->x = 228000000;
	ptMars->y = 0;
	ptMars->vt=24.22;
}

void Init_AstreJupiter(Astre* ptJupiter) {
	strcpy(ptJupiter->nom, "Jupiter");
	strcpy(ptJupiter->type, "Planete");
	ptJupiter->couleur = Creme;
	ptJupiter->rayon = 69911;
	strcpy(ptJupiter->nomGravitation, "Le Soleil");
	ptJupiter->distanceCentreGravitation = 779000000;
	ptJupiter->masse=1.898*pow(10,27);
	ptJupiter->x = 779000000;
	ptJupiter->y = 0;
	ptJupiter->vt=13.11;
	

}

void Init_AstreSaturne(Astre* ptSaturne) {
	strcpy(ptSaturne->nom, "Saturne");
	strcpy(ptSaturne->type, "Planete");
	ptSaturne->couleur = Cafe;
	ptSaturne->rayon = 58232;
	strcpy(ptSaturne->nomGravitation, "Le Soleil");
	ptSaturne->distanceCentreGravitation = 1400000000;
	ptSaturne->masse=568*pow(10,21);
	ptSaturne->x = 1400000000;
	ptSaturne->y = 0;
	ptSaturne->vt=9.7;

}

void Init_AstreUranus(Astre* ptUranus) {
	strcpy(ptUranus->nom, "Uranus");
	strcpy(ptUranus->type, "Planete");
	ptUranus->couleur = BleuCiel;
	ptUranus->rayon = 25559;
	strcpy(ptUranus->nomGravitation, "Le Soleil");
	ptUranus->distanceCentreGravitation = 2870000000;
	ptUranus->masse=8.6*pow(10,22);
	ptUranus->x = 2870000000;
	ptUranus->y = 0;
	ptUranus->vt=6.8;
	
}

void Init_AstreNeptune(Astre* ptNeptune) {
	strcpy(ptNeptune->nom, "Neptune");
	strcpy(ptNeptune->type, "Planete");
	ptNeptune->couleur = Bleu;
	ptNeptune->rayon = 24764;
	strcpy(ptNeptune->nomGravitation, "Le Soleil");
	ptNeptune->distanceCentreGravitation = 4500000000;
	ptNeptune->masse=1.02*pow(10,6);
	ptNeptune->x = 4500000000;
	ptNeptune->y = 0;
	ptNeptune->vt = 5.43;
}



void Init_AstreISS(Astre* ptISS) {
	strcpy(ptISS->nom, "ISS");
	strcpy(ptISS->type, "Satelite Pas Naturel");
	ptISS->couleur = GrisClair;
	ptISS->rayon = 69911;
	strcpy(ptISS->nomGravitation, "La Terre");
	ptISS->distanceCentreGravitation = 400;
	ptISS->x =150000000 +400  ;
	ptISS->y = 0;
	ptISS->vt=7.7;
	

}


/*
 * Fonction UpdateObjet
 * Permet de renvoyer la position d'un objet à un temps t=0
 * @param Plaete
 * @prama t =>temps écoulé depuis le début de la simiulation
 */

/*sert à faire une trajectoire circulaire*/
/*fait une trajectoire réaliste*/


/*
void UpdateObjet(Astre *Planete, Astre *Gravitation) {

    printf("\n%f\n", Planete->x);
    printf("%f\n", Planete->y);

    if (Planete->distanceCentreGravitation != 0) {

        
        printf("Mon nom : %s\n",Planete->nom);
        printf("Mon centre de gravitation : %s\n", Gravitation->nom);
        printf("Ses coordonées :\nx : %f\ny : %f\n", Gravitation->previousX, Gravitation->previousY);

        printf("%f\n", Planete->distanceCentreGravitation);
        
        printf("%f\n", (Planete->x - Gravitation->previousX));
        
        
        double alpha = acos(((Planete->x - Gravitation->previousX) / Planete->distanceCentreGravitation));
        
        
	
        if (Gravitation->y - 0.1 < Planete->y < Gravitation->y + 0.1) {
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
*/


void UpdateObjetReal(Astre *Planete, Astre* Gravitation, int deltaT) {

    printf("\n%f\n", Planete->x);
    printf("%f\n", Planete->y);

    if (Planete->distanceCentreGravitation != 0) {
        Planete->previousX = Planete->x;
        Planete->previousY = Planete->y;
        printf("Mon nom : %s\n",Planete->nom);
        printf("Mon centre de gravitation : %s\n", Gravitation->nom);
        printf("Ses coordonées :\nx : %f\ny : %f\n", Gravitation->x, Gravitation->y);

        printf("distanceCentreGravitation: %f\n", Planete->distanceCentreGravitation);
        
        printf("Diff x: %f\n", (Planete->x - Gravitation->previousX));
        
        
        double alpha = acos(((Planete->x - Gravitation->previousX) / Planete->distanceCentreGravitation));
        double deltaM=Planete->vt*deltaT+Planete->deltaV/2;
        
        Planete->deltaV=abs(Planete->deltaV-Planete->vt);
	
        if (Gravitation->y - 0.1 < Planete->y < Gravitation->y + 0.1) {
            alpha = -alpha;
        }
        
  
        alpha +=acos(1-(((deltaM)*(deltaM))/(2*Planete->distanceCentreGravitation * Planete->distanceCentreGravitation)));



        printf("%lf", alpha);
        
        printf("Calcul centre grav: %lf\n", Planete->distanceCentreGravitation * cos(alpha));
        printf("Grav x: %lf\n", Gravitation->x);

        Planete->x = Planete->distanceCentreGravitation * cos(alpha) + Gravitation->x;
        Planete->y = Planete->distanceCentreGravitation * sin(alpha) + Gravitation->y;
    }


    printf("*******************************");
    printf("\nNouveau x :%f", Planete->x);
    printf("Nouveau y :%f \n", Planete->y);
    printf("*******************************\n");

}





