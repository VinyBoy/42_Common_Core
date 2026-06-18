NAME    := $(shell awk -F= '/^COMPOSE_PROJECT_NAME=/{print $$2}' srcs/.env 2>/dev/null | tr -d '\r')
ifeq ($(strip $(NAME)),)
NAME := transcendance
endif

# --- Compose ---
COMPOSE_FILE := srcs/docker-compose.yml
ENV_FILE     := srcs/.env
COMPOSE      := docker compose -f $(COMPOSE_FILE) --env-file $(ENV_FILE) -p $(NAME)



# --- Detect Docker mode (rootless/rootful) ---
DOCKER_HOST_ROOTLESS := $(shell echo "$(DOCKER_HOST)" | grep -q "^unix:///run/user/" && echo 1 || echo 0)
ROOTLESS_SOCKET := $(shell [ -S "/run/user/$(shell id -u)/docker.sock" ] && echo 1 || echo 0)
ROOTLESS_INFO := $(shell docker info 2>/dev/null | grep -qi 'rootless' && echo 1 || echo 0)
ROOTLESS := $(shell [ "$(DOCKER_HOST_ROOTLESS)" = "1" -o "$(ROOTLESS_SOCKET)" = "1" -o "$(ROOTLESS_INFO)" = "1" ] && echo 1 || echo 0)

UID      := $(shell id -u)

# --- Docker sockets ---
DOCKER_SOCK_ROOTFUL  := /var/run/docker.sock
DOCKER_SOCK_ROOTLESS := /run/user/$(UID)/docker.sock

# --- Choose socket depending on rootless mode ---
ifeq ($(ROOTLESS),1)
  DOCKER_MODE := rootless
  DOCKER_SOCK := $(DOCKER_SOCK_ROOTLESS)
else
  DOCKER_MODE := rootful
  DOCKER_SOCK_ACCESSIBLE := $(shell [ -r "$(DOCKER_SOCK_ROOTFUL)" ] && echo 1 || echo 0)
  ifeq ($(DOCKER_SOCK_ACCESSIBLE),0)
    $(warning ⚠️  Docker socket $(DOCKER_SOCK_ROOTFUL) not accessible. Add yourself to docker group: sudo usermod -aG docker $$USER)
  endif
  DOCKER_SOCK := $(DOCKER_SOCK_ROOTFUL)
endif

# --- Ports (portable by default: >= 1024) ---
# You can override: `make up TRAEFIK_HTTP_PORT=8081 TRAEFIK_HTTPS_PORT=8443`
TRAEFIK_HTTP_PORT      ?= $(shell awk -F= '/^TRAEFIK_HTTP_PORT=/{print $$2}' $(ENV_FILE) 2>/dev/null | tr -d '\r')
TRAEFIK_HTTPS_PORT     ?= 8443
TRAEFIK_DASHBOARD_PORT ?= $(shell awk -F= '/^TRAEFIK_DASHBOARD_PORT=/{print $$2}' $(ENV_FILE) 2>/dev/null | tr -d '\r')

ifeq ($(strip $(TRAEFIK_HTTP_PORT)),)
TRAEFIK_HTTP_PORT := 8081
endif
ifeq ($(strip $(TRAEFIK_DASHBOARD_PORT)),)
TRAEFIK_DASHBOARD_PORT := 8080
endif

# --- App host from .env (fallback app.localhost) ---
APP_HOST ?= $(shell awk -F= '/^APP_HOST=/{print $$2}' $(ENV_FILE) 2>/dev/null | tr -d '\r')
ifeq ($(strip $(APP_HOST)),)
APP_HOST := app.localhost
endif

# --- Traefik certs paths (under srcs/) ---
TRAEFIK_DIR := srcs/infra/traefik
CERT_DIR    := $(TRAEFIK_DIR)/certs
CERT_CRT    := $(CERT_DIR)/local.crt
CERT_KEY    := $(CERT_DIR)/local.key

# --- Common export for compose (so docker-compose.yml sees them) ---
# We pass vars inline to avoid relying on .env for dynamic values.
define COMPOSE_ENV
DOCKER_SOCK="$(DOCKER_SOCK)" \
TRAEFIK_HTTP_PORT="$(TRAEFIK_HTTP_PORT)" \
TRAEFIK_HTTPS_PORT="$(TRAEFIK_HTTPS_PORT)" \
TRAEFIK_DASHBOARD_PORT="$(TRAEFIK_DASHBOARD_PORT)"
endef

