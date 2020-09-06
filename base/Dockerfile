FROM phusion/baseimage:master-amd64

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

ENV VBCC_USER_ID=1000
ENV VBCC_GROUP_ID=1000

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

# Install vlink
RUN curl -fsSL "http://sun.hasenbraten.de/vlink/release/vlink.tar.gz" -o /tmp/vlink.tar.gz; \
    cd /tmp; \
    tar xvfz vlink.tar.gz; \
    cd /tmp/vlink; \
    make; \
    cp ./vlink /opt/vbcc/bin; \
    rm -rf /tmp/*;

# Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/4.6/AmiSSL-4.6.lha" -o /tmp/AmiSSL.lha; \
    cd /tmp; \
    lha -xfq2 AmiSSL.lha; \
    mv ./AmiSSL/Developer /opt/sdk/AmiSSL; \
    rm -rf /tmp/*;

ENV AMISSL_INC="/opt/sdk/AmiSSL/include"

# Install FlexCat
RUN curl -fsSL "https://github.com/adtools/flexcat/releases/download/2.18/FlexCat-2.18.lha" -o /tmp/FlexCat.lha; \
    cd /tmp; \
    lha -xfq2 FlexCat.lha; \
    cp ./FlexCat/Linux-i386/flexcat /usr/bin/; \
    rm -rf /tmp/*;

# Clean up APT when done.
RUN apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Add git branch name to bash prompt
ARG BASHFILE=/home/vbcc/.bashrc
RUN cp ~/.bashrc /home/vbcc/; \
    chown vbcc:vbcc /home/vbcc/.bashrc; \
    sed -i '4c\'"\nparse_git_branch() {\n\
  git branch 2> /dev/null | sed -e \'/^[^*]/d\' -e \'s/* \\\(.*\\\)/ (\\\1)/\'\n\
}\n" ${BASHFILE}; \
    sed -i '43c\'"force_color_prompt=yes" ${BASHFILE}; \
    sed -i '57c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\[\\\033[01;32m\\\]\\\u@\\\h\\\[\\\033[00m\\\]:\\\[\\\033[01;34m\\\]\\\w\\\[\\\033[01;31m\\\]\$(parse_git_branch)\\\[\\\033[00m\\\]\\\$ '" ${BASHFILE}; \
    sed -i '59c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\u@\\\h:\\\w \$(parse_git_branch)\$ \'" ${BASHFILE};

WORKDIR /opt/code
