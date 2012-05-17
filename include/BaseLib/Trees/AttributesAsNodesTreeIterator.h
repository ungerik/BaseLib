/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_AttributesAsNodesTreeIterator_h
#define BaseLib_Trees_AttributesAsNodesTreeIterator_h



#include "BaseLib/Trees/TreeIterator.h"



namespace BaseLib {
namespace Trees {


/**
Encapsulates an AbstractTreeIterator.
Should be used by value.
*/
class BL_EXPORT AttributesAsNodesTreeIterator : public AbstractTreeIterator {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::AttributesAsNodesTreeIterator, AbstractTreeIterator);

	AttributesAsNodesTreeIterator(const TreeIterator& newSource);

	virtual AbstractTreeIterator* clone() const;

	// Compare:

	virtual bool operator ==(const AbstractTreeIterator& right) const;

	// Info:

	virtual bool isAttribute() const;
	virtual String getName() const;
	virtual String getNamespace() const;
	virtual bool hasMetaTag(const String& metaTag) const;

	// IO:

	virtual bool isReadable() const;
	virtual bool isWriteable() const;

	virtual InputStream* createInputStream() const;
	virtual OutputStream* createOutputStream() const;

	virtual String getValue() const; // no error not readable
	virtual void setValue(const String& newValue) const; // no error if not writeable

	virtual String getType() const;
	virtual bool isDefaultValue() const;
	virtual void setDefaultValue() const;
	virtual const Enumeration<String>& getValueRange() const;

	// Tree navigation:

	virtual void push();
	virtual void pop(bool restorePosition = true, bool restoreStack = true);

	// Linear node-position:
	virtual bool moveToNextNode();
	virtual bool moveToPreviousNode();

	// Attributes:
	virtual bool hasAttribute(const String& attributeName) const;
	virtual int getAttributeCount() const;
	virtual int getAttributePosition() const;
	virtual bool moveToAttribute(int attributePosition);
	virtual bool moveToAttribute(const String& attributeName);
	virtual bool moveToNextAttribute();
	virtual bool moveToPreviousAttribute();
	virtual void enumAttributeNames(const Enumerator<String>& enumerator) const;

	// Parents:
	virtual bool hasParent() const;
	virtual int getParentCount() const;
	virtual bool moveToParent();

	// Children:
	virtual bool canHaveChildNodes() const;
	virtual bool hasChildNodes() const;
	virtual bool hasChildNode(const String& childName) const;
	virtual int getChildNodeCount() const;
	virtual int getChildNodePosition() const;
	virtual bool moveToChildNode(int childPosition = 0);
	virtual bool moveToChildNode(const String& childName);
	virtual void enumChildNodeNames(const Enumerator<String>& enumerator) const;

	inline const TreeIterator& getSource() const
	{
		return source;
	}

	inline void setSource(const TreeIterator& newSource)
	{
		source = newSource;
	}

private:

	TreeIterator source;

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_AttributesAsNodesTreeIterator_h

