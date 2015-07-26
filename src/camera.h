#ifndef CAMERA_H
#define CAMERA_H

#include "../deps/linearAlg.h"
#include "vecs.h"

struct camera {
	
	struct vec3 m_position;
	struct vec3 m_forward;
	struct vec3 m_up;

	float fov;
	float aspect;
	float z_near;
	float z_far;
};

struct camera *camera_new(struct vec3 pos, float fov, float aspect,
			  float z_near, float z_far);

Matrix camera_get_view_projection(struct camera *camera);

#endif
