
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

void handleMenu (struct Window *win, struct Menu *menuStrip);

#endif



