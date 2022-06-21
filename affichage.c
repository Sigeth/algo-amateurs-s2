#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "affichage.h"
#include "menu.h"
#include "sauvegarde.h"
#include <stdbool.h>
#include <time.h>

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1280
#define HauteurFenetre 720

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);

void afficheSimu(int argc, char **argv) {
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("Simulation Spatiale - Les Amateurs", LargeurFenetre, HauteurFenetre);

    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    lanceBoucleEvenements();
}


static StateAffichage state = MenuPrincipal;
float echellePlanete = 1.0f / 100.0f;
float echelleDistances = 1.0f / 100000.0f;
static ElementAstre *ptElementAstreInitial;
static ElementAstre *ptElementAstreCourant;
static int deltaTcheck = 10000;
static float xCentre = 0.0f;
static float yCentre = 0.0f;
static Astre *astreFocused = NULL;
static bool paused = false;
static int *etoiles;
static int nbEtoiles;
static time_t t;
static struct tm tm;
static int idSave;
static char **saves;

/**
 * Permet de dessiner un cercle
 *
 * @param centreX - Le centre du cercle en x
 * @param centreY - Le centre du cercle en y
 * @param rayon - Le rayon souhaité du cercle
 * @param Pas - Le nom d'itération qui constituera le cercle. Plus le pas est élevé, plus le cercle sera précis mais plus il demandera des ressources
 */
void cercle(float centreX, float centreY, float rayon, int Pas) {
    const double PasAngulaire = 2. * M_PI / Pas;
    int index;

    for (index = 0; index < Pas; ++index) // Pour chaque secteur
    {
        const double angle = 2. * M_PI * index / Pas; // on calcule l'angle de depart du secteur
        triangle(centreX, centreY,
                 centreX + rayon * cos(angle), centreY + rayon * sin(angle),
                 centreX + rayon * cos(angle + PasAngulaire), centreY + rayon * sin(angle + PasAngulaire));
        // On trace le secteur a l'aide d'un triangle => approximation d'un cercle
    }

}

/**
 * Permet d'initialiser toutes les valeurs pour une simulation
 */
void initSimu() {
    state = Simulation;
    echellePlanete = 1.0f / 100.0f;
    echelleDistances = 1.0f / 100000.0f;
    deltaTcheck = 10000;
    xCentre = 0.0f;
    yCentre = 0.0f;
    astreFocused = NULL;
    paused = false;
}

/**
 * Permet de redéfinir la position des étoiles et donner une impression de mouvement à l'utilisateur
 */
void updateEtoiles() {
    for (int i = 0; i < nbEtoiles - 1; i += 2) {
        etoiles[i] = rand() % largeurFenetre();
        etoiles[i + 1] = rand() % hauteurFenetre();
    }
}

/**
 * Permet d'afficher les planètes, tout en grisant les planètes si nous sommes dans le state MenuSimu
 */
void affichePlanetes(bool isInMenu) {
    ptElementAstreCourant = ptElementAstreInitial;
    while (ptElementAstreCourant != NULL) {
        Astre *ptAstre = ptElementAstreCourant->ptAstre;
        if (ptAstre != NULL) {
            if (!isInMenu) {
                switch (ptAstre->couleur) {
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
                        couleurCourante(0, 0, 0);
                        break;
                }
            } else {
                switch (ptAstre->couleur) {
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
                        couleurCourante(0, 0, 0);
                        break;
                }
            }


            if (!strcmp(ptAstre->nom, "Le Soleil")) {
                echellePlanete /= 100.f;
            }

            if (ptAstre->rayon * echellePlanete < largeurFenetre() / 512) {
                cercle(ptAstre->x * echelleDistances + largeurFenetre() / 2 + xCentre,
                       ptAstre->y * echelleDistances + hauteurFenetre() / 2 + yCentre, largeurFenetre() / 512, 50);
            } else {
                cercle(ptAstre->x * echelleDistances + largeurFenetre() / 2 + xCentre,
                       ptAstre->y * echelleDistances + hauteurFenetre() / 2 + yCentre, ptAstre->rayon * echellePlanete,
                       50);
            }

            float tailleChaineAstre = tailleChaine(ptAstre->nom, 20);
            afficheChaine(ptAstre->nom, 20,
                          ptAstre->x * echelleDistances + largeurFenetre() / 2 - tailleChaineAstre / 2 + xCentre,
                          ptAstre->y * echelleDistances + hauteurFenetre() / 2 + ptAstre->rayon * echellePlanete +
                          hauteurFenetre() / 128 + yCentre);

            if (!strcmp(ptAstre->nom, "Le Soleil")) {
                echellePlanete *= 100.f;
            }
        }
        ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
    }
}

