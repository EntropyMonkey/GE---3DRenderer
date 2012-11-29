#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <list>

#include "Mesh.h"

class Triangle : public Mesh
{
public:
	Triangle(glm::vec3 _p1, glm::vec3 _p2, glm::vec3 _p3);

	void GetVertices(std::list<glm::vec3> &vertexList)
	{
		vertexList.push_back(p3);
		vertexList.push_back(p2);
		vertexList.push_back(p1);
	}

private:
	glm::vec3 p1;
	glm::vec3 p2;
	glm::vec3 p3;
};

#endif
