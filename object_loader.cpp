#include "object_loader.h"

// Debugging stuff...
void HandleScalar(std::string scalar)
{
	std::cout << scalar << std::endl;
}

void WalkNode(YAML::Node node) {
	switch (node.Type()) {
	case YAML::NodeType::Null:
		//HandleNull();
		break;
	case YAML::NodeType::Scalar:
		HandleScalar(node.Scalar());
		break;
	case YAML::NodeType::Sequence:
		for (auto it = node.begin(); it != node.end(); ++it) {
			WalkNode(*it);
		}
		break;
	case YAML::NodeType::Map:
		for (auto it = node.begin(); it != node.end(); ++it) {
			WalkNode(it->first);
			WalkNode(it->second);
		}
		break;
	case YAML::NodeType::Undefined:
		throw std::runtime_error("undefined node!");
	}
}
// Debugging stuff...

std::string NodeType(YAML::Node node)
{
	switch (node.Type()) {
	case YAML::NodeType::Null:
		return "NodeType=Null";
	case YAML::NodeType::Scalar:
		return "NodeType=Scalar";
	case YAML::NodeType::Sequence:
		return "NodeType=Sequence";
	case YAML::NodeType::Map:
		return "NodeType=Map";
	case YAML::NodeType::Undefined:
		return "NodeType=Undefined";
	}
}

enum rbTypes
{
	RB_NONE = 0,
	RB_CUBE,
	RB_PLANE,
	RB_MESH
};

class ComponentProperties
{
public:
	bool useSize = false;
	Vector3f size;

	bool useMass = false;
	float mass;

	bool useBounciness = false;
	float bounciness;

	bool useRigidBody = false;
	rbTypes rbType = RB_NONE;

	bool useRender = false;
	std::string renderModel;

	bool useConstant = false;
	float constant;

	bool useNormal = false;
	Vector3f normal;

	bool useId = false;
	int id;

	bool useRenderComponentModel = false;
	// useRenderComponentModel REQUIRES the renderComponent to be loaded first, for now.

	bool useAudioPlayer = false;
	std::string sound;

	float volumeDb;

	bool is3D = false;
	bool isLooping = false;
	bool isStreaming = false;

	bool useSetVolume;
	float volume; // Not really sure what's different here from volumeDb, no time to look into it.
	bool isMusic = false;
};

