#include "Batch.h"

CLuceBatch *CLuceBatch_new( int prealloc ) {
	CLuceBatch *self = malloc( sizeof *self );
	return self;	
}

void CLuceBatch_delete( CLuceBatch *self ) {
	if ( self ) {
		free( self );
	}
}
