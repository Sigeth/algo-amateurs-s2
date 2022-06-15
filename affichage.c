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
float echellePlanete = 1.0f/100.0f;
float echelleDistances = 1.0f/100000.0f;
static ElementAstre* ptElementAstreInitial;
static ElementAstre* ptElementAstreCourant;
static int deltaT = 0;
static int deltaTcheck = 1;
static float xCentre = 0.0f;
static float yCentre = 0.0f;
static Astre* astreFocused = NULL;
static bool paused = false;
static int* etoiles;
static int nbEtoiles;

void cercle(float centreX, float centreY, float rayon, int Pas)
{
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
        etoiles[i+1] = rand()%hauteurFenetre();
    }
}

void affichePlanetes(bool isInMenu) {
    ptElementAstreCourant = ptElementAstreInitial;
    while( ptElementAstreCourant != NULL )
    {
        Astre* ptAstre = ptElementAstreCourant -> ptAstre;
        if( ptAstre != NULL )
        {
            if (!isInMenu) {
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
                    case GrisClair:
                        couleurCourante(169, 169, 169);
                        break;
                    case Orange:
                        couleurCourante(255, 140, 0);
                        break;
                    case Rouge:
                        couleurCourante(255, 0, 0);
                        break;
                    case Creme:
                        couleurCourante(222, 184, 135);
                        break;
                    case Cafe:
                        couleurCourante(139, 69, 19);
                        break;
                    case BleuCiel:
                        couleurCourante(173, 216, 230);
                        break;
                    case Bleu:
                        couleurCourante(0, 0, 255);
                        break;
                    default:
                        couleurCourante(0,0,0);
                        break;
                }
            } else {
                switch(ptAstre->couleur) {
                    case Cyan:
                        couleurCourante(0, 106, 109);
                        break;
                    case Jaune:
                        couleurCourante(155, 155, 0);
                        break;
                    case GrisFonce:
                        couleurCourante(5, 5, 5);
                        break;
                    case GrisClair:
                        couleurCourante(69, 69, 69);
                        break;
                    case Orange:
                        couleurCourante(155, 40, 0);
                        break;
                    case Rouge:
                        couleurCourante(155, 0, 0);
                        break;
                    case Creme:
                        couleurCourante(122, 84, 35);
                        break;
                    case Cafe:
                        couleurCourante(39, 5, 0);
                        break;
                    case BleuCiel:
                        couleurCourante(73, 116, 130);
                        break;
                    case Bleu:
                        couleurCourante(0, 0, 155);
                        break;
                    default:
                        couleurCourante(0,0,0);
                        break;
                }
            }


            if (!strcmp(ptAstre->nom, "Le Soleil")) {
                echellePlanete /= 100.f;
            }

            if (ptAstre->rayon*echellePlanete < largeurFenetre()/512) {
                cercle(ptAstre->x*echelleDistances + largeurFenetre()/2 + xCentre, ptAstre->y*echelleDistances + hauteurFenetre()/2 + yCentre, largeurFenetre()/512, 50);
            } else {
                cercle(ptAstre->x*echelleDistances + largeurFenetre()/2 + xCentre, ptAstre->y*echelleDistances + hauteurFenetre()/2 + yCentre, ptAstre->rayon*echellePlanete, 50);
            }

            float tailleChaineAstre = tailleChaine(ptAstre->nom, 20);
            afficheChaine(ptAstre->nom, 20, ptAstre->x*echelleDistances + largeurFenetre()/2 - tailleChaineAstre/2 + xCentre, ptAstre->y*echelleDistances + hauteurFenetre()/2 + ptAstre->rayon*echellePlanete + hauteurFenetre()/128 + yCentre);

            if (!strcmp(ptAstre->nom, "Le Soleil")) {
                echellePlanete *= 100.f;
            }
        }
        ptElementAstreCourant = ptElementAstreCourant -> ptElementAstreSuivant;
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
            //epaisseurDeTrait(3);

            ptElementAstreInitial = InitElementAstre();
            ptElementAstreCourant = ptElementAstreInitial;
            srand(time(NULL));
            nbEtoiles = 500 + rand()%4500;
            etoiles = malloc(sizeof(int) * nbEtoiles);

            updateEtoiles();

            astreFocused = RechercheParNom(ptElementAstreInitial, "La Terre");

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
                cercle(etoiles[i], etoiles[i+1], largeurFenetre()/1024, 3);
            }

            switch (state) {
                case MenuPrincipal:
                    printf("Bonjour je suis le menu principal\n");
                    break;
                case Simulation:
                    //printf("Bonjour je suis l'affichage de la simulation\n");

                    if (deltaT >= deltaTcheck && !paused) {
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

                    affichePlanetes(false);

                    if (astreFocused) {
                        xCentre = 0 - astreFocused->x*echelleDistances;
                        yCentre = 0 - astreFocused->y*echelleDistances;
                    }

                    deltaT++;

                    couleurCourante(200,200,200);

                    break;
                case MenuSauvegardes:
                    couleurCourante(255,255,255);
                    float tailleChaineTitre = tailleChaine("Menu des Sauvegardes", 32);
                    afficheChaine("Menu des Sauvegardes", 32, largeurFenetre()/2 - tailleChaineTitre/2, hauteurFenetre() - hauteurFenetre()/12);

                    rectangle(largeurFenetre()/8 - largeurFenetre()/512, hauteurFenetre()/6 - hauteurFenetre()/512, largeurFenetre() - largeurFenetre()/8 + largeurFenetre()/512, hauteurFenetre() - hauteurFenetre()/6  + hauteurFenetre()/512);
                    couleurCourante(0,0,0);
                    rectangle(largeurFenetre()/8, hauteurFenetre()/6, largeurFenetre() - largeurFenetre()/8, hauteurFenetre() - hauteurFenetre()/6);

                    float tailleChaineSauvegarde = tailleChaine("Toutes les infos sur la sauvegarde ici", 20);

                    couleurCourante(255,255,255);
                    afficheChaine("Toutes les infos sur la sauvegarde ici", 20, largeurFenetre()/2 - tailleChaineSauvegarde/2, hauteurFenetre()/2);

                    triangle(largeurFenetre()/32, hauteurFenetre()/2 + hauteurFenetre()/32, largeurFenetre()/128, hauteurFenetre()/2, largeurFenetre()/32, hauteurFenetre()/2 - hauteurFenetre()/32);
                    triangle(largeurFenetre() - largeurFenetre()/32, hauteurFenetre()/2 + hauteurFenetre()/32, largeurFenetre() - largeurFenetre()/128, hauteurFenetre()/2,  largeurFenetre() - largeurFenetre()/32, hauteurFenetre()/2 - hauteurFenetre()/32);

                    rectangle(largeurFenetre()/4 - largeurFenetre()/512, hauteurFenetre()/8 + hauteurFenetre()/512, largeurFenetre() - largeurFenetre()/4 + largeurFenetre()/512, hauteurFenetre()/32 - hauteurFenetre()/512);
                    couleurCourante(0,0,0);
                    rectangle(largeurFenetre()/4, hauteurFenetre()/8, largeurFenetre() - largeurFenetre()/4, hauteurFenetre()/32);

                    couleurCourante(255,255,255);
                    float tailleChaineCharger = tailleChaine("Charger la sauvegarde", 28);
                    afficheChaine("Charger la sauvegarde", 28, largeurFenetre()/2 - tailleChaineCharger/2, hauteurFenetre()/16);


                    couleurCourante(200,200,200);
                    break;
                case MenuSimu:
                    affichePlanetes(true);
                    couleurCourante(100,100,100);
                    break;
                default:
                    printf("Il se passe quoi là ?????\n");
                    break;
            }
            break;

        case Clavier:
            printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

            switch(state) {
                case Simulation:
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
                        case ' ':
                            if (paused) {
                                paused = false;
                            } else {
                                paused = true;
                            }
                            break;
                        case '0':
                            xCentre = 0;
                            yCentre = 0;
                            updateEtoiles();
                            break;
                        case 27:
                            state = MenuSimu;
                            break;
                    }
                    break;
                case MenuSimu:
                    switch (caractereClavier()) {
                        case 27:
                            state = Simulation;
                            break;
                        case 'S':
                        case 's':
                            state = MenuSauvegardes;
                            break;
                    }
                    break;
                case MenuSauvegardes:
                    switch (caractereClavier()) {
                        case 'm':
                            state = MenuSimu;
                            break;
                    }
                    break;
                default:
                    printf("chaud là il se passe quoi\n");
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
                    if (state == Simulation) {
                        deltaTcheck++;
                    }
                    break;
                case ToucheFlecheDroite:
                    if (state == Simulation) {
                        if (deltaTcheck > 1) {
                            deltaTcheck--;
                        }
                    }
                    break;
                case ToucheFlecheHaut:
                    if (state == Simulation) {
                        echellePlanete *= 2;
                        echelleDistances *= 2;
                    }
                    break;
                case ToucheFlecheBas:
                    if (state == Simulation) {
                        echellePlanete /= 2;
                        echelleDistances /= 2;
                    }
                    break;
            }
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye) {
                switch (state) {

                    case Simulation:
                        if (astreFocused) {
                            astreFocused = NULL;
                        } else {
                            float xAppuye = abscisseSouris() - largeurFenetre() / 2 - xCentre;
                            float yAppuye = ordonneeSouris() - hauteurFenetre() / 2 - yCentre;

                            printf("Coordonnées dans le repère cartésien : (%f, %f)\n", xAppuye, yAppuye);

                            ptElementAstreCourant = ptElementAstreInitial;
                            while (ptElementAstreCourant != NULL) {
                                Astre *ptAstre = ptElementAstreCourant->ptAstre;
                                if (ptAstre != NULL) {
                                    float rayon = ptAstre->rayon;

                                    if (!strcmp(ptAstre->nom, "Le Soleil")) {
                                        echellePlanete /= 100.f;
                                    }

                                    if (ptAstre->rayon * echellePlanete < largeurFenetre() / 512) {
                                        rayon = largeurFenetre() / 512;
                                    }

                                    printf("xMoins : %f\nxPlus : %f\n", xAppuye / echelleDistances - rayon / echellePlanete,
                                           xAppuye / echelleDistances + rayon / echellePlanete);

                                    if (xAppuye / echelleDistances - rayon / echellePlanete <= ptAstre->x
                                        && xAppuye / echelleDistances + rayon / echellePlanete >= ptAstre->x
                                        && yAppuye / echelleDistances - rayon / echellePlanete <= ptAstre->y
                                        && yAppuye / echelleDistances + rayon / echellePlanete >= ptAstre->y) {
                                        astreFocused = ptAstre;
                                    }

                                    if (!strcmp(ptAstre->nom, "Le Soleil")) {
                                        echellePlanete *= 100.f;
                                    }

                                }

                                ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
                            }

                            if (astreFocused) {
                                printf("Astre trouvé : %s\n", astreFocused->nom);
                            }
                        }
                        break;
                    case MenuSimu:
                        break;
                    case MenuSauvegardes:
                        if (ordonneeSouris() <= hauteurFenetre()/2 + hauteurFenetre()/32 && ordonneeSouris() >= hauteurFenetre()/2 - hauteurFenetre()/32) {
                            if (abscisseSouris() <= largeurFenetre()/32 && abscisseSouris() >= largeurFenetre()/128) {
                                printf("Clic sur la flèche de gauche\n");
                            } else if (abscisseSouris() >=  largeurFenetre() - largeurFenetre()/32 && abscisseSouris() <=  largeurFenetre() - largeurFenetre()/128) {
                                printf("Clic sur la flèche de droite\n");
                            }
                        } else if (abscisseSouris() >= largeurFenetre()/4
                            && abscisseSouris() <= largeurFenetre() - largeurFenetre()/4
                            && ordonneeSouris() >= hauteurFenetre()/32
                            && ordonneeSouris() <= hauteurFenetre()/8)
                        {
                            printf("Clic sur le bouton charger la sauvegarde\n");
                        }
                        break;
                    case MenuPrincipal:
                        break;
                    default:
                        break;
                }
            }
            else if (etatBoutonSouris() == GaucheRelache)
            {
                //printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
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
