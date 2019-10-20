#pragma once

#include <string>
#include <vector>

using namespace std;

namespace KeyInput
{
	enum usercmdButton_t
	{
		UB_NONE,

		UB_FORCE_QUIT,

		UB_MOVE_FORWARD,
		UB_MOVE_BACKWARD,
		UB_MOVE_LEFT,
		UB_MOVE_RIGHT,

		UB_MAX_BUTTONS
	};

	struct userCmdString_t
	{
		const char* string;
		usercmdButton_t	button;
	};

	struct keyname_t {
		const char* name;
		const char* printable;
		int		keynum;
	};
}

namespace KeyInput
{
	const int GetKeyNumForName(const string& name);
	const usercmdButton_t& GetButtonForName(const string& name);
	const string GetKeyNameForNum(const int& keynum);
	const string GetNameForButton(const usercmdButton_t& button);
}