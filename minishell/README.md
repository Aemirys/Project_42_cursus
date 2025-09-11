# Minishell

**Minishell** est un projet de l'école **42** qui consiste à **reproduire un shell Unix** simplifié.  
L'objectif est de comprendre en profondeur le fonctionnement d'un terminal et des processus sous Unix en implémentant les fonctionnalités essentielles d'un shell.

Ce projet permet d'acquérir de solides compétences en :
- **Programmation système en C**.
- Gestion des **processus** et **signaux**.
- Manipulation des **pipes**, **redirections**, et **variables d'environnement**.
- Gestion de la **mémoire** et des erreurs.
- Conception d'un projet modulaire et robuste.

---

## Objectif du projet

Créer un shell capable de :
- Exécuter des **commandes** comme `/bin/ls` ou `cat`.
- Gérer les **redirections** (`>`, `>>`, `<`).
- Supporter les **pipes** (`|`) pour enchaîner plusieurs commandes.
- Gérer les **signaux** (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Implémenter des **built-ins** comme `echo`, `cd`, `pwd`, `export`, `unset`, `env`, et `exit`.
- Reproduire un comportement proche de **bash**.

---

## Fonctionnalités principales

| Fonctionnalité | Description |
|----------------|------------|
| **Exécution simple** | Lancer une commande externe avec ses arguments. |
| **Redirections** | Gérer les entrées et sorties avec `<`, `>`, `>>`. |
| **Pipes** | Chaîner plusieurs commandes (`cmd1 | cmd2`). |
| **Gestion des erreurs** | Messages clairs et précis pour chaque erreur. |
| **Variables d'environnement** | Utiliser et modifier l'environnement (`$HOME`, `$PATH`, etc.). |
| **Built-ins** | Implémentation des commandes internes (voir ci-dessous). |
| **Gestion des signaux** | Interruption (`Ctrl+C`), fin de fichier (`Ctrl+D`), etc. |

### Built-ins implémentés
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`
