#include "Batch.h"
#include "SDLRenderer.h"

int main( int argc, char *argv[] ) {
	CLuceBatch *batch = CLuceBatch_new( 10 );
	CLuceSDLRenderer *renderer = CLuceSDLRenderer_new((const char *) "Test", 0, 0, 640, 480, 0, 0, -1 );
	CLuceSDLRenderer_delete( renderer );
	CLuceBatch_delete( batch );
	return 0;
}

