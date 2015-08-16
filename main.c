#include "LuaBindings.h"

int main( int argc, char *argv[] ) {
//	CLuceBatch *batch = CLuceBatch_new( 1 );
//	CLuceFramesList *frames = CLuceFramesList_new( 1 );
//	CLuceWidget *widget = CLuceBatch_createWidget( batch, frames );
//	CLuceRenderable renderable = {CLUCE_BATCH,batch};

//	CLuceFramesList_addUnit( frames, 0, 640, 480, 0 );
//	CLuceSDLApplication_init("Test", 0, 0, 640, 480, 0, 0, -1, 60 );
//	CLuceSDLApplication_addTexture( "test.png" );
//	CLuceSDLApplication_addRenderable( renderable );
//	CLuceSDLApplication_run();	
	lua_State *L = luaL_newstate();
	CLuceLuaBindings_run( L );	
	lua_close( L );
	return 0;
}

