/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Strings_StringTokenizer_h
#define BaseLib_Strings_StringTokenizer_h



#include "BaseLib/Strings/String.h"
#include "BaseLib/Strings/Manipulation.h"



namespace BaseLib {
namespace Strings {



using BaseLib::Functors::Enumerator;



/**
Tokenizes a string.

@see String
*/
class BL_EXPORT StringTokenizer {
public:

	StringTokenizer(const String& stringToTokenize = Empty(), const String& tokenDelimiters = defaultTokenDelimiters, int startPosition = 0, bool reportEmptyTokens = false);

	/**
	Counts the tokens from the current position, but does not change the position.
	@see countTokensCaseInsensitive()
	*/
	int	countTokens();

	/**
	Returns if next token is available.
	@see hasPreviousToken(), hasNextTokenCaseInsensitive()
	*/
	bool hasNextToken();

	/**
	Returns if previous token is available.
	@see hasNextToken(), hasPreviousTokenCaseInsensitive()
	*/
	bool hasPreviousToken();

	/**
	Returns the next token.
	@see previousToken(), hasNextToken(), nextTokenCaseInsensitive()
	*/
	String nextToken(bool movePosition = true);

	/**
	Returns the previous token.
	@see nextToken(), hasPreviousToken(), previousTokenCaseInsensitive()
	*/
	String previousToken(bool movePosition = true);

	/**
	Counts the tokens from the current position (case insensitive), but does not change the position.
	@see countTokens()
	*/
	int	countTokensCaseInsensitive();

	/**
	Returns if next token is available (case insensitive).
	@see hasPreviousTokenCaseInsensitive(), hasNextToken()
	*/
	bool hasNextTokenCaseInsensitive();

	/**
	Returns if previous token is available (case insensitive).
	@see hasNextTokenCaseInsensitive(), hasPreviousToken()
	*/
	bool hasPreviousTokenCaseInsensitive();

	/**
	Returns the next token (case insensitive).
	@see previousTokenCaseInsensitive(), hasNextTokenCaseInsensitive(), nextToken()
	*/
	String nextTokenCaseInsensitive(bool movePosition = true);

	/**
	Returns the previous token (case insensitive).
	@see nextTokenCaseInsensitive(), hasPreviousTokenCaseInsensitive(), previousToken()
	*/
	String previousTokenCaseInsensitive(bool movePosition = true);

	/**
	Returns the current position in the string to tokenize.
	@see setPosition()
	*/
	inline int getPosition() const
	{
		return position;
	}

	/**
	Sets the current position in the string to tokenize.
	@see getPosition()
	*/
	void setPosition(int newPosition);

	/**
	Returns the delimiter characters used for tokenizing.
	@see setDelimiters
	*/
	inline const String& getDelimiters()
	{
		return delimiters;
	}

	/**
	Returns the delimiter characters used for tokenizing.
	@see getDelimiters
	*/
	void setDelimiters(const String& newDelimiters);

	/**
	Returns the string to tokenize.
	@see setString()
	*/
	inline const String& getString()
	{
		return string;
	}

	/**
	Sets the string to tokenize and does not change the current position.
	@see getString()
	*/
	void setString(const String& newStringToTokenize);

	/**
	Returns the sub-string from the current position to the end-position.
	*/
	String readToEnd() const;

	/**
	Enumerates the tokens to an enumerator.
	*/
	void tokenizeTo(const Enumerator<String>& enumerator);

	/**
	Enumerates the tokens to an enumerator.
	*/
	template<template<typename> class E>
	inline void tokenizeTo()
	{
		tokenizeTo(E<String>());
	}

	/**
	Enumerates the tokens to an enumerator.
	*/
	template<template<class, typename> class E, class C>
	inline void tokenizeTo(C& other)
	{
		tokenizeTo(E<C, String>(other));
	}

	/**
	Enumerates the tokens to a container.
	@code
	Array<String> stringArray;
	StringTokenizer("Hello World!").tokenizeTo(stringArray);
	@endcode
	*/
	template<class Container>
	void tokenizeTo(Container& container)
	{
		while (hasNextToken() == true)
		{
			container += nextToken();
		}
	}

	/**
	@todo doku
	*/
	inline bool isReportingEmptyTokens() const
	{
		return reportingEmptyTokens;
	}

	/**
	@todo doku
	*/
	inline void setReportingEmptyTokens(bool reportEmptyTokens)
	{
		reportingEmptyTokens = reportEmptyTokens;
	}

protected:
	String string;
	String delimiters;
	int position;
	bool reportingEmptyTokens;
};




} // namespace Strings
} // namespace BaseLib



#endif // #ifndef BaseLib_Strings_StringTokenizer_h