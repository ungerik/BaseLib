/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/DefaultTree.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



DefaultTree::DefaultTree(const TreeIterator& rootTreeIterator)
	: AbstractTree()
	, treeIteratorForRootNode(rootTreeIterator)
{
}



DefaultTree::DefaultTree(AbstractTreeIterator* rootAbstractTreeIterator) // takes ownership
	: AbstractTree()
	, treeIteratorForRootNode(rootAbstractTreeIterator)
{
}



TreeIterator DefaultTree::getTreeIteratorForRootNode() const
{
	return treeIteratorForRootNode;
}



} // namespace Trees
} // namespace BaseLib
