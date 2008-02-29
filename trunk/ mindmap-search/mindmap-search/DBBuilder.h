#pragma once

__interface IDBBuilder
{
public:
	virtual void Release();

// DB functions
	virtual bool OpenDB();
	virtual bool CloseDB();

// Table functions
	virtual bool AddTable();
	virtual bool DeleteTable();

// Entry functions
	virtual bool AddEntry();
	virtual bool UpdateEntry();
	virtual bool DeleteEntry();

// Manually execute commands
	virtual bool ExecCommand();
};