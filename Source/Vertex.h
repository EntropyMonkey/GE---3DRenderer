#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

class Vertex
{
public:
	Vertex(float x = 0, float y = 0, float z = 0)
	{
		position = glm::vec3(x, y, z);
		screenPos = glm::vec2(0, 0);
	}

	glm::vec3 position;

	glm::vec2 screenPos;
};

#endif
