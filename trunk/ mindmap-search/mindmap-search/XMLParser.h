#pragma once
#include <string>
using namespace std;

__interface IXMLParser
{
public:
	virtual void Release();
	
	virtual bool OpenFile(string filename);
	virtual bool Parse();
	virtual void PrintFile();
};
