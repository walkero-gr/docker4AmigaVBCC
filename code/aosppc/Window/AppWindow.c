/* AppWindow Example
gcc -o AppWindow AppWindow.c -lauto
vc +aosppc -I$AOS4_SDK_INC -lauto AppWindow.c -o AppWindow
quit
*/

/**
 **  AppWindow.c -- Application Window Example.
 **
 **  Here we attempt to show how an appwindow (and appicon) can be used
 **  to detect a drag'n'drop event. Messages are received at the app msgport
 **  and then we determine what type of event caused it. We simply print out
 **  the arguments passed, in the real world you might want to do more!
 **/

#include <workbench/workbench.h>
#include <workbench/startup.h>
#include <classes/window.h>
#include <gadgets/button.h>
#include <gadgets/layout.h>

#include <proto/intuition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/window.h>
#include <proto/layout.h>
#include <proto/button.h>

enum
{
    WID_MAIN=0,
    WID_LAST
};

enum
{
    OID_MAIN=0,
    OID_LAST
};

int main()
{
    struct MsgPort *AppPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE);

    struct Window *windows[WID_LAST];

    struct AppMessage *appmsg;
    struct WBArg *argptr;
    TEXT argname[1024];

    Object *objects[OID_LAST];

    // Make sure class files were loaded.
    if ( WindowBase == NULL || LayoutBase == NULL || ButtonBase == NULL)
        return RETURN_FAIL;
    else

    if ( AppPort != NULL )
    {
        // Create the window object.
        objects[OID_MAIN] = IIntuition->NewObject(NULL, "window.class",
            WA_ScreenTitle, "AppWindow Demo",
            WA_Title, "AppWindow Example",
            WA_Activate, TRUE,
            WA_DepthGadget, TRUE,
            WA_DragBar, TRUE,
            WA_CloseGadget, TRUE,
            WA_SizeGadget, TRUE,
            WINDOW_IconifyGadget, TRUE,
            WINDOW_AppPort, AppPort,
            WINDOW_AppWindow, TRUE,
            WINDOW_Position, WPOS_CENTERMOUSE,
            WINDOW_Layout, IIntuition->NewObject(NULL, "layout.gadget",
                LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
                LAYOUT_SpaceOuter, TRUE,
                LAYOUT_DeferLayout, TRUE,
                LAYOUT_AddChild, IIntuition->NewObject(NULL, "button.gadget",
                    GA_Text, "Drop icons here",
                    BUTTON_BevelStyle, BVS_NONE,
                    GA_ReadOnly, TRUE,
                TAG_DONE),
           TAG_DONE),
        TAG_DONE);

        //  Object creation sucessful?

        if (objects[OID_MAIN])
        {
            //  Open the window.

            if (windows[WID_MAIN] = (struct Window *)IIntuition->IDoMethod(objects[OID_MAIN], WM_OPEN))
            {
                ULONG wait, signal, app = (1L << AppPort->mp_SigBit);
                ULONG done = FALSE;
                ULONG result;
                UWORD code;

                // Obtain the window wait signal mask.

                IIntuition->GetAttr(WINDOW_SigMask, objects[OID_MAIN], &signal);

                // Input Event Loop

                while (!done)
                {
                    wait = IExec->Wait( signal | SIGBREAKF_CTRL_C | app );

                    if ( wait & SIGBREAKF_CTRL_C ) {

                        done = TRUE;
                        break;
                    }

                    if ( wait & app ) {

                        // we have been signalled to tell us a message is waiting at the port. The message type (am_Type)
                        // indicates what kind of message. We are only interested in two types, an icon being dragged into the window,
                        // and a uniconification message. We can easily tell this by the code below:-

                        // get the message from the port...
                        if (appmsg = (struct AppMessage *)IExec->GetMsg( AppPort)) {

                            // here we just print some info about the message
                            IDOS->Printf("AppMsg: Type=%ld, ID=%ld, NumArgs=%ld\n", appmsg->am_Type, appmsg->am_ID, appmsg->am_NumArgs );

                            // now lets react on the message type
                            switch (appmsg->am_Type) {

                                // the appicon was triggered, but there could be two reasons...
                                case AMTYPE_APPICON:

                                    // if no args, we need to uniconify (which is the same code as the WMHI_UNICONIFY code would be below
                                    if (appmsg->am_NumArgs == 0) {
                                        windows[WID_MAIN] = (struct Window *) IIntuition->IDoMethod(objects[OID_MAIN], WM_OPEN);
                                        if (windows[WID_MAIN])
                                            IIntuition->GetAttr(WINDOW_SigMask, objects[OID_MAIN], &signal);
                                        else
                                            done = TRUE;    // error re-opening window!

                                        break;
                                    }

                                    // but, we might have an icon dropped on us while iconified. In which case, set the message type
                                    // the same as an appwindow message, and let the switch/case block sort it out
                                    else appmsg->am_Type = AMTYPE_APPWINDOW;


                                case AMTYPE_APPWINDOW:

                                    // an icon was dropped, so get the arguments from the message
                                    argptr = appmsg->am_ArgList;

                                    int t;
                                    for (t = 0; t < appmsg->am_NumArgs; t++ ) {

                                        // for fun, just print out all arguments passed, including multiple icons
                                        IDOS->Printf("arg(%ld} : Name='%s', Lock=%p\n", t, argptr->wa_Name, BADDR(argptr->wa_Lock));
                                        IDOS->NameFromLock( argptr->wa_Lock, argname, sizeof(argname) );
                                        IDOS->Printf("wa_Lock: %s\n", argname );
                                        argptr++;
                                    }
                                    break;

                                // finally pass the message back the OS, to show we are finished
                                IExec->ReplyMsg( (struct Message *)appmsg );

                            }

                        }

                    }

                    if ( wait & signal ) {

                        while ( (result = IIntuition->IDoMethod(objects[OID_MAIN], WM_HANDLEINPUT, &code) ) != WMHI_LASTMSG )
                        {
                            switch (result & WMHI_CLASSMASK)
                            {
                                case WMHI_CLOSEWINDOW:
                                    windows[WID_MAIN] = NULL;
                                    done = TRUE;
                                    break;

                                case WMHI_ICONIFY:
                                    // normal ReAction iconification is handled here
                                    IIntuition->IDoMethod(objects[OID_MAIN], WM_ICONIFY);
                                    windows[WID_MAIN] = NULL;
                                    break;

                                case WMHI_UNICONIFY:
                                    // normally you would uniconify the window here, but this is handled
                                    // in the section that deals with the app message. This is now redundant
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

