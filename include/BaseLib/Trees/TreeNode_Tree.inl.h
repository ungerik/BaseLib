/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

// Included by BaseLib/Trees/TreeNode.h


class BL_EXPORT Tree : public AbstractTree {
public:

	Tree(TreeNode* forRootNode, AbstractFactory::CreateNodeFunctionPointer createNodeFunctionPointer, bool remove = false, bool move = false, bool copy = false, const NumberFormat* useNumberFormat = NumberFormat::getDefault());
	Tree(TreeNode* forRootNode, AbstractFactory::CreateNodeFunctor* newCreateNodeFunctor, bool remove = false, bool move = false, bool copy = false, const NumberFormat* useNumberFormat = NumberFormat::getDefault());

	virtual TreeIterator getTreeIteratorForRootNode() const;

	virtual bool canCreateNodes() const;
	virtual bool canRemoveNodes() const;
	virtual bool canRenameNodes() const;
	virtual bool canMoveNodes() const;
	virtual bool canCopyNodes() const;

	virtual void createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf = false);
	virtual void removeNode(const AbstractTreeIterator& nodePath);
	virtual void moveNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath);
	virtual void copyNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath);

protected:

	TreeNode* rootNode;
	AutoPointer<AbstractFactory::CreateNodeFunctor> createNodeFunctor;
	bool allowRemoveNodes;
	bool allowMoveNodes;
	bool allowCopyNodes;
	const NumberFormat* numberFormat;

	static TreeNode* getTreeNodeFromIterator(const AbstractTreeIterator& iterator);
};

