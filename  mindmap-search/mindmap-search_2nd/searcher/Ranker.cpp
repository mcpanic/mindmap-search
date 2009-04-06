#include "stdafx.h"
#include "Ranker.h"
#include "IndexSearch.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// listFileID 들을 추가로 랭킹한다.
// 예를들어 가중치가 아닌 파일 자체의 인기도,신뢰도 등을 적용해서 listFileID를 다시 정렬한다.
// 만약 추가적인 랭킹요소들이 없다면 구현 안해도 무방.
// 구현시, 만약 리스트의 수가 엄청나게 많다면 검색속도를 위해 listFileID 상위 100개? 정도만 랭킹해도 될 것이다.

bool compare_nocase (SearchedItem first, SearchedItem second)
{
    return (first.nWeight > second.nWeight);
}

void CRanker::Rank(std::list<SearchedItem> &listFileID)
{
	 listFileID.sort(compare_nocase);
}
