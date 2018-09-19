
#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <graphics/gfxbase.h>
#include <string.h>

#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>



// #include "includes/mainworkarea.h"
// #include "includes/toolbox.h"
// #include "includes/framearea.h"
// #include "includes/frameedition.h"
#include "includes/screen.h"


/* We only use a single menu, but the code is generalizable to */
/* more than one menu.                                         */

struct EasyStruct failedES = {
    sizeof(struct EasyStruct), 0, "CWB",
    "%s",
    "OK",
};




void createScreen() {
    struct IntuitionBase *IntuitionBase = NULL;
    struct GfxBase *GfxBase = NULL;
    struct Screen *wbscreen = NULL;
    struct Screen *clonescreen = NULL;
    struct ViewPort *vp = NULL;

    ULONG modeID;
    struct NameInfo nameinfo;
    struct DrawInfo *drawinfo;

    ULONG result;

    

    /* Fails silently when not V37 */
    IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library",37L);
    GfxBase = (struct GfxBase *)OpenLibrary("graphics.library",37L);
    wbscreen = LockPubScreen("Workbench");

    if ( IntuitionBase != NULL ) {
        if ( GfxBase != NULL ) {
            if ( wbscreen) {
                /* Using intuition.library/GetScreenDrawInfo(), we get the pen
                 * array we'll use for the screen clone the easy way. */
                drawinfo = GetScreenDrawInfo(wbscreen);

                vp = &(wbscreen->ViewPort);
                /* Use graphics.library/GetVPModeID() to get the ModeID of the
                 * Workbench screen. */
                if ((modeID = GetVPModeID(vp)) != INVALID_ID) {

                    result = GetDisplayInfoData(NULL,
                                                (UBYTE *)&nameinfo,
                                                sizeof(struct NameInfo),
                                                DTAG_NAME,
                                                modeID);


                    if (NULL != (clonescreen = OpenScreenTags(NULL,
                        /* Could use STDSCREENWIDTH/HEIGHT for non-scrollable
                         * screens. Those make */
                        SA_Width, wbscreen->Width,
                        /* OpenScreen() use the textoverscan values */
                        SA_Height, wbscreen->Height,
                        SA_DisplayID, modeID,
                        SA_Depth, wbscreen->BitMap.Depth,
                        /*Workbench always sizes up to OSCAN_TEXT, so do we */
                        SA_Overscan, OSCAN_TEXT,
                        SA_Pens, drawinfo->dri_Pens,
                        SA_Title, "Blixel",
                        /* Doesn't hurt for screens which don't scroll */
                        SA_AutoScroll, TRUE,
                        TAG_DONE))) {
                        } else
                        EasyRequest(NULL, &failedES, NULL,"Can't open screen");
                } else
                    EasyRequest(NULL, &failedES, NULL, "Invalide ModeID");
                FreeScreenDrawInfo(wbscreen, drawinfo);
                UnlockPubScreen(NULL, wbscreen);
            } else 
                EasyRequest(NULL, &failedES, NULL,"Can't lock Workbench screen");
            CloseLibrary((struct Library *)GfxBase);
        }
        CloseLibrary((struct Library *)IntuitionBase);
    }

}

void screen() {

    //crear la screen
    createScreen();
    //llamar a las distintos windows




}