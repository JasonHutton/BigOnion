#include "FileSystem.h"


string FileSystem::detail::m_basePath;
string FileSystem::detail::m_homePath;


void FileSystem::Init(const string& fs_basePath, const string& fs_homePath)
{
	string iBasePath;
	string iHomePath;

	if (fs_basePath.empty())
		iBasePath = ".";
	else
		iBasePath = fs_basePath;

	if (fs_homePath.empty())
		iHomePath = iBasePath;
	else
		iHomePath = fs_homePath;

	// If the homepath doesn't exist, create it. This probably needs some recursion added to handle multiple subdirectories.
	if (!PathExists(iHomePath, false))
	{
		if (!CreatePath(iHomePath, false))
		{
			iHomePath = iBasePath; // If we can't create it, set HomePath to BasePath.
		}
	}

	FileSystem::SetBasePath(iBasePath);
	FileSystem::SetHomePath(iHomePath);
}

const string& FileSystem::GetBasePath()
{
	return FileSystem::detail::m_basePath;
}

const string& FileSystem::GetHomePath()
{
	return FileSystem::detail::m_homePath;
}

void FileSystem::SetBasePath(string& path)
{
	if (!detail::m_basePath.empty())
	{
		return;
	}
	FileSystem::detail::m_basePath = ReplaceSeparators(path);
}

void FileSystem::SetHomePath(string& path)
{
	FileSystem::detail::m_homePath = ReplaceSeparators(path);
}

const string& FileSystem::BuildOSPath(const string& searchPath, const string& iFile, string& osPath)
{
	osPath = searchPath;
	if (osPath[osPath.length() - 1] != '/')
		osPath += "/";
	osPath += iFile;

	ReplaceSeparators(osPath);

	return osPath;
}

bool FileSystem::FileExists(const string& iFile, const bool bUseSearchPaths)
{
	if (FileExistsInPath(detail::m_homePath, iFile))
		return true;

	if (!bUseSearchPaths)
		return false; // Cut off here if we're not searching further.

	if (FileExistsInPath(detail::m_basePath, iFile))
		return true;

	return false;
}

const string& FileSystem::FindFile(const string& iFile)
{
	if (FileExistsInPath(detail::m_homePath.c_str(), iFile.c_str()))
		return detail::m_homePath;

	if (FileExistsInPath(detail::m_basePath.c_str(), iFile.c_str()))
		return detail::m_basePath;

	throw exception("File not found.");
}

bool FileSystem::FileExistsInPath(const string& path, const string& iFile)
{
	string sPath = path;
	string sIFile = iFile;
	ReplaceSeparators(sPath);
	ReplaceSeparators(sIFile);

	string checkPath;
	BuildOSPath(sPath, sIFile, checkPath);

	ifstream file;
	file.open(checkPath);
	if (file.is_open())
	{
		file.close();
		return true;
	}

	return false;
}

bool FileSystem::PathExists(const string& path, const bool& bUseHomePath)
{
	string sanitizedPath = path;
	ReplaceSeparators(sanitizedPath);
	if (bUseHomePath)
	{
		string osPath;
		BuildOSPath(detail::m_homePath, sanitizedPath, osPath);
		sanitizedPath = osPath;
	}

	if (GetFileAttributes(sanitizedPath.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}

	return true;
}

bool FileSystem::CreatePath(const string& path, const bool& bUseHomePath)
{
	string sanitizedPath = path;
	ReplaceSeparators(sanitizedPath);
	if (bUseHomePath)
	{
		string osPath;
		BuildOSPath(detail::m_homePath, sanitizedPath, osPath);
		sanitizedPath = osPath;
	}

	if (CreateDirectory(sanitizedPath.c_str(), NULL))
	{
		return true;
	}

	return false;
}

void FileSystem::ListFilesInPath(vector<File>& files, const string& path, const string& filter)
{
	string sanitizedPath = path;

	ReplaceSeparators(sanitizedPath);
	if (sanitizedPath[sanitizedPath.length() - 1] != '/')
		sanitizedPath += "/";

	string filteredPath = sanitizedPath;
	filteredPath += filter;

	WIN32_FIND_DATA foundFiles;
	HANDLE searchHandle = FindFirstFile(sanitizedPath.c_str(), &foundFiles);
	if (searchHandle != INVALID_HANDLE_VALUE)
	{
		do
		{
			string filename = foundFiles.cFileName;

			if (filename.compare(".") != 0 && filename.compare("..") != 0)
			{
				File file(filename, sanitizedPath.c_str());
				files.push_back(file);

				if (foundFiles.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					if (filename.compare(".") != 0 && filename.compare("..") != 0)
					{
						string newPath = sanitizedPath;
						newPath += filename;
						newPath += "/";

						FileSystem::ListFilesInPath(files, newPath.c_str(), filter);
					}
				}
			}
		} while (FindNextFile(searchHandle, &foundFiles));

		FindClose(searchHandle);
	}
}

const string& FileSystem::ReplaceSeparators(string& path)
{
	for (string::iterator it = path.begin(); it != path.end(); it++)
	{
		if (*it == '\\')
			* it = '/';
	}

	return path;
}

/*bool FileSystem::FileRead(const char* iFile, File& file) const
{

}*/

const string FileSystem::GetNextFilename(const string& baseFilename, const string& extension, const unsigned int& paddingDigits, const char& fillChar)
{
	ostringstream nextFilename;

	for (unsigned int incrementCount = 0; incrementCount < UINT_MAX; incrementCount++)
	{
		ostringstream tempFilename;
		if (paddingDigits > 0)
		{
			tempFilename << baseFilename << setw(paddingDigits) << setfill(fillChar) << incrementCount << extension;
		}
		else
		{
			if (incrementCount > 0)
			{
				tempFilename << baseFilename << incrementCount << extension;
			}
			else
			{
				tempFilename << baseFilename << extension;
			}
		}
		tempFilename << '\0';
		if (!FileSystem::FileExists(tempFilename.str(), true))
		{
			nextFilename << tempFilename.str();
			break;
		}
	}

	return nextFilename.str();
}