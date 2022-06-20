#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include <string.h>


//fonction test, n'a aucun impact sur le code;
int mainMoteur(int argc, char **argv) {
    //test
    ElementAstre *ptElementAstreSoleil = InitElementAstre(NULL);
    ListeElementAstre(InitElementAstre(NULL));
    ParcourListeElementAstre(ptElementAstreSoleil, 1);
    
    return 0;

}

/*Fonction InitElementAstre
 * Permet de créer et d'initialiser la liste chainée
 * @param nomSave : nom de la sauvegarde si il y'en à une, sinon NULL;
 * return le premier élement de la liste
 */
ElementAstre *InitElementAstre(char* nomSave ) {
    //premier élément //
    ElementAstre *ptElementAstreSoleil = malloc(sizeof(ElementAstre));
    ptElementAstreSoleil->ptElementAstrePrecedent = NULL;
    ptElementAstreSoleil->ptElementAstreSuivant = NULL;
    ptElementAstreSoleil->ptAstre = malloc(sizeof(Astre));
    Init_Astre(ptElementAstreSoleil->ptAstre);
    Init_AstreSoleil(ptElementAstreSoleil->ptAstre);
	
    if(nomSave != NULL){
    	ptElementAstreSoleil=loadsave(nomSave,ptElementAstreSoleil); //fonction qui "load une sauvegarde"
	printf("omg peut etre pas la segmentation"); //:TODO: à enlever avant la présentation
	}
	
    else {
    Astre* ptAstre=malloc(sizeof(Astre));
    Astre* ptAstreLune=malloc(sizeof(Astre));
    Astre* ptAstreMercure=malloc(sizeof(Astre));
    Astre* ptAstreVenus=malloc(sizeof(Astre));
    Astre* ptAstreMars=malloc(sizeof(Astre));
    Astre* ptAstreJupiter=malloc(sizeof(Astre));
    Astre* ptAstreSaturne=malloc(sizeof(Astre));
    Astre* ptAstreUranus=malloc(sizeof(Astre));
    Astre* ptAstreNeptune=malloc(sizeof(Astre));
    
   
   Init_Astre(ptAstre);
   Init_Astre(ptAstreLune);
   Init_Astre(ptAstreMercure);
   Init_Astre(ptAstreVenus);
   Init_Astre(ptAstreMars);
   Init_Astre(ptAstreJupiter);
   Init_Astre(ptAstreSaturne);
   Init_Astre(ptAstreUranus);
   Init_Astre(ptAstreNeptune);
   
    
    Init_AstreTerre(ptAstre);
    Init_AstreLune(ptAstreLune);
    Init_AstreMercure(ptAstreMercure);
    Init_AstreVenus(ptAstreVenus);
    Init_AstreMars(ptAstreMars);
    Init_AstreJupiter(ptAstreJupiter);
    Init_AstreSaturne(ptAstreSaturne);
    Init_AstreUranus(ptAstreUranus);
    Init_AstreNeptune(ptAstreNeptune);
   
    
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

}
    return ptElementAstreSoleil;

}

/*Fonction ParcourListeElementAstre
 * Permet de parcourir la liste afin d'avoir l'élément numéro nb de la liste
 * @param ptElementAstreInitial : premier élément de la liste
 * @param nb : numéro de l'élément
 * return l'élément numéro nb de la liste
 */
Astre *ParcourListeElementAstre(ElementAstre *ptElementAstreInitial, int nb) {
    int compteur = 0;
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL && compteur != nb) {
        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
        compteur++;
    }
    return ptElementAstreCourant->ptAstre;

}

/*Fonction RechercheParNom
 * Permet de connaitre l'emplacement d'un astre dans la liste avec son nom
 * @param ptElementAstreInitial : premier élément de la liste
 * @param  nom_Recherche: nom de l'élément
 * return l'élément correspondant à la recherche ou NULL;
 */
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

/*Fonction ListeElementAstre
 * Permet d'afficher les informations de la liste, sert principalement dans le cadre de test 
 * @param ptElementAstreInitial : premier élément de la liste
 * return void;
 */
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


/*Fonction CompteElementAstre
 * Permet de compter le nombre d'élément de la liste  
 * @param ptElementAstreInitial : premier élément de la liste
 * return le nombre d'élément de la liste;
 */
int CompteElementAstre(ElementAstre *ptElementAstreInitial) {
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    int cpt=0;
    while (ptElementAstreCourant != NULL) {
        cpt++;
        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    return cpt;
}


/*Fonction AjouteElementAstre
 * Permet d'ajouter un élément à la liste chainée 
 * @param ptElementAstreInitial : premier élément de la liste
 * @param NewAstre : Element à ajouter à la liste
 * return void
 */
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
}


