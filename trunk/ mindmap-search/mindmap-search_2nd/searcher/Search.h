#pragma once

#include <vector>
#include <list>
#include <string>

//리스트에 들어갈 구조체 
struct SearchedItem
{
	std::string sWord;
	std::string sFileName;
	int	nWeight;
	
};

__interface IIndexSearch
{
	virtual bool Search(const std::vector<std::string> &vecKeyWords, std::list<SearchedItem> &listFileID) = 0;	
};

__interface IRanker
{
	virtual void Rank(std::list<SearchedItem> &listFileID) = 0;
};