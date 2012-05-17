/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Strings/StringTokenizer.h"



//#include "BaseLib/Console.h" // For debugging



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;
using BaseLib::Strings::StringTokenizer;



BL_DEFINE_REFLECTION_BASE_CLASS(TreeNode)
{
	registerProperty("name", &TreeNode::getName);
	registerProperty("leafType", &TreeNode::isLeafType);
	registerProperty("hasParent", &TreeNode::hasParent);
	registerProperty("childCount", &TreeNode::getChildCountIncludingHiddenChildren);
	registerProperty("hiddenSubTree", &TreeNode::isSubTreeHidden);
	registerProperty("attributes", &TreeNode::getAttributeNamesAsString);
}



TreeNode::TreeNode()
	: parent(NULL)
{
}

	
	
TreeNode::~TreeNode()
{
}



void TreeNode::deleteSelf()
{
	delete this;
}



void TreeNode::deleteSelfAndSubTree()
{
	for (int i = getChildCount()-1; i >= 0; --i)
	{
		TreeNode* child = getChild(i);
		child->setParent(NULL); // For performance prevent child from calling removeFromParent()
		child->deleteSelfAndSubTree();
	}

	deleteSelf();
}



void TreeNode::deleteSelfAndSubTreeIncludingHiddenChildren()
{
	for (int i = getChildCountIncludingHiddenChildren()-1; i >= 0; --i)
	{
		TreeNode* child = getChild(i);
		child->setParent(NULL); // For performance prevent child from calling removeFromParent()
		child->deleteSelfAndSubTree();
	}

	deleteSelf();
}



void TreeNode::removeFromParent_DeleteSelfAndSubTree()
{
	for (int i = getChildCountIncludingHiddenChildren()-1; i >= 0; --i)
	{
		getChild(i)->removeFromParent_DeleteSelfAndSubTree();
	}

	if (parent != NULL)
	{
		const int childIndexAtParent = getChildIndexAtParent();
		if (childIndexAtParent != -1)
		{
			parent->removeChild(childIndexAtParent);
		}
		else
		{
			stateError("Child is not registered at parent!" ERROR_AT);
		}
	}

	deleteSelf();
}



bool TreeNode::isLeafType() const
{
	return false;
}



TreeNode* TreeNode::getParentForGetRootNode(bool rootNodeOfHiddenSubTree)
{
	return rootNodeOfHiddenSubTree == true && isSubTreeHidden() == true ? NULL : getParent();
}



void TreeNode::setParent(TreeNode* newParent)
{
	BL_ASSERT(newParent == NULL || parent == NULL);
	beforeSomeParentNodeChanges(this, parent, newParent);
	parent = newParent;
}



void TreeNode::beforeSomeParentNodeChanges(TreeNode* treeNode, TreeNode* oldParentNode, TreeNode* newParentNode)
{
	const int childCount = getChildCountIncludingHiddenChildren();
	for (int i = 0; i < childCount; ++i)
	{
		//Console::trace << getChild(i)->getReflectionObject()->getClass()->getName() << "   " << getChild(i)->getReflectionObject()->getProperty("id") << BaseLib::Streams::newLine;
		getChild(i)->beforeSomeParentNodeChanges(treeNode, oldParentNode, newParentNode);
	}
}



TreeNode& TreeNode::getRootNode()
{
	TreeNode* rootNode = this;
	for (TreeNode* usedParent = rootNode->getParentForGetRootNode(false); usedParent != NULL; usedParent = rootNode->getParentForGetRootNode(false))
	{
		rootNode = usedParent;
	}
	return *rootNode;
}



TreeNode& TreeNode::getRootNodeOfHiddenSubTree()
{
	TreeNode* rootNode = this;
	for (TreeNode* usedParent = rootNode->getParentForGetRootNode(true); usedParent != NULL; usedParent = rootNode->getParentForGetRootNode(true))
	{
		rootNode = usedParent;
	}
	return *rootNode;
}



TreeNode* TreeNode::getChildIfExists(const String& childName, int count)
{
	if (count > 0)
	{
		int foundChildren = 0;
		const int childCount = getChildCount();
		for (int i = 0; i < childCount; ++i)
		{
			TreeNode* childNode = getChild(i);
			if (childNode->getName() == childName)
			{
				if (++foundChildren == count)
				{
					return childNode;
				}
			}
		}
	}
	return NULL;
}



int TreeNode::getChildIndexAtParent() const
{
	if (parent != NULL)
	{
		const int siblingCount = parent->getChildCountIncludingHiddenChildren();
		for (int i = 0; i < siblingCount; ++i)
		{
			if (parent->getChild(i) == this) return i;
		}
	}

	return -1;
}



bool TreeNode::removeFromParent()
{
	const int childIndexAtParent = getChildIndexAtParent();
	if (childIndexAtParent != -1)
	{
		BL_ASSERT(parent != NULL);
		parent->removeChild(childIndexAtParent);
		parent = NULL;
		return true;
	}
	else
	{
		return false;
	}
}



