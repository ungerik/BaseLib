/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Strings/StringTokenizer.h"

#include "BaseLib/Console.h" // For debug



namespace BaseLib {
namespace Trees {



using namespace ErrorHandling;
using BaseLib::Strings::StringTokenizer;



TreeNode::AbstractFactory::AbstractFactory(CreateNodeFunctionPointer createNodeFunctionPointer, const NumberFormat* useNumberFormat)
	: parentNode(NULL)
	, currentNode(NULL)
	, numberFormat(useNumberFormat)
	, createNodeFunctor(new CreateNodeFunctionFunctor(createNodeFunctionPointer))
{
	checkArgumentNotNull(NAME_VALUE(createNodeFunctionPointer));
	checkArgumentNotNull(NAME_VALUE(useNumberFormat));
}



TreeNode::AbstractFactory::AbstractFactory(CreateNodeFunctor& newCreateNodeFunctor, const NumberFormat* useNumberFormat)
	: parentNode(NULL)
	, currentNode(NULL)
	, numberFormat(useNumberFormat)
	, createNodeFunctor(newCreateNodeFunctor.clone())
{
	checkArgumentNotNull(NAME_VALUE(useNumberFormat));
}



TreeNode::AbstractFactory::~AbstractFactory()
{
	if (currentNode != NULL)
	{
		currentNode->removeFromParent_DeleteSelfAndSubTree();
	}
}



TreeNode* TreeNode::AbstractFactory::buildTree(TreeNode* rootNode, bool ignoreText)
{
	parentNode = rootNode;
	BL_ASSERT(currentNode == NULL);

	if (buildTreeImplementation(ignoreText) == true)
	{
		BL_ASSERT(rootNode == NULL || currentNode == rootNode);
		TreeNode* result = currentNode;
		currentNode = NULL;
		return result;
	}
	else
	{
		resultError("Error while buildTreeImplementation()!" ERROR_AT);
		return NULL;
	}
}



void TreeNode::AbstractFactory::beginNode(const String& name)
{
	if (currentNode != NULL)
	{
		parentNode = currentNode; // New parent only when != NULL (we ignore NULL nodes)
	}

	currentNode = (*createNodeFunctor)(name);

	if (currentNode != NULL && parentNode != NULL)
	{
		parentNode->addChild(currentNode);
	}
}



void TreeNode::AbstractFactory::onBeforeAttributesTransaction()
{
	if (currentNode != NULL)
	{
		currentNode->onBeforeAttributesTransaction();
	}
}



void TreeNode::AbstractFactory::setNodeAttribute(const String& attributeName, const String& attributeValue)
{
	if (currentNode != NULL)
	{
		//Console::trace << attributeName << ": " << attributeValue << BaseLib::Streams::newLine;
		//if (attributeName == "id")
		//{
		//	if (attributeValue == "PortOfLoadingComboBox")
		//	{
		//		int x = 0;
		//	}
		//	else if (attributeValue == "PortOfDestinationComboBox")
		//	{
		//		int x = 0;
		//	}
		//}
		currentNode->setAttribute(attributeName, attributeValue, numberFormat);
	}
	else
	{
		//stateError("No node available to set an attribute!" ERROR_AT);
	}
}



void TreeNode::AbstractFactory::appendNodeAttribute(const String& attributeName, const String& attributeValue)
{
	if (currentNode != NULL)
	{
		currentNode->setAttribute(attributeName, currentNode->getAttribute(attributeName, numberFormat) + attributeValue, numberFormat);
	}
	else
	{
		//stateError("No node available to set an attribute!" ERROR_AT);
	}
}



void TreeNode::AbstractFactory::onAfterAttributesTransaction()
{
	if (currentNode != NULL)
	{
		currentNode->onAfterAttributesTransaction();
	}
}



void TreeNode::AbstractFactory::onBeforeChildrenTransaction()
{
	if (currentNode != NULL)
	{
		currentNode->onBeforeChildrenTransaction();
	}
}



void TreeNode::AbstractFactory::onAfterChildrenTransaction()
{
	if (currentNode != NULL)
	{
		currentNode->onAfterChildrenTransaction();
	}
}



void TreeNode::AbstractFactory::endNode()
{
	if (parentNode != NULL) // We ignore the rootNode, so currentNode won't get NULL
	{
		currentNode = parentNode;
		parentNode = parentNode->getParent();
	}
}



bool TreeNode::AbstractFactory::nodeHasAttribute(const String& attributeName) const
{
	if (currentNode != NULL)
	{
		return currentNode->hasAttribute(attributeName);
	}
	else
	{
		return false;
	}
}



String TreeNode::AbstractFactory::getNodeName() const
{
	if (currentNode != NULL)
	{
		return currentNode->getName();
	}
	else
	{
		return Empty();
	}
}



void TreeNode::AbstractFactory::setNumberFormat(const NumberFormat* newNumberFormat)
{
	if (checkArgumentNotNull(NAME_VALUE(newNumberFormat)) == true)
	{
		numberFormat = newNumberFormat;
	}
}



} // namespace Trees
} // namespace BaseLib
