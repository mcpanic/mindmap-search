#include "StdAfx.h"
#include "DBEntry.h"

DBEntry::DBEntry(void)
{
}

DBEntry::~DBEntry(void)
{
}

void DBEntry::SetNodeID (int enteredNodeID)
{
	nodeID = enteredNodeID;
}

int DBEntry::GetNodeID ()
{
	return nodeID;
}

void DBEntry::SetTimeCreated (time_t enteredTimeCreated)
{
	timeCreated = enteredTimeCreated;
}

time_t DBEntry::GetTimeCreated ()
{
	return timeCreated;
}

void DBEntry::SetTimeModified (time_t enteredTimeModified)
{
	timeModified = enteredTimeModified;
}

time_t DBEntry::GetTimeModified ()
{
	return timeModified;
}

void DBEntry::SetNodeText (string enteredNodeText)
{
	nodeText = enteredNodeText;
}

string DBEntry::GetNodeText ()
{
	return nodeText;
}

void DBEntry::SetParentNode (DBEntry *enteredParentNode)
{
	parentNode = enteredParentNode;
}
DBEntry *DBEntry::GetParentNode ()
{
	return parentNode;
}
