
#include <intuition/intuition.h>
#include <intuition/screens.h>
#include <graphics/gfxbase.h>

#include <pragmas/exec_pragmas.h>
#include <pragmas/intuition_pragmas.h>
#include <pragmas/graphics_pragmas.h>

struct IntuitionBase *IntuitionBase = NULL;
struct GfxBase *GfxBase = NULL;
// extern struct Library *SysBase;

struct EasyStruct failedES = {
    sizeof(struct EasyStruct), 0, "CWB",
    "%s",
    "OK",
};


void screen() {
    struct Screen *wbscreen = NULL;
    struct Screen *clonescreen = NULL;
    struct Window *window = NULL;
    struct ViewPort *vp = NULL;
    struct IntuiMessage *msg = NULL;
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

                    // result = GetDisplayInfoData(NULL,
                    //                             (UBYTE *)&monitorinfo,
                    //                             sizeof(struct MonitorInfo),
                    //                             DTAG_MNTR, modeID);
                    // result = GetDisplayInfoData(NULL,
                    //                             (UBYTE *)&displayinfo,
                    //                             sizeof(struct DisplayInfo),
                    //                             DTAG_DISP, modeID);
                    // result = GetDisplayInfoData(NULL,
                    //                             (UBYTE *)&dimensioninfo,
                    //                             sizeof(struct DimensionInfo),
                    //                             DTAG_DIMS,
                    //                             modeID);
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
                        SA_Title, nameinfo.Name,
                        /* Doesn't hurt for screens which don't scroll */
                        SA_AutoScroll, TRUE,
                        TAG_DONE))) {

                        if (NULL != (window = OpenWindowTags(NULL,
                            WA_Top, clonescreen->BarHeight + 1,
                            WA_Height, clonescreen->Height
                                                - (clonescreen->BarHeight + 1),
                            WA_CustomScreen, clonescreen,
                            WA_MinWidth, 320,
                            WA_MinHeight, 100,
                            WA_MaxWidth, clonescreen->Width,
                            WA_MaxHeight, clonescreen->Height,

                            /* I'm only interested in CLOSEWINDOW messages */
                            WA_IDCMP, CLOSEWINDOW,
                            WA_Flags, WINDOWSIZING|WINDOWDRAG|
                                           WINDOWDEPTH|WINDOWCLOSE|ACTIVATE,
                            WA_Title, "Close to exit.",
                            TAG_DONE))) {

                            /* Wait for the closewindow message */
                            WaitPort(window->UserPort);
                            /* And remove message from the port */
                            while(NULL != (msg = (struct IntuiMessage *)GetMsg(window->UserPort))) {
                                ReplyMsg((struct Message *)msg);
                            }
                            CloseWindow(window);
                        } else 
                            EasyRequest(NULL, &failedES, NULL,"Can't open window");
                        CloseScreen(clonescreen);
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
