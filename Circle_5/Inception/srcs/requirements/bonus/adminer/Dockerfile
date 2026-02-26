FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    ca-certificates curl php-cli php-mysqli php-mbstring \ 
    && rm -rf /var/lib/apt/lists/*

#Dl adminer
RUN mkdir -p /var/www/html \
 && curl -fLsS -o /var/www/html/adminer.php https://www.adminer.org/latest.php \
 && head -n 1 /var/www/html/adminer.php | grep -q '^<?php' \
 && printf '%s\n' '<?php require __DIR__ . "/adminer.php";' > /var/www/html/index.php


COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh

RUN chmod +x /usr/local/bin/entrypoint.sh 

EXPOSE 8080
ENTRYPOINT ["/usr/local/bin/entrypoint.sh"]
CMD ["php", "-S", "0.0.0.0:8080", "-t", "/var/www/html"]