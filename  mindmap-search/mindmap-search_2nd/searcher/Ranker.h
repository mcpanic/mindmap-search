#pragma once

#include "Search.h"
#include <list>


class CRanker : public IRanker
{
public:
	CRanker(void)
	{
	}

	virtual ~CRanker(void)
	{
	}

protected:
	/**
	 * 주어진 파일ID들을 추가적인 랭킹알고리즘을 통해 랭킹하여 재정렬한 결과를 돌려준다.
	 * 입력되는 listFileID리스트는 기본적으로 랭킹되어 있는 상태여야한다.
	 * @param &listFileID 랭킹할 파일ID리스트. 랭킹결과가 정렬되어 저장됨.
	 */
	virtual void Rank(std::list<SearchedItem> &listFileID);
};
