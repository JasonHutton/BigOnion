#include "Command.h"

Command::Command(const string& command)
{
	Init(command);
}

const string& Command::GetCommand() const
{
	return m_command;
}

const vector<string>& Command::GetTokens() const
{
	return m_tokens;
}

void Command::Init(const string& command)
{
	m_command = command;
	Utils::Tokenize(m_command, m_tokens);
}

