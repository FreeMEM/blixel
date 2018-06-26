
/*  These values are based on the ROM font Topaz8. Adjust these  */
/*  values to correctly handle the screen's current font.        */

#ifndef MAIN_H
#define MAIN_H

/*  These values are based on the ROM font Topaz8. Adjust these  */
/*  values to correctly handle the screen's current font.        */
#define MENWIDTH  (56+8)  /* Longest menu item name * font width */
                          /* + 8 pixels for trim                 */
#define MENHEIGHT (10)    /* Font height + 2 pixels              */
/* We only use a single menu, but the code is generalizable to */
/* more than one menu.                                         */

#define NUM_MENUS 1
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

/*
struct NewWindow mynewWindow =
{
40,40, 300,100, 0,1, IDCMP_CLOSEWINDOW | IDCMP_MENUPICK,
WFLG_DRAGBAR | WFLG_ACTIVATE | WFLG_CLOSEGADGET, NULL,NULL,
"Menu Test Window", NULL,NULL,0,0,0,0,WBENCHSCREEN
};
*/

/* our function prototypes */
VOID handleWindow(struct Window *win, struct Menu *menuStrip);

#endif



