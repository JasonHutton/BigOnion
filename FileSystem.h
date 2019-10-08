#pragma once

#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <exception>
#include <sstream>
#include <iomanip>
#include <Windows.h>
#include "File.h"

using namespace std;

// osPath = OS path to search through or build from other paths. The OS deals in these.
// searchPath = An osPath that the FileSystem is allowed to search and manipulate. These are set in the file system, and shouldn't be arbitrarily passed.
// iPath or iFile = The Internal Path or an Internal File. This is the path within the application's file system. It should be constant regardless of installation path, and should only care about paths within the game directory. It gets appended to an osPath(searchPath).
// FOR FUTURE USE, NOT CURRENTLY USED: gamePath = The subdirectory the game's files exist under. There can be more than one of these, which should be searched in latest->earliest loading order to allow for hiearchial overrides of data. Basically mod directories.


namespace FileSystem
{
	void Init(const string& fs_basePath = "", const string& fs_homePath = "");

	const string& GetBasePath();
	void SetBasePath(string& path);

	const string& GetHomePath();
	void SetHomePath(string& path);

	const string& BuildOSPath(const string& searchPath, const string& iFile, string& osPath); // Build an osPath from a searchPath and an iPath.
	bool FileExists(const string& iFile, const bool bUseSearchPaths); // Looks for a particular file in the iPath root. Check homepath first. If bSearch is true, continue looking if not found there.
	const string& FindFile(const string& iFile); // Goes looking for an iFile, and returns the searchPath it exists and is found in.

	bool FileExistsInPath(const string& path, const string& iFile); // Looks for a particular file in a particular path.

	const string& ReplaceSeparators(string& path); // Make sure all path separators are the same.

	//bool FileRead(const char* iFile, File& file) const; // Attempts to find and read a file, in the iPath. This will take the first file found.
	namespace detail
	{
		extern string m_basePath; // Generally ".", but can be remapped to anything. Holds the main game content, and usually(But not always.) the executable. This is only set once.
		extern string m_homePath; // Where we can write files. Also search for game content here, as it may be installed here by non-admin users.
	}

	const string GetNextFilename(const string& baseFilename, const string& extension, const unsigned int& paddingDigits = 0, const char& fillChar = '0');
}
