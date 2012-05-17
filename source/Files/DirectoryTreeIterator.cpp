/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/DirectoryTreeIterator.h"
#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/Functors/Counter.h"
#include "BaseLib/Functors/Adder.h"
#include "BaseLib/Functors/Finder.h"
#include "BaseLib/Functors/ValueAtIndexFinder.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Strings/StringTokenizer.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Streams/StringInputStream.h"
#include "BaseLib/Streams/StringOutputStream.h"



namespace BaseLib {
namespace Files {



using namespace BaseLib::Streams;
using namespace BaseLib::Strings;
using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Trees;
using namespace BaseLib::Containers;
using namespace BaseLib::Functors;
using namespace BaseLib::Buffers;



BL_DEFINE_REFLECTION_CLASS(DirectoryTreeIterator, AbstractTreeIterator)
{
}




DirectoryTreeIterator::DirectoryTreeIterator(AbstractFileSystem* forFileSystem, bool enumHiddenDirectories, bool enumSystemDirectories, const NumberFormat* useNumberFormat)
	: fileSystem(forFileSystem)
	, constFileSystem(forFileSystem)
	, currentPath()
	, currentAttribute()
	, stateStack()
	, enumHiddenDirectories(enumHiddenDirectories)
	, enumSystemDirectories(enumSystemDirectories)
	, numberFormat(useNumberFormat)
{
}



DirectoryTreeIterator::DirectoryTreeIterator(const AbstractFileSystem* forConstFileSystem, bool enumHiddenDirectories, bool enumSystemDirectories, const NumberFormat* useNumberFormat)
	: fileSystem(NULL)
	, constFileSystem(forConstFileSystem)
	, currentPath()
	, currentAttribute()
	, stateStack()
	, enumHiddenDirectories(enumHiddenDirectories)
	, enumSystemDirectories(enumSystemDirectories)
	, numberFormat(useNumberFormat)
{
}



AbstractTreeIterator* DirectoryTreeIterator::clone() const
{
	return (isFileSystemConst() == true) ?
		new DirectoryTreeIterator(constFileSystem) :
		new DirectoryTreeIterator(fileSystem);
}



bool DirectoryTreeIterator::operator ==(const AbstractTreeIterator& right) const
{
	const AbstractTreeIterator* rightImplementation = BaseLib::Trees::TreeIterator::getImplementation(right);
	return
		rightImplementation->getClass() == CLASS &&
		static_cast<const DirectoryTreeIterator*>(rightImplementation)->fileSystem == fileSystem &&
		static_cast<const DirectoryTreeIterator*>(rightImplementation)->constFileSystem == constFileSystem &&
		static_cast<const DirectoryTreeIterator*>(rightImplementation)->currentPath == currentPath &&
		static_cast<const DirectoryTreeIterator*>(rightImplementation)->currentAttribute == currentAttribute;
}



bool DirectoryTreeIterator::isAttribute() const
{
	return currentAttribute.isEmpty() == false;
}



String DirectoryTreeIterator::getName() const
{
	return isAttribute() == true ? currentAttribute : getCurrentNodeName();
}



String DirectoryTreeIterator::getNamespace() const
{
	return Empty();
}



bool DirectoryTreeIterator::hasMetaTag(const String& metaTag) const
{
	return false;
}



bool DirectoryTreeIterator::isReadable() const
{
	if (constFileSystem != NULL)
	{
		return isAttribute() == true ? true : constFileSystem->isReadable(currentPath);
	}
	else
	{
		return false;
	}
}



bool DirectoryTreeIterator::isWriteable() const
{
	if (constFileSystem != NULL)
	{
		if (isAttribute() == true)
		{
			// switch writeable attributes...
			return false;
		}
		else
		{
			return constFileSystem->isWriteable(currentPath);
		}
	}
	else
	{
		return false;
	}
}



InputStream* DirectoryTreeIterator::createInputStream() const
{
	return NULL;
}



OutputStream* DirectoryTreeIterator::createOutputStream() const
{
	return NULL;
}



String DirectoryTreeIterator::getValue() const
{	
	return getValueOfAttribute(currentAttribute);
}



void DirectoryTreeIterator::setValue(const String& newValue) const
{
}



String DirectoryTreeIterator::getValueOfAttribute(const String& attributeName) const
{
	return Empty();
}



void DirectoryTreeIterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
}



String DirectoryTreeIterator::getType() const
{
	return Empty();
}



bool DirectoryTreeIterator::isDefaultValue() const
{
	return false;
}



void DirectoryTreeIterator::setDefaultValue() const
{
}



const Enumeration<String>& DirectoryTreeIterator::getValueRange() const
{
	static const EmptyEnumeration<String> emptyStringEnumeration;
	return emptyStringEnumeration;
}



void DirectoryTreeIterator::push()
{
	stateStack.push(State(currentPath, currentAttribute));
}



void DirectoryTreeIterator::pop(bool restorePosition, bool restoreStack)
{
	if (restorePosition == true)
	{
		currentPath = stateStack.top().path;
		currentAttribute = stateStack.top().attribute;
	}
	if (restoreStack == true)
	{
		stateStack.pop();
	}
}



int DirectoryTreeIterator::getAttributeCount() const
{
	return 2;
}



int DirectoryTreeIterator::getAttributePosition() const
{
	return -1;
}



bool DirectoryTreeIterator::moveToAttribute(int attributePosition)
{
	return false;
}



bool DirectoryTreeIterator::moveToAttribute(const String& attributeName)
{
	return false;
}



bool DirectoryTreeIterator::hasParent() const
{
	return currentPath.isEmpty() == false || isAttribute() == true;
}



bool DirectoryTreeIterator::moveToParent()
{
	if (isAttribute() == true)
	{
		currentAttribute.setLength(0);
		return true;
	}
	else
	{
		if (currentPath.isEmpty() == false)
		{
			currentPath = getParentPath();
			return true;
		}
		else
		{
			return false;
		}
	}
}



bool DirectoryTreeIterator::canHaveChildNodes() const
{
	return true;
}



bool DirectoryTreeIterator::hasChildNodes() const
{
	return constFileSystem->isEmpty(currentPath) == false;
}



bool DirectoryTreeIterator::hasChildNode(const String& childName) const
{
	String path = currentPath;
	if (currentPath.isEmpty() == true)
	{
		path = childName;
	}
	else
	{
		path.ensureEndsWith('/');
		path += childName;
	}

	return constFileSystem->exists(path);
}



int DirectoryTreeIterator::getChildNodeCount() const
{
	Counter<String> counter;
	constFileSystem->enumDirectoryNames(counter, currentPath, enumHiddenDirectories, enumSystemDirectories);
	return counter.getCount();
}



int DirectoryTreeIterator::getChildNodePosition() const
{
	if (currentPath.isEmpty() == false)
	{
		String parentPath = getParentPath();
		String currentNodeName = getCurrentNodeName();
		
		Finder<String> finder(currentNodeName);
		constFileSystem->enumDirectoryNames(finder, parentPath, enumHiddenDirectories, enumSystemDirectories);
		if (finder.hasResult() == true)
		{
			return finder.getIndex();
		}
	}

	return -1;
}



bool DirectoryTreeIterator::moveToChildNode(int childPosition)
{
	ValueAtIndexFinder<String> valueAtIndexFinder(childPosition);
	constFileSystem->enumDirectoryNames(valueAtIndexFinder, currentPath);
	if (valueAtIndexFinder.hasResult() == false)
	{
		return false;
	}

	if (currentPath.isEmpty() == true)
	{
		currentPath = valueAtIndexFinder.getValue();
	}
	else
	{
		currentPath.ensureEndsWith('/');
		currentPath += valueAtIndexFinder.getValue();
	}
	return true;
}



bool DirectoryTreeIterator::moveToChildNode(const String& childName)
{
	String newPath = currentPath;
	if (currentPath.isEmpty() == true)
	{
		newPath = childName;
	}
	else
	{
		newPath.ensureEndsWith('/');
		newPath += childName;
	}

	if (constFileSystem->exists(newPath) == true && constFileSystem->isDirectory(newPath) == true)
	{
		currentPath = newPath;
		return true;
	}
	else
	{
		return false;
	}
}



void DirectoryTreeIterator::enumChildNodeNames(const Enumerator<String>& enumerator) const
{
	constFileSystem->enumDirectoryNames(enumerator, currentPath);
}



String DirectoryTreeIterator::getCurrentNodeName() const
{
	int length = currentPath.getLength();
	if (currentPath.endsWith('/') == true) --length;
	int slashPos = currentPath.findLast('/', 0, length);
	return currentPath.subString(slashPos+1, length-slashPos-1);
}



String DirectoryTreeIterator::getParentPath() const
{
	BL_ASSERT(currentPath.isEmpty() == false);
	int length = currentPath.getLength();
	if (currentPath.endsWith('/') == true) --length;
	int slashPos = currentPath.findLast('/', 0, length);
	return currentPath.subString(0, slashPos+1);
}



} // namespace Files
} // namespace BaseLib
