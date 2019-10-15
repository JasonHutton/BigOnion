#include "InputHandler.h"
#include <stdexcept>

InputHandler::InputHandler()
{
	
	for (map<int, keyState>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		UnBind(it->second);
	}
	
	// Setup the default controls.
	BindDefault('`', UB_TOGGLECONSOLE);

	BindDefault(K_F1, UB_RED);
	BindDefault(K_F2, UB_GREEN);
	BindDefault(K_F3, UB_BLUE);
	BindDefault('q', UB_SELECT_PREV);
	BindDefault('w', UB_SELECT_NEXT);
	BindDefault(K_ESCAPE, UB_FORCE_QUIT);
	BindDefault(K_F5, UB_LOG_GLEXTENSIONS);

	BindDefault(K_UPARROW, UB_ROT_UP);
	BindDefault(K_DOWNARROW, UB_ROT_DOWN);
	BindDefault(K_LEFTARROW, UB_ROT_LEFT);
	BindDefault(K_RIGHTARROW, UB_ROT_RIGHT);

	BindDefault(K_F6, UB_SCREENSHOT);
	
	ResetBindings(); // Set the default controls.

}

void InputHandler::KeyEvent(const int& scankey, const bool& status, const int& repeats)
{
	int mappedKey = MapKey(scankey);

	keys[mappedKey].prevKeyDown = keys[mappedKey].keyDown;
	keys[mappedKey].keyDown = status;
	keys[mappedKey].repeats = repeats;
}

/*const keyState& InputHandler::GetKey(const int& scankey) const
{
	return keys[MapKey(scankey)];
}*/

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

/*const ContextControl& InputHandler::GetControl(const int& key) const
{
	return keys[key].controls;
}*/

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

/*const keyState* const InputHandler::GetAllKeyStates() const
{
	return keys;
}*/