#pragma once

#include "Setting.h"
#include "src/engine//utils/utils.h"
#include "CommandSystem.h"
//#include "GameLogic.h"
#include "InputHandler.h"

//using std::string;
using namespace std;

namespace Settings
{
	namespace detail
	{
		//static GameLogic* m_logic;
		static InputHandler* m_input;
	}

	//void AttachLogic(GameLogic* logic);
	void AttachInput(InputHandler* input);

	extern Setting g_ResWindowWidth;
	extern Setting g_ResWindowHeight;
	extern Setting g_ResWindowBits;
	extern Setting g_ResFullscreenWidth;
	extern Setting g_ResFullscreenHeight;
	extern Setting g_ResFullscreenBits;
	extern Setting g_StartFullscreen;

	extern struct Resolution
	{
		int width;
		int height;
		int bits;
	};

	extern bool IsFullscreen;
	extern Resolution CurrentResolution;

	extern float lastX;
	extern float lastY;
}