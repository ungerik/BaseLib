/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



template<typename CharType, int direction>
class AbstractCharIterator : public Enumeration<CharType>::AbstractIteratorImplementation {
public:

	inline AbstractCharIterator(const String* forString, int pos)
		: string(forString)
		, position(pos)
	{
	}

	virtual void next()
	{
		position += direction;
	}

	virtual void previous()
	{
		position -= direction;
	}

	const String* getString() const
	{
		return string;
	}

	int getPosition() const
	{
		return position;
	}

	virtual bool equals(const typename Enumeration<CharType>::AbstractIteratorImplementation* right) const
	{
		const AbstractCharIterator<CharType, direction>* rightIterator = static_cast<const AbstractCharIterator<CharType, direction>*>(right);
		return string == rightIterator->string && position == rightIterator->position;
	}

protected:

	const String* string;
	int position;
};



template<int direction>
class Char8Iterator : public AbstractCharIterator<char8, direction> {
public:

	inline Char8Iterator<direction>(const String* forString, int pos)
		: AbstractCharIterator<char8, direction>(forString, pos)
	{
	}
	
	inline Char8Iterator<direction>(const Char8Iterator<direction>& other)
		: AbstractCharIterator<char8, direction>(other.getString(), other.getPosition())
	{
	}

	inline Char8Iterator& operator =(const Char8Iterator<direction>& right)
	{
		string = right.getString();
		position = right.getPosition();

		return *this;
	}

	virtual Enumeration<char8>::AbstractIteratorImplementation* clone() const
	{
		return new Char8Iterator<direction>(string, position);
	}

	virtual const char8 get() const
	{
		return string->getChar8Array()[position];
	}
};



template<int direction>
class Char16Iterator : public AbstractCharIterator<char16, direction> {
public:

	inline Char16Iterator<direction>(const String* forString, int pos)
		: AbstractCharIterator<char16, direction>(forString, pos)
	{
	}

	inline Char16Iterator<direction>(const Char16Iterator<direction>& other)
		: AbstractCharIterator<char16, direction>(other.getString(), other.getPosition())
	{
	}

	inline Char16Iterator& operator =(const Char16Iterator<direction>& right)
	{
		string = right.getString();
		position = right.getPosition();

		return *this;
	}

	virtual Enumeration<char16>::AbstractIteratorImplementation* clone() const
	{
		return new Char16Iterator<direction>(string, position);
	}

	virtual const char16 get() const
	{
		return string->getChar16Array()[position];
	}
};



public:



class Char8ForwardIterator : public Char8Iterator<+1> {
public:

	inline Char8ForwardIterator(const String* forString, int pos)
		: Char8Iterator<+1>(forString, pos)
	{
	}
	
	inline Char8ForwardIterator(const Char8ForwardIterator& other)
		: Char8Iterator<+1>(other.getString(), other.getPosition())
	{
	}

};



class Char16ForwardIterator : public Char16Iterator<+1> {
public:

	inline Char16ForwardIterator(const String* forString, int pos)
		: Char16Iterator<+1>(forString, pos)
	{
	}
	
	inline Char16ForwardIterator(const Char16ForwardIterator& other)
		: Char16Iterator<+1>(other.getString(), other.getPosition())
	{
	}

};



class Char8ReverseIterator : public Char8Iterator<-1> {
public:

	inline Char8ReverseIterator(const String* forString, int pos)
		: Char8Iterator<-1>(forString, pos)
	{
	}
	
	inline Char8ReverseIterator(const Char8ReverseIterator& other)
		: Char8Iterator<-1>(other.getString(), other.getPosition())
	{
	}

};



class Char16ReverseIterator : public Char16Iterator<-1> {
public:

	inline Char16ReverseIterator(const String* forString, int pos)
		: Char16Iterator<-1>(forString, pos)
	{
	}
	
	inline Char16ReverseIterator(const Char16ReverseIterator& other)
		: Char16Iterator<-1>(other.getString(), other.getPosition())
	{
	}

};



inline Char8ForwardIterator beginChar8() const
{
	return Char8ForwardIterator(this, BEGIN);
}



inline Char16ForwardIterator beginChar16() const
{
	return Char16ForwardIterator(this, BEGIN);
}



inline Char8ForwardIterator endChar8() const
{
	return Char8ForwardIterator(this, END);
}



inline Char16ForwardIterator endChar16() const
{
	return Char16ForwardIterator(this, END);
}



inline Char8ReverseIterator reverseBeginChar8() const
{
	return Char8ReverseIterator(this, reverseBegin());
}



inline Char16ReverseIterator reverseBeginChar16() const
{
	return Char16ReverseIterator(this, reverseBegin());
}



inline Char8ReverseIterator reverseEndChar8() const
{
	return Char8ReverseIterator(this, reverseEnd());
}



inline Char16ReverseIterator reverseEndChar16() const
{
	return Char16ReverseIterator(this, reverseEnd());
}

