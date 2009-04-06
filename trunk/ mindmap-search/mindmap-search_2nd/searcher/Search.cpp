#include "stdafx.h"
#include "IndexSearch.h"
#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>

using namespace std;

int main(int argc, char* argv[])
{
	vector<string> vSearchWords; 
	char searchWords[100];
	string szTemp;
	std::list<SearchedItem> listFileID;
	
	IIndexSearch *indexSearch = new CIndexSearch;

	cout << "Enter the Search word : ";
	cin.getline(searchWords, sizeof(searchWords));

	stringstream ss(searchWords);

	while (ss >> szTemp)
        vSearchWords.push_back(szTemp);

	bool bSearch = indexSearch->Search(vSearchWords, listFileID); 

	std::list<SearchedItem>::iterator itList;

	itList = listFileID.begin();
	
	if (false == bSearch) 
	{
		cout << endl << "------------------------------------ " << endl;
		cout << "검색결과가 없습니다." << endl;
	}
	else
	{
		cout << endl << "------------------------------------ " << endl;
		cout << "아래와 같은 검색결과를 찾았습니다." << endl;
		cout << "------------------------------------ " << endl;
		
	    for (itList = listFileID.begin(); itList != listFileID.end(); ++itList) {
			 cout << "fileName : " << (*itList).sFileName << endl;
			 cout << "weight   : " << (*itList).nWeight << endl;
			 cout << "------------------------------------ " << endl;
		}
	}
	
	delete indexSearch;
	indexSearch = NULL;

	cout << "Press anykey ... " << endl;
	getch();

	return 0;
}
