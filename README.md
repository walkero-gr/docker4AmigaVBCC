# docker4AmigaVBCC
A docker image with VBCC compiler for Amiga Cross Compiling

To create the container run
```bash
docker run --rm -it walkero/docker4amigavbcc:1.0-m68k bash
docker run -it --rm --name amigavbcc -v "$PWD"/code:/opt/code -w /opt/code walkero/docker4amigavbcc:1.0-m68k bash
```

based on:
* https://blitterstudio.com/setting-up-an-amiga-cross-compiler/
* https://github.com/Ozzyboshi/DockerAmigaVbcc