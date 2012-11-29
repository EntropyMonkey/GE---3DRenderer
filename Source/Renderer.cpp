#include "Renderer.h"

Renderer::Renderer()
{
	meshes = new std::list<Mesh*>();
}

Renderer::~Renderer()
{
	delete meshes;
}

void Renderer::Add(Mesh *m)
{
	meshes->push_back(m);
}

void Renderer::Render(SDL_Surface *screen)
{
}