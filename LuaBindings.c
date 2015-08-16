#include "LuaBindings.h"
#include "SDLApplication.h"
#include "Cache.h"
#include "Batch.h"
#include "FramesList.h"
#include "Widget.h"

static int createBatch( lua_State *L ) {
	CLuceBatch *batch = CLuceCache_createBatch( CLuceSDLApplication_instance()->cache, 1 );
	lua_pushlightuserdata( L, batch );
	//printf("L=%p batch=%p\n", L, batch);
	return 1;
}

static int createWidget( lua_State *L ) {
	CLuceBatch *batch = lua_touserdata(L,-2);
	CLuceFramesList *framesList = lua_touserdata(L,-1);
	if ( batch ) {
		//printf("L=%p batch=%p framesList=%p\n", L, batch, framesList );
		lua_pushlightuserdata( L, CLuceBatch_createWidget( batch, framesList ));
		return 1;
	} else {
		return 0;
	}
}

static int createFramesList( lua_State *L ) {
	lua_pushlightuserdata( L, CLuceCache_createFramesList( CLuceSDLApplication_instance()->cache, 1 ));
	return 1;
}

static int addFrame( lua_State *L ) {
	CLuceFramesList *framesList = lua_touserdata(L,-1);
	if ( framesList ) {
		lua_pushnumber( L, CLuceFramesList_add( framesList, 
			lua_tointeger(L,-2), 
			lua_tointeger(L,-3), lua_tointeger(L,-4), lua_tointeger(L,-5), lua_tointeger(L,-6),
			lua_tointeger(L,-7), lua_tointeger(L,-8), lua_tointeger(L,-9)));
		return 1;
	} else {
		return 0;
	}
}

static int addUnitFrame( lua_State *L ) {
	CLuceFramesList *framesList = lua_touserdata(L,-5);
	if ( framesList ) {
		lua_pushnumber( L, CLuceFramesList_addUnit( framesList, lua_tointeger(L,-4), lua_tointeger(L,-3), lua_tointeger(L,-2), lua_tointeger(L,-1) ));
		return 1;
	} else {
		return 0;
	}
}

static int loadTexture( lua_State *L ) {
	const char *path = lua_tolstring( L, -1, NULL );
	if ( path ) {
		lua_pushnumber( L, CLuceSDLApplication_loadTexture( path ));
		return 1;
	} else {
		return 0;
	}	
}

static int addBatch( lua_State *L ) {
	CLuceBatch *batch = lua_touserdata(L,-1);
	if ( batch ) {
		CLuceSDLApplication_addBatch( batch );
		return 1;
	} else {
		return 0;
	}
}

static int init( lua_State *L ) {
	CLuceSDLApplication_init( lua_tolstring(L,-1,NULL), 0, 0, 640, 480, 0, 0, -1, 60 ); 
	return 0;
}

static int run( lua_State *_ ) {
	CLuceSDLApplication_run();
	return 0;
}

static int stop( lua_State *_ ) {
	CLuceSDLApplication_stop();
	return 0;
}

static int quit( lua_State *_ ) {
	CLuceSDLApplication_quit();
	return 0;
}

static int setAttr( lua_State *L ) {
	CLuceWidget *widget = lua_touserdata( L, -3 );
	CLuceAttrName name = lua_tointeger( L, -2 );
	CLuceAttr value = lua_tonumber( L, -1 );
	CLuceWidget_set( widget, name, value );
	return 0;
}

static int getAttr( lua_State *L ) {
	CLuceWidget *widget = lua_touserdata( L, -2 );
	CLuceAttrName name = lua_tointeger( L, -1 );
	lua_pushnumber( L, CLuceWidget_get( widget, name ));
	return 1;
}

static int addAttr( lua_State *L ) {
	CLuceWidget *widget = lua_touserdata( L, -3 );
	CLuceAttrName name = lua_tointeger( L, -2 );
	CLuceAttr value = lua_tonumber( L, -1 );
	CLuceWidget_add( widget, name, value );
	return 0;
}

static const struct luaL_Reg clucelib[] = {
	{"createBatch", createBatch},
	{"createWidget", createWidget},
	{"createFramesList", createFramesList},
	{"loadTexture", loadTexture},
	{"addUnitFrame", addUnitFrame},
	{"addFrame", addFrame},
	{"addBatch",addBatch},
	{"init",init},
	{"run",run},
	{"stop",stop},
	{"quit",quit},
	{"setAttr",setAttr},
	{"addAttr",addAttr},
	{"getAttr",getAttr},
	{NULL,NULL},
};

int luaopen_cluce( lua_State *L ) {
	luaL_newlib( L, clucelib );
	return 1;
}

void CLuceLuaBindings_run( lua_State *L ) {
	if ( L ) {
		luaL_openlibs( L );
		luaopen_cluce( L );
		lua_setglobal( L, "cluce" );
		if (luaL_loadfile(L,"main.lua") || lua_pcall(L,0,0,0)) {
			printf( "[ERROR] %s\n", lua_tostring( L,-1 ));
		}
	}
}

