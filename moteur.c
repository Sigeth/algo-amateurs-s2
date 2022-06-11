#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include <string.h>


//int cpt = 0;

int mainMoteur(int argc, char **argv) {
    ElementAstre* ptElementAstreSoleil=InitElementAstre();
   
    for (int i = 0; i < 2; i++) {

     	printf("\n %p \n",ParcourListeElementAstre(ptElementAstreSoleil,1));
     	UpdateObjet(ParcourListeElementAstre(ptElementAstreSoleil,1));

    }

//    Astre **TabAstre = (Astre**)malloc(50 * sizeof(Astre*)); 

    // Initial -> Terre
    // Affiche les astres
    
    ListeElementAstre(InitElementAstre());
    ParcourListeElementAstre(ptElementAstreSoleil,1);
     
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


ElementAstre* InitElementAstre()
{
	 
    ElementAstre* ptElementAstreSoleil = malloc( sizeof(ElementAstre));
    ptElementAstreSoleil-> ptElementAstrePrecedent = NULL;
    ptElementAstreSoleil-> ptElementAstreSuivant = NULL;
    ptElementAstreSoleil-> ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreSoleil-> ptAstre);
    Init_AstreSoleil(ptElementAstreSoleil-> ptAstre);

	
    ElementAstre* ptElementAstreTerre = malloc( sizeof(ElementAstre));
    ptElementAstreTerre-> ptElementAstrePrecedent = ptElementAstreSoleil;
    ptElementAstreTerre-> ptElementAstreSuivant = NULL;
    ptElementAstreTerre-> ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreTerre-> ptAstre);
    Init_AstreTerre(ptElementAstreTerre-> ptAstre);
    
     ptElementAstreSoleil-> ptElementAstreSuivant=ptElementAstreTerre;
    
    
    ElementAstre* ptElementAstreLune = malloc( sizeof(ElementAstre));
    ptElementAstreLune-> ptElementAstrePrecedent = ptElementAstreTerre;
    ptElementAstreLune-> ptElementAstreSuivant = NULL;
    ptElementAstreLune-> ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreLune-> ptAstre);
    Init_AstreLune(ptElementAstreLune-> ptAstre);
    
    ptElementAstreTerre-> ptElementAstreSuivant = ptElementAstreLune;
        
      
    
    return ptElementAstreSoleil;

}

Astre* ParcourListeElementAstre(ElementAstre* ptElementAstreInitial, int nb) {
	int compteur=0;
 	ElementAstre* ptElementAstreCourant = ptElementAstreInitial;
 	while( ptElementAstreCourant != NULL && compteur!= nb)
 	{
	    	ptElementAstreCourant = ptElementAstreCourant -> ptElementAstreSuivant;
	    	compteur++;
	    }
	return ptElementAstreCourant -> ptAstre ;

}







void ListeElementAstre(ElementAstre* ptElementAstreInitial)
{
    ElementAstre* ptElementAstreCourant = ptElementAstreInitial;
    while( ptElementAstreCourant != NULL )
    {
    	Astre* ptAstre = ptElementAstreCourant -> ptAstre;
    	if( ptAstre != NULL )
    	{
    	    printf( "\n%s :\n", ptAstre -> nom );
    	    printf( " \n rayon : %f", ptAstre -> rayon );
    	    printf( " \n T : %ld \n", ptAstre -> T );
    	}
    	
    	ptElementAstreCourant = ptElementAstreCourant -> ptElementAstreSuivant;
    }
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
    ptAstre->vx = 0;
    ptAstre->vy = 0;
    ptAstre->T = 0;
    ptAstre->distanceCentreGravitation = 0;
    ptAstre->xGravitation = 0;
    ptAstre->yGravitation = 0;
}

void Init_AstreTerre(Astre *ptTerre)
{
    strcpy(ptTerre->nom, "La Terre");
    strcpy(ptTerre->type, "Planète");
    ptTerre->couleur = Cyan;
    ptTerre->rayon = 6371;
    ptTerre->distanceCentreGravitation=150000000;
    ptTerre->T=365;
    ptTerre->x = 150000000;
    ptTerre->y = 0;
}

void Init_AstreLune(Astre *ptLune)
{
    strcpy(ptLune->nom, "La Lune");
    strcpy(ptLune->type, "Satellite naturel");
    ptLune->couleur = GrisFonce;
    ptLune->rayon = 1737.0;
    ptLune->distanceCentreGravitation=384467;
    ptLune->T=28;
    ptLune->x = 1884467;
    ptLune->y = 0;
}

void Init_AstreSoleil(Astre *ptSoleil)
{
    strcpy(ptSoleil->nom, "Le Soleil");
    strcpy(ptSoleil->type, "Étoile");
    ptSoleil->couleur = Jaune;
    ptSoleil->rayon=696340;
    ptSoleil->x = 0;
    ptSoleil->y = 0;
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
    Astre* ptNull;
    ptNull=&AstreNull;
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
    int cpt=0;
	printf("\n%f\n",Planete->x);
	printf("%f\n",Planete->y);

    if (Planete->distanceCentreGravitation != 0) {
        printf("%f\n", Planete->distanceCentreGravitation);
        double alpha = acos((Planete->x / Planete->distanceCentreGravitation));
        printf("%f\n",alpha);
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
        Planete->x = Planete->distanceCentreGravitation * cos(alpha);
        Planete->y = Planete->distanceCentreGravitation * sin(alpha);
    }

    printf("*******************************");
    printf("\nNouveau x :%f", Planete->x);
    printf("Nouveau y :%f \n", Planete->y);
    printf("*******************************\n");
    

}