bool TreeNode::isSubTreeHidden() const
{
	return false;
}



void TreeNode::onBeforeAttributesTransaction()
{
}



void TreeNode::onAfterAttributesTransaction()
{
}



void TreeNode::onBeforeChildrenTransaction()
{
}



void TreeNode::onAfterChildrenTransaction()
{
	//const int childCount = getChildCountIncludingHiddenChildren();
	//for (int i = 0; i < childCount; ++i)
	//{
	//	getChild(i)->onAfterChildrenTransaction();
	//}
}



String TreeNode::getAttribute(const String& attributeName, const NumberFormat* numberFormat) const
{
	String attributeValue;
	if (getAttributeIfAvailable(attributeName, attributeValue, numberFormat) == false)
	{
		argumentError(ATTRIBUTE_DOESNT_EXIST(attributeName));
	}
	return attributeValue;
}



Object* TreeNode::getReflectionObject()
{
	return this;
}



const Object* TreeNode::getReflectionObject() const
{
	return this;
}



String TreeNode::getPath() const
{
	if (parent != NULL)
	{
		String name = getName();
		int siblingsBeforeWithSameName = 0;
		for (int index = getChildIndexAtParent()-1; index >= 0; --index)
		{
			if (parent->getChild(index)->getName() == name)
			{
				++siblingsBeforeWithSameName;
			}
			else
			{
				break;
			}
		}		
		String path = parent->getPath() + '/' + name;
		if (siblingsBeforeWithSameName > 0)
		{
			path += '[' + String::createFrom(siblingsBeforeWithSameName+1) + ']';
		}
		return path;
	}
	else
	{
		return "/" + getName();
	}
}



TreeNode* TreeNode::findNodeByAttributeValueInWholeTree(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	TreeNode* rootNode = &getRootNodeOfHiddenSubTree();
	if (rootNode->isSubTreeHidden() == false)
	{
		// We are at the normal root-node whithout hidden children
		BL_ASSERT(rootNode->getParent() == NULL);
		return rootNode->findNodeByAttributeValueInSubTree(attributeName, attributeValue, false, numberFormat);
	}
	else
	{
		// The root-node has hidden children, so check if we can find the attribute in the sub-tree of this node
		TreeNode* resultNode = rootNode->findNodeByAttributeValueInSubTree(attributeName, attributeValue, true, numberFormat);
		while (resultNode == NULL && rootNode->isSubTreeHidden() == true)
		{
			rootNode = rootNode->getParent();
			if (rootNode != NULL && rootNode->getParent() != NULL)
			{
				// If we can't find a node in the hidden sub-tree, try the sub-trees in parent direction
				rootNode = &rootNode->getRootNodeOfHiddenSubTree();
				resultNode = rootNode->findNodeByAttributeValueInSubTree(attributeName, attributeValue, true, numberFormat);
			}
			else
			{
				// If no parent, we have reached the real root-node, so we can't find other nodes anymore
				return NULL;
			}
		}
		return resultNode;
	}
}



TreeNode* TreeNode::findNodeByAttributeValueInWholeTreeIncludingHiddenChildren(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	TreeNode* rootNode = &getRootNodeOfHiddenSubTree();
	TreeNode* resultNode = rootNode->findNodeByAttributeValueInSubTreeIncludingHiddenChildren(attributeName, attributeValue, numberFormat);
	if (resultNode == NULL && rootNode->getParent() != NULL)
	{
		rootNode = &rootNode->getRootNode();
		resultNode = rootNode->findNodeByAttributeValueInSubTreeIncludingHiddenChildren(attributeName, attributeValue, numberFormat);
	}
	return resultNode;
}



TreeNode* TreeNode::findNodeByAttributeValueInSubTree(const String& attributeName, const String& attributeValue, bool includeHiddenDirectChildren, const NumberFormat* numberFormat)
{
	String attribute;
	if (getAttributeIfAvailable(attributeName, attribute, numberFormat) == true && attribute == attributeValue)
	{
		return this;
	}
	else
	{	
		const int childCount = includeHiddenDirectChildren == true ? getChildCountIncludingHiddenChildren() : getChildCount();
		for (int i = 0; i < childCount; ++i)
		{
			TreeNode* result = getChild(i)->findNodeByAttributeValueInSubTree(attributeName, attributeValue, false, numberFormat);
			if (result != NULL)
			{
				return result;
			}
		}
		return NULL;
	}
}



TreeNode* TreeNode::findNodeByAttributeValueInSubTreeIncludingHiddenChildren(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat)
{
	String attribute;
	if (getAttributeIfAvailable(attributeName, attribute, numberFormat) == true && attribute == attributeValue)
	{
		return this;
	}
	else
	{	
		const int childCount = getChildCountIncludingHiddenChildren();
		for (int i = 0; i < childCount; ++i)
		{
			TreeNode* result = getChild(i)->findNodeByAttributeValueInSubTreeIncludingHiddenChildren(attributeName, attributeValue, numberFormat);
			if (result != NULL)
			{
				return result;
			}
		}
		return NULL;
	}
}



