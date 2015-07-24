#include <stdio.h>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"

int main(void)
{
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

	while (!d->is_closed) {
		clear(0.0, 0.15, 0.3, 1.0);
		shader_bind(s);
		texture_bind(t, 0);
		mesh_draw(m);
		update(d);
	}
	display_free(d);
	shader_free(s);
	mesh_free(m);
	SDL_Quit();
	return 0;
}
