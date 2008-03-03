#pragma once
#include "DBBuilder.h"

//#include <sqlite3.h>
#include "CppSQLite3.h"

class SQLiteDBBuilder: public IDBBuilder
{
public:
	SQLiteDBBuilder();
	virtual ~SQLiteDBBuilder();

// Release function
	void Release();

// DB functions
	bool OpenDB();
	bool CloseDB();

// Table functions
	bool AddTable();
	bool DeleteTable();

// Entry functions
	bool AddEntry();
	bool UpdateEntry();
	bool DeleteEntry();

// Manually execute commands
	bool ExecCommand();
};
