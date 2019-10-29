#include "src/engine/utils/utils.h"
#include <algorithm>

const std::string& Utils::StripLeadingWhitespace(std::string& str)
{
	str.erase(str.begin(), find_if(str.begin(), str.end(), isgraph));

	return str;
}

const std::string& Utils::StripTrailingWhitespace(std::string& str)
{
	str.erase(std::find_if(str.rbegin(), str.rend(), isgraph).base(), str.end());

	return str;
}

const std::string& Utils::StripLeadingAndTrailingWhitespace(std::string& str)
{
	StripLeadingWhitespace(str);
	StripTrailingWhitespace(str);

	return str;
}

const std::string& Utils::StripAllWhitespace(std::string& str)
{
	std::string temp;
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		if (!isspace(*it))
			temp += *it; // Just omit all whitespace and return the results;
	}
	str = temp;
	return str;
}

const std::string& Utils::StripComments(std::string& str)
{
	size_t commentBeginPos = str.find("//");
	if (commentBeginPos != std::string::npos)
	{
		str = str.substr(0, commentBeginPos);
	}

	return str;
}

const std::vector<std::string>& Utils::Tokenize(const std::string& input, std::vector<std::string>& tokens, const std::string& deliminators)
{
	std::string::size_type lastPos = input.find_first_not_of(deliminators);
	std::string::size_type pos = input.find_first_of(deliminators, lastPos);

	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		tokens.push_back(input.substr(lastPos, pos - lastPos));
		lastPos = input.find_first_not_of(deliminators, pos);
		pos = input.find_first_of(deliminators, lastPos);
	}

	return tokens;
}