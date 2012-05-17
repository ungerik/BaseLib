/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/AbstractTreeIterator.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/Math.h"
#include "BaseLib/Functors/Finder.h"
#include "BaseLib/intern/Errors.h"



namespace BaseLib {
namespace Trees {



using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Strings;
using namespace BaseLib::Containers;
using namespace BaseLib::Functors;



BL_DEFINE_REFLECTION_BASE_CLASS(BaseLib::Trees::AbstractTreeIterator)
{
	registerProperty("attribute", &AbstractTreeIterator::isAttribute);
	registerProperty("name", &AbstractTreeIterator::getName);
	registerProperty("namespace", &AbstractTreeIterator::getNamespace);
	registerProperty("readable", &AbstractTreeIterator::isReadable);
	registerProperty("writeable", &AbstractTreeIterator::isWriteable);
	registerProperty("path", &AbstractTreeIterator::getPath);
	registerProperty("nodePosition", &AbstractTreeIterator::getNodePosition);
	registerProperty("attributeCount", &AbstractTreeIterator::getAttributeCount);
	registerProperty("attributePosition", &AbstractTreeIterator::getAttributePosition);
	registerProperty("parentCount", &AbstractTreeIterator::getParentCount);
	registerProperty("childNodePosition", &AbstractTreeIterator::getChildNodePosition);
	registerProperty("childNodeCount", &AbstractTreeIterator::getChildNodeCount);
	registerProperty("hasNextNodeSibling", &AbstractTreeIterator::hasNextNodeSibling);
	registerProperty("hasPreviousNodeSibling", &AbstractTreeIterator::hasPreviousNodeSibling);
}



AbstractTreeIterator::~AbstractTreeIterator()
{
}



bool AbstractTreeIterator::hasMetaTag(const String& metaTag) const
{
	return false;
}



String AbstractTreeIterator::getValueOfAttribute(int attributePosition) const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);

	String result;
	unconst->push();
	if (unconst->moveToAttribute(attributePosition) == true)
	{
		result = getValue();
	}	
	unconst->pop();
	return result;
}



void AbstractTreeIterator::setValueOfAttribute(int attributePosition, const String& newValue) const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);

	unconst->push();
	if (unconst->moveToAttribute(attributePosition) == true)
	{
		setValue(newValue);
	}	
	unconst->pop();
}



String AbstractTreeIterator::getValueOfAttribute(const String& attributeName) const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);

	String result;
	unconst->push();
	if (unconst->moveToAttribute(attributeName) == true)
	{
		result = getValue();
	}	
	unconst->pop();
	return result;
}



void AbstractTreeIterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);

	unconst->push();
	if (unconst->moveToAttribute(attributeName) == true)
	{
		setValue(newValue);
	}	
	unconst->pop();
}



String AbstractTreeIterator::getType() const
{
	return Empty();
}



bool AbstractTreeIterator::isDefaultValue() const
{
	return false;
}



void AbstractTreeIterator::setDefaultValue() const
{
}



const Enumeration<String>& AbstractTreeIterator::getValueRange() const
{
	static EmptyEnumeration<String> result;
	return result;
}



String getSiblingPositionString(const AbstractTreeIterator* treeIterator)
{
	if (treeIterator->isAttribute() == false && treeIterator->hasParent() == true)
	{
		int position = 0;
		String name = treeIterator->getName();

		AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(treeIterator);
		unconst->push();

		while (unconst->moveToPreviousNodeSibling() == true && unconst->getName() == name)
		{
			++position;
		}

		unconst->pop();

		if (position > 0)
		{
			return '[' + String::createFrom(position) + ']';
		}
	}	
	return Empty();
}



String AbstractTreeIterator::getPath() const
{
	String path = (isAttribute() == false) ? '/' + getName() + getSiblingPositionString(this) : '@' + getName();

	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
	unconst->push();

	while (unconst->moveToParent() == true)
	{
		path.insert('/' + getName() + getSiblingPositionString(this));
	}

	unconst->pop();
	return path;
}



