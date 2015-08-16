#ifndef CLUCE_CACHE_H_
#define CLUCE_CACHE_H_

#include "Types.h"
#include "DynamicArray.h"

typedef struct CLuceCache {
	DYNAMIC_ARRAY_DECLARE(framesLists,CLuceFramesList*);
	DYNAMIC_ARRAY_DECLARE(batches,CLuceBatch*);
} CLuceCache;

CLuceCache *CLuceCache_new( size_t framesListAlloc, size_t batchAlloc );
void CLuceCache_delete( CLuceCache *self );
CLuceBatch *CLuceCache_createBatch( CLuceCache *self, size_t widgetsAlloc );
CLuceFramesList *CLuceCache_createFramesList( CLuceCache *self, size_t framesAlloc );

#endif
