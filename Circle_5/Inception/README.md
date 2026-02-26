# Inception

*This project has been created as part of the 42 curriculum by vnieto-j.*

## Description

**Inception** is a system administration and DevOps project focused on containerization using Docker. The goal is to set up a complete web infrastructure consisting of multiple services running in separate Docker containers, orchestrated with Docker Compose.

The project implements:
- A WordPress website with PHP-FPM
- An NGINX web server as a reverse proxy with TLS encryption
- A MariaDB database
- Additional services: Redis cache, Adminer (database manager), FTP server, static website, and a Next.js application

All services run in isolated containers, communicate through a custom Docker network, and persist data using Docker volumes.

## Instructions

### Prerequisites

- Docker and Docker Compose installed
- Linux system (tested on Debian/Ubuntu)
- Sudo privileges (for volume management)
- Make utility

### Installation

1. **Clone the repository:**
```bash
git clone <repository-url>
cd Inception
```

2. **Configure environment variables:**
```bash
cp srcs/.env.example srcs/.env
```

Edit `srcs/.env` and set your values:
- `LOGIN`: Your 42 login
- `DOMAIN_NAME`: Your domain (e.g., `vnieto-j.42.fr`)
- Database and WordPress credentials

3. **Create secrets files:**
```bash
mkdir -p secrets
echo "your_db_root_password" > secrets/db_root_password.txt
echo "your_db_password" > secrets/db_password.txt
echo "your_wp_admin_password" > secrets/wp_admin_password.txt
echo "your_wp_user_password" > secrets/wp_user_password.txt
echo "your_ftp_password" > secrets/ftp_password.txt
```

4. **Update /etc/hosts:**
```bash
sudo nano /etc/hosts
```

Add:
```
127.0.0.1    your_login.42.fr app.your_login.42.fr
```

### Compilation & Execution

Build and start all services:
```bash
make
```

Or equivalently:
```bash
make up
```

Stop services:
```bash
make down
```

Clean containers and volumes:
```bash
make clean
```

Full cleanup (includes data):
```bash
make fclean
```

Rebuild everything:
```bash
make re
```

### Accessing Services

- **WordPress**: https://your_login.42.fr
- **Next.js App**: https://app.your_login.42.fr
- **Adminer**: http://localhost:8080
- **Static Website**: http://localhost:8081
- **FTP**: Port 2121

## Project Description

### Docker Usage

This project leverages Docker to create a microservices architecture where each service runs in its own isolated container. Docker Compose orchestrates these containers, managing their lifecycle, networking, and dependencies.

**Key containerized services:**
- **mariadb**: Database server (Debian-based)
- **wordpress**: PHP-FPM application (Debian-based)
- **nginx**: Web server and reverse proxy (Debian-based)
- **redis**: In-memory cache (Debian-based)
- **adminer**: Database management interface (Debian-based)
- **ftp**: File transfer server (Debian-based)
- **static**: Static HTML/CSS/JS website (Debian-based with nginx)
- **nextjs**: Next.js application (Node.js Alpine-based)

### Design Choices

#### Virtual Machines vs Docker

| Aspect | Virtual Machines | Docker |
|--------|------------------|--------|
| **Isolation** | Full OS isolation | Process-level isolation |
| **Resource Usage** | Heavy (GBs per VM) | Lightweight (MBs per container) |
| **Startup Time** | Minutes | Seconds |
| **Portability** | Limited | Highly portable |
| **Use Case** | Complete OS simulation | Application deployment |

**Our choice:** Docker provides faster deployment, better resource efficiency, and easier orchestration for this microservices architecture.

#### Secrets vs Environment Variables

| Aspect | Secrets | Environment Variables |
|--------|---------|----------------------|
| **Security** | Encrypted, not in logs | Visible in process list |
| **Storage** | Separate files/services | Included in config files |
| **Docker Support** | Native secrets API | Built-in support |
| **Git Safety** | Should never be committed | Risk of accidental commit |

**Our choice:** Docker secrets for sensitive data (passwords) to prevent accidental exposure. Environment variables for non-sensitive configuration (domain names, usernames).

#### Docker Network vs Host Network

| Aspect | Docker Network | Host Network |
|--------|----------------|--------------|
| **Isolation** | Network namespace isolation | Uses host's network stack |
| **DNS Resolution** | Automatic service discovery | Manual IP management |
| **Port Conflicts** | No conflicts between containers | Potential port conflicts |
| **Security** | Better isolation | Direct host exposure |

**Our choice:** Custom bridge network (`inception`) for service isolation and automatic DNS resolution (e.g., `wordpress:9000`, `mariadb:3306`).

#### Docker Volumes vs Bind Mounts

| Aspect | Docker Volumes | Bind Mounts |
|--------|----------------|-------------|
| **Management** | Docker-managed | User-managed paths |
| **Portability** | Portable across hosts | Path-dependent |
| **Performance** | Optimized by Docker | Direct filesystem access |
| **Backup** | Docker tools | Standard filesystem tools |

**Our choice:** Bind mounts to `/home/$LOGIN/data/` for easy access and backup. Data persists in a known location on the host filesystem.

### Source Files Structure

```
srcs/
├── docker-compose.yml          # Orchestration configuration
├── .env                        # Environment variables
└── requirements/
    ├── mariadb/                # Database container
    │   ├── Dockerfile
    │   ├── conf/50-server.cnf  # MariaDB configuration
    │   └── tools/entrypoint.sh # Initialization script
    ├── wordpress/              # WordPress + PHP-FPM
    │   ├── Dockerfile
    │   ├── conf/www.conf       # PHP-FPM pool config
    │   └── tools/entrypoint.sh # WP-CLI automation
    ├── nginx/                  # Web server & reverse proxy
    │   ├── Dockerfile
    │   ├── conf/nginx.conf     # Server blocks, TLS, proxying
    │   └── tools/entrypoint.sh # Cert generation, config templating
    └── bonus/
        ├── redis/              # Cache server
        ├── adminer/            # Database UI
        ├── ftp/                # FTP server (vsftpd)
        ├── static/             # Static HTML site
        └── nextjs/             # Next.js React application
```

## Resources

### Documentation & References

- **Docker Official Documentation**: https://docs.docker.com/
- **Docker Compose Reference**: https://docs.docker.com/compose/
- **NGINX Documentation**: https://nginx.org/en/docs/
- **WordPress with Docker**: https://hub.docker.com/_/wordpress (adapted for custom PHP-FPM setup)
- **MariaDB Documentation**: https://mariadb.com/kb/en/
- **Next.js Documentation**: https://nextjs.org/docs
- **PHP-FPM Configuration**: https://www.php.net/manual/en/install.fpm.php
- **Docker Secrets**: https://docs.docker.com/engine/swarm/secrets/
- **TLS/SSL with OpenSSL**: https://www.openssl.org/docs/

---

For more detailed information:
- **User documentation**: See [USER_DOC.md](USER_DOC.md)
- **Developer documentation**: See [DEV_DOC.md](DEV_DOC.md)
