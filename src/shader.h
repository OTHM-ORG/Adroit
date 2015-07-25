#ifndef SHADER_H
#define SHADER_H

#include <string.h>
#include <stdio.h>
#include <GL/glew.h>
#include "transform.h"

#define NUM_SHADERS 2

enum
{
	TRANSFORM_U,

	NUM_UNIFORMS
};

struct shader {
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

struct shader *shader_new(char *file_name);
void shader_bind(struct shader *shader);
void shader_free(struct shader *shader);
void shader_update(struct shader *shader,
		   struct transform *transform);

#endif
