#pragma once

#include <string>
#include <iostream>
#include "DBIndex.h"

// DBEntry�� ���� ���ҷ�, ���� ���� getter, setter����.
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

	void SetWord (char* a_Word); // Dictionary�� ����� �ܾ�
	string GetWord ();

	void SetWeight (int a_Weight);  // IndexDB�� ����� ����ġ
	int GetWeight ();

	void SetFileID (char* a_FileID);  // FileDB�� ����� file ������ ID
	int GetFileID ();

	void SetFileName(char* a_FileName);	// FileDB�� ����Ǵ� file �̸�
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
	DBIndexEntity *parentNode;	// Parent Node pointer ���� �ұ� �ƴϸ� ID ���� �ұ�?
	string parentNodeID;

/*
	* indexID		: �ܾ ������ ������ ID
	* fileID		: ������ ������ ������ ID
	* weight		: ����ġ
	* word			: ��忡 ��ϵ� �ؽ�Ʈ
	* m_strFileName : mm file �̸�
	* m_strNodeName : Parsing�� ����� �̸�
*/

};
