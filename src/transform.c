#include "transform.h"
#include <stdlib.h>

struct transform *transform_new(struct vec3 pos,
				struct vec3 rot,
				struct vec3 scale)
{
	struct transform *new_transform;

	new_transform = malloc(sizeof(struct transform));
	new_transform->model = IDENTITY_MATRIX;

	new_transform->m_pos = pos;
	new_transform->m_rot = rot;
	new_transform->m_scale = scale;

	return new_transform;
}

float *transform_get_model(struct transform *transform)
{
	Matrix actual = transform->model;
	actual.m[3] = transform->m_pos.x;
	actual.m[7] = transform->m_pos.y;
	actual.m[11] = transform->m_pos.z;

	scale(&actual,
	      transform->m_scale.x,
	      transform->m_scale.y,
	      transform->m_scale.z);
	rotateX(&actual,
		transform->m_rot.x);
	rotateY(&actual,
		transform->m_rot.y);
	rotateZ(&actual,
		transform->m_rot.z);
	transform->actual = actual;
	return transform->actual.m;
}

void transform_free(struct transform *transform)
{
	return;
}
