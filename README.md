# Simulation Spatiale - Les Amateurs
Projet Final d'Algorithmie à l'ISEN du Semestre 2 - Groupe des Amateurs<br>
Réalisé pendant le 2ème semestre du cursus CIN1.

## Informations sur le projet
- Projet du 2ème semestre à l'ISEN en Algorithmie
- Groupe composé de Bastient SCHNEIDER, Quentin TURCOTTI, Léo REY et Thomas SEIGNOUR (Les Amateurs)
- Projet rendu le 21/06/2022

## Présentation du projet
### Description
Pour cet ultime projet d'algorithmie de la première année du cursus CIN, les professeurs nous ont demandé de créer **un logiciel permettant de simuler des astres dans l'espace**. La majorité des étudiants ont décidé d'intégrer le système solaire dans leur logiciel.

### Solution
Pour notre groupe, le logiciel affiche en effet tout le système solaire et les planètes qui tournent, mis à l'échelle affichée en bas à droite de l'écran.<br>
Le **logiciel permet de faire un focus sur chaque planète**, affichant par la même occasion des informations sur cette planète.<br>
Une sauvegarde est possible, ainsi qu'un chargement de la sauvegarde.<br>
Le **temps peut être accéléré ou décéléré**, et la simulation montre la date exacte où l'utilisateur devrait se trouver.<br>
L'utilisateur peut également **se déplacer librement** dans tout le système solaire.<br>
Le programme a cependant un dysfonctionnement, il n'arrive pas à afficher la Lune, qui disparaît dès le lancement.<br>
**Il y a beaucoup de fonctionnalités** que vous pourrez découvrir en lançant le programme et en vous balandant entre tous les boutons, et en essayant les **raccourcis claviers décrits ci-dessous** !

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


