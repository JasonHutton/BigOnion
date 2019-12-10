#pragma once
#ifndef MODEL_H
#define MODEL_H


#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "model_mesh.h"
#include "shader.h"
#include "ShaderAttribute.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <mutex>

class Model
{
public:
	/*  Model Data */

	Shader* shader;
	ShaderAttribute shaderAttribute;
	string path;

	Model(string const& _path, Shader* shader);

	// draws the model, and thus all its meshes
	void Draw();

	// draws the model with a outside set shader, won't set Attribute to it 
	void Draw(Shader* shader);

	// draws the model with shader and attribute
	void Draw(Shader* shader, ShaderAttribute* shaderAttribute);

	vector<Mesh>& getMeshes();

private:

	vector<Mesh> meshes;
	vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	string directory;

	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(string const& path);

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode* node, const aiScene* scene);

	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

	Material loadMaterial(aiMaterial* mat);
	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

	unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

	static std::mutex modelLoadMutex;

	bool firstDraw = true;
};

#endif