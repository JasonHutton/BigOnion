#pragma once

#include "SDL.h"
#include "SDL_ttf.h"

#include "Window.h"

class Font
{
public:
	TTF_Font* font;
	
	Font(int );


	~Font();
	

	//text��texture
	SDL_Texture* loadTex(char, int);


};