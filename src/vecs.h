#ifndef VECTS_H
#define VECTS_H

#include "../deps/linearAlg.h"

struct vec2 {
	float x;
	float y;
};

struct vec3 {
	float x;
	float y;
	float z;
};

struct vec3 vec3_new(float x, float y, float z);

Vector4 vec3_to_4(struct vec3 vec3);

#endif
