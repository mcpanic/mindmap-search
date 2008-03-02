#include "StdAfx.h"
#include "DBEntry.h"

DBEntry::DBEntry(void)
{
}

DBEntry::~DBEntry(void)
{
}

void DBEntry::PrintNode()
{
	cout << "nodeID		: " << nodeID << endl;
	cout << "nodeName	: " << nodeName << endl;
	cout << "timeCreated	: " << timeCreated << endl;
	cout << "timeModified	: " << timeModified << endl;
	cout << "nodeText	: " << nodeText << endl;
	cout << "parentNodeID	: " << parentNodeID << endl;
}

void DBEntry::ProcessNode()
{

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
	nodeName = a_NodeName;
}

string DBEntry::GetNodeName ()
{
	return nodeName;
}

void DBEntry::SetTimeCreated (string a_TimeCreated)
{
	timeCreated = a_TimeCreated;
}

string DBEntry::GetTimeCreated ()
{
	return timeCreated;
}

void DBEntry::SetTimeModified (string a_TimeModified)
{
	timeModified = a_TimeModified;
}

string DBEntry::GetTimeModified ()
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

vector<string> &DBEntry::GetNodeToken ()
{
	return nodeToken;
}

void DBEntry::PrintNodeToken()
{
	vector<string>::iterator itNodes;
	for (itNodes = nodeToken.begin(); itNodes != nodeToken.end(); itNodes++)
	{
		cout << *itNodes << ", ";
	}
	cout << endl;
}

