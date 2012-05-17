/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_Sax_Parser_h
#define BaseLib_Xml_Sax_Parser_h



#include "BaseLib/Xml/Sax/Handler.h"


struct _xmlParserCtxt;
struct _xmlSAXHandler;



namespace BaseLib {
namespace Xml {
namespace Sax {



using namespace BaseLib::Strings;



class BL_EXPORT Parser {
public:

	Parser(const String& fileName);
	Parser(const void* buffer, int byteSize);
	//Parser(const InputStream& inputStream);

	~Parser();

	inline int isReportingCharacters() const
	{
		return reportingCharacters;
	}
	void setReportingCharacters(bool shouldReportCharacters);

	inline int isReportingIgnorableWhitespace() const
	{
		return reportingIgnorableWhitespace;
	}
	void setReportingIgnorableWhitespace(bool shouldReportIgnorableWhitespace);

	inline bool isReportingComments()
	{
		return true;
	}

	bool parse(Handler& handler);

private:

	bool reportingCharacters;
	bool reportingIgnorableWhitespace;
	_xmlParserCtxt* context;
	_xmlSAXHandler* saxHandler;

	void initHandler();

	static void __cdecl startDocument(void *ctx);
	static void __cdecl endDocument(void *ctx);
	static void __cdecl startElementNs(void *ctx, const unsigned char * localname, const unsigned char *prefix, const unsigned char *URI, int nb_namespaces, const unsigned char **namespaces, int nb_attributes, int nb_defaulted, const unsigned char **attributes);
	static void __cdecl endElementNs(void *ctx,	const unsigned char * localname, const unsigned char *prefix, const unsigned char *URI);

	static void __cdecl cdataBlock(void *ctx, const unsigned char *value, int len);
	static void __cdecl characters(void *ctx, const unsigned char *ch, int len);
	static void __cdecl ignorableWhitespace(void *ctx, const unsigned char *ch, int len);
	static void __cdecl processingInstruction(void *ctx, const unsigned char *target, const unsigned char *data);
	static void __cdecl comment(void *ctx, const unsigned char *value);
	static void __cdecl warning(void *ctx, const char *msg, ...);
	static void __cdecl error(void *ctx, const char *msg, ...);
	static void __cdecl fatalError(void *ctx, const char *msg, ...);
};



} // namespace Sax
} // namespace Xml
} // namespace BaseLib


#endif // #ifndef BaseLib_Xml_Sax_Parser_h
