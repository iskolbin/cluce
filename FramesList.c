#include "FramesList.h"

CLuceFramesList *CLuceFramesList_new( size_t framesAlloc ) {
	CLuceFramesList *self = malloc( sizeof *self );
	DYNAMIC_ARRAY_ALLOC(self->frames,framesAlloc);
	return self;
}

void CLuceFramesList_delete( CLuceFramesList *self ) {
	if ( self ) {
		DYNAMIC_ARRAY_FREE(self->frames);
		free( self );
	}
}


size_t CLuceFramesList_add( CLuceFramesList *self, int id, int x, int y, int w, int h, int xoffset, int yoffset, CLuceFrameFlag flags ) {
	CLuceFrame frame = {id,x,y,w,h,xoffset,yoffset,flags};
	DYNAMIC_ARRAY_PUSH(self->frames,frame);
	return self->framesCount - 1;
}	
