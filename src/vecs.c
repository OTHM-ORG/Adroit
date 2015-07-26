#include "vecs.h"

struct vec3 vec3_new(float x, float y, float z)
{
	struct vec3 new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;

	return new_vec;
}

Vector4 vec3_to_4(struct vec3 vec3)
{
	Vector4 vec4;
	vec4.x = vec3.x;
	vec4.y = vec3.y;
	vec4.z = vec3.z;
	vec4.w = 0;
	return vec4;
}
