#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install vbcc ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://phoenix.owl.de/tags/vbcc0_9hP3.tar.gz" -o vbcc.tar.gz || exit $?;
tar xfz vbcc.tar.gz;
mkdir -p ./vbcc/bin;
yes '' | make -C ./vbcc TARGET=m68k;
yes '' | make -C ./vbcc TARGET=m68ks;
cp ./vbcc/bin/vbcc* ./vbcc/bin/vc ./vbcc/bin/vprof /opt/vbcc/bin;
rm -rf vbcc vbcc.tar.gz;

echo -e "${CCPINK}${CCBOLD}\n---> Install vbcc targets ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_target_m68k-amigaos.lha" -o vbcc_target_m68k-amigaos.lha || exit $?;
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://server.owl.de/~frank/vbcc/2022-05-22/vbcc_unix_config.tar.gz" -o vbcc_unix_config.tar.gz || exit $?;
lha -xfq2 vbcc_target_m68k-amigaos.lha;
tar xfz vbcc_unix_config.tar.gz;
mv config $VBCC/;
mv vbcc_target_m68k-amigaos/targets $VBCC/;
rm -rf vbcc_target_m68k-amigaos vbcc_target_m68k-amigaos.lha vbcc_unix_config.tar.gz config;
