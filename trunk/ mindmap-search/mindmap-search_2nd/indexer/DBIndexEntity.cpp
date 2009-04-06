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
	//indexID = atoi(a_IndexID); // parsing�ؼ� ���� ���� char type�̱� ������ ���������� ����ȯ (fileID is digit)
}

int DBIndexEntity::GetIndexID ()
{
	return indexID++;
}

void DBIndexEntity::SetWord (char* a_Word) // Dictionary�� ����� �ܾ�
{
	word = (string)a_Word;	// ��� �ܾ ����ؾ��ϱ� ������ string type���� ����ȯ
}

string DBIndexEntity::GetWord ()
{
	return word;
}

void DBIndexEntity::SetWeight (int a_Weight)  // IndexDB�� ����� ����ġ
{
	weight = a_Weight;	// parsing�ؼ� ���� ���� char type�̱� ������ ���������� ����ȯ (weight is digit)
}

int DBIndexEntity::GetWeight ()
{
	return weight;
}

void DBIndexEntity::SetFileID (char* a_FileID)  // FileDB�� ����� file ������ ID
{
	fileID = atoi(a_FileID);
}

int DBIndexEntity::GetFileID ()
{
	return fileID;
}

void DBIndexEntity::SetFileName (char* a_FileName)	// FileDB�� ����Ǵ� file �̸�
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