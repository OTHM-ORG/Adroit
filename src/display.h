#ifndef DISPLAY
#define DISPLAY

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>

struct display
{
	int width;
	int height;
	char *title;
	SDL_Window *m_window;
	SDL_GLContext m_glContext;
	int is_closed;
};

struct display *display_new(int width, int height, char *title);
void display_free(struct display *display);
void update(struct display *display);
void clear(float r, float g, float b, float a);

#endif
