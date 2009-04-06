#pragma once

#include <string>
#include <iostream>
#include "DBIndex.h"

// DBEntry와 같은 역할로, 변수 저장 getter, setter생성.
using namespace std;

#define MAX_NODE_TEXT 512

typedef enum
{
	eAttrNodeName,
	eAttrNodeID,
	eAttrIndexID,
	eAttrFileID,
	eAttrWeight,
	eAttrWord,
	eAttrParentNodeID,
	eAttrFileName,
	eAttrTimeCreated,
	eAttrTimeModified,
	eAttrOther 
} EATTRTYPE;

class DBIndexEntity
{
public:
	DBIndexEntity();
	~DBIndexEntity();

	void SetNodeName (char* a_Nodename);
	std::string GetNodeName();

	void SetIndexID (char* a_IndexID);  // IndexID
	int GetIndexID ();

	void SetWord (char* a_Word); // Dictionary에 저장될 단어
	string GetWord ();

	void SetWeight (int a_Weight);  // IndexDB에 저장될 가중치
	int GetWeight ();

	void SetFileID (char* a_FileID);  // FileDB에 저장될 file 고유의 ID
	int GetFileID ();

	void SetFileName(char* a_FileName);	// FileDB에 저장되는 file 이름
	std::string GetFileName();	

	int GetNodeID() const {return 0;}

	int GetTimeCreated() const {return 0;}

	int GetTimeModified() const {return 0;}

	void SetParentNode (DBIndexEntity *a_ParentNode);

	DBIndexEntity *GetParentNode ();

	void SetParentNodeID (string a_ParentNodeID);

	string GetParentNodeID ();


private:
	int indexID;
	int fileID;
	int weight;
	string word;
	std::string m_strFileName;
	std::string m_strNodeName;
	DBIndexEntity *parentNode;	// Parent Node pointer 여야 할까 아니면 ID 여야 할까?
	string parentNodeID;

/*
	* indexID		: 단어가 고유로 가지는 ID
	* fileID		: 파일이 고유로 가지는 ID
	* weight		: 가중치
	* word			: 노드에 기록된 텍스트
	* m_strFileName : mm file 이름
	* m_strNodeName : Parsing된 노드의 이름
*/

};
