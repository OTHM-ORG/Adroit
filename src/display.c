#include "display.h"

struct display *display_new(int width, int height, char *title)
{
	struct display *new_display;

	new_display = malloc(sizeof(struct display));
	new_display->width = width;
	new_display->height = height;
	new_display->title = title;

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	new_display->m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, width, height,
						 SDL_WINDOW_OPENGL);
	new_display->m_glContext = SDL_GL_CreateContext(new_display->m_window);

	new_display->is_closed = 0;

	return new_display;
}

void display_free(struct display *old_display)
{
	SDL_GL_DeleteContext(old_display->m_glContext);
	SDL_DestroyWindow(old_display->m_window);
	free(old_display);
}

void update(struct display *display)
{
	SDL_GL_SwapWindow(display->m_window);

	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if(e.type == SDL_QUIT)
			display->is_closed = 1;
	}
}

void clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
}
