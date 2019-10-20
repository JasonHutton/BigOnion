#include <memory>
#include "game/game_loader.h"
#include "engine/BOEngine.h"


#include<stdio.h>
#include<stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION

#include "../../Settings.h"
#include "../SoundFile.h"
#include "../TextFile.h"


int runMain()
{
	std::unique_ptr<BOEngine> engine;
	try {
		std::unique_ptr<GameLoader> loader = std::make_unique<GameLoader>();

		engine = std::make_unique<BOEngine>();
		
		std::cout << "Initializing Virtual File System..." << std::endl;
		FileSystem::Init("./src");

		CommandSystem::AttachInput(&loader->input);

		std::cout << "Loading configuration settings..." << std::endl;
		TextFile* settingsFile = new TextFile("settings.cfg");
		if (settingsFile->Read())
		{
			Settings::LoadSettingsFromData(settingsFile->GetData());
		}
		else
		{
			std::cout << "Configuration settings not found. Saving default configuration settings..." << std::endl; // Not exactly accurate, this is a few lines down outside of this else block. But it serves the purpose.
			// If there's no configuration file, detect the current screen settings and set them as the default for fullscreen mode.

			/*
			GLFWmonitor *primary = glfwGetPrimaryMonitor(); // GLFW not initializeed yet, so this fails, I think?
			const GLFWvidmode *currentMode = glfwGetVideoMode(primary);
			if (currentMode != NULL && currentMode->width != 0 && currentMode->height != 0)
			{
				Settings::g_ResFullscreenBits.Set(currentMode->blueBits); // Need to check if this is total 32 bits or something, or just 8*8*8?
				Settings::g_ResFullscreenHeight.Set(currentMode->height);
				Settings::g_ResFullscreenWidth.Set(currentMode->width);
			}
			*/
		}
		settingsFile->SetData(Settings::SaveSettingsToData());
		settingsFile->Write(false); // Don't overwrite any existing settings. Only write new ones if there is no file.
		delete settingsFile;

		// Initialize some global settings...
		Settings::IsFullscreen = Settings::g_StartFullscreen.GetBool();
		if (Settings::IsFullscreen)
		{
			Settings::CurrentResolution.width = Settings::g_ResFullscreenWidth.GetInteger();
			Settings::CurrentResolution.height = Settings::g_ResFullscreenHeight.GetInteger();
			Settings::CurrentResolution.bits = Settings::g_ResFullscreenBits.GetInteger();
		}
		else
		{
			Settings::CurrentResolution.width = Settings::g_ResWindowWidth.GetInteger();
			Settings::CurrentResolution.height = Settings::g_ResWindowHeight.GetInteger();
			Settings::CurrentResolution.bits = Settings::g_ResWindowBits.GetInteger();
		}
		Settings::lastX = Settings::CurrentResolution.width / 2.0f;
		Settings::lastY = Settings::CurrentResolution.height / 2.0f;
		// Done initializing global settings...

		loader->createGame();
		engine->initialize();

		loader->setEngine(*engine);
		loader->startGame();

		return engine->exit();
	}
	catch (std::exception& e) {
		if (engine) {
			engine->exitInError(e.what());
		}
		else {
			std::cout << "Exception initialising core: " << e.what() << std::endl;
		}
		return 1;
	}
	catch (...) {
		if (engine) {
			engine->exitInError("");
		}
		else {
			std::cout << "Unknown exception initialising core." << std::endl;
		}
		return 1;
	}
}
/*
int main()
{
	return runMain();
}

*/
int main(int argc, char* argv[]) {

	SDL_Surface* pTextSurface = NULL;
	SDL_Texture* pTextTexture = NULL;
	
	SDL_Rect rect;
	rect.x = 100;
	rect.y = 100;

	SDL_Rect Trect;
	Trect.x = 300;
	Trect.y = 100;
	Trect.w = 100;
	Trect.h = 50;

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("sdl",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600,
		SDL_WINDOW_SHOWN);

	SDL_Renderer* rend = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	
	//background*****
	SDL_Rect xrect;
	xrect.x = 0;
	xrect.y = 0;
	xrect.h = 600;
	xrect.w = 800;

	SDL_Surface* image2 = IMG_Load("onion.jpg");
	SDL_Texture* imagetex2 = SDL_CreateTextureFromSurface(rend, image2);

	SDL_RenderCopy(rend, imagetex2, NULL, &xrect);
	SDL_RenderPresent(rend);


	//Text******************************
	if (TTF_Init() == -1)
		return -1;
	
	TTF_Font* font;
	font = TTF_OpenFont("Roboto-Black.ttf", 12);
	if (!font)
	{

		return -1;
	}

	SDL_Color color2 = { 255,225,0 };

	
	const char* Text[3] = { "Play Game", "Shop", "Rate List" };
	for (int i = 0; i < 3; i++) {

		pTextSurface = TTF_RenderText_Blended(font, Text[i], color2);
		pTextTexture = SDL_CreateTextureFromSurface(rend, pTextSurface);


		SDL_RenderCopy(rend, pTextTexture, NULL, &Trect); 
		SDL_RenderPresent(rend);
		Trect.y = Trect.y + 100;
	}
	//Text*****


	//Buttons******************************

	SDL_Surface* image = IMG_Load("B1.png");
	SDL_Texture* imagetex = NULL;
	

	rect.w = image->w;
	rect.h = image->h;

	int imagehh = image->h;
	int imagehw = image->w;
	int mouseX = 0;
	int mouseY = 0;

	
	for (int i = 0; i < 3; i++) {

		const char* Button[3] = { "B1.png", "shop2.png", "onionrate.png" };
		SDL_Surface* image = IMG_Load(Button[i]);
		SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 255, 255));//transparent white
	    imagetex = SDL_CreateTextureFromSurface(rend, image);

		//SDL_BlitSurface(image, NULL, surface, &rect);
		//SDL_RenderClear(rend);
		SDL_RenderCopy(rend, imagetex, NULL, &rect);
		SDL_RenderPresent(rend);
		rect.y = rect.y + 100;
	}
	rect.y = 100;
	SDL_RenderClear(rend);
	//Buttons******************************

	//Event********************
	SDL_Event event;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT) {
				quit = true;
			}

			else if (event.type == SDL_MOUSEMOTION) {
				mouseX = event.motion.x;
				mouseY = event.motion.y;
				//cout << mouseX << "," << mouseY << endl;
			}
			
			else  if (event.type == SDL_MOUSEBUTTONDOWN) {

				if (event.button.button == SDL_BUTTON_LEFT) {
					if (rect.x + imagehw > mouseX && mouseX > rect.x && rect.y + imagehh > mouseY && mouseY > rect.y) {
		
						return runMain();
					
						
					}
					else if (rect.x + imagehw > mouseX && mouseX > rect.x  && rect.y + 100 + imagehh > mouseY && mouseY > rect.y + 100) {
						
						cout << "lol" << endl;
					}
					else if (rect.x  + imagehw > mouseX && mouseX > rect.x && rect.y + 200 + imagehh > mouseY && mouseY > rect.y + 200) {
						cout << "lmao" << endl;
					}
				}
			}   
			SDL_UpdateWindowSurface(window);
		}
		SDL_Delay(5);
	}

	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);
	SDL_FreeSurface(pTextSurface);
	SDL_DestroyRenderer(rend);
	SDL_DestroyTexture(pTextTexture);
	SDL_DestroyTexture(imagetex);
	SDL_DestroyTexture(imagetex2);
	TTF_CloseFont(font);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


