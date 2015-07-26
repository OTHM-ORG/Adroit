#include <stdlib.h>
#include <stdio.h>
#include "camera.h"

struct camera *camera_new(struct vec3 pos, float fov, float aspect,
			  float z_near, float z_far)
{
	struct camera *new_camera;
	new_camera = malloc(sizeof(struct camera));

	/* new_camera->m_perspective = perspective(fov, aspect, z_near, z_far); */
	new_camera->m_position = pos;
	new_camera->m_forward = vec3_new(0, 0, 1);
	new_camera->m_up = vec3_new(0, 1, 0);

	new_camera->fov = fov;
	new_camera->aspect = aspect;
	new_camera->z_near = z_near;
	new_camera->z_far = z_far;

	return new_camera;
}

Matrix camera_get_view_projection(struct camera *camera)
{
	Vector4 position = vec3_to_4(camera->m_position);
	Vector4 up = vec3_to_4(camera->m_up);
	Vector4 forward = vec3_to_4(camera->m_forward);

	Matrix view = lookAt(position, addvec4(position, forward), up);

	Matrix m_perspective = perspective(camera->fov, camera->aspect,
					   camera->z_near, camera->z_far);
	return multiplymat4(&m_perspective, &view);
 	/* return camera->m_perspective; */
}
