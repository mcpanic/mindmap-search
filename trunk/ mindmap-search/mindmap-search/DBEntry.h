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
	DBEntry * parentNode;	// Parent Node pointer 여야 할까 아니면 ID 여야 할까?
	string parentNodeID;


/*
	* ID (int, primary key): DB 저장용 primary key (내부적으로만 사용된다)
	* Node ID (int): Freemind에서 자동생성하는 노드 ID
	* Name (char): 노드의 이름 (주로 node가 된다)
    * Time created (time): 생성시간, timestamp 사용고려
    * Time last modified (time): 최종수정시간, timestamp 사용고려
    * Text (char): 노드에 기록된 텍스트
    * Parent node (int, default=NULL): root의 경우에는 NULL
    * Note (char): 컬러, 이모티콘 등 
*/

};
