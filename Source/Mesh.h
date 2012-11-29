#ifndef MESH_H
#define MESH_H

#include <list>
#include <glm/glm.hpp>

class Mesh
{
public:
	virtual void GetVertices(std::list<glm::vec3> &vertexList) = 0;

	// position and orientation in homogeneous coordinates
	glm::mat4x4	modelMatrix;
private:
};

#endif
