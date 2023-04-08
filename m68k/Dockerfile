FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

WORKDIR /tmp

# Install vasm
RUN curl -fsSL "http://phoenix.owl.de/tags/vasm1_9a.tar.gz" -o /tmp/vasm_1.9a.tar.gz || exit $?; \
    tar xvfz vasm_1.9a.tar.gz; \
    make -C vasm CPU=m68k SYNTAX=mot; \
    cp ./vasm/vasmm68k_mot ./vasm/vobjdump /opt/vbcc/bin; \
    rm -rf /tmp/*;
ENV VBCC="/opt/vbcc"
ENV PATH="${VBCC}/bin:$PATH"

# Install vbcc
RUN curl -fsSL "http://phoenix.owl.de/tags/vbcc0_9hP2.tar.gz" -o /tmp/vbcc.tar.gz || exit $?; \
    tar xvfz vbcc.tar.gz; \
    mkdir -p ./vbcc/bin; \
    yes '\
' | make -C ./vbcc TARGET=m68k; \
    yes '\
' | make -C ./vbcc TARGET=m68ks; \
    cp ./vbcc/bin/vbcc* ./vbcc/bin/vc ./vbcc/bin/vprof /opt/vbcc/bin; \
    rm -rf /tmp/*;

RUN curl -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_target_m68k-amigaos.lha" -o /tmp/vbcc_target_m68k-amigaos.lha || exit $?; \
    curl -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz || exit $?; \
    lha -xfq2 vbcc_target_m68k-amigaos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_m68k-amigaos/targets $VBCC/; \
    rm -rf /tmp/*;

# Install NDK39
RUN curl -fsSL "http://hp.alinea-computer.de/AmigaOS/NDK39.lha" -o /tmp/NDK39.lha || exit $?; \
    lha -xfq2 NDK39.lha; \
    mv ./NDK_3.9 /opt/sdk/; \
    rm -rf /tmp/*;
ENV NDK_INC="/opt/sdk/NDK_3.9/Include/include_h"
ENV NDK_LIB="/opt/sdk/NDK_3.9/Include/linker_libs"

# Install NDK32
RUN curl -fsSL "http://aminet.net/dev/misc/NDK3.2.lha" -o /tmp/ndk32.lha || exit $?; \
    lha -xfq2w=NDK3.2 ndk32.lha; \
    mv ./NDK3.2 /opt/sdk/; \
    rm -rf /tmp/*;
ENV NDK32_INC="/opt/sdk/NDK3.2/Include_H"
ENV NDK32_LIB="/opt/sdk/NDK3.2/lib"

# Install MUI 3.8 dev
RUN curl -fsSL "https://github.com/amiga-mui/muidev/releases/download/3.8/mui38dev.lha" -o /tmp/mui38dev.lha || exit $?; \
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

# Install Roadshow SDK
RUN curl -fsSL "http://amiga-projects.net/Roadshow-SDK.lha" -o /tmp/Roadshow-SDK.lha || exit $?; \
    lha -xfq2w=Roadshow-SDK Roadshow-SDK.lha; \
    mv ./Roadshow-SDK /opt/sdk/Roadshow-SDK; \
    rm -rf /tmp/*;
ENV TCP_INC="/opt/sdk/Roadshow-SDK/include"
ENV NET_INC="/opt/sdk/Roadshow-SDK/netinclude"

# Install Posix Lib
RUN curl -fsSL "http://aminet.net/dev/c/vbcc_PosixLib.lha" -o /tmp/vbcc_PosixLib.lha || exit $?; \
    lha -xfq2 vbcc_PosixLib.lha; \
    mkdir -p /opt/sdk/PosixLib/; \
    mv ./PosixLib/include/ /opt/sdk/PosixLib/; \
    rm -rf /tmp/*;
ENV POSIXLIB_INC="/opt/sdk/PosixLib/include"

# Install SQLite
RUN curl -fsSL --retry 5 "http://aminet.net/biz/dbase/sqlite-3.34.0-amiga.lha" -o /tmp/sqlite.lha || exit $?; \
    lha -xfq2 sqlite.lha; \
    mkdir -p /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-m68k-amigaos/include/ /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-m68k-amigaos/lib/ /opt/sdk/sqlite/; \
    rm -rf /tmp/*;
ENV SQLITE_INC="/opt/sdk/sqlite/include"

# Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/5.5/AmiSSL-5.5-SDK.lha" -o /tmp/AmiSSL.lha && \
    lha -xfq2 AmiSSL.lha && \
    cp ./AmiSSL/Developer/include/* /opt/sdk/NDK3.2/Include_H/ -r && \
    cp ./AmiSSL/Developer/Autodocs/* /opt/sdk/NDK3.2/Autodocs/ && \
    cp ./AmiSSL/Developer/Examples/*.c /opt/sdk/NDK3.2/Examples/ && \
    cp ./AmiSSL/Developer/fd/* /opt/sdk/NDK3.2/FD/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS3/* /opt/sdk/NDK3.2/lib/ && \
    cp ./AmiSSL/Developer/sfd/* /opt/sdk/NDK3.2/SFD/ && \
    cp ./AmiSSL/Developer/include/* /opt/sdk/NDK_3.9/Include/include_h/ -r && \
    cp ./AmiSSL/Developer/Autodocs/* /opt/sdk/NDK_3.9/Documentation/Autodocs/ && \
    cp ./AmiSSL/Developer/Examples/*.c /opt/sdk/NDK_3.9/Examples/ && \
    cp ./AmiSSL/Developer/fd/* /opt/sdk/NDK_3.9/Include/fd/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS3/* /opt/sdk/NDK_3.9/Include/linker_libs/ && \
    cp ./AmiSSL/Developer/sfd/* /opt/sdk/NDK_3.9/Include/sfd/ && \
    rm -rf /tmp/*;

USER amidev
ARG BASHFILE=/home/amidev/.bashrc
RUN sed -i '4c'"export PATH=${PATH}\n" ${BASHFILE};

WORKDIR /opt/code

USER root
RUN chown amidev:amidev /opt -R
