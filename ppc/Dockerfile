FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

WORKDIR /tmp

# Install vasm
RUN curl -fsSL "http://sun.hasenbraten.de/vasm/release/vasm.tar.gz" -o /tmp/vasm_1.9.tar.gz || exit $?; \
    tar xvfz vasm_1.9.tar.gz; \
    make -C vasm CPU=ppc SYNTAX=std; \
    cp ./vasm/vasmppc_std ./vasm/vobjdump /opt/vbcc/bin; \
    rm -rf /tmp/*;
ENV VBCC="/opt/vbcc"
ENV PATH="${VBCC}/bin:$PATH"

# Install vbcc
RUN curl -fsSL "http://phoenix.owl.de/tags/vbcc0_9hP2.tar.gz" -o /tmp/vbcc.tar.gz || exit $?; \
    tar xvfz vbcc.tar.gz; \
    mkdir -p ./vbcc/bin; \
    yes '\
' | make -C ./vbcc TARGET=ppc; \
    make -C ./vbcc TARGET=ppc bin/vscppc; \
    cp ./vbcc/bin/vbcc* ./vbcc/bin/vscppc ./vbcc/bin/vc ./vbcc/bin/vprof /opt/vbcc/bin; \
    rm -rf /tmp/*;

RUN curl -fsSL "http://server.owl.de/~frank/vbcc/2022-03-23/vbcc_target_ppc-amigaos.lha" -o /tmp/vbcc_target_ppc-amigaos.lha || exit $?; \
    curl -fsSL "http://server.owl.de/~frank/vbcc/2022-03-23/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz || exit $?; \
    lha -xfq2 vbcc_target_ppc-amigaos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_ppc-amigaos/targets $VBCC/; \
    rm -rf /tmp/*;

# Install AmigaOS 4 SDK
RUN curl -fksSL "https://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=82&amp;Itemid=82" -o /tmp/AmigaOS4-SDK.lha || exit $?; \
    lha -xfq2 AmigaOS4-SDK.lha; \
    lha -xfq2 SDK_Install/clib2*.lha; \
    lha -xfq2 SDK_Install/newlib*.lha; \
    lha -xfq2 SDK_Install/base.lha; \
    mv ./Documentation /opt/sdk/ppc-amigaos; \
    mv ./Examples /opt/sdk/ppc-amigaos; \
    mv ./Include /opt/sdk/ppc-amigaos; \
    mv ./newlib /opt/sdk/ppc-amigaos; \
    mv ./clib2 /opt/sdk/ppc-amigaos; \
    rm -rf /tmp/*;
ENV AOS4_SDK_INC="/opt/sdk/ppc-amigaos/Include/include_h"
ENV AOS4_NET_INC="/opt/sdk/ppc-amigaos/Include/netinclude"
ENV AOS4_NLIB_INC="/opt/sdk/ppc-amigaos/newlib/include"
ENV AOS4_CLIB_INC="/opt/sdk/ppc-amigaos/clib2/include"

# Install MUI 5.0 dev
RUN curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os4.lha" -o /tmp/MUI-5.0.lha || exit $?; \
    curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os4-contrib.lha" -o /tmp/MUI-5.0-contrib.lha || exit $?; \
    lha -xfq2 MUI-5.0.lha; \
    lha -xfq2 MUI-5.0-contrib.lha; \
    mv ./SDK/MUI /opt/sdk/MUI_5.0; \
    rm -rf /tmp/*;
ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

# Install libCurl
# RUN curl -fsSL "http://os4depot.net/share/development/library/misc/libcurl.lha" -o /tmp/libcurl.lha || exit $?; \
#
#     lha -xfq2 libcurl.lha; \
#     mv ./SDK/Local /opt/sdk/libcurl; \
#     rm -rf /tmp/*;

# Install SQLite
RUN curl -fsSL "http://aminet.net/biz/dbase/sqlite-3.34.0-amiga.lha" -o /tmp/sqlite.lha || exit $?; \
    lha -xfq2 sqlite.lha; \
    mkdir -p /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-ppc-amigaos/include/ /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-ppc-amigaos/lib/ /opt/sdk/sqlite/; \
    rm -rf /tmp/*;
ENV SQLITE_INC="/opt/sdk/sqlite/include"

USER amidev
ARG BASHFILE=/home/amidev/.bashrc
RUN sed -i '4c'"export PATH=${PATH}\n" ${BASHFILE};

WORKDIR /opt/code

USER root
RUN chown amidev:amidev /opt -R
