# Variables
DOCKER_COMPOSE = docker compose
PROJECT_NAME = inception
SERVICE_NGINX = nginx
SERVICE_MARIADB = mariadb
DOCKER_COMPOSE_FILE = srcs/docker-compose.yml
ENV_FILE = ./srcs/.env  # Spécifie le fichier d'environnement


# Commandes Docker
build:
	@echo "Building project..."
	@mkdir -p /home/estosche/data/mariadb
	@mkdir -p /home/estosche/data/wordpress
	chmod -R 777 /home/estosche/data
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) build

up:
	@echo "Starting project..."
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) up -d

start: build up

down:
	@echo "Stopping project..."
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) down -v

	@echo "Cleanup complete."
logs:
	@echo "Displaying logs..."
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) logs -f

restart:
	@echo "Restarting project..."
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) restart

re: down clean build up

clean:
	@echo "Cleaning up containers, volumes, and certificates..."
	$(DOCKER_COMPOSE) --env-file $(ENV_FILE) -f $(DOCKER_COMPOSE_FILE) down -v
	docker system prune -af --volumes
	docker image prune -af
	sudo rm -rf ../../data
	@echo "Cleanup complete."

# Autres tâches
install:
	@echo "Installing dependencies..."
	# Ajoutez ici les commandes pour installer des dépendances (ex: apt-get, npm, etc.)

.PHONY: build up down logs restart clean install generate-certs