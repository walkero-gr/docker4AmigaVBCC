#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install MUI 5.0 ${CCEND}";
  curl --retry 10 --retry-delay 5 --retry-connrefused -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os3.lha" -o ./MUI-5.0.lha || exit $? && \
  curl --retry 10 --retry-delay 5 --retry-connrefused -fsSL "https://github.com/amiga-mui/muidev/releases/download/MUI-5.0-20210831/MUI-5.0-20210831-os3-contrib.lha" -o ./MUI-5.0-contrib.lha || exit $? && \
    lha -xfq2 MUI-5.0.lha && \
    lha -xfq2 MUI-5.0-contrib.lha && \
    mv ./SDK/MUI /opt/sdk/MUI_5.0 && \
    rm -rf /tmp/*;
