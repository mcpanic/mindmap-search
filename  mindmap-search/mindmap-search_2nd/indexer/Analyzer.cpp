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

// fileName�� �޾� parsing.
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

// Insert DB ( Dictionary, IndexDB / �ܾ�, ID, ����ġ(weight=0) )
bool Analyzer::getResult(vector<DBIndexEntity> &vNodes, string szFilename, IDBIndex *dbIndex)
{
	CppSQLite3Query qry;
       
	std::string nodeName;

	string s_resultWord;
    vector<DBIndexEntity>::iterator itNodes;
    for (itNodes = vNodes.begin(); itNodes != vNodes.end(); itNodes++) {
		s_resultWord = (*itNodes).GetWord();

		// NODE�� �����ϱ� ���ؼ�, Pasing�ÿ� ��������� �̾Ƴ���.
		nodeName = (*itNodes).GetNodeName();
	
		// nodeName�� "node"�϶� insertion
		if (strcmp("node",nodeName.c_str()) == 0 && s_resultWord != "") {
			dbIndex->insertDictionary(s_resultWord, vNodes);
			dbIndex->insertIndexDB(s_resultWord, szFilename, vNodes);
		}
    }   
    return true;
}

// Weight�� ����Ͽ� �ʱ�ȭ�Ǿ��� ����� weight������ ��ȯ���ش�.
bool Analyzer::calcWeight(vector<DBIndexEntity> &vNodes, IDBIndex *dbIndex)
{
	// calculate Weight. �������� (DOMNode�� ���� XercesParser�� �̿��� Parsing�� ��ü������ �䱸.
	return true;
}