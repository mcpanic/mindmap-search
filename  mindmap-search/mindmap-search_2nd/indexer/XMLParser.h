#pragma once
#include <string>
#include <vector>

using namespace std;

__interface IXMLParser
{
public:
	virtual void Release() = 0;
	
	virtual bool OpenFile(string filename) = 0;
	virtual bool Parse() = 0;
	virtual void PrintFile() = 0;
	virtual void Build(vector<class DBIndexEntity> &a_vNodes) = 0;
};
