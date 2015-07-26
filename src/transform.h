#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "mesh.h"

#include "../deps/linearAlg.h"
#include "vecs.h"

struct transform {
	struct vec3 m_pos;
	struct vec3 m_rot;
	struct vec3 m_scale;
	Matrix model;
	Matrix actual;
};

struct transform *transform_new(struct vec3 pos,
				struct vec3 rot,
				struct vec3 scale);
void transform_free(struct transform *transform);
Matrix *transform_get_model(struct transform *transform);


#endif
