#ifndef MAINWORKAREA_H
#define MAINWORKAREA_H

struct EasyStruct failedES = {
    sizeof(struct EasyStruct), 0, "CWB",
    "%s",
    "OK",
};

struct RenderEngineData
{
	struct Window* window;
	BOOL run;
};



#endif

