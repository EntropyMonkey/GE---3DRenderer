#ifndef VECTORHELPER_H
#define VECTORHELPER_H

#include <glm/glm.hpp>

class VectorHelper
{
public:
	static glm::vec3 zero;

	static void Normalize(glm::vec3 &v);

	static glm::vec3 CrossProduct(glm::vec3 v1, glm::vec3 v2);
};

#endif
