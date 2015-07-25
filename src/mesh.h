#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include "vecs.h"

struct vertex {
	struct vec3 pos;
	struct vec2 texCoord;
};

struct vertex vertex_new(float posx, float posy, float posz,
			 float tcx, float tcy);

enum
{
	POSITION_VB,
	TEXCOORD_VB,
	NUM_BUFFERS
};

struct mesh {
	unsigned int num_verticies;
	struct vertex *verticies;
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

void mesh_draw(struct mesh *mesh);
struct mesh *mesh_new(struct vertex *verticies,
		      unsigned int num_verticies);
void mesh_free(struct mesh *mesh);

#endif
