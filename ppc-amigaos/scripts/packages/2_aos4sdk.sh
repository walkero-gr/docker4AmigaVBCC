#!/usr/bin/bash
#
set -e

SDK_PATH="/opt/sdk/ppc-amigaos"

echo -e "${CCPINK}${CCBOLD}\n---> Install AmigaOS 4 SDK ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "https://www.hyperion-entertainment.com/index.php?option=com_registration&amp;view=download&amp;format=raw&amp;file=137&amp;Itemid=137" -o /tmp/AmigaOS4-SDK.lha && \
    lha -xfq2 AmigaOS4-SDK.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/clib2*.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/exec*.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/newlib*.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/base.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/pthreads*.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/SDI-*.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/cairo-*.lha && \
    lha -xfq2w=${SDK_PATH} SDK_Install/expat-*.lha && \
    cp -r ${SDK_PATH}/Examples/Locale/include/internal/* ${SDK_PATH}/Include/include_h/ && \
    cp -r ${SDK_PATH}/Local/* ${SDK_PATH}/local/ && \
    rm -rf ${SDK_PATH}/Local ${SDK_PATH}/C ${SDK_PATH}/Data ${SDK_PATH}/S \
        ${SDK_PATH}/AmigaOS\ 4.1\ SDK.pdf.info \
        ${SDK_PATH}/Documentation.info && \
    rm -rf /tmp/*;

echo -e "${CCPINK}${CCBOLD}\n---> Setup AmigaOS 4 SDK links ${CCEND}";
ln -s ${SDK_PATH}/clib2/lib/libamiga.a 	${SDK_PATH}/newlib/lib/ && \
    ln -s ${SDK_PATH}/clib2/lib/libamiga.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/clib2/lib/libamiga.a 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/clib2/lib/libdebug.a 	${SDK_PATH}/newlib/lib/ && \
    ln -s ${SDK_PATH}/clib2/lib/libdebug.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/clib2/lib/libdebug.a 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/crtbegin.o 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/crtend.o 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/crtend.o 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/libauto.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/libauto.a 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/libc.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/libm.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/libm.a 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/librauto.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/librauto.a 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/libsocket.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/libsocket.a 	${SDK_PATH}/newlib/lib/small-data/ && \
    ln -s ${SDK_PATH}/newlib/lib/libunix.a 	${SDK_PATH}/newlib/lib/baserel/ && \
    ln -s ${SDK_PATH}/newlib/lib/libunix.a 	${SDK_PATH}/newlib/lib/small-data/;
