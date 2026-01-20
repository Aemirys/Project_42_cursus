# Makefile Camagru

COMPOSE = docker-compose
WEB_SERVICE = web
DB_SERVICE = db

# Dossiers d'images à nettoyer
UPLOADS_DIR = web/public/uploads
THUMBS_DIR = web/public/thumbs
AVATAR_DIR = web/public/avatar

.PHONY: start up down build logs ps clean reset-images

## Build + Up
start:
	$(COMPOSE) build
	$(COMPOSE) up -d
	@echo "🚀 Application lancée (build + up)"

## Up simple
up:
	$(COMPOSE) up -d
	@echo "▶️  Containers démarrés"

## Down simple
down:
	$(COMPOSE) down
	@echo "⏹️  Containers arrêtés"

## Logs
logs:
	$(COMPOSE) logs -f

## Status
ps:
	$(COMPOSE) ps

## Nettoyage images uniquement
reset-images:
	@echo "🧹 Nettoyage des images..."
	rm -f $(UPLOADS_DIR)/*
	rm -f $(THUMBS_DIR)/*
	rm -f $(AVATAR_DIR)/*
	@echo "✅ Images supprimées"

## Clean total : containers + volumes + images
clean:
	@echo "⚠️  Nettoyage complet : containers, volumes et images"
	$(COMPOSE) down -v --rmi all
	rm -f $(UPLOADS_DIR)/*
	rm -f $(THUMBS_DIR)/*
	rm -f $(AVATAR_DIR)/*
	@echo "✅ Clean complet effectué"
