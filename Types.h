#ifndef CLUCE_TYPES_H_
#define CLUCE_TYPES_H_

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

	CLUCE_N_ATTRS,
} CLuceAttrName;

#define CLUCE_WIDGET_SIZE ((size_t)CLUCE_N_ATTRS)

typedef struct CLuceFramesList {
	CLuceAttr *frames;
	int framesCount;
} CLuceFramesList;

struct CLuceWidget {
	CLuceAttr attr[CLUCE_N_ATTRS];
	CLuceAttr attrWld[CLUCE_N_ATTRS];
	CLuceAttr frameIdx;
	CLuceFramesList *framesList;

	struct CLuceBatch *batch;
	size_t shift;
	
	struct CLuceWidget *parent;
	struct CLuceWidget *head;
	struct CLuceWidget *next;
	struct CLuceWidget *prev;
};

typedef struct CLuceAtlasFrame {
	int rect[4];
	int spriteRect[4];
	int sourceSize[2];
	int trimmed;
	int rotated;	
} CLuceAtlasFrame;

typedef struct CLuceAtlas {
	struct CLuceAtlasFrame *frames;
	int framesAlloc;
	int framesCount;
} CLuceAtlas;

typedef struct CLuceBatch {
	struct CLuceWidget *widgets;
	int widgetsCount;
	int widgetsAlloc;
	CLuceAttr *renderList;
} CLuceBatch;

typedef struct CLuceWidget CLuceWidget;

#endif
