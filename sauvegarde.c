#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "sauvegarde.h"
#include "moteur.h"
#include <string.h>

void initinfo(info *a) {
    a->x = 0;
    a->y = 0;
    a->previousX = 0;
    a->previousY = 0;
}

void sauvergarde(char *nomdesauvegarde, ElementAstre *ptElementAstreInitial) {
    ElementAstre *ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            printf("Bonjour, je suis %s\n", ptAstre->nom);
        }

        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }

    FILE *f = NULL;
    f = fopen(nomdesauvegarde, "a");
    if (f != NULL) {
        fputs(nomdesauvegarde, f);
        fclose(f);
    }

    free(ptElementAstreCourant);
}

void nomdesauvegarde() {
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
    FILE *fi = NULL;
    fi = fopen(a, "w");
    fclose(fi);
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

