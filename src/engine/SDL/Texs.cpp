#include "Texs.h"


Texs::Texs()
	{
	  
		//char* str = new char[6];
	    //str[0] = 'a';
		
		char* str[6];

		str[0] == "button1";
		str[1] == "button2";
		str[2] == "button3";
		str[3] == "button4";
		str[4] == "button5";
		str[5] == "button6";


	    //char* str[6] == { "��ť0", "��ť1", "��ť2", "��ť3", "��ť4", "�˳�" };
		for (int i = 0; i < 6; i++)
		{
			tex[i] = font.loadTex(str[i], 4);
			int w, h;
			//��ȡ�����С
			SDL_QueryTexture(tex[i], NULL, NULL, &w, &h);
			//�����������ʾ����
			box[i].x = 250;
			box[i].y = i * 150 + 100;
			box[i].w = w;
			box[i].h = h;
		}
	}

	//��������
Texs:: ~Texs()
	{
		for (int i = 0; i < 6; i++)
		{
			if (tex[i] != NULL)
				SDL_DestroyTexture(tex[i]);
		}
	}

	//��ʾtex
void Texs::showTex(int n)
	{
		SDL_RenderCopy(renderer, tex[n], NULL, &box[n]);
	}