# 📸 Camagru

Camagru est une application web permettant aux utilisateurs de prendre des photos avec leur webcam, d’y appliquer des filtres et de les partager avec la communauté. Les utilisateurs peuvent également liker et commenter les photos.

---

## 🚀 Fonctionnalités

* Inscription et connexion des utilisateurs
* Authentification sécurisée
* Prise de photo via webcam
* Upload d’images
* Application de filtres
* Galerie publique
* Likes et commentaires
* Gestion du profil utilisateur

---

## 🛠️ Technologies utilisées

* Backend : PHP
* Frontend : HTML, CSS, JavaScript
* Base de données : MySQL
* Serveur : Apache / Nginx

---

## 📦 Installation complète

### Prérequis

* PHP >= 7.x
* MySQL ou MariaDB
* Serveur web (Apache/Nginx) ou serveur PHP intégré
* Navigateur moderne avec accès à la webcam

---

## ⚠️ Configuration obligatoire : fichier `.env`

Ce projet nécessite un fichier `.env` pour fonctionner correctement.
Pour des raisons de sécurité, ce fichier **n’est pas inclus dans le dépôt GitHub**.

---

### 1️⃣ Cloner le projet

```bash
git clone https://github.com/ton_username/camagru.git
cd camagru
```

---

### 2️⃣ Créer le fichier `.env`

À la racine du projet, crée un fichier `.env` :

```bash
touch .env
```

Puis colle **exactement** ce contenu dans `.env` :

```env
APP_ENV=production
APP_URL=https://localhost:8443

DB_HOST=db
DB_PORT=3306
DB_NAME=camagru
DB_USER=camagru
DB_PASS=pw

MYSQL_ROOT_PASSWORD=rootpassword

MAIL_FROM=noreply@localhost
```

---

### 3️⃣ Initialiser la base de données

Si un fichier SQL est fourni (ex: `database.sql`) :

```bash
mysql -u camagru -p camagru < database.sql
```

Ou avec root :

```bash
mysql -u root -p camagru < database.sql
```

Assure-toi que :

* La base `camagru` existe
* L’utilisateur a les droits nécessaires

---

### 4️⃣ Permissions des dossiers (OBLIGATOIRE)

Ces dossiers doivent être accessibles en écriture :

```bash
chmod -R 777 web/public/uploads web/public/thumbs web/public/avatar
```

Ces dossiers servent à :

* L’upload des images
* La génération des miniatures
* La gestion des avatars

---

### 5️⃣ Lancer l’application (Docker / Makefile)

Le projet se lance via **Docker Compose** à l’aide du **Makefile**.

#### Démarrer (build + up)

```bash
make start
```

#### Démarrer (up simple)

```bash
make up
```

#### Arrêter

```bash
make down
```

#### Voir les logs

```bash
make logs
```

#### Voir l’état des containers

```bash
make ps
```

Une fois lancé, l’application est accessible à l’URL définie dans le `.env` :

```env
APP_URL=https://localhost:8443
```

➡️ Ouvre donc : `https://localhost:8443`

> ℹ️ Si ton navigateur affiche un avertissement de certificat (HTTPS en local), c’est normal : accepte l’exception pour continuer.

---

### 6️⃣ Permissions des dossiers (OBLIGATOIRE)

Même en Docker, ces dossiers doivent être accessibles en écriture (selon ta configuration de volumes).

```bash
chmod -R 777 web/public/uploads web/public/thumbs web/public/avatar
```

Ces dossiers servent à :

* L’upload des images
* La génération des miniatures
* La gestion des avatars

---

### Commandes Makefile utiles

| Commande            | Description                                            |
| ------------------- | ------------------------------------------------------ |
| `make start`        | Build + up (recommandé)                                |
| `make up`           | Démarre les containers                                 |
| `make down`         | Arrête les containers                                  |
| `make logs`         | Affiche les logs en direct                             |
| `make ps`           | Affiche l’état des containers                          |
| `make reset-images` | Supprime uniquement les images (uploads/thumbs/avatar) |
| `make clean`        | Nettoyage complet : containers + volumes + images      |

---

## 📧 Gestion des emails (MailHog)

Ce projet utilise **MailHog** pour intercepter les emails envoyés par l’application en environnement local.

Cela permet de tester :

* La confirmation d’inscription
* La réinitialisation de mot de passe
* Les notifications

### Accéder à MailHog

Une fois les containers lancés :

```bash
make start
```

Ouvre dans ton navigateur :

```
http://localhost:8025
```

Tu y verras **tous les emails envoyés par l’application**.

---

### Configuration

Dans ton fichier `.env` :

```env
MAIL_FROM=noreply@localhost
```

Les emails ne sont **pas réellement envoyés**, ils sont capturés par MailHog.

---

### Notes

* Aucun email réel n’est envoyé
* Tout reste en local
* Utile pour le debug et les tests

---

## 📁 Structure du projet

```
camagru/
│
├── web/
│   └── public/
│       ├── uploads/
│       ├── thumbs/
│       ├── avatar/
│       ├── css/
│       └── js/
│
├── src/
├── config/
├── .env
├── README.md
└── .gitignore
```

---

## 🔐 Sécurité

* Mots de passe hashés
* Protection contre les injections SQL
* Protection contre les XSS
* Validation des entrées utilisateur
* Sessions sécurisées

---

## ℹ️ Notes importantes

* Le fichier `.env` est obligatoire pour lancer le projet
* Les permissions `chmod` sont indispensables
* Certains navigateurs exigent HTTPS pour l’accès webcam
* Le projet fonctionne correctement sur `localhost`

---

## 📌 Projet scolaire

Ce projet a été réalisé dans le cadre du cursus de l'école 42.
