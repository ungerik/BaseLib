/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Strings/EmptyStringImplementation.h"
#include "BaseLib/Strings/Char8StringImplementation.h"
#include "BaseLib/Strings/Char16StringImplementation.h"



namespace BaseLib {
namespace Strings {



AbstractStringImplementation::Factory::~Factory()
{
}



AbstractStringImplementation* AbstractStringImplementation::Factory::create(StringEncoding stringEncoding)
{
	#ifdef BL_NO_EMPTY_STRING_OPTIMIZATION
		if (stringEncoding == CHAR8_ENCODING)
		{
			return new Char8StringImplementation(0);
		}
		else
		{
			return new Char16StringImplementation(0);
		}
	#else
		return stringEncoding == CHAR8_ENCODING ? EmptyStringImplementation::getChar8Instance() : EmptyStringImplementation::getChar16Instance();
	#endif
}


AbstractStringImplementation* AbstractStringImplementation::Factory::create(StringEncoding stringEncoding, int length, bool emptyOptimization)
{
	#ifdef BL_NO_EMPTY_STRING_OPTIMIZATION
		emptyOptimization = false;
	#endif

	if (length == 0 && emptyOptimization == true)
	{
		return create(stringEncoding);
	}
	else
	{
		if (stringEncoding == CHAR8_ENCODING)
		{
			return new Char8StringImplementation(length);
		}
		else
		{
			return new Char16StringImplementation(length);
		}
	}
}



// Moved to BaseLib.cpp because of initialization order:
//AbstractStringImplementation::Factory AbstractStringImplementation::defaultFactory;
//AbstractStringImplementation::Factory* AbstractStringImplementation::factory = getDefaultFactory();



AbstractStringImplementation::Factory* AbstractStringImplementation::getDefaultFactory()
{
	return &defaultFactory;
}



AbstractStringImplementation::Factory* AbstractStringImplementation::getFactory()
{
	return factory;
}



void AbstractStringImplementation::setFactory(Factory* newFactory)
{
	factory = newFactory;
}



// AbstractStringImplementation:



AbstractStringImplementation::AbstractStringImplementation()
	: referenceCount(1)
{
}



AbstractStringImplementation::~AbstractStringImplementation()
{
}



AbstractStringImplementation* AbstractStringImplementation::getUnsharedInstance()
{
	BL_ASSERT(referenceCount > 0);
	if (referenceCount == 1)
	{
		return this;
	}
	else
	{
		--referenceCount;
		return clone();
	}
}



AbstractStringImplementation* AbstractStringImplementation::getUnsharedInstance(int start, int length)
{
	BL_ASSERT(referenceCount > 0);
	if (referenceCount == 1)
	{
		if (start != 0)
		{
			remove(0, start);
		}
		if (length != getLength())
		{
			setLength(length);
		}
		return this;
	}
	else
	{
		--referenceCount;
		return clone(start, length);
	}
}



void AbstractStringImplementation::addReference()
{
	++referenceCount;
}



void AbstractStringImplementation::releaseReference()
{
	BL_ASSERT(referenceCount > 0);
	--referenceCount;
	if (referenceCount == 0)
	{
		delete this;
	}
}



} // namespace Strings
} // namespace BaseLib
