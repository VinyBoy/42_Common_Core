NAME    = inception
COMPOSE    = docker compose -f srcs/docker-compose.yml

DATA_DIR = /home/vnieto-j/data
MDB_DIR  = $(DATA_DIR)/mariadb
WP_DIR   = $(DATA_DIR)/wordpress
FTP_DIR  = $(DATA_DIR)/ftp

all: up

up:
	@mkdir -p $(MDB_DIR) $(WP_DIR) $(FTP_DIR)
	@$(COMPOSE) up -d --build
	@echo "🚀 Inception is up"

down:
	@$(COMPOSE) down
	@echo "🛑 Inception stopped"

clean:
	@$(COMPOSE) down -v
	@echo "🧹 Containers & volumes removed"

fclean: clean
	@sudo rm -rf $(DATA_DIR)
	@echo "🔥 All data deleted"

re: fclean all

ps:
	@$(COMPOSE) ps

logs:
	@$(COMPOSE) logs

.PHONY: all up down clean fclean re ps logs