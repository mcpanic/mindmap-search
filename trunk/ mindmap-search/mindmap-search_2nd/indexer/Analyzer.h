#pragma once
#include "AnalysisFile.h"
#include "DBIndexEntity.h"
#include "CppSQLite3.h"

using namespace std;

class Analyzer: public IAnalysisFile
{
public:
	Analyzer();
	virtual ~Analyzer();

//protected:
	void Release();

	bool initFile(string szFilename, vector<DBIndexEntity> &vNodes);
	bool getResult(vector<DBIndexEntity> &vNodes, string szFilename, IDBIndex *dbIndex); //  getResult에서 매개변수로 받은 결과값을 받아 DB에 insert하는 함수입니다.
	bool calcWeight(vector<DBIndexEntity> &vNodes, IDBIndex *dbIndex);

};