#include <memory>
#include "game/game_loader.h"
#include "engine/BOEngine.h"


#include<stdio.h>
#include<stdlib.h>

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
		string homePath = getenv("APPDATA"); // C:\Users\*Username*\AppData\Roaming
		if (!(homePath[homePath.length()] == '\\' || homePath[homePath.length()] == '/'))
		{
			homePath += "/";
		}
		homePath += "BigOnion/"; // C:\Users\*Username*\AppData\Roaming/BigOnion/
		homePath = FileSystem::ReplaceSeparators(homePath); // C:/Users/*Username*/AppData/Roaming/BigOnion/
		// Create the directory if it doesn't exist.
		if (!FileSystem::PathExists(homePath, false))
		{
			FileSystem::CreatePath(homePath, false);
		}
		FileSystem::Init("./src", homePath);

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

int main()
{
	return runMain();
}


