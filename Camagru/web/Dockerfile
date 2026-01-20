FROM php:8.2-fpm

# =========================
# System dependencies
# =========================
RUN apt-get update && apt-get install -y \
    libpng-dev \
    libjpeg62-turbo-dev \
    libfreetype6-dev \
    libzip-dev \
    zip \
    unzip \
    git \
    libonig-dev \
    libicu-dev \
    libxml2-dev \
    gnupg2 \
    default-mysql-client \
 && docker-php-ext-configure gd --with-freetype --with-jpeg \
 && docker-php-ext-install -j$(nproc) \
    gd \
    pdo \
    pdo_mysql \
    mbstring \
    zip \
    intl \
    opcache \
 && pecl install xdebug-3.1.6 || true \
 && docker-php-ext-enable xdebug || true \
 && apt-get clean \
 && rm -rf /var/lib/apt/lists/*

RUN docker-php-ext-install fileinfo || true

WORKDIR /var/www/html

# =========================
# PHP configuration
# =========================
COPY php.ini /usr/local/etc/php/php.ini

# =========================
# Upload & images directories
# =========================
RUN mkdir -p \
    /var/www/html/public/uploads \
    /var/www/html/public/uploads/avatar \
    /var/www/html/public/thumbs \
 && chown -R www-data:www-data /var/www/html/public \
 && chmod -R 755 /var/www/html/public

# =========================
# Composer & PHPMailer
# =========================
RUN curl -sS https://getcomposer.org/installer | php \
 && php composer.phar require phpmailer/phpmailer \
 && mv composer.phar /usr/local/bin/composer


EXPOSE 9000

CMD ["php-fpm"]