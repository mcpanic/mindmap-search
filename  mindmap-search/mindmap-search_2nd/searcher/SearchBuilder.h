/*#pragma once

#include <string>
#include <vector>

using namespace std;

class Search: public IDBSearcher
{
public:
	Search();
	virtual ~Search();

	bool OpenDB();
	bool CloseDB();

// Release function
	void Release();
	bool SearchDB(string search_word, std::vector<DBEntry> &a_vNodes);	// 검색할 함수 선언

private:
	CppSQLite3DB db;	// sqlite로 생성할 db객체 이름- 'db' SQLiteDBBuilder.cpp에서 구현
	string m_szDBFilename;  // 실제 DB file이름 ; mindmapSearch.cpp에서 변수선언됨

};*/

#pragma once

#include <vector>
#include <list>
#include <string>


/**
 * @group	searcher
 * @date	2009-03-06
 * @author	taekwonv
 * 
 * DB에서 특정 키워드들이 검색된 파일ID들을 얻는다.
 */
__interface IIndexSearch
{
	/**
	 * 주어진키워드들로 인덱스DB를 검색하여 검색된 파일ID들을 돌려준다.
	 *
	 * @param &vecKeywords	검색할 키워드들
	 * @param &listFileID	키워드가 검색된 파일ID들 결과
	 * @return 성공시 true. 실패시 false.
	 */
	virtual bool Search(const std::vector<std::string> &vecKeywords, std::list<unsigned long> &listFileID) = 0;
	virtual int ExecCommand(std::string a_szCommand);
};


/**
 * @group	searcher
 * @date	2009-03-06
 * @author	taekwonv
 * 
 * 주어진 파일ID들을 랭킹한다. 
 */
__interface IRanker
{
	/**
	 * 주어진 파일ID들을 추가적인 랭킹알고리즘을 통해 랭킹하여 재정렬한 결과를 돌려준다.
	 * 입력되는 listFileID리스트는 기본적으로 랭킹되어 있는 상태여야한다.
	 * @param &listFileID 랭킹할 파일ID리스트. 랭킹결과가 정렬되어 저장됨.
	 */
	virtual void Rank(std::list<unsigned long> &listFileID) = 0;
};
