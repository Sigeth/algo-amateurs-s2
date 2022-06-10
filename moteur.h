

typedef struct Astre {
	char* nom;
	char* type;
	char* couleur;
	float rayon;
	double masse;
	long int T;
	float x;
	float y;
	float vx;
	float vy;
	float xGravitation;
	float yGravitation;
	float distanceCentreGravitation;
}Astre;

void UpdateObjet(Astre* Planete);
void AjouteElmTab(Astre** TabAstre, Astre* NewAstre);
void CreerTab(Astre** TabAstre);
void modif_poss_Gravitation(Astre* ptAstre,int x, int y);
void modif_poss_astre(Astre* ptAstre,int x, int y);
void Init_Astre(Astre* ptAstre);
void ListrePlanete(Astre** TabAstre);
int mainMoteur(int argc, char **argv);
