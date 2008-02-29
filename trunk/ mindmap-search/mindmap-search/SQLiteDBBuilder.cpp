#include "StdAfx.h"
#include "SQLiteDBBuilder.h"

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
	return true;
}

bool SQLiteDBBuilder::CloseDB()
{ 
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
bool SQLiteDBBuilder::ExecCommand()
{ 
	return true;
}
