# Philosophers

**Philosophers** est un projet de l'école **42** qui consiste à résoudre le **problème classique des philosophes** en utilisant la **programmation concurrente**.  
Ce projet permet de comprendre la gestion des threads, la synchronisation avec les mutex et la prévention des problèmes de **deadlock**, **race conditions**, et **starvation**.

---

## Objectif du projet

Créer un programme capable de simuler un groupe de philosophes qui :
- Pensent,
- Mangent,
- Dorment,

en partageant un nombre limité de **fourchettes** (ressources) tout en évitant les blocages.

Chaque philosophe doit :
1. Prendre deux fourchettes pour manger.
2. Manger pendant un certain temps.
3. Reposer les fourchettes et dormir.
4. Recommencer le cycle jusqu'à ce qu'il meure ou que la simulation s'arrête.

---

## Paramètres du programme

Le programme doit être lancé avec les paramètres suivants :

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
