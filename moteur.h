
typedef enum {Rouge, Vert, Bleu, Jaune, Cyan, GrisClair, GrisFonce}
        Couleur;


typedef struct Astre {
	char* nom;
	char* type;
	Couleur couleur;
	float rayon;
	double masse;
	long int T;
	float x;
	float y;
	float vx;
	float vy;
	char* nomGravitation;
	float xGravitation;
	float yGravitation;
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
void ListeElementAstre(struct ElementAstre* ptElementAstreInitial);
Astre* ParcourListeElementAstre(ElementAstre* ptElementAstreInitial, int nb);
Astre* RechercheParNom(ElementAstre* ptElementAstreInitial, char* nom_Recherche);
ElementAstre* InitElementAstre();
void UpdateObjet(Astre *Planete, Astre* Gravitation);

void AjouteElmTab(Astre** TabAstre, Astre* NewAstre);
void CreerTab(Astre** TabAstre);
void modif_poss_Gravitation(Astre* ptAstre,int x, int y);
void modif_poss_astre(Astre* ptAstre,int x, int y);
void Init_Astre(Astre* ptAstre);
void ListrePlanete(Astre** TabAstre);
int mainMoteur(int argc, char **argv);
