/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Reflection_PropertiesTreeIterator_h
#define BaseLib_Reflection_PropertiesTreeIterator_h



#include "BaseLib/Trees/AbstractTreeIterator.h"
#include "BaseLib/Containers/Stack.h"



namespace BaseLib {
namespace Reflection {



using BaseLib::Containers::Stack;
using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;



class BL_EXPORT PropertiesTreeIterator : public BaseLib::Trees::AbstractTreeIterator {

	friend PropertiesTreeIterator;

public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Reflection::PropertiesTreeIterator, BaseLib::Trees::AbstractTreeIterator);

	PropertiesTreeIterator(Object* forObject, const NumberFormat* useNumberFormat);
	PropertiesTreeIterator(const Object* forConstObject, const NumberFormat* useNumberFormat);

	inline bool isObjectConst() const
	{
		return object == NULL;
	}

	inline void makeObjectConst()
	{
		object = NULL;
	}

	virtual AbstractTreeIterator* clone() const;
	virtual bool operator ==(const AbstractTreeIterator& right) const;
	virtual bool isAttribute() const;
	virtual BaseLib::Strings::String getName() const;
	virtual BaseLib::Strings::String getNamespace() const;
	virtual bool hasMetaTag(const BaseLib::Strings::String& metaTag) const;
	virtual bool isReadable() const;
	virtual bool isWriteable() const;
	virtual InputStream* createInputStream() const;
	virtual OutputStream* createOutputStream() const;
	virtual BaseLib::Strings::String getValue() const;
	virtual void setValue(const BaseLib::Strings::String& newValue) const;
	virtual BaseLib::Strings::String getValueOfAttribute(const BaseLib::Strings::String& attributeName) const;
	virtual void setValueOfAttribute(const BaseLib::Strings::String& attributeName, const BaseLib::Strings::String& newValue) const;
	virtual BaseLib::Strings::String getType() const;
	virtual bool isDefaultValue() const;
	virtual void setDefaultValue() const;
	virtual const Enumeration<BaseLib::Strings::String>& getValueRange() const;
	virtual void push();
	virtual void pop(bool restorePosition = true, bool restoreStack = true);
	virtual int getAttributeCount() const; // uses parent-node if current is attribute
	virtual int getAttributePosition() const;
	virtual bool moveToAttribute(int attributePosition);
	virtual bool moveToAttribute(const BaseLib::Strings::String& attributeName);
	virtual bool hasParent() const;
	virtual bool moveToParent();
	virtual int getChildNodeCount() const; // uses parent-node if current is attribute
	virtual int getChildNodePosition() const; // uses parent-node if current is attribute
	virtual bool moveToChildNode(int childPosition); // uses parent-node if current is attribute

private:

	const Object* constObject;
	Object* object;
	const NumberFormat* numberFormat;
	BaseLib::Strings::String currentProperty;
	Stack<BaseLib::Strings::String> stateStack;


};



} // namespace Reflection
} // namespace BaseLib



#endif // #ifndef BaseLib_Reflection_PropertiesTreeIterator_h
