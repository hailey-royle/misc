#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>

typedef int32_t i32;
typedef int64_t i64;

#define ansi_foreground_red "\x1b[41m"
#define ansi_foreground_default "\x1b[49m"

void assert_failed( char* file, i32 line, const char* func, char* expression ){
	fprintf( stderr, "%s%s:%d:%s%s \"%s\"\r\n", ansi_foreground_red, file, line, func, ansi_foreground_default, expression );
	fflush( stderr );
	exit( 1 );
}

#define assert( expression ){\
	if( !( expression )){\
		assert_failed( __FILE__, __LINE__, __func__, #expression );\
	}\
}

void* thread_main( void* argt ){
	i32 thread_index = (i32) argt;
	printf( "Thread: %d\n", thread_index );
	return NULL;
}

i32 main( i32 argc, char* argv[] ){
        i64 cpu_count = sysconf( _SC_NPROCESSORS_ONLN );
	assert( cpu_count > 0 );
	pthread_t thread_array[ cpu_count - 1 ];
	for( i64 i = 0; i < cpu_count - 1; i++ ){
	        i32 error = pthread_create( &thread_array[ i ], NULL, thread_main, (void*) i );
		assert( !error );
	}
	thread_main( (void*) ( cpu_count - 1 ));
	for( i64 i = 0; i < cpu_count - 1; i++ ){
		pthread_join( thread_array[ i ], NULL );
	}
	return 0;
}
