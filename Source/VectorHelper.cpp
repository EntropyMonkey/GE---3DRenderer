#include "VectorHelper.h"

using namespace glm;

vec3 VectorHelper::zero = vec3(0, 0, 0);

void VectorHelper::Normalize(vec3 &v)
{
	float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v /= length;
}

vec3 VectorHelper::CrossProduct(vec3 v1, vec3 v2)
{
	vec3 r = zero;

	r.x = v1.y * v2.z - v1.z * v2.y;
	r.y = -v1.x * v2.z + v1.z * v2.x;
	r.z = v1.x * v2.y - v1.y * v2.x;

	return r;
}