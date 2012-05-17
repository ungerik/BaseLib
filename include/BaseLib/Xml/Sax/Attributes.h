/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_Sax_Attributes_h
#define BaseLib_Xml_Sax_Attributes_h



#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace Xml {
namespace Sax {



using BaseLib::Strings::String;
using BaseLib::Containers::Enumeration;



// shouldReportCharacters
// shouldReportIgnorableWhitespace
// canReportComments

class BL_EXPORT Attributes {
public:

	//Attributes(const unsigned char** atts);
	Attributes(int count, const unsigned char** atts);

	int getIndex(const String& qName) const;
	int getIndex(const String& uri, const String& localName) const;
	inline int getLength() const
	{
		return length;
	}
	String getLocalName(int index) const;
	String getQName(int index) const;
	//String getType(int index) const;
	//String getType(const String& qName) const;
	//String getType(const String& uri, const String& localName) const;
	String getURI(int index) const;
	String getValue(int index) const;
	String getValue(const String& qName) const;
	String getValue(const String& uri, const String& localName) const;

private:

	const unsigned char** attributes;
	int length;



	template<int direction>
	class AbstractAttributeIterator : public Enumeration<String>::AbstractIteratorImplementation {
	public:

		explicit AbstractAttributeIterator<direction>(const Attributes& forAttributes, int fromIndex)
			: attributes(forAttributes)
			, index(fromIndex)
		{
		}

		virtual void next()
		{
			index += direction;
		}

		virtual void previous()
		{
			index -= direction;
		}

		virtual bool equals(const Enumeration<String>::AbstractIteratorImplementation* right) const
		{
			const AbstractAttributeIterator<direction>* rightIterator = static_cast<const AbstractAttributeIterator<direction>*>(right);
			return &attributes == &rightIterator->attributes && index == rightIterator->index;
		}

	protected:

		const Attributes& attributes;
		int index;
	};



	template<int direction>
	class AttributeNameIterator : public AbstractAttributeIterator<direction> {
	public:

		explicit AttributeNameIterator<direction>(const Attributes& forAttributes, int fromIndex)
			: AbstractAttributeIterator<direction>(forAttributes, fromIndex)
		{
		}

		virtual Enumeration<String>::AbstractIteratorImplementation* clone() const
		{
			return new AttributeNameIterator<direction>(attributes, index);
		}

		virtual const String get() const
		{
			return attributes.getQName(index);
		}
	};



	template<int direction>
	class AttributeValueIterator : public AbstractAttributeIterator<direction> {
	public:

		explicit AttributeValueIterator<direction>(const Attributes& forAttributes, int fromIndex)
			: AbstractAttributeIterator<direction>(forAttributes, fromIndex)
		{
		}

		virtual Enumeration<String>::AbstractIteratorImplementation* clone() const
		{
			return new AttributeValueIterator<direction>(attributes, index);
		}

		virtual const String get() const
		{
			return attributes.getValue(index);
		}
	};



public:


	class NamesEnumeration : public Enumeration<String> {
	public:

		NamesEnumeration(const Attributes* forAttributes, bool ownsWrappedContainer = false)
			: Enumeration<String>(ownsWrappedContainer)
			, attributes(forAttributes)
		{
		}

		virtual ~NamesEnumeration()
		{
			if (owner == true)
			{
				delete attributes;
			}
		}

		virtual int getCount() const
		{
			return attributes->getLength();
		}

		virtual Iterator begin() const
		{
			return Iterator(new AttributeNameIterator<+1>(*attributes, 0));
		}

		virtual Iterator end() const
		{
			return Iterator(new AttributeNameIterator<+1>(*attributes, attributes->getLength()));
		}

		virtual ReverseIterator reverseBegin() const
		{
			return Iterator(new AttributeNameIterator<-1>(*attributes, attributes->getLength()-1));
		}

		virtual ReverseIterator reverseEnd() const
		{
			return Iterator(new AttributeNameIterator<-1>(*attributes, -1));
		}

	protected:
		
		const Attributes* attributes;
	};



	class ValuesEnumeration : public Enumeration<String> {
	public:

		ValuesEnumeration(const Attributes* forAttributes, bool ownsWrappedContainer = false)
			: Enumeration<String>(ownsWrappedContainer)
			, attributes(forAttributes)
		{
		}

		virtual ~ValuesEnumeration()
		{
			if (owner == true)
			{
				delete attributes;
			}
		}

		virtual int getCount() const
		{
			return attributes->getLength();
		}

		virtual Iterator begin() const
		{
			return Iterator(new AttributeValueIterator<+1>(*attributes, 0));
		}

		virtual Iterator end() const
		{
			return Iterator(new AttributeValueIterator<+1>(*attributes, attributes->getLength()));
		}

		virtual ReverseIterator reverseBegin() const
		{
			return Iterator(new AttributeValueIterator<-1>(*attributes, attributes->getLength()-1));
		}

		virtual ReverseIterator reverseEnd() const
		{
			return Iterator(new AttributeValueIterator<-1>(*attributes, -1));
		}

	protected:
		
		const Attributes* attributes;
	};

};



} // namespace Sax
} // namespace Xml
} // namespace BaseLib


#endif // #ifndef BaseLib_Xml_Sax_Attributes_h
