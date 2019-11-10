#include "TextFile.h"
#include <sstream>

bool TextFile::Read()
{
	bool bReadSuccess = false;

	ifstream file;
	file.open(this->GetOSPath(), ios::in);
	if (file.is_open())
	{
		string temp;
		while (getline(file, temp))
		{
			m_data.push_back(temp);
			bReadSuccess = true;
		}
		if (file.bad())
		{
			// We had a problem.
		}
		file.close();
	}
	return bReadSuccess;
}

bool TextFile::Write(const bool overwrite) const
{
	bool bWriteSuccess = false;

	string osPath;
	FileSystem::BuildOSPath(FileSystem::GetHomePath(), this->GetIFile(), osPath);

	if (!overwrite)
	{
		ifstream chkFile;

		chkFile.open(osPath, std::ios_base::in);
		if (chkFile.is_open())
		{
			chkFile.close();
			return false;
		}
	}

	ofstream file;
	file.open(osPath, ios::out);
	if (file.is_open())
	{
		vector<string>::const_iterator it;
		for (it = m_data.begin(); it != m_data.end(); it++)
		{
			file << *it;
			bWriteSuccess = true;
		}
		if (file.bad())
		{
			// We had a problem.
		}
		file.close();
	}
	return bWriteSuccess;
}

const vector<string>& TextFile::GetData() const
{
	return m_data;
}

const char* TextFile::c_str()
{
	if(m_data_c != NULL)
		free(m_data_c);

	int dataSize = 0;
	vector<string>::const_iterator it;
	for (it = m_data.begin(); it != m_data.end(); it++)
	{
		dataSize += sizeof(char) * (it->length() + 1);
	}
	dataSize += sizeof(char) * m_data.size(); // Allocate space for newlines as well.
	m_data_c = static_cast<char*>(malloc(dataSize));
	m_data_c[0] = '\0'; // Ensure there's a null terminator at the end of the (blank) string in the allocated memory.

	int numWritten = 0;
	for (it = m_data.begin(); it != m_data.end(); it++)
	{
		if (strncat_s(m_data_c, dataSize, it->c_str(), (sizeof(char) * it->length() + 1)) != 0)
		{
			// Do some error handling...
		}
		strncat_s(m_data_c, dataSize, "\n", 1 * sizeof(char));
	}

	return m_data_c;
}

void TextFile::SetData(const vector<string>& data)
{
	m_data = data;
}

void TextFile::SetData(const string& data)
{
	m_data.clear();

	istringstream iss(data);
	string line;
	while (std::getline(iss, line))
	{
		m_data.push_back(line + "\n");
	}
}

void TextFile::ClearData()
{
	m_data.clear();
}

