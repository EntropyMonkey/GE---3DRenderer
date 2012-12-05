#include "Camera.h"

using namespace glm;

Camera::Camera()
{
	position = vec3(10, 10, 20);
	target = vec3(0, 0, 0);
	up = vec3(0, -1, 0);

	UpdateViewMatrix();

	frustum = Frustum(
		70.0f, SCREEN_WIDTH / SCREEN_HEIGHT,
		0.1f, 100.0f
	);

	UpdateProjectionMatrix();
}

// http://webglfactory.blogspot.dk/2011/06/how-to-create-view-matrix.html
// http://glm.g-truc.net/code.html
// see glm matrix_transform.inl file
void Camera::UpdateViewMatrix()
{
	vec3 f = normalize(target - position); // lookdirection vector
	vec3 s = normalize(cross(f, up)); // orthogonal to layer defined by lookdirection and up
	vec3 u = cross(s, f);

	viewMatrix = mat4(
		s.x, u.x, -f.x, 0,
		s.y, u.y, -f.y, 0,
		s.z, u.z, -f.z, 0,
		-dot(s, position), -dot(u, position), dot(f, position), 1
		);
}

// http://www.gamedev.net/topic/264248-building-a-projection-matrix-without-api/
void Camera::UpdateProjectionMatrix()
{
	float e = 1 / tan(frustum.fov * 0.5f);
	float A = e / frustum.aspect;
	float B = (-frustum.far - frustum.near) / (frustum.far - frustum.near);
	float C = (-2 * frustum.far * frustum.near)/(frustum.far - frustum.near);


	projectionMatrix = mat4(
		e, 0, 0, 0,
		0, A, 0, 0,
		0, 0, B, C,
		0, 0, -1, 0
		);
}

void Camera::Rotate(float angle)
{

	mat3 rot = mat3(1);
	rot = mat3(
		cos(angle * DEG2RAD), -sin(angle * DEG2RAD), 0,
		sin(angle * DEG2RAD), cos(angle * DEG2RAD), 0,
		0, 0, 1
		);

	position = rot * position;
}