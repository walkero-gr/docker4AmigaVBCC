FROM phusion/baseimage:master

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

RUN apt-get update && apt-get -y install gcc \
    wget \
    curl \
    make \
    mc \
    git \
    lhasa;

RUN mkdir -p /opt/vbcc/bin; \
    mkdir -p /opt/code; \
    mkdir -p /opt/sdk;

# Install vasm
RUN curl -fSL "http://sun.hasenbraten.de/vasm/release/vasm.tar.gz" -o /tmp/vasm.tar.gz; \
    cd /tmp; \
    tar xvfz vasm.tar.gz; \
    cd /tmp/vasm; \
    make CPU=ppc SYNTAX=std; \
    cp vasmppc_std vobjdump /opt/vbcc/bin; 

ENV VBCC="/opt/vbcc"

# Install vlink
RUN curl -fSL "http://sun.hasenbraten.de/vlink/release/vlink.tar.gz" -o /tmp/vlink.tar.gz; \
    cd /tmp; \
    tar xvfz vlink.tar.gz; \
    cd /tmp/vlink; \
    make; \
    cp vlink /opt/vbcc/bin;

# Install vbcc
RUN curl -fSL "http://www.ibaug.de/vbcc/vbcc.tar.gz" -o /tmp/vbcc.tar.gz; \
    cd /tmp; \
    tar xvfz vbcc.tar.gz; \
    cd /tmp/vbcc; \
    mkdir bin; \
    yes '\
' | make TARGET=ppc; \
    cp bin/vbcc* bin/vc bin/vprof /opt/vbcc/bin;

RUN curl -fSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_target_ppc-amigaos.lha" -o /tmp/vbcc_target_ppc-amigaos.lha; \
    # curl -fSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_target_ppc-morphos.lha" -o /tmp/vbcc_target_ppc-morphos.lha; \
    curl -fSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz; \
    cd /tmp; \
    lhasa x vbcc_target_ppc-amigaos.lha; \
    # lhasa x vbcc_target_ppc-morphos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv config $VBCC/; \
    mv vbcc_target_ppc-amigaos/targets $VBCC/; 
    # cp vbcc_target_ppc-morphos/targets/* $VBCC/targets/ -r;

ENV PATH="$VBCC/bin:$PATH"

# Install AmigaOS 4 SDK
RUN curl -fSL "http://www.hyperion-entertainment.biz/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=82&amp;Itemid=82" -o /tmp/AmigaOS4-SDK.lha; \
    cd /tmp; \
    lhasa -xf AmigaOS4-SDK.lha; \
    cd SDK_Install; \
    lhasa -xf newlib*.lha; \
    lhasa -xf base.lha; \
    mv Documentation /opt/sdk/ppc-amigaos; \
    mv Examples /opt/sdk/ppc-amigaos; \
    mv Include /opt/sdk/ppc-amigaos; \
    mv newlib /opt/sdk/ppc-amigaos;

ENV AOS4_SDK_INC="/opt/sdk/ppc-amigaos/Include/include_h"
ENV AOS4_NET_INC="/opt/sdk/ppc-amigaos/Include/netinclude"

# Install MUI 5.0 dev
RUN curl -fSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2019R4-os3.lha" -o /tmp/MUI-5.0-os3.lha; \
    curl -fSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2019R4-os3-contrib.lha" -o /tmp/MUI-5.0-os3-contrib.lha; \
    cd /tmp; \
    lhasa -xf MUI-5.0-os3.lha; \
    lhasa -xf MUI-5.0-os3-contrib.lha; \
    mv SDK/MUI /opt/sdk/MUI_5.0;

ENV MUI50_INC="/opt/sdk/MUI_5.0/C/include"

# Install AMISSL SDK
# RUN curl -fSL "https://github.com/jens-maus/amissl/releases/download/4.3/AmiSSL-4.3.lha" -o /tmp/AmiSSL-4.3.lha; \
#     cd /tmp; \
#     lhasa -xf AmiSSL-4.3.lha; \
#     mv AmiSSL/Developer /opt/sdk/AmiSSL;

# ENV AMISSL_INC="/opt/sdk/AmiSSL/include"

# Install GL4ES SDK
# RUN curl -fSL "https://github.com/kas1e/GL4ES-SDK/releases/download/1.1/gl4es_sdk-1.1.lha" -o /tmp/gl4es_sdk-1.1.lha; \
#     cd /tmp; \
#     lhasa -xf gl4es_sdk-1.1.lha; \
#     mv SDK/local/common /opt/sdk/GL4ES;

# ENV GL4ES_INC="/opt/sdk/GL4ES/include"

WORKDIR /opt/code

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*