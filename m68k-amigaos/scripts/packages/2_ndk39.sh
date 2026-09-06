#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install NDK 3.9 ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://hp.alinea-computer.de/AmigaOS/NDK39.lha" -o /tmp/NDK39.lha || exit $? && \
    lha -xfq2 NDK39.lha && \
    mv ./NDK_3.9 /opt/sdk/ && \
    rm -rf /tmp/*;
