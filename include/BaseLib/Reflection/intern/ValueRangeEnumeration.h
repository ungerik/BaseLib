/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com 
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_ValueRangeEnumeration_h
#define BaseLib_Reflection_ValueRangeEnumeration_h



//#include "BaseLib/Strings/String.h"
//#include "BaseLib/Containers/Enumeration.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Enumeration;



template<class P>
class ValueRangeEnumeration : public Enumeration<BaseLib::Strings::String> {
public:

	template<int direction>
	class ValueIterator : public AbstractIteratorImplementation {
	public:

		ValueIterator(const P* forProperty, int i)
			: property(forProperty)
			, index(i)
		{
		}

		virtual AbstractIteratorImplementation* clone() const
		{
			return new ValueIterator<direction>(property, index);
		}

		virtual const BaseLib::Strings::String get() const
		{
			static BaseLib::Strings::String value = (index == 0) ?
				BaseLib::Strings::String::createFrom(property->getMinimum()) :
				BaseLib::Strings::String::createFrom(property->getMaximum());

			return value;
		}

		virtual void next()
		{
			if (direction == +1)
			{
				if (index <= 1) ++index;
			}
			else
			{
				if (index >= 0) --index;
			}
		}

		virtual void previous()
		{
			if (direction == +1)
			{
				if (index >= 0) --index;
			}
			else
			{
				if (index <= 1) ++index;
			}
		}

		virtual bool equals(const AbstractIteratorImplementation* right) const
		{
			const ValueIterator<direction>* rightIterator = static_cast<const ValueIterator<direction>*>(right);
			return property == rightIterator->property && index == rightIterator->index;
		}

	protected:

		const P* property;
		int index;
	};

	ValueRangeEnumeration(bool ownsWrappedContainer = false)
		: Enumeration<BaseLib::Strings::String>(ownsWrappedContainer)
		, property(NULL)
	{
	}
	
	virtual ~ValueRangeEnumeration()
	{
		if (owner == true)
		{
			delete property;
		}
	}

	void setProperty(const P* newProperty)
	{
		property = newProperty;
	}

	virtual bool isEmpty() const
	{
		return false;
	}

	virtual int getCount() const
	{
		return 2;
	}

	virtual Iterator begin() const
	{
		return Iterator(new ValueIterator<+1>(property, 0));
	}

	virtual Iterator end() const
	{
		return Iterator(new ValueIterator<+1>(property, 2));
	}

	virtual ReverseIterator reverseBegin() const
	{
		return ReverseIterator(new ValueIterator<-1>(property, 1));
	}

	virtual ReverseIterator reverseEnd() const
	{
		return ReverseIterator(new ValueIterator<-1>(property, -1));
	}

protected:

	const P* property;
};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_ValueRangeEnumeration_h
