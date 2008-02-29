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

	void SetNodeID (int enteredNodeID);
	int GetNodeID ();

	void SetTimeCreated (time_t enteredTimeCreated);
	time_t GetTimeCreated ();
	
	void SetTimeModified (time_t enteredTimeModified);
	time_t GetTimeModified ();
	
	void SetNodeText (string enteredNodeText);
	string GetNodeText ();

	void SetParentNode (DBEntry *enteredParentNode);
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
