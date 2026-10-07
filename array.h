#define make_array( type )\
\
typedef struct {\
	type* data;\
	i32 count;\
	i32 allocated;\
} type ## _array;\
\
void push_ ## type ## _array( type ## _array* array, type push ){\
	assert( array != NULL );\
        if( array->count >= array->allocated ){\
                i32 new_allocated = ( array->allocated == 0 ) ? 16 : array->allocated * 2;\
                type* tmp = realloc( array->data, sizeof( array->data[ 0 ]) * new_allocated );\
		assert( tmp != NULL );\
		array->data = tmp;\
                memset( &array->data[ array->allocated ], 0, sizeof( array->data[ 0 ]) * ( new_allocated - array->allocated ));\
                array->allocated = new_allocated;\
        }\
        array->data[ array->count ] = push;\
        array->count += 1;\
}\
\
void alloc_ ## type ## _array( type ## _array* array, i32 count ){\
        assert( array != NULL );\
        if( array->count + count > array->allocated ){\
                i32 new_allocated = array->count + count;\
                type* tmp = realloc( array->data, sizeof( array->data[ 0 ]) * new_allocated );\
                assert( tmp != NULL );\
                array->data = tmp;\
                memset( &array->data[ array->allocated ], 0, sizeof( array->data[ 0 ]) * ( new_allocated - array->allocated ));\
                array->allocated = new_allocated;\
        }\
}\

