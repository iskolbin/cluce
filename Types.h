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

struct CLuceWidget {
	CLuceAttr attr[CLUCE_N_ATTRS];
	CLuceAttr attrWld[CLUCE_N_ATTRS];
	CLuceAttr frameIdx;
	CLuceAttr *framesList;
	int framesCount;
	
	struct CLuceBatch *batch;
	size_t shift;
	
	struct CLuceWidget *parent;
	struct CLuceWidget *head;
	struct CLuceWidget *next;
	struct CLuceWidget *prev;
};


struct CLuceBatch {
	struct CLuceWidget *widgets;
	int widgetsCount;
	int widgetsAlloc;
	CLuceAttr *renderList;
};

typedef struct CLuceWidget CLuceWidget;
typedef struct CLuceBatch CLuceBatch;

#endif
