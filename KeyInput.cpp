#include "KeyInput.h"
#include <algorithm>
#include <GLFW/glfw3.h>

namespace KeyInput
{
	// Make sure everything here is lower-case. We're not checking both ways.
	userCmdString_t	userCmdStrings[] = {
		{ "_force_quit", UB_FORCE_QUIT },
		{ "_move_forward", UB_MOVE_FORWARD },
		{ "_move_backward", UB_MOVE_BACKWARD },
		{ "_move_left", UB_MOVE_LEFT },
		{ "_move_right", UB_MOVE_RIGHT },
		{ NULL, UB_MAX_BUTTONS },

		{ NULL,	UB_NONE } // Must be last.
	};

	// Make sure everything here is upper-case. We're not checking both ways.
	keyname_t keynames[] = {
		{"UNKNOWN",	NULL,	GLFW_KEY_UNKNOWN },
		{"SPACE",	" ",	GLFW_KEY_SPACE },
		{"\'",		NULL,	GLFW_KEY_APOSTROPHE },
		{",",		NULL,	GLFW_KEY_COMMA },
		{"-",		NULL,	GLFW_KEY_MINUS },
		{".",		NULL,	GLFW_KEY_PERIOD },
		{"/",		NULL,	GLFW_KEY_SLASH },
		{"0",		NULL,	GLFW_KEY_0 },
		{"1",		NULL,	GLFW_KEY_1 },
		{"2",		NULL,	GLFW_KEY_2 },
		{"3",		NULL,	GLFW_KEY_3 },
		{"4",		NULL,	GLFW_KEY_4 },
		{"5",		NULL,	GLFW_KEY_5 },
		{"6",		NULL,	GLFW_KEY_6 },
		{"7",		NULL,	GLFW_KEY_7 },
		{"8",		NULL,	GLFW_KEY_8 },
		{"9",		NULL,	GLFW_KEY_9 },
		{";",		NULL,	GLFW_KEY_SEMICOLON },
		{"=",		NULL,	GLFW_KEY_EQUAL },
		{"A",		NULL,	GLFW_KEY_A },
		{"B",		NULL,	GLFW_KEY_B },
		{"C",		NULL,	GLFW_KEY_C },
		{"D",		NULL,	GLFW_KEY_D },
		{"E",		NULL,	GLFW_KEY_E },
		{"F",		NULL,	GLFW_KEY_F },
		{"G",		NULL,	GLFW_KEY_G },
		{"H",		NULL,	GLFW_KEY_H },
		{"I",		NULL,	GLFW_KEY_I },
		{"J",		NULL,	GLFW_KEY_J },
		{"K",		NULL,	GLFW_KEY_K },
		{"L",		NULL,	GLFW_KEY_L },
		{"M",		NULL,	GLFW_KEY_M },
		{"N",		NULL,	GLFW_KEY_N },
		{"O",		NULL,	GLFW_KEY_O },
		{"P",		NULL,	GLFW_KEY_P },
		{"Q",		NULL,	GLFW_KEY_Q },
		{"R",		NULL,	GLFW_KEY_R },
		{"S",		NULL,	GLFW_KEY_S },
		{"T",		NULL,	GLFW_KEY_T },
		{"U",		NULL,	GLFW_KEY_U },
		{"V",		NULL,	GLFW_KEY_V },
		{"W",		NULL,	GLFW_KEY_W },
		{"X",		NULL,	GLFW_KEY_X },
		{"Y",		NULL,	GLFW_KEY_Y },
		{"Z",		NULL,	GLFW_KEY_Z },
		{"[",		NULL,	GLFW_KEY_LEFT_BRACKET },
		{"\\",		NULL,	GLFW_KEY_BACKSLASH },
		{"]",		NULL,	GLFW_KEY_RIGHT_BRACKET },
		{"`",		NULL,	GLFW_KEY_GRAVE_ACCENT },
		{"NON-US#1",		NULL,	GLFW_KEY_WORLD_1 },
		{"NON-US#2",		NULL,	GLFW_KEY_WORLD_2 },
		{"ESCAPE",		NULL,	GLFW_KEY_ESCAPE },
		{"ENTER",		NULL,	GLFW_KEY_ENTER },
		{"TAB",		NULL,	GLFW_KEY_TAB },
		{"BACKSPACE",		NULL,	GLFW_KEY_BACKSPACE },
		{"INSERT",		NULL,	GLFW_KEY_INSERT },
		{"DELETE",		NULL,	GLFW_KEY_DELETE },
		{"RIGHT",		NULL,	GLFW_KEY_RIGHT },
		{"LEFT",		NULL,	GLFW_KEY_LEFT },
		{"DOWN",		NULL,	GLFW_KEY_DOWN },
		{"UP",		NULL,	GLFW_KEY_UP },
		{"PAGEUP",		NULL,	GLFW_KEY_PAGE_UP },
		{"PAGEDOWN",		NULL,	GLFW_KEY_PAGE_DOWN },
		{"HOME",		NULL,	GLFW_KEY_HOME },
		{"END",		NULL,	GLFW_KEY_END },
		{"CAPSLOCK",		NULL,	GLFW_KEY_CAPS_LOCK },
		{"SCROLLLOCK",		NULL,	GLFW_KEY_SCROLL_LOCK },
		{"NUMLOCK",		NULL,	GLFW_KEY_NUM_LOCK },
		{"PRINTSCREEN",		NULL,	GLFW_KEY_PRINT_SCREEN },
		{"PAUSE",		NULL,	GLFW_KEY_PAUSE },
		{"F1",		NULL,	GLFW_KEY_F1 },
		{"F2",		NULL,	GLFW_KEY_F2 },
		{"F3",		NULL,	GLFW_KEY_F3 },
		{"F4",		NULL,	GLFW_KEY_F4 },
		{"F5",		NULL,	GLFW_KEY_F5 },
		{"F6",		NULL,	GLFW_KEY_F6 },
		{"F7",		NULL,	GLFW_KEY_F7 },
		{"F8",		NULL,	GLFW_KEY_F8 },
		{"F9",		NULL,	GLFW_KEY_F9 },
		{"F10",		NULL,	GLFW_KEY_F10 },
		{"F11",		NULL,	GLFW_KEY_F11 },
		{"F12",		NULL,	GLFW_KEY_F12 },
		{"F13",		NULL,	GLFW_KEY_F13 },
		{"F14",		NULL,	GLFW_KEY_F14 },
		{"F15",		NULL,	GLFW_KEY_F15 },
		{"F16",		NULL,	GLFW_KEY_F16 },
		{"F17",		NULL,	GLFW_KEY_F17 },
		{"F18",		NULL,	GLFW_KEY_F18 },
		{"F19",		NULL,	GLFW_KEY_F19 },
		{"F20",		NULL,	GLFW_KEY_F20 },
		{"F21",		NULL,	GLFW_KEY_F21 },
		{"F22",		NULL,	GLFW_KEY_F22 },
		{"F23",		NULL,	GLFW_KEY_F23 },
		{"F24",		NULL,	GLFW_KEY_F24 },
		{"F25",		NULL,	GLFW_KEY_F25 },
		{"KP_0",		"0",	GLFW_KEY_KP_0 },
		{"KP_1",		"1",	GLFW_KEY_KP_1 },
		{"KP_2",		"2",	GLFW_KEY_KP_2 },
		{"KP_3",		"3",	GLFW_KEY_KP_3 },
		{"KP_4",		"4",	GLFW_KEY_KP_4 },
		{"KP_5",		"5",	GLFW_KEY_KP_5 },
		{"KP_6",		"6",	GLFW_KEY_KP_6 },
		{"KP_7",		"7",	GLFW_KEY_KP_7 },
		{"KP_8",		"8",	GLFW_KEY_KP_8 },
		{"KP_9",		"9",	GLFW_KEY_KP_9 },
		{"KP_DECIMAL",		".",	GLFW_KEY_KP_DECIMAL },
		{"KP_DIVIDE",		"/",	GLFW_KEY_KP_DIVIDE },
		{"KP_MULTIPLY",		"*",	GLFW_KEY_KP_MULTIPLY },
		{"KP_SUBTRACT",		"-",	GLFW_KEY_KP_SUBTRACT },
		{"KP_ADD",		"+",	GLFW_KEY_KP_ADD },
		{"KP_ENTER",		NULL,	GLFW_KEY_KP_ENTER },
		{"KP_EQUAL",		"=",	GLFW_KEY_KP_EQUAL },
		{"LEFTSHIFT",		NULL,	GLFW_KEY_LEFT_SHIFT },
		{"LEFTCONTROL",		NULL,	GLFW_KEY_LEFT_CONTROL },
		{"LEFTALT",		NULL,	GLFW_KEY_LEFT_ALT },
		{"LEFTSUPER",		NULL,	GLFW_KEY_LEFT_SUPER },
		{"RIGHTSHIFT",		NULL,	GLFW_KEY_RIGHT_SHIFT },
		{"RIGHTCONTROL",		NULL,	GLFW_KEY_RIGHT_CONTROL },
		{"RIGHTALT",		NULL,	GLFW_KEY_RIGHT_ALT },
		{"RIGHTSUPER",		NULL,	GLFW_KEY_RIGHT_SUPER },
		{"MENU",		NULL, GLFW_KEY_MENU },
		{"LASTKEY",		NULL, GLFW_KEY_LAST },
	};

