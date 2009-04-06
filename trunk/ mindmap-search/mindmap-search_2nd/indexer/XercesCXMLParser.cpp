#include "StdAfx.h"
#include "XercesCXMLParser.h"

using namespace std;

XercesCXMLParser::XercesCXMLParser()
{

}

XercesCXMLParser::~XercesCXMLParser()
{
}

void XercesCXMLParser::Release()
{
	delete m_pParser;
    delete m_pErrHandler;

	XMLPlatformUtils::Terminate();

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

	m_pParser = new XercesDOMParser();
    m_pErrHandler = (ErrorHandler*) new HandlerBase();

    m_pParser->setValidationScheme(XercesDOMParser::Val_Auto);  
	
    m_pParser->setDoNamespaces(false);
    m_pParser->setDoSchema(true);
    
    m_pParser->setErrorHandler(m_pErrHandler);

	const char *xmlFile = m_szFilename.c_str();

    try 
	{
        m_pParser->parse(xmlFile);
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

	m_pDocument = m_pParser->getDocument();

	return true;
}

// Transform parsed node data into DBEntry format
int XercesCXMLParser::ProcessParsed(DOMNode *node, bool bPrint, vector<DBIndexEntity> &a_vNodes)
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

				DBIndexEntity *dbEntry = new DBIndexEntity;

                char *name = XMLString::transcode(node->getNodeName());
                XERCES_STD_QUALIFIER cout <<"----------------------------------------------------------"<<XERCES_STD_QUALIFIER endl;
                XERCES_STD_QUALIFIER cout <<"Encountered Element : "<< name << XERCES_STD_QUALIFIER endl;
     
				dbEntry->SetNodeName(name);

                if(node->hasAttributes()) 
				{
                    // get all the attributes of the node
                    DOMNamedNodeMap *pAttributes = node->getAttributes();
                    int nSize = pAttributes->getLength();
                    XERCES_STD_QUALIFIER cout <<"\tAttributes" << XERCES_STD_QUALIFIER endl;
                    XERCES_STD_QUALIFIER cout <<"\t----------" << XERCES_STD_QUALIFIER endl;
                    for (int i=0;i<nSize;++i) 
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
							eAttrType = eAttrWord;
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

						if (eAttrType == eAttrIndexID)
						{
							dbEntry->SetIndexID(name);
						}
						else if (eAttrType == eAttrWord)
						{	
							dbEntry->SetWord(name);
						}
                        XERCES_STD_QUALIFIER cout << name << XERCES_STD_QUALIFIER endl;
                        XMLString::release(&name);
                    }
                }

				// Add the entry into the vector 
				a_vNodes.push_back (*dbEntry);
            }
			++count;
		}

        for (child = node->getFirstChild(); child != 0; child=child->getNextSibling())
            count += ProcessParsed(child, bPrint, a_vNodes);

    }
    return count;
}


void XercesCXMLParser::Build(vector<DBIndexEntity> &a_vNodes)
{
    unsigned int elementCount = 0;
    if (m_pDocument) 
	{
        elementCount = ProcessParsed((DOMNode*)m_pDocument->getDocumentElement(), true, a_vNodes);
	}
}

void XercesCXMLParser::PrintFile()
{

	DOMImplementation *pImplement = NULL;
	// these two are needed to display DOM output.
	DOMWriter *pSerializer = NULL;
	XMLFormatTarget *pTarget = NULL;

	// get a serializer, an instance of DOMWriter (the "LS" stands for load-save).
	pImplement = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
	pSerializer = ( (DOMImplementationLS*)pImplement )->createDOMWriter();
	pTarget = new StdOutFormatTarget();
	// set user specified end of line sequence and output encoding
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

	pSerializer->writeNode(pTarget, *m_pDocument);
}