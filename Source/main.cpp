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
Mesh* CreateCube();

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

	bool rotate;
	bool moveUpDown;
	float rotationDir;
	float moveDir;

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
		}

		renderer->Render(screen);

		SDL_Flip(screen);
	}

	return 0;
}

void Init()
{

	renderer = new Renderer();
	renderer->Add(CreateCube());
}

Mesh* CreateCube()
{
	// it's a leaking cube
	Mesh *cube = new Mesh(); // cube front

	float size = 1.0f;
	
	// draw a cube

	Vertex A = Vertex(0, 0, 0);
	Vertex B = Vertex(size, 0, 0);
	Vertex C = Vertex(size, size, 0);
	Vertex D = Vertex(0, size, 0);
	
	Vertex E = Vertex(0, 0, size);
	Vertex F = Vertex(size, 0, size);
	Vertex G = Vertex(size, size, size);
	Vertex H = Vertex(0, size, size);

	cube->AddVertex(A);
	cube->AddVertex(B);
	cube->AddVertex(C);
	cube->AddVertex(G);
	cube->AddVertex(F);
	cube->AddVertex(C);
	cube->AddVertex(D);
	cube->AddVertex(H);
	cube->AddVertex(G);
	cube->AddVertex(D);
	cube->AddVertex(A);
	cube->AddVertex(E);
	cube->AddVertex(H);
	cube->AddVertex(A);
	cube->AddVertex(B);
	cube->AddVertex(F);
	cube->AddVertex(E);
	cube->AddVertex(B);

	return cube;
}