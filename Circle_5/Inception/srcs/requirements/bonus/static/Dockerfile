FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends nginx ca-certificates \
 && rm -rf /var/lib/apt/lists/*

COPY conf/default.conf /etc/nginx/sites-available/default

COPY website/ /usr/share/nginx/html/

EXPOSE 80
CMD ["nginx", "-g", "daemon off;"]