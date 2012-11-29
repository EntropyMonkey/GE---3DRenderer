#include "SDL.h"

#ifdef _WIN32
#pragma comment(lib, "SDL.lib")
#pragma comment(lib, "SDLmain.lib")
#pragma comment(lib, "SDL_image.lib")
#endif

#if DEBUG
#ifdef __cplusplus
extern "C"
#define main	SDL_main
#endif
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_COLORDEPTH 32

int main (int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
        printf("Can't init SDL:  %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 
		SCREEN_COLORDEPTH, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_OPENGL);

	SDL_Delay(3000);

	return 0;
}
