#ifndef CLUCE_WIDGET_H_
#define CLUCE_WIDGET_H_

#include <stdlib.h>
#include <string.h>
#include "Types.h"

#define CLuceWidget_get(self,attr) ((self)->attr[(attr)])

#define CLuceWidget_set(self,attr,value) \
	((self)->attr[(attr)]=value); \
	CLuce_update((self),(attr))	

#define CLuceWidget_setPos(self,x,y) \
	CLuceWidget_set((self),CLUCE_ATTR_X,(x)); \
	CLuceWidget_set((self),CLUCE_ATTR_Y,(y))

#define CLuceWidget_setScl(self,xscl,yscl) \
	CLuceWidget_set((self),CLUCE_ATTR_XSCL,(xscl)); \
	CLuceWidget_set((self),CLUCE_ATTR_YSCL,(yscl))

#define CLuceWidget_setPiv(self,xpiv,ypiv) \
	CLuceWidget_set((self),CLUCE_ATTR_XPIV,(xpiv)); \
	CLuceWidget_set((self),CLUCE_ATTR_YPIV,(ypiv))

#define CLuceWidget_setRGB(self,r,g,b) \
	CLuceWidget_set((self),CLUCE_ATTR_RED,(r)); \
	CLuceWidget_set((self),CLUCE_ATTR_GREEN,(g)); \
	CLuceWidget_set((self),CLUCE_ATTR_BLUE,(b))

#define CLuceWidget_setRGBA(self,r,g,b,a) \
	CLuceWidget_set((self),CLUCE_ATTR_RED,(r)); \
	CLuceWidget_set((self),CLUCE_ATTR_GREEN,(g)); \
	CLuceWidget_set((self),CLUCE_ATTR_BLUE,(b)); \
	CLuceWidget_set((self),CLUCE_ATTR_ALPHA,(a)); 

#define CLuceWidget_setAlpha(self,alpha) CLuceWidget_set((self),CLUCE_ATTR_ALPHA,(alpha))

#define CLuceWidget_setRot(self,rot) CLuceWidget_set((self),CLUCE_ATTR_ROT,(rot))

CLuceWidget * CLuceWidget_new( void );
void CLuceWidget_delete( CLuceWidget *self );
void CLuceWidget_update( CLuceWidget *self, CLuceAttrName attr );
void CLuceWidget_setParent( CLuceWidget *self, CLuceWidget *parent );
//CLuceTween *CLuceWidget_move( CLuceWidget *self, CLuceAttrName attr, CLuceAttr value, CLuceTweenTime length, CLuceTweenEase ease, CLuceTweenAfter after ); 

#endif
