#pragma once

#include <string>
#include <vector>

#include "Vector3.h"

namespace Utils
{
	const std::string& StripLeadingWhitespace(std::string& str);
	const std::string& StripTrailingWhitespace(std::string& str);
	const std::string& StripLeadingAndTrailingWhitespace(std::string& str);
	const std::string& StripAllWhitespace(std::string& str);
	const std::string& StripComments(std::string& str);
	const std::vector<std::string>& Tokenize(const std::string& input, std::vector<std::string>& tokens, const std::string& deliminators = " \t");
}