# #!/bin/bash

# # S'assurer que les répertoires ont les bonnes permissions
# mkdir -p /var/run/mysqld /var/lib/mysql
# chown -R mysql:mysql /var/run/mysqld /var/lib/mysql
# chmod 777 /var/run/mysqld
# chmod 755 /var/lib/mysql

# # Initialiser la base de données si elle n'existe pas
# if [ ! -d "/var/lib/mysql/mysql" ]; then
#     # Initialiser la base de données
#     mysql_install_db --user=mysql --datadir=/var/lib/mysql --rpm > /dev/null

#     # Démarrer MySQL temporairement pour configurer les utilisateurs
#     tfile=$(mktemp)
#     cat << EOF > $tfile
# USE mysql;
# FLUSH PRIVILEGES;
# DELETE FROM mysql.user WHERE User='';
# DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');
# ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
# CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
# CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
# GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%';
# FLUSH PRIVILEGES;
# EOF

#     # Configurer la base de données
#     /usr/sbin/mysqld --user=mysql --bootstrap < $tfile
#     rm -f $tfile
# fi

# # Démarrer MariaDB avec les bonnes permissions
# exec mysqld --user=mysql --console

# #!/bin/bash
# # Répertoire MariaDB
# # MARIADB_DIR="/home/estosche/data/mariadb"

# # cd $MARIADB_DIR || { echo "Erreur : impossible de se déplacer dans le répertoire Mariadb"; exit 1; }
# # # Assurer que le répertoire MariaDB a les bonnes permissions
# # echo "Setting permissions for MariaDB directory..."
# # chown -R $(whoami):$(whoami) $MARIADB_DIR
# # chmod -R u+rw $MARIADB_DIR

# # Assurer que les répertoires existent avec les bonnes permissions
# mkdir -p /var/run/mysqld /var/lib/mysql
# chown -R mysql:mysql /var/run/mysqld /var/lib/mysql
# chmod 777 /var/run/mysqld
# chmod 755 /var/lib/mysql

# # Vérifier si la base de données est déjà initialisée
# if [ ! -d "/var/lib/mysql/mysql" ]; then
#     echo "Initialisation de la base de données..."
    
#     # Initialiser la base de données
#     mysql_install_db --user=mysql --datadir=/var/lib/mysql --rpm > /dev/null

#     # Fichier temporaire pour les commandes SQL
#     tfile=$(mktemp)

#     # Générer les commandes SQL pour la configuration initiale
#     cat << EOF > $tfile
# USE mysql;
# FLUSH PRIVILEGES;

# -- Supprimer les utilisateurs anonymes
# DELETE FROM mysql.user WHERE User='';

# -- Supprimer l'accès root distant
# DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');

# -- Définir le mot de passe root
# ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';

# -- Ajouter un accès root depuis n'importe où (optionnel)
# CREATE USER 'root'@'%' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
# GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;

# -- Créer la base de données si elle n'existe pas
# CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

# -- Créer l'utilisateur pour WordPress ou autre service
# CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
# GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%';

# FLUSH PRIVILEGES;
# EOF

#     # Exécuter la configuration SQL
#     /usr/sbin/mysqld --user=mysql --bootstrap < $tfile
#     rm -f $tfile
#     echo "Base de données initialisée avec succès."
# fi

# # Démarrer MariaDB
# echo "Démarrage de MariaDB..."
# exec mysqld --user=mysql --console

#!/bin/bash

# Assurer que les répertoires existent avec les bonnes permissions
mkdir -p /var/run/mysqld /var/lib/mysql
chown -R mysql:mysql /var/run/mysqld /var/lib/mysql
chmod 777 /var/run/mysqld
chmod 755 /var/lib/mysql

echo "Vérification de l'état de la base de données..."

# Vérifier si MariaDB est déjà initialisée
if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]; then
    echo "🚀 Initialisation de MariaDB..."

    # Initialiser MariaDB si nécessaire
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null 2>&1

    echo "✅ Base de données initialisée."

    # Création d'un fichier temporaire pour les commandes SQL
    tfile=$(mktemp)
    
    cat << EOF > $tfile
USE mysql;
FLUSH PRIVILEGES;

-- Supprimer les utilisateurs anonymes
DELETE FROM mysql.user WHERE User='';

-- Supprimer l'accès root distant
DELETE FROM mysql.user WHERE User='root' AND Host NOT IN ('localhost', '127.0.0.1', '::1');

-- Définir le mot de passe root
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';

-- Ajouter un accès root depuis n'importe où (optionnel)
CREATE USER 'root'@'%' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' WITH GRANT OPTION;

-- Créer la base de données si elle n'existe pas
CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- Créer l'utilisateur pour WordPress
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%';

# -- Mettre à jour les paramètres WP_HOME et WP_SITEURL dans la table wp_options
# USE $MYSQL_DATABASE;
# INSERT INTO wp_options (option_name, option_value) VALUES ('home', '$WP_HOME') ON DUPLICATE KEY UPDATE option_value = '$WP_HOME';
# INSERT INTO wp_options (option_name, option_value) VALUES ('siteurl', '$WP_SITEURL') ON DUPLICATE KEY UPDATE option_value = '$WP_SITEURL';

FLUSH PRIVILEGES;
EOF

    # Exécuter la configuration SQL
    echo "🔄 Configuration de MariaDB..."
    /usr/sbin/mysqld --user=mysql --bootstrap < $tfile
    rm -f $tfile
    echo "✅ Configuration terminée."

else
    echo "📌 La base de données existe déjà. Aucune initialisation nécessaire."
fi

# Démarrer MariaDB en mode sûr
echo "🚀 Démarrage de MariaDB..."
exec mysqld_safe --user=mysql