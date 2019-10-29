#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include "../src/engine/utils/utils.h"

using std::string;
using std::vector;
using std::transform;

class Command
{
public:
	Command(const string& command = "");

	const string& GetCommand() const;
	const vector<string>& GetTokens() const;
protected:
	void Init(const string& command);
protected:
	string m_command;
	vector<string> m_tokens;
};
