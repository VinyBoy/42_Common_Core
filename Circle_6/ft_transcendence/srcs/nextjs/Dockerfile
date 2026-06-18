FROM node:20-alpine

WORKDIR /app

RUN apk add --no-cache curl tzdata

# Copier les manifests pour profiter du cache Docker
COPY package*.json ./

# Prisma a besoin du schema/config pendant "npm ci" (postinstall -> prisma generate)
COPY prisma.config.ts ./
COPY prisma ./prisma

# ✅ Fournir un DATABASE_URL factice uniquement le temps du build
# (Prisma veut juste une valeur valide à parser pour generate)
RUN DATABASE_URL="postgresql://user:pass@localhost:5432/db?schema=public" npm ci --no-audit --no-fund

# Copier tout le code source de l'application
COPY . .
COPY entrypoint.sh .

RUN chmod +x entrypoint.sh

EXPOSE 3000

ENTRYPOINT ["sh", "/app/entrypoint.sh"]
CMD ["npm", "run", "dev", "--", "-H", "0.0.0.0", "-p", "3000"]