/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Strings/String.h



class BL_EXPORT ConstChar {
public:

	ConstChar(const String& newString, int newPosition)
		: string(newString), position(newPosition)
	{
	}

	inline operator char8() const
	{
		return string.getChar8(position);
	}

	inline operator char16() const
	{
		return string.getChar16(position);
	}

	inline operator char32() const
	{
		return string.getChar32(position);
	}

	inline bool operator ==(const Char& right) const
	{
		return string.getChar32(position) == right.operator char32();
	}

	inline bool operator ==(const ConstChar& right) const
	{
		return string.getChar32(position) == right.operator char32();
	}

	inline bool operator ==(char8 right) const
	{
		return string.getChar8(position) == right;
	}

	inline bool operator ==(char16 right) const
	{
		return string.getChar16(position) == right;
	}

	inline bool operator ==(char32 right) const
	{
		return string.getChar32(position) == right;
	}

	template<class T>
	inline bool operator !=(const T& right) const
	{
		return !operator ==(right);
	}

	inline bool operator <(const Char& right) const
	{
		return string.getChar32(position) < right.operator char32();
	}

	inline bool operator <(const ConstChar& right) const
	{
		return string.getChar32(position) < right.operator char32();
	}

	inline bool operator <(char8 right) const
	{
		return string.getChar8(position) < right;
	}

	inline bool operator <(char16 right) const
	{
		return string.getChar16(position) < right;
	}

	inline bool operator <(char32 right) const
	{
		return string.getChar32(position) < right;
	}

	inline bool operator >(const Char& right) const
	{
		return string.getChar32(position) > right.operator char32();
	}

	inline bool operator >(const ConstChar& right) const
	{
		return string.getChar32(position) > right.operator char32();
	}

	inline bool operator >(char8 right) const
	{
		return string.getChar8(position) > right;
	}

	inline bool operator >(char16 right) const
	{
		return string.getChar16(position) > right;
	}

	inline bool operator >(char32 right) const
	{
		return string.getChar32(position) > right;
	}

	inline const String& getString() const
	{
		return string;
	}

	inline int getPosition() const
	{
		return position;
	}

private:
	const String& string;
	const int position;
};
