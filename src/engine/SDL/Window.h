#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "SDL.h"
#include <iostream>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

using namespace std;

class Window
{
public:
	//upload success or not
	bool load;
	Window(Uint32, Uint32, int);

	//
	~Window();
	
	//fill windoe
	void fullWindow();
	
	//update window
	void reflush();
	
};
