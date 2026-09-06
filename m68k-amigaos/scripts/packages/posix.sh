#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install PosixLib ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://aminet.net/dev/c/vbcc_PosixLib.lha" -o vbcc_PosixLib.lha || exit $? && \
    lha -xfq2 vbcc_PosixLib.lha && \
    mkdir -p /opt/sdk/PosixLib/ && \
    mv ./PosixLib/include/ /opt/sdk/PosixLib/ && \
    rm -rf /tmp/*;
