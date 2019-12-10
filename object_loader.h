#pragma once

#include <iostream>

#include "yaml-cpp/yaml.h"
#include <exception>>
#include "../FileSystem.h"
#include <string>

#include "src/engine/ECS/Component.h"
#include "src/engine/ECS/GameObject.h"
#include "src/engine/graphic/camera.h"

#include "src/engine/graphic/shader_m.h"

#include "src/engine/BOEngine.h"

void HandleScalar(std::string scalar);
void WalkNode(YAML::Node node);
GameObject* Object_Load(YAML::Node node, BOEngine* engine, Shader* shader);
GameObject* Object_Load(std::string filename, BOEngine* engine, Shader* shader);
GameObject* Audio_Load(std::string filename, BOEngine* engine, Shader* shader, Camera* camera, AudioEngine* audio);
vector<std::string> Skybox_Load(std::string filename);