bool AbstractTreeIterator::moveTo(const String& path)
{
	push();

	if (path.beginsWith('/') == true)
	{
		moveToRootNode();
	}

	StringTokenizer tokenizer(path, '/');
	while (tokenizer.hasNextToken() == true)
	{
		String token = tokenizer.nextToken();
		if (token == '.')
		{
		}
		else if (token == "..")
		{
			if (moveToParent() == false)
			{
				pop();
				return false;				
			}
		}
		else 
		{
			int at = token.findFirst('@');
			String childName = token.subString(0, at);
			if (moveToChildNode(childName) == false)
			{
				pop();
				return false;				
			} 
			if (at != String::END)
			{
				String attributeName = token.subString(at+1);
				if (moveToAttribute(attributeName) == false)
				{
					pop();
					return false;
				}
			}
		}
	}

	pop(false);
	return true;
}



int AbstractTreeIterator::getNodePosition() const
{
	int position = 0;

	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
	unconst->push();
	while (unconst->moveToPreviousNode() == true)
	{
		++position;
	}
	unconst->pop();

	return position;
}



bool AbstractTreeIterator::moveToNodePosition(int nodePosition)
{
	push();
	moveToRootNode();
	
	for (int i = 0; i < nodePosition; ++i)
	{
		if (moveToNextNode() == false)
		{
			pop();
			return false;
		}
	}

	pop(false);
	return true;
}



bool AbstractTreeIterator::moveToNextNode()
{
	if (getChildNodeCount() > 0) // go down
	{
		return moveToChildNode(0);
	}
	else if (hasNextNodeSibling() == true) // go sidewards
	{
		return moveToNextNodeSibling();
	}
	else // go up
	{
		push();

		while (hasParent() == true)
		{			
			moveToParent();
			if (moveToNextNodeSibling() == true)
			{
				pop(false);
				return true;
			}
		}

		pop();
		return false;
	}
}



bool AbstractTreeIterator::moveToPreviousNode()
{
	push();

	if (isAttribute() == true)
	{
		moveToParent();
	}

	int childPosition = getChildNodePosition();
	if (childPosition != 0)
	{
		moveToParent();

		if (childPosition > 0)
		{
			moveToChildNode(childPosition - 1);
			for (int childCount = getChildNodeCount(); childCount > 0; childCount = getChildNodeCount())
			{
				moveToChildNode(childCount-1);
			}
		}

		pop(false);
		return true;
	}

	pop();
	return false;
}



bool AbstractTreeIterator::hasAttribute(const String& attributeName) const
{
	Finder<String> finder(attributeName);
	enumAttributeNames(finder);
	return finder.hasResult();
}



bool AbstractTreeIterator::moveToAttribute(const String& attributeName)
{
	push();

	if (isAttribute() == true)
	{
		moveToParent();
	}

	int attributeCount = getAttributeCount();
	for (int i = 0; i < attributeCount; ++i)
	{
		moveToAttribute(i);
		if (getName() == attributeName)
		{
			pop(false);
			return true;
		}
		moveToParent();
	}

	pop();
	return false;
}



bool AbstractTreeIterator::moveToNextAttribute()
{
	if (isAttribute() == true)
	{
		int nextAttributePosition = getAttributePosition() + 1;
		push();
		moveToParent();
		int attributeCount = getAttributeCount();
		if (nextAttributePosition < attributeCount)
		{
			pop(false);
			return moveToAttribute(nextAttributePosition);
		}
		else
		{
			pop();
			return false;
		}
	}
	else
	{
		if (getAttributeCount() > 0)
		{
			return moveToAttribute(0);
		}
		else
		{
			return false;
		}
	}
}



bool AbstractTreeIterator::moveToPreviousAttribute()
{
	if (isAttribute() == true)
	{
		int previousAttributePosition = getAttributePosition() - 1;
		push();
		moveToParent();
		if (previousAttributePosition >= 0)
		{
			pop(false);
			return moveToAttribute(previousAttributePosition);
		}
		else
		{
			pop();
			return false;
		}
	}
	else
	{
		return false;
	}
}



void AbstractTreeIterator::enumAttributeNames(const Enumerator<String>& enumerator) const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
	unconst->push();
	for (int i = 0; unconst->moveToAttribute(i) == true && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(getName());
	}
	unconst->pop();
}



int AbstractTreeIterator::getParentCount() const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
	unconst->push();
	int parentCount = 0;
	while (unconst->moveToParent() == true)
	{
		++parentCount;
	}
	unconst->pop();
	return parentCount;
}



bool AbstractTreeIterator::moveToParent(int parentGeneration)
{
	push();
	for (int i = 0; i < parentGeneration; ++i)
	{
		if (moveToParent() == false)
		{
			pop();
			return false;
		}
	}
	pop(false);
	return true;
}