// It probably makes more sense to try to handle individual component collections rather than all of them at once here. Fix later.
void Component_Load(YAML::Node node, GameObject* gObj, BOEngine* engine, Shader* shader, AudioEngine* audio)
{
	ComponentProperties properties;

	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
	{
		if (it->Type() == YAML::NodeType::Map)
		{
			//std::cout << NodeType(it->first) << std::endl;
			for (auto sit = it->begin(); sit != it->end(); sit++)
			{
				if (sit->first.as<string>().compare("type") == 0)
				{
					if (sit->second.as<string>().compare("RigidBody") == 0)
					{
						properties.useRigidBody = true;
					}
					else if (sit->second.as<string>().compare("Render") == 0)
					{
						properties.useRender = true;
					}
					else if (sit->second.as<string>().compare("AudioPlayer") == 0)
					{
						properties.useAudioPlayer = true;
					}
				}
				else if (sit->first.as<string>().compare("model") == 0)
				{
					properties.renderModel = sit->second.as<string>();
					if (properties.renderModel.compare("RenderComponentModel") == 0) // This is really brittle, fix it up later.
					{
						properties.useRenderComponentModel = true; // useRenderComponentModel REQUIRES the renderComponent to be loaded first, for now.
						properties.renderModel = ""; // It may make sense to actually not clear this, or set it to something specific, but just doing so for now.
					}
				}
				else if (sit->first.as<string>().compare("sound") == 0)
				{
					properties.sound = sit->second.as<string>();
				}
				else if (sit->first.as<string>().compare("volumeDB") == 0)
				{
					properties.volumeDb = atof(sit->second.as<string>().c_str());
				}
				else if (sit->first.as<string>().compare("is3D") == 0)
				{
					properties.is3D = atoi(sit->second.as<string>().c_str());
				}
				else if (sit->first.as<string>().compare("isLooping") == 0)
				{
					properties.isLooping = atoi(sit->second.as<string>().c_str());
				}
				else if (sit->first.as<string>().compare("isStreaming") == 0)
				{
					properties.isStreaming = atoi(sit->second.as<string>().c_str());
				}
				else if (sit->first.as<string>().compare("cube") == 0) // This is really brittle, fix it up later.
				{
					properties.rbType = RB_CUBE;
				}
				else if (sit->first.as<string>().compare("plane") == 0) // This is really brittle, fix it up later.
				{
					properties.rbType = RB_PLANE;
				}
				else if (sit->first.as<string>().compare("mesh") == 0) // This is really brittle, fix it up later.
				{
					properties.rbType = RB_MESH;
				}
				else if (sit->first.as<string>().compare("size") == 0)
				{
					std::vector<float> size;
					for (auto pit = sit->second.begin(); pit != sit->second.end(); ++pit)
					{
						size.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
					}

					properties.size = Vector3f(size[0], size[1], size[2]);
					properties.useSize = true;
				}
				else if (sit->first.as<string>().compare("mass") == 0)
				{
					properties.mass = atof(sit->second.as<string>().c_str());
					properties.useMass = true;
				}
				else if (sit->first.as<string>().compare("normal") == 0)
				{
					std::vector<float> normal;
					for (auto pit = sit->second.begin(); pit != sit->second.end(); ++pit)
					{
						normal.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
					}

					properties.normal = Vector3f(normal[0], normal[1], normal[2]);
					properties.useNormal = true;
				}
				else if (sit->first.as<string>().compare("constant") == 0)
				{
					properties.constant = atof(sit->second.as<string>().c_str());
					properties.useConstant = true;
				}
				else if (sit->first.as<string>().compare("bounciness") == 0)
				{
					properties.bounciness = atof(sit->second.as<string>().c_str());
					properties.useBounciness = true;
				}
				else if (sit->first.as<string>().compare("id") == 0)
				{
					properties.id = atoi(sit->second.as<string>().c_str());
					properties.useId = true;
				}
				else if (sit->first.as<string>().compare("volume") == 0)
				{
					properties.volume = atof(sit->second.as<string>().c_str());
					properties.useSetVolume = true;
				}
				else if (sit->first.as<string>().compare("isMusic") == 0)
				{
					properties.isMusic = atoi(sit->second.as<string>().c_str());
				}
				/*else
				{
					std::cout << NodeType(sit->first) << " " << sit->first.as<string>() << std::endl;
					std::cout << NodeType(sit->second) << " " << sit->second.as<string>() << std::endl;
				}*/
			}
		}
	}

	// Actually construct the component that's had parts of it delayed.
	if (properties.useRender)
	{
		gObj->addComponent(new RenderComponent(engine, properties.renderModel, shader));
	}

	if (properties.useRigidBody)
	{
		switch (properties.rbType)
		{
		case RB_CUBE:
			if (properties.useSize && properties.useMass && properties.useBounciness)
				gObj->addComponent(RigidBodyComponent::createWithCube(properties.size[0], properties.size[1], properties.size[2], properties.mass, properties.bounciness));
			else if (properties.useSize && properties.useMass)
				gObj->addComponent(RigidBodyComponent::createWithCube(properties.size[0], properties.size[1], properties.size[2], properties.mass));
			else if (properties.useSize)
				gObj->addComponent(RigidBodyComponent::createWithCube(properties.size[0], properties.size[1], properties.size[2]));
			break;
		case RB_PLANE:
			if(properties.useNormal && properties.useConstant)
				gObj->addComponent(RigidBodyComponent::createWithPlane(properties.normal[0], properties.normal[1], properties.normal[2], properties.constant));
			break;
		case RB_MESH:
			// useRenderComponentModel REQUIRES the renderComponent to be loaded first, for now.
			if (properties.useRenderComponentModel && properties.useBounciness && properties.useId)
				gObj->addComponent(RigidBodyComponent::createWithMesh(&gObj->getComponent<RenderComponent>()->model, properties.bounciness, properties.id));
			break;
		case RB_NONE:
		default:
			break;
		}
	}

	if (properties.useAudioPlayer)
	{
		gObj->addComponent(new AudioPlayerComponent(*audio, properties.sound, properties.volumeDb, properties.is3D, properties.isLooping, properties.isStreaming));
		if (properties.useSetVolume)
		{
			gObj->getComponent<AudioPlayerComponent>()->volume(properties.volume, properties.isMusic);
		}
	}
}

