/* Window Example
gcc -o Window Window.c -lauto
vc +aosppc -I$AOS4_SDK_INC -lauto Window.c -o Window
quit
*/

/**
 **  Window.c -- Window Example.
 **
 **  Simple window.class example used to test newer features.
 **/

#include <dos/dos.h>
#include <classes/window.h>
#include <gadgets/button.h>
#include <gadgets/layout.h>

#include <proto/intuition.h>
#include <proto/exec.h>
#include <proto/window.h>
#include <proto/layout.h>
#include <proto/button.h>

enum
{
    WID_MAIN = 0,
    WID_LAST
};

enum
{
    OID_MAIN = 0,
    OID_LAST
};

int main()
{
    // Make sure class files were loaded.
    if ( WindowBase == NULL || LayoutBase == NULL || ButtonBase == NULL)
    {
        return RETURN_FAIL;
    }

    struct Window *windows[WID_LAST];
    Object *objects[OID_LAST];

    struct MsgPort *AppPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE);

    if ( AppPort != NULL )
    {
        objects[OID_MAIN] = IIntuition->NewObject(NULL, "window.class",
            WA_ScreenTitle, "Window Example",
            WA_Title, "Window Example",
            WA_Activate, TRUE,
            WA_DepthGadget, TRUE,
            WA_DragBar, TRUE,
            WA_CloseGadget, TRUE,
            WA_SizeGadget, TRUE,

            // If on the Workbench screen, this tells window.class that
            // we can handle the iconify/uniconify when changing screens.
            WINDOW_Iconifiable, TRUE,

            WINDOW_AppPort, AppPort,
            WINDOW_Position, WPOS_CENTERMOUSE,
            WINDOW_Layout, IIntuition->NewObject(NULL, "layout.gadget",
                LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
                LAYOUT_SpaceOuter, TRUE,
                LAYOUT_DeferLayout, TRUE,
                LAYOUT_AddChild, IIntuition->NewObject(NULL, "button.gadget",
                    GA_Text, "Click Me",
                TAG_DONE),
           TAG_DONE),
        TAG_DONE);

        if (objects[OID_MAIN] != NULL)
        {
            //  Open the window.
            windows[WID_MAIN] = (struct Window *)IIntuition->IDoMethod(objects[OID_MAIN], WM_OPEN);

            if (windows[WID_MAIN] != NULL)
            {
                // Obtain the window wait signal mask.

                uint32 signal = 0;
                IIntuition->GetAttr(WINDOW_SigMask, objects[OID_MAIN], &signal);

                // Input Event Loop

                BOOL done = FALSE;

                while (!done)
                {
                    uint32 wait = IExec->Wait(signal | SIGBREAKF_CTRL_C);

                    if ( wait & SIGBREAKF_CTRL_C )
                    {
                        done = TRUE;
                        break;
                    }

                    if ( wait & signal )
                    {
                        uint32 result = WMHI_LASTMSG;
                        int16 code = 0;

                        while ((result = IIntuition->IDoMethod(objects[OID_MAIN], WM_HANDLEINPUT, &code)) != WMHI_LASTMSG)
                        {
                            switch (result & WMHI_CLASSMASK)
                            {
                                case WMHI_CLOSEWINDOW:
                                    windows[WID_MAIN] = NULL;
                                    done = TRUE;
                                    break;

                                case WMHI_ICONIFY:
                                    IIntuition->IDoMethod(objects[OID_MAIN], WM_ICONIFY);
                                    windows[WID_MAIN] = NULL;
                                    break;

                                case WMHI_UNICONIFY:
                                    windows[WID_MAIN] = (struct Window *)IIntuition->IDoMethod(objects[OID_MAIN], WM_OPEN);
                                    break;
                            }
                        }
                    }
                }
            }

            /* Disposing of the window object will also close the window if it is
             * already opened, and it will dispose of the layout object attached to it.
             */
            IIntuition->DisposeObject(objects[OID_MAIN]);
        }

    }

    IExec->FreeSysObject(ASOT_PORT, AppPort);

    return RETURN_OK;
}
