# docker4AmigaVBCC
A docker image with VBCC compiler for Amiga Cross Compiling. It is based on Ubuntu and has everything needed for compiling your applications for AmigaOS m68k.

This image contains the following:

| app               | version               | source
|-------------------|-----------------------|-----------------------------------|
| vbcc              | 0.9g (04-Oct-2019)    | http://sun.hasenbraten.de/vbcc/
| vlink             | 0.16c (10-Jun-2019)   | http://sun.hasenbraten.de/vlink/
| vasm              | 1.8g (04-Oct-2019)    | http://sun.hasenbraten.de/vasm/
| NDK               | 3.9                   | http://www.haage-partner.de/download/AmigaOS/
| MUI 3.x dev       | 3.8                   | http://muidev.de/downloads
| MUI 5.x dev       | 5.0-2019R3            | http://muidev.de/downloads
| MCC_GuiGfx        | 19.2                  | http://aminet.net/package/dev/mui/MCC_Guigfx
| MCC_TextEditor    | 15.53                 | http://aminet.net/package/dev/mui/MCC_TextEditor-15.53

## Create a docker container

To create a container based on this image run in the terminal:

```bash
docker run -it --rm --name amigavbcc -v "$PWD"/code:/opt/code -w /opt/code walkero/docker4amigavbcc:1.0-m68k bash
```

If you want to use it with **docker-compose**, you can create a *docker-compose.yml* file, with the following content:

```yaml
version: '3'

services:
  vbcc:
    image: 'walkero/docker4amigavbcc:1.0-m68k'
    volumes:
      - './code:/opt/code'
```

And then you can create and get into the container by doing the following:
```bash
docker-compose up -d
docker-compose vbcc exec bash
```

To compile your project you have to get into the container, inside the */opt/code/projectname* folder, which is shared with the host machine, and run the compilation.

## Set you own include paths

The image has the following ENV variables set:

* **VBCC**: /opt/vbcc
* **PATH**: /opt/vbcc/bin
* **NDK_INC**: /opt/sdk/NDK_3.9/Include/include_h
* **NDK_LIB**: /opt/sdk/NDK_3.9/Include/linker_libs
* **MUI38_INC**: /opt/sdk/MUI_3.8/C/Include
* **MUI50_INC**: /opt/sdk/MUI_5.0/C/include

You can set your own paths, if you want, by using environment variables on docker execution or inside the docker-compose.yml file, like:
```bash
docker run -it --rm --name amigavbcc -v "$PWD"/code:/opt/code -w /opt/code -e NDK_INC="/your/folder/path" walkero/docker4amigavbcc:1.0-m68k bash
```
docker-compose.yml
```yaml
version: '3'

services:
  vbcc:
    image: 'walkero/docker4amigavbcc:1.0-m68k'
    environment:
      NDK_INC: "/opt/sdk/ext_includes/NDK_3.9/Include/include_h"
    volumes:
      - './code:/opt/code'
      - './ext_includes:/opt/sdk/ext_includes'
```


This docker image is based on the following sources:
* https://blitterstudio.com/setting-up-an-amiga-cross-compiler/
* https://github.com/Ozzyboshi/DockerAmigaVbcc
