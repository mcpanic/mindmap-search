#pragma once

#include "Search.h"
#include "CppSQLite3.h"
#include <string>

class CIndexSearch : public IIndexSearch
{
public:
	CIndexSearch(void)
	{		
		OpenDB(); // DB�� open�Ѵ�.
	}

	virtual ~CIndexSearch(void)
	{
		CloseDB(); // DB�� close�Ѵ�.	
	}


protected:
	virtual bool Search(const std::vector<std::string> &vecKeyWords, std::list<SearchedItem> &listFileID);

private:
	// �Ʒ� �� �Լ��� �ܺο��� ȣ���� �ʿ䰡 �����Ƿ� private���� ����
	void OpenDB();
	void CloseDB();

	CppSQLite3DB m_dbMindmap;	// sqlite�� ������ db��ü �̸�- 'db' SQLiteDBBuilder.cpp���� ����
	std::string m_szDBFilename;  // ���� DB file�̸� ; mindmapSearch.cpp���� ���������
};

