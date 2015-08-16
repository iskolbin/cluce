#ifndef CLUCE_TYPES_H_
#define CLUCE_TYPES_H_

#include <stdlib.h>
#include <stdio.h>
#include "DynamicArray.h"

typedef float CLuceAttr;

typedef enum {
	CLUCE_ATTR_X,
	CLUCE_ATTR_Y,
	CLUCE_ATTR_FRAME,
	CLUCE_ATTR_XSCL,
	CLUCE_ATTR_YSCL,
	CLUCE_ATTR_ROT,
	CLUCE_ATTR_XPIV,
	CLUCE_ATTR_YPIV,
	CLUCE_ATTR_RED,
	CLUCE_ATTR_GREEN,
	CLUCE_ATTR_BLUE,
	CLUCE_ATTR_ALPHA,

} CLuceAttrName;

#define CLUCE_N_ATTRS (CLUCE_ATTR_ALPHA+1)

#define CLUCE_WIDGET_SIZE ((size_t)CLUCE_N_ATTRS)

typedef enum {
	CLUCE_FRAME_TRIMMED,
	CLUCE_FRAME_ROTATED,
} CLuceFrameFlag;

typedef struct CLuceFrame {
	int id;
	int x;
	int y;
	int w;
	int h;
	int xoffset;
	int yoffset;
	CLuceFrameFlag flags;	
} CLuceFrame;

typedef struct CLuceFramesList {
	DYNAMIC_ARRAY_DECLARE(frames,CLuceFrame);
} CLuceFramesList;

struct CLuceWidget {
	CLuceAttr attr[CLUCE_N_ATTRS];
	CLuceAttr attrWld[CLUCE_N_ATTRS];
	CLuceFramesList *framesList;
	struct CLuceBatch *batch;
	struct CLuceWidget *parent;
	struct CLuceWidget *head;
	struct CLuceWidget *next;
	struct CLuceWidget *prev;
};

#define CLUCE_WIDGET_STRUCT_INITIALIZER(batch,framesList) {{0,0,0,1,1,0,0,0,1,1,1,1},{0,0,0,1,1,0,0,0,1,1,1,1},(framesList),(batch),NULL,NULL,NULL,NULL}

typedef struct CLuceWidget CLuceWidget;

typedef struct CLuceBatch {
	DYNAMIC_ARRAY_DECLARE(widgets,CLuceWidget);	
	int altered;
} CLuceBatch;

#endif
