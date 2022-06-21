# Simulation Spatiale - Les Amateurs
Projet Final d'Algorithmie à l'ISEN du Semestre 2 - Groupe des Amateurs

## Manuel d'utilisation
### Utilisation et première compilation
Voici une liste d'instructions pour compiler le programme pour la première fois.
- Le programme est destiné aux utilisateurs de Linux. Veiller à utiliser un système d'exploitation Linux.
- Ouvrez un terminal
- GLUT est nécessaire à la compilation du programme. S'il n'est pas déjà installé, utilisez la commande `sudo apt install freeglut3-dev`
- Importer le programme: `git clone https://github.com/Sigeth/algo-amateurs-s2.git` puis `cd algo-amateurs-s2`
- Compiler le programme: `make`
- Lancer le programme: `./main`

### Raccourcis clavier disponibles

| Situation du programme | Touche | Effet                                                  |
|------------------------|--------|--------------------------------------------------------|
| Tous                   | F1     | Change le taux de rafraichissement à 60 FPS            |
| Tous                   | F2     | Change le taux de rafraichissement à 10 FPS            |
| Tous                   | F3     | Change le taux de rafraichissement à 0 FPS             |
| Tous                   | F4     | Ferme le programme                                     |
| Tous                   | F11    | Passe le programme en plein écran                      |
| Simulation             | Z      | Déplacement vers le haut                               |
| Simulation             | Q      | Déplacement vers la gauche                             |
| Simulation             | S      | Déplacement vers le bas                                |
| Simulation             | D      | Déplacement vers la droite                             |
| Simulation             | Espace | Met pause à la simulation                              |
| Simulation             | 0      | Réinitialise la position de la caméra (0,0)            |
| Simulation             | ←      | Décélère le temps de la simulation                     |
| Simulation             | →      | Accélère le temps de la simulation                     |
| Simulation             | ↑      | Zoom                                                   |
| Simulation             | ↓      | Dézoom                                                 |
| Simulation             | F      | Mise en focus sur Le Soleil                            |
| Simulation (focus)     | Q      | Change le focus sur la planète précédente              |
| Simulation (focus)     | D      | Change le focus sur la planète suivante                |
| Simulation             | Échap  | Accède au menu de pause de la simulation               |
| Menu Pause Simulation  | Échap  | Revient à la simulation                                |
| Menu des sauvegardes   | ←      | Navigue vers la précédente sauvegarde disponible       |
| Menu des sauvegardes   | →      | Navigue vers la prochaine sauvegarde disponible        |
| Menu des sauvegardes   | Entrée | Lance une simulation à partir de la sauvegarde choisie |
| Menu des sauvegardes   | Échap  | Revient au menu principal                              |


## Informations sur le projet
- Projet du 2ème semestre à l'ISEN en Algorithmie
- Groupe composé de Bastient SCHNEIDER, Quentin TURCOTTI, Léo REY et Thomas SEIGNOUR (Les Amateurs)
- Projet rendu le 21/06/2022

