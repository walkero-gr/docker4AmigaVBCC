#!/usr/bin/bash
# 

echo -e "${CCPINK}${CCBOLD}\n---> Install AmiSSL SDK${CCEND}";
	curl -fsSL "https://github.com/jens-maus/amissl/releases/download/5.27/AmiSSL-5.27-SDK.lha" -o /tmp/AmiSSL.lha && \
		lha -xfq2 AmiSSL.lha && \
		cp ./AmiSSL/Developer/include/* ${NDK32_PATH}/Include_H/ -r && \
		cp ./AmiSSL/Developer/Autodocs/* ${NDK32_PATH}/Autodocs/ && \
		cp ./AmiSSL/Developer/Examples/*.c ${NDK32_PATH}/Examples/ && \
		cp ./AmiSSL/Developer/fd/* ${NDK32_PATH}/FD/ && \
		cp ./AmiSSL/Developer/lib/AmigaOS3/* ${NDK32_PATH}/lib/ && \
		cp ./AmiSSL/Developer/sfd/* ${NDK32_PATH}/SFD/ && \
		cp ./AmiSSL/Developer/include/* ${NDK39_PATH}/Include/include_h/ -r && \
		cp ./AmiSSL/Developer/Autodocs/* ${NDK39_PATH}/Documentation/Autodocs/ && \
		cp ./AmiSSL/Developer/Examples/*.c ${NDK39_PATH}/Examples/ && \
		cp ./AmiSSL/Developer/fd/* ${NDK39_PATH}/Include/fd/ && \
		cp ./AmiSSL/Developer/lib/AmigaOS3/* ${NDK39_PATH}/Include/linker_libs/ && \
		cp ./AmiSSL/Developer/sfd/* ${NDK39_PATH}/Include/sfd/ && \
		rm -rf /tmp/*;