/*Fonction FreeTab
 * Permet de désalouer la mémoire de la liste
 * @param ptElementAstreInitial : premier élément de la liste
 * return void
 */
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
    ptTerre->x = -26529958.000000;
    ptTerre->y =147635232.000000;
    ptTerre->masse=5.9736*pow(10,24);
    ptTerre->vt=29.79;
    
}

void Init_AstreLune(Astre *ptLune) {
    strcpy(ptLune->nom, "La Lune");
    strcpy(ptLune->type, "Satellite naturel");
    ptLune->couleur = GrisFonce;
    ptLune->rayon = 1737.0;
    strcpy(ptLune->nomGravitation, "La Terre");
    ptLune->distanceCentreGravitation = 384470;
    ptLune->x = 0;
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
	ptMercure->x = 27522270.000000;
	ptMercure->y = -51054136.000000;
	ptMercure->vt=48.7999;
	ptMercure->masse=3.3*pow(10,23);

}

void Init_AstreVenus(Astre *ptVenus) {
    	strcpy(ptVenus->nom, "Venus");
	strcpy(ptVenus->type, "Planete");
	ptVenus->couleur = Orange;
	ptVenus->rayon = 6051;
	strcpy(ptVenus->nomGravitation, "Le Soleil");
	ptVenus->distanceCentreGravitation = 108000000;
	ptVenus->x = -40906248.000000;
	ptVenus->y = -99953384.000000;
	ptVenus->masse=4.87*pow(10,24);
	ptVenus->vt=35.009998;
}

void Init_AstreMars(Astre *ptMars) {
    	strcpy(ptMars->nom, "Mars");
	strcpy(ptMars->type, "Planete");
	ptMars->couleur = Rouge;
	ptMars->rayon = 3396;
	strcpy(ptMars->nomGravitation, "Le Soleil");
	ptMars->distanceCentreGravitation = 228000000;
	ptMars->masse=6.417*pow(10,23);
	ptMars->x = 187034784.000000;
	ptMars->y = 130391688.000000;
	ptMars->vt=24.2199;
	}

void Init_AstreJupiter(Astre* ptJupiter) {
	strcpy(ptJupiter->nom, "Jupiter");
	strcpy(ptJupiter->type, "Planete");
	ptJupiter->couleur = Creme;
	ptJupiter->rayon = 69911;
	strcpy(ptJupiter->nomGravitation, "Le Soleil");
	ptJupiter->distanceCentreGravitation = 779000000;
	ptJupiter->masse=1.898*pow(10,27);
	ptJupiter->x = 575373952.000000;
	ptJupiter->y = 525153120.000000;
	ptJupiter->vt=13.05;
	

}

void Init_AstreSaturne(Astre* ptSaturne) {
	strcpy(ptSaturne->nom, "Saturne");
	strcpy(ptSaturne->type, "Planete");
	ptSaturne->couleur = Cafe;
	ptSaturne->rayon = 58232;
	strcpy(ptSaturne->nomGravitation, "Le Soleil");
	ptSaturne->distanceCentreGravitation = 1400000000;
	ptSaturne->masse=568*pow(10,21);
	ptSaturne->x = -1360571264.000000;
	ptSaturne->y = 329917696.000000;
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
	ptUranus->x = 1576615552.000000;
	ptUranus->y = 2398162688.000000;
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
	ptNeptune->x = 3962831616.000000;
	ptNeptune->y = 2132126464.000000;
	ptNeptune->vt = 5.43;
}







