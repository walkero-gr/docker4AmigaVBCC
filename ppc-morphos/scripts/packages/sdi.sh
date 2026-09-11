#!/usr/bin/bash
#
set -e

SDK_PATH="/opt/sdk"
NDK39_PATH="${SDK_PATH}/NDK_3.9"

echo -e "${CCPINK}${CCBOLD}\n---> Install SDI ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://aminet.net/dev/c/SDI_headers.lha" -o SDI_headers.lha || exit $? && \
    lha -xfq2 SDI_headers.lha && \
    mkdir -p ${NDK39_PATH}/Examples/SDI && \
    cp -r ./SDI/includes/* ${NDK39_PATH}/Include/include_h/ && \
    cp -r ./SDI/examples/* ${NDK39_PATH}/Examples/SDI/ && \
    rm -rf /tmp/*;
