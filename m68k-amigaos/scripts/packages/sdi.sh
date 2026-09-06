#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install SDI ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://aminet.net/dev/c/SDI_headers.lha" -o SDI_headers.lha || exit $?; \
    lha -xfq2 SDI_headers.lha && \
    mkdir ${NDK32_PATH}/Examples/SDI ${NDK39_PATH}/Examples/SDI && \
    cp -r ./SDI/includes/* ${NDK32_PATH}/Include_H/ && \
    cp -r ./SDI/examples/* ${NDK32_PATH}/Examples/SDI/ && \
    cp -r ./SDI/includes/* ${NDK39_PATH}/Include/include_h/ && \
    cp -r ./SDI/examples/* ${NDK39_PATH}/Examples/SDI/ && \
    rm -rf /tmp/*;
