#pragma once
#include <string>

__interface IDBBuilder
{
public:
	virtual void Release() = 0;

// DB functions
	virtual bool OpenDB() = 0;
	virtual bool CloseDB() = 0;

// Table functions
	virtual bool AddTable() = 0;
	virtual bool DeleteTable() = 0;

// Specified table functions
	virtual bool AddTextDBTable() = 0;
	virtual bool AddNodeDBTable() = 0;

// Entry functions
	virtual bool AddEntry() = 0;
	virtual bool UpdateEntry() = 0;
	virtual bool DeleteEntry() = 0;

// Manually execute commands
	virtual int ExecCommand(std::string a_szCommand) = 0;

// Add entry to specified DB
	virtual bool AddToNodeDB(std::string a_szDBFilename, class DBEntry &) = 0;
	virtual bool AddToTextDB(std::string a_szDBFilename, class DBEntry &) = 0;

// Set the DB file name
	virtual void SetDBName(std::string a_szDBFilename);
};