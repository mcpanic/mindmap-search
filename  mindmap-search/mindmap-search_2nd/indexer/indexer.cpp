// mindmap-search.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.

#include "stdafx.h"
#include "indexer.h"

using namespace std;

static IDBIndex *CreateDBIndexBuilder()			// �ε��� ���� interface
{
	return new DBIndexBuilder;
}

void StoreInDB (vector<DBIndexEntity> &a_vNodes, string g_szDBFilename, IDBIndex *dbIndex)
{
	dbIndex->SetDBName(g_szDBFilename);
	dbIndex->OpenDB();
	dbIndex->AddDictionaryTable();  // Dictionary Table����
	dbIndex->AddIndexDBTable();	// IndexDBTable ����
}

int main (int argc, char* args[])
{
	string g_szDBFilename = "mindmap.db";
	char charChoice;
	IDBIndex *dbIndex = CreateDBIndexBuilder();
	IAnalysisFile *analyzer = new Analyzer; // �ܾ�м�����

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
		// ������ �ܾ �ҷ��´�
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

	cout << "\nDB������ �Ϸ�Ǿ����ϴ�." << endl;
	dbIndex->CloseDB();
	dbIndex->Release();
	dbIndex = NULL;
	
	return 0;
}

