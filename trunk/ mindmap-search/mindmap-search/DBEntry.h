#pragma once

#include <string>
#include <ctime>

using namespace std;

#define MAX_NODE_TEXT 512

class DBEntry
{
public:
	DBEntry(void);
	~DBEntry(void);

	void SetNodeID (int nodeID);
	int GetNodeID ();

	void SetTimeCreated (time_t timeCreated);
	time_t GetTimeCreated ();
	
	void SetTimeModified (time_t timeModified);
	time_t GetTimeModified ();
	
	void SetNodeText (string nodeText);
	string GetNodeText ();

	void SetParentNode (DBEntry *parentNode);
	DBEntry *GetParentNode ();

private:
	int nodeID;
	time_t timeCreated;
	time_t timeModified;
	string nodeText;
	DBEntry * parentNode;


/*
	* ID (int, primary key): 식별을 위한 고유 ID
    * Time created (time): 생성시간, timestamp 사용고려
    * Time last modified (time): 최종수정시간, timestamp 사용고려
    * Text (char): 노드에 기록된 텍스트
    * Parent node (int, default=NULL): root의 경우에는 NULL
    * Note (char): 컬러, 이모티콘 등 
*/

};
