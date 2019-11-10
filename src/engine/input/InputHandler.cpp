#include "InputHandler.h"
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <iostream>

InputHandler::InputHandler()
{

	for (map<int, keyState>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		UnBind(it->second);
	}
	
	// Setup the default controls.
	BindDefault(GLFW_KEY_ESCAPE, UB_FORCE_QUIT);
	BindDefault(GLFW_KEY_W, UB_MOVE_FORWARD);
	BindDefault(GLFW_KEY_S, UB_MOVE_BACKWARD);
	BindDefault(GLFW_KEY_A, UB_MOVE_LEFT);
	BindDefault(GLFW_KEY_D, UB_MOVE_RIGHT);

	BindDefault(GLFW_KEY_UP, UB_MOVE_FORWARD);
	BindDefault(GLFW_KEY_DOWN, UB_MOVE_BACKWARD);
	BindDefault(GLFW_KEY_LEFT, UB_MOVE_LEFT);
	BindDefault(GLFW_KEY_RIGHT, UB_MOVE_RIGHT);
	
	ResetBindings(); // Set the default controls.

}

void InputHandler::Bind(const int& key, const usercmdButton_t& button, const string& context)
{
	keys[key].keyDown = false;
	keys[key].prevKeyDown = false;
	keys[key].repeats = 0;
	keys[key].controls.SetControl(button, context);
}

void InputHandler::BindDefault(const int& key, const usercmdButton_t& button, const string& context)
{
	if (keys.find(key) == keys.end())
	{
		keyState ks;
		ks.defaultControls.SetControl(button, context);
		keys.insert({ key, ks });
	}
	else
	{
		keys[key].defaultControls.SetControl(button, context);
	}
}

void InputHandler::ResetBinding(const int& key)
{
	UnBind(key);

	ContextControl control = keys[key].defaultControls;
	if (control.IsSet())
	{
		vector<string> contexts;
		control.GetContexts(contexts);
		for (vector<string>::const_iterator it = contexts.begin(); it != contexts.end(); it++)
		{
			Bind(key, control.GetControl(*it), *it);
		}
	}
}

void InputHandler::ResetBindings()
{
	for (map<int, keyState>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		ResetBinding(it->first);
	}
}

const ContextControl& InputHandler::GetControl(const int& key)
{
	return this->keys[key].controls;
}

/*const keyState& InputHandler::GetKeyState(const int& scankey, const string& context) const
{
	return keys[MapKey(scankey)];
}*/

void InputHandler::UnBind(const int& key, const string& context)
{
	UnBind(keys[key], context);
}

void InputHandler::UnBind(keyState& key, const string& context)
{
	key.keyDown = false;
	key.prevKeyDown = false;
	key.repeats = 0;
	key.controls.UnSetAllControls();
}

void InputHandler::UnBindAll()
{
	for (map<int, keyState>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		UnBind(it->second);
	}
}

map<int, keyState>& InputHandler::GetAllKeyStates()
{
	return keys;
}