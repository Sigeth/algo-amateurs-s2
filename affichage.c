#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "affichage.h"
#include <stdbool.h>
#include <time.h>

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1280
#define HauteurFenetre 720

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);

void afficheSimu(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("Simulation Spatiale - Les Amateurs", LargeurFenetre, HauteurFenetre);

    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    lanceBoucleEvenements();
}

static StateAffichage state = Simulation;
float echellePlanete = 1.0f/10000.0f;
float echelleDistances = 1.0f/500000.0f;
static ElementAstre* ptElementAstreInitial;
static ElementAstre* ptElementAstreCourant;
static int deltaT = 0;
static int deltaTcheck = 6;
static float xCentre = 0.0f;
static float yCentre = 0.0f;
static bool focused = false;
static int* etoiles;
static int nbEtoiles;

void cercle(float centreX, float centreY, float rayon)
{
    const int Pas = 100; // Nombre de secteurs pour tracer le cercle
    const double PasAngulaire = 2.*M_PI/Pas;
    int index;

    for (index = 0; index < Pas; ++index) // Pour chaque secteur
    {
        const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
        triangle(centreX, centreY,
                 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
                 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
        // On trace le secteur a l'aide d'un triangle => approximation d'un cercle
    }

}

void updateEtoiles() {
    for (int i=0;i<nbEtoiles-1;i+=2) {
        etoiles[i] = rand()%largeurFenetre();
        etoiles[i+1] = rand()%largeurFenetre();
    }
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
    static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas


    switch (evenement)
    {
        case Initialisation:

            ptElementAstreInitial = InitElementAstre();
            ptElementAstreCourant = ptElementAstreInitial;
            srand(time(NULL));
            nbEtoiles = 500 + rand()%4500;
            etoiles = malloc(sizeof(int) * nbEtoiles);

            updateEtoiles();

            /* Le message "Initialisation" est envoye une seule fois, au debut du
            programme : il permet de fixer "image" a la valeur qu'il devra conserver
            jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
            pas pu etre lue, soit "image" pointera sur une structure contenant
            les caracteristiques de l'image "imageNB.bmp" */

            // Configure le systeme pour generer un message Temporisation
            // toutes les 20 millisecondes
            demandeTemporisation(20);
            break;

        case Temporisation:
            rafraichisFenetre();
            break;

        case Affichage:

            // On part d'un fond d'ecran blanc
            effaceFenetre(0, 0, 0);

            for (int i=0;i<nbEtoiles-1;i+=2) {
                cercle(etoiles[i], etoiles[i+1], largeurFenetre()/1024);
            }

            switch (state) {
                case MenuPrincipal:
                    printf("Bonjour je suis le menu principal\n");
                    break;
                case Simulation:
                    //printf("Bonjour je suis l'affichage de la simulation\n");

                    if (deltaT >= deltaTcheck) {
                        ptElementAstreCourant = ptElementAstreInitial;
                        while( ptElementAstreCourant != NULL )
                        {
                            Astre* ptAstre = ptElementAstreCourant -> ptAstre;
                            if( ptAstre != NULL )
                            {
                                UpdateObjet(ptAstre, RechercheParNom(ptElementAstreInitial, ptAstre->nomGravitation));
                            }

                            ptElementAstreCourant = ptElementAstreCourant -> ptElementAstreSuivant;
                        }

                        deltaT = 0;
                    }

                    ptElementAstreCourant = ptElementAstreInitial;
                    while( ptElementAstreCourant != NULL )
                    {
                        Astre* ptAstre = ptElementAstreCourant -> ptAstre;
                        if( ptAstre != NULL )
                        {
                            switch(ptAstre->couleur) {
                                case Cyan:
                                    couleurCourante(0, 206, 209);
                                    break;
                                case Jaune:
                                    couleurCourante(255, 255, 0);
                                    break;
                                case GrisFonce:
                                    couleurCourante(69, 69, 69);
                                    break;
                                default:
                                    couleurCourante(0,0,0);
                                    break;
                            }



                            if (ptAstre->rayon*echellePlanete < largeurFenetre()/256) {
                                cercle(ptAstre->x*echelleDistances + largeurFenetre()/2 + xCentre, ptAstre->y*echelleDistances + hauteurFenetre()/2 + yCentre, largeurFenetre()/256);
                            } else {
                                cercle(ptAstre->x*echelleDistances + largeurFenetre()/2 + xCentre, ptAstre->y*echelleDistances + hauteurFenetre()/2 + yCentre, ptAstre->rayon*echellePlanete);
                            }

                            float tailleChaineAstre = tailleChaine(ptAstre->nom, 12);
                            afficheChaine(ptAstre->nom, 12, ptAstre->x*echelleDistances + largeurFenetre()/2 - tailleChaineAstre/2 + xCentre, ptAstre->y*echelleDistances + hauteurFenetre()/2 + ptAstre->rayon*echellePlanete + hauteurFenetre()/128 + yCentre);
                        }
                        ptElementAstreCourant = ptElementAstreCourant -> ptElementAstreSuivant;
                    }

                    deltaT++;

                    break;
                case MenuSauvegardes:
                    printf("Bonjour j'aimerai afficher les sauvegardes\n");
                    break;
                default:
                    printf("Il se passe quoi là ?????\n");
                    break;
            }
            break;

        case Clavier:
            printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

            switch (caractereClavier()) {
                case 'Z':
                case 'z':
                    yCentre -= 100;
                    updateEtoiles();
                    break;
                case 'Q':
                case 'q':
                    xCentre += 100;
                    updateEtoiles();
                    break;
                case 'S':
                case 's':
                    yCentre += 100;
                    updateEtoiles();
                    break;
                case 'D':
                case 'd':
                    xCentre -= 100;
                    updateEtoiles();
                    break;
            }
            break;

        case ClavierSpecial:
            printf("ASCII %d\n", toucheClavier());

            switch (toucheClavier()) {
                case ToucheF1:
                    // Configure le systeme pour generer un message Temporisation
                    // toutes les 20 millisecondes (rapide)
                    demandeTemporisation(20);
                    break;
                case ToucheF2:
                    // Configure le systeme pour generer un message Temporisation
                    // toutes les 100 millisecondes (lent)
                    demandeTemporisation(100);
                    break;
                case ToucheF3:
                    // Configure le systeme pour ne plus generer de message Temporisation
                    demandeTemporisation(-1);
                    break;
                case ToucheF4:
                    termineBoucleEvenements();
                    break;
                case ToucheF11:
                    pleinEcran = !pleinEcran; // Changement de mode plein ecran
                    if (pleinEcran)
                        modePleinEcran();
                    else
                        redimensionneFenetre(LargeurFenetre, HauteurFenetre);
                    break;
                case ToucheFlecheGauche:
                    deltaTcheck++;
                    break;
                case ToucheFlecheDroite:
                    if (deltaTcheck > 1) {
                        deltaTcheck--;
                    }
                    break;
                case ToucheFlecheHaut:
                    echellePlanete *= 2;
                    echelleDistances *= 2;
                    break;
                case ToucheFlecheBas:
                    echellePlanete /= 2;
                    echelleDistances /= 2;
                    break;
            }
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye)
            {
                printf("Bouton gauche appuye en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
                float xAppuye = abscisseSouris() - largeurFenetre()/2 - xCentre;
                float yAppuye = ordonneeSouris() - hauteurFenetre()/2 - yCentre;

                printf("Coordonnées dans le repère cartésien : (%f, %f)", xAppuye, yAppuye);


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

        case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
            // Donc le systeme nous en informe
            printf("Largeur : %d\t", largeurFenetre());
            printf("Hauteur : %d\n", hauteurFenetre());
            updateEtoiles();
            break;
    }
}
