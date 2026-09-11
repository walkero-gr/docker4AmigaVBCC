#!/usr/bin/bash
#
set -e

SDK_PATH="/opt/sdk"
NDK39_PATH="${SDK_PATH}/NDK_3.9"

echo -e "${CCPINK}${CCBOLD}\n---> Install AmiSSL ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://github.com/jens-maus/amissl/releases/download/5.27/AmiSSL-5.27-SDK.lha" -o AmiSSL.lha || exit $? && \
    lha -xfq2 AmiSSL.lha && \
    cp ./AmiSSL/Developer/include/* ${NDK39_PATH}/Include/include_h/ -r && \
    cp ./AmiSSL/Developer/Autodocs/* ${NDK39_PATH}/Documentation/Autodocs/ && \
    cp ./AmiSSL/Developer/Examples/*.c ${NDK39_PATH}/Examples/ && \
    cp ./AmiSSL/Developer/fd/* ${NDK39_PATH}/Include/fd/ && \
    cp ./AmiSSL/Developer/lib/AmigaOS3/* ${NDK39_PATH}/Include/linker_libs/ && \
    cp ./AmiSSL/Developer/sfd/* ${NDK39_PATH}/Include/sfd/ && \
    rm -rf /tmp/*;
