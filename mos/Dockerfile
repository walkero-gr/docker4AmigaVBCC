FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

WORKDIR /tmp

# Install vasm
RUN curl -fsSL "http://phoenix.owl.de/tags/vasm1_9e.tar.gz" -o /tmp/vasm.tar.gz || exit $?; \
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

RUN curl -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_target_ppc-morphos.lha" -o /tmp/vbcc_target_ppc-morphos.lha || exit $?; \
    curl -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz || exit $?; \
    lha -xfq2 vbcc_target_ppc-morphos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_ppc-morphos/targets $VBCC/; \
    rm -rf /tmp/*;
ENV PATH="$VBCC/bin:$PATH"

# Install NDK39
RUN curl -fsSL "http://hp.alinea-computer.de/AmigaOS/NDK39.lha" -o /tmp/NDK39.lha || exit $?; \
    lha -xfq2 NDK39.lha; \
    mv ./NDK_3.9 /opt/sdk/; \
    rm -rf /tmp/*;
ENV NDK39_PATH="/opt/sdk/NDK_3.9"
ENV NDK_INC="${NDK39_PATH}/Include/include_h"
ENV NDK_LIB="${NDK39_PATH}/Include/linker_libs"

# Install MorphOS SDK
# RUN curl -fksSL "https://www.morphos-team.net/files/sdk-20200422.lha" -o /tmp/MorphOS-SDK.lha || exit $?; \
#
#     lha -xfq2 MorphOS-SDK.lha; \
#     cd morphossdk; \
#     tar -xJf sdk.pack; \
#     cd Development/gg; \
#     mkdir -p /opt/sdk/morphos; \
#     mv ./include /opt/sdk/morphos/include; \
#     mv ./includestd /opt/sdk/morphos/includestd; \
#     mv ./lib /opt/sdk/morphos/lib; \
#     mv ./os-include /opt/sdk/morphos/os-include; \
#     mv ./ppc-morphos /opt/sdk/morphos/ppc-morphos;

# ENV MOS_SDK_INC="/opt/sdk/morphos/include"
# ENV MOS_SDK_STD="/opt/sdk/morphos/includestd"
# ENV MOS_OS_INC="/opt/sdk/morphos/os-include"

# Install MUI 3.8 dev
RUN curl -fsSL "http://muidev.de/download/MUI%203.8%20-%20AmigaOS3-m68k/mui38dev.lha" -o /tmp/mui38dev.lha || exit $?; \
    lha -xfq2 mui38dev.lha; \
    mv ./MUI/Developer /opt/sdk/MUI_3.8; \
    mkdir -p /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;
ENV MUI38_INC="/opt/sdk/MUI_3.8/C/Include"

# Install MUI 5.0 dev
RUN curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os3.lha" -o /tmp/MUI-5.0.lha || exit $?; \
    curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os3-contrib.lha" -o /tmp/MUI-5.0-contrib.lha || exit $?; \
    lha -xfq2 MUI-5.0.lha; \
    lha -xfq2 MUI-5.0-contrib.lha; \
    mv ./SDK/MUI /opt/sdk/MUI_5.0; \
    rm -rf /tmp/*;
ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

# Install MCC_GuiGfx
RUN curl -fsSL "http://aminet.net/dev/mui/MCC_Guigfx.lha" -o /tmp/MCC_Guigfx.lha || exit $?; \
    lha -xfq2 MCC_Guigfx.lha; \
    cp ./MCC_Guigfx/Developer/C/Include/MUI/* /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

# Install MCC_TextEditor
RUN curl -fsSL "http://aminet.net/dev/mui/MCC_TextEditor-15.56.lha" -o /tmp/MCC_TextEditor.lha || exit $?; \
    lha -xfq2 MCC_TextEditor.lha; \
    cp ./MCC_TextEditor/Developer/C/include/mui/* /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

# Install SQLite
RUN curl -fsSL "http://aminet.net/biz/dbase/sqlite-3.34.0-amiga.lha" -o /tmp/sqlite.lha || exit $?; \
    lha -xfq2 sqlite.lha; \
    mkdir -p /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-ppc-morphos/include/ /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-ppc-morphos/lib/ /opt/sdk/sqlite/; \
    rm -rf /tmp/*;
ENV SQLITE_INC="/opt/sdk/sqlite/include"

# Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/5.8/AmiSSL-5.8-SDK.lha" -o /tmp/AmiSSL.lha && \
    lha -xfq2 AmiSSL.lha && \
    cp ./AmiSSL/Developer/include/* ${NDK39_PATH}/Include/include_h/ -r && \
    cp ./AmiSSL/Developer/Autodocs/* ${NDK39_PATH}/Documentation/Autodocs/ && \
    cp ./AmiSSL/Developer/Examples/*.c ${NDK39_PATH}/Examples/ && \
    cp ./AmiSSL/Developer/fd/* ${NDK39_PATH}/Include/fd/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS3/* ${NDK39_PATH}/Include/linker_libs/ && \
    cp ./AmiSSL/Developer/sfd/* ${NDK39_PATH}/Include/sfd/ && \
    rm -rf /tmp/*;

# Install SDI headers
RUN curl -fsSL "http://aminet.net/dev/c/SDI_headers.lha" -o /tmp/SDI_headers.lha || exit $?; \
    lha -xfq2 SDI_headers.lha && \
    mkdir ${NDK39_PATH}/Examples/SDI && \
    cp -r ./SDI/includes/* ${NDK39_PATH}/Include/include_h/ && \
    cp -r ./SDI/examples/* ${NDK39_PATH}/Examples/SDI/ && \
    rm -rf /tmp/*;

USER amidev
ARG BASHFILE=/home/amidev/.bashrc
RUN sed -i '4c'"export PATH=${PATH}\n" ${BASHFILE};

WORKDIR /opt/code

USER root
RUN chown amidev:amidev /opt -R
