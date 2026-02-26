#Build stage
FROM node:20-alpine AS builder
WORKDIR /app

# 1 - Install dependances
COPY app/package*.json ./
RUN npm ci

#2 - Copier le code puis build
COPY app/ .
RUN npm run build

# Run stage
FROM node:20-alpine
WORKDIR /app
ENV NODE_ENV=production

COPY --from=builder /app/package*.json ./
COPY --from=builder /app/node_modules ./node_modules
COPY --from=builder /app/.next ./.next
COPY --from=builder /app/public ./public
COPY --from=builder /app/next.config* ./2>/dev/null

#entrypoint
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

EXPOSE 3000
ENTRYPOINT ["/entrypoint.sh"]
CMD ["npm", "run", "start"]