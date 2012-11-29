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

#include <iostream>
#include <glm/glm.hpp>

#include "Triangle.h"
#include "Renderer.h"

using namespace std;
using namespace glm;

void Init();

Renderer renderer;

int main (int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) 
	{
        printf("Can't init SDL:  %s\n", SDL_GetError());
        exit(1);
    }

    atexit(SDL_Quit);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 
		SCREEN_COLORDEPTH, SDL_SWSURFACE);

	bool quit;
	SDL_Event event = SDL_Event();

	Init();

	while(!quit)
	{
		if(SDL_PollEvent(&event))
        {
			if(event.type == SDL_KEYDOWN)
            {
				cout << (char)event.key.keysym.sym << endl;
			}
			else if (event.type == SDL_KEYUP)
			{
				cout << (char)event.key.keysym.sym << endl;
			}
			else if( event.type == SDL_QUIT )
            {
				quit = true;
            }
		}

		renderer.Render(screen);

		SDL_Flip(screen);
	}

	return 0;
}

void Init()
{
	Triangle tri1 = Triangle(vec3(), vec3(), vec3());

	renderer = Renderer();
	renderer.Add(&tri1);
}
