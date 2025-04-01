# #!/bin/bash

# # Répertoire WordPress
# # WORDPRESS_DIR="/home/estosche/data/wordpress"

# # # Aller dans le répertoire WordPress
# # cd $WORDPRESS_DIR || { echo "Erreur : impossible de se déplacer dans le répertoire WordPress"; exit 1; }

# # # Assurer que le répertoire WordPress a les bonnes permissions
# # echo "Setting permissions for WordPress directory..."
# # chown -R $(whoami):$(whoami) $WORDPRESS_DIR
# # chmod -R u+rw $WORDPRESS_DIR

# # Attendre que MariaDB soit prêt
# echo "Waiting for MariaDB to be ready..."
# while ! mysqladmin ping -h"mariadb" --silent; do
#     sleep 2
# done
# echo "MariaDB is ready!"

# if [ "$(ls -A /var/www/html)" ]; then
#     echo "Le répertoire WordPress contient déjà des fichiers. Suppression en cours..."
#     rm -rf /var/www/html/*
# else
#     echo "Le répertoire WordPress est vide. Aucune suppression nécessaire."
# fi

# # Créer le répertoire pour PHP-FPM
# mkdir -p /run/php
# chown www-data:www-data /run/php

# cd /var/www/html

# # Nettoyer l'installation précédente si elle existe
# if [ -f "wp-config.php" ]; then
#     rm -f wp-config.php
# fi

# # Télécharger WordPress si nécessaire
# if [ ! -f "index.php" ]; then
#     wp core download --allow-root
# fi

# # Attendre que la base de données soit prête
# until mysql -h"mariadb" -u"$MYSQL_USER" -p"$MYSQL_PASSWORD" -e "USE $MYSQL_DATABASE"; do
#     echo "Waiting for database to be ready..."
#     sleep 2
# done
# echo "Database is ready!"

# # Créer la configuration WordPress
# wp config create --allow-root \
#     --dbname="$MYSQL_DATABASE" \
#     --dbuser="$MYSQL_USER" \
#     --dbpass="$MYSQL_PASSWORD" \
#     --dbhost="mariadb" \
#     --dbcharset="utf8mb4" \
#     --dbcollate="utf8mb4_unicode_ci" \
#     --force

# # Installer WordPress si ce n'est pas déjà fait
# if ! wp core is-installed --allow-root; then
#     wp core install --allow-root \
#         --url=$DOMAIN_NAME \
#         --title=$WP_TITLE \
#         --admin_user=$WP_ADMIN_USER \
#         --admin_password=$WP_ADMIN_PASSWORD \
#         --admin_email=$WP_ADMIN_EMAIL

#     wp user create --allow-root \
#         "$WP_USER" \
#         "$WP_USER_EMAIL" \
#         --user_pass="$WP_USER_PASSWORD" \
#         --role="author"
# fi

# # Configurer les permissions
# chown -R www-data:www-data /var/www/html
# find /var/www/html -type d -exec chmod 755 {} \;
# find /var/www/html -type f -exec chmod 644 {} \;

# # Démarrer PHP-FPM
# exec php-fpm7.4 -F


#!/bin/bash

# Attendre que MariaDB soit prêt
echo "Waiting for MariaDB to be ready..."
while ! mysqladmin ping -h"mariadb" --silent; do
    sleep 2
done
echo "MariaDB is ready!"

if [ "$(ls -A /var/www/html)" ]; then
    echo "Le répertoire WordPress contient déjà des fichiers. Suppression en cours..."
    rm -rf /var/www/html/*
else
    echo "Le répertoire WordPress est vide. Aucune suppression nécessaire."
fi

# Créer le répertoire pour PHP-FPM
mkdir -p /run/php
chown www-data:www-data /run/php

cd /var/www/html

# Nettoyer l'installation précédente si elle existe
if [ -f "wp-config.php" ]; then
    rm -f wp-config.php
fi

# Télécharger WordPress si nécessaire
if [ ! -f "index.php" ]; then
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
        --admin_email=$WP_ADMIN_EMAIL

    wp user create --allow-root \
        "$WP_USER" \
        "$WP_USER_EMAIL" \
        --user_pass="$WP_USER_PASS" \
        --role="author"
fi

# Configurer les permissions
chown -R www-data:www-data /var/www/html
find /var/www/html -type d -exec chmod 755 {} \;
find /var/www/html -type f -exec chmod 644 {} \;

# Démarrer PHP-FPM
exec php-fpm7.4 -F