bool AbstractTreeIterator::moveToParent(const String& parentName, int count)
{
	if (count > 0)
	{
		push();
		int foundParents = 0;
		while (moveToParent() == true)
		{
			if (getName() == parentName)
			{
				if (++foundParents == count)
				{
					pop(false);
					return true;
				}
			}
		}
		pop();
	}
	return false;
}



bool AbstractTreeIterator::moveToParentOrSelf(const String& parentOrSelfName)
{
	if (getName() == parentOrSelfName)
	{
		return true;
	}
	else
	{
		return moveToParent(parentOrSelfName);
	}
}



void AbstractTreeIterator::moveToRootNode()
{
	while (moveToParent() == true);
}



bool AbstractTreeIterator::canHaveChildNodes() const
{
	return isAttribute() == false;
}



bool AbstractTreeIterator::hasChildNodes() const
{
	return getChildNodeCount() > 0;
}



bool AbstractTreeIterator::hasChildNode(const String& childName) const
{
	Finder<String> finder(childName);
	enumChildNodeNames(finder);
	return finder.hasResult();
}



bool AbstractTreeIterator::moveToChildNode(const String& childName)
{
	int childCount = getChildNodeCount();
	if (childCount > 0)
	{
		push();
		for (int i = 0; i < childCount; ++i)
		{
			moveToChildNode(i);
			if (getName() == childName)
			{
				pop(false);
				return true;
			}
			moveToParent();
		}
		pop();
	}
	return false;
}



void AbstractTreeIterator::enumChildNodeNames(const Enumerator<String>& enumerator) const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
	for (int i = 0; unconst->moveToChildNode(i) == true && enumerator.stop() == false; ++i)
	{
		enumerator.enumerate(getName());
		unconst->moveToParent();
	}
}



bool AbstractTreeIterator::hasNextNodeSibling() const
{
	AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
	unconst->push();
	if (isAttribute() == true)
	{
		unconst->moveToParent();
	}

	bool result = false;
	int childPosition = getChildNodePosition();
	if (childPosition != -1)
	{
		unconst->moveToParent();
		int childCount = getChildNodeCount();
		result = (childPosition + 1) < childCount;
	}
	unconst->pop();
	return result;
}



bool AbstractTreeIterator::moveToNextNodeSibling(int count)
{
	if (count != 0 && hasParent() == true)
	{
		push();

		if (isAttribute() == true)
		{
			moveToParent();
		}		

		int childPosition = getChildNodePosition();
		if (childPosition != -1)
		{
			bool result = moveToParent();
			BL_ASSERT(result == true);
			int siblingPosition = childPosition + count;
			if (siblingPosition >= 0 && siblingPosition < getChildNodeCount())
			{
				pop(false);
				return moveToChildNode(siblingPosition);
			}
		}

		pop();
	}
	return false;
}



bool AbstractTreeIterator::moveToNextNodeSibling(const String& siblingName, int count)
{
	if (count != 0)
	{
		push();
		if (isAttribute() == true)
		{
			moveToParent();
		}

		int childPosition = getChildNodePosition();
		if (childPosition != -1)
		{
			moveToParent();
			int direction = sign(count); // -1 or +1
			int foundSiblings = 0;
			while (moveToChildNode(childPosition += direction) == true)
			{
				if (getName() == siblingName)
				{
					foundSiblings += direction;
					if (foundSiblings == count)
					{
						pop(false);
						return true;
					}
				}
				moveToParent();
			}

		}

		pop();
	}
	return false;
}



bool AbstractTreeIterator::hasPreviousNodeSibling() const
{
	if (isAttribute() == true)
	{
		AbstractTreeIterator* unconst = const_cast<AbstractTreeIterator*>(this);
		unconst->push();
		unconst->moveToParent();
		int childPosition = getChildNodePosition();
		unconst->pop();
		return childPosition > 0;
	}
	else
	{
		return getChildNodePosition() > 0;
	}
}



bool AbstractTreeIterator::moveToPreviousNodeSibling(int count)
{
	return moveToNextNodeSibling(-count);
}



bool AbstractTreeIterator::moveToPreviousNodeSibling(const String& siblingName, int count)
{
	return moveToNextNodeSibling(siblingName, -count);
}



} // namespace Trees
} // namespace BaseLib
