#pragma once
#include <string>
#include <vector>
class DBIndexEntity;

__interface IDBIndex
{
public:
	virtual void Release() = 0;

// DB functions
	virtual bool OpenDB() = 0;
	virtual bool CloseDB() = 0;

// Insert DB
	virtual bool insertDictionary(std::string s_Word, std::vector<DBIndexEntity> &vNodes) = 0;
	virtual bool insertIndexDB(std::string s_Word, std::string szFilename, std::vector<DBIndexEntity> &vNodes) = 0;

// Specified table functions
	virtual bool AddIndexDBTable() = 0;	// indexDB table 초기화
	virtual bool AddDictionaryTable() = 0;	// dictionary table 초기화

// Manually execute commands
	virtual int ExecCommand(char* a_szCommand) = 0;

// Set the DB file name
	virtual void SetDBName(std::string a_szDBFilename);

};