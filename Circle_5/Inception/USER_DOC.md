# User Documentation - Inception

This guide explains how to use the Inception platform as an end user or system administrator.

## What is Inception?

Inception is a complete web infrastructure that provides:

- **WordPress Website**: A full-featured content management system
- **Next.js Application**: A modern web application framework
- **Database Management**: Adminer interface for database administration
- **Static Website**: A simple HTML/CSS/JS site
- **FTP Access**: File transfer capability for managing website files
- **Redis Cache**: Performance optimization for WordPress

## Starting and Stopping the Project

### Start All Services

From the project root directory:

```bash
make
```

or

```bash
make up
```

**What happens:**
- Creates data directories if they don't exist
- Builds Docker images (first time only)
- Starts all containers in detached mode
- Services are ready in 30-60 seconds

**Expected output:**
```
🚀 Inception is up
```

### Stop All Services

To stop without removing data:

```bash
make down
```

**What happens:**
- Stops all running containers
- Keeps volumes and data intact
- Can be restarted without data loss

**Expected output:**
```
🛑 Inception stopped
```

### Check Running Services

To see which services are running:

```bash
make ps
```

You should see 8 containers running:
- `mariadb`
- `wordpress`
- `nginx`
- `redis`
- `adminer`
- `ftp`
- `static`
- `nextjs`

## Accessing the Services

### WordPress Website

**URL:** https://your_login.42.fr (e.g., https://vnieto-j.42.fr)

**Note:** Your browser will show a security warning because we use a self-signed certificate. Click "Advanced" → "Proceed to site" (or equivalent in your browser).

**What you can do:**
- View and read blog posts
- Create an account (if registration is enabled)
- Comment on posts (if logged in)

### WordPress Admin Panel

**URL:** https://your_login.42.fr/wp-admin

**Credentials:**
- Username: Value of `WP_ADMIN_USER` from `.env` file
- Password: Content of `secrets/wp_admin_password.txt`

**What you can do:**
- Create and edit posts
- Manage users
- Install themes and plugins
- Configure site settings
- Manage media files

### Next.js Application

**URL:** https://app.your_login.42.fr (e.g., https://app.vnieto-j.42.fr)

A modern web application built with Next.js and React.

### Adminer (Database Management)

**URL:** http://localhost:8080

**Login credentials:**
- System: `MySQL`
- Server: `mariadb`
- Username: Value of `MYSQL_USER` from `.env` file
- Password: Content of `secrets/db_password.txt`
- Database: Value of `MYSQL_DATABASE` from `.env` file (usually `wordpress`)

**What you can do:**
- Browse database tables
- Execute SQL queries
- Export/import database
- View WordPress data structure

**⚠️ Warning:** Be careful when modifying the database directly. Always backup before making changes.

### Static Website

**URL:** http://localhost:8081

A simple static HTML website for demonstration purposes.

### FTP Access

**Connection details:**
- Host: `localhost` or `your_login.42.fr`
- Port: `2121`
- Username: Value of `FTP_USER` from `.env` file
- Password: Content of `secrets/ftp_password.txt`
- Protocol: FTP (passive mode)

**What you can do:**
- Upload files to WordPress directory
- Download backups
- Manage website files

**Using FileZilla or command line:**
```bash
ftp -p localhost 2121
```

## Managing Credentials

### Where Credentials are Stored

All sensitive credentials are stored in the `secrets/` directory:

```
secrets/
├── db_root_password.txt      # MariaDB root password
├── db_password.txt            # WordPress database user password
├── wp_admin_password.txt      # WordPress admin password
├── wp_user_password.txt       # WordPress regular user password
└── ftp_password.txt           # FTP user password
```

### Viewing Credentials

To see a password:

```bash
cat secrets/db_password.txt
```

### Changing Passwords

**⚠️ Important:** Changing passwords requires recreating the services.

1. Stop the services:
```bash
make down
```

2. Edit the secret file:
```bash
echo "new_password" > secrets/wp_admin_password.txt
```

3. For database passwords, you need to rebuild:
```bash
make fclean
make
```

4. For WordPress passwords, you can change them via the admin panel after logging in.

### Non-Sensitive Configuration

