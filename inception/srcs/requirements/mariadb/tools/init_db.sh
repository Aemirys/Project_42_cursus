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