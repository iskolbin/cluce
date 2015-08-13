#ifndef CLUCE_BATCH_H_
#define CLUCE_BATCH_H_

#include <string.h>
#include <stdlib.h>
#include "Types.h"

CLuceBatch *CLuceBatch_new( int prealloc );
void CLuceBatch_delete( CLuceBatch *self );

#endif