Other configuration values are in `srcs/.env`:

```bash
cat srcs/.env
```

Example values:
- `LOGIN`: Your 42 login
- `DOMAIN_NAME`: Your domain name
- `MYSQL_DATABASE`: Database name
- `MYSQL_USER`: Database username
- `WP_TITLE`: Website title
- `WP_ADMIN_USER`: Admin username
- `WP_ADMIN_EMAIL`: Admin email

## Checking Service Health

### Quick Health Check

Run:
```bash
make ps
```

All services should show `Up` status.

### View Live Logs

To see logs from all services:

```bash
make logs
```

To follow logs in real-time (press `Ctrl+C` to exit):

```bash
docker compose -f srcs/docker-compose.yml logs -f
```

To view logs for a specific service:

```bash
docker logs nginx
docker logs wordpress
docker logs mariadb
```

### Test Web Services

**Check WordPress:**
```bash
curl -kI https://vnieto-j.42.fr
```

Expected: `HTTP/2 200` or `HTTP/2 301`

**Check Next.js:**
```bash
curl -kI https://app.vnieto-j.42.fr
```

Expected: `HTTP/2 200`

**Check Adminer:**
```bash
curl -I http://localhost:8080
```

Expected: `HTTP/1.1 200 OK`

### Database Connection Test

Enter MariaDB container:

```bash
docker exec -it mariadb mysql -u root -p
```

Enter the root password from `secrets/db_root_password.txt`.

Check databases:
```sql
SHOW DATABASES;
USE wordpress;
SHOW TABLES;
EXIT;
```

### Redis Cache Test

Check if Redis is running:

```bash
docker exec -it redis redis-cli ping
```

Expected output: `PONG`

Check cache statistics:
```bash
docker exec -it redis redis-cli INFO stats
```

## Troubleshooting

### Service Won't Start

**Check logs:**
```bash
docker logs <service_name>
```

**Common issues:**
- Port already in use (stop conflicting services)
- Insufficient disk space
- Invalid credentials in secret files

### Can't Access Website

1. **Check /etc/hosts:**
```bash
grep "42.fr" /etc/hosts
```

Should contain:
```
127.0.0.1    vnieto-j.42.fr app.vnieto-j.42.fr
```

2. **Check nginx is running:**
```bash
docker ps | grep nginx
```

3. **Test with curl:**
```bash
curl -kI https://vnieto-j.42.fr
```

### WordPress Shows "Error Establishing Database Connection"

1. **Wait 30 seconds** (MariaDB might still be initializing)

2. **Check MariaDB logs:**
```bash
docker logs mariadb
```

3. **Verify credentials match** between `.env` and `secrets/db_password.txt`

### FTP Connection Fails

1. **Check FTP container is running:**
```bash
docker ps | grep ftp
```

2. **Verify passive ports are available:**
```bash
netstat -tlnp | grep 21
```

3. **Use passive mode** in your FTP client

### Permission Denied on Data Directories

Data directories need proper permissions:

```bash
sudo chmod -R 755 /home/vnieto-j/data
sudo chown -R vnieto-j:vnieto-j /home/vnieto-j/data
```

## Data Backup

### Backup WordPress Files

```bash
sudo tar -czf wordpress-backup-$(date +%Y%m%d).tar.gz /home/vnieto-j/data/wordpress/
```

### Backup Database

```bash
docker exec mariadb mysqldump -u root -p$(cat secrets/db_root_password.txt) wordpress > wordpress-db-backup-$(date +%Y%m%d).sql
```

### Restore Database

```bash
docker exec -i mariadb mysql -u root -p$(cat secrets/db_root_password.txt) wordpress < wordpress-db-backup-20260210.sql
```

## Maintenance Mode

To perform maintenance:

1. Stop services:
```bash
make down
```

2. Perform maintenance (backups, updates, etc.)

3. Restart:
```bash
make up
```

## Getting Help

If you encounter issues:

1. Check this documentation
2. Review logs: `make logs`
3. Check individual service: `docker logs <service>`
4. Refer to [DEV_DOC.md](DEV_DOC.md) for technical details
5. Verify all prerequisites are met in [README.md](README.md)
