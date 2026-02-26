# Developer Documentation - Inception

This guide explains how to set up, build, and maintain the Inception project from a developer's perspective.

## Table of Contents

1. [Environment Setup](#environment-setup)
2. [Project Structure](#project-structure)
3. [Building the Project](#building-the-project)
4. [Container Management](#container-management)
5. [Volume Management](#volume-management)
6. [Network Architecture](#network-architecture)
7. [Service Details](#service-details)
8. [Development Workflow](#development-workflow)
9. [Debugging](#debugging)

## Environment Setup

### Prerequisites

Install required software:

```bash
# Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo usermod -aG docker $USER
# Log out and back in for group changes to take effect

# Docker Compose (if not included)
sudo apt-get update
sudo apt-get install docker-compose-plugin

# Make (usually pre-installed)
sudo apt-get install make
```

Verify installations:

```bash
docker --version          # Should be 20.10+
docker compose version    # Should be 2.0+
make --version
```

### Initial Configuration

1. **Clone and enter project:**
```bash
git clone <repository-url>
cd Inception
```

2. **Create environment file:**
```bash
cp srcs/.env.example srcs/.env
```

3. **Edit `.env` with your values:**
```bash
nano srcs/.env
```

Required variables:
```bash
LOGIN=your_42_login              # Your 42 login (for data paths)
DOMAIN_NAME=your_login.42.fr     # Your domain name

# Database
MYSQL_DATABASE=wordpress         # WordPress database name
MYSQL_USER=wpuser               # Database user (not root)

# WordPress
WP_TITLE=Inception              # Site title
WP_ADMIN_USER=admin_user        # Admin username
WP_ADMIN_EMAIL=admin@your_login.42.fr

WP_USER=player                  # Regular user
WP_USER_EMAIL=player@your_login.42.fr

# FTP
FTP_USER=ftpuser                # FTP username
PASV_ADDRESS=127.0.0.1          # FTP passive mode address
PASV_MIN_PORT=21100             # Passive port range start
PASV_MAX_PORT=21110             # Passive port range end
```

4. **Create secrets:**
```bash
mkdir -p secrets

# Generate strong passwords (or use your own)
openssl rand -base64 32 > secrets/db_root_password.txt
openssl rand -base64 32 > secrets/db_password.txt
openssl rand -base64 32 > secrets/wp_admin_password.txt
openssl rand -base64 32 > secrets/wp_user_password.txt
openssl rand -base64 32 > secrets/ftp_password.txt

# Set proper permissions
chmod 600 secrets/*
```

5. **Configure hosts file:**
```bash
sudo nano /etc/hosts
```

Add (replace with your login):
```
127.0.0.1    vnieto-j.42.fr app.vnieto-j.42.fr
```

6. **Create data directories:**
```bash
sudo mkdir -p /home/$USER/data/{mariadb,wordpress}
sudo chown -R $USER:$USER /home/$USER/data
```

## Project Structure

```
Inception/
├── Makefile                    # Build automation
├── secrets/                    # Sensitive credentials (gitignored)
│   ├── db_root_password.txt
│   ├── db_password.txt
│   ├── wp_admin_password.txt
│   ├── wp_user_password.txt
│   └── ftp_password.txt
└── srcs/
    ├── .env                    # Environment variables (gitignored)
    ├── docker-compose.yml      # Service orchestration
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── 50-server.cnf
        │   └── tools/
        │       └── entrypoint.sh
        ├── wordpress/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── www.conf
        │   └── tools/
        │       └── entrypoint.sh
        ├── nginx/
        │   ├── Dockerfile
        │   ├── conf/
        │   │   └── nginx.conf
        │   └── tools/
        │       └── entrypoint.sh
        └── bonus/
            ├── adminer/
            ├── redis/
            ├── ftp/
            ├── static/
            └── nextjs/
```

## Building the Project

### Using Makefile (Recommended)

The Makefile provides convenient commands:

```bash
make           # Build and start (same as 'make up')
make up        # Build images and start containers
make down      # Stop containers (keep data)
make clean     # Stop containers and remove volumes
make fclean    # Full cleanup (removes data directories)
make re        # Rebuild everything from scratch
make ps        # Show running containers
make logs      # View all logs
```

### Using Docker Compose Directly

Equivalent Docker Compose commands:

```bash
# Build and start
docker compose -f srcs/docker-compose.yml --env-file srcs/.env up -d --build

# Stop services
docker compose -f srcs/docker-compose.yml down

# Remove volumes
docker compose -f srcs/docker-compose.yml down -v

# View logs
docker compose -f srcs/docker-compose.yml logs -f

# Rebuild specific service
docker compose -f srcs/docker-compose.yml build --no-cache nginx
docker compose -f srcs/docker-compose.yml up -d nginx
```

### Build Process Explained

1. **Image Building:**
   - Each service has its own Dockerfile
   - Built from Debian Bookworm (stable) or Alpine Linux
   - Multi-stage builds used for Next.js (smaller final image)

2. **Dependency Order:**
   ```
   mariadb (independent)
     ↓
   wordpress (depends on mariadb)
     ↓
   nginx (depends on wordpress)
   
   redis (independent)
   adminer (depends on mariadb)
   ftp (independent)
   static (independent)
   nextjs (depends on mariadb)
   ```

3. **First Build:**
   - Takes 3-5 minutes
   - Downloads base images
   - Installs packages
   - Caches layers for faster rebuilds

4. **Subsequent Builds:**
   - Uses cache (30-60 seconds)
   - Only rebuilds changed layers

## Container Management

### Viewing Container Status

```bash
# All containers
docker ps -a

# Specific service
docker ps -a | grep nginx

# With formatting
docker ps --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}"
```

### Accessing Containers

```bash
# Interactive shell
docker exec -it mariadb bash
docker exec -it wordpress bash
docker exec -it nginx sh

# Execute single command
docker exec mariadb ps aux
docker exec wordpress wp --info --allow-root

# As specific user
docker exec -u www-data wordpress wp plugin list --allow-root
```

### Container Logs

```bash
# View logs
docker logs nginx
docker logs -f wordpress          # Follow mode
docker logs --tail 50 mariadb     # Last 50 lines
docker logs --since 5m wordpress  # Last 5 minutes

# All services
docker compose -f srcs/docker-compose.yml logs

# Specific service
docker compose -f srcs/docker-compose.yml logs nginx
```

### Restarting Containers

```bash
# Single container
docker restart nginx

# All containers
docker compose -f srcs/docker-compose.yml restart

# Specific service rebuild
docker compose -f srcs/docker-compose.yml up -d --build --no-deps nginx
```

### Removing Containers

```bash
# Stop and remove all
docker compose -f srcs/docker-compose.yml down

# Remove specific container
docker rm -f nginx

# Remove all stopped containers
docker container prune
```

## Volume Management

### Understanding Volumes

```yaml
volumes:
  mariadb_data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/${LOGIN}/data/mariadb

  wordpress_data:
    driver: local
    driver_opts:
      type: none
      o: bind
      device: /home/${LOGIN}/data/wordpress
```

These are **bind mounts** - they link host directories to container paths.

### Inspecting Volumes

```bash
# List volumes
docker volume ls

# Inspect volume
docker volume inspect inception_mariadb_data

# Check host directory
ls -lah /home/$USER/data/mariadb/
ls -lah /home/$USER/data/wordpress/
```

### Data Persistence

**MariaDB data** (`/home/$USER/data/mariadb/`):
- Database files
- Transaction logs
- System tables

**WordPress data** (`/home/$USER/data/wordpress/`):
- WordPress core files
- Themes and plugins
- Uploaded media (wp-content/uploads/)
- Configuration (wp-config.php)

### Backup Volumes

```bash
# Backup MariaDB data
sudo tar -czf backup-mariadb-$(date +%Y%m%d).tar.gz /home/$USER/data/mariadb/

# Backup WordPress data
sudo tar -czf backup-wordpress-$(date +%Y%m%d).tar.gz /home/$USER/data/wordpress/

# Backup database content
docker exec mariadb mysqldump -u root -p$(cat secrets/db_root_password.txt) --all-databases > backup-db-$(date +%Y%m%d).sql
```

### Restore Volumes

```bash
# Stop services
make down

# Restore data
sudo tar -xzf backup-mariadb-20260210.tar.gz -C /

# Restart services
make up
```

### Clean Volumes

```bash
# Remove unused volumes
docker volume prune

# Full cleanup (including data)
make fclean
```

## Network Architecture

### Network Configuration

```yaml
networks:
  inception:
    name: inception
    driver: bridge
```

### Network Inspection

```bash
# List networks
docker network ls

# Inspect network
docker network inspect inception

# See connected containers
docker network inspect inception | grep Name
```

### Container Communication

Services communicate via **service names** as hostnames:

```bash
# From wordpress container:
ping mariadb        # Reaches MariaDB container
ping redis          # Reaches Redis container

# DNS resolution handled by Docker
docker exec wordpress getent hosts mariadb
```

### Port Mapping

| Service | Internal Port | External Port | Protocol |
|---------|--------------|---------------|----------|
| nginx | 80, 443 | 80, 443 | HTTP/HTTPS |
| adminer | 8080 | 8080 | HTTP |
| static | 80 | 8081 | HTTP |
| ftp | 2121, 21100-21110 | 2121, 21100-21110 | FTP |
| mariadb | 3306 | Not exposed | MySQL |
| wordpress | 9000 | Not exposed | PHP-FPM |
| redis | 6379 | Not exposed | Redis |
| nextjs | 3000 | Not exposed | HTTP |

### Testing Network Connectivity

```bash
# Enter a container
docker exec -it wordpress bash

# Test connectivity
apt-get update && apt-get install -y iputils-ping telnet

# Ping another service
ping -c 3 mariadb

# Check if port is open
telnet mariadb 3306
telnet redis 6379

# Curl internal services
curl wordpress:9000
curl nextjs:3000
```

## Service Details

### MariaDB

**Base image:** `debian:bookworm-slim`

**Purpose:** MySQL-compatible database server

**Key files:**
- `conf/50-server.cnf`: Server configuration (bind address, charset)
- `tools/entrypoint.sh`: Initialization script (creates database, users)

**Initialization:**
1. Starts MySQL temporarily
2. Creates database from `$MYSQL_DATABASE`
3. Creates user from `$MYSQL_USER` with password from secret
4. Grants privileges
5. Sets root password from secret
6. Stops temporary MySQL
7. Starts MySQL normally

**Manual database access:**
```bash
docker exec -it mariadb mysql -u root -p
# Enter password from secrets/db_root_password.txt
```

### WordPress

**Base image:** `debian:bookworm-slim`

**Purpose:** PHP-FPM running WordPress

**Key files:**
- `conf/www.conf`: PHP-FPM pool configuration
- `tools/entrypoint.sh`: WordPress installation and configuration

**Initialization:**
1. Waits for MariaDB to be ready
2. Downloads WordPress if not present
3. Creates `wp-config.php` with database credentials
4. Installs WordPress via WP-CLI
5. Creates admin user and regular user
6. Configures Redis object cache
7. Starts PHP-FPM

**WP-CLI commands:**
```bash
docker exec wordpress wp --allow-root plugin list
docker exec wordpress wp --allow-root theme list
docker exec wordpress wp --allow-root user list
docker exec wordpress wp --allow-root cache flush
```

### Nginx

**Base image:** `debian:bookworm-slim`

**Purpose:** Web server and reverse proxy

**Key files:**
- `conf/nginx.conf`: Server blocks for WordPress and Next.js
- `tools/entrypoint.sh`: SSL certificate generation and config templating

**Configuration features:**
- TLS 1.2/1.3 with self-signed certificates
- HTTP to HTTPS redirect
- FastCGI proxy to WordPress PHP-FPM
- Reverse proxy to Next.js
- Static file caching
- Two server blocks:
  - `${DOMAIN_NAME}` → WordPress
  - `app.${DOMAIN_NAME}` → Next.js

**Testing config:**
```bash
docker exec nginx nginx -t            # Test configuration
docker exec nginx nginx -s reload     # Reload without restart
```

### Redis

**Base image:** `debian:bookworm-slim`

**Purpose:** In-memory cache for WordPress

**Integration:** WordPress uses Redis Object Cache plugin (configured in entrypoint)

**Testing:**
```bash
docker exec redis redis-cli ping
docker exec redis redis-cli KEYS '*'
docker exec redis redis-cli INFO stats
```

### Adminer

**Base image:** `debian:bookworm-slim`

**Purpose:** Web-based database management

**Access:** http://localhost:8080

**Single-file PHP application running under PHP built-in server**

### FTP

**Base image:** `debian:bookworm-slim`

**Purpose:** VSFTPD server for file access to WordPress volume

**Key config:**
- Passive mode (required for containerized FTP)
- Chrooted to `/var/www/html`
- User created from `$FTP_USER` and secret

### Static

**Base image:** `debian:bookworm-slim`

**Purpose:** Simple nginx serving static HTML/CSS/JS

**Content:** Basic webpage in `website/` directory

### Next.js

**Base image:** `node:20-alpine` (multi-stage build)

**Purpose:** Next.js React application

**Build stages:**
1. **Builder stage:** Install deps, copy code, run `npm run build`
2. **Production stage:** Copy built artifacts, run `npm start`

**Environment:** Database connection configured for potential future features

## Development Workflow

### Making Changes

1. **Modify service configuration:**
```bash
# Edit Dockerfile or config files
nano srcs/requirements/nginx/conf/nginx.conf
```

2. **Rebuild specific service:**
```bash
docker compose -f srcs/docker-compose.yml build nginx
docker compose -f srcs/docker-compose.yml up -d nginx
```

3. **Test changes:**
```bash
docker logs nginx
curl -kI https://vnieto-j.42.fr
```

### Adding a New Service

1. Create service directory:
```bash
mkdir -p srcs/requirements/bonus/myservice/{conf,tools}
```

2. Create Dockerfile:
```Dockerfile
FROM debian:bookworm-slim
RUN apt-get update && apt-get install -y mypackage
COPY conf/myconfig.conf /etc/myservice/
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
EXPOSE 8080
ENTRYPOINT ["/entrypoint.sh"]
CMD ["myservice"]
```

3. Add to `docker-compose.yml`:
```yaml
services:
  myservice:
    container_name: myservice
    image: myservice
    build:
      context: ./requirements/bonus/myservice
    networks:
      - inception
    restart: unless-stopped
```

4. Build and test:
```bash
make re
```

### Updating Dependencies

```bash
# Rebuild without cache
docker compose -f srcs/docker-compose.yml build --no-cache wordpress

# Pull latest base images
docker pull debian:bookworm-slim
docker pull node:20-alpine

# Rebuild all
make re
```

## Debugging

### Service Won't Start

```bash
# Check logs
docker logs <service_name>

# Check if port is in use
ss -tlnp | grep :443

# Verify dependencies
docker ps | grep mariadb
```

### Database Connection Issues

```bash
# Check MariaDB is running
docker exec mariadb mysqladmin -u root -p$(cat secrets/db_root_password.txt) ping

# Test connection from WordPress container
docker exec wordpress mysqladmin -h mariadb -u $MYSQL_USER -p$(cat secrets/db_password.txt) ping

# Check database exists
docker exec mariadb mysql -u root -p$(cat secrets/db_root_password.txt) -e "SHOW DATABASES;"
```

### Network Issues

```bash
# Inspect network
docker network inspect inception

# Check DNS resolution
docker exec wordpress getent hosts mariadb

# Test connectivity
docker exec wordpress ping -c 3 mariadb
```

### Volume Permission Issues

```bash
# Check ownership
ls -la /home/$USER/data/

# Fix permissions
sudo chown -R $USER:$USER /home/$USER/data/
sudo chmod -R 755 /home/$USER/data/
```

### SSL Certificate Issues

```bash
# Regenerate certificates
docker exec nginx rm -rf /etc/nginx/ssl/*
docker restart nginx

# Check certificate
docker exec nginx openssl x509 -in /etc/nginx/ssl/vnieto-j.42.fr.crt -text -noout
```

### Clean Slate Rebuild

When everything is broken:

```bash
# Nuclear option - complete reset
make fclean
docker system prune -a --volumes
rm -rf /home/$USER/data/*

# Rebuild from scratch
make
```

### Performance Issues

```bash
# Check resource usage
docker stats

# Check disk space
df -h
docker system df

# Clean unused resources
docker system prune
```

## Useful Commands Cheat Sheet

```bash
# Build & Start
make                                          # Start everything
make down                                     # Stop everything
make re                                       # Rebuild from scratch

# Monitoring
docker ps                                     # Running containers
docker stats                                  # Resource usage
make logs                                     # All logs

# Container Access
docker exec -it <container> bash              # Interactive shell
docker exec <container> <command>             # Run command

# logs
docker logs <container>                       # View logs
docker logs -f <container>                    # Follow logs

# Network
docker network ls                             # List networks
docker network inspect inception              # Network details

# Volumes
docker volume ls                              # List volumes
ls -lah /home/$USER/data/                     # Check data

# Cleanup
docker system prune                           # Clean unused
docker system prune -a --volumes              # Nuclear cleanup
make fclean                                   # Project cleanup

# Database
docker exec -it mariadb mysql -u root -p      # MySQL root
docker exec wordpress wp --allow-root ...     # WP-CLI

# Rebuild Single Service
docker compose -f srcs/docker-compose.yml build --no-cache nginx
docker compose -f srcs/docker-compose.yml up -d nginx
```

## Contributing

When modifying the project:

1. Test changes locally
2. Update documentation if needed
3. Ensure `make fclean && make` works
4. Check all services are healthy
5. Commit with clear messages

## Additional Resources

- **Docker Documentation**: https://docs.docker.com/
- **Docker Compose Reference**: https://docs.docker.com/compose/compose-file/
- **Nginx Documentation**: https://nginx.org/en/docs/
- **MariaDB Knowledge Base**: https://mariadb.com/kb/en/
- **WordPress Developer Resources**: https://developer.wordpress.org/
- **WP-CLI Documentation**: https://wp-cli.org/
- **Next.js Documentation**: https://nextjs.org/docs
