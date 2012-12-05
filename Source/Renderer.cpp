#include "Renderer.h"

using namespace glm;

Renderer::Renderer()
{
	meshes = new std::vector<Mesh*>();
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
	camera.Rotate(1.0f);
	camera.UpdateViewMatrix();

	clearScreen(screen);
	for (std::vector<Mesh*>::iterator it = meshes->begin();
		it != meshes->end();
		it++)
	{
		draw(*it, screen);
	}
}


void Renderer::draw(Mesh *mesh, SDL_Surface *screen)
{	
	std::vector<Vertex> vertices = mesh->GetVertices();
	std::vector<Vertex>::iterator nextVertex;

	for (std::vector<Vertex>::iterator vertex = vertices.begin();
		vertex != vertices.end();
		vertex++)
	{
		// copy vertex data
		vec4 v = vec4(vertex->position.x, vertex->position.y, vertex->position.z, 1);

		// convert vertex from object coords to clip coords
		mat4 modelViewProjectionMatrix = camera.projectionMatrix * 
			camera.viewMatrix * mesh->modelMatrix;

		v = modelViewProjectionMatrix * v;

		// normalize clip coordinates / get normalized device coordinates
		v = v / v.w;

		// clip vertices outside the viewport
		if ((v.x < -1 || v.x > 1) ||
			(v.y < -1 || v.y > 1))
		{
			// go to next vertex if this one is outside
			continue;
		}

		// map clip coordinates to screen coordinates
		float width = screen->w;
		float height = screen->h;
		v.x = v.x * width * 0.5f + width * 0.5f;
		v.y = -v.y * height * 0.5f + height * 0.5f;

		vertex->screenPos = vec2(v.x, v.y);

		drawPixel(vertex->screenPos, screen, 255, 0, 0);
		
		nextVertex = vertex;
		nextVertex ++;
		// rendering meshes as line loops
		if (vertex != vertices.begin())
			drawLine((vertex-1)->screenPos, vertex->screenPos, screen);
		
		if (nextVertex == vertices.end())
			drawLine(vertices.begin()->screenPos, vertex->screenPos, screen);
	}
}

void Renderer::drawLine(vec2 v1, vec2 v2, SDL_Surface *surface)
{
	vec2 distance = v2 - v1;
	float length = glm::length(distance);

	float stepSizeX = distance.x / length;
	float stepSizeY = distance.y / length;

	vec2 currentPos = v1;

	for (float i = 0; i < length; i++)
	{
		drawPixel(currentPos, surface, 0, 255, 255);
		currentPos.x += stepSizeX;
		currentPos.y += stepSizeY;
	}
}

void Renderer::drawPixel(vec2 pos, SDL_Surface *surface,
	unsigned char red, unsigned char green, unsigned char blue)
{
	// check if it's in the surface's bounds
	if (pos.x < 0 || pos.y < 0 || pos.x > surface->w || pos.y > surface->h)
		return;

	setPixel(surface, pos.x, pos.y, SDL_MapRGB(surface->format, red, green, blue));
}

void Renderer::clearScreen(SDL_Surface *surface)
{
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			setPixel(surface, x, y, SDL_MapRGB(surface->format, 0, 0, 0));
		}
	}
}

Uint32 Renderer::getPixel(SDL_Surface *surface, int x, int y)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    return pixels[(y * surface->w) + x];
}

//setPixel(surface, x, y, SDL_MapRGB(screen->format, 255, 255, 255));
void Renderer::setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    //Convert the pixels to 32 bit
    Uint32 *pixels = (Uint32 *)surface->pixels;

    pixels[(y * surface->w) + x] = pixel;
}