#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>

#include "SDL.h"

#include "Mesh.h"
#include "Vertex.h"
#include "Camera.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void					Add(Mesh *m);

	void					Render(SDL_Surface *screen);

private:
	std::vector<Mesh*>*		meshes;

	Camera					camera;

	void					draw(Mesh *mesh, SDL_Surface *screen);
	void					draw(Vertex vertex);
	void					drawPixel(glm::vec2 pos, SDL_Surface* surface, 
		unsigned char red, unsigned char green, unsigned char blue);
	void					drawLine(glm::vec2 v1, glm::vec2 v2, SDL_Surface *surface);
	void					clearScreen(SDL_Surface *surface);
	
	static void				setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
	static Uint32			getPixel(SDL_Surface *surface, int x, int y);
};

#endif
