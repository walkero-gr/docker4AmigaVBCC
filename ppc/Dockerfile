FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

ENV OS4_SDK="/opt/sdk/ppc-amigaos"

WORKDIR /tmp

# Install vasm
RUN curl -fsSL "http://phoenix.owl.de/tags/vasm1_9a.tar.gz" -o /tmp/vasm_1.9a.tar.gz || exit $?; \
    tar xvfz vasm_1.9a.tar.gz; \
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

RUN curl -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_target_ppc-amigaos.lha" -o /tmp/vbcc_target_ppc-amigaos.lha || exit $?; \
    curl -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz || exit $?; \
    lha -xfq2 vbcc_target_ppc-amigaos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_ppc-amigaos/targets $VBCC/; \
    rm -rf /tmp/*;

# Install AmigaOS 4 SDK
RUN curl -fksSL "https://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=127&amp;Itemid=127" -o /tmp/AmigaOS4-SDK.lha && \
    lha -xfq2 AmigaOS4-SDK.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/clib2*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/exec*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/newlib*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/base.lha && \
    rm -rf /tmp/* ${OS4_SDK}/C ${OS4_SDK}/Data ${OS4_SDK}/S ${OS4_SDK}/Tools;
ENV AOS4_SDK_INC="${OS4_SDK}/Include/include_h" \
    AOS4_NET_INC="${OS4_SDK}/Include/netinclude" \
    AOS4_NLIB="${OS4_SDK}/newlib" \
    AOS4_CLIB="${OS4_SDK}/clib2" \
    AOS4_NLIB_INC="${AOS4_NLIB}/include" \
    AOS4_CLIB_INC="${AOS4_CLIB}/include"

# Install MUI 5.0 dev
RUN curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os4.lha" -o /tmp/MUI-5.0.lha || exit $?; \
    curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os4-contrib.lha" -o /tmp/MUI-5.0-contrib.lha || exit $?; \
    lha -xfq2 MUI-5.0.lha; \
    lha -xfq2 MUI-5.0-contrib.lha; \
    mv ./SDK/MUI /opt/sdk/MUI_5.0; \
    rm -rf /tmp/*;
ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

# Install libCurl
RUN curl -fsSL "http://os4depot.net/share/development/library/misc/libcurl.lha" -o /tmp/libcurl.lha && \
    lha -xfq2 libcurl.lha && \
    cp -r ./SDK/* ${OS4_SDK}/ && \
    rm -rf /tmp/*;

# Install SQLite
RUN curl -fsSL "http://aminet.net/biz/dbase/sqlite-3.34.0-amiga.lha" -o /tmp/sqlite.lha && \
    lha -xfq2 sqlite.lha && \
    cp ./sqlite-3.34.0-amiga/build-ppc-amigaos/include/*.h ${OS4_SDK}/local/newlib/include/ && \
    cp ./sqlite-3.34.0-amiga/build-ppc-amigaos/lib/*.a ${OS4_SDK}/local/newlib/lib/ && \
    rm -rf /tmp/*;

# # Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/5.5/AmiSSL-5.5-SDK.lha" -o /tmp/AmiSSL.lha && \
    lha -xfq2 AmiSSL.lha && \
    cp ./AmiSSL/Developer/include/* ${OS4_SDK}/Include/include_h/ -r && \
    cp ./AmiSSL/Developer/Autodocs/* ${OS4_SDK}/Documentation/AutoDocs/ && \
    cp ./AmiSSL/Developer/Examples/*.c ${OS4_SDK}/Examples/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS4/clib2/*.a ${OS4_SDK}/local/clib2/lib/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS4/newlib/*.a ${OS4_SDK}/local/newlib/lib/ && \
    rm -rf /tmp/*;

USER amidev
ARG BASHFILE=/home/amidev/.bashrc
RUN sed -i '4c'"export PATH=${PATH}\n" ${BASHFILE};

WORKDIR /opt/code

USER root
RUN chown amidev:amidev /opt -R
