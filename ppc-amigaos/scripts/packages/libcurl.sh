#!/usr/bin/bash
#
set -e

SDK_PATH="/opt/sdk/ppc-amigaos"

echo -e "${CCPINK}${CCBOLD}\n---> Install libCurl ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://os4depot.net/share/development/library/misc/libcurl.lha" -o /tmp/libcurl.lha && \
    lha -xfq2 libcurl.lha && \
    cp -r ./SDK/* ${SDK_PATH}/ && \
    rm -rf /tmp/*;
