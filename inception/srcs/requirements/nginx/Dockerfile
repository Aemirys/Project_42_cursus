FROM debian:bullseye

RUN apt-get update && apt-get install -y nginx openssl

# Configuration SSL
RUN mkdir -p /etc/nginx/ssl
RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt \
    -subj "/C=FR/ST=IDF/L=Paris/O=42/CN=estosche.42.fr"

# COPY conf/nginx.conf /etc/nginx/conf.d/nginx.conf
COPY conf/default /etc/nginx/sites-available/.

RUN chmod 755 /var/www/html
RUN chown -R www-data:www-data /var/www/html

EXPOSE 443

CMD ["nginx", "-g", "daemon off;"]