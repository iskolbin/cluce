#ifndef SDL_APPLICATION_H_
#define SDL_APPLICATION_H_

#include "SDL.h"
#include "SDL_image.h"
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>
#include "Types.h"
#include "Cache.h"

typedef enum {
	CLUCE_INPUT_MOUSE_MOVE,
	CLUCE_INPUT_MOUSE_DOWN,
	CLUCE_INPUT_MOUSE_UP,
	CLUCE_INPUT_KEYBOARD_DOWN,
	CLUCE_INPUT_KEYBOARD_UP,
} CLuceSDLInputEvent;

typedef struct CLuceSDLApplication {
	SDL_Window *window;
	SDL_Renderer *renderer;

	DYNAMIC_ARRAY_DECLARE(textures,SDL_Texture*);
	DYNAMIC_ARRAY_DECLARE(surfaces,SDL_Surface*);
	DYNAMIC_ARRAY_DECLARE(renderlist,CLuceBatch*);

	int inited;
	int resized;

	Uint32 ticks;
	
	Uint32 renderCounter;
	Uint32 renderLimit;
	
	Uint32 updateCounter;
	Uint32 updateLimit;

	CLuceCache *cache;

	void (*update)(int dt);
	void (*input)(CLuceSDLInputEvent event);
} CLuceSDLApplication;

CLuceSDLApplication *CLuceSDLApplication_instance( void );
void CLuceSDLApplication_init( const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags, int driverIndex, int fps );
void CLuceSDLApplication_run( void );
void CLuceSDLApplication_stop( void );
void CLuceSDLApplication_quit( void );
size_t CLuceSDLApplication_loadTexture( const char *file );
size_t CLuceSDLApplication_addBatch( CLuceBatch *batch );


#endif
