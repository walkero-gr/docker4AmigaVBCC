#!/usr/bin/bash
#
set -e

SDK_PATH="/opt/sdk/ppc-amigaos"

echo -e "${CCPINK}${CCBOLD}\n---> Install AmiSSL ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://github.com/jens-maus/amissl/releases/download/5.27/AmiSSL-5.27-SDK.lha" -o /tmp/AmiSSL.lha && \
    lha -xfq2 AmiSSL.lha && \
    cp ./AmiSSL/Developer/include/* ${SDK_PATH}/Include/include_h/ -r && \
    cp ./AmiSSL/Developer/Autodocs/* ${SDK_PATH}/Documentation/AutoDocs/ && \
    cp ./AmiSSL/Developer/Examples/*.c ${SDK_PATH}/Examples/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS4/clib2/*.a ${SDK_PATH}/local/clib2/lib/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS4/newlib/*.a ${SDK_PATH}/local/newlib/lib/ && \
    rm -rf /tmp/*;
