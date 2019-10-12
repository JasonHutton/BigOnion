#include "Font.h"

	TTF_Font* font;
	
	Font::Font(int size = 100)
	{
		TTF_Init();
	    font = NULL;

	}

	
	Font::~Font()
	{
		TTF_CloseFont(font);
		font = 0;
		TTF_Quit();
	}

	//text to texture
	SDL_Texture* Font::loadTex(char* str, int type = 4)
	{
		switch (type)
		{
		case 0:TTF_SetFontStyle(font, TTF_STYLE_BOLD); break; //粗体
		case 1:TTF_SetFontStyle(font, TTF_STYLE_ITALIC); break; //斜体
		case 2:TTF_SetFontStyle(font, TTF_STYLE_UNDERLINE); break; //下划线
		case 3:TTF_SetFontStyle(font, TTF_STYLE_STRIKETHROUGH); break; //删除线
		case 4:TTF_SetFontStyle(font, TTF_STYLE_NORMAL); break; //正常
		}

		//back color text
		SDL_Color color = { 0, 0, 0, 255 };

		SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, color);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		SDL_FreeSurface(surface);
		return texture;

	}
