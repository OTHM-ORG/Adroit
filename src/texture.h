#ifndef TEXTURE_H
#define TEXTURE_H

#include <string.h>
#include <GL/glew.h>

struct texture {
	char *filename;
	GLuint m_texture;
};

struct texture *texture_new(char *file_name);
void texture_free(struct texture *texture);
void texture_bind(struct texture *texture, unsigned int unit);

#endif
