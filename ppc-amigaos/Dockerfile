FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

WORKDIR /tmp

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

ENV VBCC="/opt/vbcc"
ENV PATH="${VBCC}/bin:$PATH"

ENV SDK_PATH="/opt/sdk/ppc-amigaos"
ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

COPY ./scripts /scripts
RUN chmod +x /scripts/* -R && bash /scripts/setup-sdk.sh;\
    chown amidev:amidev /opt -R; \
    \
    sed -i '4c'"export PATH=${PATH}\n" /home/amidev/.bashrc;

WORKDIR /opt/code
