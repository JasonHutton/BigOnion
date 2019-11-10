#pragma once

#include "File.h"
#include "AccessibleFileI.h"
#include <vector>

class TextFile : public File, AccessibleFileI
{
public:
	TextFile(const string& iFile = "", const string& explicitPath = "") : File(iFile, explicitPath) {};

public:
	virtual bool Read();
	virtual bool Write(const bool overwrite = true) const;

	const vector<string>& GetData() const;
	const char* c_str();
	void SetData(const vector<string>& data);
	void SetData(const string& data);
	virtual void ClearData();
	vector<string>& AccessData(); // Read-write accessor...

private:
	vector<string> m_data;
	char* m_data_c;
};