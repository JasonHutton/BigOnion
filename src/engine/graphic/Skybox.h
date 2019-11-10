#pragma once
#include "shader_m.h"


class Skybox
{
public:
	Shader* skyboxShader;

	Skybox();

	void load(vector<std::string> faces);
	void draw();


private:
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;

	void createBuffer();
};

