#!/usr/bin/bash
#
set -e

SDK_PATH="/opt/sdk/ppc-amigaos"

echo -e "${CCPINK}${CCBOLD}\n---> Install sqlite ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL --retry 5 "https://aminet.net/biz/dbase/sqlite-3.34.0.a-amiga.lha" -o sqlite.lha || exit $? && \
    lha -xfq2 sqlite.lha && \
    cp ./sqlite-3.34.0.a-amiga/build-ppc-amigaos/include/*.h ${SDK_PATH}/local/newlib/include/ && \
    cp ./sqlite-3.34.0.a-amiga/build-ppc-amigaos/lib/*.a ${SDK_PATH}/local/newlib/lib/ && \
    rm -rf /tmp/*;
