#pragma once

#include "Command.h"
#include "src/engine/utils/utils.h"
#include "Setting.h"
#include "src/engine/input/InputHandler.h"

namespace CommandSystem
{
	void DoCommand(const Command& command);
	void AttachInput(InputHandler* input);
	vector<string> SettingsToCommandList(vector<string>& commandList);
	vector<string> BindingsToCommandList(vector<string>& commandList);

	namespace detail
	{
		extern InputHandler* m_input;
	}
}