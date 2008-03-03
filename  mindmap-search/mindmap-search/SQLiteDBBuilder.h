#pragma once
#include "DBBuilder.h"

//#include <sqlite3.h>
#include "CppSQLite3.h"

using namespace std;

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

// Specified table functions
	bool AddTextDBTable();
	bool AddNodeDBTable();

// Entry functions
	bool AddEntry();
	bool UpdateEntry();
	bool DeleteEntry();

// Manually execute commands
	int ExecCommand(string a_szCommand);

// Add entry to specified DB
	bool AddToNodeDB(string a_szDBFilename, DBEntry &a_vNodes);
	bool AddToTextDB(string a_szDBFilename, DBEntry &a_vNodes);

// Set the DB file name
	void SetDBName(string a_szDBFilename);

private:
	CppSQLite3DB db;
	string m_szDBFilename;

};
