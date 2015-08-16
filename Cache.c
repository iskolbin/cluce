#include "Cache.h"
#include "FramesList.h"
#include "Batch.h"
#include <stdlib.h>

CLuceCache *CLuceCache_new( size_t framesListsAlloc, size_t batchesAlloc ) {
	CLuceCache *self = malloc( sizeof *self );
	DYNAMIC_ARRAY_ALLOC( self->framesLists, framesListsAlloc );	
	DYNAMIC_ARRAY_ALLOC( self->batches, batchesAlloc );
	return self;
}

void CLuceCache_delete( CLuceCache *self ) {
	if ( self ) {
		DYNAMIC_ARRAY_DELETE( self->framesLists, CLuceFramesList_delete );
		DYNAMIC_ARRAY_DELETE( self->batches, CLuceBatch_delete );
		free( self );
	}
}

CLuceBatch *CLuceCache_createBatch( CLuceCache *self, size_t widgetsAlloc ) {
	CLuceBatch *batch = CLuceBatch_new( widgetsAlloc );
	DYNAMIC_ARRAY_PUSH( self->batches, batch );
	return DYNAMIC_ARRAY_PEEK( self->batches );
}

CLuceFramesList *CLuceCache_createFramesList( CLuceCache *self, size_t framesAlloc ) {
	CLuceFramesList *framesList = CLuceFramesList_new( framesAlloc );
	DYNAMIC_ARRAY_PUSH( self->framesLists, framesList );
	return DYNAMIC_ARRAY_PEEK( self->framesLists );
}