	const int GetKeyNumForName(const string& name)
	{
		keyname_t* kn;
		string searchName = name;
		transform(searchName.begin(), searchName.end(), searchName.begin(), toupper);
		for (kn = keynames; kn->name != NULL; kn++)
		{
			if (searchName.compare(kn->name) == 0)
				return kn->keynum;
		}

		return kn->keynum;
	}

	const string GetKeyNameForNum(const int& keynum)
	{
		keyname_t* kn;

		for (kn = keynames; kn->name != NULL; kn++)
		{
			if (keynum == kn->keynum)
			{
				return kn->name;
			}
		}

		return kn->name;
	}

	const usercmdButton_t& GetButtonForName(const string& name)
	{
		userCmdString_t* cmd;
		string searchName = name;
		transform(searchName.begin(), searchName.end(), searchName.begin(), tolower);
		for (cmd = userCmdStrings; cmd->string != NULL; cmd++)
		{
			if (searchName.compare(cmd->string) == 0)
			{
				return cmd->button;
			}
		}

		return cmd->button;
	}

	const string GetNameForButton(const usercmdButton_t& button)
	{
		userCmdString_t* cmd;

		for (cmd = userCmdStrings; cmd->string != NULL; cmd++)
		{
			if (cmd->button == button)
			{
				return cmd->string;
			}
		}

		return NULL;
	}
}