#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"

int main(int argc, char ** argv) { 
	Astre Planete;
	Astre* PtPlanete=&Planete;
	Init_Astre(PtPlanete);
	Planete.T=88;
	Planete.rayon=20000;
	Planete.x=20000;
	Planete.y=0.0;
	printf("%ld",PtPlanete->T);
	UpdateObjet(PtPlanete);
	//free(PtPlanete);
	
}

/* Fonction Init_Astre
 * Fonction qui initialise la structure Astre
 *@param ptAstre
 */

void Init_Astre(Astre* ptAstre){
	ptAstre->nom=(char*)malloc(10*sizeof(char));
	ptAstre->type=(char*)malloc(15*sizeof(char));
	ptAstre->couleur=(char*)malloc(15*sizeof(char));
	ptAstre->rayon=0;
	ptAstre->masse=0;
	ptAstre->x=0;
	ptAstre->y=0;
	ptAstre->vx=0;
	ptAstre->vy=0;
	ptAstre->T=0;
	ptAstre->distanceCentreGravitation=0;
	ptAstre->xGravitation=0;
	ptAstre->yGravitation=0;
}


void modif_poss_astre(Astre* ptAstre,int x, int y){
	ptAstre->x=x;
	ptAstre->y=y;
}
void modif_Temps(Astre* ptAstre,long int T){
	ptAstre->T=T;
}

void modif_poss_Gravitation(Astre* ptAstre,int x, int y){
	ptAstre->xGravitation=x;
	ptAstre->yGravitation=y;
}

void CreerTab(Astre* TabAstre) {
	TabAstre=(Astre*)malloc(50*sizeof(Astre));
	
}

void AjouteElmTab(Astre** TabAstre, Astre* NewAstre) {
	int cpt=0;
	Astre AstreNull;
	Astre* ptNull=&AstreNull;
	for(int i=0;i<sizeof(TabAstre);i++){
		if(TabAstre[i]->nom==NULL) {
			TabAstre[i]=NewAstre;
			cpt++;
		}
	}
	if(cpt==0) {
		*TabAstre=(Astre*)realloc(TabAstre,sizeof(TabAstre+1)*sizeof(int));
		TabAstre[sizeof(TabAstre-1)]=NewAstre;		
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

void UpdateObjet(Astre* Planete){
	double alpha=acos((Planete->x/Planete->rayon)*3.14/180);
	alpha+=(2*M_PI)/Planete->T ;//correspond à un décalage de 1s si le tour fait T secondes
	Planete->x=Planete->rayon*cos(alpha);
	Planete->y=Planete->rayon*sin(alpha);
	printf("%f",Planete->x);
	printf("%f",Planete->y);

}








