/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_AbstractTreeIterator_h
#define BaseLib_Trees_AbstractTreeIterator_h



#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Containers/Enumeration.h"
//#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Reflection/Object.h"



namespace BaseLib {
namespace Trees {



using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
using BaseLib::Strings::String;
using BaseLib::Containers::Enumeration;
using BaseLib::Functors::Enumerator;



class BL_EXPORT AbstractTreeIterator : public BaseLib::Reflection::Object {
public:

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Trees::AbstractTreeIterator);

	virtual ~AbstractTreeIterator();

	virtual AbstractTreeIterator* clone() const = 0;

	// Compare:

	virtual bool operator ==(const AbstractTreeIterator& right) const = 0;

	inline bool operator !=(const AbstractTreeIterator& right) const
	{
		return !operator ==(right);
	}

	// Info:

	virtual bool isAttribute() const = 0;
	virtual String getName() const = 0;
	virtual String getNamespace() const = 0;
	virtual bool hasMetaTag(const String& metaTag) const;

	// IO:

	virtual bool isReadable() const = 0;
	virtual bool isWriteable() const = 0;

	virtual InputStream* createInputStream() const = 0;
	virtual OutputStream* createOutputStream() const = 0;

	virtual String getValue() const = 0; // no error not readable
	virtual void setValue(const String& newValue) const = 0; // no error if not writeable
	virtual String getValueOfAttribute(int attributePosition) const; // no error if attribute doesn't exist
	virtual void setValueOfAttribute(int attributePosition, const String& newValue) const; // no error if attribute doesn't exist
	virtual String getValueOfAttribute(const String& attributeName) const; // no error if attribute doesn't exist
	virtual void setValueOfAttribute(const String& attributeName, const String& newValue) const; // no error if attribute doesn't exist

	virtual String getType() const;
	virtual bool isDefaultValue() const;
	virtual void setDefaultValue() const;
	virtual const Enumeration<String>& getValueRange() const;
	virtual String getPath() const;

	// Tree navigation:

	virtual void push() = 0;
	virtual void pop(bool restorePosition = true, bool restoreStack = true) = 0;
	virtual bool moveTo(const String& path);

	// Linear node-position:
	virtual int getNodePosition() const; // uses parent-node if current is attribute
	virtual bool moveToNodePosition(int nodePosition);
	virtual bool moveToNextNode(); // uses parent-node if current is attribute
	virtual bool moveToPreviousNode(); // uses parent-node if current is attribute

	// Attributes:
	virtual bool hasAttribute(const String& attributeName) const; // uses parent-node if current is attribute
	virtual int getAttributeCount() const = 0; // uses parent-node if current is attribute
	virtual int getAttributePosition() const = 0;
	virtual bool moveToAttribute(int attributePosition) = 0;
	virtual bool moveToAttribute(const String& attributeName);
	virtual bool moveToNextAttribute();
	virtual bool moveToPreviousAttribute();
	virtual void enumAttributeNames(const Enumerator<String>& enumerator) const;

	// Parents:
	virtual bool hasParent() const = 0;
	virtual int getParentCount() const;
	virtual bool moveToParent() = 0;
	virtual bool moveToParent(int parentGeneration);
	virtual bool moveToParent(const String& parentName, int count = 1);
	virtual bool moveToParentOrSelf(const String& parentOrSelfName);
	virtual void moveToRootNode();

	// Children:
	virtual bool canHaveChildNodes() const;
	virtual bool hasChildNodes() const;
	virtual bool hasChildNode(const String& childName) const; // uses parent-node if current is attribute
	virtual int getChildNodeCount() const = 0; // uses parent-node if current is attribute
	virtual int getChildNodePosition() const = 0; // uses parent-node if current is attribute
	virtual bool moveToChildNode(int childPosition = 0) = 0; // uses parent-node if current is attribute
	virtual bool moveToChildNode(const String& childName); // uses parent-node if current is attribute
	virtual void enumChildNodeNames(const Enumerator<String>& enumerator) const;

	// Siblings:
	virtual bool hasNextNodeSibling() const; // uses parent-node if current is attribute
	virtual bool moveToNextNodeSibling(int count = 1); // uses parent-node if current is attribute
	virtual bool moveToNextNodeSibling(const String& siblingName, int count = 1); // uses parent-node if current is attribute
	virtual bool hasPreviousNodeSibling() const; // uses parent-node if current is attribute
	virtual bool moveToPreviousNodeSibling(int count = 1); // uses parent-node if current is attribute
	virtual bool moveToPreviousNodeSibling(const String& siblingName, int count = 1); // uses parent-node if current is attribute

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_AbstractTreeIterator_h

