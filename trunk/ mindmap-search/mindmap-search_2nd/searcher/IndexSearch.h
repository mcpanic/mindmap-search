#pragma once

#include "Search.h"
#include "CppSQLite3.h"
#include <string>

class CIndexSearch : public IIndexSearch
{
public:
	CIndexSearch(void)
	{		
		OpenDB(); // DB를 open한다.
	}

	virtual ~CIndexSearch(void)
	{
		CloseDB(); // DB를 close한다.	
	}


protected:
	virtual bool Search(const std::vector<std::string> &vecKeyWords, std::list<SearchedItem> &listFileID);

private:
	// 아래 두 함수는 외부에서 호출할 필요가 없으므로 private으로 만듦
	void OpenDB();
	void CloseDB();

	CppSQLite3DB m_dbMindmap;	// sqlite로 생성할 db객체 이름- 'db' SQLiteDBBuilder.cpp에서 구현
	std::string m_szDBFilename;  // 실제 DB file이름 ; mindmapSearch.cpp에서 변수선언됨
};

