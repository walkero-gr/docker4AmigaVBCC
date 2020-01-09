#include <libraries/mui.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/muimaster.h>
#include <libraries/gadtools.h>
#include <libraries/iffparse.h>
#include <stdio.h>
#include <proto/intuition.h>
#include <proto/graphics.h>

#define MAKE_ID(a,b,c,d) ((ULONG) (a)<<24 | (ULONG) (b)<<16 | (ULONG) (c)<<8 | (ULONG) (d))

#define IPTR ULONG

struct IntuitionBase *IntuitionBase;
struct GfxBase *GfxBase;
struct Library *MUIMasterBase;

BOOL Open_Libs(void)
{
  if ( !(IntuitionBase=(struct IntuitionBase *) OpenLibrary("intuition.library",39)) )
    return(0);

  if ( !(GfxBase=(struct GfxBase *) OpenLibrary("graphics.library",0)) )
  {
    CloseLibrary((struct Library *)IntuitionBase);
    return(0);
  }

  if ( !(MUIMasterBase=OpenLibrary(MUIMASTER_NAME,19)) )
  {
    CloseLibrary((struct Library *)GfxBase);
    CloseLibrary((struct Library *)IntuitionBase);
    return(0);
  }

  return(1);
}

void Close_Libs(void)
{
  if (IntuitionBase)
    CloseLibrary((struct Library *)IntuitionBase);

  if (GfxBase)
    CloseLibrary((struct Library *)GfxBase);

  if (MUIMasterBase)
    CloseLibrary(MUIMasterBase);
}

