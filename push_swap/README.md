# push_swap

**push_swap** est un projet de l'école **42** qui a pour but d'implémenter un algorithme permettant de **trier une pile d'entiers** en utilisant un **ensemble d'instructions limité**.  
L'objectif est de **minimiser le nombre de coups** nécessaires pour trier la pile et d'optimiser les performances de l'algorithme.

Ce projet permet de travailler sur :
- La conception d'algorithmes efficaces.
- La gestion de la complexité algorithmique.
- La manipulation de structures de données comme les **piles** et **listes chaînées**.

---

## Objectif du projet

Créer deux programmes :

1. **push_swap**  
   - Reçoit une liste d'entiers en argument.
   - Trie la pile `a` en utilisant une pile `b` et un ensemble restreint d'instructions.

2. **checker** *(optionnel pour tester)*  
   - Lit une série d'instructions depuis l'entrée standard.
   - Vérifie si elles trient correctement la pile.

---

## Instructions disponibles

| Commande | Description |
|-----------|------------|
| **sa** | Swap les 2 premiers éléments de la pile `a` |
| **sb** | Swap les 2 premiers éléments de la pile `b` |
| **ss** | `sa` et `sb` en même temps |
| **pa** | Push le premier élément de `b` sur `a` |
| **pb** | Push le premier élément de `a` sur `b` |
| **ra** | Rotate `a` (décale tous les éléments vers le haut) |
| **rb** | Rotate `b` |
| **rr** | `ra` et `rb` en même temps |
| **rra** | Reverse rotate `a` (décale tous les éléments vers le bas) |
| **rrb** | Reverse rotate `b` |
| **rrr** | `rra` et `rrb` en même temps |

---

## Règles et contraintes

- Le programme doit être écrit **en C pur**, conforme à la Norme 42.
- Aucune fonction interdite ne doit être utilisée.
- Le nombre de coups doit être **le plus petit possible**.
- Le programme doit gérer :
  - Les doublons (interdits → erreur).
  - Les entrées invalides (non numériques, dépassement d'int).
  - Les grands ensembles de données (ex: 500 nombres).

---
