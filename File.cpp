#include "File.h"

File::File(const string& iFile, const string& explicitPath)
{
	Init(iFile, explicitPath);
}

void File::Init(const string& iFile, const string& explicitPath)
{
	m_iFile = iFile;


	if (!explicitPath.empty())
	{
		FileSystem::BuildOSPath(explicitPath, m_iFile, m_osPath);
	}
	else
	{
		try
		{
			FileSystem::BuildOSPath(FileSystem::FindFile(iFile), m_iFile, m_osPath);
		}
		catch (exception ex)
		{
			// We're going to crash now, most likely. File not found.
		}
	}
}

const string& File::GetIFile() const
{
	return m_iFile;
}

const string& File::GetOSPath() const
{
	return m_osPath;
}