#include "SDLRenderer.h"

CLuceSDLRenderer *CLuceSDLRenderer_new( const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags, int driverIndex ) {
	CLuceSDLRenderer *self = malloc( sizeof ( *self ));
	self->window = SDL_CreateWindow( title, x, y, w, h, windowFlags );
	self->renderer = SDL_CreateRenderer( self->window, driverIndex, rendererFlags );
	self->rects = calloc( 8, sizeof( *self->rects ));
	self->rectsAlloc = 8;
	self->rectsCount = 0;
	return self;
}

void CLuceSDLRenderer_delete( CLuceSDLRenderer *self ) {
	if ( self ) {
		if ( self->window ) { SDL_DestroyWindow( self->window ); self->window = NULL;}
		if ( self->renderer ) { SDL_DestroyRenderer( self->renderer ); self->renderer = NULL; }
		if ( self->rects ) { free( self->rects ); self->rects = NULL; }
		free( self );
	}
}

int CLuceSDLRenderer_addRect( CLuceSDLRenderer *self, SDL_Rect rect ) {
	return 0;
}

void CLuceSDLRenderer_renderBatch( CLuceSDLRenderer *self, CLuceBatch *batch ) {
	size_t i;

	for ( i = 0; i < batch->widgetsCount; i += CLUCE_WIDGET_SIZE ) {
		CLuceAttr xscl = batch->renderList[i+CLUCE_ATTR_XSCL];
		CLuceAttr yscl = batch->renderList[i+CLUCE_ATTR_YSCL];
		SDL_Rect srcrect = self->rects[(int)batch->renderList[i+CLUCE_ATTR_FRAME]];	
		SDL_Rect destrect = {
			xscl == 1 ? batch->renderList[i+CLUCE_ATTR_X] : (batch->renderList[i+CLUCE_ATTR_X] + (srcrect.w * (1 - xscl))),
			xscl == 1 ? srcrect.w : srcrect.w * xscl,
			yscl == 1 ? batch->renderList[i+CLUCE_ATTR_Y] : (batch->renderList[i+CLUCE_ATTR_Y] + (srcrect.h * (1 - yscl))),
			yscl == 1 ? srcrect.h : srcrect.h * yscl};
		SDL_Point center = {
			batch->renderList[i+CLUCE_ATTR_XPIV], 
			batch->renderList[i+CLUCE_ATTR_YPIV],};

		SDL_RenderCopyEx( self->renderer, self->texture, &srcrect, &destrect, batch->renderList[i+CLUCE_ATTR_ROT], &center, 0 ); 
	}
}
