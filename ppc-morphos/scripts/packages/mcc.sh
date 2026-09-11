#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install MCC_GuiGfx ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://aminet.net/dev/mui/MCC_Guigfx.lha" -o MCC_Guigfx.lha || exit $? && \
    lha -xfq2 MCC_Guigfx.lha && \
    cp ./MCC_Guigfx/Developer/C/Include/MUI/* /opt/sdk/MUI_3.8/C/Include/mui && \
    rm -rf /tmp/*;

echo -e "${CCPINK}${CCBOLD}\n---> Install MCC_TextEditor ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://aminet.net/dev/mui/MCC_TextEditor-15.56.lha" -o MCC_TextEditor.lha || exit $? && \
    lha -xfq2 MCC_TextEditor.lha && \
    cp ./MCC_TextEditor/Developer/C/include/mui/* /opt/sdk/MUI_3.8/C/Include/mui && \
    rm -rf /tmp/*;
