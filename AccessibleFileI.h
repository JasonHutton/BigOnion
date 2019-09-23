#pragma once

class AccessibleFileI
{
public:
	virtual ~AccessibleFileI() {}

	// File IO functions...
	virtual bool Read() = 0; // Reads file into internally implemented data member.
	virtual bool Write(const bool overwrite = true) const = 0; // Writes internally implemented data member to file.

	// Data functions...
	// virtual void GetData() const = 0; // Classes are responsible for their own data members and their accessors, since they can be of different types.
	// virtual void SetData(const void& data); const = 0; // Classes are responsible for their own data members and their accessors, since they can be of different types.
	virtual void ClearData() = 0; // Clears loaded data from file, but retains the other data about the file. Since this doesn't expose an internal type, this will be defined in the interface.
};