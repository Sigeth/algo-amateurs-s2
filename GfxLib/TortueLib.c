// Veuillez reporter tout commentaire a ghislain.oudinet@isen.fr
// Version 1

#include "TortueLib.h"
#include "GfxLib.h"
#include <math.h>

// Place la tortue en (0; 0), orientée à 0 radian et stylo levé
void initialiseTortue(Tortue *tortue)
{
	tortue->x = 0.;
	tortue->y = 0.;
	tortue->orientation = 0.;
	tortue->trace = false;
}

// Baisse le stylo de façon à ce qu'un déplacement de la tortue s'accompagne d'un tracé
void baisseStyloTortue(Tortue *tortue)
{
	tortue->trace = true;
}

// Lève le stylo de façon à ce qu'un déplacement de la tortue ne s'accompagne pas d'un tracé
void leveStyloTortue(Tortue *tortue)
{
	tortue->trace = false;
}

void placeTortue_en(Tortue *tortue, double x, double y)
{
	if(tortue->trace)
		ligne(tortue->x, tortue->y, x, y);
	tortue->x = x;
	tortue->y = y;
}

void tourneTortue_de(Tortue *tortue, double radians)
{
	tortue->orientation += radians;
}

void avanceTortue_de(Tortue *tortue, double longueur)
{
	double prochainX = tortue->x + longueur*cos(tortue->orientation);
	double prochainY = tortue->y + longueur*sin(tortue->orientation);
	if (tortue->trace)
		ligne(tortue->x, tortue->y, prochainX, prochainY);
	tortue->x = prochainX;
	tortue->y = prochainY;
}

