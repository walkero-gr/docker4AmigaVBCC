#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install sqlite ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL --retry 5 "https://aminet.net/biz/dbase/sqlite-3.34.0.a-amiga.lha" -o sqlite.lha || exit $? && \
    lha -xfq2 sqlite.lha && \
    mkdir -p /opt/sdk/sqlite/ && \
    cp -r ./sqlite-3.34.0.a-amiga/build-ppc-morphos/include/ /opt/sdk/sqlite/ && \
    cp -r ./sqlite-3.34.0.a-amiga/build-ppc-morphos/lib/ /opt/sdk/sqlite/ && \
    rm -rf /tmp/*;
