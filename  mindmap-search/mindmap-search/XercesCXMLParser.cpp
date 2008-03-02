#include "StdAfx.h"
#include "XercesCXMLParser.h"
#include "DBEntry.h"

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

bool XercesCXMLParser::OpenFile(string a_szFilename)
{
	m_szFilename = a_szFilename;
	return true;
}


bool XercesCXMLParser::Parse()
{
    try 
	{
        XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch) 
	{
        char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "Error during initialization! :\n" << message << "\n";
        XMLString::release(&message);
        return false;
    }

    XercesDOMParser* parser = new XercesDOMParser();
    parser->setValidationScheme(XercesDOMParser::Val_Auto);  
	//parser->setLoadExternalDTD(true);
    parser->setDoNamespaces(false);
    parser->setDoSchema(true);
    //parser->setValidationSchemaFullChecking(true);

    ErrorHandler* errHandler = (ErrorHandler*) new HandlerBase();
    parser->setErrorHandler(errHandler);

	const char *xmlFile = m_szFilename.c_str();

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

	m_pDoc = parser->getDocument();
	m_pDocument = parser->getDocument();

	Build();

	// for the debugging purpose
//	PrintFile();

/*
	int errorCount = 0;
	errorCount = parser->getErrorCount();

	if (errorCount == 0)
	{
        XERCES_STD_QUALIFIER cout << "\nFinished parsing the memory buffer containing the following "
			<< XERCES_STD_QUALIFIER endl;
	}
*/

    delete parser;
    delete errHandler;

	
	XMLPlatformUtils::Terminate();
	return true;
}


string XercesCXMLParser::GetParentNodeID (DOMNode *node)
{
	char *name;
	DOMNode *parent;
	bool bSuccess = false;

	parent = node->getParentNode();

	if (parent->hasAttributes())
	{
        // get all the attributes of the node
        DOMNamedNodeMap *pAttributes = node->getAttributes();
        int nSize = pAttributes->getLength();
        for(int i=0;i<nSize;++i) 
		{
            DOMAttr *pAttributeNode = (DOMAttr*) pAttributes->item(i);
            // get attribute name
            name = XMLString::transcode(pAttributeNode->getName());
            
			if (strcmp(name, "ID") == 0)
			{
				XMLString::release(&name);  
				// get attribute type
				name = XMLString::transcode(pAttributeNode->getValue());
				bSuccess = true;
				break;
			}
			//XMLString::release(&name);

        }
	}

	if (bSuccess)
		return name;
	else
		return "NONE";
}


int XercesCXMLParser::ProcessParsed(DOMNode *node, bool bPrint)
{
    DOMNode *child;
	EATTRTYPE eAttrType;

    int count = 0;
    if (node) 
	{
        if (node->getNodeType() == DOMNode::ELEMENT_NODE)
		{
            if(bPrint) 
			{

				DBEntry *dbEntry = new DBEntry;

                char *name = XMLString::transcode(node->getNodeName());
                XERCES_STD_QUALIFIER cout <<"----------------------------------------------------------"<<XERCES_STD_QUALIFIER endl;
                XERCES_STD_QUALIFIER cout <<"Encountered Element : "<< name << XERCES_STD_QUALIFIER endl;
     
				dbEntry->SetNodeName (name);

                XMLString::release(&name);

				// Set the parent ID
				dbEntry->SetParentNodeID(GetParentNodeID(node));
			
                if(node->hasAttributes()) 
				{
                    // get all the attributes of the node
                    DOMNamedNodeMap *pAttributes = node->getAttributes();
                    int nSize = pAttributes->getLength();
                    XERCES_STD_QUALIFIER cout <<"\tAttributes" << XERCES_STD_QUALIFIER endl;
                    XERCES_STD_QUALIFIER cout <<"\t----------" << XERCES_STD_QUALIFIER endl;
                    for(int i=0;i<nSize;++i) 
					{
                        DOMAttr *pAttributeNode = (DOMAttr*) pAttributes->item(i);
                        // get attribute name
                        char *name = XMLString::transcode(pAttributeNode->getName());
                        
						if (strcmp(name, "ID") == 0)
						{
							eAttrType = eAttrNodeID;
						}
						else if (strcmp(name, "CREATED") == 0)
						{
							eAttrType = eAttrTimeCreated;
						}
						else if (strcmp(name, "MODIFIED") == 0)
						{
							eAttrType = eAttrTimeModified;
						}
						else if (strcmp(name, "TEXT") == 0)
						{
							eAttrType = eAttrNodeText;
						}
						else
						{
							// do nothing for now
							eAttrType = eAttrOther;
						}

                        XERCES_STD_QUALIFIER cout << "\t" << name << "=";
                        XMLString::release(&name);
                        
                        // get attribute type
                        name = XMLString::transcode(pAttributeNode->getValue());

						if (eAttrType == eAttrNodeID)
						{
							dbEntry->SetNodeID (name);
						}
						else if (eAttrType == eAttrTimeCreated)
						{
							dbEntry->SetTimeCreated (name);
						}
						else if (eAttrType == eAttrTimeModified)
						{
							dbEntry->SetTimeModified (name);
						}
						else if (eAttrType == eAttrNodeText)
						{	
							dbEntry->SetNodeText (name);
						}
						else 
						{
							// do nothing for now
						}
                        XERCES_STD_QUALIFIER cout << name << XERCES_STD_QUALIFIER endl;
                        XMLString::release(&name);
                    }
                }

				dbEntry->PrintNode();
            }
			++count;
		}

        for (child = node->getFirstChild(); child != 0; child=child->getNextSibling())
            count += ProcessParsed(child, bPrint);
    }
    return count;
}


