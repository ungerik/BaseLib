/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/DefaultTreeNode.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



BL_DEFINE_REFLECTION_CLASS(DefaultTreeNode, TreeNode)
{
}



DefaultTreeNode::DefaultTreeNode(bool subTreeIsHidden)
	: TreeNode()
	, children()
	, hideSubTree(subTreeIsHidden)
{
}



int DefaultTreeNode::getChildCountIncludingHiddenChildren() const
{
	return children.getCount();
}



TreeNode* DefaultTreeNode::getChild(int index)
{
	return children[index];
}



void DefaultTreeNode::addChild(TreeNode* newChild)
{
	if (checkArgumentNotNull(NAME_VALUE(newChild)) == true)
	{
		newChild->removeFromParent();
		children += newChild;
		newChild->setParent(this);
	}
}



void DefaultTreeNode::insertChild(TreeNode* newChild, int index)
{
	if (checkArgumentNotNull(NAME_VALUE(newChild)) == true)
	{
		children.insert(newChild, index);
		newChild->setParent(this);
	}
}



TreeNode* DefaultTreeNode::removeChild(int index)
{
	if (checkArgumentRange(NAME_VALUE(index), 0, children.getCount()-1) == true)
	{
		TreeNode* oldChild = children[index];
		oldChild->setParent(NULL);
		children.remove(index);
		return oldChild;
	}
	else
	{
		return NULL;
	}
}



TreeNode* DefaultTreeNode::replaceChild(int index, TreeNode* newChild)
{
	if (checkArgumentRange(NAME_VALUE(index), 0, children.getCount()-1) == true &&
		checkArgumentNotNull(NAME_VALUE(newChild)) == true)
	{
		TreeNode* oldChild = children[index];
		oldChild->setParent(NULL);

		children[index] = newChild;
		newChild->setParent(this);
		return oldChild;
	}
	else
	{
		return NULL;
	}
}



bool DefaultTreeNode::isSubTreeHidden() const
{
	return hideSubTree;
}




} // namespace Trees
} // namespace BaseLib
