#pragma once
#include "DBIndex.h"
#include "DBIndexEntity.h"

//#include <sqlite3.h>
#include "CppSQLite3.h"

using namespace std;

class DBIndexBuilder: public IDBIndex
{
public: 
	DBIndexBuilder();
	virtual ~DBIndexBuilder();

// Release function
	void Release();

// DB functions
	bool OpenDB();
	bool CloseDB();

// insertDB
	bool insertDictionary(string s_Word, std::vector<DBIndexEntity> &a_vNodes);
	bool insertIndexDB(string s_Word, string szFilename, std::vector<DBIndexEntity> &a_vNodes);

// create Index
	bool AddIndexDBTable();
	bool AddDictionaryTable();

// Manually execute commands
	int ExecCommand(char* a_szCommand);

// Set the DB file name
	void SetDBName(string a_szDBFilename);

private:
	CppSQLite3DB m_dbMindmap;	// sqlite�� ������ db��ü �̸�- 'db' SQLiteDBBuilder.cpp���� ����
	string m_szDBFilename;  // ���� DB file�̸� ; mindmapSearch.cpp���� ���������
};