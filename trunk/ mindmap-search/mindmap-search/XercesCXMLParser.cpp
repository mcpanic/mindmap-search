#include "StdAfx.h"
#include "XercesCXMLParser.h"

XercesCXMLParser::XercesCXMLParser()
{
}

XercesCXMLParser::~XercesCXMLParser()
{
}

void XercesCXMLParser::Release()
{
	delete this;
}

bool XercesCXMLParser::OpenFile(string insertedFile)
{
	filename = insertedFile;
	return true;
}


bool XercesCXMLParser::Parse()
{
    try {
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Error during initialization! :\n" << message << "\n";
        XMLString::release(&message);
        return false;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Auto);    
    parser->setDoNamespaces(true);    // optional

	parser->setValidationScheme(XercesDOMParser::Val_Auto);
    parser->setDoNamespaces(true);
    parser->setDoSchema(true);
    parser->setValidationSchemaFullChecking(true);

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

	const char *xmlFile = filename.c_str();
//    char* xmlFile = "personal.xml";

/*
	// Create a progressive scan token
	XMLPScanToken token;

	if (!parser->parseFirst(xmlFile, token))
	{
	  XERCES_STD_QUALIFIER cerr << "scanFirst() failed\n" << XERCES_STD_QUALIFIER endl;
	  return false;
	}


	//
	// We started ok, so lets call scanNext()
	// until we find what we want or hit the end.
	//
	bool gotMore = true;
	//while (gotMore && !handler->getDone())
	while (gotMore)
	  gotMore = parser->parseNext(token);
*/

    try 
	{
        parser->parse(xmlFile);
    }
	catch (const OutOfMemoryException&) 
	{
		std::cout << "Exception message is: \n" << "OutOfMemoryException" << "\n";
        return false;
    }
    catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return false;
    }
    catch (const DOMException& toCatch) {
        char* message = XMLString::transcode(toCatch.msg);
		std::cout << "Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return false;
    }
	catch (const SAXException& toCatch) {
	    char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "SAX Exception message is: \n" << message << "\n";
        XMLString::release(&message);
        return false;
	}
    catch (...) {
		std::cout << "Unexpected Exception \n" ;
        return false;
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

	return true;
}

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