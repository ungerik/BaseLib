/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_TreeIterator_h
#define BaseLib_Trees_TreeIterator_h



#include "BaseLib/Trees/AbstractTreeIterator.h"
#include "BaseLib/Utilities/AutoPointer.h"



namespace BaseLib {
namespace Trees {



using BaseLib::Utilities::AutoPointer;



/**
Encapsulates an AbstractTreeIterator.
Should be used by value.
*/
class BL_EXPORT TreeIterator : public AbstractTreeIterator {
public:

	static AbstractTreeIterator* getImplementation(AbstractTreeIterator& abstractTreeIterator);
	static const AbstractTreeIterator* getImplementation(const AbstractTreeIterator& abstractTreeIterator);

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::TreeIterator, AbstractTreeIterator);

	TreeIterator(AbstractTreeIterator* newImplementation);

	virtual AbstractTreeIterator* clone() const;

	inline bool hasImplementation() const
	{
		return implementation != NULL;
	}

	inline AbstractTreeIterator* getImplementation()
	{
		return implementation;
	}

	inline const AbstractTreeIterator* getImplementation() const
	{
		return implementation;
	}

	inline void setImplementation(AbstractTreeIterator* newImplementation)
	{
		implementation = newImplementation;
	}

	inline void setImplementation(const AbstractTreeIterator& newImplementation)
	{
		implementation = newImplementation.clone();
	}

	// Assignment:

	TreeIterator(const TreeIterator& other)
		: implementation(other.getImplementation() != NULL ? other.getImplementation()->clone() : NULL)
	{
	}

	inline TreeIterator& operator =(const TreeIterator& right)
	{
		const AbstractTreeIterator* rightImplementation = right.getImplementation();
		implementation = rightImplementation != NULL ? right.getImplementation()->clone() : NULL;
		return *this;
	}

	// Compare:

	virtual bool operator ==(const AbstractTreeIterator& right) const;

	inline bool operator ==(const TreeIterator& right) const
	{
		const AbstractTreeIterator* rightImplementation = right.getImplementation();
		return (rightImplementation != NULL) ? (operator ==(*rightImplementation)) : (implementation == rightImplementation);
	}

	inline bool operator !=(const TreeIterator& right) const
	{
		return !operator ==(right);
	}


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

	virtual void push();
	virtual void pop(bool restorePosition = true, bool restoreStack = true);
	virtual bool moveTo(const String& path);

	// Linear node-position:
	virtual int getNodePosition() const;
	virtual bool moveToNodePosition(int nodePosition);
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
	virtual bool moveToParent(int parentGeneration);
	virtual bool moveToParent(const String& parentName, int count = 1);
	virtual bool moveToParentOrSelf(const String& parentOrSelfName);
	virtual void moveToRootNode();

	// Children:
	virtual bool canHaveChildNodes() const;
	virtual bool hasChildNodes() const;
	virtual bool hasChildNode(const String& childName) const;
	virtual int getChildNodeCount() const;
	virtual int getChildNodePosition() const;
	virtual bool moveToChildNode(int childPosition = 0);
	virtual bool moveToChildNode(const String& childName);
	virtual void enumChildNodeNames(const Enumerator<String>& enumerator) const;

	// Siblings:
	virtual bool hasNextNodeSibling() const;
	virtual bool moveToNextNodeSibling(int count = 1);
	virtual bool moveToNextNodeSibling(const String& siblingName, int count = 1);
	virtual bool hasPreviousNodeSibling() const;
	virtual bool moveToPreviousNodeSibling(int count = 1);
	virtual bool moveToPreviousNodeSibling(const String& siblingName, int count = 1);

private:

	AutoPointer<AbstractTreeIterator> implementation;

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_TreeIterator_h


