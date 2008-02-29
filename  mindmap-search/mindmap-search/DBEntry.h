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
	* ID (int, primary key): �ĺ��� ���� ���� ID
    * Time created (time): �����ð�, timestamp �����
    * Time last modified (time): ���������ð�, timestamp �����
    * Text (char): ��忡 ��ϵ� �ؽ�Ʈ
    * Parent node (int, default=NULL): root�� ��쿡�� NULL
    * Note (char): �÷�, �̸�Ƽ�� �� 
*/

};
