#include "StdAfx.h"
#include "SQLiteDBBuilder.h"
#include <iostream>
#include <ctime>
#include "DBEntry.h"

using namespace std;


SQLiteDBBuilder::SQLiteDBBuilder()
{
}

SQLiteDBBuilder::~SQLiteDBBuilder()
{
}

void SQLiteDBBuilder::Release()
{
	delete this;
}

// DB functions
bool SQLiteDBBuilder::OpenDB()
{ 
    db.open(m_szDBFilename.c_str());
 
	return true;
}

bool SQLiteDBBuilder::CloseDB()
{ 
	db.close();
	return true;
}

// Table functions
bool SQLiteDBBuilder::AddTable()
{ 
	return true;
}

bool SQLiteDBBuilder::DeleteTable()
{ 
	return true;
}

// Specified table functions
bool SQLiteDBBuilder::AddTextDBTable()
{
	if (ExecCommand("create table textDB(token text, nodeID text, weight integer, tag text, position integer)"))
		return true;
	else
		return false;
}

bool SQLiteDBBuilder::AddNodeDBTable()
{
	if (ExecCommand("create table nodeDB(nodeID text, timeCre text, timeMod text, parentNodeID text)"))
		return true;
	else
		return false;
}


// Entry functions
bool SQLiteDBBuilder::AddEntry()
{ 
	return true;
}

bool SQLiteDBBuilder::UpdateEntry()
{ 
	return true;
}

bool SQLiteDBBuilder::DeleteEntry()
{ 
	return true;
}

// Manually execute commands
int SQLiteDBBuilder::ExecCommand(string a_szCommand)
{ 
	int nResult = 0;

	try
	{
		nResult = db.execDML(a_szCommand.c_str());
    }
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
		return -1;
    }
	return nResult;
}

void SQLiteDBBuilder::SetDBName(string a_szDBFilename)
{
	m_szDBFilename = a_szDBFilename;
}

bool SQLiteDBBuilder::AddToNodeDB(string a_szDBFilename, DBEntry &a_vNodes)
{
   // time_t tmStart, tmEnd;

	string szCommand;

	if (!db.tableExists("nodeDB"))
	{
		cout << endl << "NodeDB doesn't exist. Creating NodeDB table" << endl;
		AddNodeDBTable();
	}

	//nodeDB(nodeID text, timeCre text, timeMod text, parentNodeID text)"))

	szCommand = "insert into nodeDB values ('";
	szCommand.append(a_vNodes.GetNodeID());
	szCommand.append("', '");
	szCommand.append(a_vNodes.GetTimeCreated());
	szCommand.append("', '");
	szCommand.append(a_vNodes.GetTimeModified());
	szCommand.append("', '");
	szCommand.append(a_vNodes.GetParentNodeID());
	szCommand.append("');");

	int nRows = ExecCommand(szCommand);
	cout << nRows << " row(s) added to nodeDB table" << endl;

	return true;
}

bool SQLiteDBBuilder::AddToTextDB(string a_szDBFilename, DBEntry &a_vNodes)
{
	string szCommand;
	vector<string> vNodes = a_vNodes.GetNodeToken();
	int nRows = 0;

	if (!db.tableExists("textDB"))
	{
		cout << endl << "TextDB doesn't exist. Creating TextDB table" << endl;
		AddTextDBTable();
	}

	//textDB(token text, nodeID text, weight integer, tag text, position integer)"))

	vector<string>::iterator itNodes;
	for (itNodes = vNodes.begin(); itNodes != vNodes.end(); itNodes++)
	{
		szCommand = "insert into textDB values ('";
		szCommand.append(*itNodes);
		szCommand.append("', '");
		szCommand.append(a_vNodes.GetNodeID());
		szCommand.append("', 0, '', 0);");

		nRows += ExecCommand(szCommand);
	}

	cout << nRows << " row(s) added to textDB table" << endl;
	return true;
}


/*
    int nRowsToCreate(50000);
    cout << endl << "Transaction test, creating " << nRowsToCreate;
    cout << " rows please wait..." << endl;
    tmStart = time(0);
    db.execDML("begin transaction;");

    for (i = 0; i < nRowsToCreate; i++)
    {
        char buf[128];
        sprintf(buf, "insert into emp values (%d, 'Empname%06d');", i, i);
        db.execDML(buf);
    }

    db.execDML("commit transaction;");
    tmEnd = time(0);

    ////////////////////////////////////////////////////////////////////////////////
    // Demonstrate CppSQLiteDB::execScalar()
    ////////////////////////////////////////////////////////////////////////////////
    cout << db.execScalar("select count(*) from emp;") << " rows in emp table in ";
    cout << tmEnd-tmStart << " seconds (that was fast!)" << endl;
*/