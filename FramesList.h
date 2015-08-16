#ifndef CLUCE_FRAME_LIST_H_
#define CLUCE_FRAME_LIST_H_

#include <stdlib.h>
#include <limits.h>
#include "Types.h"
#include "DynamicArray.h"

CLuceFramesList *CLuceFramesList_new( size_t framesAlloc );
void CLuceFramesList_delete( CLuceFramesList *self );
size_t CLuceFramesList_add( CLuceFramesList *self, int id, int x, int y, int w, int h, int xoffset, int yoffset, CLuceFrameFlag flags ); 

#define CLuceFramesList_addUnit(self,id,w,h,flags)	(CLuceFramesList_add((self),(id),0,0,(w),(h),0,0,(flags)))

#endif
