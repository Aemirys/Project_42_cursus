# Inception

**Inception** est un projet de l'école **42** qui consiste à mettre en place une architecture de services à l'aide de **Docker** et **docker-compose**, dans une **machine virtuelle Debian**.  
Ce projet permet de découvrir la **virtualisation**, l'orchestration de conteneurs et la mise en place d'environnements de développement et de production sécurisés.

> **Score final : 100% ✅**

---

## Objectifs du projet

- Découvrir **Docker** et son fonctionnement.
- Déployer plusieurs services dans des conteneurs isolés.
- Gérer la communication entre les conteneurs grâce à `docker-compose`.
- Sécuriser l'infrastructure avec **TLS/SSL**.
- Assurer la **persistance des données** dans la base de données et les fichiers.
- Comprendre la logique des **infrastructures modernes** et la conteneurisation.

---

## Architecture des services

L'objectif est de créer une infrastructure composée de plusieurs services qui communiquent entre eux, en respectant la logique suivante :

| Service         | Description |
|-----------------|-------------|
| **NGINX**       | Reverse proxy + gestion du certificat SSL. |
| **WordPress**   | Site web dynamique pour héberger le contenu. |
| **MariaDB**     | Base de données relationnelle pour WordPress. |

---

## Fonctionnalités principales

- Mise en place d'une architecture avec **3 services principaux** :
  - Serveur **NGINX** sécurisé avec un certificat TLS/SSL.
  - **WordPress** avec un accès via HTTPS uniquement.
  - **MariaDB** pour stocker les données et utilisateurs.
- Gestion complète des conteneurs avec `docker-compose`.
- Création de **volumes persistants** pour les données :
  - Base de données.
  - Fichiers WordPress.
- Configuration et déploiement automatisés via des **Dockerfiles**.
- Infrastructure entièrement contenue dans une **machine virtuelle Debian**.

---

## Schéma de l'infrastructure

