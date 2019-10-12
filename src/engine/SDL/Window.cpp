#include "Window.h"

//Window::Window(char title[20], Uint32 w = 720, Uint32 h = 1280, int flag = 0)
Window::Window(Uint32 w = 720, Uint32 h = 1280, int flag = 0)
{
	load = false;
	if (!SDL_Init(SDL_INIT_VIDEO))
		if (window = SDL_CreateWindow("good", 0, 0, w, h, flag))
			if (renderer = SDL_CreateRenderer(window, -1, 0))
			{
				//window ok
				load = true;
			}
}
Window::~Window()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::fullWindow()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, NULL);
}
void Window::reflush()
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
}
