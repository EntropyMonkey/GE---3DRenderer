#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <list>

#include "Mesh.h"
#include "Vertex.h"

class Triangle : public Mesh
{
public:
	Triangle(Vertex _p1, Vertex _p2, Vertex _p3)
	{
		modelMatrix = glm::mat4(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		vertices.push_back(_p1);
		vertices.push_back(_p2);
		vertices.push_back(_p3);
	}
};

#endif
