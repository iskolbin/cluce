#include "Batch.h"

CLuceBatch *CLuceBatch_new( size_t widgetsAlloc ) {
	CLuceBatch *self = malloc( sizeof *self );
	DYNAMIC_ARRAY_ALLOC(self->widgets,widgetsAlloc);
	self->altered = 1;
	return self;	
}

void CLuceBatch_delete( CLuceBatch *self ) {
	if ( self ) {
		DYNAMIC_ARRAY_FREE(self->widgets);
		free( self );
	}
}

CLuceWidget *CLuceBatch_createWidget( CLuceBatch *self, CLuceFramesList *framesList ) {
	CLuceWidget widget = CLUCE_WIDGET_STRUCT_INITIALIZER(self,framesList);
	DYNAMIC_ARRAY_PUSH(self->widgets,widget);	
	return &DYNAMIC_ARRAY_PEEK(self->widgets);
}
