/* Window Popup Example
gcc -o WindowPopup windowpopup.c -lauto
vc +aosppc -I$AOS4_SDK_INC -lauto WindowPopup.c -o WindowPopup
quit
*/

/**
 **  WindowPopup.c -- Window Popup menu example.
 **
 **  This example shows how the new popup menu can be used, and 
 **  expanded by adding custom items.
 **/

#include <workbench/workbench.h>
#include <workbench/startup.h>
#include <classes/window.h>
#include <classes/popupmenu.h>
#include <gadgets/checkbox.h>
#include <gadgets/layout.h>

#include <proto/intuition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/window.h>
#include <proto/popupmenu.h>
#include <proto/layout.h>
#include <proto/checkbox.h>

// we make these global so the hook can query them
struct Gadget *CBFirst, *CBSecond, *ShowScreens;


// these are the ID numbers for the custom popupmenu items which are
// returned in the lower word when a WMHI_POPUPMENU event is received.
enum
{
    POPUP_FIRST = 1,
    POPUP_SECOND,
    POPUP_LAST
};


// we create a hook here which will add the custom menu options. Any items you add
// will be disposed of automatically when the menu is closed. There is no need for
// any sort of post-processing, it is all handled for you.

LONG PopupHookFunc( struct Hook *hook, APTR popupmenu, UNUSED APTR reserved )
{
    // This hook gets called by window.class everytime the popup menu
    // gadget is clicked. 
    LONG firstval, secondval;
    APTR item;
    LONG added = 0;
    
    // get the checkbox states so we know what to add.
    IIntuition->GetAttrs( CBFirst, GA_Selected, &firstval, TAG_DONE );
    IIntuition->GetAttrs( CBSecond, GA_Selected, &secondval, TAG_DONE );
    
    if( firstval || secondval )
    {
        // We will be adding at least one item, so add a separator item to 
        // give a visual distinction between standard and custom options
        
        if(( item = IIntuition->NewObject( IPopupMenu->POPUPMENU_GetItemClass(), NULL,
            PMIA_WideTitleBar, TRUE,
            TAG_DONE )))
        {
            if(!( IIntuition->IDoMethod( popupmenu, PM_INSERT, item, ~0 )))
            {
                IIntuition->DisposeObject( item );
            }
            else
            {
                added++;
            }
        }
    }
    
    if( firstval )
    {
        // create the first item and add it to the popup object
        
        if(( item = IIntuition->NewObject( IPopupMenu->POPUPMENU_GetItemClass(), NULL,
            PMIA_Title, (ULONG) "Custom First Option",
            PMIA_ID, (ULONG)POPUP_FIRST,
            TAG_DONE )))
        {
            if(!( IIntuition->IDoMethod( popupmenu, PM_INSERT, item, ~0 )))
            {
                IIntuition->DisposeObject( item );
            }
            else
            {
                added++;
            }
        }
    }
    
    if( secondval )
    {
        // create the second item and add it to the popup object
        
        if(( item = IIntuition->NewObject( IPopupMenu->POPUPMENU_GetItemClass(), NULL,
            PMIA_Title, (ULONG) "Custom Second Option",
            PMIA_ID, (ULONG)POPUP_SECOND,
            TAG_DONE )))
        {
            if(!( IIntuition->IDoMethod( popupmenu, PM_INSERT, item, ~0 )))
            {
                IIntuition->DisposeObject( item );
            }
            else
            {
                added++;
            }
        }
    }
    
    // the return code is the amount of items added. This is used by window.class
    // to determine if the menu is empty or not.
    return added;
}