void afficheInfoPlanete() {

    couleurCourante(255, 255, 255);
    rectangle(largeurFenetre() - largeurFenetre() / 4 - largeurFenetre() / 512,
              hauteurFenetre() - hauteurFenetre() / 7 + hauteurFenetre() / 512,
              largeurFenetre() - largeurFenetre() / 256 + largeurFenetre() / 512,
              hauteurFenetre() / 7 - hauteurFenetre() / 512);
    couleurCourante(0, 0, 0);
    rectangle(largeurFenetre() - largeurFenetre() / 4, hauteurFenetre() - hauteurFenetre() / 7,
              largeurFenetre() - largeurFenetre() / 256, hauteurFenetre() / 7);

    switch (astreFocused->couleur) {
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
            couleurCourante(0, 0, 0);
            break;
    }

    int lengthNom = snprintf(NULL, 0, "%s", astreFocused->nom);
    char *chaineNom = malloc(sizeof(char) * lengthNom + 1);
    snprintf(chaineNom, lengthNom + 1, "%s", astreFocused->nom);
    float tailleNom = tailleChaine(chaineNom, 32);
    afficheChaine(chaineNom, 32, largeurFenetre() - largeurFenetre() / 8 - tailleNom / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 16);

    couleurCourante(255, 255, 255);

    float tailleIntroType = tailleChaine("Type : ", 20);
    afficheChaine("Type : ", 20, largeurFenetre() - largeurFenetre() / 4 + largeurFenetre() / 16 - tailleIntroType / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 8);
    int lengthType = snprintf(NULL, 0, "%s", astreFocused->type);
    char *chaineType = malloc(sizeof(char) * lengthType + 1);
    snprintf(chaineType, lengthType + 1, "%s", astreFocused->type);
    float tailleType = tailleChaine(chaineType, 20);
    afficheChaine(chaineType, 20, largeurFenetre() - largeurFenetre() / 4 + largeurFenetre() / 6 - tailleType / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 8);

    float tailleIntroRayon = tailleChaine("Rayon : ", 20);
    afficheChaine("Rayon : ", 20,
                  largeurFenetre() - largeurFenetre() / 4 + largeurFenetre() / 16 - tailleIntroRayon / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 6);
    int lengthRayon = snprintf(NULL, 0, "%fkm", astreFocused->rayon);
    char *chaineRayon = malloc(sizeof(char) * lengthRayon + 1);
    snprintf(chaineRayon, lengthRayon + 1, "%fkm", astreFocused->rayon);
    float tailleRayon = tailleChaine(chaineRayon, 20);
    afficheChaine(chaineRayon, 20, largeurFenetre() - largeurFenetre() / 4 + largeurFenetre() / 6 - tailleRayon / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 6);

    float tailleIntroMasse = tailleChaine("Masse : ", 20);
    afficheChaine("Masse : ", 20, largeurFenetre() - largeurFenetre() / 8 - tailleIntroMasse / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 4.7);
    int lengthMasse = snprintf(NULL, 0, "%ft", astreFocused->masse / 1000000.f);
    char *chaineMasse = malloc(sizeof(char) * lengthMasse + 1);
    snprintf(chaineMasse, lengthMasse + 1, "%ft", astreFocused->masse / 1000000.f);
    float tailleMasse = tailleChaine(chaineMasse, 20);
    afficheChaine(chaineMasse, 20, largeurFenetre() - largeurFenetre() / 8 - tailleMasse / 2,
                  hauteurFenetre() - hauteurFenetre() / 7 - hauteurFenetre() / 4);


    Astre *astreGravitation = RechercheParNom(ptElementAstreInitial, astreFocused->nomGravitation);

    if (astreFocused->distanceCentreGravitation != 0) {
        float tailleIntroNomGravitation = tailleChaine("Je gravite autour de", 20);
        afficheChaine("Je gravite autour de", 20,
                      largeurFenetre() - largeurFenetre() / 8 - tailleIntroNomGravitation / 2, hauteurFenetre() / 2);
        int lengthNomGravitation = snprintf(NULL, 0, "%s", astreGravitation->nom);
        char *chaineNomGravitation = malloc(sizeof(char) * lengthNomGravitation + 1);
        snprintf(chaineNomGravitation, lengthNomGravitation + 1, "%s", astreGravitation->nom);
        float tailleNomGravitation = tailleChaine(chaineNomGravitation, 20);
        afficheChaine(chaineNomGravitation, 20, largeurFenetre() - largeurFenetre() / 8 - tailleNomGravitation / 2,
                      hauteurFenetre() / 2 - hauteurFenetre() / 12);

        float tailleIntroDistanceGravitation = tailleChaine("avec une distance de", 20);
        afficheChaine("avec une distance de", 20,
                      largeurFenetre() - largeurFenetre() / 8 - tailleIntroDistanceGravitation / 2,
                      hauteurFenetre() / 2 - hauteurFenetre() / 4);
        int lengthDistanceGravitation = snprintf(NULL, 0, "%fkm", astreFocused->distanceCentreGravitation / 1000.f);
        char *chaineDistanceGravitation = malloc(sizeof(char) * lengthDistanceGravitation + 1);
        snprintf(chaineDistanceGravitation, lengthDistanceGravitation + 1, "%fkm",
                 astreFocused->distanceCentreGravitation / 1000.f);
        float tailleDistanceGravitation = tailleChaine(chaineDistanceGravitation, 20);
        afficheChaine(chaineDistanceGravitation, 20,
                      largeurFenetre() - largeurFenetre() / 8 - tailleDistanceGravitation / 2,
                      hauteurFenetre() / 2 - hauteurFenetre() / 4 - hauteurFenetre() / 12);

        free(chaineNomGravitation);
        free(chaineDistanceGravitation);
    }

    free(chaineNom);
    free(chaineType);
    free(chaineRayon);
    free(chaineMasse);
}

