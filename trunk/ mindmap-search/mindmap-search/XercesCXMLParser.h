#pragma once
#include "xmlparser.h"

class XercesCXMLParser: public IXMLParser
{
public:
	XercesCXMLParser();
	virtual ~XercesCXMLParser();

// Release function
	void Release();

	bool OpenFile();
	bool Parse();
};
