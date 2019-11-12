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
	RB_CUBE
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
};

// It probably makes more sense to try to handle individual component collections rather than all of them at once here. Fix later.
void Component_Load(YAML::Node node, GameObject* gObj, BOEngine* engine, Shader* shader)
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
				}
				else if (sit->first.as<string>().compare("model") == 0)
				{
					properties.renderModel = sit->second.as<string>();
				}
				else if (sit->first.as<string>().compare("cube") == 0) // This is really brittle, fix it up later.
				{
					properties.rbType = RB_CUBE;
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
		if (properties.useSize && properties.useMass && properties.useBounciness)
		{
			switch (properties.rbType)
			{
			case RB_CUBE:
				gObj->addComponent(RigidBodyComponent::createWithCube(properties.size[0], properties.size[1], properties.size[2], properties.mass, properties.bounciness));
				break;
			case RB_NONE:
			default:
				break;
			}
		}
		else if (properties.useSize && properties.useMass)
		{
			switch (properties.rbType)
			{
			case RB_CUBE:
				gObj->addComponent(RigidBodyComponent::createWithCube(properties.size[0], properties.size[1], properties.size[2], properties.mass));
				break;
			case RB_NONE:
			default:
				break;
			}
		}
		else if (properties.useSize)
		{
			switch (properties.rbType)
			{
			case RB_CUBE:
				gObj->addComponent(RigidBodyComponent::createWithCube(properties.size[0], properties.size[1], properties.size[2]));
				break;
			case RB_NONE:
			default:
				break;
			}
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
			/*
			std::vector<float> scale;
			for (auto pit = it->second.begin(); pit != it->second.end(); ++pit)
			{
				scale.push_back(atof(pit->Scalar().c_str())); // Kinda questionable, clean up later...
			}

			if (scale.size() == 1)
				gObj->transform.scale = scale[0];
			else
				gObj->transform.scale = Vector3f(scale[0], scale[1], scale[2]);
			*/
			string scale = it->second.as<string>();
			gObj->transform.scale = atof(scale.c_str());
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
		else if (it->first.as<std::string>().compare("component") == 0)
		{
			Component_Load(it->second, gObj, engine, shader); // There may be purposes to walking through it->first, but for the uses so far, this just results in "component" which we already know.
		}
	}

	return gObj;
}

GameObject* Object_Load(std::string filename, BOEngine* engine, Shader* shader)
{
	std::string osPath;
	FileSystem::BuildOSPath(FileSystem::FindFile(filename), filename, osPath);
	YAML::Node node = YAML::LoadFile(osPath);
	YAML::Node obj = node["onion"]; // Fix me

	return Object_Load(obj, engine, shader);
}