FROM debian:bullseye

RUN apt-get update && apt-get install -y \
    php7.4-fpm \
    php7.4-mysql \
    php7.4-curl \
    php7.4-gd \
    php7.4-intl \
    php7.4-mbstring \
    php7.4-soap \
    php7.4-xml \
    php7.4-xmlrpc \
    php7.4-zip \
    curl \
    wget \
    mariadb-client

# Installation de WordPress CLI
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Configuration de PHP-FPM
# RUN sed -i 's/listen = \/run\/php\/php7.4-fpm.sock/listen = 9000/g' /etc/php/7.4/fpm/pool.d/www.conf \
#     && sed -i 's/;clear_env = no/clear_env = no/g' /etc/php/7.4/fpm/pool.d/www.conf

COPY ./conf/www.conf /etc/php/7.4/fpm/pool.d/
RUN chmod 644 /etc/php/7.4/fpm/pool.d/www.conf


COPY tools/wp-config.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/wp-config.sh

RUN apt-get update && apt-get install -y sendmail

WORKDIR /var/www/html

EXPOSE 9000

CMD ["bash", "/usr/local/bin/wp-config.sh"]