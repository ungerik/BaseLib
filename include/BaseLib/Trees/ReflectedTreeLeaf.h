/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_ReflectedTreeLeaf_h
#define BaseLib_Trees_ReflectedTreeLeaf_h



#include "BaseLib/Trees/DefaultTreeLeaf.h"
#include "BaseLib/Functors/Functor3.h"



namespace BaseLib {
namespace Trees {



class BL_EXPORT ReflectedTreeLeaf : public DefaultTreeLeaf {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::ReflectedTreeLeaf, DefaultTreeLeaf);

	typedef Functor3<void, TreeNode*, TreeNode*, TreeNode*> ChangeParentNodeFunctor;

	ReflectedTreeLeaf(bool useClassNameSpaces = false, Object* newReflectionObject = NULL);

	void setReflectionObject(
		Object* newReflectionObject,
		ChangeParentNodeFunctor* newOnBeforeSomeParentNodeChangesFunctor = NULL,
		ChangeParentNodeFunctor* newOnBeforeParentNodeChangesFunctor = NULL,
		ChangeParentNodeFunctor* newOnAfterParentNodeChangedFunctor = NULL/*,
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

	virtual void beforeSomeParentNodeChanges(TreeNode* treeNode, TreeNode* oldParentNode, TreeNode* newParentNode);
	virtual void setParent(TreeNode* newParent);

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

	virtual void onBeforeAttributesTransaction();
	virtual void onAfterAttributesTransaction();

private:

	Object* reflectionObject;
	AutoPointer<ChangeParentNodeFunctor> onBeforeSomeParentNodeChangesFunctor;
	AutoPointer<ChangeParentNodeFunctor> onBeforeParentNodeChangesFunctor;
	AutoPointer<ChangeParentNodeFunctor> onAfterParentNodeChangedFunctor;
	//AutoPointer<Functor0<void> > beginSetAttributesSequenceFunctor;
	//AutoPointer<Functor0<void> > endSetAttributesSequenceFunctor;
	bool nameUsesClassNameSpaces;
};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_ReflectedTreeLeaf_h

