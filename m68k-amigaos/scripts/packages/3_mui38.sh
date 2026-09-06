#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install MUI 3.8 ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://aminet.net/dev/mui/mui38dev.lha" -o mui38dev.lha || exit $? && \
    7z x mui38dev.lha && \
    mv ./MUI/Developer /opt/sdk/MUI_3.8 && \
    mkdir -p /opt/sdk/MUI_3.8/C/Include/mui && \
    rm -rf MUI* mui*;
