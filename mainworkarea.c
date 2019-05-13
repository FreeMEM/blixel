// #include "includes/mainmenu.h"
#include <exec/types.h>
#include <exec/memory.h>
#include <stdio.h>
#include <graphics/text.h>
#include <intuition/intuition.h>
#include <intuition/intuitionbase.h>

#include <clib/exec_protos.h>
#include <clib/graphics_protos.h>
#include <clib/intuition_protos.h>

struct Window *toolwin = NULL;

void mainWorkarea(struct Screen *clonescreen) {
    // struct Window *window = NULL;
    // struct ViewPort *vp = NULL;
    // struct IntuiMessage *msg = NULL;
    int i=0;
    printf("hola");


      if (NULL != (toolwin = OpenWindowTags(NULL,
                                        WA_Left,
                                        0,
                                        WA_Top, 10,
                                        WA_Width, 80,
                                        WA_Height, 400,
                                        WA_DragBar,
                                        TRUE,
                                        WA_CloseGadget,
                                        TRUE,
                                        WA_SmartRefresh,TRUE,
                                        WA_NoCareRefresh, TRUE,
                                        WA_IDCMP,
                                        IDCMP_CLOSEWINDOW,
                                        WA_Title,
                                        "Tools",
                                        WA_CustomScreen, 
                                        clonescreen,
                                        TAG_END)
                                        )
                                    ){
                                        printf("llegooo");
                                    }


  
  
}