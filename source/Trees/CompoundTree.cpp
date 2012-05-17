/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/CompoundTree.h"
#include "BaseLib/Trees/DataTreeNode.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::Strings;
using namespace BaseLib::ErrorHandling;



CompoundTree::CompoundTree(const String& rootNodeName, const NumberFormat* useNumberFormat)
	: DefaultTree(NULL)
	, subTrees()
	, rootNode(new DataTreeNode(rootNodeName))
	, baseRootNodeTreeIterator(rootNode, String(), useNumberFormat)
{
	treeIteratorForRootNode.setImplementation(new Iterator(this));
}



CompoundTree::~CompoundTree()
{
	foreach (SubTrees::Iterator, i, subTrees)
	{
		delete i->second;
	}

	rootNode->removeFromParent_DeleteSelfAndSubTree();
}



CompoundTree::AbstractTree* CompoundTree::getSubTree(const String& id)
{
	SubTrees::Iterator i = subTrees.find(id);
	if (i != subTrees.end())
	{
		return i->second->tree;
	}
	else
	{
		argumentError("No sub-tree with id=" + id + " found!" ERROR_AT);
		return NULL;
	}
}



void CompoundTree::addSubTree(AbstractTree* newSubTree, const String& id, const String& parentPath, const String& renameSubTreeRootNodeAs)
{
	if (checkArgumentNotNull(NAME_VALUE(newSubTree)) == true)
	{
		if (subTrees.find(id) != subTrees.end())
		{
			argumentError("Sub-tree with id '" + id + "' already exists!" ERROR_AT);
		}

		if (parentPath.beginsWith('/') == true)
		{
			argumentError("parentPath must not be an absolute path!" ERROR_AT);
			return;
		}

		// Navigate to path with creating missing nodes:
		TreeNode* currentNode = rootNode;
		StringTokenizer tokenizer(parentPath, "/.");
		while (tokenizer.hasNextToken() == true)
		{
			String pathToken = tokenizer.nextToken();
			currentNode = currentNode->getChildIfExists(pathToken);
			if (currentNode == NULL)
			{
				TreeNode* newNode = new DataTreeNode(pathToken);
				currentNode->addChild(newNode);
				currentNode = newNode;
			}
		}

		// add sub-tree:
		String subTreeRootName = (renameSubTreeRootNodeAs.isEmpty() == true) ?
			newSubTree->getTreeIteratorForRootNode().getName() :
			renameSubTreeRootNodeAs;

		subTrees[id] = new SubTree(newSubTree, subTreeRootName, id, currentNode);
	}
}



void CompoundTree::removeSubTree(const String& id, bool deleteOldSubTreeObject)
{
	AbstractTree* oldSubTree = getSubTree(id);
	if (oldSubTree != NULL)
	{
		subTrees.erase(id);
		if (deleteOldSubTreeObject == true)
		{
			delete oldSubTree;
		}
	}
}



bool CompoundTree::canCreateNodes() const
{
	return false;
}



bool CompoundTree::canRemoveNodes() const
{
	return false;
}



bool CompoundTree::canRenameNodes() const
{
	return false;
}



bool CompoundTree::canMoveNodes() const
{
	return false;
}



bool CompoundTree::canCopyNodes() const
{
	return false;
}



void CompoundTree::createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf)
{
}



void CompoundTree::removeNode(const AbstractTreeIterator& nodePath)
{
}



void CompoundTree::renameNode(const AbstractTreeIterator& nodePath, const String& newName)
{
}



void CompoundTree::moveNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath)
{
}



void CompoundTree::copyNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath)
{
}



} // namespace Trees
} // namespace BaseLib
