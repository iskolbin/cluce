#ifndef SDL_RENDERER_H_
#define SDL_RENDERER_H_

#include <SDL2/SDL.h>
#include "Types.h"

typedef struct CLuceSDLRenderer {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Rect *rects;
	int rectsAlloc;
	int rectsCount;
} CLuceSDLRenderer;

CLuceSDLRenderer *CLuceSDLRenderer_new( const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags, int driverIndex );
void CLuceSDLRenderer_delete( CLuceSDLRenderer *self );
int CLuceSDLRenderer_addRect( CLuceSDLRenderer *self, SDL_Rect rect );
void CLuceSDLRenderer_renderBatch( CLuceSDLRenderer *self, CLuceBatch *batch );

#endif
