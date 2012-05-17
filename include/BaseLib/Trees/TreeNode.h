/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_TreeNode_h
#define BaseLib_Trees_TreeNode_h



#include "BaseLib/Strings/String.h"
#include "BaseLib/Containers/Enumeration.h"
#include "BaseLib/Containers/Stack.h"
#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Trees/AbstractTree.h"
#include "BaseLib/Strings/NumberFormat.h"



namespace BaseLib {
namespace Trees {



using BaseLib::Strings::String;
using BaseLib::Strings::NumberFormat;
using BaseLib::Containers::Enumeration;
using BaseLib::Containers::Stack;
using BaseLib::Containers::Array;
using BaseLib::Reflection::Object;
using namespace BaseLib::Functors;



class BL_EXPORT TreeNode : public Object {
public:

	#include "BaseLib/Trees/TreeNode_AbstractFactory.inl.h"
	#include "BaseLib/Trees/TreeNode_Tree.inl.h"
	#include "BaseLib/Trees/TreeNode_Iterator.inl.h"

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::Trees::TreeNode);

	virtual ~TreeNode();

	virtual void deleteSelf();
	void deleteSelfAndSubTree();
	void deleteSelfAndSubTreeIncludingHiddenChildren();
	void removeFromParent_DeleteSelfAndSubTree();

	virtual bool isLeafType() const;

	inline TreeNode* getParent()
	{
		return parent;
	}

	inline const TreeNode* getParent() const
	{
		return parent;
	}

	/**
	Can be overridden to return NULL, so that getRootNode() returns this node.
	*/
	virtual TreeNode* getParentForGetRootNode(bool rootNodeOfHiddenSubTree);
	inline const TreeNode* getParentForGetRootNode(bool rootNodeOfHiddenSubTree) const
	{
		return const_cast<TreeNode*>(this)->getParentForGetRootNode(rootNodeOfHiddenSubTree);
	}

	inline bool hasParent() const
	{
		return parent != NULL;
	}

	TreeNode& getRootNode();
	inline const TreeNode& getRootNode() const
	{
		return const_cast<TreeNode*>(this)->getRootNode();
	}

	TreeNode& getRootNodeOfHiddenSubTree();
	inline const TreeNode& getRootNodeOfHiddenSubTree() const
	{
		return const_cast<TreeNode*>(this)->getRootNodeOfHiddenSubTree();
	}

	TreeNode* findNodeByAttributeValueInSubTree(const String& attributeName, const String& attributeValue, bool includeHiddenDirectChildren = false, const NumberFormat* numberFormat = NumberFormat::getDefault());
	inline const TreeNode* findNodeByAttributeValueInSubTree(const String& attributeName, const String& attributeValue, bool includeHiddenDirectChildren = false, const NumberFormat* numberFormat = NumberFormat::getDefault()) const
	{
		return const_cast<TreeNode*>(this)->findNodeByAttributeValueInSubTree(attributeName, attributeValue, includeHiddenDirectChildren, numberFormat);
	}

	TreeNode* findNodeByAttributeValueInSubTreeIncludingHiddenChildren(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault());
	inline const TreeNode* findNodeByAttributeValueInSubTreeIncludingHiddenChildren(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) const
	{
		return const_cast<TreeNode*>(this)->findNodeByAttributeValueInSubTreeIncludingHiddenChildren(attributeName, attributeValue, numberFormat);
	}

	// Searches first in the hidden sub-tree if the node is in a hidden sub-tree,
	// if nothing found, search in the whole tree beginning at the true root-node:
	TreeNode* findNodeByAttributeValueInWholeTree(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault());

	inline const TreeNode* findNodeByAttributeValueInWholeTree(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) const
	{
		return const_cast<TreeNode*>(this)->findNodeByAttributeValueInWholeTree(attributeName, attributeValue, numberFormat);
	}

	// Searches first in the hidden sub-tree if the node is in a hidden sub-tree,
	// if nothing found, search in the whole tree beginning at the true root-node:
	TreeNode* findNodeByAttributeValueInWholeTreeIncludingHiddenChildren(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault());

