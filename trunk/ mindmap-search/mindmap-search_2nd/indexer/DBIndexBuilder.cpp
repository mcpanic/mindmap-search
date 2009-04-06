#include "stdAfx.h"
#include "DBIndexBuilder.h"
#include "CppSQLite3.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>

#pragma warning(disable:4996)

using namespace std;

DBIndexBuilder::DBIndexBuilder()
{
}

DBIndexBuilder::~DBIndexBuilder()
{
}

void DBIndexBuilder::Release()
{
	delete this;
}

bool DBIndexBuilder::OpenDB()
{ 
    m_dbMindmap.open(m_szDBFilename.c_str()); // DB open
 
	return true;
}

bool DBIndexBuilder::CloseDB() // // DB close
{ 
	m_dbMindmap.close();
	return true;
}

// insert DB
bool DBIndexBuilder::insertIndexDB(string s_Word, string szFilename, vector<DBIndexEntity> &a_vNodes)
{
	string szCommand;

	if (!m_dbMindmap.tableExists("IndexDB"))
	{
		cout << endl << "IndexDB doesn't exist. Creating IndexDB table" << endl;
		AddIndexDBTable();
	}

	if (a_vNodes.size() < 1)
	{
		printf("size lacking.");
		return false;
	}

	char szTemp[1024] = {0,};
	char sQuery[1024] = {0,};

	CppSQLite3Query qry;
	
	std::vector<int> vecIndexID;
	std::vector<DBIndexEntity>::iterator it = a_vNodes.begin(); 
	for (; it != a_vNodes.end(); ++it)
	{
		sprintf(sQuery, _T("select indexID from Dictionary where Word = '%s';"), s_Word.c_str());

		try
		{
			qry = m_dbMindmap.execQuery(sQuery);
		}
		catch (CppSQLite3Exception &ex)
		{
			printf("Query문에 문제(%s)가 발생하여 프로그램을 종료합니다.(1)", ex.errorMessage());
			abort();
		}
		
		if (true == qry.eof())
			continue;
	
		else {				
			sprintf(szTemp, _T("insert into IndexDB(IndexID, FileName, weight) values ((SELECT IndexID FROM Dictionary where word = '%s'), '%s', 0);"), s_Word.c_str(), szFilename.c_str());
			try
			{
				m_dbMindmap.execQuery(szTemp);
			}
			catch (CppSQLite3Exception &ex)
			{
				printf("Query문에 문제(%s)가 발생하여 프로그램을 종료합니다.(2)\n", ex.errorMessage());
				abort();
			}
			break;
		}
	}
	return true;
}

bool DBIndexBuilder::insertDictionary(string s_Word, vector<DBIndexEntity> &a_vNodes)
{
	string szCommand;
	int nField = 0;

	if (!m_dbMindmap.tableExists("Dictionary"))
	{
		cout << endl << "Dictionary doesn't exist. Creating Dictionary table" << endl;
		AddDictionaryTable();
	}

	if (a_vNodes.size() < 1)
	{
		printf("Size Error!.");
		return false;
	}

	char szTemp[1024] = {0,};
	char sQuery[1024] = {0,};

	CppSQLite3Query qry;
	
	std::vector<int> vecIndexID;
	std::vector<DBIndexEntity>::iterator it = a_vNodes.begin(); 
	for (; it != a_vNodes.end(); ++it)
	{
		sprintf(sQuery, _T("select indexID from Dictionary where Word = '%s';"), s_Word);
	
		try
		{
			qry = m_dbMindmap.execQuery(sQuery);
		}
		catch (CppSQLite3Exception &ex)
		{
			printf("Query문에 문제(%s)가 발생하여 프로그램을 종료합니다.(1)", ex.errorMessage());
			abort();
		}
		
		if (true != qry.eof())
			continue;	

		else
		{
			sprintf(szTemp, _T("insert into Dictionary(indexID, Word) values ((SELECT max(indexID) FROM Dictionary)+1, '%s');"), s_Word.c_str());
	
			try
			{
				m_dbMindmap.execQuery(szTemp);
			}
			catch (CppSQLite3Exception &ex)
			{
				printf("Query문에 문제(%s)가 발생하여 프로그램을 종료합니다.(2)", ex.errorMessage());
				abort();
			}
			break;
		}
	}
	
	return true;
}

bool DBIndexBuilder::AddIndexDBTable()			
{
	if (m_dbMindmap.tableExists("IndexDB"))
	{
		return false;
	}

	if (ExecCommand("create table IndexDB(IndexID integer PRIMARY KEY, FileName TEXT, weight integer)"))
		return true;
	else
		return false;
}

bool DBIndexBuilder::AddDictionaryTable()			
{
	if (m_dbMindmap.tableExists("Dictionary"))
	{
		return false;
	}

	if (ExecCommand("create table Dictionary(IndexID integer PRIMARY KEY, word TEXT)"))
		return true;
	else
		return false;
}

int DBIndexBuilder::ExecCommand(char* a_szCommand)
{ 
	int nResult = 0;

	try
	{
		nResult = m_dbMindmap.execDML(a_szCommand); //a_szCommand.c_str();
    }
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
		return -1;
    }
	return nResult;
}

void DBIndexBuilder::SetDBName(string a_szDBFilename)
{
	m_szDBFilename = a_szDBFilename;
}