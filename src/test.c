#include <stdio.h>
#include <math.h>
#include "vecs.h"
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"

int main(void)
{
	float counter = 0.0f;

	SDL_Init(SDL_INIT_EVERYTHING);

	struct display *d = display_new(800, 600, "hello world");
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		fprintf(stderr, "Glew failed to initialize: %s\n",
			glewGetErrorString(status));
	}

	struct vertex verticies[] = { vertex_new(-0.5, -0.5, 0,
						 0.0, 0.0),
				      vertex_new(0, 0.5, 0,
						 0.5, 1.0),
				      vertex_new(0.5, -0.5, 0,
						 1.0, 0.0) };
	struct mesh *m = mesh_new
		(verticies, sizeof(verticies)/sizeof(verticies[0]));

	struct shader *s = shader_new("./res/basicShader");

	struct texture *t = texture_new("./res/bricks.jpg");

	struct transform *tr = transform_new(vec3_new(0, 0, 0),
					     vec3_new(1, 0, 0),
					     vec3_new(0.5, 0.5, 0.5));

	struct camera *cam = camera_new(vec3_new(0, 0, -0.75), 70.0f,
					600.0f/800.0f, 0.1f, 1000.0f);
	while (!d->is_closed) {
		clear(0.0, 0.15, 0.3, 1.0);

		/* tr->m_pos.x = sinf(counter); */
		/* tr->m_pos.z = counter; */
		shader_bind(s);
		texture_bind(t, 0);
		shader_update(s, tr, cam);
		mesh_draw(m);
		update(d);
		cam->m_position.z = cosf(counter) - 2;
		cam->m_position.x = sinf(counter);
		/* tr->m_rot.x = counter; */
		/* tr->m_rot.y = sinf(counter); */
		/* tr->m_scale.x = cosf(counter); */
		/* tr->m_scale.y = cosf(counter); */
		/* tr->m_scale.z = cosf(counter); */
		counter += 0.01f;
	}
	display_free(d);
	shader_free(s);
	mesh_free(m);
	SDL_Quit();
	return 0;
}