int main()
{
    struct MsgPort *AppPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE);

    Object *obj;
    struct Window *win;
    struct Hook popuphook;
    
    enum
    {
        GID_SHOWSCREENS = 1,
        GID_LAST
    };
    
    popuphook.h_Entry = (HOOKFUNC)PopupHookFunc;
    popuphook.h_SubEntry = NULL;
    popuphook.h_Data = NULL;
    
    
    // Make sure class files were loaded.
    if ( WindowBase == NULL || LayoutBase == NULL || CheckBoxBase == NULL)
        return RETURN_FAIL;
    else

    if ( AppPort != NULL )
    {
        // Create the window object.
        obj = IIntuition->NewObject(NULL, "window.class",
            WA_ScreenTitle, "Window Popup Demo",
            WA_Title, "Window Popup Example",
            WA_Activate, TRUE,
            WA_DepthGadget, TRUE,
            WA_DragBar, TRUE,
            WA_CloseGadget, TRUE,
            WA_SizeGadget, TRUE,
            WA_InnerWidth, 300,
            WINDOW_IconifyGadget, TRUE,
            WINDOW_PopupGadget, TRUE,
            WINDOW_PopupHook, popuphook,
            WINDOW_AppPort, AppPort,
            WINDOW_AppWindow, TRUE,
            WINDOW_Position, WPOS_CENTERMOUSE,
            WINDOW_Layout, IIntuition->NewObject(NULL, "layout.gadget",
                LAYOUT_Orientation, LAYOUT_ORIENT_VERT,
                LAYOUT_SpaceOuter, TRUE,
                LAYOUT_DeferLayout, TRUE,
                LAYOUT_AddChild, ShowScreens = (struct Gadget *)IIntuition->NewObject(NULL, "checkbox.gadget",
                    GA_Text, "Show Screens Menu",
                    GA_ID, GID_SHOWSCREENS,
                    GA_RelVerify, TRUE,
                TAG_DONE),
                LAYOUT_AddChild, CBFirst = (struct Gadget *)IIntuition->NewObject(NULL, "checkbox.gadget",
                    GA_Text, "Add First item",
                TAG_DONE),
                LAYOUT_AddChild, CBSecond = (struct Gadget *)IIntuition->NewObject(NULL, "checkbox.gadget",
                    GA_Text, "Add Second Item",
                TAG_DONE),
           TAG_DONE),
        TAG_DONE);

        //  Object creation sucessful?
        if (obj)
        {
            //  Open the window.
            if (win = (struct Window *)IIntuition->IDoMethod(obj, WM_OPEN))
            {
                ULONG wait, signal, app = (1L << AppPort->mp_SigBit);
                ULONG done = FALSE;
                ULONG result;
                UWORD code;

                // Obtain the window wait signal mask.
                IIntuition->GetAttr(WINDOW_SigMask, obj, &signal);

                // Input Event Loop
                while (!done)
                {
                    wait = IExec->Wait( signal | SIGBREAKF_CTRL_C | app );

                    if ( wait & SIGBREAKF_CTRL_C ) 
                    {
                        done = TRUE;
                        break;
                    }

                    // app messages are ignored in this example
                    
                    if ( wait & signal ) 
                    {
                        while ( (result = IIntuition->IDoMethod(obj, WM_HANDLEINPUT, &code) ) != WMHI_LASTMSG )
                        {
                            switch (result & WMHI_CLASSMASK)
                            {
                                case WMHI_CLOSEWINDOW:
                                    win = NULL;
                                    done = TRUE;
                                    break;

                                case WMHI_ICONIFY:
                                    // normal ReAction iconification is handled here
                                    IIntuition->IDoMethod(obj, WM_ICONIFY);
                                    win = NULL;
                                    break;

                                case WMHI_UNICONIFY:
                                    // normal ReAction uniconification is handled here
                                    if(( win = (struct Window *) IIntuition->IDoMethod(obj, WM_OPEN)))
                                        IIntuition->GetAttr(WINDOW_SigMask, obj, &signal);
                                    break;
                                
                                case WMHI_JUMPSCREEN:
                                {
                                    // The user wants this window object to jump to another screen.
                                    // We get the pointer to the screen from the window object, 
                                    // close the window, set the screen and reopen it. Setting the
                                    // screen pointer is required as the WA_PubScreen attribute is
                                    // only used as a storage area for the new screen pointer so
                                    // that your code can get access to it.
                                    // Some window objects may need to do some extra disposal when
                                    // the object is closed, which is why we need to handle the 
                                    // jump manually. It is not possible to automate this and handle
                                    // every possible situation with any degree of reliability.
                                    
                                    struct Screen *screen;
                                    IIntuition->GetAttrs( obj, WA_PubScreen, &screen, TAG_DONE );
                                    if( screen )
                                    {
                                        IDOS->Printf("The window is moving to screen: %p\n", screen );
                                        
                                        IIntuition->IDoMethod(obj, WM_CLOSE );
                                        
                                        IIntuition->SetAttrs( obj, WA_PubScreen, screen, TAG_DONE );
                                        
                                        if(( win = (struct Window *)IIntuition->IDoMethod(obj, WM_OPEN )))
                                        {
                                            IIntuition->GetAttr(WINDOW_SigMask, obj, &signal);
                                            
                                            // now bring the screen to the front.
                                            IIntuition->ScreenToFront( screen );
                                        }
                                    }
                                    
                                }
                                break;
                                        
                                case WMHI_POPUPMENU:
                                {   
                                    //get the ID from the mask just like we do for gadgets.
                                    
                                    switch (result & WMHI_GADGETMASK)
                                    {
                                        case POPUP_FIRST:
                                            IDOS->Printf("First item selected\n");
                                            break;
                                            
                                        case POPUP_SECOND:
                                            IDOS->Printf("Second item selected\n");
                                            break;
                                    }
                                }
                                break;
                                
                                case WMHI_GADGETUP:
                                {
                                    switch (result & WMHI_GADGETMASK)
                                    {
                                        case GID_SHOWSCREENS:
                                            // this checkbox toggles the "Jump to screen" menu on and off
                                            IIntuition->SetAttrs( obj, WINDOW_JumpScreensMenu, (code?TRUE:FALSE), TAG_DONE );
                                            break;
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }

            /* Disposing of the window object will also close the window if it is
             * already opened, and it will dispose of the layout object attached to it.
             */
            IIntuition->DisposeObject(obj);
        }

    }

    IExec->FreeSysObject(ASOT_PORT, AppPort);

    return RETURN_OK;
}

