#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include "moteur.h"
#include <string.h>
#define nbplanete 8

void sauvegarder(char *nomdesauvegarde,ElementAstre* ptElementAstreInitial){// a pas utiliser car est dans nomsauvegarde
    FILE * f = fopen(nomdesauvegarde, "wb"); // ouvre le fichier en mode écriture binaire
     ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        }

    
    if(f != NULL) // si l'ouverture s'est bien passée
    {
        if(fwrite(ptElementAstreCourant, sizeof(ptElementAstreCourant), 1, f) != 1) // écris t1 dans le fichier avec fwrite
        {
            perror("Erreur lors de l'ecriture des donnees dans le fichier!!");
            fclose(f);
        }
                ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
        }

}}
void nomdesauvegarde(ElementAstre *ptElementAstreInitial) {//fonction qui permet de creer la sauvegarde
    printf("nom de la sauvegarde :");//attention sauvegarde en un mot
    char a[100];
    scanf("%s", a);
    FILE *f = NULL;
    f = fopen("pastouche", "a");
    if (f != NULL) {
        fputs(a, f);
        fputs("\n", f);
        fclose(f);
    }

    sauvegarder(a,ptElementAstreInitial);
}

void listesauvegarde() {//quand vous voulez avoir la liste des sauvegardes, juste utiliser la fonction
    char a[100];
    FILE *fi = fopen("pastouche", "r");
    if (fi != NULL) {
        printf("voici la liste de vos sauvegarde :\n");
        while (fscanf(fi, "%s", a) != EOF) {//prends le chaine de char suivante tant que on est pas a la fin du fichier
            printf("%s \n", a);
        }
        fclose(fi);
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

ElementAstre *loadsave(char save,ElementAstre *ptElementAstreInitial){//recharger une sauvegarde.renvois la liste chainé
	FILE * f = fopen("save", "rb");
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

