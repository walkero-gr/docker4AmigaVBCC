FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Install vasm
RUN curl -fsSL "http://sun.hasenbraten.de/vasm/release/vasm.tar.gz" -o /tmp/vasm_1.8j.tar.gz; \
    cd /tmp; \
    tar xvfz vasm_1.8j.tar.gz; \
    cd /tmp/vasm; \
    make CPU=m68k SYNTAX=mot; \
    cp ./vasmm68k_mot ./vobjdump /opt/vbcc/bin; \
    rm -rf /tmp/*;

ENV VBCC="/opt/vbcc"
ENV PATH="${VBCC}/bin:$PATH"

# Install vbcc
RUN curl -fsSL "http://www.ibaug.de/vbcc/vbcc.tar.gz" -o /tmp/vbcc.tar.gz; \
    cd /tmp; \
    tar xvfz vbcc.tar.gz; \
    cd /tmp/vbcc; \
    mkdir bin; \
    yes '\
' | make TARGET=m68k; \
    yes '\
' | make TARGET=m68ks; \
    cp ./bin/vbcc* ./bin/vc ./bin/vprof /opt/vbcc/bin; \
    rm -rf /tmp/*;

RUN curl -fsSL "http://server.owl.de/~frank/vbcc/2019-10-04/vbcc_target_m68k-amigaos.lha" -o /tmp/vbcc_target_m68k-amigaos.lha; \
    curl -fsSL "http://server.owl.de/~frank/vbcc/2019-10-04/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz; \
    cd /tmp; \
    lha -xfq2 vbcc_target_m68k-amigaos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_m68k-amigaos/targets $VBCC/; \
    rm -rf /tmp/*;

# Install NDK39
RUN curl -fsSL "http://www.haage-partner.de/download/AmigaOS/NDK39.lha" -o /tmp/NDK39.lha; \
    cd /tmp; \
    lha -xfq2 NDK39.lha; \
    mv ./NDK_3.9 /opt/sdk/; \
    rm -rf /tmp/*;

ENV NDK_INC="/opt/sdk/NDK_3.9/Include/include_h"
ENV NDK_LIB="/opt/sdk/NDK_3.9/Include/linker_libs"

# Install NDK32
RUN curl -fsSL "https://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=123&amp;Itemid=123" -o /tmp/ndk32.lha; \
    cd /tmp; \
    lha -xfq2 ndk32.lha; \
    mv ./NDK3.2 /opt/sdk/; \
    rm -rf /tmp/*;

ENV NDK32_INC="/opt/sdk/NDK3.2/Include_H"
ENV NDK32_LIB="/opt/sdk/NDK3.2/lib"

# Install MUI 3.8 dev
RUN curl -fsSL "http://muidev.de/download/MUI%203.8%20-%20AmigaOS3-m68k/mui38dev.lha" -o /tmp/mui38dev.lha; \
    cd /tmp; \
    lha -xfq2 mui38dev.lha; \
    mv ./MUI/Developer /opt/sdk/MUI_3.8; \
    mkdir -p /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

ENV MUI38_INC="/opt/sdk/MUI_3.8/C/Include"

# Install MUI 5.0 dev
RUN curl -fsSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2020R3-os3.lha" -o /tmp/MUI-5.0.lha; \
    curl -fsSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2020R3-os3-contrib.lha" -o /tmp/MUI-5.0-contrib.lha; \
    cd /tmp; \
    lha -xfq2 MUI-5.0.lha; \
    lha -xfq2 MUI-5.0-contrib.lha; \
    mv ./SDK/MUI /opt/sdk/MUI_5.0; \
    rm -rf /tmp/*;

ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

# Install MCC_GuiGfx
RUN curl -fsSL "http://aminet.net/dev/mui/MCC_Guigfx.lha" -o /tmp/MCC_Guigfx.lha; \
    cd /tmp; \
    lha -xfq2 MCC_Guigfx.lha; \
    cp ./MCC_Guigfx/Developer/C/Include/MUI/* /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

# Install MCC_TextEditor
RUN curl -fsSL "http://aminet.net/dev/mui/MCC_TextEditor-15.55.lha" -o /tmp/MCC_TextEditor.lha; \
    cd /tmp; \
    lha -xfq2 MCC_TextEditor.lha; \
    cp ./MCC_TextEditor/Developer/C/include/mui/* /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

# Install Roadshow SDK
RUN curl -fsSL "http://amiga-projects.net/Roadshow-SDK.lha" -o /tmp/Roadshow-SDK.lha; \
    cd /tmp; \
    lha -xfq2w=Roadshow-SDK Roadshow-SDK.lha; \
    mv ./Roadshow-SDK /opt/sdk/Roadshow-SDK; \
    rm -rf /tmp/*;

ENV TCP_INC="/opt/sdk/Roadshow-SDK/include"
ENV NET_INC="/opt/sdk/Roadshow-SDK/netinclude"

# Install Posix Lib
RUN curl -fsSL "http://aminet.net/dev/c/vbcc_PosixLib.lha" -o /tmp/vbcc_PosixLib.lha; \
    cd /tmp; \
    lha -xfq2 vbcc_PosixLib.lha; \
    mkdir -p /opt/sdk/PosixLib/; \
    mv ./PosixLib/include/ /opt/sdk/PosixLib/; \
    rm -rf /tmp/*;

ENV POSIXLIB_INC="/opt/sdk/PosixLib/include"

WORKDIR /tmp

# Install SQLite
RUN curl -fsSL --retry 5 "http://aminet.net/biz/dbase/sqlite-3.34.0-amiga.lha" -o /tmp/sqlite.lha && \
    lha -xfq2 sqlite.lha || exit; \
    mkdir -p /opt/sdk/sqlite/; \
    mv ./sqlite-3.34.0-amiga/build-m68k-amigaos/include/ /opt/sdk/sqlite/; \
    rm -rf /tmp/*;

ENV SQLITE_INC="/opt/sdk/sqlite/include"

USER amidev
ARG BASHFILE=/home/amidev/.bashrc
RUN sed -i '4c\'"\nexport PATH=${PATH}\n" ${BASHFILE};

USER root
RUN chown amidev:amidev /opt -R
