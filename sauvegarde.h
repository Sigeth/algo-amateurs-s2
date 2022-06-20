#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include <string.h>
void nomdesauvegarde(ElementAstre *ptElementAstreInitial, time_t t);
void listesauvegarde(); 
void delsauvegarde();
void sauvegarder(char *a,ElementAstre *ptElementAstreInitial, time_t t);
ElementAstre* loadsave(char *a,ElementAstre *ptElementAstreInitial);
int nbsave();
