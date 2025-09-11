# Cub3D

**Cub3D** est un projet 42 inspiré de **Wolfenstein 3D**.  
L'objectif est de créer un petit moteur graphique 3D basé sur la technique du **raycasting**, tout en gérant les collisions, les textures et les déplacements en temps réel.

## Objectifs du projet
- Comprendre et implémenter le **raycasting** pour simuler une vue 3D à partir d'une carte 2D  
- Gérer le rendu des textures pour les murs  
- Implémenter la gestion des collisions avec les murs et obstacles  
- Gérer les entrées clavier/souris pour le déplacement du joueur  
- Charger et interpréter une carte décrite dans un fichier `.cub`  
- Développer une structure de code claire et performante

## Fonctionnalités principales
- Déplacements du joueur avec les touches `W`, `A`, `S`, `D`  
- Rotation de la caméra avec la souris ou les touches directionnelles  
- Gestion du sol et du plafond avec des couleurs personnalisées  
- Affichage des murs avec textures PNG  
- Gestion des collisions avec un rayon (hitbox) pour éviter de traverser les murs  
- Mini-map intégrée pour visualiser la position du joueur et la carte  
- Parsing robuste du fichier `.cub` :
  - Vérification de la validité de la carte
  - Position initiale du joueur (`N`, `S`, `E`, `W`)
  - Chemins des textures murales
  - Couleurs du sol et du plafond

## Stack technique
- **Langage :** C  
- **Bibliothèque graphique :** MLX42  
- **Gestion des images et textures :** PNG avec `load_png`  
- **Architecture logicielle :** Approche modulaire avec parsing, moteur graphique et logique de jeu séparés