void TreeNode::xPathQuery(const String& xPath, const Enumerator<TreeNode*>& enumerator, bool includeHiddenChildren, const NumberFormat* numberFormat)
{
	// Get tokens of xPath:
	Array<String> tokens;
	StringTokenizer(xPath, "/").tokenizeTo(tokens);

	int tokenIndex = 0;

	// If we have tokens:
	if (tokens.isEmpty() == false)
	{
		TreeNode* currentNode;
		if (xPath.beginsWith('/') == true)
		{
			currentNode = &getRootNode();
			if (currentNode->getName() == tokens[0])
			{
				++tokenIndex;
			}
			else
			{
				return;
			}
		}
		else
		{
			currentNode = this;
		}
		currentNode->xPathTestNode(tokens, tokenIndex, enumerator, includeHiddenChildren, numberFormat);
	}
}



void TreeNode::xPathTestNode(const Array<String>& tokens, int tokenIndex, const Enumerator<TreeNode*>& enumerator, bool includeHiddenChildren, const NumberFormat* numberFormat)
{
	if (tokenIndex == tokens.getCount())
	{
		// If no further path-tokens are available, we are at the end of the path,
		// and have found a target-node to add to the result:
		enumerator.enumerate(this);
	}
	else
	{
		int nextTokenIndex = tokenIndex + 1;
		const String& token = tokens[tokenIndex];
		if (token == "..")
		{
			if (parent != NULL)
			{
				parent->xPathTestNode(tokens, nextTokenIndex, enumerator, includeHiddenChildren, numberFormat);
			}
			else
			{
				argumentError("XPath invalid for current tree!" ERROR_AT);
				return;
			}
		}
		else if (token == '.')
		{
			xPathTestNode(tokens, nextTokenIndex, enumerator, includeHiddenChildren, numberFormat);
		}
		else
		{
			int where = token.findFirst('[');
			if (where == String::END)
			{
				// If no [ was found:
				// For every child-node:
				int childCount = includeHiddenChildren == true ? getChildCountIncludingHiddenChildren() : getChildCount();
				for (int i = 0; i < childCount; ++i)
				{
					TreeNode* childNode = getChild(i);
					if (childNode->getName() == token || token == '*')
					{
						// If name of child-node is valid for the next path-token:
						childNode->xPathTestNode(tokens, nextTokenIndex, enumerator, includeHiddenChildren, numberFormat);
					}
				}
			}
			else
			{
				// If [ was found:
				String name = token.subString(0, where).trimTail();
				int countOfNodesWithMatchingName = 0;
				// For every child-node:
				int childCount = includeHiddenChildren == true ? getChildCountIncludingHiddenChildren() : getChildCount();
				for (int i = 0; i < childCount; ++i)
				{
					TreeNode* childNode = getChild(i);
					if (childNode->getName() == name || name == '*')
					{
						++countOfNodesWithMatchingName;

						// If name of child-node is valid for the next path-token,
						// get expression between [ and ]:
						String expression = token.subString(where + 1, token.findLast(']') - (where + 1));
						if (expression.beginsWith('@') == true)
						{
							// If we are dealing with an attribute:
							int equalPos = expression.findFirst('=');
							if (equalPos == String::END)
							{
								String attributeName = expression.subString(1);
								if (childNode->hasAttribute(attributeName) == true)
								{
									childNode->xPathTestNode(tokens, nextTokenIndex, enumerator, includeHiddenChildren, numberFormat);
								}
							}
							else
							{
								String attributeName = expression.subString(1, equalPos-1).trimTail();
								String value = expression.subString(equalPos + 1).trimFront();
								String attribute;
								if (getAttributeIfAvailable(attributeName, attribute, numberFormat) == true && attribute == value)
								{
									childNode->xPathTestNode(tokens, nextTokenIndex, enumerator, includeHiddenChildren, numberFormat);
								}
							}
						}
						else if (expression.isDec() == true)
						{
							// If we are dealing with a node-indexer:
							if (expression.parseInt() == countOfNodesWithMatchingName)
							{
								childNode->xPathTestNode(tokens, nextTokenIndex, enumerator, includeHiddenChildren, numberFormat);
							}
						}
						else
						{
							argumentError("Unsupported XPath expression: " + token + ERROR_AT);
						}

					} // if (childNode->getName() == name || name == '*')

				} // for (int i = 0; i < childCount; ++i)

			} // else if (where == String::END)

		} // else if (token == "..") else if if (token == '.')

	} // else if (tokenIndex == tokens.getLength())

}



String TreeNode::getAttributeNamesAsString() const
{
	return String().implode(getAttributeNames(), ' ');
}



int TreeNode::getChildCount() const
{
	return isSubTreeHidden() == false ? getChildCountIncludingHiddenChildren() : 0;
}



} // namespace Trees
} // namespace BaseLib
