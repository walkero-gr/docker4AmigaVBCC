FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

ENV OS4_SDK="/opt/sdk/ppc-amigaos"

WORKDIR /tmp

# Install vasm
RUN curl -fsSL "http://phoenix.owl.de/tags/vasm2_0a.tar.gz" -o /tmp/vasm.tar.gz || exit $?; \
    tar xvfz vasm.tar.gz; \
    make -C vasm CPU=ppc SYNTAX=std; \
    cp ./vasm/vasmppc_std ./vasm/vobjdump /opt/vbcc/bin; \
    rm -rf /tmp/*;
ENV VBCC="/opt/vbcc"
ENV PATH="${VBCC}/bin:$PATH"

# Install vbcc
RUN curl -fsSL "http://phoenix.owl.de/tags/vbcc0_9hP3.tar.gz" -o /tmp/vbcc.tar.gz || exit $?; \
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
RUN curl -fskSL "https://www.hyperion-entertainment.com/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=127&amp;Itemid=127" -o /tmp/AmigaOS4-SDK.lha && \
    lha -xfq2 AmigaOS4-SDK.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/clib2*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/exec*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/newlib*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/base.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/pthreads*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/SDI-*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/cairo-*.lha && \
    lha -xfq2w=${OS4_SDK} SDK_Install/expat-*.lha && \
    cp -r ${OS4_SDK}/Examples/Locale/include/internal/* ${OS4_SDK}/Include/include_h/ && \
    cp -r ${OS4_SDK}/Local/* ${OS4_SDK}/local/ && \
    rm -rf ${OS4_SDK}/Local ${OS4_SDK}/C ${OS4_SDK}/Data ${OS4_SDK}/S \
        ${OS4_SDK}/AmigaOS\ 4.1\ SDK.pdf.info \
        ${OS4_SDK}/Documentation.info && \
    rm -rf /tmp/*;

    # Necessary links
RUN ln -s ${OS4_SDK}/clib2/lib/libamiga.a 	${OS4_SDK}/newlib/lib/ && \
    ln -s ${OS4_SDK}/clib2/lib/libamiga.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/clib2/lib/libamiga.a 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/clib2/lib/libdebug.a 	${OS4_SDK}/newlib/lib/ && \
    ln -s ${OS4_SDK}/clib2/lib/libdebug.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/clib2/lib/libdebug.a 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/crtbegin.o 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/crtend.o 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/crtend.o 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/libauto.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/libauto.a 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/libc.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/libm.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/libm.a 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/librauto.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/librauto.a 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/libsocket.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/libsocket.a 	${OS4_SDK}/newlib/lib/small-data/ && \
    ln -s ${OS4_SDK}/newlib/lib/libunix.a 	${OS4_SDK}/newlib/lib/baserel/ && \
    ln -s ${OS4_SDK}/newlib/lib/libunix.a 	${OS4_SDK}/newlib/lib/small-data/;

ENV AOS4_SDK_INC="${OS4_SDK}/Include/include_h" \
    AOS4_NET_INC="${OS4_SDK}/Include/netinclude" \
    AOS4_NLIB="${OS4_SDK}/newlib" \
    AOS4_CLIB="${OS4_SDK}/clib2"
ENV AOS4_NLIB_INC="${AOS4_NLIB}/include" \
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
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/5.19/AmiSSL-5.19-SDK.lha" -o /tmp/AmiSSL.lha && \
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
