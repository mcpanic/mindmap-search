#include "stdafx.h"
#include "IndexSearch.h"
#include "CppSQLite3.h"
#include "Ranker.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

/**
 * �־���Ű������ �ε���DB�� �˻��Ͽ� �˻��� ����ID���� �����ش�.
 *
 * @param &vecKeywords	�˻��� Ű�����
 * @param &listFileID	Ű���尡 �˻��� ����ID�� ���
 * @return ������ true. ���н� false.
**/

bool CIndexSearch::Search(const std::vector<std::string> &vecKeywords, std::list<SearchedItem> &listFileID)
{
	char sQuery[1024];
	
	IRanker *rank = new CRanker;

	cout << "-------------Your words------------- " << endl;
	copy (vecKeywords.begin(), vecKeywords.end(),ostream_iterator<std::string>(cout," "));

	std::map<int/*indexid*/, std::string/*Ű����*/>	mapKeyword;
	std::vector<int> vecIndexID;
	CppSQLite3Query qry;
	std::vector<string>::const_iterator it = vecKeywords.begin(); 

	for (; it != vecKeywords.end(); ++it)
	{
		sprintf(sQuery, "select IndexID from Dictionary where word = '%s'", it->c_str()); 
		
		try 
		{
			qry = m_dbMindmap.execQuery(sQuery); 
		}
		catch (CppSQLite3Exception &pEx)
		{
			printf(pEx.errorMessage());
			continue;
		}

		if (true == qry.eof()) 
			continue;
		
		int nIndexID = qry.getIntField("IndexID");
		vecIndexID.push_back(nIndexID);		

		mapKeyword.insert(std::map<int, std::string>::value_type(nIndexID, *it));
	}

	if (vecIndexID.size() < 1)
		return false;

	std::string strQuery; 
	std::string finQuery; 
	char szIndex[16];
	std::vector<int> inxIndexID; 
	std::vector<int>::iterator itx = vecIndexID.begin();

	strQuery = "select IndexID, FileName, count(weight) from IndexDB where IndexID = ";
	
	while (itx != vecIndexID.end())
	{
		itoa(*itx, szIndex, 10);
		strQuery += szIndex;

		++itx;

		if (itx == vecIndexID.end())
			break;

		strQuery += " or IndexID = ";
	}
		
	strQuery += " group by FileName order by count(weight) limit 1000";  

	try 
	{
		qry = m_dbMindmap.execQuery(strQuery.c_str()); 
	}
	catch (CppSQLite3Exception &ex)
	{
		printf(ex.errorMessage());
		abort();
	}
	
	SearchedItem item; 

	while (!qry.eof())
	{
		//item.sWord = mapKeyword.find(qry.getIntField("IndexID"))->second; 
		item.sFileName = qry.getStringField("FileName");
		item.nWeight = qry.getIntField(2); 

		listFileID.push_back(item);	

		qry.nextRow();
	}

	rank->Rank(listFileID);
	
	return true;
}

void CIndexSearch::OpenDB()
{
	m_dbMindmap.open("mindmap.db"); 
}

void CIndexSearch::CloseDB()
{
	m_dbMindmap.close();
}

