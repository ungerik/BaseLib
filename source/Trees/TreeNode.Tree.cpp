/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/Trees/TreeCloner.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



TreeNode* TreeNode::Tree::getTreeNodeFromIterator(const AbstractTreeIterator& iterator)
{
	const AbstractTreeIterator* abstractIterator = (iterator.getClass() == TreeIterator::CLASS)
		? static_cast<const TreeIterator&>(iterator).getImplementation()
		: &iterator;

	if (abstractIterator != NULL && abstractIterator->getClass() == Iterator::CLASS)
	{
		return static_cast<const Iterator*>(abstractIterator)->currentTreeNode;
	}
	else
	{
		return NULL;
	}
}



TreeNode::Tree::Tree(TreeNode* forRootNode, AbstractFactory::CreateNodeFunctionPointer createNodeFunctionPointer, bool remove, bool move, bool copy, const NumberFormat* useNumberFormat)
	: rootNode(forRootNode)
	, createNodeFunctor(new AbstractFactory::CreateNodeFunctionFunctor(createNodeFunctionPointer))
	, allowRemoveNodes(remove)
	, allowMoveNodes(move)
	, allowCopyNodes(copy)
	, numberFormat(useNumberFormat)
{
}



TreeNode::Tree::Tree(TreeNode* forRootNode, AbstractFactory::CreateNodeFunctor* newCreateNodeFunctor, bool remove, bool move, bool copy, const NumberFormat* useNumberFormat)
	: rootNode(forRootNode)
	, createNodeFunctor(newCreateNodeFunctor)
	, allowRemoveNodes(remove)
	, allowMoveNodes(move)
	, allowCopyNodes(copy)
	, numberFormat(useNumberFormat)
{
}



TreeIterator TreeNode::Tree::getTreeIteratorForRootNode() const
{
	return TreeIterator(new Iterator(rootNode, String(), numberFormat));
}




bool TreeNode::Tree::canCreateNodes() const
{
	return createNodeFunctor != NULL;
}



bool TreeNode::Tree::canRemoveNodes() const
{
	return allowRemoveNodes;
}



bool TreeNode::Tree::canRenameNodes() const
{
	return false;
}



bool TreeNode::Tree::canMoveNodes() const
{
	return allowMoveNodes;
}



bool TreeNode::Tree::canCopyNodes() const
{
	return allowCopyNodes;
}



void TreeNode::Tree::createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf)
{
	if (canCreateNodes() == true)
	{
		TreeNode* parentNode = getTreeNodeFromIterator(parentPath);
		if (parentNode != NULL)
		{
			TreeNode* newNode = (*createNodeFunctor)(name);
			parentNode->addChild(newNode);
			newNode->setParent(parentNode);
		}
		else
		{
			argumentError("Need a TreeNode::Iterator to create a node!" ERROR_AT);
		}
	}
	else
	{
		stateError("Tree can't create nodes!" ERROR_AT);
	}
}



void TreeNode::Tree::removeNode(const AbstractTreeIterator& nodePath)
{
	if (canRemoveNodes() == true)
	{
		TreeNode* treeNode = getTreeNodeFromIterator(nodePath);
		if (treeNode != NULL)
		{
			treeNode->removeFromParent_DeleteSelfAndSubTree();
		}
		else
		{
			argumentError("Need a TreeNode::Iterator to remove a node!" ERROR_AT);
		}
	}
	else
	{
		stateError("Tree can't remove nodes!" ERROR_AT);
	}
}



void TreeNode::Tree::moveNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath)
{
	if (canMoveNodes() == true)
	{
		TreeNode* treeNode = getTreeNodeFromIterator(nodePath);
		TreeNode* newParentNode = getTreeNodeFromIterator(newParentPath);
		if (treeNode != NULL && newParentNode != NULL)
		{
			TreeNode* oldParentNode = treeNode->getParent();
			treeNode->setParent(NULL);
			oldParentNode->removeChild(treeNode->getChildIndexAtParent());
			newParentNode->addChild(treeNode);
			treeNode->setParent(newParentNode);
		}
		else
		{
			argumentError("Need a TreeNode::Iterator to move a node!" ERROR_AT);
		}
	}
	else
	{
		stateError("Tree can't move nodes!" ERROR_AT);
	}
}



void TreeNode::Tree::copyNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath)
{
	if (canCopyNodes() == true)
	{
		TreeNode* treeNode = getTreeNodeFromIterator(nodePath);
		TreeNode* newParentNode = getTreeNodeFromIterator(newParentPath);
		if (treeNode != NULL && newParentNode != NULL)
		{
			TreeCloner treeCloner(treeNode, *createNodeFunctor);
			TreeNode* clonedTreeNode = treeCloner.buildTree();
			if (clonedTreeNode != NULL)
			{
				newParentNode->addChild(clonedTreeNode);
				clonedTreeNode->setParent(newParentNode);
			}
			else
			{
				resultError("Can't clone the tree-node to copy!" ERROR_AT);
			}
		}
		else
		{
			argumentError("Need a TreeNode::Iterator to copy a node!" ERROR_AT);
		}
	}
	else
	{
		stateError("Tree can't remove nodes!" ERROR_AT);
	}
}





} // namespace Trees
} // namespace BaseLib
