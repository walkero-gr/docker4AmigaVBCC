FROM walkero/docker4amigavbcc:latest-base

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Install vasm
RUN curl -fsSL "http://sun.hasenbraten.de/vasm/release/vasm.tar.gz" -o /tmp/vasm.tar.gz; \
    cd /tmp; \
    tar xvfz vasm.tar.gz; \
    cd /tmp/vasm; \
    make CPU=ppc SYNTAX=std; \
    cp ./vasmppc_std ./vobjdump /opt/vbcc/bin; \
    rm -rf /tmp/*;

ENV VBCC="/opt/vbcc"

# Install vbcc
RUN curl -fsSL "http://phoenix.owl.de/tags/vbcc0_9g.tar.gz" -o /tmp/vbcc.tar.gz; \
    cd /tmp; \
    tar xvfz vbcc.tar.gz; \
    cd /tmp/vbcc; \
    mkdir bin; \
    yes '\
' | make TARGET=ppc; \
    make TARGET=ppc bin/vscppc; \
    cp ./bin/vbcc* ./bin/vscppc ./bin/vc ./bin/vprof /opt/vbcc/bin; \
    rm -rf /tmp/*;

RUN curl -fsSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_target_ppc-amigaos.lha" -o /tmp/vbcc_target_ppc-amigaos.lha; \
    curl -fsSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz; \
    cd /tmp; \
    lha -xfq2 vbcc_target_ppc-amigaos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_ppc-amigaos/targets $VBCC/; \
    rm -rf /tmp/*;

ENV PATH="$VBCC/bin:$PATH"

# Install AmigaOS 4 SDK
RUN curl -fksSL "https://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=82&amp;Itemid=82" -o /tmp/AmigaOS4-SDK.lha; \
    cd /tmp; \
    lha -xfq2 AmigaOS4-SDK.lha; \
    cd SDK_Install; \
    lha -xfq2 clib2*.lha; \
    lha -xfq2 newlib*.lha; \
    lha -xfq2 base.lha; \
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
RUN curl -fsSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2020R1-os4.lha" -o /tmp/MUI-5.0.lha; \
    curl -fsSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2020R1-os4-contrib.lha" -o /tmp/MUI-5.0-contrib.lha; \
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
    cp ./MCC_Guigfx/Developer/C/Include/MUI/* /opt/sdk/MUI_5.0/C/include/mui; \
    rm -rf /tmp/*;

# Install GL4ES SDK
# RUN curl -fsSL "https://github.com/kas1e/GL4ES-SDK/releases/download/1.1/gl4es_sdk-1.1.lha" -o /tmp/gl4es_sdk-1.1.lha; \
#     cd /tmp; \
#     lha -xfq2 gl4es_sdk-1.1.lha; \
#     mv SDK/local/common /opt/sdk/GL4ES;

# ENV GL4ES_INC="/opt/sdk/GL4ES/include"

# Install SQLite
RUN curl -fsSL "http://aminet.net/biz/dbase/sqlite-3.6.1-amiga.lha" -o /tmp/sqlite.lha; \
    cd /tmp; \
    lha -xfq2 sqlite.lha; \
    mkdir -p /opt/sdk/sqlite/; \
    mv ./sqlite-3.6.1-amiga/build-ppc-amigaos/include/ /opt/sdk/sqlite/; \
    rm -rf /tmp/*;

ENV SQLITE_INC="/opt/sdk/sqlite/include"

RUN chown vbcc:vbcc /opt -R
