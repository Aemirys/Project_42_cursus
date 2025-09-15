# ft_transcendance

## Table des matières
- [Introduction](#introduction)
- [Fonctionnalités](#fonctionnalités)
- [Architecture](#architecture)
- [Technologies utilisées](#technologies-utilisées)
- [Installation et Lancement](#installation-et-lancement)
- [Configuration](#configuration)
- [Utilisation](#utilisation)
- [Déploiement](#déploiement)
- [Auteurs](#auteurs)
- [Licence](#licence)

---

## Introduction

**ft_transcendance** est un projet de la formation 42 visant à concevoir une application web complète.  
Le but est de créer une plateforme permettant à des utilisateurs de jouer à **Pong** en ligne ainsi qu'à un **deuxième jeu inspiré de Space Invaders**, tout en intégrant un système social avancé et des fonctionnalités modernes de sécurité et de communication.

L'application est entièrement conteneurisée avec **Docker**, et peut être déployée localement ou en production.

---

## Fonctionnalités

Voici les principales fonctionnalités déjà implémentées :

| Fonctionnalité            | Description |
|---------------------------|-------------|
| **Authentification OAuth** | Connexion via Google |
| **Double Authentification (2FA)** | Sécurité renforcée via Google Authenticator |
| **Jeu Pong**               | Jouable en local |
| **Deuxième jeu**           | Jeu inspiré de *Space Invaders* |
| **Système d'amis**         | Ajout et gestion d'amis |
| **Chat et messagerie**     | Communication entre utilisateurs |
| **Avatars personnalisés**  | Modification de l'avatar du profil |
| **HTTPS**                   | Accès sécurisé via SSL (certificat auto-signé en local) |
| **Gestion via Docker**      | Déploiement simplifié avec `docker-compose` |

---

## Architecture

L'application suit une architecture modulaire et repose sur plusieurs services conteneurisés :

```
┌────────────────────────────┐
│         Frontend            │
│ (TypeScript + Vite Vanilla) │
└─────────────▲──────────────┘
              │ HTTPS (8443)
┌─────────────┴──────────────┐
│          Backend            │
│ (Node.js + Fastify)         │
└─────────────▲──────────────┘
              │ PostgreSQL
┌─────────────┴──────────────┐
│          Database           │
│         (PostgreSQL)        │
└────────────────────────────┘
```

- **Frontend** : application web SPA en TypeScript.
- **Backend** : API REST + WebSockets pour les jeux et la communication en temps réel.
- **Database** : stockage des utilisateurs, amis, scores, parties et chats.

---

## Technologies utilisées

| Côté       | Technologie            |
|------------|-----------------------|
| **Frontend** | TypeScript, Vite Vanilla |
| **Backend**  | Node.js, Fastify |
| **Base de données** | PostgreSQL |
| **Auth**     | OAuth (Google), 2FA (Google Authenticator) |
| **Sécurité** | HTTPS avec certificat SSL auto-signé |
| **Conteneurisation** | Docker & Docker Compose |

---

## Installation et Lancement

### Prérequis
- [Docker](https://www.docker.com/)
- [Docker Compose](https://docs.docker.com/compose/)

---

### Étapes

1. **Cloner le projet**

   ```bash
   git clone <URL_DU_REPO>
   cd ft_transcendance
   ```

2. **Configurer le fichier `.env`**

   Copier le fichier d'exemple :

   ```bash
   cp .env.example .env
   ```

   Puis modifier les variables selon votre environnement local :

   ```
   # Exemple
   DOMAIN=pongwars.com
   BACKEND_PORT=8443
   DB_USER=postgres
   DB_PASSWORD=mot_de_passe
   DB_NAME=transcendence
   DB_PORT=5432
   GOOGLE_CLIENT_ID=ton_client_id_google
   GOOGLE_CLIENT_SECRET=ton_client_secret_google
   ```

   ⚠️ **Important :**  
   - Ajouter `pongwars.com` au fichier `/etc/hosts` :
     ```
     127.0.0.1 pongwars.com
     ```

3. **Lancer le projet**

   ```bash
   docker-compose up --build
   ```

4. **Accéder au site**

   Une fois les conteneurs démarrés, ouvrir :

   ```
   https://pongwars.com:8443
   ```

   > ⚠️ Comme il s'agit d'un certificat auto-signé, le navigateur affichera un avertissement.  
   > Acceptez l'exception de sécurité pour continuer.

---

## Configuration

### Variables d'environnement principales

| Variable | Description |
|-----------|-------------|
| `DOMAIN` | Domaine utilisé (ex: `pongwars.com`) |
| `BACKEND_PORT` | Port HTTPS du backend (par défaut `8443`) |
| `DB_USER` | Utilisateur PostgreSQL |
| `DB_PASSWORD` | Mot de passe PostgreSQL |
| `DB_NAME` | Nom de la base de données |
| `GOOGLE_CLIENT_ID` | ID client Google pour OAuth |
| `GOOGLE_CLIENT_SECRET` | Secret client Google pour OAuth |

---

## Utilisation

### Authentification
- Connexion via **Google OAuth**
- Option de sécurisation supplémentaire avec **Google Authenticator** (2FA)

### Jeux disponibles
- **Pong** : jouable en local entre deux joueurs.
- **Space Invaders Like** : second jeu plus avancé.

### Système social
- Ajouter et gérer ses amis.
- Voir l'état de connexion des autres joueurs.
- Envoyer des messages en direct via le chat intégré.

---

## Déploiement

En production, il est conseillé de :

1. Configurer un certificat SSL valide (Let's Encrypt par exemple).
2. Héberger les services Docker sur un serveur dédié ou un VPS.
3. Utiliser un reverse proxy (Nginx, Traefik) pour gérer HTTPS et le routage.

---

## Auteurs

Projet réalisé par l'équipe :  

- **[Nom 1]**
- **[Nom 2]**
- **[Nom 3]**
- **[Nom 4]**

---

## Licence

Ce projet est sous licence [MIT](https://opensource.org/licenses/MIT).  

Vous êtes libre de l'utiliser, le modifier et le redistribuer sous certaines conditions.
