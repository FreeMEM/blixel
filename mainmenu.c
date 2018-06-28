
#include <exec/types.h>
#include <exec/memory.h>
#include <graphics/text.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>

#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>





struct Library *GfxBase;
struct Library *IntuitionBase;


/* To keep this example simple, we'll hard-code the font used for menu */
/* items.  Algorithmic layout can be used to handle arbitrary fonts.   */
/* Under Release 2, GadTools provides font-sensitive menu layout.      */
/* Note that we still must handle fonts for the menu headers.          */



/*
**   Wait for the user to select the close gadget.
*/
VOID handleWindow(struct Window *win, struct Menu *menuStrip) {
    struct IntuiMessage *msg;
    SHORT done;
    ULONG class;
    UWORD menuNumber;
    UWORD menuNum;
    UWORD itemNum;
    UWORD subNum;
    struct MenuItem *item;

    done = FALSE;
    while (FALSE == done) {
        /* we only have one signal bit, so we do not have to check which
        ** bit broke the Wait().
        */
        Wait(1L << win->UserPort->mp_SigBit);

        while ( (FALSE == done) && (msg = (struct IntuiMessage *)GetMsg(win->UserPort))) {
            class = msg->Class;
            if(class == IDCMP_MENUPICK)   menuNumber = msg->Code;

            switch (class) {
                case IDCMP_CLOSEWINDOW:
                    done = TRUE;
                    break;
                case IDCMP_MENUPICK:
                    while ((menuNumber != MENUNULL) && (!done)) {
                        item = ItemAddress(menuStrip, menuNumber);

                        /* process this item
                        ** if there were no sub-items attached to that item,
                        ** SubNumber will equal NOSUB.
                        */
                        menuNum = MENUNUM(menuNumber);
                        itemNum = ITEMNUM(menuNumber);
                        subNum  = SUBNUM(menuNumber);

                        /* Note that we are printing all values, even things
                        ** like NOMENU, NOITEM and NOSUB.  An application should
                        ** check for these cases.
                        */
                        printf("IDCMP_MENUPICK: menu %d, item %d, sub %d\n",
                            menuNum, itemNum, subNum);

                        /* This one is the quit menu selection...
                        ** stop if we get it, and don't process any more.
                        */
                        if ((menuNum == 0) && (itemNum == 4))
                            done = TRUE;

                        menuNumber = item->NextSelect;
                    }
                break;
            }
            ReplyMsg((struct Message *)msg);
        }
    }
}
