#pragma once

#include <string>
#include <ctime>

using namespace std;

#define MAX_NODE_TEXT 512

class DBEntry
{
public:
	DBEntry();
	~DBEntry();

	void PrintNode();

	void SetNodeID (string a_NodeID);
	string GetNodeID ();

	void SetNodeName (string a_NodeName);
	string GetNodeName ();

	void SetTimeCreated (time_t a_TimeCreated);
	time_t GetTimeCreated ();
	
	void SetTimeModified (time_t a_TimeModified);
	time_t GetTimeModified ();
	
	void SetNodeText (string a_NodeText);
	string GetNodeText ();

	void SetParentNode (DBEntry *a_ParentNode);
	DBEntry *GetParentNode ();

	void SetParentNodeID (string a_ParentNodeID);
	string GetParentNodeID ();

private:
	string nodeID;
	string nodeName;
	time_t timeCreated;
	time_t timeModified;
	string nodeText;
	DBEntry * parentNode;	// Parent Node pointer ���� �ұ� �ƴϸ� ID ���� �ұ�?
	string parentNodeID;


/*
	* ID (int, primary key): DB ����� primary key (���������θ� ���ȴ�)
	* Node ID (int): Freemind���� �ڵ������ϴ� ��� ID
	* Name (char): ����� �̸� (�ַ� node�� �ȴ�)
    * Time created (time): �����ð�, timestamp �����
    * Time last modified (time): ���������ð�, timestamp �����
    * Text (char): ��忡 ��ϵ� �ؽ�Ʈ
    * Parent node (int, default=NULL): root�� ��쿡�� NULL
    * Note (char): �÷�, �̸�Ƽ�� �� 
*/

};
