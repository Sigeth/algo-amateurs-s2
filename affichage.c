#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "affichage.h"

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
float echelle = 1.0f/10000.0f;
static ElementAstre* ptElementAstreInitial;
static ElementAstre* ptElementAstreCourant;
static long int deltaT = 0;

void cercle(float centreX, float centreY, float rayon)
{
    const int Pas = 20; // Nombre de secteurs pour tracer le cercle
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
            effaceFenetre(255, 255, 255);

            switch (state) {
                case MenuPrincipal:
                    printf("Bonjour je suis le menu principal\n");
                    break;
                case Simulation:
                    //printf("Bonjour je suis l'affichage de la simulation\n");

                    if (deltaT > 60) {
                        ptElementAstreCourant = ptElementAstreInitial;
                        while( ptElementAstreCourant != NULL )
                        {
                            Astre* ptAstre = ptElementAstreCourant -> ptAstre;
                            if( ptAstre != NULL )
                            {
                                UpdateObjet(ptAstre);
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



                            if (ptAstre->rayon*echelle < largeurFenetre()/256) {
                                cercle(ptAstre->x*echelle + largeurFenetre()/2, ptAstre->y*echelle + hauteurFenetre()/2, largeurFenetre()/256);
                            } else {
                                cercle(ptAstre->x*echelle + largeurFenetre()/2, ptAstre->y*echelle + hauteurFenetre()/2, ptAstre->rayon*echelle);
                            }

                            float tailleChaineAstre = tailleChaine(ptAstre->nom, 12);
                            afficheChaine(ptAstre->nom, 12, ptAstre->x*echelle + largeurFenetre()/2 - tailleChaineAstre/2, ptAstre->y*echelle + hauteurFenetre()/2 + ptAstre->rayon*echelle + hauteurFenetre()/128);
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
                case 'A':
                case 'a':
                    printf("omg j'appuie sur A !!!!!");
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
            }
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

        case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
            // Donc le systeme nous en informe
            printf("Largeur : %d\t", largeurFenetre());
            printf("Hauteur : %d\n", hauteurFenetre());
            break;
    }
}