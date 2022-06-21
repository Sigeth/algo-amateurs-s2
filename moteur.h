#ifndef MOTEUR_H
#define MOTEUR_H
#include "time.h"


typedef enum {Rouge, Vert, Bleu, Jaune, Cyan, GrisClair, GrisFonce, Orange, Creme, Cafe, BleuCiel}
        Couleur;


typedef struct Astre {
	char* nom;
	char* type;
	Couleur couleur;
	float rayon;
	double masse;
	float x;
	float y;
    	float previousX;
    	float previousY;
	float vt;
	float vx;
	float vy;
	char* nomGravitation;
	float F;
	float deltaV;
	float distanceCentreGravitation;
}Astre;


//typedef struct ElementAstre ElementAstre;

typedef struct ElementAstre
{
	Astre* ptAstre;
	struct ElementAstre* ptElementAstrePrecedent;
	struct ElementAstre* ptElementAstreSuivant;
} ElementAstre;

//Fonctions gérant les listes chainées
ElementAstre *InitElementAstre(char* nomSave,time_t* t );
Astre* ParcourListeElementAstre(ElementAstre* ptElementAstreInitial, int nb);
Astre* RechercheParNom(ElementAstre* ptElementAstreInitial, char* nom_Recherche);
ElementAstre* InitElementAstre();
void ListeElementAstre(ElementAstre* ptElementAstreInitial);
void AjouteElementAstre(ElementAstre *ptElementAstreInitial, Astre* NewAstre);

int mainMoteur(int argc, char **argv);


//Fonctions d'initialisation
void Init_AstreMercure(Astre *ptMercure);
void Init_AstreVenus(Astre *ptVenus);
void Init_AstreMars(Astre *ptMars);
void Init_AstreJupiter(Astre* ptJupiter);
void Init_AstreSaturne(Astre* ptSaturne);
void Init_AstreUranus(Astre* ptUranus);
void Init_AstreNeptune(Astre* ptNeptune);
void Init_Astre(Astre* ptAstre);
void Init_AstreLune(Astre *ptLune);
void Init_AstreTerre(Astre *ptTerre);
void Init_AstreSoleil(Astre *ptSoleil);



//Fonctions devenues inutiles ; mais on les laisse par nostalgie
void modif_poss_Gravitation(Astre* ptAstre,int x, int y);
void modif_poss_astre(Astre* ptAstre,int x, int y);

void ListrePlanete(Astre** TabAstre);


void UpdateObjet(Astre *Planete, Astre* Gravitation);

/*void UpdateObjetRealEllipse(Astre *Planete, Astre* Gravitation, int t);
void Init_AstreISS(Astre* ptISS);
void MoteurCalculForce(Astre* Planete,Astre* CentreGravitation);*/


//void UpdateObjetRealEllipse(Astre *Planete, Astre* Gravitation, int t);
#endif
