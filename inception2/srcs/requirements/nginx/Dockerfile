# FROM debian:bullseye

# # Mise à jour et installation des paquets nécessaires
# RUN apt update && apt install -y \
#     openssl \
#     nginx

# # Création des répertoires pour les certificats SSL
# RUN mkdir -p /etc/nginx/ssl/

# COPY conf/inception.conf /etc/nginx/ssl
# # Génération des certificats SSL (auto-signés ici)
# RUN openssl req -x509 -nodes \
#     -out /etc/nginx/ssl/cert.crt \
#     -keyout /etc/nginx/ssl/cert.key \
#     -subj "/C=FR/ST=IDF/L=Paris/O=42/CN=estosche.42.fr"\
#     -config /etc/nginx/ssl/inception.conf


# # Définir les bonnes permissions pour les certificats
# RUN chmod 644 /etc/nginx/ssl/cert.crt /etc/nginx/ssl/cert.key

# # Copier la configuration Nginx (nginx.conf) dans le conteneur
# COPY ./conf/nginx.conf /etc/nginx/nginx.conf

# RUN chmod 755 /var/www/html
# RUN chown -R www-data:www-data /var/www/html

# # Exposer le port 80 et 443 pour HTTPS
# EXPOSE 8443

# # Commande pour démarrer nginx en mode premier plan (pas en background)
# CMD ["nginx", "-g", "daemon off;"]

FROM debian:bullseye

RUN apt-get update && apt-get install -y nginx openssl

# Configuration SSL
RUN mkdir -p /etc/nginx/ssl
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/CN=estosche.42.fr"

# COPY conf/nginx.conf /etc/nginx/conf.d/default.conf
# COPY conf/nginx.conf /etc/nginx/nginx.conf

COPY conf/default /etc/nginx/sites-available/.

RUN chmod 755 /var/www/html
RUN chown -R www-data:www-data /var/www/html

# COPY conf/default /etc/nginx/sites-available/.

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]