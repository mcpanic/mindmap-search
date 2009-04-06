#include "stdAfx.h"
#include "Analyzer.h"
#include "DBIndexEntity.h"
#include "XercesCXMLParser.h"
#include "CppSQLite3.h"
#include <iostream>
#include <ctime>

using namespace std;

Analyzer::Analyzer()
{
}

Analyzer::~Analyzer()
{
}

void Analyzer::Release()
{
	delete this;
}

// fileName을 받아 parsing.
bool Analyzer::initFile(string szFilename, vector<DBIndexEntity> &vNodes)
{
	IXMLParser *pXMLParser = new XercesCXMLParser;

	// Parsing
	pXMLParser->OpenFile(szFilename);
	if (!pXMLParser->Parse())
		return 0;

	// Store parsed node data into DBEntry format
	pXMLParser->Build(vNodes);
	pXMLParser->Release();

	cout <<"----------------------------------------------------------"<< endl;
	cout << "parse successful." << endl << endl;
	return true;
}

// Insert DB ( Dictionary, IndexDB / 단어, ID, 가중치(weight=0) )
bool Analyzer::getResult(vector<DBIndexEntity> &vNodes, string szFilename, IDBIndex *dbIndex)
{
	CppSQLite3Query qry;
       
	std::string nodeName;

	string s_resultWord;
    vector<DBIndexEntity>::iterator itNodes;
    for (itNodes = vNodes.begin(); itNodes != vNodes.end(); itNodes++) {
		s_resultWord = (*itNodes).GetWord();

		// NODE만 삽입하기 위해서, Pasing시에 노드종류를 뽑아낸다.
		nodeName = (*itNodes).GetNodeName();
	
		// nodeName이 "node"일때 insertion
		if (strcmp("node",nodeName.c_str()) == 0 && s_resultWord != "") {
			dbIndex->insertDictionary(s_resultWord, vNodes);
			dbIndex->insertIndexDB(s_resultWord, szFilename, vNodes);
		}
    }   
    return true;
}

// Weight를 계산하여 초기화되었던 계산한 weight값으로 변환해준다.
bool Analyzer::calcWeight(vector<DBIndexEntity> &vNodes, IDBIndex *dbIndex)
{
	// calculate Weight. 구현중지 (DOMNode의 사용과 XercesParser를 이용한 Parsing의 구체적이해 요구.
	return true;
}