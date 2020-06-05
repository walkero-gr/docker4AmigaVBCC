FROM phusion/baseimage:focal-1.0.0-alpha1-amd64

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

ARG VBCC_USER_ID=1000
ARG VBCC_GROUP_ID=1000

RUN apt-get update && apt-get -y install gcc \
    wget \
    curl \
    make \
    mc \
    git; \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*;

RUN mkdir -p /opt/vbcc/bin; \
    mkdir -p /opt/code; \
    mkdir -p /opt/sdk;

# Add vbcc user and group
RUN existing_group=$(getent group "${VBCC_GROUP_ID}" | cut -d: -f1); \
    if [[ -n "${existing_group}" ]]; then delgroup "${existing_group}"; fi; \
    existing_user=$(getent passwd "${VBCC_USER_ID}" | cut -d: -f1); \
    if [[ -n "${existing_user}" ]]; then deluser "${existing_user}"; fi; \
    addgroup --gid ${VBCC_GROUP_ID} vbcc; \
    adduser --system --uid ${VBCC_USER_ID} --disabled-password --shell /bin/bash --gid ${VBCC_GROUP_ID} vbcc; \
    sed -i '/^vbcc/s/!/*/' /etc/shadow;

# Install latest lha from git repo
RUN apt-get update && apt-get -y install dh-autoreconf; \
    cd /tmp; \
    git clone https://github.com/jca02266/lha.git; \
    mkdir build; \
    cd lha; \
    autoreconf -vfi; \
    cd ../build; \
    ../lha/configure --prefix=/usr; \
    make; \
    make install; \
    apt-get -y purge dh-autoreconf && apt-get -y autoremove; \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*;

# Install vasm
RUN curl -fsSL "http://sun.hasenbraten.de/vasm/release/vasm.tar.gz" -o /tmp/vasm.tar.gz; \
    cd /tmp; \
    tar xvfz vasm.tar.gz; \
    cd /tmp/vasm; \
    make CPU=ppc SYNTAX=std; \
    cp ./vasmppc_std ./vobjdump /opt/vbcc/bin; \
    rm -rf /tmp/*;

ENV VBCC="/opt/vbcc"

# Install vlink
RUN curl -fsSL "http://sun.hasenbraten.de/vlink/release/vlink.tar.gz" -o /tmp/vlink.tar.gz; \
    cd /tmp; \
    tar xvfz vlink.tar.gz; \
    cd /tmp/vlink; \
    make; \
    cp ./vlink /opt/vbcc/bin; \
    rm -rf /tmp/*;

# Install vbcc
RUN curl -fsSL "http://www.ibaug.de/vbcc/vbcc.tar.gz" -o /tmp/vbcc.tar.gz; \
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
RUN curl -fsSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2019R4-os4.lha" -o /tmp/MUI-5.0.lha; \
    curl -fsSL "http://muidev.de/download/MUI%205.0%20-%20Release/MUI-5.0-2019R4-os4-contrib.lha" -o /tmp/MUI-5.0-contrib.lha; \
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

# Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/4.5/AmiSSL-4.5.lha" -o /tmp/AmiSSL.lha; \
    cd /tmp; \
    lha -xfq2 AmiSSL.lha; \
    mv ./AmiSSL/Developer /opt/sdk/AmiSSL; \
    rm -rf /tmp/*;

ENV AMISSL_INC="/opt/sdk/AmiSSL/include"

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

# Install FlexCat
RUN curl -fsSL "https://github.com/adtools/flexcat/releases/download/2.18/FlexCat-2.18.lha" -o /tmp/FlexCat.lha; \
    cd /tmp; \
    lha -xfq2 FlexCat.lha; \
    cp ./FlexCat/Linux-i386/flexcat /usr/bin/; \
    rm -rf /tmp/*;

# Add git branch name to bash prompt
RUN sed -i '4c\'"\nparse_git_branch() {\n\
  git branch 2> /dev/null | sed -e \'/^[^*]/d\' -e \'s/* \\\(.*\\\)/ (\\\1)/\'\n\
}\n" ~/.bashrc; \
    sed -i '43c\'"force_color_prompt=yes" ~/.bashrc; \
    sed -i '57c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\[\\\033[01;32m\\\]\\\u@\\\h\\\[\\\033[00m\\\]:\\\[\\\033[01;34m\\\]\\\w\\\[\\\033[01;31m\\\]\$(parse_git_branch)\\\[\\\033[00m\\\]\\\$ '" ~/.bashrc; \
    sed -i '59c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\u@\\\h:\\\w \$(parse_git_branch)\$ \'" ~/.bashrc;

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# USER vbcc
WORKDIR /opt/code
