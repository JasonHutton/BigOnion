#pragma once
#include<stdio.h>
#include<stdlib.h>
#include "SDL.h"
#include <iostream>
#include "Font.h"
class Texs
{
public:
    SDL_Texture* tex[6];
	SDL_Rect box[6];
	Font font;
	//���캯��
	Texs();


	//��������
	~Texs();
	

	//��ʾtex
	void showTex(int n);
	
};
