#!/usr/bin/bash
set -e				# Exit on error
set -o pipefail		# Propagate errors through pipes
set -u				# Exit on undefined variable

cd /tmp

echo -e "${CCPINK}${CCBOLD}\n---> Install packages ${CCEND}";
find /scripts/packages -type f -name '*.sh' | sort | while read i; do
  bash "$i"
done
