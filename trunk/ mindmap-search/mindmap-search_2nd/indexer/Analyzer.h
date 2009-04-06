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
	bool getResult(vector<DBIndexEntity> &vNodes, string szFilename, IDBIndex *dbIndex); //  getResult���� �Ű������� ���� ������� �޾� DB�� insert�ϴ� �Լ��Դϴ�.
	bool calcWeight(vector<DBIndexEntity> &vNodes, IDBIndex *dbIndex);

};