void XercesCXMLParser::Build()
{
    unsigned int elementCount = 0;
    if (m_pDocument) 
	{
        elementCount = ProcessParsed((DOMNode*)m_pDocument->getDocumentElement(), true);
        // test getElementsByTagName and getLength
/*
		XMLCh xa[] = {chAsterisk, chNull};
        if (elementCount != m_pDocument->getElementsByTagName(xa)->getLength()) 
		{
            XERCES_STD_QUALIFIER cout << "\nErrors occurred, element count is wrong\n" << XERCES_STD_QUALIFIER endl;
        }
*/
	}



}

void XercesCXMLParser::PrintFile()
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

	pSerializer->writeNode(pTarget, *m_pDoc);
}

/*
	DOMNamedNodeMap *pNodeMap;

	DOMNode *currentNode;
	DOMElement *pElement = m_pDocument->getDocumentElement();

	// create an iterator to visit all text nodes.
	DOMTreeWalker *iterator = m_pDocument->createTreeWalker(pElement, DOMNodeFilter::SHOW_TEXT, NULL, true);
	// use the tree walker to print out the text nodes.
	for ( currentNode = iterator->nextNode(); currentNode != 0; currentNode = iterator->nextNode() )
	{
		//currentNode->normalize();
		// note: this leaks memory!
		cout << "child  : " << currentNode->hasAttributes() << endl;
		cout << "attr   : " << currentNode->hasChildNodes() << endl;
		cout << "parent : " << currentNode->getParentNode() << endl;
		cout << "child  : " << currentNode->getFirstChild() << endl;
		cout << "sibprev: " << currentNode->getPreviousSibling() << endl;
		cout << "sibnext: " << currentNode->getNextSibling() << endl;
		//cout << "URI    : " << XMLString::transcode(currentNode->getNamespaceURI()) << endl;
		//cout << "prefi  : " << XMLString::transcode(currentNode->getPrefix()) << endl;
		//cout << "local  : " << XMLString::transcode(currentNode->getLocalName()) << endl;


		cout << "name   : " << XMLString::transcode(currentNode->getNodeName()) << endl;
		cout << "type   : " << currentNode->getNodeType() << endl;
		cout << "value  : " << XMLString::transcode(currentNode->getNodeValue()) << endl;
		cout << "text   : " << XMLString::transcode(currentNode->getTextContent()) << endl;
		
		pNodeMap= currentNode->getAttributes();
		if (pNodeMap)
		{
			cout << "leng : " << pNodeMap->getLength() << endl;
			cout << "COLOR: " << pNodeMap->getNamedItem(XMLString::transcode("COLOR")) << endl;
			cout << "CREATED: " << pNodeMap->getNamedItem(XMLString::transcode("CREATED")) << endl;
		}
		cout << endl;
	}
*/	