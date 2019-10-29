#include "Setting.h"


Setting* Setting::first = NULL;
Setting* Setting::last = NULL;

Setting::Setting(const string& name, const string& description, const string& defaultValue, const string& value)
{
	Init(name, description, defaultValue, value);
}

void Setting::Init(const string& name, const string& description, const string& defaultValue, const string& value)
{
	this->m_name = name;
	this->m_description = description;
	this->m_defaultValue = defaultValue;
	this->m_value = value;

	if (value.empty() || value.compare("") == 0)
		this->Reset();

	if (Setting::last != NULL)
	{
		this->prev = Setting::last;
		this->prev->next = this;
	}
	else
	{
		this->prev = NULL;
		this->next = NULL;
	}

	if (Setting::first == NULL)
		Setting::first = this;

	Setting::last = this;
}

const string& Setting::Name() const
{
	return this->m_name;
}

const string& Setting::Description() const
{
	return this->m_description;
}

void Setting::Reset()
{
	this->m_value = this->m_defaultValue;
}

void Setting::Set(const string& value)
{
	this->m_value = value;
}

void Setting::Set(const int& value)
{
	stringstream ss;
	ss << value;
	this->m_value = ss.str();
}

const string& Setting::GetString() const
{
	return this->m_value;
}

const int Setting::GetInteger() const
{
	return atoi(this->m_value.c_str());
}

const double Setting::GetDouble() const
{
	return atof(this->m_value.c_str());
}

const bool Setting::GetBool() const
{
	return atoi(this->m_value.c_str()) != 0 ? true : false;
}

Setting* Setting::Prev()
{
	return this->prev;
}

Setting* Setting::Next()
{
	return this->next;
}

Setting* Setting::First()
{
	return Setting::first;
}

Setting* Setting::Last()
{
	return Setting::last;
}