all: up

help:
	@echo "Targets:"
	@echo "  up            Build & run stack (generates local TLS certs if needed)"
	@echo "  down          Stop stack"
	@echo "  restart       down + up"
	@echo "  ps            List containers"
	@echo "  logs          Follow logs"
	@echo "  logs-app      Follow app logs"
	@echo "  logs-traefik  Follow traefik logs"
	@echo "  logs-postgres Follow postgres logs"
	@echo "  health        Curl /api/healthz through Traefik (HTTP)"
	@echo "  health-https  Curl /api/healthz through Traefik (HTTPS, -k)"
	@echo "  routers       List Traefik routers via dashboard API"
	@echo "  prismastudio  Launch Prisma Studio in the nextjs container"
	@echo "  doctor        Diagnostic Docker socket & permissions"
	@echo "  clean         Down + remove volumes/orphans"
	@echo "  fclean        clean + delete local data + prune"
	@echo ""
	@echo "Variables (override on CLI):"
	@echo "  TRAEFIK_HTTP_PORT=8081"
	@echo "  TRAEFIK_HTTPS_PORT=8443"
	@echo "  TRAEFIK_DASHBOARD_PORT=8080"
	@echo "  APP_HOST=app.localhost"
	@echo ""
	@echo "Detected:"
	@echo "  project=$(NAME)"
	@echo "  mode=$(DOCKER_MODE)"
	@echo "  socket=$(DOCKER_SOCK)"

certs:
	@mkdir -p $(CERT_DIR)
	@if [ ! -f "$(CERT_CRT)" ] || [ ! -f "$(CERT_KEY)" ]; then \
		echo "🔐 Generating local TLS certs for $(APP_HOST) ..."; \
		openssl req -x509 -newkey rsa:2048 -sha256 -days 365 -nodes \
			-keyout "$(CERT_KEY)" \
			-out "$(CERT_CRT)" \
			-subj "/CN=$(APP_HOST)" >/dev/null 2>&1; \
		echo "✅ TLS certs created:"; \
		echo "   - $(CERT_CRT)"; \
		echo "   - $(CERT_KEY)"; \
	else \
		echo "✅ TLS certs already exist."; \
	fi

# --- Main ---
up: certs
	@bash -c "source $$HOME/.nvm/nvm.sh && nvm install 22 && nvm use 22 && nvm alias default 22"
	@npm install --prefix ./srcs/nextjs --no-audit --no-fund
	@npx --prefix ./srcs/nextjs prisma generate --schema=./srcs/nextjs/prisma/schema.prisma
	@mkdir -p srcs/data/backups
	@echo "🐳 Docker mode: $(DOCKER_MODE)"
	@echo "🔌 Docker socket: $(DOCKER_SOCK)"
	@echo "🌐 App URL (HTTP):  http://$(APP_HOST):$(TRAEFIK_HTTP_PORT)"
	@echo "🔒 App URL (HTTPS): https://$(APP_HOST):$(TRAEFIK_HTTPS_PORT)"
	@echo "📊 Traefik dashboard: http://localhost:$(TRAEFIK_DASHBOARD_PORT)"
	@$(COMPOSE_ENV) $(COMPOSE) up -d --build
	@echo "⏳ Attente que les services soient prêts..."
	@$(COMPOSE_ENV) $(COMPOSE) exec -T traefik sh -c 'for i in 1 2 3 4 5 6 7 8 9 10; do test -S /var/run/docker.sock && echo "✓ Socket accessible" && break || echo "✗ Socket check $$i/10" && sleep 1; done' 2>/dev/null || echo "⚠️  Socket warning (peut être ignoré si les conteneurs démarrent)"
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20; do \
		$(COMPOSE) ps | grep -q "(healthy)" && $(COMPOSE) ps | grep -q nextjs && $(COMPOSE) ps | grep -q postgres && echo "✅ $(NAME) is up" && exit 0 || true; \
		echo "⏳ $$i/20 - En attente de l'état healthy..."; \
		sleep 1; \
	done; \
	echo "⚠️  Services démarrés mais certains ne sont peut-être pas encore healthy"

down:
	@$(COMPOSE) down
	@echo "🛑 $(NAME) stopped"

restart: down up

ps:
	@$(COMPOSE) ps

logs:
	@$(COMPOSE) logs -f --tail=200

