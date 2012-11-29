#ifndef RENDERER_H
#define RENDERER_H

#include "SDL.h"

#include "Mesh.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Add(Mesh *m);

	void Render(SDL_Surface *screen);

private:
	std::list<Mesh*>* meshes;


};

#endif
