// mindmap-search.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MindmapSearch.h"

static IXMLParser *CreateXMLParser()
{
	return new XercesCXMLParser;
}

static ILexAnalyzer *CreateLexAnalyzer()
{
	return new SimpleLexAnalyzer;
}

static IWeightAssigner *CreateWeightAssigner()
{
	return new SimpleWeightAssigner;
}

static IIndexBuilder *CreateIndexBuilder()
{
	return new SimpleIndexBuilder;
}

static IDBBuilder *CreateDBBuilder()
{
	return new SQLiteDBBuilder;
}

  
/*
int main(int argc, char* argv[])
{
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    // Do your failure processing here
    return 1;
  }

  // Do your actual work with Xerces-C++ here.

  XMLPlatformUtils::Terminate();

  // Other terminations and cleanup.
  return 0;
}


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/

//using namespace std;

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

int main (int argc, char* args[]) {

    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Error during initialization! :\n"
             << message << "\n";
        XMLString::release(&message);
        return 1;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Auto);    
    parser->setDoNamespaces(true);    // optional
/*
	parser->setValidationScheme(XercesDOMParser::Val_Auto);
    parser->setDoNamespaces(true);
    parser->setDoSchema(true);
    parser->setValidationSchemaFullChecking(true);
*/
    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

    char* xmlFile = "personal.xml";

/*

static const char*  gXMLInMemBuf =
"\
<?xml version='1.0' encoding='\" MEMPARSE_ENCODING \"'?>\n\
<!DOCTYPE company [\n\
<!ELEMENT company     (product,category,developedAt)>\n\
<!ELEMENT product     (#PCDATA)>\n\
<!ELEMENT category    (#PCDATA)>\n\
<!ATTLIST category idea CDATA #IMPLIED>\n\
<!ELEMENT developedAt (#PCDATA)>\n\
]>\n\n\
<company>\n\
    <product>XML4C</product>\n\
    <category idea='great'>XML Parsing Tools</category>\n\
    <developedAt>\n\
      IBM Center for Java Technology, Silicon Valley, Cupertino, CA\n\
    </developedAt>\n\
</company>\
";

static const char*  gMemBufId = "prodInfo";




    MemBufInputSource* memBufIS = new MemBufInputSource
    (
        (const XMLByte*)gXMLInMemBuf
        , strlen(gXMLInMemBuf)
        , gMemBufId
        , false
    );



*/
	// Create a progressive scan token
XMLPScanToken token;

if (!parser->parseFirst(xmlFile, token))
{
  XERCES_STD_QUALIFIER cerr << "scanFirst() failed\n" << XERCES_STD_QUALIFIER endl;
  return -1;
}

//
// We started ok, so lets call scanNext()
// until we find what we want or hit the end.
//
bool gotMore = true;
//while (gotMore && !handler->getDone())
while (gotMore)
  gotMore = parser->parseNext(token);


    try {
  //      parser->parse(xmlFile);
    }
	catch (const OutOfMemoryException&) {
		std::cout << "Exception message is: \n"
             << "OutOfMemoryException" << "\n";
        return -1;
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return -1;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
		std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return -1;
    }
	catch (const SAXException& toCatch) {
	    char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "SAX Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return -1;
	}
    catch (...) {
		std::cout << "Unexpected Exception \n" ;
        return -1;
    }

/*
	int errorCount = 0;
	errorCount = parser->getErrorCount();

	if (errorCount == 0)
	{
        XERCES_STD_QUALIFIER cout << "\nFinished parsing the memory buffer containing the following "
			<< XERCES_STD_QUALIFIER endl;
	}
*/

//	XMLPlatformUtils::Terminate();
    delete parser;
    delete errHandler;

	return 0;
}