GameObject* Object_Load(YAML::Node node, BOEngine* engine, Shader* shader)
{
	GameObject* gObj = NULL;

	for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
	{
		//std::cout << NodeType(it->first) << std::endl;
		//std::cout << NodeType(it->second) << std::endl;

		if (it->first.as<std::string>().compare("name") == 0)
		{
			string name = it->second.as<string>();
			gObj = new GameObject(name);
		}
		else if (it->first.as<std::string>().compare("scale") == 0)
		{
			if(it->second.Type() == YAML::NodeType::Sequence)
			{
				std::vector<float> scale;
				for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
				{
					scale.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
				}
				gObj->transform.scale = Vector3f(scale[0], scale[1], scale[2]);
			}
			else if (it->second.Type() == YAML::NodeType::Scalar)
			{
				string scale = it->second.as<string>();
				gObj->transform.scale = Vector3f(atof(scale.c_str()), atof(scale.c_str()), atof(scale.c_str()));
			}
		}
		else if (it->first.as<std::string>().compare("position") == 0)
		{
			std::vector<float> pos;
			for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
			{
				pos.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
			}

			gObj->transform.position = Vector3f(pos[0], pos[1], pos[2]);
		}
		else if (it->first.as<std::string>().compare("rotation") == 0)
		{
			std::vector<float> pos;
			for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
			{
				pos.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
			}

			gObj->transform.rotation = Vector3f(pos[0], pos[1], pos[2]);
		}
		else if (it->first.as<std::string>().compare("component") == 0)
		{
			Component_Load(it->second, gObj, engine, shader, NULL); // There may be purposes to walking through it->first, but for the uses so far, this just results in "component" which we already know.
		}
	}

	return gObj;
}

GameObject* Object_Load(std::string filename, BOEngine* engine, Shader* shader)
{
	std::string osPath;
	FileSystem::BuildOSPath(FileSystem::FindFile(filename), filename, osPath);
	YAML::Node node = YAML::LoadFile(osPath);
	YAML::Node obj;

	if (obj = node["object"])
	{
		return Object_Load(obj, engine, shader);
	}
	else if (obj = node["skybox"])
	{
		return NULL; // Not actually using this route for now, just testing how this loads.
	}	
}

// This is ugly and hacky, needs cleaning up later, into something inherited with OOP.
GameObject* Audio_Load(std::string filename, BOEngine* engine, Shader* shader, Camera* camera, AudioEngine* audio)
{
	std::string osPath;
	FileSystem::BuildOSPath(FileSystem::FindFile(filename), filename, osPath);
	YAML::Node node = YAML::LoadFile(osPath);
	YAML::Node obj;

	GameObject* gObj = NULL;

	if (obj = node["audio"])
	{
		for (YAML::const_iterator it = obj.begin(); it != obj.end(); ++it)
		{
			//std::cout << NodeType(it->first) << std::endl;
			//std::cout << NodeType(it->second) << std::endl;

			if (it->first.as<std::string>().compare("name") == 0)
			{
				string name = it->second.as<string>();
				gObj = new GameObject(name);
			}
			else if (it->first.as<std::string>().compare("position") == 0)
			{
				if (it->second.Type() == YAML::NodeType::Sequence)
				{
					for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
					{
						std::vector<float> pos;
						for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
						{
							pos.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
						}

						gObj->transform.position = Vector3f(pos[0], pos[1], pos[2]);
					}
				}
				else if (it->second.Type() == YAML::NodeType::Scalar)
				{
					Vector3f pos;
					if (it->second.as<string>().compare("CameraPosition") == 0) // This is really brittle, fix it up later.
					{
						pos.x = camera->Position.x;
						pos.y = camera->Position.y;
						pos.z = camera->Position.z;

						gObj->transform.position = pos;
					}

					gObj->transform.position = Vector3f(pos.x, pos.y, pos.z);
				}
			}
			else if (it->first.as<std::string>().compare("component") == 0)
			{
				Component_Load(it->second, gObj, engine, shader, audio); // There may be purposes to walking through it->first, but for the uses so far, this just results in "component" which we already know.
			}
		}

		return gObj;
	}

	return gObj;
}

vector<std::string> Skybox_Load(std::string filename)
{
	std::string osPath;
	FileSystem::BuildOSPath(FileSystem::FindFile(filename), filename, osPath);
	YAML::Node node = YAML::LoadFile(osPath);
	YAML::Node obj;

	vector<std::string> faces;
	if (obj = node["skybox"])
	{
		for (YAML::const_iterator it = obj.begin(); it != obj.end(); ++it)
		{
			if (it->first.as<std::string>().compare("name") == 0)
			{
				// Do nothing. We don't really care currently.
			}
			else if (it->first.as<std::string>().compare("faces") == 0)
			{
				if (it->second.Type() == YAML::NodeType::Sequence)
				{
					for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
					{
						faces.push_back(pit->as<std::string>()); // Kinda questionable, clean up later...
					}
				}
			}
		}
	}

	return faces;
}