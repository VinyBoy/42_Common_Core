#!/bin/sh
set -e

echo "🚀 Starting FT_Transcendence Next.js entrypoint..."

# Wait for postgres to be ready
until nc -z ${DATABASE_HOST:-postgres} ${DATABASE_PORT:-5432}; do
  echo "⏳ Waiting for postgres at ${DATABASE_HOST:-postgres}:${DATABASE_PORT:-5432}..."
  sleep 1
done

echo "✅ Postgres is ready. Synchronizing database schema..."

# Build DATABASE_URL from secrets
export POSTGRES_PASSWORD=$(cat /run/secrets/postgres_password)
export DATABASE_URL="postgresql://${DATABASE_USER}:${POSTGRES_PASSWORD}@${DATABASE_HOST:-postgres}:${DATABASE_PORT:-5432}/${DATABASE_NAME:-transcendence}"

# Check for new dependencies
echo "📦 Synchronizing dependencies in container..."
npm install

# Prisma sync
npx prisma generate
npx prisma db push --accept-data-loss

echo "🎉 Database synchronized! Starting application..."

# Execute CMD (npm run dev)
exec "$@"
