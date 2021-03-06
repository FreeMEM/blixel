
#include <exec/types.h>
#include <exec/memory.h>
#include <graphics/text.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>

#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>


/*  These values are based on the ROM font Topaz8. Adjust these  */
/*  values to correctly handle the screen's current font.        */
#define MENWIDTH  (56+8)  /* Longest menu item name * font width */
                          /* + 8 pixels for trim                 */
#define MENHEIGHT (10)    /* Font height + 2 pixels              */
/* We only use a single menu, but the code is generalizable to */
/* more than one menu.                                         */

#define NUM_MENUS 1


struct Library *GfxBase;
struct Library *IntuitionBase;
STRPTR menutitle[NUM_MENUS] =  {   "Project"   };

/* To keep this example simple, we'll hard-code the font used for menu */
/* items.  Algorithmic layout can be used to handle arbitrary fonts.   */
/* Under Release 2, GadTools provides font-sensitive menu layout.      */
/* Note that we still must handle fonts for the menu headers.          */
struct TextAttr Topaz80 =
{
    "topaz.font", 8, 0, 0
};

struct IntuiText menuIText[] =
{
    { 0, 1, JAM2, 0, 1, &Topaz80, "Open...",  NULL },
    { 0, 1, JAM2, 0, 1, &Topaz80, "Save",     NULL },
    { 0, 1, JAM2, 0, 1, &Topaz80, "Print \273",  NULL },
    { 0, 1, JAM2, 0, 1, &Topaz80, "Draft",    NULL },
    { 0, 1, JAM2, 0, 1, &Topaz80, "NLQ",      NULL },
    { 0, 1, JAM2, 0, 1, &Topaz80, "Quit",     NULL }
};

struct MenuItem submenu1[] =
{
    { /* Draft  */
        &submenu1[1], 
        MENWIDTH-2,
        -2 ,
        MENWIDTH,
        MENHEIGHT,
        ITEMTEXT | MENUTOGGLE | ITEMENABLED | HIGHCOMP,
        0,
        (APTR)&menuIText[3],
        NULL,
        NULL,
        NULL,
        NULL
    },
    { /* NLQ    */
    NULL,         MENWIDTH-2, MENHEIGHT-2, MENWIDTH, MENHEIGHT,
    ITEMTEXT | MENUTOGGLE | ITEMENABLED | HIGHCOMP,
    0, (APTR)&menuIText[4], NULL, NULL, NULL, NULL
    }
};

struct MenuItem menu1[] =
{
    { /* Open... */
    &menu1[1], 0, 0,            MENWIDTH, MENHEIGHT,
    ITEMTEXT | MENUTOGGLE | ITEMENABLED | HIGHCOMP,
    0, (APTR)&menuIText[0], NULL, NULL, NULL, NULL
    },
    { /* Save    */
    &menu1[2], 0,  MENHEIGHT ,  MENWIDTH, MENHEIGHT,
    ITEMTEXT | MENUTOGGLE | ITEMENABLED | HIGHCOMP,
    0, (APTR)&menuIText[1], NULL, NULL, NULL, NULL
    },
    { /* Print   */
    &menu1[3], 0, 2*MENHEIGHT , MENWIDTH, MENHEIGHT,
    ITEMTEXT | MENUTOGGLE | ITEMENABLED | HIGHCOMP,
    0, (APTR)&menuIText[2], NULL, NULL, &submenu1[0] , NULL
    },
    { /* Quit    */
    NULL, 0, 3*MENHEIGHT , MENWIDTH, MENHEIGHT,
    ITEMTEXT | MENUTOGGLE | ITEMENABLED | HIGHCOMP,
    0, (APTR)&menuIText[5], NULL, NULL, NULL, NULL
    },
};


struct Menu menustrip[NUM_MENUS] =
{
    {
    NULL,                    /* Next Menu          */
    0, 0,                    /* LeftEdge, TopEdge, */
    0, MENHEIGHT,            /* Width, Height,     */
    MENUENABLED,             /* Flags              */
    NULL,                    /* Title              */
    &menu1[0]                /* First item         */
    }
};

/* To keep this example simple, we'll hard-code the font used for menu */
/* items.  Algorithmic layout can be used to handle arbitrary fonts.   */
/* Under Release 2, GadTools provides font-sensitive menu layout.      */
/* Note that we still must handle fonts for the menu headers.          */



/*
**   Wait for the user to select the close gadget.
*/
VOID handleMenu(struct Window *win, struct Menu *menuStrip) {
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
                        // printf("IDCMP_MENUPICK: menu %d, item %d, sub %d\n",
                        //     menuNum, itemNum, subNum);

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
