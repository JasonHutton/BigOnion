#pragma once

#include <string>
#include <map>
#include <vector>
#include "KeyInput.h"

using namespace std;
using namespace KeyInput;

class ContextControl
{
public:
	void SetControl(const usercmdButton_t& control, const string& context = "");
	const usercmdButton_t GetControl(const string& context = "") const;
	vector<string>& GetContexts(vector<string>& contexts) const;
	const bool UnSetControl(const string& context = "");
	void UnSetAllControls();
	const bool IsSet() const;

private:
	map<string, usercmdButton_t> m_controlContexts;
};
