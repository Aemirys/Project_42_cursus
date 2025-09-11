# Ft_transcendence

**Ft_transcendence** est un projet 42 inspiré de **Pong**, développé pour s’entraîner au backend, au frontend, et à la communication entre services.

## Stack technique
- **Frontend :** TypeScript, HTML, CSS, Vite  
- **Backend :** Node.js, Fastify  
- **Services :**  
  - Avatar Service (gestion des avatars)   
  - User Service (gestion des utilisateurs et scores)  
  - TwoFA Service (authentification à deux facteurs)  
  - Google Auth Service (connexion via Google OAuth2)  
  - Blockchain Service (gestion de la logique de tournois et matchs, smart contracts)  
- **Déploiement :** Docker  

## Fonctionnalités principales
- Jeu de Pong en local contre un autre joueur  
- Gestion des comptes utilisateurs et avatars  
- Authentification via Google  
- Authentification à deux facteurs (optionnelle)  
- Historique des scores  
- Enregistrement et gestion des matchs via le `blockchain_service`  

## Installation
1. Cloner le projet :  
```bash
git clone https://github.com/tonpseudo/Project_42_cursus.git
cd ft_transcendence

