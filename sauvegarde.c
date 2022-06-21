#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include "moteur.h"
#include <string.h>
#include <dirent.h>

#define nbplanete 8

void sauvegarder(char *nomdesauvegarde, ElementAstre *ptElementAstreInitial,
                 time_t t) {// a pas utiliser car est dans nomsauvegarde
    FILE *f = fopen(nomdesauvegarde, "w");
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    fprintf(f, "%ld\n", t);
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        }

        fprintf(f, "%f\n", ptAstre->x);
        fprintf(f, "%f\n", ptAstre->y);
        fprintf(f, "%f\n", ptAstre->previousX);
        fprintf(f, "%f\n", ptAstre->previousY);
        fprintf(f, "%f\n", ptAstre->vt);
        fprintf(f, "%f\n", ptAstre->vx);
        fprintf(f, "%f\n", ptAstre->vy);
        fprintf(f, "%f\n", ptAstre->F);
        fprintf(f, "%f\n", ptAstre->deltaV);
        fprintf(f, "%f\n", ptAstre->distanceCentreGravitation);


        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
    fclose(f);
}


int nbsave(DIR *d) {//quand vous voulez avoir la liste des sauvegardes, juste utiliser la fonction
    struct dirent *dir;
    d = opendir("saves/");
    int nbSave = 0;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                nbSave++;
            }
            //nbSave=nbSave;
        }
        closedir(d);
        return nbSave;
    }
    return 0;
}

void listesauvegarde(char **a)//quand vous voulez avoir la liste des sauvegardes, juste utiliser la fonction
{
    DIR *d;
    struct dirent *dir;
    d = opendir("saves/");
    int i = 0;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                int length = strlen(dir->d_name);
                a[i] = malloc(sizeof(char) * length);

                strcpy(a[i], dir->d_name);
                i++;
            }
        }
        closedir(d);
    }
}


void loadsave(char *save,ElementAstre *ptElementAstreInitial,time_t* t){
	FILE *f=fopen("saves/save","r") ;
	printf("çamarche");
	/*char* b;
	strcpy(b,"saves/");
    	strcat(b,save);
    	f = fopen(b, "r");*/
	int i=0;
	ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
	ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
	fscanf(f,"%ld\n",t);
    printf("Le temps : %ld\n", *t);
	while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        
	fscanf(f,"%f\n",&ptAstre->x);
	fscanf(f,"%f\n",&ptAstre->y);
	fscanf(f,"%f\n",&ptAstre->previousX);
	printf("monpreviousX est%f",ptAstre->previousX);
	fscanf(f,"%f\n",&ptAstre->previousY);
	fscanf(f,"%f\n",&ptAstre->vt);
	fscanf(f,"%f\n",&ptAstre->vx);
	fscanf(f,"%f\n",&ptAstre->vy);
	fscanf(f,"%f\n",&ptAstre->F);
	fscanf(f,"%f\n",&ptAstre->deltaV);
	fscanf(f,"%f\n",&ptAstre->distanceCentreGravitation);
	i++;
	ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
	}}}	
time_t tps(char* save){
FILE* f;
time_t t;
char* b;
strcpy(b,"saves/");
    	strcat(b,save);
    	f = fopen(b, "r");
    	fscanf(f,"%ld",&t);
    	return t;}	
void nomdesauvegarde(ElementAstre *ptElementAstreInitial, time_t t) {//fonction qui permet de creer la sauvegarde
    char a[100];
    DIR *d;
    struct dirent *dir;
    d = opendir("saves/");
    int j;
    j=nbsave(d);
    closedir(d);
    snprintf(a,6,"%d\n",j);
    FILE *f = NULL;
    char b[50];
    strcpy(b, "saves/");
    strcat(b, a);
    f = fopen(b, "a");


    sauvegarder(b, ptElementAstreInitial, t);
}

