/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeCloner.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;



TreeCloner::TreeCloner(const TreeNode* newSourceRootNode, CreateNodeFunctionPointer createNodeFunctionPointer, const String& exceptAttributeWithName, const NumberFormat* useNumberFormat)
	: TreeNode::AbstractFactory(createNodeFunctionPointer, useNumberFormat)
	, sourceRootNode(newSourceRootNode)
	, exceptAttribute(exceptAttributeWithName)
{
	checkArgumentNotNull(NAME_VALUE(newSourceRootNode));
}



TreeCloner::TreeCloner(const TreeNode* newSourceRootNode, CreateNodeFunctor& newCreateNodeFunctor, const String& exceptAttributeWithName, const NumberFormat* useNumberFormat)
	: TreeNode::AbstractFactory(newCreateNodeFunctor, useNumberFormat)
	, sourceRootNode(newSourceRootNode)
	, exceptAttribute(exceptAttributeWithName)
{
}



bool TreeCloner::buildTreeImplementation(bool ignoreText)
{
	return cloneNode(sourceRootNode);
}



bool TreeCloner::cloneNode(const TreeNode* sourceNode)
{
	BL_ASSERT(sourceNode != NULL);

	beginNode(sourceNode->getName());
	bool nodeAvailAble = isNodeAvailable();
	if (nodeAvailAble == true)
	{
		// Set attributes:
		onBeforeAttributesTransaction();
		const Enumeration<String>& attributeNames = sourceNode->getAttributeNames();
		foreach (Enumeration<String>::Iterator, i, attributeNames)
		{
			if (*i != exceptAttribute)
			{
				setNodeAttribute(*i, sourceNode->getAttribute(*i, numberFormat));
			}
		}
		onAfterAttributesTransaction();

		// Clone child-nodes recursive:
		//onBeforeChildrenTransaction();
		int childCount = sourceNode->getChildCount();
		for (int i = 0; i < childCount; ++i)
		{
			cloneNode(sourceNode->getChild(i));
		}
		//onAfterChildrenTransaction();
	}
	endNode();

	return nodeAvailAble;
}



} // namespace Trees
} // namespace BaseLib
