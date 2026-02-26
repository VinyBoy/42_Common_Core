FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    vsftpd ca-certificates gettext-base iproute2 net-tools && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/run/vsftpd/empty \
    && chmod 755 /var/run/vsftpd/empty

COPY conf/vsftpd.conf /etc/vsftpd.conf
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 21
ENTRYPOINT [ "/usr/local/bin/entrypoint.sh" ]
CMD ["vsftpd", "/etc/vsftpd.conf"]