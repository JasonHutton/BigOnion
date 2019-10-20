#include "CommandSystem.h"
#include "GLFW//glfw3.h"

InputHandler* CommandSystem::detail::m_input = NULL;

void CommandSystem::DoCommand(const Command& command)
{
	vector<string> tokens = command.GetTokens();
	size_t numTokens = tokens.size();

	if (tokens[0].compare("set") == 0 && numTokens >= 3)
	{
		bool bFoundSetting = false;
		Setting* setting = Setting::First();
		while (setting != NULL)
		{
			string sname = setting->Name();
			transform(sname.begin(), sname.end(), sname.begin(), tolower);
			transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(), tolower);
			if (sname.compare(tokens[1]) == 0)
			{
				bFoundSetting = true;
				setting->Set(tokens[2]);
			}
			setting = setting->Next();
		}
		if (!bFoundSetting)
		{
			cout << "ERROR: Setting variable not found: " << tokens[1] << endl;
		}
	}
	else if (tokens[0].compare("bind") == 0 && numTokens >= 3)
	{
		transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(), toupper); // Key to upper
		transform(tokens[2].begin(), tokens[2].end(), tokens[2].begin(), tolower); // Control to lower
		if (numTokens >= 4)
		{
			transform(tokens[3].begin(), tokens[3].end(), tokens[3].begin(), tolower); // Context to lower
		}

		int key;
		usercmdButton_t button;

		try
		{
			key = GetKeyNumForName(tokens[1]);
			button = GetButtonForName(tokens[2]);
		}
		catch (std::runtime_error ex)
		{
			cout << "ERROR: " << ex.what() << endl;
			return;
		}

		if (numTokens >= 4)
		{
			detail::m_input->Bind(key, button, tokens[3]);
		}
		else
		{
			detail::m_input->Bind(key, button);
		}
	}
	else if (tokens[0].compare("unbindall") == 0 && numTokens == 1)
	{
		detail::m_input->UnBindAll();
	}
	else
	{
		cout << "ERROR: Unrecognized command: " << tokens[0] << endl;
		return;
	}
}

void CommandSystem::AttachInput(InputHandler* input)
{
	detail::m_input = input;
}

vector<string> CommandSystem::SettingsToCommandList(vector<string>& commandList)
{
	Setting* setting = Setting::First();

	while (setting != NULL)
	{
		string os;
		os += "set " + setting->Name() + " " + setting->GetString() + "\n";
		commandList.push_back(os);

		setting = setting->Next();
	}

	return commandList;
}

vector<string> CommandSystem::BindingsToCommandList(vector<string>& commandList)
{
	std::map<int, keyState>& keys = detail::m_input->GetAllKeyStates();
	for (map<int, keyState>::iterator itk = keys.begin(); itk != keys.end(); itk++)
	{
		ContextControl control = detail::m_input->GetControl(itk->first);
		if (control.IsSet())
		{
			vector<string> contexts;
			control.GetContexts(contexts);
			for (vector<string>::const_iterator it = contexts.begin(); it != contexts.end(); it++)
			{
				string os;
				try
				{
					os += "bind " + GetKeyNameForNum(itk->first) + " " + GetNameForButton(control.GetControl(*it));
				}
				catch (std::runtime_error ex)
				{
					cout << "ERROR: " << ex.what() << endl;
				}
				if (!it->empty())
					os += " " + *it;
				os += "\n";

				commandList.push_back(os);
			}
		}
	}

	return commandList;
}