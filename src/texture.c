#include <stdlib.h>
#include <stdio.h>
#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"
#include <assert.h>

struct texture *texture_new(char *file_name)
{
	struct texture *new_texture;
	int width, height, num_components;
	unsigned char *image_data;

	new_texture = malloc(sizeof(struct texture));
	image_data = stbi_load(file_name, &width, &height, &num_components, 4);

	if (image_data == NULL)
		fprintf(stderr, "Texture loading failed for texture: %s\n",
			file_name);

	glGenTextures(1, &new_texture->m_texture);
	glBindTexture(GL_TEXTURE_2D, new_texture->m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		     GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);
	return new_texture;
}

void texture_free(struct texture *texture)
{
	glDeleteTextures(1, &texture->m_texture);
	free(texture);
}

void texture_bind(struct texture *texture, unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, texture->m_texture);
}
