#include "StdAfx.h"
#include "DBEntry.h"
#include <iostream>

DBEntry::DBEntry(void)
{
}

DBEntry::~DBEntry(void)
{
}

void DBEntry::PrintNode()
{
	if (nodeName != "node")
		return;

	cout << "nodeID " << nodeID << endl;
	cout << "nodeName " << nodeName << endl;
	cout << "timeCreated " << timeCreated << endl;
	cout << "timeModified " << timeModified << endl;
	cout << "nodeText " << nodeText << endl;
	cout << "parentNodeID " << parentNodeID << endl;
}

void DBEntry::SetNodeID (string a_NodeID)
{
	nodeID = a_NodeID;
}

string DBEntry::GetNodeID ()
{
	return nodeID;
}

void DBEntry::SetNodeName (string a_NodeName)
{
	nodeText = a_NodeName;
}

string DBEntry::GetNodeName ()
{
	return nodeName;
}

void DBEntry::SetTimeCreated (time_t a_TimeCreated)
{
	timeCreated = a_TimeCreated;
}

time_t DBEntry::GetTimeCreated ()
{
	return timeCreated;
}

void DBEntry::SetTimeModified (time_t a_TimeModified)
{
	timeModified = a_TimeModified;
}

time_t DBEntry::GetTimeModified ()
{
	return timeModified;
}

void DBEntry::SetNodeText (string a_NodeText)
{
	nodeText = a_NodeText;
}

string DBEntry::GetNodeText ()
{
	return nodeText;
}

void DBEntry::SetParentNode (DBEntry *a_ParentNode)
{
	parentNode = a_ParentNode;
}
DBEntry *DBEntry::GetParentNode ()
{
	return parentNode;
}

void DBEntry::SetParentNodeID (string a_ParentNodeID)
{
	parentNodeID = a_ParentNodeID;
}

string DBEntry::GetParentNodeID ()
{
	return parentNodeID;
}