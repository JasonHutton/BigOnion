#pragma once

#include <fstream>
#include <string>
#include <iostream>

#include "FileSystem.h"

using namespace std;

// Need to somehow add support for variable paths to this.

class File
{
public:
	File(const string& iFile = "", const string& explicitPath = "");

protected:
	virtual void Init(const string& iFile, const string& explicitPath);

public:
	const string& GetIFile() const;
	const string& GetOSPath() const;

private:
	string m_iFile; // The internal path to the file.
	string m_osPath; // OS path. The path the OS is actually going to be seeing.
};

namespace FileSystem
{
	bool PathExists(const string& path, const bool& bUseSearchPaths = true);
	bool CreatePath(const string& path, const bool& bUseHomePath = true);
	void ListFilesInPath(vector<File>& files, const string& path, const string& filter = "*"); // Recursive search, using a specific path.
}