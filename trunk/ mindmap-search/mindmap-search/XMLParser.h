#pragma once
#include <string>
#include <vector>

using namespace std;

__interface IXMLParser
{
public:
	virtual void Release();
	
	virtual bool OpenFile(string filename);
	virtual bool Parse();
	virtual void PrintFile();
	virtual void Build(vector<class DBEntry> &a_vNodes);

};
