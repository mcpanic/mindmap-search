#pragma once
#include "xmlparser.h"
#include "DBIndexEntity.h"  // 여기서 DBEntry 를 너희들이 만든 걸루 바꿀꺼지?

#include <vector>

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/XMLPScanToken.hpp>
#include <xercesc/framework/StdOutFormatTarget.hpp>
//#include <xercesc/dom/impl/DOMWriterImpl.hpp>

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

	bool OpenFile(string a_szFilename);
	bool Parse();
	void PrintFile();
	void Build(vector<DBIndexEntity> &a_vNodes);

private:
	int ProcessParsed(DOMNode *node, bool bPrint, vector<DBIndexEntity> &a_vNodes);
	
	string m_szFilename;
	DOMNode *m_pDoc;
	DOMDocument *m_pDocument;

	XercesDOMParser* m_pParser;
	ErrorHandler* m_pErrHandler;

};
