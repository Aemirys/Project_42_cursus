# Webserv

**Webserv** est un projet de l'école **42** qui consiste à recréer un **serveur web HTTP/1.1** en C++, capable de gérer plusieurs clients simultanément.  
L'objectif est de comprendre en profondeur le fonctionnement des serveurs web, des **protocoles réseaux**, et de la **programmation orientée objet**.

> **Score final : 110% ✅**

---

## Objectifs du projet

- Développer un serveur web **similaire à Nginx**.
- Gérer plusieurs connexions simultanées **sans threads**, en utilisant des **sockets non-bloquants** et la fonction `poll()`.
- Implémenter le **parsing d'un fichier de configuration**.
- Gérer les **méthodes HTTP** de base : `GET`, `POST`, et `DELETE`.
- Permettre l'exécution de **CGI (Common Gateway Interface)**, notamment en Python et PHP.
- Servir des **fichiers statiques** (HTML, CSS, images, etc.).
- Implémenter une **page d'erreur personnalisée**.
- Gérer le **timeout des connexions** et la **fermeture propre des sockets**.

---

## Fonctionnalités principales

| Fonctionnalité | Description |
|----------------|-------------|
| **Serveur multi-clients** | Gestion simultanée de plusieurs clients grâce à `poll()`. |
| **Parsing du fichier de configuration** | Syntaxe similaire à celle de Nginx. |
| **Méthodes HTTP** | Support complet de `GET`, `POST`, `DELETE`. |
| **CGI** | Support des scripts CGI (Python, PHP, etc.). |
| **Pages d'erreurs personnalisées** | Pages dédiées pour les erreurs HTTP (404, 500...). |
| **Gestion des uploads** | Possibilité d'envoyer des fichiers via des formulaires HTML. |
| **Logs** | Messages d'erreurs et logs pour le debug. |
| **Timeout** | Fermeture automatique des connexions inactives. |

---

## Exemple de fichier de configuration

Le serveur lit un fichier de configuration `.conf` qui ressemble à celui de Nginx :

```conf
server {
    listen 8080;
    server_name my_webserv;

    root ./www;

    location / {
        index index.html;
    }

    location /uploads {
        upload_path ./www/uploads;
        allow_methods GET POST;
    }

    error_page 404 ./www/errors/404.html;
    error_page 500 ./www/errors/500.html;
}
