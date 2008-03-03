// mindmap-search.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MindmapSearch.h"

static IXMLParser *CreateXMLParser()
{
	return new XercesCXMLParser;
}

static ILexAnalyzer *CreateLexAnalyzer()
{
	return new SimpleLexAnalyzer;
}

static IWeightAssigner *CreateWeightAssigner()
{
	return new SimpleWeightAssigner;
}

static IIndexBuilder *CreateIndexBuilder()
{
	return new SimpleIndexBuilder;
}

static IDBBuilder *CreateDBBuilder()
{
	return new SQLiteDBBuilder;
}

bool ProcessNodeText (vector<DBEntry> &a_vNodes)
{
	ILexAnalyzer *lexAnalyzer = CreateLexAnalyzer();
	IWeightAssigner *weightAssigner = CreateWeightAssigner();
	IIndexBuilder *indexBuilder = CreateIndexBuilder();

	string szNodeText;

	vector<DBEntry>::iterator itNodes;
	for (itNodes = a_vNodes.begin(); itNodes != a_vNodes.end(); itNodes++)
	{
		szNodeText = itNodes->GetNodeText();
		
		// 1. Analyze lexically (separating whitespaces in the node text)
		lexAnalyzer->Analyze(*itNodes);

		// Print lexically analyzed tokens for the node
		itNodes->PrintNodeToken();
		
		// 2. Assign weight to each analyzed pieces
		weightAssigner->Assign();

		// 3. Create indices 
		indexBuilder->Build();
	}

	lexAnalyzer->Release();
	weightAssigner->Release();
	indexBuilder->Release();

	return true;
}

void StoreInTextDB (vector<DBEntry> &a_vNodes)
{
	IDBBuilder *dbBuilder = CreateDBBuilder();

	// 4. Add the entry to the DB
	dbBuilder->ExecCommand();
	
	dbBuilder->Release();

}

void StoreInNodeDB (vector<DBEntry> &a_vNodes)
{
	IDBBuilder *dbBuilder = CreateDBBuilder();
	dbBuilder->Release();
}

int main (int argc, char* args[]) 
{
	// Create module objects
	IXMLParser *pXMLParser = CreateXMLParser();

	string szFilename;
	cout << "Enter the mind map XML file name: ";
	cin >> szFilename;

	// Create DB tables

	// Parse
	pXMLParser->OpenFile(szFilename);
	if (!pXMLParser->Parse())
		return 0;
	cout << "\nparse successful" << endl;

	// Store parsed node data into DBEntry format
	vector<DBEntry> vNodes;
	pXMLParser->Build(vNodes);


	//vector<DBEntry>::iterator itNodes;
	//for (itNodes = vNodes.begin(); itNodes != vNodes.end(); itNodes++)
	//	cout << (*itNodes).GetNodeText() << endl;

	// 1) For the node text, call ProcessNodeText -> StoreInTextDB
	ProcessNodeText (vNodes);
	StoreInNodeDB (vNodes);

	// 2) For the general node info, call StoreInNodeDB
	StoreInTextDB (vNodes);

	// Delete module objects
	pXMLParser->Release();

	return 0;
}

