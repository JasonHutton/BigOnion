#include "ContextControl.h"
#include <algorithm>

void ContextControl::SetControl(const usercmdButton_t& control, const string& context)
{
	this->m_controlContexts[context] = control;
}

const usercmdButton_t ContextControl::GetControl(const string& context) const
{
	map<string, usercmdButton_t>::const_iterator it = this->m_controlContexts.find(context);
	if (it != this->m_controlContexts.end())
		return it->second;
	else
		return UB_NONE;
}

vector<string>& ContextControl::GetContexts(vector<string>& contexts) const
{
	for (map<string, usercmdButton_t>::const_iterator it = this->m_controlContexts.begin(); it != this->m_controlContexts.end(); it++)
	{
		if (find(contexts.begin(), contexts.end(), it->first) == contexts.end())
		{
			contexts.push_back(it->first);
		}
	}
	return contexts;
}

const bool ContextControl::UnSetControl(const string& context)
{
	map<string, usercmdButton_t>::const_iterator it = this->m_controlContexts.find(context);
	if (it != this->m_controlContexts.end())
	{
		this->m_controlContexts.erase(it);
		return true;
	}

	return false;
}

void ContextControl::UnSetAllControls()
{
	this->m_controlContexts.clear();
}

const bool ContextControl::IsSet() const
{
	return !this->m_controlContexts.empty();
}