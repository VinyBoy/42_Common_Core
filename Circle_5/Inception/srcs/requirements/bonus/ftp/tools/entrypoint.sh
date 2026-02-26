#!/bin/bash
set -euo pipefail

: "${FTP_USER:?FTP_USER missing}"

FTP_SECRET_PATH="${FTP_SECRET_PATH:-/run/secrets/ftp_password}"

if [ ! -f "$FTP_SECRET_PATH" ]; then
  echo "ERROR: missing secret $FTP_SECRET_PATH"
  ls -la /run/secrets || true
  exit 1
fi

FTP_PASS="$(cat "$FTP_SECRET_PATH")"

# Create user if missing
if ! id "$FTP_USER" >/dev/null 2>&1; then
  useradd -m -d "/home/${FTP_USER}" -s /bin/bash "$FTP_USER"
else
  # Si le user existe déjà, on force un shell valide au cas où
  usermod -s /bin/bash "$FTP_USER" || true
fi

# Always apply password (même si user existe déjà)
echo "${FTP_USER}:${FTP_PASS}" | chpasswd

# Permissions for FTP volume
mkdir -p /home/${FTP_USER}/ftp
chown -R "${FTP_USER}:${FTP_USER}" /home/${FTP_USER}/ftp || true
chmod -R 755 /home/${FTP_USER}/ftp\

# mkdir -p /var/www/html
# chown -R "${FTP_USER}:${FTP_USER}" /var/www/html || true

envsubst < /etc/vsftpd.conf > /etc/vsftpd.conf.rendered

exec vsftpd /etc/vsftpd.conf.rendered