/*
 * Fonction UpdateObjetReal 
 * Permet de faire une trajectoire réaliste
 * @param Planete
 * @param Gravitation
 * @prama t =>temps écoulé depuis le début de la simiulation
 */
 
 void UpdateObjetReal(Astre *Planete, Astre* Gravitation, int t) {
   int x=0;
   int y=0;
    MoteurCalculForce(Planete,Gravitation);
    
    if (Planete->distanceCentreGravitation != 0) {
 
        if (strcmp(Planete->nomGravitation,"Le Soleil")){
        		Planete->F+=Gravitation->F; //2ème loi de Newton (somme des forces ext = ma) 
        }
        float a=Planete->F/Gravitation->masse; //formule du cours
        
        Planete->deltaV=a*t;
 
        Planete->vt+=Planete->deltaV;

        double alpha = acos(((Planete->x - Gravitation->previousX) / Planete->distanceCentreGravitation));
    
        double deltaM=Planete->vt*t+(a*t*t/2);
    
        if (Gravitation->y - 0.1 < Planete->y < Gravitation->y + 0.1) {
            alpha = -alpha;
        }
        alpha +=acos(1-(((deltaM)*(deltaM))/(2*Planete->distanceCentreGravitation * Planete->distanceCentreGravitation)));
        
        Planete->distanceCentreGravitation=sqrt((Planete->distanceCentreGravitation*sqrt(pow(Planete->distanceCentreGravitation,2)+pow(deltaM,2)))+sqrt(Planete->distanceCentreGravitation*sqrt(pow(Planete->distanceCentreGravitation,2)-pow(deltaM,2)))/2);
        
        /*
        Planete->x = Planete->distanceCentreGravitation * cos(alpha) + Gravitation->x;
        Planete->y = Planete->distanceCentreGravitation * sin(alpha) + Gravitation->y;
        */
        
        /*  if(!strcmp(Planete->nom,"La Lune")){
          
        x = Gravitation->x + Planete->distanceCentreGravitation;
        y = Gravitation->y + Planete->distanceCentreGravitation;
        
    }*/
    
        Planete->x = Planete->distanceCentreGravitation * cos(alpha) + x;
        Planete->y = Planete->distanceCentreGravitation * sin(alpha) + y;
        

}
}
/*Fonction de calcul de la force d'un astre sur une planete/satelite
 *@param Planete : la planéte concernée par l'attraction gravitationelle
 *@param Gravitation : L'astre exerçant l'attraction gravitationelle
 */

void MoteurCalculForce(Astre* Planete,Astre* Gravitation){
	Planete->F=(6.673*pow(10,-11)*(Planete->masse + (Gravitation->masse))/(pow(Planete->distanceCentreGravitation,2)));
}



/* ANCIENNES FONTIONS ET PROTOTYPES  : 



void UpdateObjetRealEllipse(Astre *Planete, Astre* Gravitation, int t) {
//INIT

    float acc=Planete->masse/Planete->F; //formule du cours
    
    MoteurCalculForce(Planete,Gravitation);
    
    float G=6.673*pow(10,-11);

    float a = cbrt(pow(Planete->T,2)*G*((Planete->masse+Gravitation->masse))/pow(4*M_PI,2));  //demi grand axe 
    //float b =sqrt(Planete->distanceCentreGravitation*Planete->distMin)); 	      //demi petit axe
    float c =sqrt(pow(a,2)-pow(b,2));  					      //demie deistance focale
    float e=c/a;							      //exentricité
    
    //calcul du rayon affin de ne pas avoir une trajectoire circulaire mais une ellipse
    
 
      
    //vitesse de la planéte en fonction de la distance à son centre de gravitation voir pdf pour détails :TODO: Faire le pdf
    Planete->vt=sqrt(G*(Planete->masse+Gravitation->masse)*((2/Planete->distanceCentreGravitation)-(1/a))); 
    
    
    double alpha = acos(((Planete->x - Gravitation->previousX) / Planete->distanceCentreGravitation));
    double deltaM=Planete->vt*t+(acc*t*t/2);
    float m=2*M_PI/Planete->T;
      
//Fin INIT        
    if (Planete->distanceCentreGravitation != 0) {
       //AFFICHAGE EN CONSOLE POUR DEBUG  TODO:à supp à la fin 
     
        Planete->previousX = Planete->x;
        Planete->previousY = Planete->y;
        printf("Mon nom : %s\n",Planete->nom);
        printf("Mon centre de gravitation : %s\n", Gravitation->nom);
        printf("Ses coordonées :\nx : %f\ny : %f\n", Gravitation->x, Gravitation->y);

        printf("distanceCentreGravitation: %f\n", Planete->distanceCentreGravitation);
        
        printf("Diff x: %f\n", (Planete->x - Gravitation->previousX));
        printf("Force : %f\n", (Planete->F));
        
        //FIN AFFICHAGE
        
        if (!strcmp(Planete->nomGravitation,"Le Soleil")){
        		Planete->F+=Gravitation->F; //2ème loi de Newton (somme des forces ext = ma)
        }


        
        if (Gravitation->y - 0.1 < Planete->y < Gravitation->y + 0.1) {  
        //Pour faire un tour complet (math.h ne prend en compte que les valeurs comprises entre -pi et pi
            alpha = -alpha;
        }
        //viens de la formule du cours voir PDF pour détails :TODO:Faire le pdf
        alpha=e*sin(alpha)+m;
        Planete->distanceCentreGravitation=a*(1-e*cos(alpha)); 

        Planete->x = a*(cos(alpha)-e);
        Planete->y = a*sqrt(1-pow(e,2));
       
        //
     }
     }
*/




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