logs-app:
	@$(COMPOSE) logs -f --tail=200 nextjs

logs-traefik:
	@$(COMPOSE) logs -f --tail=200 traefik

logs-postgres:
	@$(COMPOSE) logs -f --tail=200 postgres

health:
	@echo "==> Health via Traefik HTTP (Host: $(APP_HOST))"
	@curl -i --max-time 5 "http://localhost:$(TRAEFIK_HTTP_PORT)/api/healthz" -H 'Host: $(APP_HOST)' || true
	@echo ""
	@echo "==> Containers:"
	@$(COMPOSE) ps

health-https:
	@echo "==> Health via Traefik HTTPS (Host: $(APP_HOST))"
	@curl -k -i --max-time 5 "https://localhost:$(TRAEFIK_HTTPS_PORT)/api/healthz" -H 'Host: $(APP_HOST)' || true
	@echo ""
	@echo "==> Containers:"
	@$(COMPOSE) ps

prismastudio:
	@echo "🚀 Launching Prisma Studio..."
	@$(COMPOSE) exec -d nextjs sh -c 'export POSTGRES_PASSWORD=$$(cat /run/secrets/postgres_password); export DATABASE_URL="postgresql://$${DATABASE_USER}:$${POSTGRES_PASSWORD}@$${DATABASE_HOST}:$${DATABASE_PORT}/$${DATABASE_NAME}"; HOST=0.0.0.0 npx prisma studio --port 5555 --browser none'
	@echo "📊 Prisma Studio is running at http://localhost:5555"

routers:
	@echo "==> Traefik routers (dashboard API)"
	@curl -s "http://localhost:$(TRAEFIK_DASHBOARD_PORT)/api/http/routers" | head -n 200
	@echo ""
	@echo "Tip: if you only see api@internal/dashboard@internal => Traefik doesn't see Docker (bad socket)."

doctor:
	@echo "🔍 Docker Configuration Diagnostic"
	@echo ""
	@echo "1️⃣  Docker Mode Detection:"
	@echo "   Mode: $(DOCKER_MODE)"
	@echo "   Socket: $(DOCKER_SOCK)"
	@echo ""
	@echo "2️⃣  Socket Files:"
	@ls -la /var/run/docker.sock 2>/dev/null && echo "   ✓ Rootful socket found" || echo "   ✗ Rootful socket not found"
	@ls -la /run/user/$(UID)/docker.sock 2>/dev/null && echo "   ✓ Rootless socket found" || echo "   ✗ Rootless socket not found"
	@echo ""
	@echo "3️⃣  User & Groups:"
	@echo "   User: $(shell whoami) (UID=$(UID))"
	@groups | grep -q docker && echo "   ✓ User is in docker group" || echo "   ✗ User NOT in docker group (run: sudo usermod -aG docker $$USER && newgrp docker)"
	@echo ""
	@echo "4️⃣  Docker Access Test:"
	@docker ps >/dev/null 2>&1 && echo "   ✓ Docker command works" || echo "   ✗ Docker command FAILS"
	@echo ""
	@echo "5️⃣  Traefik Container Check:"
	@$(COMPOSE) ps 2>/dev/null | grep -q traefik && echo "   ✓ Traefik container is running" || echo "   ✗ Traefik container NOT running"
	@if $(COMPOSE) ps 2>/dev/null | grep -q traefik; then \
		$(COMPOSE_ENV) $(COMPOSE) exec traefik ls -la /var/run/docker.sock 2>/dev/null && echo "   ✓ Socket mounted in Traefik" || echo "   ✗ Socket NOT mounted in Traefik"; \
		$(COMPOSE_ENV) $(COMPOSE) exec traefik test -r /var/run/docker.sock 2>/dev/null && echo "   ✓ Socket readable by Traefik" || echo "   ✗ Socket NOT readable by Traefik"; \
	fi
	@echo ""
	@echo "6️⃣  Container Health:"
	@$(COMPOSE) ps 2>/dev/null || echo "   ✗ Cannot list containers"

clean:
	@$(COMPOSE) down -v --remove-orphans
	@echo "🧹 Containers, volumes & orphans removed"

fclean: clean
	@docker system prune -af --volumes
	@echo "🔥 All data & images deleted"

re: fclean all

.PHONY: all help certs up down restart ps logs logs-app logs-traefik logs-postgres health health-https routers prismastudio doctor clean fclean re