	inline const TreeNode* findNodeByAttributeValueInWholeTreeIncludingHiddenChildren(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) const
	{
		return const_cast<TreeNode*>(this)->findNodeByAttributeValueInWholeTreeIncludingHiddenChildren(attributeName, attributeValue, numberFormat);
	}

	void xPathQuery(const String& xPath, const Enumerator<TreeNode*>& enumerator, bool includeHiddenChildren = false, const NumberFormat* numberFormat = NumberFormat::getDefault());
	inline void xPathQuery(const String& xPath, const Enumerator<const TreeNode*>& enumerator, bool includeHiddenChildren = false, const NumberFormat* numberFormat = NumberFormat::getDefault()) const
	{
		return const_cast<TreeNode*>(this)->xPathQuery(xPath, reinterpret_cast<const Enumerator<TreeNode*>&>(enumerator), includeHiddenChildren, numberFormat);
	}
	String getPath() const;

	virtual String getName() const = 0;

	int getChildCount() const;
	virtual int getChildCountIncludingHiddenChildren() const = 0;
	virtual TreeNode* getChild(int index) = 0;
	inline const TreeNode* getChild(int index) const
	{
		return const_cast<TreeNode*>(this)->getChild(index);
	}
	TreeNode* getChildIfExists(const String& childName, int count = 1);
	inline const TreeNode* getChildIfExists(const String& childName, int count = 1) const
	{
		return const_cast<TreeNode*>(this)->getChildIfExists(childName, count);
	}
	virtual void addChild(TreeNode* newChild) = 0;
	virtual void insertChild(TreeNode* newChild, int index) = 0;
	virtual TreeNode* removeChild(int index) = 0;
	virtual TreeNode* replaceChild(int index, TreeNode* newChild) = 0;
	virtual int getChildIndexAtParent() const;
	bool removeFromParent();
	virtual bool isSubTreeHidden() const;

	virtual void onBeforeAttributesTransaction();
	virtual void onAfterAttributesTransaction();
	virtual void onBeforeChildrenTransaction();
	virtual void onAfterChildrenTransaction();

	virtual const Enumeration<String>& getAttributeNames() const = 0;
	virtual bool isAttributeReadable(const String& attributeName) const = 0;
	virtual bool isAttributeWriteable(const String& attributeName) const = 0;
	String getAttribute(const String& attributeName, const NumberFormat* numberFormat = NumberFormat::getDefault()) const;
	virtual bool getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) const = 0; // faster than if hasAttribute() then getAttribute()	
	virtual void setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) = 0;
	//virtual const InputStream* createInputStreamForAttribute(const String& attributeName) const = 0;
	//virtual const OutputStream* createOutputStreamForAttribute(const String& attributeName) const = 0;
	virtual bool hasAttribute(const String& attributeName) const = 0;
	virtual bool hasMetaTag(const String& metaTag) const = 0;
	virtual bool hasAttributeMetaTag(const String& attributeName, const String& metaTag) const = 0;
	virtual String getAttributeType(const String& attributeName) const = 0;
	virtual bool isAttributeDefault(const String& attributeName) const = 0;
	virtual void setAttributeToDefault(const String& attributeName) = 0;
	virtual const Enumeration<String>& getAttributeValueRange(const String& attributeName) const = 0;

	virtual Object* getReflectionObject();
	virtual const Object* getReflectionObject() const;

	String getAttributeNamesAsString() const;

protected:

	friend class DefaultTreeNode;

	TreeNode* parent;

	TreeNode();
	virtual void beforeSomeParentNodeChanges(TreeNode* treeNode, TreeNode* oldParentNode, TreeNode* newParentNode);
	virtual void setParent(TreeNode* newParent); // Does not remove self from old parent
	void xPathTestNode(const Array<String>& tokens, int currentToken, const Enumerator<TreeNode*>& enumerator, bool includeHiddenChildren, const NumberFormat* numberFormat);

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_TreeNode_h

