FROM phusion/baseimage:resolute

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

ENV CCRED="\033[31m" \
    CCGREEN="\033[32m" \
    CCYELLOW="\033[33m" \
    CCBLUE="\033[34m" \
    CCPINK="\033[35m" \
    CCLBLUE="\033[36m" \
    CCEND="\033[0m" \
    CCBOLD="\033[1m" \
    CCITAL="\033[3m" \
    CCUNDR="\033[4m"

ENV AMIDEV_USER_ID=1000 \
    AMIDEV_GROUP_ID=1000

COPY --from=walkero/lha-on-docker /usr/bin/lha /usr/bin/lha
COPY scripts/setup-tools.sh /setup-tools.sh
COPY scripts/setup-user.sh /setup-user.sh

RUN chmod +x /setup-tools.sh && /setup-tools.sh && \
    chmod +x /setup-user.sh && /setup-user.sh

WORKDIR /opt/code
