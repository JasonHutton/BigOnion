#include "model.h"

// #define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h> // stb_image can only be included in cpp instead of header.

#include "../FileSystem.h"

using namespace std;

// constructor, expects a filepath to a 3D model.
Model::Model(string const& path, Shader* _shader) : shader(_shader), shaderAttribute()
{
	loadModel(path);
}

// draws the model, and thus all its meshes
void Model::Draw()
{
	this->Draw(this->shader, &this->shaderAttribute);
}

// draws the model, and thus all its meshes
void Model::Draw(Shader* _shader, ShaderAttribute* shaderAttribute)
{
	shaderAttribute->applyAttributeTo(_shader);

	this->Draw(_shader);
}

// draws the model, and thus all its meshes with a outside shader which already set
void Model::Draw(Shader* _shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(*_shader);
}

/* private Functions */
// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
void Model::loadModel(string const& path)
{
	// read file via ASSIMP
	Assimp::Importer importer;
	string osPath;
	FileSystem::BuildOSPath(FileSystem::FindFile(path), path, osPath);

	const aiScene* scene = importer.ReadFile(osPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return;
	}

	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	Material mesh_material;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		_asm {
			// vector.x = mesh->mVertices[i].x;
			imul        eax, dword ptr[ebp - 9Ch], 0Ch
			mov         ecx, dword ptr[mesh]
			mov         edx, dword ptr[ecx + 0Ch]
			movss       xmm0, dword ptr[edx + eax]
			// movss       dword ptr[ebp - 0F0h], xmm0
			movss         dword ptr[ebp - 0DCh], xmm0 // vertex.Position.x = x
			// vector.y = mesh->mVertices[i].y;
			//imul        eax, dword ptr[ebp - 9Ch], 0Ch
			//mov         ecx, dword ptr[mesh]
			//mov         edx, dword ptr[ecx + 0Ch]
			movss       xmm0, dword ptr[edx + eax + 4]
			// movss       dword ptr[ebp - 0ECh], xmm0
			movss         dword ptr[ebp - 0D8h], xmm0  // vertex.Position.y = y
			//	vector.z = mesh->mVertices[i].z;
			/*imul        eax, dword ptr[ebp - 9Ch], 0Ch
			mov         ecx, dword ptr[mesh]
			mov         edx, dword ptr[ecx + 0Ch]*/
			movss       xmm0, dword ptr[edx + eax + 8]
			// movss       dword ptr[ebp - 0E8h], xmm0
			movss       dword ptr[ebp - 0D4h], xmm0 // vertex.Position.z = z

			//	vertex.Position = vector;
			//mov         eax, dword ptr[ebp - 0F0h]
			//mov         dword ptr[ebp - 0DCh], eax // x
			//mov         ecx, dword ptr[ebp - 0ECh]
			//mov         dword ptr[ebp - 0D8h], ecx // y
			//mov         edx, dword ptr[ebp - 0E8h]
			//mov         dword ptr[ebp - 0D4h], edx // z

			// normals
			//	vector.x = mesh->mNormals[i].x;
			/*imul        eax, dword ptr[ebp - 9Ch], 0Ch
			mov         ecx, dword ptr[mesh]*/
			mov         edx, dword ptr[ecx + 10h]
			movss       xmm0, dword ptr[edx + eax]
			// movss       dword ptr[ebp - 0F0h], xmm0
			movss         dword ptr[ebp - 0D0h], xmm0
			//	vector.y = mesh->mNormals[i].y;
			/*imul        eax, dword ptr[ebp - 9Ch], 0Ch
			mov         ecx, dword ptr[mesh]
			mov         edx, dword ptr[ecx + 10h]*/
			movss       xmm0, dword ptr[edx + eax + 4]
			// movss       dword ptr[ebp - 0ECh], xmm0
			movss         dword ptr[ebp - 0CCh], xmm0
			//	vector.z = mesh->mNormals[i].z;
		/*	imul        eax, dword ptr[ebp - 9Ch], 0Ch
			mov         ecx, dword ptr[mesh]
			mov         edx, dword ptr[ecx + 10h]*/
			movss       xmm0, dword ptr[edx + eax + 8]
			// movss       dword ptr[ebp - 0E8h], xmm0
			movss         dword ptr[ebp - 0C8h], xmm0
			//	vertex.Normal = vector;
			/*mov         eax, dword ptr[ebp - 0F0h]
			mov         dword ptr[ebp - 0D0h], eax
			mov         ecx, dword ptr[ebp - 0ECh]
			mov         dword ptr[ebp - 0CCh], ecx
			mov         edx, dword ptr[ebp - 0E8h]
			mov         dword ptr[ebp - 0C8h], edx*/
		}
		// positions
		//vector.x = mesh->mVertices[i].x;
		//vector.y = mesh->mVertices[i].y;
		//vector.z = mesh->mVertices[i].z;
		//vertex.Position = vector;
		//// normals
		//vector.x = mesh->mNormals[i].x;
		//vector.y = mesh->mNormals[i].y;
		//vector.z = mesh->mNormals[i].z;
		//vertex.Normal = vector;
		// texture coordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		// tangent
		if (mesh->mTangents != nullptr) {
			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;
		}
		else {
			vertex.Tangent = glm::vec3(0.0f);
		}
		// bitangent
		if (mesh->mBitangents != nullptr) {
			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else {
			vertex.Bitangent = glm::vec3(0.0f);
		}
		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
	// 1. diffuse maps
	vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	mesh_material = loadMaterial(material);

	// return a mesh object created from the extracted mesh data
	return Mesh(vertices, indices, textures, mesh_material);
}

Material Model::loadMaterial(aiMaterial* mat)
{
	Material material;
	aiColor3D color(0.f, 0.f, 0.f);
	float flt;
	aiString str;

	mat->Get(AI_MATKEY_NAME, str);
	// mtl  name for debug;
	const char* name = str.C_Str();

	mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
	material.AmbientColor = glm::vec3(color.r, color.b, color.g);

	mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
	material.DiffuseColor = glm::vec3(color.r, color.b, color.g);

	mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
	material.SpecularColor = glm::vec3(color.r, color.b, color.g);

	mat->Get(AI_MATKEY_SHININESS, flt);
	material.Shininess = flt;

	//mat->Get(AI_MATKEY_OPACITY, flt);
	//material.OpticalDensity = flt;

	//mat->Get(AI_MATKEY_OPACITY, flt);
	//material.Dissolve = flt;

	//mat->Get(AI_MATKEY_OPACITY, flt);
	//material.Illumination = flt;

	return material;
}

// checks all material textures of a given type and loads the textures if they're not loaded yet.
// the required info is returned as a Texture struct.
vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
		bool skip = false;
		for (unsigned int j = 0; j < textures_loaded.size(); j++)
		{
			if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(textures_loaded[j]);
				skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if (!skip)
		{   // if texture hasn't been loaded already, load it
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

unsigned int Model::TextureFromFile(const char* path, const string& directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	string osPath;
	FileSystem::BuildOSPath(FileSystem::FindFile(filename), filename, osPath);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(osPath.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format = GL_RGBA;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

vector<Mesh>& Model::getMeshes()
{
	return meshes;
}

