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
	 * �־��� ����ID���� �߰����� ��ŷ�˰����� ���� ��ŷ�Ͽ� �������� ����� �����ش�.
	 * �ԷµǴ� listFileID����Ʈ�� �⺻������ ��ŷ�Ǿ� �ִ� ���¿����Ѵ�.
	 * @param &listFileID ��ŷ�� ����ID����Ʈ. ��ŷ����� ���ĵǾ� �����.
	 */
	virtual void Rank(std::list<SearchedItem> &listFileID);
};
