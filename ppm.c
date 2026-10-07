#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#define WIDTH 640
#define HEIGHT 480
#define BACKGROUND 0xff131012
#define FOREGROUND 0xff4dee0
#define FILENAME "out.ppm"

uint32_t pixels[WIDTH * HEIGHT ] = { 0 };

void DrawBackground( uint32_t* pixels, int width, int height, uint32_t color ) {
        for( int i = 0; i < width * height; ++i ) {
                pixels[ i ] = color;
        }
}

void DrawPixel( uint32_t* pixels, int width, int height, uint32_t color, int x0, int y0 ) {
        if( x0 < 0 || y0 < 0 || x0 >= width || y0 >= height) {
                return;
        }
        pixels[ x0 + width * y0 ] = color;
}

void DrawLine( uint32_t* pixels, int width, int height, uint32_t color, int x0, int y0, int x1, int y1 ) {
        int dx = abs( x1 - x0 );
        int dy = -abs( y1 - y0 );
        int sx = x0 < x1 ? 1 : -1;
        int sy = y0 < y1 ? 1 : -1;
        int err = dx + dy;
        int e2;
        while( 1 ) {
                DrawPixel( pixels, width, height, color, x0, y0 );
                if( x0 == x1 && y0 == y1 ) break;
                e2 = 2 * err;
                if( e2 >= dy ) {
                        err += dy;
                        x0 += sx;
                }
                if( e2 <= dx ) {
                        err += dx;
                        y0 += sy;
                }
        }
}

void OutputPPM( uint32_t* pixels, int width, int height, char* filename ) {
        FILE* file = fopen( filename, "w" );
        assert( file != NULL );
        fprintf( file, "P6\n%d %d\n255\n", width, height );
        for( int i = 0; i < width * height; ++i ) {
                uint8_t color[ 3 ] = {
                        pixels[ i ] & 0xff,
                        pixels[ i ] >> 8 & 0xff,
                        pixels[ i ] >> 16 & 0xff,
                };
                fwrite( color, sizeof( color ), 1, file );
        }
        fclose(file);
}

int main() {
        DrawBackground( pixels, WIDTH, HEIGHT, BACKGROUND );
        DrawLine( pixels, WIDTH, HEIGHT, FOREGROUND, 0, 0, WIDTH - 1, HEIGHT - 1 );
        DrawLine( pixels, WIDTH, HEIGHT, FOREGROUND, 0, 0, WIDTH - 1, 0 );
        DrawLine( pixels, WIDTH, HEIGHT, FOREGROUND, WIDTH - 1, 0, WIDTH - 1, HEIGHT -1 );
        DrawLine( pixels, WIDTH, HEIGHT, FOREGROUND, WIDTH - 1, 0, 0, HEIGHT - 1 );
        DrawLine( pixels, WIDTH, HEIGHT, FOREGROUND, 100, -100, 500, 300 );
        DrawLine( pixels, WIDTH, HEIGHT, FOREGROUND, -100, 100, 300, 800 );
        OutputPPM( pixels, WIDTH, HEIGHT, FILENAME );
        return 0;
}
