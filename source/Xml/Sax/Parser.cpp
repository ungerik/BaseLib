/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Xml/Sax/Parser.h"
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include "BaseLib/Xml/Sax/Handler.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Files/LocalFile.h"



namespace BaseLib {
namespace Xml {
namespace Sax {



using BaseLib::Files::LocalFile;
using namespace BaseLib::ErrorHandling;



Parser::Parser(const String& fileName)
	: reportingCharacters(true)
	, reportingIgnorableWhitespace(false)
	, context(xmlCreateFileParserCtxt(fileName.getChar8Array()))
	, saxHandler(NULL)
{
	if (LocalFile::exists(fileName) == true)
	{
		initHandler();
	}
	else
	{
		ioError("File '" + fileName + "' not found!" ERROR_AT);
	}
}



Parser::Parser(const void* buffer, int byteSize)
	: reportingCharacters(true)
	, reportingIgnorableWhitespace(false)
	, context(xmlCreateMemoryParserCtxt(static_cast<const char*>(buffer), byteSize))
	, saxHandler(NULL)
{
	initHandler();
}



Parser::~Parser()
{
	delete saxHandler;
    xmlFreeParserCtxt(context);
}



void Parser::initHandler()
{
	saxHandler = new xmlSAXHandler();
	memset(saxHandler, 0, sizeof(xmlSAXHandler));
	saxHandler->startDocument = reinterpret_cast<startDocumentSAXFunc>(&Parser::startDocument);
	saxHandler->endDocument = reinterpret_cast<endDocumentSAXFunc>(&Parser::endDocument);
	saxHandler->startElementNs = reinterpret_cast<startElementNsSAX2Func>(&Parser::startElementNs);
	saxHandler->endElementNs = reinterpret_cast<endElementNsSAX2Func>(&Parser::endElementNs);
	//saxHandler->cdataBlock = reinterpret_cast<cdataBlockSAXFunc>(&Parser::cdataBlock);
	if (reportingCharacters == true) saxHandler->characters = reinterpret_cast<charactersSAXFunc>(&Parser::characters);
	if (reportingIgnorableWhitespace == true) saxHandler->ignorableWhitespace = reinterpret_cast<ignorableWhitespaceSAXFunc>(&Parser::ignorableWhitespace);
	saxHandler->processingInstruction = reinterpret_cast<processingInstructionSAXFunc>(&Parser::processingInstruction);
	saxHandler->comment = reinterpret_cast<commentSAXFunc>(&Parser::comment);
	saxHandler->warning = reinterpret_cast<warningSAXFunc>(&Parser::warning);
	saxHandler->error = reinterpret_cast<errorSAXFunc>(&Parser::error);
	saxHandler->fatalError = reinterpret_cast<fatalErrorSAXFunc>(&Parser::fatalError);
}



void Parser::setReportingCharacters(bool shouldReportCharacters)
{
	reportingCharacters = shouldReportCharacters;
	saxHandler->characters = (reportingCharacters == true) ? reinterpret_cast<charactersSAXFunc>(&Parser::characters) : NULL;
}



void Parser::setReportingIgnorableWhitespace(bool shouldReportIgnorableWhitespace)
{
	reportingIgnorableWhitespace = shouldReportIgnorableWhitespace;
	saxHandler->ignorableWhitespace = (reportingIgnorableWhitespace == true) ? reinterpret_cast<ignorableWhitespaceSAXFunc>(&Parser::ignorableWhitespace) : NULL;
}



bool Parser::parse(Handler& handler)
{
	context->_private = &handler;

	xmlSAXHandler* originalSAXHandler = context->sax;
	context->sax = saxHandler;

	try
	{
		xmlParseDocument(context);
		context->sax = originalSAXHandler;
		return true;
	}
	/*catch(const std::exception& ex)
	{
		context->sax = originalSAXHandler;
		resultError(ex.what() + ERROR_AT);
	}*/
	catch(...)
	{
		context->sax = originalSAXHandler;
		//resultError("Unknown exception in xmlParseDocument()!" ERROR_AT);
		return false;
	}

	/*
    if(context->myDoc != NULL )
    {
		xmlFreeDoc(context->myDoc);
    }
	*/
}



inline Handler* getHandler(void *ctx)
{
	return static_cast<Handler*>(static_cast<xmlParserCtxt*>(ctx)->_private);
}


void Parser::startDocument(void *ctx)
{
	getHandler(ctx)->startDocument();
}



void Parser::endDocument(void *ctx)
{
	getHandler(ctx)->endDocument();
}



void Parser::startElementNs(void *ctx, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI, int nb_namespaces, const xmlChar **namespaces, int nb_attributes, int nb_defaulted, const xmlChar **attributes)
{
	String uri = (URI != NULL) ? reinterpret_cast<const char8 *>(URI) : "";
	String localName = (localname != NULL) ? reinterpret_cast<const char8 *>(localname) : "";
	String qName = (URI != NULL) ? uri + ':' + localName : localName;
	getHandler(ctx)->startElement(uri, localName, qName, Attributes(nb_attributes, attributes));
}



void Parser::endElementNs(void *ctx, const xmlChar *localname, const xmlChar *prefix, const xmlChar *URI)
{
	String uri = (URI != NULL) ? reinterpret_cast<const char8 *>(URI) : "";
	String localName = (localname != NULL) ? reinterpret_cast<const char8 *>(localname) : "";
	String qName = (URI != NULL) ? uri + ':' + localName : localName;
	getHandler(ctx)->endElement(uri, localName, qName);
}



void Parser::cdataBlock(void *ctx, const unsigned char *value, int len)
{
	getHandler(ctx)->cdataBlock(String(reinterpret_cast<const char8 *>(value), len));
}



void Parser::characters(void *ctx, const xmlChar *ch, int len)
{
	getHandler(ctx)->characters(String(reinterpret_cast<const char8 *>(ch), len));
}



void Parser::ignorableWhitespace(void *ctx, const xmlChar *ch, int len)
{
	getHandler(ctx)->ignorableWhitespace(String(reinterpret_cast<const char8 *>(ch), len));
}



void Parser::processingInstruction(void *ctx, const xmlChar *target, const xmlChar *data)
{
	getHandler(ctx)->processingInstruction(String(reinterpret_cast<const char8 *>(target)), String(reinterpret_cast<const char8 *>(data)));
}



void Parser::comment(void *ctx, const xmlChar *value)
{
	getHandler(ctx)->comment(String(reinterpret_cast<const char8 *>(value)));
}



void Parser::warning(void *ctx, const char *msg, ...)
{
	getHandler(ctx)->warning(msg, -1, -1);
}



void Parser::error(void *ctx, const char *msg, ...)
{
	getHandler(ctx)->error(msg, -1, -1);
}



void Parser::fatalError(void *ctx, const char *msg, ...)
{
	getHandler(ctx)->fatalError(msg, -1, -1);
}






} // namespace Sax
} // namespace Xml
} // namespace BaseLib
