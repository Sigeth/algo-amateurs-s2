// Veuillez reporter tout commentaire a ghislain.oudinet@isen.fr
// Version 1

#ifndef TORTUE_H
#define TORTUE_H

#include <stdbool.h>

typedef struct Tortue
{
	double x;
	double y;
	double orientation;
	bool trace;
} Tortue;

// Place la tortue en (0; 0), orientée à 0 radian et stylo levé
void initialiseTortue(Tortue *tortue);
// Baisse le stylo de façon à ce qu'un déplacement de la tortue s'accompagne d'un tracé
void baisseStyloTortue(Tortue *tortue);
// Lève le stylo de façon à ce qu'un déplacement de la tortue ne s'accompagne pas d'un tracé
void leveStyloTortue(Tortue *tortue);
void placeTortue_en(Tortue *tortue, double x, double y);
void tourneTortue_de(Tortue *tortue, double radians);
void avanceTortue_de(Tortue *tortue, double longueur);

#endif
