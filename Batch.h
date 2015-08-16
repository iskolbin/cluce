#ifndef CLUCE_BATCH_H_
#define CLUCE_BATCH_H_

#include <string.h>
#include <stdlib.h>
#include "Types.h"

CLuceBatch *CLuceBatch_new( size_t widgetsAlloc );

void CLuceBatch_delete( CLuceBatch *self );
CLuceWidget *CLuceBatch_createWidget( CLuceBatch *self, CLuceFramesList *frames );

#endif
