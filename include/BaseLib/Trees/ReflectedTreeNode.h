/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_ReflectedTreeNode_h
#define BaseLib_Trees_ReflectedTreeNode_h



#include "BaseLib/Trees/DefaultTreeNode.h"
#include "BaseLib/Functors/Functor2.h"
#include "BaseLib/Functors/Functor3.h"



namespace BaseLib {
namespace Trees {



class BL_EXPORT ReflectedTreeNode : public DefaultTreeNode {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::ReflectedTreeNode, DefaultTreeNode);

	typedef Functor3<void, TreeNode*, TreeNode*, TreeNode*> ChangeParentNodeFunctor;
	typedef Functor2<void, TreeNode*, int> ChildNodeAddedFunctor;
	typedef Functor2<void, TreeNode*, int> ChildNodeRemovedFunctor;

	ReflectedTreeNode(bool useClassNameSpaces = false, Object* newReflectionObject = NULL, bool subTreeIsHidden = false);

	void setReflectionObject(
		Object* newReflectionObject,
		ChangeParentNodeFunctor* newOnBeforeSomeParentNodeChangesFunctor = NULL,
		ChangeParentNodeFunctor* newOnBeforeParentNodeChangesFunctor = NULL,
		ChangeParentNodeFunctor* newOnAfterParentNodeChangedFunctor = NULL,
		ChildNodeAddedFunctor* newOnChildNodeAddedFunctor = NULL,
		ChildNodeRemovedFunctor* newOnChildNodeRemovedFunctor = NULL,
		Functor0<void>* newOnBeforeChildrenTransactionFunctor = NULL,
		Functor0<void>* newOnAfterChildrenTransactionFunctor = NULL/*,
		Functor0<void>* newBeginSetAttributesSequenceFunctor = NULL,
		Functor0<void>* newEndAddSetAttributesSequenceFunctor = NULL*/);

	inline bool isUsingClassNameSpaces() const
	{
		return nameUsesClassNameSpaces;
	}

	String getReflectionObjectClassNameWithNameSpace() const
	{
		return getReflectionObject()->getClass()->getName();
	}

	virtual void deleteSelf();

	virtual String getName() const;

	virtual const Enumeration<String>& getAttributeNames() const;
	virtual bool isAttributeReadable(const String& attributeName) const;
	virtual bool isAttributeWriteable(const String& attributeName) const;
	virtual bool getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) const;
	virtual void setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault());
	//virtual const InputStream* createInputStreamForAttribute(const String& attributeName) const;
	//virtual const OutputStream* createOutputStreamForAttribute(const String& attributeName) const;
	virtual bool hasAttribute(const String& attributeName) const;
	virtual bool hasMetaTag(const String& metaTag) const;
	virtual bool hasAttributeMetaTag(const String& attributeName, const String& metaTag) const;
	virtual String getAttributeType(const String& attributeName) const;
	virtual bool isAttributeDefault(const String& attributeName) const;
	virtual void setAttributeToDefault(const String& attributeName);
	virtual const Enumeration<String>& getAttributeValueRange(const String& attributeName) const;
	virtual Object* getReflectionObject();
	virtual const Object* getReflectionObject() const;

	virtual void beforeSomeParentNodeChanges(TreeNode* treeNode, TreeNode* oldParentNode, TreeNode* newParentNode);
	virtual void setParent(TreeNode* newParent);
	virtual void addChild(TreeNode* newChild);
	virtual void insertChild(TreeNode* newChild, int index);
	virtual TreeNode* replaceChild(int index, TreeNode* newChild);
	virtual TreeNode* removeChild(int index);

	virtual void onBeforeAttributesTransaction();
	virtual void onAfterAttributesTransaction();
	virtual void onBeforeChildrenTransaction();
	virtual void onAfterChildrenTransaction();

private:

	Object* reflectionObject;
	AutoPointer<ChangeParentNodeFunctor> onBeforeSomeParentNodeChangesFunctor;
	AutoPointer<ChangeParentNodeFunctor> onBeforeParentNodeChangesFunctor;
	AutoPointer<ChangeParentNodeFunctor> onAfterParentNodeChangedFunctor;
	AutoPointer<ChildNodeAddedFunctor> childNodeAddedFunctor;
	AutoPointer<ChildNodeRemovedFunctor> childNodeRemovedFunctor;
	AutoPointer<Functor0<void> > onBeforeChildrenTransactionFunctor;
	AutoPointer<Functor0<void> > onAfterChildrenTransactionFunctor;
	//AutoPointer<Functor0<void> > beginSetAttributesSequenceFunctor;
	//AutoPointer<Functor0<void> > endSetAttributesSequenceFunctor;
	bool nameUsesClassNameSpaces;
};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_ReflectedTreeNode_h

