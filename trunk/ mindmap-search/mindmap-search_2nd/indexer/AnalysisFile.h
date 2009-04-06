#pragma once
#include <string>
#include <vector>
#include "DBIndexEntity.h"
#include "DBIndexBuilder.h"

__interface IAnalysisFile
{
public:
	virtual void Release() = 0;

	virtual bool initFile(std::string szFilename, std::vector<DBIndexEntity> &vNodes) = 0;
	virtual bool getResult(std::vector<DBIndexEntity> &vNodes, std::string szFilename, IDBIndex *dbIndex) = 0; //  getResult에서 매개변수로 받은 결과값을 받아 DB에 insert하는 함수입니다.
	virtual bool calcWeight(std::vector<DBIndexEntity> &vNodes, IDBIndex *dbIndex) = 0;

};