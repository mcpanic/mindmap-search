// mindmap-search.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.

#include "stdafx.h"
#include "indexer.h"

using namespace std;

static IDBIndex *CreateDBIndexBuilder()			// 인덱스 생성 interface
{
	return new DBIndexBuilder;
}

void StoreInDB (vector<DBIndexEntity> &a_vNodes, string g_szDBFilename, IDBIndex *dbIndex)
{
	dbIndex->SetDBName(g_szDBFilename);
	dbIndex->OpenDB();
	dbIndex->AddDictionaryTable();  // Dictionary Table생성
	dbIndex->AddIndexDBTable();	// IndexDBTable 생성
}

int main (int argc, char* args[])
{
	string g_szDBFilename = "mindmap.db";
	char charChoice;
	IDBIndex *dbIndex = CreateDBIndexBuilder();
	IAnalysisFile *analyzer = new Analyzer; // 단어분석위해

	// Create module objects
	do {
		string szFilename;	// mm file 
		cout << "\nEnter the mind map XML file name: ";
		cin >> szFilename;

		// Parsing
		vector<DBIndexEntity> vNodes;
		analyzer->initFile(szFilename, vNodes);

		vector<string>::iterator resultWord;
		vector<DBIndexEntity>::iterator itNodes;
		cout << szFilename << " file has these words ... " << endl;
		// 각각의 단어를 불러온다
		for (itNodes = vNodes.begin(); itNodes != vNodes.end(); itNodes++)
			cout << (*itNodes).GetWord() << endl;         

		//dbIndex->OpenDB();
		// Store in DB.
		StoreInDB (vNodes, g_szDBFilename, dbIndex);	
	
		// Insert all Nodes in Dictionary and IndexDB.table
		analyzer->getResult(vNodes, szFilename, dbIndex);

		// Calculate weight and insert.
		analyzer->calcWeight(vNodes, dbIndex);
	
		cout << "Do you want to add more mindmap file? (y/n) ";
		cin >> charChoice;

    } while ((charChoice == 'y') || (charChoice == 'Y'));

	cout << "\nDB저장이 완료되었습니다." << endl;
	dbIndex->CloseDB();
	dbIndex->Release();
	dbIndex = NULL;
	
	return 0;
}

