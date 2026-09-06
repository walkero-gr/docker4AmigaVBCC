#!/usr/bin/bash
#
set -e

echo -e "${CCPINK}${CCBOLD}\n---> Install vasm ${CCEND}";
curl --retry 5 --retry-delay 2 --retry-connrefused -fsSL "http://phoenix.owl.de/tags/vasm2_0f.tar.gz" -o vasm.tar.gz || exit $?;
tar xfz vasm.tar.gz;
make -C vasm CPU=m68k SYNTAX=mot;
cp ./vasm/vasmm68k_mot ./vasm/vobjdump /opt/vbcc/bin;
rm -rf vasm vasm.tar.gz;
