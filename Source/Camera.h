#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>

#include "Defines.h"
#include "VectorHelper.h"

class Camera
{
public:
	struct Frustum
	{
		float width;
		float height;
		float near;
		float far;

		Frustum(float fov, float aspect, float _near, float _far) :
			near(_near), far(_far)
		{
			width = -2 * near * tan(fov * 0.5f);
			height = width / aspect;
		}

		Frustum() {}
	};

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	Frustum frustum;

	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;

	Camera();

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();
};

#endif
