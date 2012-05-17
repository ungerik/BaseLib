/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_CompoundTree_h
#define BaseLib_Trees_CompoundTree_h



#include "BaseLib/Trees/DefaultTree.h"
#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/Containers/StringMap.h"



namespace BaseLib {
namespace Trees {



class BL_EXPORT CompoundTree : public DefaultTree {
public:

	CompoundTree(const String& rootNodeName, const NumberFormat* useNumberFormat = NumberFormat::getDefault());
	~CompoundTree();

	AbstractTree* getSubTree(const String& id);

	/**
	@param newSubTree Takes ownership of newSubTree
	@param id
	@param parentPath Relative path from root-node (without root-node)
	@param renameSubTreeRootNodeAs If not "", new name for the root-node of newSubTree
	*/
	void addSubTree(AbstractTree* newSubTree, const String& id, const String& parentPath, const String& renameSubTreeRootNodeAs = Empty());
	void removeSubTree(const String& id, bool deleteOldSubTreeObject = true);

	virtual bool canCreateNodes() const;
	virtual bool canRemoveNodes() const;
	virtual bool canRenameNodes() const;
	virtual bool canMoveNodes() const;
	virtual bool canCopyNodes() const;

	virtual void createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf = false);
	virtual void removeNode(const AbstractTreeIterator& nodePath);
	virtual void renameNode(const AbstractTreeIterator& nodePath, const String& newName);
	virtual void moveNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath);
	virtual void copyNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath);

private:

	struct SubTree {
		AutoPointer<AbstractTree> tree;
		String rootNodeName;
		String id;
		String parentPath;
		TreeNode* parentNode;

		SubTree(AbstractTree* newTree, const String& newRootNodeName, const String& newId, TreeNode* newParentNode)
			: tree(newTree)
			, rootNodeName(newRootNodeName)
			, id(newId)
			, parentNode(newParentNode)
		{
		}

	};

	class BL_EXPORT Iterator : public AbstractTreeIterator {
	public:

		BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::CompoundTree::Iterator, AbstractTreeIterator);

		explicit Iterator(CompoundTree* forCompoundTree);

		virtual AbstractTreeIterator* clone() const;
		virtual bool operator ==(const AbstractTreeIterator& right) const;
		virtual bool isAttribute() const;
		virtual bool hasMetaTag(const String& metaTag) const;
		virtual String getName() const;
		virtual String getNamespace() const;
		virtual bool isReadable() const;
		virtual bool isWriteable() const;
		virtual InputStream* createInputStream() const;
		virtual OutputStream* createOutputStream() const;
		virtual String getValue() const;
		virtual void setValue(const String& newValue) const;
		virtual String getValueOfAttribute(int attributePosition) const;
		virtual void setValueOfAttribute(int attributePosition, const String& newValue) const;
		virtual String getValueOfAttribute(const String& attributeName) const;
		virtual void setValueOfAttribute(const String& attributeName, const String& newValue) const;
		virtual String getType() const;
		virtual bool isDefaultValue() const;
		virtual void setDefaultValue() const;
		virtual const Enumeration<String>& getValueRange() const;
		virtual void push();
		virtual void pop(bool restorePosition = true, bool restoreStack = true);
		virtual int getAttributeCount() const;
		virtual int getAttributePosition() const;
		virtual bool moveToAttribute(int attributePosition);
		virtual bool hasParent() const;
		virtual bool moveToParent();
		virtual int getChildNodeCount() const;
		virtual int getChildNodePosition() const;
		virtual bool moveToChildNode(int childPosition);

	private:
		
		CompoundTree* compoundTree;
		TreeNode* baseTreeNode;
		SubTree* subTree;
		TreeIterator subTreeIterator;

		struct State {

			TreeNode* baseTreeNode;
			SubTree* subTree;
			TreeIterator subTreeIterator; // OPTIMIZE -> copy by value = new allocation!!!

			State(TreeNode* newBaseTreeNode = NULL, SubTree* newSubTree = NULL, const TreeIterator& newSubTreeIterator = TreeIterator(NULL))
				: baseTreeNode(newBaseTreeNode)
				, subTree(newSubTree)
				, subTreeIterator(newSubTreeIterator)
			{
			}
		};

		typedef Stack<State> PositionStack;
		PositionStack positionStack;

		inline bool isSubTree() const
		{
			return subTree != NULL;
		}
	};

	friend Iterator;

	typedef BaseLib::Containers::StringMap<SubTree*> SubTrees;
	SubTrees subTrees;

	TreeNode* rootNode;
	TreeNode::Iterator baseRootNodeTreeIterator;
};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_CompoundTree_h

