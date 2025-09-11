FROM debian:bullseye

RUN apt-get update && apt-get install -y mariadb-server

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/
COPY tools/init_db.sh /usr/local/bin/

# Créer les répertoires nécessaires et définir les permissions
RUN mkdir -p /var/run/mysqld /var/lib/mysql && \
    chown -R mysql:mysql /var/run/mysqld && \
    chown -R mysql:mysql /var/lib/mysql && \
    chown -R mysql:mysql /etc/mysql && \
    chmod 777 /var/run/mysqld && \
    chmod 755 /var/lib/mysql && \
    chmod +x /usr/local/bin/init_db.sh

EXPOSE 3306

CMD ["bash", "/usr/local/bin/init_db.sh"]