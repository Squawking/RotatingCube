#include <iostream>
#include "SDL2/SDL.h"
#include "GL/glew.h"

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event event;

bool running = true;

void CreateWindow(SDL_Window* window, SDL_GLContext glContext, const std::string& title, int width, int height) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (window == NULL) {
		std::cerr << "Window could not be created" << std::endl;
	}

	glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL) {
		std::cerr << "OpenGL context could not be opened" << std::endl;
	}

	GLuint status = glewInit();
	if (status != GLEW_OK) {
		std::cerr << "GLEW could not be initialized" << std::endl;
	}

}

void DestroyWindow() {

	SDL_GL_CreateContext(window);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void inputListen() {

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				running = false;
				break;
			}
		}
	}
}

void draw() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	SDL_GL_SwapWindow(window);

}

int main() {

	CreateWindow(window, glContext, "Hello", 800, 600);

	while (running) {

		draw();

		inputListen();

	}

	DestroyWindow();

	return 0;
}
