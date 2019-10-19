#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

class Setting
{
public:
	/// <summary> Create a setting to store configuration information. </summary>
	/// <param="name"> The name of the setting. Referenced in files. Unique. </param>
	/// <param="description"> A helpful description of the setting. </param>
	/// <param="defaultValue"> The default value of the setting. Constant. </param>
	/// <param="value"> The set value of the setting. Variable. </param>
	Setting(const string& name = "", const string& description = "", const string& defaultValue = "", const string& value = "");
	const string& Name() const;
	const string& Description() const;

	void Init(const string& name, const string& description, const string& defaultValue, const string& value);

	/// <summary> Reset the current value of the setting to the default value. </summary>
	void Reset();

	/// <summary> Set the current value of the setting. </summary>
	/// <param="value"> The value to change to. </param>
	void Set(const string& value);
	void Set(const int& value);

	const string& GetString() const;
	const int GetInteger() const;
	const double GetDouble() const;
	const bool GetBool() const;

public:
	Setting* Prev();
	Setting* Next();

	static Setting* First();
	static Setting* Last();

private:
	string m_name;
	string m_description;
	string m_defaultValue;
	string m_value;

	Setting* prev;
	Setting* next;

	static Setting* first;
	static Setting* last;
};

namespace Settings
{
	/// <summary> Loads the values for all currently registered settings from a file. </summary>
	/// <param="filename"> Filename to load the settings from. </param>
	/// <remark> Need a LOT more error checking here. </remark>
	void LoadSettings(const char* filename);
	void LoadSettingsFromData(const vector<string>& data);

	/// <summary> Saves the values for all currently registered settings to a file. </summary>
	/// <param="filename"> Filename to save the settings to. </param>
	/// <param="overwrite"> Should an existing file be overwritten? (False for writing defaults at first load.) </param>
	void SaveSettings(const char* filename, bool overwrite = true);
	const vector<string> SaveSettingsToData();
}