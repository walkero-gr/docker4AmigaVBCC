# Changelog
All notable changes to this project will be documented in this file.

## docker4amigavbcc [future]
### Added
- Added a new base image which is used for common installations of all images

### Changed
- Updated AmiSSL SDK to latest released version 4.6
- Brought back vbcc v0.9g on both PPC and MOS images, by using the archive from phoenix.owl.de

## docker4amigavbcc v1.6 - 2020-06-07
### Added
- Added sqlite 3.6.1 on all images
- Added MUI 3.8 and MUI 5.0-2019R4 OS4 SDKs at the MorphOS image
- Added NDK 3.9 at the MorphOS image
- Added git branch name to bash prompt

### Changed
- Optimized the images and made them 21%-40% smaller
- Compiled lha from the latest available version at https://github.com/jca02266/lha.git to v2 PMA
- Experimental: Changed to Ubuntu in image to 20.04
- Set silent argument to curls
- Reverted vbcc for PPC and MOS images to v0.9f, because of the error "Segmentation fault (core dump)" that I get when compiling iGame for AmigaOS 4 and MorphOS. With this version this error doesn't occur.

### Removed
- Removed MorphOS SDK since it doesn't work with VBCC

## docker4amigavbcc v1.5 - 2020-04-29
### Added
- Added lha v1.14i because it is able to compress files in lha format, and will be useful for packaging
- Added MorphOS image with the MorphOS 3.14 SDK - April 2020

### Changed
- Updated vasm to v1.8h (18-Apr-2020) on all images
- Updated vlink to v0.16d (18-Apr-2020) on all images

### Removed
- Removed lhasa because it can only extract lha files

## docker4amigavbcc v1.4 - 2020-03-30
### Added
- Added on PPC image the clib2 includes
- Added MCC_GuiGfx installation at the PPC image
- Added vscppc at the PPC image
- Added vbcc user and group, with ids 1000 so that the changed files have the same permissions from the host machine as well
- Added FlexCat 2.18 on both images, m68k and ppc

### Changed
- Fixes on m68k image on MCC_GuiGfx copy
- Updated AmiSSL version to 4.5 on both images, m68k and ppc

## docker4amigavbcc v1.3 - 2020-03-02
### Changed
- Fixed on PPC image the MUI version. It included OS3 version files
- Added on PPC & m68k images lhasa quite argument, to minimize the output text
- Version now covers both images. Only ppc-latest and m68k-latest tags will be updated for now

## docker4amigavbcc:1.2-m68k - 2020-03-02
### Added
- AmiSSL 4.4 SDK
- Posix Lib includes

## docker4amigavbcc:1.1-ppc - 2020-02-28
### Added
- AmiSSL 4.4 SDK
- Newlib Env variable for the newlib includes

## docker4amigavbcc:1.0-ppc - 2020-01-09
### Added
- Initial ppc release
- Latest vbcc, vlink, vasm
- AmigaOS 4 SDK v53.30
- MUI 5.x Dev, v5.0-2019R4

## docker4amigavbcc:1.1-m68k - 2020-01-09
### Added
- Introduced the docker4amigavbcc:latest-m68k
- Changed the Makefile to build and push the latest-m68k tag
- Roadshow SDK
- git
- Added shell, logs and clean to the makefile

## docker4amigavbcc:1.1-m68k - 2019-12-31
### Added
- Initial m68k release
- Latest vbcc, vlink, vasm
- NDK 3.9
- MUI 3.x Dev, v3.8
- MUI 5.x Dev, v5.0-2019R4
- MCC_GuiGfx v19.2
- MCC_TextEditor v15.53






The format of this changelog file is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)