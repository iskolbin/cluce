#include "SDLApplication.h"

static CLuceSDLApplication application = {0};

static void render( void );
static int  altered( void );

CLuceSDLApplication *CLuceSDLApplication_instance( void ) {
	return &application;
}

void CLuceSDLApplication_init( const char *title, int x, int y, int w, int h, Uint32 windowFlags, Uint32 rendererFlags, int driverIndex, int fps ) {
	if ( !application.inited ) {
		SDL_Init( SDL_INIT_EVERYTHING );
		application.window = SDL_CreateWindow( title, x, y, w, h, windowFlags );
		application.renderer = SDL_CreateRenderer( application.window, driverIndex, rendererFlags );
		DYNAMIC_ARRAY_ALLOC(application.textures,16);
		DYNAMIC_ARRAY_ALLOC(application.surfaces,16);
		DYNAMIC_ARRAY_ALLOC(application.renderlist,16);
		application.inited = 1;
		application.resized = 1;
		application.ticks = SDL_GetTicks();
		application.renderLimit = 1000 / fps;
		application.renderCounter = 0;
		application.cache = CLuceCache_new(16,16);
	}
}

void CLuceSDLApplication_run( void ) {
	SDL_Event event;
	Uint32 ticks, dt;

	while ( application.inited ) {
		ticks = SDL_GetTicks();
		dt = ticks - application.ticks;
		application.ticks = ticks;
		
		if ( application.renderCounter < dt ) {
			if ( altered() ) {
				SDL_SetRenderDrawColor( application.renderer, 0, 0, 0, 0 );
				SDL_RenderClear( application.renderer );
				
				render();

				SDL_RenderPresent( application.renderer );
				application.resized = 0;
			}
			application.renderCounter = application.renderLimit;
		} else {
			application.renderCounter -= dt;
		}
	
		if ( application.update ) {
			if ( application.updateCounter <= dt ) {
				application.update( dt - application.updateCounter );
				application.updateCounter = application.updateLimit;
			} else {
				application.updateCounter -= dt;
			}
		}

		if ( SDL_WaitEvent( &event )) {
			switch( event.type ) {
				case SDL_KEYDOWN: switch( event.key.keysym.sym ) {
					case SDLK_ESCAPE: CLuceSDLApplication_quit(); break;
				}
				case SDL_WINDOWEVENT: application.resized = 1;
			}			
		}
	}
}

void CLuceSDLApplication_stop( void ) {
}

void CLuceSDLApplication_quit( void ) {
	if ( application.inited ) {
		if ( application.window ) { SDL_DestroyWindow( application.window ); application.window = NULL;}
		if ( application.renderer ) { SDL_DestroyRenderer( application.renderer ); application.renderer = NULL; }
		DYNAMIC_ARRAY_DELETE(application.textures,SDL_DestroyTexture);
		DYNAMIC_ARRAY_DELETE(application.surfaces,SDL_FreeSurface);
		DYNAMIC_ARRAY_FREE(application.renderlist);
		application.inited = 0;
		SDL_Quit();
	}
}

size_t CLuceSDLApplication_loadTexture( const char *file ) {
	SDL_Surface *surface = IMG_Load( file );
	SDL_Texture *texture = SDL_CreateTextureFromSurface( application.renderer, surface );
	DYNAMIC_ARRAY_PUSH(application.surfaces,surface);
	DYNAMIC_ARRAY_PUSH(application.textures,texture);
	return application.texturesCount - 1;
}

size_t CLuceSDLApplication_addBatch( CLuceBatch *batch ) {
	DYNAMIC_ARRAY_PUSH(application.renderlist,batch);
	return application.renderlistCount - 1;
}

void render( void ) {
	size_t i, j;
	for ( i = 0; i < application.renderlistCount; i++ ) {
		CLuceBatch *batch = application.renderlist[i];
		for ( j = 0; j < batch->widgetsCount; j++ ) {
			CLuceWidget *wgt = batch->widgets + j;
			if ( wgt->framesList ) {
				CLuceAttr x = wgt->attrWld[CLUCE_ATTR_X];
				CLuceAttr y = wgt->attrWld[CLUCE_ATTR_Y];
				CLuceAttr xscl = wgt->attrWld[CLUCE_ATTR_XSCL];
				CLuceAttr yscl = wgt->attrWld[CLUCE_ATTR_YSCL];
				CLuceFrame frame = wgt->framesList->frames[(int)wgt->attrWld[CLUCE_ATTR_FRAME]];
				SDL_Rect srcrect = {frame.x,frame.y,frame.w,frame.h};
				SDL_Rect destrect = {
					xscl == 1 ? frame.xoffset + x : frame.xoffset + x + (srcrect.w * (1 - xscl)),
					yscl == 1 ? frame.yoffset + y : frame.yoffset + y + (srcrect.h * (1 - yscl)),
					xscl == 1 ? srcrect.w : srcrect.w * xscl,
					yscl == 1 ? srcrect.h : srcrect.h * yscl};
				SDL_Point center = {wgt->attrWld[CLUCE_ATTR_XPIV], wgt->attrWld[CLUCE_ATTR_YPIV]};
				SDL_RenderCopyEx( application.renderer, application.textures[frame.id], &srcrect, &destrect, wgt->attrWld[CLUCE_ATTR_ROT], &center, 0 );
			}	
			//printf( "[%d] %d %d %d %d => %d %d %d %d; C: %d %d\n", frame.id, frame.x, frame.y, frame.w, frame.h, destrect.x, destrect.y, destrect.w, destrect.h, center.x, center.y );
		}
		batch->altered = 0;
	}	
}

int altered( void ) {
	if ( application.resized ) {
		return 1;
	} else {
		size_t i;
		for ( i = 0; i < application.renderlistCount; i++ ) {
			if ( application.renderlist[i]->altered ) return 1;
		}
		return 0;
	}
}
