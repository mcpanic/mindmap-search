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
	virtual bool getResult(std::vector<DBIndexEntity> &vNodes, std::string szFilename, IDBIndex *dbIndex) = 0; //  getResult���� �Ű������� ���� ������� �޾� DB�� insert�ϴ� �Լ��Դϴ�.
	virtual bool calcWeight(std::vector<DBIndexEntity> &vNodes, IDBIndex *dbIndex) = 0;

};