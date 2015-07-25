#include "vecs.h"

struct vec3 vec3_new(float x, float y, float z)
{
	struct vec3 new_vec;

	new_vec.x = x;
	new_vec.y = y;
	new_vec.z = z;

	return new_vec;
}
