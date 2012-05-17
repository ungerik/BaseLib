/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/AbstractTree.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



AbstractTree::~AbstractTree()
{
}



bool AbstractTree::canCreateNodes() const
{
	return false;
}



bool AbstractTree::canRemoveNodes() const
{
	return false;
}



bool AbstractTree::canRenameNodes() const
{
	return false;
}



bool AbstractTree::canMoveNodes() const
{
	return false;
}



bool AbstractTree::canCopyNodes() const
{
	return false;
}



void AbstractTree::createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf)
{
	notImplementedError("AbstractTree::createNode()" ERROR_AT);
}



void AbstractTree::removeNode(const AbstractTreeIterator& nodePath)
{
	notImplementedError("AbstractTree::removeNode()" ERROR_AT);
}



void AbstractTree::renameNode(const AbstractTreeIterator& nodePath, const String& newName)
{
	notImplementedError("AbstractTree::renameNode()" ERROR_AT);
}



void AbstractTree::moveNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath)
{
	notImplementedError("AbstractTree::moveNode()" ERROR_AT);
}



void AbstractTree::copyNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath)
{
	notImplementedError("AbstractTree::copyNode()" ERROR_AT);
}



void AbstractTree::createNode(const String& parentPath, const String& name, bool leaf)
{
	TreeIterator parentPathIterator = getTreeIteratorForRootNode();
	if (parentPathIterator.moveTo(parentPath) == true)
	{
		createNode(parentPathIterator, name, leaf);
	}
	else
	{
		argumentError("Invalid path in tree!" ERROR_AT);
	}
}



void AbstractTree::removeNode(const String& nodePath)
{
	TreeIterator nodePathIterator = getTreeIteratorForRootNode();
	if (nodePathIterator.moveTo(nodePath) == true)
	{
		removeNode(nodePathIterator);
	}
	else
	{
		argumentError("Invalid path in tree!" ERROR_AT);
	}
}



void AbstractTree::renameNode(const String& nodePath, const String& newName)
{
	TreeIterator nodePathIterator = getTreeIteratorForRootNode();
	if (nodePathIterator.moveTo(nodePath) == true)
	{
		renameNode(nodePathIterator, newName);
	}
	else
	{
		argumentError("Invalid path in tree!" ERROR_AT);
	}
}



void AbstractTree::moveNode(const String& nodePath, const String& newParentPath)
{
	TreeIterator nodePathIterator = getTreeIteratorForRootNode();
	if (nodePathIterator.moveTo(nodePath) == false)
	{
		argumentError("Invalid path in tree!" ERROR_AT);
		return;
	}

	TreeIterator newParentPathIterator = getTreeIteratorForRootNode();
	if (newParentPathIterator.moveTo(newParentPath) == false)
	{
		argumentError("Invalid path in tree!" ERROR_AT);
		return;
	}

	moveNode(nodePathIterator, newParentPathIterator);

}



void AbstractTree::copyNode(const String& nodePath, const String& newParentPath)
{
	TreeIterator nodePathIterator = getTreeIteratorForRootNode();
	if (nodePathIterator.moveTo(nodePath) == false)
	{
		argumentError("Invalid path in tree!" ERROR_AT);
		return;
	}

	TreeIterator newParentPathIterator = getTreeIteratorForRootNode();
	if (newParentPathIterator.moveTo(newParentPath) == false)
	{
		argumentError("Invalid path in tree!" ERROR_AT);
		return;
	}

	copyNode(nodePathIterator, newParentPathIterator);
}



} // namespace Trees
} // namespace BaseLib
