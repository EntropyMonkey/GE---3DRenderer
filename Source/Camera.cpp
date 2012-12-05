#include "Camera.h"

using namespace glm;

Camera::Camera()
{
	position = vec3(0, 0, 0);
	lookAt = vec3(0, 0, 1);
	up = vec3(0, 1, 0);

	UpdateViewMatrix();

	frustum = Frustum(
		90, SCREEN_WIDTH / SCREEN_HEIGHT,
		-1, 1
	);

	UpdateProjectionMatrix();
}

// http://webglfactory.blogspot.dk/2011/06/how-to-create-view-matrix.html
// http://glm.g-truc.net/code.html
void Camera::UpdateViewMatrix()
{

	vec3 lookDirection = position - lookAt;
	VectorHelper::Normalize(lookDirection);
	vec3 normal = VectorHelper::CrossProduct(up, lookDirection);
	VectorHelper::Normalize(normal);
	vec3 vy = VectorHelper::CrossProduct(lookDirection, normal);

	viewMatrix = mat4(
		lookDirection.x, lookDirection.y, lookDirection.z,	-position.x,
		vy.x,		vy.y,		vy.z,		-position.y,
		normal.x,	normal.y,	normal.z,	-position.z,
		0,			0,			0,			1
		);

	// calculate inverse here because
	// 1 - need to transform everything to camera space
	// 2 - don't need to do it each frame, only when camera changes
	//viewMatrix = glm::inverse(viewMatrix);

	//viewMatrix = glm::normalize(viewMatrix);
}

// http://www.gamedev.net/topic/264248-building-a-projection-matrix-without-api/
void Camera::UpdateProjectionMatrix()
{
	float right, left, top, bottom;
	right = frustum.width * 0.5f;
	left = -frustum.width * 0.5f;
	top = frustum.height * 0.5f;
	bottom = -frustum.height * 0.5f;

	float A = (right + left) / (right - left);
	float B = (top + bottom) / (top - bottom);
	float C = -(frustum.far + frustum.near) / (frustum.far - frustum.near);
	float D = -(2 * frustum.far * frustum.near) / (frustum.far - frustum.near);
	float E = frustum.near / frustum.width;
	float F = frustum.near / frustum.height;

	projectionMatrix = mat4(
		E, 0, /*A*/0, 0,
		0, F, /*B*/0, 0,
		0, 0, C, D,
		0, 0, -1, 0
		);

	//projectionMatrix = glm::normalize(projectionMatrix);
}
