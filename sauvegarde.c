#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include "moteur.h"
#include <string.h>
#include <dirent.h>
#define nbplanete 8

void sauvegarder(char *nomdesauvegarde,ElementAstre* ptElementAstreInitial, time_t t){// a pas utiliser car est dans nomsauvegarde
    FILE * f = fopen(nomdesauvegarde, "w"); 
     ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
     ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
     fprintf(f,"%ld\n",t);
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        }

	fprintf(f,"%f\n",ptAstre->x);
	fprintf(f,"%f\n",ptAstre->y);
	fprintf(f,"%f\n",ptAstre->previousX);
	fprintf(f,"%f\n",ptAstre->previousY);
	fprintf(f,"%f\n",ptAstre->vt);
	fprintf(f,"%f\n",ptAstre->vx);
	fprintf(f,"%f\n",ptAstre->vy);
	fprintf(f,"%f\n",ptAstre->F);
	fprintf(f,"%f\n",ptAstre->deltaV);
	fprintf(f,"%f\n",ptAstre->distanceCentreGravitation);	
	
    
       
        
ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
}fclose(f);}
void nomdesauvegarde(ElementAstre *ptElementAstreInitial, time_t t) {//fonction qui permet de creer la sauvegarde
    printf("nom de la sauvegarde :");//attention sauvegarde en un mot
    char a[100];
    scanf("%s", a);
    FILE *f = NULL;
    char b[50];
    strcpy(b,"saves/");
    strcat(b,a);
    f = fopen(b, "a");

    
    sauvegarder(b,ptElementAstreInitial, t);
}
int nbsave(DIR *d) {//quand vous voulez avoir la liste des sauvegardes, juste utiliser la fonction
    struct dirent *dir;
    d = opendir("saves/");
    int nbSave = 0;
    if (d) {
        while ((dir = readdir(d)) != NULL)
     {   
	nbSave++;
        }
        //nbSave=nbSave;
        closedir(d);
        return  nbSave;
    }}

void listesauvegarde(char** a)//quand vous voulez avoir la liste des sauvegardes, juste utiliser la fonction
{
    DIR *d;
    struct dirent *dir;
    d = opendir("saves/");
    int i=0;
    if (d) {
        while ((dir = readdir(d)) != NULL)
        {
            printf("çava");
            printf("%s\n", dir->d_name);
            //strcpy(a[0],dir->d_name);
            //strcpy(a[0],"oui");
            a[i]=dir->d_name;
            i++;
        }
        closedir(d);
    }
    }


void delsauvegarde() {//supprime tous les fichiers lié à la sauvegarde pour faire de la place
    char a[100];
    FILE *fi = fopen("pastouche", "r");
    if (fi != NULL) {
        printf("voici la liste de vos sauvegarde :\n");
        while (fscanf(fi, "%s", a) != EOF) {
            remove(a);
        }
        fclose(fi);
        remove("pastouche");
    }
}

ElementAstre *loadsave(char *save,ElementAstre *ptElementAstreInitial){//recharger une sauvegarde.renvois la liste chainé
	FILE * f = fopen("saves/save", "rb");
	int i=nbplanete;
	Astre* ptAstre=malloc(sizeof(Astre));
	AjouteElementAstre(ptElementAstreInitial,ptAstre);
	ElementAstre* astre[nbplanete];
	while(i==nbplanete){
	i=fread(astre,sizeof(Astre),nbplanete,f);
	for(int j=0;j<i;j++){
	AjouteElementAstre(ptElementAstreInitial,astre[j]);}
    /*AjouteElementAstre(ptElementAstreInitial,ptAstreLune);
    AjouteElementAstre(ptElementAstreInitial,ptAstreMercure);
    AjouteElementAstre(ptElementAstreInitial,ptAstreVenus);
    AjouteElementAstre(ptElementAstreInitial,ptAstreMars);
    AjouteElementAstre(ptElementAstreInitial,ptAstreJupiter);
    AjouteElementAstre(ptElementAstreInitial,ptAstreSaturne);
    AjouteElementAstre(ptElementAstreInitial,ptAstreUranus);
    AjouteElementAstre(ptElementAstreInitial,ptAstreNeptune);*/}
    return ptElementAstreInitial;}

