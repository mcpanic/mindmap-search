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


	pDoc = parser->getDocument();

	// for the debugging purpose
	//Print();

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

void XercesCXMLParser::Print()
{

	DOMImplementation *pImplement = NULL;
	// these two are needed to display DOM output.
	DOMWriter *pSerializer = NULL;
	XMLFormatTarget *pTarget = NULL;

	// get a serializer, an instance of DOMWriter (the "LS" stands for load-save).
	// mcpanic 8301 XercesString -> XMLString
//	pImplement = DOMImplementationRegistry::getDOMImplementation(XMLString("LS"));
	pImplement = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
	pSerializer = ( (DOMImplementationLS*)pImplement )->createDOMWriter();
	pTarget = new StdOutFormatTarget();
	// set user specified end of line sequence and output encoding
	// mcpanic 8301 XercesString -> XMLString
	pSerializer->setNewLine( XMLString::transcode("\n") );

	// set feature if the serializer supports the feature/mode
	if ( pSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, false) )
	pSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, false);

	if ( pSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, false) )
	pSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, false);

	// turn off serializer "pretty print" option
	if ( pSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, false) )
	pSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, false);

	if ( pSerializer->canSetFeature(XMLUni::fgDOMWRTBOM, false) )
	pSerializer->setFeature(XMLUni::fgDOMWRTBOM, false);

	pSerializer->writeNode(pTarget, *pDoc);

}
