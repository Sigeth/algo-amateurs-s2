#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include "moteur.h"
#include <string.h>

void sauvegarde (char *nomdesauvegarde, ElementAstre *ptElementAstreInitial)
{
    FILE * f = fopen(nomdesauvegarde, "wb"); // ouvre le fichier en mode lecture/écriture binaire
     ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        }

    
    if(f != NULL) // si l'ouverture s'est bien passée
    {
        if(fwrite(ptElementAstreInitial, sizeof(ptElementAstreInitial), 1, f) != 1) // écris t1 dans le fichier avec fwrite
        {
            perror("Erreur lors de l'ecriture des donnees dans le fichier!!");
            fclose(f);
        }
                ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
        }

}}

void nomdesauvegarde(ElementAstre *ptElementAstreInitial) {
    printf("nom de la sauvegarde :");
    char a[100];
    scanf("%s", a);
    FILE *f = NULL;
    f = fopen("pastouche", "a");
    if (f != NULL) {
        fputs(a, f);
        fputs("\n", f);
        fclose(f);
    }

    sauvegarde(a,ElementAstre *ptElementAstreInitial);
}

void listesauvegarde() {
    char a[100];
    FILE *fi = fopen("pastouche", "r");
    if (fi != NULL) {
        printf("voici la liste de vos sauvegarde :\n");
        while (fscanf(fi, "%s", a) != EOF) {
            printf("%s \n", a);
        }
        fclose(fi);
    }
}

void delsauvegarde() {
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
void sauvegarde (char *nomdesauvegarde, ElementAstre *ptElementAstreInitial)
{
    FILE * f = fopen(nomdesauvegarde, "wb"); // ouvre le fichier en mode lecture/écriture binaire
     ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        }

    
    if(f != NULL) // si l'ouverture s'est bien passée
    {
        if(fwrite(ptElementAstreInitial, sizeof(ptElementAstreInitial), 1, f) != 1) // écris t1 dans le fichier avec fwrite
        {
            perror("Erreur lors de l'ecriture des donnees dans le fichier!!");
            fclose(f);
        }
                ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
        }

}}

