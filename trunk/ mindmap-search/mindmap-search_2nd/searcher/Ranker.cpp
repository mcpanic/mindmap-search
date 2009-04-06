#include "stdafx.h"
#include "Ranker.h"
#include "IndexSearch.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// listFileID ���� �߰��� ��ŷ�Ѵ�.
// ������� ����ġ�� �ƴ� ���� ��ü�� �α⵵,�ŷڵ� ���� �����ؼ� listFileID�� �ٽ� �����Ѵ�.
// ���� �߰����� ��ŷ��ҵ��� ���ٸ� ���� ���ص� ����.
// ������, ���� ����Ʈ�� ���� ��û���� ���ٸ� �˻��ӵ��� ���� listFileID ���� 100��? ������ ��ŷ�ص� �� ���̴�.

bool compare_nocase (SearchedItem first, SearchedItem second)
{
    return (first.nWeight > second.nWeight);
}

void CRanker::Rank(std::list<SearchedItem> &listFileID)
{
	 listFileID.sort(compare_nocase);
}
