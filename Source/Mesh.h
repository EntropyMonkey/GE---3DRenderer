#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

#include "Vertex.h"

class Mesh
{
public:
	Mesh()
	{
		modelMatrix = glm::mat4(1.0f);
	}

	virtual void GetVertices(std::vector<Vertex> &vertexList)
	{
		for (std::vector<Vertex>::iterator it = vertices.begin();
			it != vertices.end();
			it++)
		{
			vertexList.push_back(*it);
		}
	}

	void AddVertex(Vertex v)
	{
		vertices.push_back(v);
	}

	// position and orientation in homogeneous coordinates
	glm::mat4	modelMatrix;
protected:
	std::vector<Vertex> vertices;
};

#endif
