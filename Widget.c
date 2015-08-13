#include "Widget.h"

CLuceWidget * CLuceWidget_new( void ) {
	CLuceWidget *self = malloc( sizeof *self );
	//self->attr = NULL;
	//self->attrWld = NULL;
	self->frameIdx = 0;
	self->framesList = NULL;
	self->framesCount = 0;
	self->shift = 0;
	self->parent = self->head = self->next = self->prev = NULL;
	return self;
}

void CLuceWidget_delete( CLuceWidget *self ) {
	if ( self != NULL ) {
		free( self );
	}
}

#define MAKE_ATTR_UPDATER(ATTR,OP)																	\
	static void update_##ATTR( CLuceWidget *self ) {									\
		CLuceWidget *ch = self->head; 																	\
		self->attrWld[(ATTR)] = self->attr[(ATTR)]; 										\
		if(self->parent) {																							\
			self->attrWld[(ATTR)] OP##= (self)->parent->attrWld[(ATTR)];	\
		}																																\
		while(ch) { 																										\
			CLuceWidget_update(ch,(ATTR));																\
			ch = ch->next; 																								\
		} 																															\
	}																																	

MAKE_ATTR_UPDATER(CLUCE_ATTR_X,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_Y,+)
//MAKE_ATTR_UPDATER(CLUCE_ATTR_FRAME,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_XSCL,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_YSCL,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_XPIV,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_YPIV,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_ROT,+)
MAKE_ATTR_UPDATER(CLUCE_ATTR_RED,*)
MAKE_ATTR_UPDATER(CLUCE_ATTR_GREEN,*)
MAKE_ATTR_UPDATER(CLUCE_ATTR_BLUE,*)
MAKE_ATTR_UPDATER(CLUCE_ATTR_ALPHA,*)

void CLuceWidget_update( CLuceWidget *self, CLuceAttrName attr ) {
	switch( attr ) {
		case CLUCE_ATTR_X: update_CLUCE_ATTR_X( self ); break; 
		case CLUCE_ATTR_Y: update_CLUCE_ATTR_Y( self ); break;
		//case CLUCE_ATTR_FRAME: update_CLUCE_ATTR_FRAME( self ); break;
		case CLUCE_ATTR_XSCL: update_CLUCE_ATTR_XSCL( self ); break;
		case CLUCE_ATTR_YSCL: update_CLUCE_ATTR_YSCL( self ); break;
		case CLUCE_ATTR_ROT: update_CLUCE_ATTR_ROT( self ); break;
		case CLUCE_ATTR_XPIV: update_CLUCE_ATTR_XPIV( self ); break;
		case CLUCE_ATTR_YPIV: update_CLUCE_ATTR_YPIV( self ); break;
		case CLUCE_ATTR_RED: update_CLUCE_ATTR_RED( self ); break;
		case CLUCE_ATTR_GREEN: update_CLUCE_ATTR_GREEN( self ); break;
		case CLUCE_ATTR_BLUE: update_CLUCE_ATTR_BLUE( self ); break;
		case CLUCE_ATTR_ALPHA: update_CLUCE_ATTR_ALPHA( self ); break;
	}
}

void CLuceWidget_setParent( CLuceWidget *self, CLuceWidget *parent ) {
	if ( parent != self->parent ) {
		if ( self->parent ) {
			if ( self->next ) self->next->prev = self->prev;
			if ( self->prev ) self->prev->next = self->next;
			if ( self == self->parent->head ) self->parent->head = self->next;
		} 
		self->parent = parent;
		self->prev = NULL;
		self->next = self->parent->head;
		if ( parent ) {
			parent->head->prev = self;
			parent->head = self;
		}
	}
}


//CLuceTween *CLuceWidget_move( CLuceWidget *self, CLuceAttrName attr, CLuceAttr value, CLuceTweenTime length, CLuceTweenEase ease, CLuceTweenAfter after ) {}
