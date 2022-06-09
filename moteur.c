#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"

int main(int argc, char ** argv) { 
	Astre Astretest;
	Astre* ptAstre=&Astretest;
	Init_Astre(ptAstre);



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
	ptAstre->distanceCentreGravitation=0;
	ptAstre->xGravitation=0;
	ptAstre->yGravitation=0;
}


void modif_poss_astre(Astre* ptAstre,int x, int y){
	ptAstre->x=x;
	ptAstre->y=y;
}

void modif_poss_Gravitation(Astre* ptAstre,int x, int y){
	ptAstre->xGravitation=x;
	ptAstre->yGravitation=y;
}

void CreerTab(Astre* TabAstre) {
	TabAstre=(Astre*)malloc(50*sizeof(Astre));

}

void AjouteElmTab(Astre* TabAstre, Astre NewAstre) {
	int cpt=0;
	for(int i=0;i<sizeof(TabAstre);i++){
		if(TabAstre[i]==NULL) {
			TabAstre[i]=NewAstre;
			cpt++;
		}
	}
	if(cpt==0) {
		TabAstre=(Astre*)realloc(TabAstre,sizeof(TabAstre+1)*sizeof(int));
		TabAstrie[sizeof(TabAstre-1)]=NewAstre;		
	}

}


/*
 * Fonction UpdateObjet
 * Permet de renvoyer la position d'un objet à un temps t=0
 * @param Plaete
 * @prama t =>temps écoulé depuis le début de la simiulation
 */

/*sert à faire une trajectoire circulaire*/ 

void UpdateObjet_alpha(Astre* Planete){
	double float alpha=acos(Planete->x/Planete->rayon)
	alpha+=0.017 //correspond à 1 degres
	Planete->x=Planete->rayon*cos(alpha);
	Planete->y=Planete->rayon*sin(alpha);
	printf("%f",Planete->x);
	printf("%f",Planete->y);

}



/*calcul de la vitesse idée en tête mais c'est long et je fais ça demain*/
void UpdateObjet_alpha(Astre* Planete,double float alpha){
	
	
	
}






