#ifndef DYNAMIC_ARRAY_H_
#define DYNAMIC_ARRAY_H_

#define DYNAMIC_ARRAY_DECLARE(NAME,TYPE) 			\
	TYPE *NAME;																	\
	size_t NAME##Count;													\
	size_t NAME##Alloc; 												\

#define DYNAMIC_ARRAY_ALLOC(NAME,ALLOC)				\
	NAME = calloc((ALLOC), sizeof( *(NAME) ));  \
	NAME##Count = 0;														\
	NAME##Alloc = (ALLOC);											\

#define DYNAMIC_ARRAY_FREE(NAME)							\
	if ((NAME)) {																\
		free( (NAME) );														\
		NAME = NULL;															\
	}																						\

#define DYNAMIC_ARRAY_RESIZE_ADD(NAME)				\
	if ((NAME##Alloc <= NAME##Count )) {				\
		NAME##Alloc *= 2;													\
		NAME = realloc( NAME, NAME##Alloc );			\
	}																						\

#define DYNAMIC_ARRAY_PUSH(NAME,ITEM)					\
	DYNAMIC_ARRAY_RESIZE_ADD(NAME);							\
	NAME[NAME##Count] = (ITEM);									\
	NAME##Count += 1;														\

#define DYNAMIC_ARRAY_PEEK(NAME)	( NAME[NAME##Count - 1] )									

#define DYNAMIC_ARRAY_DELETE(NAME,DESTRUCTOR) 			\
	if ((NAME)) {																			\
		size_t DA_CNT_;																	\
		for (DA_CNT_=0;DA_CNT_<NAME##Count;DA_CNT_++) {	\
			DESTRUCTOR( NAME[DA_CNT_] );									\
		}																								\
		DYNAMIC_ARRAY_FREE(NAME);												\
	}																									\

#endif
