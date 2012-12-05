#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp>

#include "Defines.h"

class Camera
{
public:
	struct Frustum
	{
		float near;
		float far;
		float fov;
		float aspect;

		Frustum(float _fov, float _aspect, float _near, float _far) :
			fov(_fov), aspect(_aspect), near(_near), far(_far)
		{
		}

		Frustum() {}
	};

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	Frustum frustum;

	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;

	Camera();

	void UpdateViewMatrix();
	void UpdateProjectionMatrix();

	void Rotate(float angle);
};

#endif
