#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"


struct vertex vertex_new(float posx, float posy, float posz,
			 float tcx, float tcy)
{
	struct vec3 new_vec3;
	struct vec2 new_vec2;
	struct vertex new_vertex;

	/* new_vec = malloc(sizeof(struct vec3)); */
	new_vec3.x = posx;
	new_vec3.y = posy;
	new_vec3.z = posz;

	new_vec2.x = tcx;
	new_vec2.y = tcy;

	new_vertex.pos = new_vec3;
	new_vertex.texCoord = new_vec2;

	return new_vertex;
}

struct mesh *mesh_new(struct vertex *verticies,
		      unsigned int num_verticies)
{
	struct mesh *new_mesh = malloc(sizeof(struct mesh));
	new_mesh->m_drawCount = num_verticies;
	new_mesh->num_verticies = num_verticies;
	new_mesh->verticies = verticies;

	glGenVertexArrays(1, &new_mesh->m_vertexArrayObject);
	glBindVertexArray(new_mesh->m_vertexArrayObject);

	struct vec3 *positions = malloc(sizeof(struct vec3) * num_verticies);
	struct vec2 *texcoords = malloc(sizeof(struct vec2) * num_verticies);

	unsigned int i;
	for (i = 0; i < num_verticies; ++i) {
		positions[i] = verticies[i].pos;
		texcoords[i] = verticies[i].texCoord;
	}

	glGenBuffers(NUM_BUFFERS, new_mesh->m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER,
		     new_mesh->m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_verticies * sizeof(positions[0]),
		     &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ARRAY_BUFFER,
		     new_mesh->m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, num_verticies * sizeof(texcoords[0]),
		     &texcoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
	free(positions);
	free(texcoords);
	return new_mesh;
}

void mesh_free(struct mesh *mesh)
{
	glDeleteVertexArrays(1, &mesh->m_vertexArrayObject);
	free(mesh);
}

void mesh_draw(struct mesh *mesh)
{
	glBindVertexArray(mesh->m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, mesh->m_drawCount);

	glBindVertexArray(0);
}

