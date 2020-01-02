# 
# Target OS: Amiga OS3.X
# Compiler : VBCC
#

APPNAME = Project
CC = vc
OPTIONS = +aos68k -c99 -lamiga -lauto
CFLAGS = -I$(NDK_INC) -I$(MUI38_INC)
FILES = project.c

project:
	$(CC) $(OPTIONS) $(CFLAGS) -o $(APPNAME) $(FILES)
	
clean:
	rm $(APPNAME)
	