/**
 * Gère le clic sur la flèche gauche en state MenuSauvegardes
 */
void clicFlecheGaucheSauvegarde() {
    printf("Clic sur la flèche gauche\n");
    if (idSave > 0) {
        idSave--;
    }
}

/**
 * Gère le clic sur la flèche droite en state MenuSauvegardes
 */
void clicFlecheDroiteSauvegarde() {
    if (idSave < nbsave() - 1) {
        idSave++;
    }
}

/**
 * Gère le clic sur le bouton "Charger la sauvegarde" en state MenuSauvegardes
 */
void clicChargerSauvegarde() {
    ptElementAstreInitial = InitElementAstre(saves[idSave], &t);
    initSimu();
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement) {
    static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas


    switch (evenement) {
        case Initialisation:
            epaisseurDeTrait(3);
            struct tm dateDuDeces = {0, 0, 0, 21, 5, 122};
            t = mktime(&dateDuDeces);
            epaisseurDeTrait(1);
            ptElementAstreInitial = InitElementAstre(NULL, &t);
            ptElementAstreCourant = ptElementAstreInitial;
            srand(time(NULL));
            nbEtoiles = 500 + rand() % 4500;
            etoiles = malloc(sizeof(int) * nbEtoiles);
            saves = malloc(sizeof(char *) * 50);
            idSave = 0;

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


            for (int i = 0; i < nbEtoiles - 1; i += 2) {
                cercle(etoiles[i], etoiles[i + 1], largeurFenetre() / 1024, 3);
            }

            switch (state) {
                case MenuPrincipal:
                    couleurCourante(255, 255, 255);
                    epaisseurDeTrait(5);

                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2.31,
                              largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.76,
                              largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.58);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.43,
                              largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.30);
                    couleurCourante(0, 0, 0);

                    afficheChaine("Lancer Simulation", 30,
                                  largeurFenetre() / 2 - tailleChaine("Lancer Simulation", 30) / 2,
                                  hauteurFenetre() - hauteurFenetre() / 2.1);
                    afficheChaine("Charger", 30, largeurFenetre() / 2 - tailleChaine("Charger", 30) / 2,
                                  hauteurFenetre() - hauteurFenetre() / 1.64);
                    afficheChaine("Quitter", 30, largeurFenetre() / 2 - tailleChaine("Quitter", 30) / 2,
                                  hauteurFenetre() - hauteurFenetre() / 1.34);

                    couleurCourante(200, 200, 200);
                    epaisseurDeTrait(1);
                    break;
                case Simulation:
                    //printf("Bonjour je suis l'affichage de la simulation\n");

                    if (!paused) {
                        ptElementAstreCourant = ptElementAstreInitial;
                        while (ptElementAstreCourant != NULL) {
                            Astre *ptAstre = ptElementAstreCourant->ptAstre;
                            if (ptAstre != NULL) {
                                UpdateObjetReal(ptAstre,
                                                RechercheParNom(ptElementAstreInitial, ptAstre->nomGravitation),
                                                deltaTcheck);
                            }

                            ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
                        }

                        t += deltaTcheck;
                        tm = *localtime(&t);
                    }

                    affichePlanetes(false);

                    if (astreFocused) {
                        xCentre = 0 - astreFocused->x * echelleDistances;
                        yCentre = 0 - astreFocused->y * echelleDistances;
                        afficheInfoPlanete();
                    }

                    couleurCourante(255, 255, 255);
                    rectangle(largeurFenetre() - largeurFenetre() / 4 - largeurFenetre() / 512,
                              hauteurFenetre() / 8 + hauteurFenetre() / 512,
                              largeurFenetre() - largeurFenetre() / 256 + largeurFenetre() / 512,
                              hauteurFenetre() / 64 - hauteurFenetre() / 512);
                    couleurCourante(0, 0, 0);
                    rectangle(largeurFenetre() - largeurFenetre() / 4, hauteurFenetre() / 8,
                              largeurFenetre() - largeurFenetre() / 256, hauteurFenetre() / 64);

                    couleurCourante(255, 255, 255);

                    int lengthEchelleT = snprintf(NULL, 0, "EcheLLe de temps : %ds / actualisation", deltaTcheck);
                    char *chaineEchelleT = malloc(sizeof(char) * lengthEchelleT + 1);
                    snprintf(chaineEchelleT, lengthEchelleT + 1, "EcheLLe de temps : %ds / actualisation", deltaTcheck);
                    float tailleEchelleT = tailleChaine(chaineEchelleT, 12);
                    afficheChaine(chaineEchelleT, 12, largeurFenetre() - largeurFenetre() / 8 - tailleEchelleT / 2,
                                  hauteurFenetre() / 8 - hauteurFenetre() / 32);

                    int lengthEchelleDistances = snprintf(NULL, 0, "EcheLLe de distances : 1/%fm",
                                                          1 / echelleDistances);
                    char *chaineEchelleDistances = malloc(sizeof(char) * lengthEchelleDistances + 1);
                    snprintf(chaineEchelleDistances, lengthEchelleDistances + 1, "EcheLLe de distances : 1/%fm",
                             1 / echelleDistances);
                    float tailleEchelleDistances = tailleChaine(chaineEchelleDistances, 12);

                    afficheChaine(chaineEchelleDistances, 12,
                                  largeurFenetre() - largeurFenetre() / 8 - tailleEchelleDistances / 2,
                                  hauteurFenetre() / 8 - hauteurFenetre() / 16);

                    int lengthEchelleRayons = snprintf(NULL, 0, "EcheLLe de rayon : 1/%fm",
                                                       1 / (echellePlanete / 100.f));
                    char *chaineEchelleRayons = malloc(sizeof(char) * lengthEchelleRayons + 1);
                    snprintf(chaineEchelleRayons, lengthEchelleRayons + 1, "EcheLLe de rayon : 1/%fm",
                             1 / (echellePlanete / 100.f));
                    float tailleEchelleRayons = tailleChaine(chaineEchelleRayons, 12);

                    afficheChaine(chaineEchelleRayons, 12,
                                  largeurFenetre() - largeurFenetre() / 8 - tailleEchelleRayons / 2,
                                  hauteurFenetre() / 8 - hauteurFenetre() / 10);


                    int lengthDate = snprintf(NULL, 0, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                    char *chaineDate = malloc(sizeof(char) * lengthDate + 1);
                    snprintf(chaineDate, lengthDate + 1, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
                    float tailleDate = tailleChaine(chaineDate, 24);
                    afficheChaine(chaineDate, 24, largeurFenetre() / 2 - tailleDate / 2,
                                  hauteurFenetre() - hauteurFenetre() / 16);


                    free(chaineEchelleT);
                    free(chaineEchelleDistances);
                    free(chaineEchelleRayons);
                    free(chaineDate);
                    couleurCourante(200, 200, 200);

                    break;
                case MenuSauvegardes:
                    couleurCourante(255, 255, 255);
                    epaisseurDeTrait(5);
                    ligne(largeurFenetre() / 64, hauteurFenetre() - hauteurFenetre() / 64, largeurFenetre() / 16,
                          hauteurFenetre() - hauteurFenetre() / 16);
                    ligne(largeurFenetre() / 64, hauteurFenetre() - hauteurFenetre() / 16, largeurFenetre() / 16,
                          hauteurFenetre() - hauteurFenetre() / 64);
                    epaisseurDeTrait(1);

                    float tailleChaineTitre = tailleChaine("Menu des Sauvegardes", 32);
                    afficheChaine("Menu des Sauvegardes", 32, largeurFenetre() / 2 - tailleChaineTitre / 2,
                                  hauteurFenetre() - hauteurFenetre() / 12);

                    listesauvegarde(saves);

                    if (nbsave() == 0) {
                        float tailleChaineRien = tailleChaine("Aucune sauvegarde trouvee...", 64);
                        afficheChaine("Aucune sauvegarde trouvee", 64, largeurFenetre() / 2 - tailleChaineRien / 2,
                                      hauteurFenetre() / 2);
                    } else {
                        rectangle(largeurFenetre() / 8 - largeurFenetre() / 512,
                                  hauteurFenetre() / 6 - hauteurFenetre() / 512,
                                  largeurFenetre() - largeurFenetre() / 8 + largeurFenetre() / 512,
                                  hauteurFenetre() - hauteurFenetre() / 6 + hauteurFenetre() / 512);
                        couleurCourante(0, 0, 0);
                        rectangle(largeurFenetre() / 8, hauteurFenetre() / 6, largeurFenetre() - largeurFenetre() / 8,
                                  hauteurFenetre() - hauteurFenetre() / 6);

                        couleurCourante(255, 255, 255);
                        int lengthNomSave = snprintf(NULL, 0, "Sauvegarde %s", saves[idSave]);
                        char *chaineNomSave = malloc(sizeof(char) * lengthNomSave + 1);
                        snprintf(chaineNomSave, lengthNomSave + 1, "Sauvegarde %s", saves[idSave]);
                        float tailleChaineSave = tailleChaine(chaineNomSave, 32);
                        afficheChaine(chaineNomSave, 32,
                                      largeurFenetre() / 2 - tailleChaineSave / 2,
                                      hauteurFenetre() - hauteurFenetre() / 4);

                        float tailleChaineTitreDate = tailleChaine("Date de la sauvegarde :", 32);
                        afficheChaine("Date de la sauvegarde :", 32, largeurFenetre() / 2 - tailleChaineTitreDate / 2,
                                      hauteurFenetre() / 2);

                        time_t tpsSave = tps(saves[idSave]);
                        tm = *localtime(&tpsSave);

                        int lengthDateSave = snprintf(NULL, 0, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
                                                      tm.tm_year + 1900);
                        char *chaineDateSave = malloc(sizeof(char) * lengthDateSave + 1);
                        snprintf(chaineDateSave, lengthDateSave + 1, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
                                 tm.tm_year + 1900);
                        float tailleDateSave = tailleChaine(chaineDateSave, 32);
                        afficheChaine(chaineDateSave, 32, largeurFenetre() / 2 - tailleDateSave / 2,
                                      hauteurFenetre() / 4);

                        if (idSave > 0) {
                            triangle(largeurFenetre() / 32, hauteurFenetre() / 2 + hauteurFenetre() / 32,
                                     largeurFenetre() / 128, hauteurFenetre() / 2, largeurFenetre() / 32,
                                     hauteurFenetre() / 2 - hauteurFenetre() / 32);
                        }
                        if (idSave < nbsave() - 1) {
                            triangle(largeurFenetre() - largeurFenetre() / 32,
                                     hauteurFenetre() / 2 + hauteurFenetre() / 32,
                                     largeurFenetre() - largeurFenetre() / 128, hauteurFenetre() / 2,
                                     largeurFenetre() - largeurFenetre() / 32,
                                     hauteurFenetre() / 2 - hauteurFenetre() / 32);
                        }

                        rectangle(largeurFenetre() / 4 - largeurFenetre() / 512,
                                  hauteurFenetre() / 8 + hauteurFenetre() / 512,
                                  largeurFenetre() - largeurFenetre() / 4 + largeurFenetre() / 512,
                                  hauteurFenetre() / 32 - hauteurFenetre() / 512);
                        couleurCourante(0, 0, 0);
                        rectangle(largeurFenetre() / 4, hauteurFenetre() / 8, largeurFenetre() - largeurFenetre() / 4,
                                  hauteurFenetre() / 32);

                        couleurCourante(255, 255, 255);
                        float tailleChaineCharger = tailleChaine("Charger la sauvegarde", 28);
                        afficheChaine("Charger la sauvegarde", 28, largeurFenetre() / 2 - tailleChaineCharger / 2,
                                      hauteurFenetre() / 16);

                        printf("%s\n", saves[idSave]);

                        free(chaineNomSave);
                        free(chaineDateSave);

                    }

                    couleurCourante(200, 200, 200);
                    break;
                case MenuSimu:
                    affichePlanetes(true);

                    couleurCourante(255, 255, 255);
                    epaisseurDeTrait(5);

                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2.31,
                              largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.76,
                              largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.58);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.43,
                              largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.30);
                    couleurCourante(0, 0, 0);

                    afficheChaine("Reprendre", 30, largeurFenetre() / 2 - tailleChaine("Reprendre", 30) / 2,
                                  hauteurFenetre() - hauteurFenetre() / 2.1);
                    afficheChaine("Sauvegarder", 30, largeurFenetre() / 2 - tailleChaine("Sauvegarder", 30) / 2,
                                  hauteurFenetre() - hauteurFenetre() / 1.64);
                    afficheChaine("Retour Menu Principal", 30,
                                  largeurFenetre() / 2 - tailleChaine("Retour Menu Principal", 30) / 2,
                                  hauteurFenetre() - hauteurFenetre() / 1.34);

                    epaisseurDeTrait(1);
                    couleurCourante(100, 100, 100);
                    break;
                default:
                    printf("Il se passe quoi là ?????\n");
                    break;
            }
            break;

        case Clavier:
            printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

            switch (state) {
                case Simulation:
                    switch (caractereClavier()) {
                        case 'Z':
                        case 'z':
                            if (!astreFocused) {
                                yCentre -= 100;
                                updateEtoiles();
                            }
                            break;
                        case 'Q':
                        case 'q':
                            if (!astreFocused) {
                                xCentre += 100;
                                updateEtoiles();
                            } else {
                                ptElementAstreCourant = ptElementAstreInitial;
                                while (ptElementAstreCourant != NULL) {
                                    //printf("Nom de l'astre : %s\n",ptElementAstreCourant -> ptAstre -> nom);
                                    if (ptElementAstreCourant->ptElementAstrePrecedent &&
                                        !strcmp(ptElementAstreCourant->ptAstre->nom, astreFocused->nom)) {
                                        astreFocused = ptElementAstreCourant->ptElementAstrePrecedent->ptAstre;
                                        break;
                                    }

                                    ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
                                }
                            }
                            break;
                        case 'S':
                        case 's':
                            if (!astreFocused) {
                                yCentre += 100;
                                updateEtoiles();
                            }
                            break;
                        case 'D':
                        case 'd':
                            if (!astreFocused) {
                                xCentre -= 100;
                                updateEtoiles();
                            } else {
                                ptElementAstreCourant = ptElementAstreInitial;
                                while (ptElementAstreCourant != NULL) {
                                    //printf("Nom de l'astre : %s\n",ptElementAstreCourant -> ptAstre -> nom);
                                    if (ptElementAstreCourant->ptElementAstreSuivant &&
                                        !strcmp(ptElementAstreCourant->ptAstre->nom, astreFocused->nom)) {
                                        astreFocused = ptElementAstreCourant->ptElementAstreSuivant->ptAstre;
                                        break;
                                    }
                                    ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
                                }
                            }
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
                        case 'f':
                        case 'F':
                            astreFocused = RechercheParNom(ptElementAstreInitial, "Le Soleil");
                            break;
                    }
                    break;
                case MenuSimu:
                    switch (caractereClavier()) {
                        case 27:
                            state = Simulation;
                            break;
                    }
                    break;
                case MenuSauvegardes:
                    switch (caractereClavier()) {
                        case 27:
                            state = MenuPrincipal;
                            break;
                        case 13:
                            if (nbsave() != 0) {
                                clicChargerSauvegarde();
                            }
                            break;
                    }
                    break;
                default:
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
                        if (deltaTcheck > 0) {
                            deltaTcheck -= 1000;
                        }
                    } else if (state == MenuSauvegardes) {
                        clicFlecheGaucheSauvegarde();
                    }
                    break;
                case ToucheFlecheDroite:
                    if (state == Simulation) {
                        deltaTcheck += 1000;
                    } else if (state == MenuSauvegardes) {
                        clicFlecheDroiteSauvegarde();
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

                    case MenuPrincipal:

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 &&
                            ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 &&
                            ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2) {
                            ptElementAstreInitial = InitElementAstre(NULL, &t);
                            struct tm dateDuDeces = {0, 0, 0, 21, 5, 122};
                            t = mktime(&dateDuDeces);
                            state = menu(1);
                            initSimu();
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 &&
                            ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 &&
                            ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58) {
                            idSave = 0;
                            state = menu(4);
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 &&
                            ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 &&
                            ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30) {
                            state = menu(5);
                        }
                        break;

                    case Simulation:
                        if (astreFocused) {
                            astreFocused = NULL;
                        }

                        float xAppuye = abscisseSouris() - largeurFenetre() / 2 - xCentre;
                        float yAppuye = ordonneeSouris() - hauteurFenetre() / 2 - yCentre;

                        ptElementAstreCourant = ptElementAstreInitial;
                        while (ptElementAstreCourant != NULL) {
                            Astre *ptAstre = ptElementAstreCourant->ptAstre;
                            if (ptAstre != NULL) {
                                float rayon = ptAstre->rayon;

                                if (!strcmp(ptAstre->nom, "Le Soleil")) {
                                    echellePlanete *= 100.f;
                                }

                                if (ptAstre->rayon * echellePlanete < largeurFenetre() / 512) {
                                    rayon = largeurFenetre() / 512;
                                }

                                if (xAppuye / echelleDistances - rayon / echellePlanete <= ptAstre->x
                                    && xAppuye / echelleDistances + rayon / echellePlanete >= ptAstre->x
                                    && yAppuye / echelleDistances - rayon / echellePlanete <= ptAstre->y
                                    && yAppuye / echelleDistances + rayon / echellePlanete >= ptAstre->y) {
                                    astreFocused = ptAstre;
                                }

                                if (!strcmp(ptAstre->nom, "Le Soleil")) {
                                    echellePlanete /= 100.f;
                                }

                            }

                            ptElementAstreCourant = ptElementAstreCourant->ptElementAstreSuivant;
                        }

                        if (astreFocused) {
                            printf("Astre trouvé : %s\n", astreFocused->nom);
                        }
                        break;
                    case MenuSimu:
                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 &&
                            ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 &&
                            ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2) {
                            state = mini_menu(2, ptElementAstreInitial, t);
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 &&
                            ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 &&
                            ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58) {
                            mini_menu(3, ptElementAstreInitial, t);
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 &&
                            ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 &&
                            ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30) {
                            state = mini_menu(6, ptElementAstreInitial, t);
                        }
                        break;
                    case MenuSauvegardes:
                        if (ordonneeSouris() <= hauteurFenetre() / 2 + hauteurFenetre() / 32 &&
                            ordonneeSouris() >= hauteurFenetre() / 2 - hauteurFenetre() / 32) {
                            if (abscisseSouris() <= largeurFenetre() / 32 &&
                                abscisseSouris() >= largeurFenetre() / 128) {
                                clicFlecheGaucheSauvegarde();
                            } else if (abscisseSouris() >= largeurFenetre() - largeurFenetre() / 32 &&
                                       abscisseSouris() <= largeurFenetre() - largeurFenetre() / 128) {
                                clicFlecheDroiteSauvegarde();
                            }
                        } else if (abscisseSouris() >= largeurFenetre() / 4
                                   && abscisseSouris() <= largeurFenetre() - largeurFenetre() / 4
                                   && ordonneeSouris() >= hauteurFenetre() / 32
                                   && ordonneeSouris() <= hauteurFenetre() / 8
                                   && nbsave() != 0) {
                            clicChargerSauvegarde();
                        } else if (abscisseSouris() >= largeurFenetre() / 64
                                   && abscisseSouris() <= largeurFenetre() / 16
                                   && ordonneeSouris() >= hauteurFenetre() - hauteurFenetre() / 16
                                   && ordonneeSouris() <= hauteurFenetre() - hauteurFenetre() / 64) {
                            state = MenuPrincipal;
                        }
                        break;
                    default:
                        break;
                }
            } else if (etatBoutonSouris() == GaucheRelache) {
                //printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
            }
            break;

        case Souris: // Si la souris est deplacee

            /* Nous aurions bien voulu utiliser cet événement
             * malheureusement, il se trouve que ce dernier ne fonctionne pas
             * En effet, il faut cliquer sur la souris pour que le programme se rende compte que la souris bouge
             * Dommage.
             */

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
