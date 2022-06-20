#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "moteur.h"
#include <string.h>
void nomdesauvegarde(ElementAstre *ptElementAstreInitial);
char** listesauvegarde(); 
void delsauvegarde();
void sauvegarder(char *a,ElementAstre *ptElementAstreInitial);
ElementAstre* loadsave(char *a,ElementAstre *ptElementAstreInitial);
