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
    git \
    xz-utils; \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*;

RUN mkdir -p /opt/vbcc/bin; \
    mkdir -p /opt/code; \
    mkdir -p /opt/sdk/morphos;

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

RUN curl -fsSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_target_ppc-morphos.lha" -o /tmp/vbcc_target_ppc-morphos.lha; \
    curl -fsSL "https://server.owl.de/~frank/vbcc/2019-10-04/vbcc_unix_config.tar.gz" -o /tmp/vbcc_unix_config.tar.gz; \
    cd /tmp; \
    lha -xfq2 vbcc_target_ppc-morphos.lha; \
    tar xvfz vbcc_unix_config.tar.gz; \
    mv ./config $VBCC/; \
    mv ./vbcc_target_ppc-morphos/targets $VBCC/; \
    rm -rf /tmp/*;

ENV PATH="$VBCC/bin:$PATH"

# Install NDK39
RUN curl -fsSL "http://www.haage-partner.de/download/AmigaOS/NDK39.lha" -o /tmp/NDK39.lha; \
    cd /tmp; \
    lha -xfq2 NDK39.lha; \
    mv ./NDK_3.9 /opt/sdk/; \
    rm -rf /tmp/*;

ENV NDK_INC="/opt/sdk/NDK_3.9/Include/include_h"
ENV NDK_LIB="/opt/sdk/NDK_3.9/Include/linker_libs"

# # Install MorphOS SDK
# RUN curl -fksSL "https://www.morphos-team.net/files/sdk-20200422.lha" -o /tmp/MorphOS-SDK.lha; \
#     cd /tmp; \
#     lha -xfq2 MorphOS-SDK.lha; \
#     cd morphossdk; \
#     tar -xJf sdk.pack; \
#     cd Development/gg; \
#     mv ./include /opt/sdk/morphos/include; \
#     mv ./includestd /opt/sdk/morphos/includestd; \
#     mv ./lib /opt/sdk/morphos/lib; \
#     mv ./os-include /opt/sdk/morphos/os-include; \
#     mv ./ppc-morphos /opt/sdk/morphos/ppc-morphos;

# ENV MOS_SDK_INC="/opt/sdk/morphos/include"
# ENV MOS_SDK_STD="/opt/sdk/morphos/includestd"
# ENV MOS_OS_INC="/opt/sdk/morphos/os-include"

# Install MUI 3.8 dev
RUN curl -fsSL "http://muidev.de/download/MUI%203.8%20-%20AmigaOS3-m68k/mui38dev.lha" -o /tmp/mui38dev.lha; \
    cd /tmp; \
    lha -xfq2 mui38dev.lha; \
    mv ./MUI/Developer /opt/sdk/MUI_3.8; \
    mkdir -p /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

ENV MUI38_INC="/opt/sdk/MUI_3.8/C/Include"

# Install MCC_GuiGfx
RUN curl -fsSL "http://aminet.net/dev/mui/MCC_Guigfx.lha" -o /tmp/MCC_Guigfx.lha; \
    cd /tmp; \
    lha -xfq2 MCC_Guigfx.lha; \
    cp ./MCC_Guigfx/Developer/C/Include/MUI/* /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

# Install MCC_TextEditor
RUN curl -fsSL "http://aminet.net/dev/mui/MCC_TextEditor-15.53.lha" -o /tmp/MCC_TextEditor.lha; \
    cd /tmp; \
    lha -xfq2 MCC_TextEditor.lha; \
    cp ./MCC_TextEditor/Developer/C/include/mui/* /opt/sdk/MUI_3.8/C/Include/mui; \
    rm -rf /tmp/*;

# Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/4.5/AmiSSL-4.5.lha" -o /tmp/AmiSSL.lha; \
    cd /tmp; \
    lha -xfq2 AmiSSL.lha; \
    mv ./AmiSSL/Developer /opt/sdk/AmiSSL; \
    rm -rf /tmp/*;

ENV AMISSL_INC="/opt/sdk/AmiSSL/include"

# Install SQLite
RUN curl -fsSL "http://aminet.net/biz/dbase/sqlite-3.6.1-amiga.lha" -o /tmp/sqlite.lha; \
    cd /tmp; \
    lha -xfq2 sqlite.lha; \
    mkdir -p /opt/sdk/sqlite/; \
    mv ./sqlite-3.6.1-amiga/build-ppc-morphos/include/ /opt/sdk/sqlite/; \
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
