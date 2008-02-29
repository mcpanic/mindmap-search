#pragma once
#include "xmlparser.h"

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#if defined(XERCES_NEW_IOSTREAMS)
#include <iostream>
#else
#include <iostream.h>
#endif

XERCES_CPP_NAMESPACE_USE


class XercesCXMLParser: public IXMLParser
{
public:
	XercesCXMLParser();
	virtual ~XercesCXMLParser();

// Release function
	void Release();

	bool OpenFile(string insertedFile);
	bool Parse();

private:
	string filename;
};
