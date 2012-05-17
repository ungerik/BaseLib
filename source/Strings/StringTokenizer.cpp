/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/StringTokenizer.h"



namespace BaseLib {
namespace Strings {



StringTokenizer::StringTokenizer(const String& stringToTokenize, const String& tokenDelimiters, int startPosition, bool reportEmptyTokens)
	: string(stringToTokenize)
	, delimiters(tokenDelimiters)
	, position(startPosition)
	, reportingEmptyTokens(reportEmptyTokens)
{
}



int	StringTokenizer::countTokens()
{
	int count = 0;
	int oldPosition = position;
	while (hasNextToken() == true)
	{
		nextToken();
		++count;
	}
	position = oldPosition;
	return count;
}



bool StringTokenizer::hasNextToken()
{
	if (reportingEmptyTokens == true)
	{
		return 
			position >= 0 &&
			position < string.getLength()-1;
	}
	else
	{
		return 
			position >= 0 &&
			position < string.getLength() &&
			string.findFirstNotOf(delimiters, position) != String::END;
	}
}



bool StringTokenizer::hasPreviousToken()
{
	if (reportingEmptyTokens == true)
	{
		return position > 0;
	}
	else
	{
		return
			(position == String::END || position > 0) &&
			position <= string.getLength() &&
			string.findLastNotOf(delimiters, 0, position) != String::END;
	}
}



String StringTokenizer::nextToken(bool movePosition)
{
	if (position < 0 || position >= string.getLength())
	{
		return Empty();
	}

	int start;
	if (reportingEmptyTokens == false)
	{
		start = string.findFirstNotOf(delimiters, position);
	}
	else
	{
		start = delimiters.findFirst(string[position]) != String::END ? position + 1 : position;
	}
	if (start < 0 || start >= string.getLength())
	{
		return Empty();
	}

	int end = string.findFirstOf(delimiters, start);
	if (movePosition == true)
	{
		position = end;
	}
	if (end == String::END)
	{
		end = string.getLength();
	}

	return string.subString(start, end - start);
}



String StringTokenizer::previousToken(bool movePosition)
{
	if (position <= 0 || position > string.getLength())
	{
		return Empty();
	}

	int end = reportingEmptyTokens == true ? position : string.findLastNotOf(delimiters, 0, position) + 1;
	if (end == 0)
	{
		end = position;
	}
	int start = reportingEmptyTokens == true ? position - 1 : string.findLastOf(delimiters, 0, end) + 1;
	if (movePosition == true)
	{
		position = start;
	}

	return string.subString(start, end - start);
}



int	StringTokenizer::countTokensCaseInsensitive()
{
	int count = 0;
	int oldPosition = position;
	while (hasNextTokenCaseInsensitive() == true)
	{
		nextTokenCaseInsensitive();
		++count;
	}
	position = oldPosition;
	return count;
}



bool StringTokenizer::hasNextTokenCaseInsensitive()
{
	if (reportingEmptyTokens == true)
	{
		return 
			position >= 0 &&
			position < string.getLength()-1;
	}
	else
	{
		return
			position >= 0 &&
			position < string.getLength() &&
			string.findFirstNotOfCaseInsensitive(delimiters, position) != String::END;
	}
}



bool StringTokenizer::hasPreviousTokenCaseInsensitive()
{
	if (reportingEmptyTokens == true)
	{
		return position > 0;
	}
	else
	{
		return
			(position == String::END || position > 0) &&
			position <= string.getLength() &&
			string.findLastNotOfCaseInsensitive(delimiters, 0, position) != String::END;
	}
}



String StringTokenizer::nextTokenCaseInsensitive(bool movePosition)
{
	if (position == String::END || position >= string.getLength())
	{
		return Empty();
	}

	int start;
	if (reportingEmptyTokens == false)
	{
		start = string.findFirstNotOfCaseInsensitive(delimiters, position);
	}
	else
	{
		start = delimiters.findFirstCaseInsensitive(string[position]) != String::END ? position + 1 : position;
	}


	int end = string.findFirstOfCaseInsensitive(delimiters, start + 1);
	if (movePosition == true)
	{
		position = reportingEmptyTokens == true && end == position ? position+1 : end;
	}
	if (end == String::END)
	{
		end = string.getLength();
	}

	return string.subString(start, end - start);
}



String StringTokenizer::previousTokenCaseInsensitive(bool movePosition)
{
	if (position <= 0 || position > string.getLength())
	{
		return Empty();
	}

	int end = reportingEmptyTokens == true ? position : string.findLastNotOfCaseInsensitive(delimiters, 0, position) + 1;
	if (end == 0)
	{
		end = position;
	}
	int start = reportingEmptyTokens == true ? position - 1 : string.findLastOfCaseInsensitive(delimiters, 0, end) + 1;
	if (movePosition == true)
	{
		position = start;
	}

	return string.subString(start, end - start);
}



void StringTokenizer::setPosition(int newPosition)
{
	BL_ASSERT(newPosition >= -1);
	position = newPosition;
}



void StringTokenizer::setDelimiters(const String& newDelimiters)
{
	delimiters = newDelimiters;
}



void StringTokenizer::setString(const String& newStringToTokenize)
{
	string = newStringToTokenize;
}



String StringTokenizer::readToEnd() const
{
	return string.subString(position);
}



void StringTokenizer::tokenizeTo(const Enumerator<String>& enumerator)
{
	while (hasNextToken() == true && enumerator.stop() == false)
	{
		enumerator.enumerate(nextToken());
	}
}



} // namespace Strings
} // namespace BaseLib
