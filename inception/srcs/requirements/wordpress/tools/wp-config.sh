#!/bin/bash

# Attendre que MariaDB soit prêt
echo "Waiting for MariaDB to be ready..."
while ! mysqladmin ping -h"mariadb" --silent; do
    sleep 2
done
echo "MariaDB is ready!"

# Créer le répertoire pour PHP-FPM
mkdir -p /run/php
chown www-data:www-data /run/php
chmod 755 /var/run/php

cd /var/www/html

# Nettoyer une installation précédente
if [ -f "wp-config.php" ]; then
    echo "Existing WordPress installation detected. Removing old files..."
    rm -rf wp-config.php
fi

echo "Setting up WordPress..."

# Télécharger WordPress si ce n'est pas déjà fait
if [ ! -f "index.php" ]; then
    echo "Downloading WordPress core..."
    wp core download --allow-root
fi

# Attendre que la base de données soit prête
until mysql -h"mariadb" -u"$MYSQL_USER" -p"$MYSQL_PASSWORD" -e "USE $MYSQL_DATABASE"; do
    echo "Waiting for database to be ready..."
    sleep 2
done

echo "Database is ready!"

# Créer la configuration WordPress
wp config create --allow-root \
    --dbname="$MYSQL_DATABASE" \
    --dbuser="$MYSQL_USER" \
    --dbpass="$MYSQL_PASSWORD" \
    --dbhost="mariadb" \
    --dbcharset="utf8mb4" \
    --dbcollate="utf8mb4_unicode_ci" \
    --force

# Installer WordPress si ce n'est pas déjà fait
if ! wp core is-installed --allow-root; then
    wp core install --allow-root \
        --url=$DOMAIN_NAME \
        --title=$WP_TITLE \
        --admin_user=$WP_ADMIN_USER \
        --admin_password=$WP_ADMIN_PASS \
        --admin_email=$WP_ADMIN_EMAIL \
        --skip-email \
        --allow-root

    wp user create --allow-root \
        "$WP_USER" \
        "$WP_USER_EMAIL" \
        --user_pass="$WP_USER_PASS" \
        --allow-root
fi

# Installer et activer le thème Inspiro
wp theme install inspiro --activate --allow-root

# Démarrer PHP-FPM
exec php-fpm7.4 -F