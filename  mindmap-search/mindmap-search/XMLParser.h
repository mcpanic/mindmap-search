#pragma once

__interface IXMLParser
{
public:
	virtual bool OpenFile();
	virtual bool Parse();
};
