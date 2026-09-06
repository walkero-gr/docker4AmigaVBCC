#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install NDK 3.2 ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://aminet.net/dev/misc/NDK3.2.lha" -o /tmp/ndk32.lha || exit $? && \
    lha -xfq2w=NDK3.2 ndk32.lha && \
    mv ./NDK3.2 /opt/sdk/ && \
    rm -rf /tmp/*;
