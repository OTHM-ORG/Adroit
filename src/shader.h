#ifndef SHADER_H
#define SHADER_H

#include <string.h>
#include <stdio.h>
#include <GL/glew.h>

#define NUM_SHADERS 2

struct shader {
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};

struct shader *shader_new(char *file_name);
void shader_bind(struct shader *shader);
void shader_free(struct shader *shader);

#endif
