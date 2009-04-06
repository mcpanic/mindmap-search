#include "stdlib.h" // atoi()
#include "StdAfx.h"
#include "DBIndexEntity.h"

DBIndexEntity::DBIndexEntity(void)
{
}

DBIndexEntity::~DBIndexEntity(void)
{
}

void DBIndexEntity::SetNodeName (char *a_Nodename)
{
	//nodeName = a_Nodename;
	m_strNodeName = a_Nodename;
}

std::string DBIndexEntity::GetNodeName()
{
	//return nodeName;
	return m_strNodeName;
}
void DBIndexEntity::SetIndexID (char* a_IndexID)  // IndexID
{
	indexID = 0;
	//indexID = atoi(a_IndexID); // parsing해서 받은 값이 char type이기 때문에 정수형으로 형변환 (fileID is digit)
}

int DBIndexEntity::GetIndexID ()
{
	return indexID++;
}

void DBIndexEntity::SetWord (char* a_Word) // Dictionary에 저장될 단어
{
	word = (string)a_Word;	// 노드 단어를 출력해야하기 때문에 string type으로 형변환
}

string DBIndexEntity::GetWord ()
{
	return word;
}

void DBIndexEntity::SetWeight (int a_Weight)  // IndexDB에 저장될 가중치
{
	weight = a_Weight;	// parsing해서 받은 값이 char type이기 때문에 정수형으로 형변환 (weight is digit)
}

int DBIndexEntity::GetWeight ()
{
	return weight;
}

void DBIndexEntity::SetFileID (char* a_FileID)  // FileDB에 저장될 file 고유의 ID
{
	fileID = atoi(a_FileID);
}

int DBIndexEntity::GetFileID ()
{
	return fileID;
}

void DBIndexEntity::SetFileName (char* a_FileName)	// FileDB에 저장되는 file 이름
{
	//fileName = a_FileName;
	m_strFileName = a_FileName;
}
std::string DBIndexEntity::GetFileName()
{
	//return fileName;
	return m_strFileName;
}

void DBIndexEntity::SetParentNode (DBIndexEntity *a_ParentNode)
{
	parentNode = a_ParentNode;
}

DBIndexEntity *DBIndexEntity::GetParentNode ()
{
	return parentNode;
}

void DBIndexEntity::SetParentNodeID (string a_ParentNodeID)
{
	parentNodeID = a_ParentNodeID;
}

string DBIndexEntity::GetParentNodeID ()
{
	return parentNodeID;
}