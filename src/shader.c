#include "shader.h"
#include <stdlib.h>
#include "../deps/linearAlg.h"

static void check_shader_error(GLuint shader, GLuint flag, int is_program,
			       char *error_message)
{
	GLuint success = 0;
	GLchar error[1024] = { 0 };

	if (is_program)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (is_program)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		fprintf(stderr, "%s: '%s'\n",
			error_message, error);
	}
}

static GLuint create_shader(char *text, GLenum shaderType)
{
	GLuint shader;

	shader = glCreateShader(shaderType);

	if (shader == 0)
		fprintf(stderr, "Error: Shader creation failed!\n");

	const GLchar *shader_source_strings[1];
	GLint shader_source_strings_lengths[1];

	shader_source_strings[0] = text;
	shader_source_strings_lengths[0] = strlen(text);

	glShaderSource(shader, 1, shader_source_strings,
		       shader_source_strings_lengths);
	glCompileShader(shader);

	check_shader_error(shader, GL_COMPILE_STATUS, 0,
			   "Error: Shader compilation failed: ");

	return shader;
}

static char *load_shader(char *file_name)
{
	FILE *f;
	char *contents;
	long fsize;

	f = fopen(file_name, "rb");
	fseek(f, 0, SEEK_END);
	fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	contents = malloc(fsize + 1);
	fread(contents, fsize, 1, f);
	fclose(f);
	contents[fsize] = '\0';

        return contents;
}


/* static char vertex_shader_extension = ".vs"; */
/* static char fragment_shader_extension = ".fs"; */
struct shader *shader_new(char *file_name)
{
	struct shader *new_shader;
	char *fn_vs;
	char *fn_fs;
	int file_name_size;

	new_shader = malloc(sizeof(struct shader));
	file_name_size = strlen(file_name) + 4;
	fn_vs = malloc(file_name_size);
	fn_fs = malloc(file_name_size);

	strcpy(fn_vs, file_name);
	strcat(fn_vs, ".vs");
	strcpy(fn_fs, file_name);
	strcat(fn_fs, ".fs");

	new_shader->m_program = glCreateProgram();
	new_shader->m_shaders[0] = create_shader(load_shader(fn_vs),
						GL_VERTEX_SHADER);
	new_shader->m_shaders[1] = create_shader(load_shader(fn_fs),
						GL_FRAGMENT_SHADER);

	unsigned int i;
	for(i = 0; i < NUM_SHADERS; ++i)
		glAttachShader(new_shader->m_program,
			       new_shader->m_shaders[i]);

	glBindAttribLocation(new_shader->m_program, 0, "position");
	glBindAttribLocation(new_shader->m_program, 1, "texCoord");


	glLinkProgram(new_shader->m_program);
	check_shader_error(new_shader->m_program, GL_LINK_STATUS, 1,
			   "Error: Program linking failed: ");

	glValidateProgram(new_shader->m_program);
	check_shader_error(new_shader->m_program, GL_VALIDATE_STATUS, 1,
			   "Error: Program is invalid: ");

	new_shader->m_uniforms[TRANSFORM_U] = glGetUniformLocation(new_shader->m_program,
								   "transform");
	free(fn_vs);
	free(fn_fs);
	return new_shader;
}

void shader_free(struct shader *shader)
{
	unsigned int i;
	for(i = 0; i < NUM_SHADERS; ++i) {
		glDetachShader(shader->m_program,
			       shader->m_shaders[i]);
		glDeleteShader(shader->m_shaders[i]);
	}
	glDeleteProgram(shader->m_program);
	free(shader);
}

void shader_bind(struct shader *shader)
{
	glUseProgram(shader->m_program);
}

void shader_update(struct shader *shader,
		   struct transform *transform,
		   struct camera *camera)
{
	Matrix projecton = camera_get_view_projection(camera);
	/* projecton.m[15] = 1.0f; */
	Matrix model = *transform_get_model(transform);
	Matrix result = multiplymat4(&projecton, &model);
	/* rotateX(&transform->model, 0.05); */
	/* glUniformMatrix4fv(shader->m_uniforms[TRANSFORM_U], 1, */
	/* 		   GL_TRUE, */
	/* 		   multiplymat4(&projecton, */
	/* 				transform_get_model(transform)).m); */
	/* projecton.m[3] = 0.5; */
	/* projecton.m[7] = 0.5; */

	/* printf("%f, %f, %f, %f\n" */
	/*        "%f, %f, %f, %f\n" */
	/*        "%f, %f, %f, %f\n" */
	/*        "%f, %f, %f, %f\n", */
	/*        projecton.m[0], projecton.m[1], projecton.m[2], projecton.m[3], projecton.m[4], */
	/*        projecton.m[5], projecton.m[6], projecton.m[7], projecton.m[8], projecton.m[9], */
	/*        projecton.m[10], projecton.m[11], projecton.m[12], projecton.m[13], projecton.m[14], */
	/*        projecton.m[15]); */
	/* getchar(); */
	glUniformMatrix4fv(shader->m_uniforms[TRANSFORM_U], 1,
			   GL_FALSE,
			   &(result.m[0]));
	/* glUniformMatrix4fv(shader->m_uniforms[TRANSFORM_U], 1, */
	/* 		   GL_TRUE, ); */
}
