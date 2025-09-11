# So_long

**So_long** est un projet de l'école **42** qui consiste à développer un **petit jeu 2D** en C en utilisant la **MiniLibX**.  
L'objectif est de renforcer la compréhension de la **programmation graphique**, de la gestion des **événements clavier**, et du **parsing de fichiers**.

---

## Objectif du projet

Créer un jeu simple où un joueur doit :
- Se déplacer dans une carte en ramassant tous les objets (collectibles).
- Atteindre la sortie une fois que tous les objets ont été collectés.
- Éviter les ennemis (bonus).

Le jeu se termine lorsque le joueur :
- Ramasse tous les objets et atteint la sortie.
- Ou meurt s'il touche un ennemi (bonus).

---

## Format de la carte

Le jeu utilise une **map** définie dans un fichier `.ber`.  
Elle est composée de plusieurs caractères représentant les différents éléments du jeu :

| Caractère | Signification |
|------------|---------------|
| `0` | Sol vide |
| `1` | Mur |
| `C` | Objet à collecter |
| `E` | Sortie |
| `P` | Position de départ du joueur |
| `X` *(bonus)* | Ennemi |



