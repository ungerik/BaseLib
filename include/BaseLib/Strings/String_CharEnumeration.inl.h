/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



template<typename CharType, template<int direction> class IteratorType>
class CharEnumeration : public Enumeration<CharType> {
public:

	#ifdef BL_COMPILER_GCC
		class Iterator;
		class ReverseIterator;
		class AbstractIteratorImplementation;
	#endif

	inline explicit CharEnumeration(const String* forString, bool ownsWrappedContainer = false)
		: Enumeration<CharType>(ownsWrappedContainer)
		, string(forString)
	{
	}

	virtual ~CharEnumeration()
	{
		if (owner == true)
		{
			delete string;
		}
	}

	virtual bool isEmpty() const
	{
		return string->isEmpty();
	}

	virtual int getCount() const
	{
		return string->getLength();
	}

	virtual Iterator begin() const
	{
		return Iterator(new IteratorType<+1>(string, 0));
	}

	virtual Iterator end() const
	{
		return Iterator(new IteratorType<+1>(string, string->getLength()));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new IteratorType<-1>(string, string->getLength()-1));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new IteratorType<-1>(string, -1));
	}

protected:
	
	const String* string;
};



public:



inline const Enumeration<char8>* createChar8Enumeration() const
{
	return new CharEnumeration<char8, Char8Iterator>(this);
}



inline const Enumeration<char16>* createChar16Enumeration() const
{
	return new CharEnumeration<char16, Char16Iterator>(this);
}
