#pragma once

#include <string>
#include <iostream>
#include "MindmapSearch.h"

using namespace std;

#define MAX_NODE_TEXT 512


typedef enum
{
	eAttrNodeID,
	eAttrNodeName,
	eAttrTimeCreated,
	eAttrTimeModified,
	eAttrNodeText,
	eAttrParentNodeID,
	eAttrOther
} EATTRTYPE;

class DBEntry
{
public:
	DBEntry();
	~DBEntry();

	void PrintNode();
	void ProcessNode();

	void SetNodeID (string a_NodeID);
	string GetNodeID ();

	void SetNodeName (string a_NodeName);
	string GetNodeName ();

	void SetTimeCreated (string a_TimeCreated);
	string GetTimeCreated ();
	
	void SetTimeModified (string a_TimeModified);
	string GetTimeModified ();
	
	void SetNodeText (string a_NodeText);
	string GetNodeText ();

	void SetParentNode (DBEntry *a_ParentNode);
	DBEntry *GetParentNode ();

	void SetParentNodeID (string a_ParentNodeID);
	string GetParentNodeID ();

private:
	string nodeID;
	string nodeName;
	string timeCreated;
	string timeModified;
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
    * Other (char): �÷�, �̸�Ƽ�� �� 
*/

};
