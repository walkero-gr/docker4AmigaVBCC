#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install Roadshow SDK ${CCEND}";
  curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://walkero.gr/betas/Roadshow-SDK-1.8.lha" -o Roadshow-SDK.lha || exit $? && \
    lha -xfq2w=Roadshow-SDK Roadshow-SDK.lha && \
    mv ./Roadshow-SDK /opt/sdk/Roadshow-SDK && \
    rm -rf /tmp/*;
