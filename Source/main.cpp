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

#include <iostream>
#include <glm/glm.hpp>

#include "Defines.h"
#include "Triangle.h"
#include "Renderer.h"

using namespace std;
using namespace glm;

void Init();

Renderer *renderer;

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

	bool pan;
	vec3 panDirection;

	quit = false;
	while(!quit)
	{
		if(SDL_PollEvent(&event))
        {
			if (event.type == SDL_QUIT)
			{
				quit = true;
				continue;
			}

			if(event.type == SDL_KEYDOWN)
            {
				if (event.key.keysym.sym == SDLK_LEFT)
				{
					pan = true;
					panDirection = vec3(-1, 0, 0);
				}
				else if (event.key.keysym.sym == SDLK_RIGHT)
				{
					pan = true;
					panDirection = vec3(1, 0, 0);
				}
				else if (event.key.keysym.sym == SDLK_UP)
				{
					pan = true;
					panDirection = vec3(0, 0, 1);
				}
				else if (event.key.keysym.sym == SDLK_DOWN)
				{
					pan = true;
					panDirection = vec3(0, 0, -1);
				}
			}
			else if (event.type == SDL_KEYUP)
			{
				if (event.key.keysym.sym == SDLK_LEFT || 
					event.key.keysym.sym == SDLK_RIGHT ||
					event.key.keysym.sym == SDLK_UP ||
					event.key.keysym.sym == SDLK_DOWN)
				{
					pan = false;
				}
			}
			else if( event.type == SDL_QUIT )
            {
				quit = true;
            }
		}

		if (pan)
		{
			panDirection *= 0.1f;
			renderer->PanCamera(panDirection);
		}

		renderer->Render(screen);

		SDL_Flip(screen);
	}

	return 0;
}

void Init()
{
	Mesh *my = new Mesh();

	float size = 1;
	
	my->AddVertex(Vertex(0, size, 0));
	my->AddVertex(Vertex(0, 0, 0));

	Mesh *mx = new Mesh();
	mx->AddVertex(Vertex(0, 0, 0));
	mx->AddVertex(Vertex(size, 0, 0));

	Mesh *mz = new Mesh();
	mz->AddVertex(Vertex(0, 0, 0));
	mz->AddVertex(Vertex(0, 0, size));

	renderer = new Renderer();
	renderer->Add(my);
	renderer->Add(mx);
	renderer->Add(mz);
}
