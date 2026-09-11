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

ENV NDK39_PATH="/opt/sdk/NDK_3.9"
ENV NDK_INC="${NDK39_PATH}/Include/include_h" \
    NDK_LIB="${NDK39_PATH}/Include/linker_libs"

ENV MUI38_INC="/opt/sdk/MUI_3.8/C/Include"
ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

ENV SQLITE_INC="/opt/sdk/sqlite/include"

COPY ./scripts /scripts
RUN chmod +x /scripts/* -R && bash /scripts/setup-sdk.sh;\
    chown amidev:amidev /opt -R; \
    \
    sed -i '4c'"export PATH=${PATH}\n" /home/amidev/.bashrc;

WORKDIR /opt/code
