/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/DefaultTreeLeaf.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



BL_DEFINE_REFLECTION_CLASS(DefaultTreeLeaf, TreeNode)
{
}



bool DefaultTreeLeaf::isLeafType() const
{
	return true;
}



int DefaultTreeLeaf::getChildCountIncludingHiddenChildren() const
{
	return 0;
}



TreeNode* DefaultTreeLeaf::getChild(int index)
{
	return NULL;
}



void DefaultTreeLeaf::addChild(TreeNode* newChild)
{
	notImplementedError("Can't add child to a tree-leaf!" ERROR_AT);
}



void DefaultTreeLeaf::insertChild(TreeNode* newChild, int index)
{
	notImplementedError("Can't insert child to a tree-leaf!" ERROR_AT);
}



TreeNode* DefaultTreeLeaf::removeChild(int index)
{
	notImplementedError("Can't remove child from a tree-leaf!" ERROR_AT);
	return NULL;
}



TreeNode* DefaultTreeLeaf::replaceChild(int index, TreeNode* newChild)
{
	notImplementedError("Can't replace child at a tree-leaf!" ERROR_AT);
	return NULL;
}




} // namespace Trees
} // namespace BaseLib
