FROM walkero/lha-on-docker:latest as lha-image

FROM phusion/baseimage:master

LABEL maintainer="Georgios Sokianos <walkero@gmail.com>"

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

COPY --from=lha-image /usr/bin/lha /usr/bin/lha

ENV AMIDEV_USER_ID=1000
ENV AMIDEV_GROUP_ID=1000

RUN mkdir -p /opt/vbcc/bin; \
    mkdir -p /opt/code; \
    mkdir -p /opt/sdk;

# Add amidev user and group
RUN existing_group=$(getent group "${AMIDEV_GROUP_ID}" | cut -d: -f1); \
    if [[ -n "${existing_group}" ]]; then delgroup "${existing_group}"; fi; \
    existing_user=$(getent passwd "${AMIDEV_USER_ID}" | cut -d: -f1); \
    if [[ -n "${existing_user}" ]]; then deluser "${existing_user}"; fi; \
    addgroup --gid ${AMIDEV_GROUP_ID} amidev; \
    adduser --system --uid ${AMIDEV_USER_ID} --disabled-password --shell /bin/bash --gid ${AMIDEV_GROUP_ID} amidev; \
    sed -i '/^amidev/s/!/*/' /etc/shadow; 

ENV PACKAGES="\
    curl \
    gcc \
    git \
    libc-dev \
    make \
    mc \
    splint \
    wget"

RUN apt-get update && apt-get -y --no-install-recommends install ${PACKAGES}; \
    apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*;

# Compile and install vlink
WORKDIR /tmp
RUN curl -fsSL "http://sun.hasenbraten.de/vlink/release/vlink.tar.gz" -o /tmp/vlink_0.17.tar.gz || exit $?; \
    tar xvfz vlink_0.17.tar.gz; \
    make -C vlink || exit $?; \
    cp /tmp/vlink/vlink /opt/vbcc/bin || exit $?; \
    rm -rf /tmp/*;

# Install AMISSL SDK
RUN curl -fsSL "https://github.com/jens-maus/amissl/releases/download/4.12/AmiSSL-4.12.lha" -o /tmp/AmiSSL.lha || exit $?; \
    lha -xfq2 AmiSSL.lha; \
    mv ./AmiSSL/Developer /opt/sdk/AmiSSL; \
    rm -rf /tmp/*;
ENV AMISSL_INC="/opt/sdk/AmiSSL/include"

# Install FlexCat
RUN curl -fsSL "https://github.com/adtools/flexcat/releases/download/2.18/FlexCat-2.18.lha" -o /tmp/FlexCat.lha || exit $?; \
    lha -xfq2 FlexCat.lha; \
    cp ./FlexCat/Linux-i386/flexcat /usr/bin/; \
    rm -rf /tmp/*;

# Add git branch name to bash prompt
ARG BASHFILE=/home/amidev/.bashrc
RUN cp ~/.bashrc /home/amidev/; \
    chown amidev:amidev ${BASHFILE}; \
    sed -i '4c\'"\nparse_git_branch() {\n\
  git branch 2> /dev/null | sed -e \'/^[^*]/d\' -e \'s/* \\\(.*\\\)/ (\\\1)/\'\n\
}\n" ${BASHFILE}; \
    sed -i '43c\'"force_color_prompt=yes" ${BASHFILE}; \
    sed -i '57c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\[\\\033[01;32m\\\]\\\u@\\\h\\\[\\\033[00m\\\]:\\\[\\\033[01;34m\\\]\\\w\\\[\\\033[01;31m\\\]\$(parse_git_branch)\\\[\\\033[00m\\\]\\\$ '" ${BASHFILE}; \
    sed -i '59c\'"    PS1=\'\${debian_chroot:+(\$debian_chroot)}\\\u@\\\h:\\\w \$(parse_git_branch)\$ \'" ${BASHFILE};

WORKDIR /opt/code
