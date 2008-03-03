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

	try
    {
//        int i, fld;
//        time_t tmStart, tmEnd;

        cout << "SQLite Version: " << db.SQLiteVersion() << endl;

        
		
		////////////////////////////////////////////////////////////////////////////////
        // Execute some DML, and print number of rows affected by each one
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "DML tests" << endl;
        int nRows = db.execDML("insert into emp values (7, 'David Beckham');");
        cout << nRows << " rows inserted" << endl;

        nRows = db.execDML("update emp set empname = 'Christiano Ronaldo' where empno = 7;");
        cout << nRows << " rows updated" << endl;

        nRows = db.execDML("delete from emp where empno = 7;");
        cout << nRows << " rows deleted" << endl;
/*
        ////////////////////////////////////////////////////////////////////////////////
        // Transaction Demo
        // The transaction could just as easily have been rolled back
        ////////////////////////////////////////////////////////////////////////////////
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

        ////////////////////////////////////////////////////////////////////////////////
        // Re-create emp table with auto-increment field
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "Auto increment test" << endl;
        db.execDML("drop table emp;");
        db.execDML("create table emp(empno integer primary key, empname char(20));");
        cout << nRows << " rows deleted" << endl;

        for (i = 0; i < 5; i++)
        {
            char buf[128];
            sprintf(buf, "insert into emp (empname) values ('Empname%06d');", i+1);
            db.execDML(buf);
            cout << " primary key: " << (int)db.lastRowId() << endl;
        }

        ////////////////////////////////////////////////////////////////////////////////
        // Query data and also show results of inserts into auto-increment field
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "Select statement test" << endl;
        CppSQLite3Query q = db.execQuery("select * from emp order by 1;");

        for (fld = 0; fld < q.numFields(); fld++)
        {
            cout << q.fieldName(fld) << "(" << q.fieldDeclType(fld) << ")|";
        }
        cout << endl;

        while (!q.eof())
        {
            cout << q.fieldValue(0) << "|";
            cout << q.fieldValue(1) << "|" << endl;
            q.nextRow();
        }


        ////////////////////////////////////////////////////////////////////////////////
        // SQLite's printf() functionality. Handles embedded quotes and NULLs
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "SQLite sprintf test" << endl;
        CppSQLite3Buffer bufSQL;
        bufSQL.format("insert into emp (empname) values (%Q);", "He's bad");
        cout << (const char*)bufSQL << endl;
        db.execDML(bufSQL);

        bufSQL.format("insert into emp (empname) values (%Q);", NULL);
        cout << (const char*)bufSQL << endl;
        db.execDML(bufSQL);

        ////////////////////////////////////////////////////////////////////////////////
        // Fetch table at once, and also show how to use CppSQLiteTable::setRow() method
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "getTable() test" << endl;
        CppSQLite3Table t = db.getTable("select * from emp order by 1;");

        for (fld = 0; fld < t.numFields(); fld++)
        {
            cout << t.fieldName(fld) << "|";
        }
        cout << endl;
        for (int row = 0; row < t.numRows(); row++)
        {
            t.setRow(row);
            for (int fld = 0; fld < t.numFields(); fld++)
            {
                if (!t.fieldIsNull(fld))
                    cout << t.fieldValue(fld) << "|";
                else
                    cout << "NULL" << "|";
            }
            cout << endl;
        }


        ////////////////////////////////////////////////////////////////////////////////
        // Test CppSQLiteBinary by storing/retrieving some binary data, checking
        // it afterwards to make sure it is the same
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "Binary data test" << endl;
        db.execDML("create table bindata(desc char(10), data blob);");
        
        unsigned char bin[256];
        CppSQLite3Binary blob;

        for (i = 0; i < sizeof bin; i++)
        {
            bin[i] = i;
        }

        blob.setBinary(bin, sizeof bin);

        bufSQL.format("insert into bindata values ('testing', %Q);", blob.getEncoded());
        db.execDML(bufSQL);
        cout << "Stored binary Length: " << sizeof bin << endl;

        q = db.execQuery("select data from bindata where desc = 'testing';");

        if (!q.eof())
        {
            blob.setEncoded((unsigned char*)q.fieldValue("data"));
            cout << "Retrieved binary Length: " << blob.getBinaryLength() << endl;
        }
		q.finalize();

        const unsigned char* pbin = blob.getBinary();
        for (i = 0; i < sizeof bin; i++)
        {
            if (pbin[i] != i)
            {
                cout << "Problem: i: ," << i << " bin[i]: " << pbin[i] << endl;
            }
        }


		////////////////////////////////////////////////////////////////////////////////
        // Pre-compiled Statements Demo
        ////////////////////////////////////////////////////////////////////////////////
        cout << endl << "Transaction test, creating " << nRowsToCreate;
        cout << " rows please wait..." << endl;
        db.execDML("drop table emp;");
        db.execDML("create table emp(empno int, empname char(20));");
        tmStart = time(0);
        db.execDML("begin transaction;");

        CppSQLite3Statement stmt = db.compileStatement("insert into emp values (?, ?);");
        for (i = 0; i < nRowsToCreate; i++)
        {
            char buf[16];
            sprintf(buf, "EmpName%06d", i);
            stmt.bind(1, i);
            stmt.bind(2, buf);
            stmt.execDML();
            stmt.reset();
        }

        db.execDML("commit transaction;");
        tmEnd = time(0);

        cout << db.execScalar("select count(*) from emp;") << " rows in emp table in ";
        cout << tmEnd-tmStart << " seconds (that was even faster!)" << endl;

		*/
        cout << endl << "End of tests" << endl;
    }
    catch (CppSQLite3Exception& e)
    {
        cerr << e.errorCode() << ":" << e.errorMessage() << endl;
    }

	return true;
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