// mindmap-search.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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


int main (int argc, char* args[]) 
{
	// Create module objects
	IXMLParser *xmlParser = CreateXMLParser();
	ILexAnalyzer *lexAnalyzer = CreateLexAnalyzer();
	IWeightAssigner *weightAssigner = CreateWeightAssigner();
	IIndexBuilder *indexBuilder = CreateIndexBuilder();
	IDBBuilder *dbBuilder = CreateDBBuilder();

	string filename;
	cout << "Enter the mind map XML file name:";
	cin >> filename;

	// Create DB tables

	// Parse
	xmlParser->OpenFile(filename);
	if (!xmlParser->Parse())
		return 0;
	cout << "\nparse successful" << endl;

	// For each node, transform parsed data into DBEntry object format.
	DBEntry *dbEntry = new DBEntry;
	dbEntry->SetNodeID(10);

/*
    Freemind�� ���ε�� XML ����
    * <map> �±�: �ֻ��� �±׷�, ���������� ǥ�õȴ�. ������ �ǹ̴�?
    * <node> �±�: ���ε�� ���� �� �±׸� �ǹ��Ѵ�. parents �±� ���� child ����� �±װ� ���� nested ���¸� ���. 

<node> �±� �Ӽ��϶�

    * CREATED = ���� �ð��� timestamp�� ����
    * ID = ��庰 ������ ID
    * MODIFIED = ���� ���� �ð��� timestamp�� ����
    * TEXT = ����� �ؽ�Ʈ
    * POSITION = ��� �����κ����� ����� ��ġ (right, left)
    * HGAP = ��� �����κ��� ���� ��ġ ���� ����
    * VSHIFT = ��� �����κ����� ����� ���� ��ġ (+�� ȭ�� �Ʒ�����, -�� ���ʹ���)
    * COLOR = ��� ����
    * FOLDED = ���� ȭ�鿡 ���̴����� ���� (true, false) 
*/

	// For each node text, perform the following four steps repeatedly.

	// 1. Analyze lexically (separating whitespaces in the node text)
	lexAnalyzer->Analyze();

	// 2. Assign weight to each analyzed pieces
	weightAssigner->Assign();

	// 3. Create indices 
	indexBuilder->Build();

	// 4. Add the entry to the DB
	dbBuilder->AddEntry();
	

	// Delete module objects
	xmlParser->Release();
	lexAnalyzer->Release();
	weightAssigner->Release();
	indexBuilder->Release();
	dbBuilder->Release();

	return 0;
}

/*
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/
