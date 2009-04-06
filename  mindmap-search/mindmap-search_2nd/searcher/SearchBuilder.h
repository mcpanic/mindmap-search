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
	bool SearchDB(string search_word, std::vector<DBEntry> &a_vNodes);	// �˻��� �Լ� ����

private:
	CppSQLite3DB db;	// sqlite�� ������ db��ü �̸�- 'db' SQLiteDBBuilder.cpp���� ����
	string m_szDBFilename;  // ���� DB file�̸� ; mindmapSearch.cpp���� ���������

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
 * DB���� Ư�� Ű������� �˻��� ����ID���� ��´�.
 */
__interface IIndexSearch
{
	/**
	 * �־���Ű������ �ε���DB�� �˻��Ͽ� �˻��� ����ID���� �����ش�.
	 *
	 * @param &vecKeywords	�˻��� Ű�����
	 * @param &listFileID	Ű���尡 �˻��� ����ID�� ���
	 * @return ������ true. ���н� false.
	 */
	virtual bool Search(const std::vector<std::string> &vecKeywords, std::list<unsigned long> &listFileID) = 0;
	virtual int ExecCommand(std::string a_szCommand);
};


/**
 * @group	searcher
 * @date	2009-03-06
 * @author	taekwonv
 * 
 * �־��� ����ID���� ��ŷ�Ѵ�. 
 */
__interface IRanker
{
	/**
	 * �־��� ����ID���� �߰����� ��ŷ�˰����� ���� ��ŷ�Ͽ� �������� ����� �����ش�.
	 * �ԷµǴ� listFileID����Ʈ�� �⺻������ ��ŷ�Ǿ� �ִ� ���¿����Ѵ�.
	 * @param &listFileID ��ŷ�� ����ID����Ʈ. ��ŷ����� ���ĵǾ� �����.
	 */
	virtual void Rank(std::list<unsigned long> &listFileID) = 0;
};
