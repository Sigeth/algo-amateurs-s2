#ifndef MOTEUR_H
#define MOTEUR_H
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
	float xGravitation;
	float yGravitation;
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



void Init_AstreLune(Astre *ptLune);
void Init_AstreTerre(Astre *ptTerre);
void Init_AstreSoleil(Astre *ptSoleil);
void ListeElementAstre(ElementAstre* ptElementAstreInitial);

Astre* ParcourListeElementAstre(ElementAstre* ptElementAstreInitial, int nb);
Astre* RechercheParNom(ElementAstre* ptElementAstreInitial, char* nom_Recherche);
ElementAstre* InitElementAstre();
void UpdateObjet(Astre *Planete, Astre* Gravitation);
void AjouteElementAstre(ElementAstre *ptElementAstreInitial, Astre* NewAstre);
void Init_AstreMercure(Astre *ptMercure);
void Init_AstreVenus(Astre *ptVenus);
void Init_AstreMars(Astre *ptMars);
void Init_AstreJupiter(Astre* ptJupiter);
void Init_AstreSaturne(Astre* ptSaturne);
void Init_AstreUranus(Astre* ptUranus);
void Init_AstreNeptune(Astre* ptNeptune);

void AjouteElmTab(Astre** TabAstre, Astre* NewAstre);
void CreerTab(Astre** TabAstre);
void modif_poss_Gravitation(Astre* ptAstre,int x, int y);
void modif_poss_astre(Astre* ptAstre,int x, int y);
void Init_Astre(Astre* ptAstre);
void ListrePlanete(Astre** TabAstre);
int mainMoteur(int argc, char **argv);
void UpdateObjetRealEllipse(Astre *Planete, Astre* Gravitation, int t);
void Init_AstreISS(Astre* ptISS);
void MoteurCalculForce(Astre* Planete,Astre* CentreGravitation);
ElementAstre *InitElementAstre(char* nomSave );

//void UpdateObjetRealEllipse(Astre *Planete, Astre* Gravitation, int t);
#endif
