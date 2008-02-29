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
    Freemind의 마인드맵 XML 형태
    * <map> 태그: 최상위 태그로, 버전정보가 표시된다. 버전의 의미는?
    * <node> 태그: 마인드맵 상의 각 태그를 의미한다. parents 태그 내에 child 노드의 태그가 들어가서 nested 형태를 띈다. 

<node> 태그 속성일람

    * CREATED = 생성 시간의 timestamp로 추정
    * ID = 노드별 고유의 ID
    * MODIFIED = 최종 수정 시간의 timestamp로 추정
    * TEXT = 노드의 텍스트
    * POSITION = 가운데 점으로부터의 상대적 위치 (right, left)
    * HGAP = 가운데 점으로부터 가로 위치 차이 정도
    * VSHIFT = 가운데 점으로부터의 상대적 세로 위치 (+면 화면 아래방향, -면 위쪽방향)
    * COLOR = 노드 색깔
    * FOLDED = 현재 화면에 보이는지의 여부 (true, false) 
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
