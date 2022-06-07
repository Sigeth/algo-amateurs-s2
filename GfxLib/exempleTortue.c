#include <stdlib.h> // Pour pouvoir utiliser exit() et random()
#include <time.h>	// Pour time()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()
#include "TortueLib.h"	// Pour utiliser les commandes de la tortue

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 800
#define HauteurFenetre 600

// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);

int main(int argc, char **argv)
{
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);
	
	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	
	return 0;
}

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	static Tortue tortue;	//Une structure pour mémoriser l'état de notre tortue
	
	switch (evenement)
	{
		case Initialisation:
			srandom(time(NULL));
			break;
			
		case Affichage:
			
			// On part d'un fond d'ecran blanc
			effaceFenetre (255, 255, 255);

// 			couleurCourante(64, 192, 0);
			couleurCourante(0, 0, 0);
			epaisseurDeTrait(1);
			
			// Place la tortue en (0; 0), orientée à 0 radian et stylo levé
			initialiseTortue(&tortue);
			
			// Lève le stylo de façon à ce qu'un déplacement de la tortue ne s'accompagne pas d'un tracé
			leveStyloTortue(&tortue);

			placeTortue_en(&tortue, largeurFenetre()/2., hauteurFenetre()/2.);

			// Baisse le stylo de façon à ce qu'un déplacement de la tortue s'accompagne d'un tracé
			baisseStyloTortue(&tortue);

			avanceTortue_de(&tortue, 100);
			tourneTortue_de(&tortue, M_PI/2.);
			avanceTortue_de(&tortue, 100);
			tourneTortue_de(&tortue, M_PI/2.);
			break;
			
		case Clavier:
			printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// On force un rafraichissement
					rafraichisFenetre();
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
				printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			else if (etatBoutonSouris() == GaucheRelache)
			{
				printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
			}
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Temporisation: // Quand une temporisation est definie
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}

