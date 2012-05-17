/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Files/FileSystemTreeIterator.h"
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



#define DIRECTORY_ATTRIBUTE_NAME "directory"
#define SIZE_ATTRIBUTE_NAME "size"



const String FileSystemTreeIterator::FILE_TYPE = "File";
const String FileSystemTreeIterator::DIRECTORY_TYPE = "Directory";



BL_DEFINE_REFLECTION_CLASS(FileSystemTreeIterator, AbstractTreeIterator)
{
}




FileSystemTreeIterator::FileSystemTreeIterator(AbstractFileSystem* forFileSystem, bool enumHiddenFiles, bool enumSystemFiles, const NumberFormat* useNumberFormat)
	: fileSystem(forFileSystem)
	, constFileSystem(forFileSystem)
	, currentPath()
	, currentAttribute()
	, stateStack()
	, enumHiddenFiles(enumHiddenFiles)
	, enumSystemFiles(enumSystemFiles)
	, numberFormat(useNumberFormat)
{
}



FileSystemTreeIterator::FileSystemTreeIterator(const AbstractFileSystem* forConstFileSystem, bool enumHiddenFiles, bool enumSystemFiles, const NumberFormat* useNumberFormat)
	: fileSystem(NULL)
	, constFileSystem(forConstFileSystem)
	, currentPath()
	, currentAttribute()
	, stateStack()
	, enumHiddenFiles(enumHiddenFiles)
	, enumSystemFiles(enumSystemFiles)
	, numberFormat(useNumberFormat)
{
}



AbstractTreeIterator* FileSystemTreeIterator::clone() const
{
	return (isFileSystemConst() == true) ?
		new FileSystemTreeIterator(constFileSystem) :
		new FileSystemTreeIterator(fileSystem);
}



bool FileSystemTreeIterator::operator ==(const AbstractTreeIterator& right) const
{
	const AbstractTreeIterator* rightImplementation = BaseLib::Trees::TreeIterator::getImplementation(right);
	return
		rightImplementation->getClass() == CLASS &&
		static_cast<const FileSystemTreeIterator*>(rightImplementation)->fileSystem == fileSystem &&
		static_cast<const FileSystemTreeIterator*>(rightImplementation)->constFileSystem == constFileSystem &&
		static_cast<const FileSystemTreeIterator*>(rightImplementation)->currentPath == currentPath &&
		static_cast<const FileSystemTreeIterator*>(rightImplementation)->currentAttribute == currentAttribute;
}



bool FileSystemTreeIterator::isAttribute() const
{
	return currentAttribute.isEmpty() == false;
}



String FileSystemTreeIterator::getName() const
{
	return isAttribute() == true ? currentAttribute : getCurrentNodeName();
}



String FileSystemTreeIterator::getNamespace() const
{
	return Empty();
}



bool FileSystemTreeIterator::hasMetaTag(const String& metaTag) const
{
	return false;
}



bool FileSystemTreeIterator::isReadable() const
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



bool FileSystemTreeIterator::isWriteable() const
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



InputStream* FileSystemTreeIterator::createInputStream() const
{
	if (isAttribute() == true)
	{
		return new StringInputStream(StringInputStream::MethodFunctor<FileSystemTreeIterator>(this, &FileSystemTreeIterator::getValue));		
	}
	else
	{
		return isReadable() ? constFileSystem->createInputStream(currentPath) : NULL;
	}
}



OutputStream* FileSystemTreeIterator::createOutputStream() const
{
	if (isAttribute() == true)
	{
		return new StringOutputStream(ConstMethodFunctor1<FileSystemTreeIterator, void, const String&>(this, &FileSystemTreeIterator::setValue));		
	}
	else
	{
		return isWriteable() ? constFileSystem->createOutputStream(currentPath) : NULL;
	}
}



String FileSystemTreeIterator::getValue() const
{	
	return getValueOfAttribute(currentAttribute);
}



void FileSystemTreeIterator::setValue(const String& newValue) const
{
}



String FileSystemTreeIterator::getValueOfAttribute(const String& attributeName) const
{
	if (attributeName == "directory")
	{
		return String::createFrom(constFileSystem->isDirectory(currentPath));
	}
	else if (attributeName == "size")
	{
		return String::createFrom(constFileSystem->sizeOf(currentPath));
	}
	else
	{
		return Empty();
	}
}



void FileSystemTreeIterator::setValueOfAttribute(const String& attributeName, const String& newValue) const
{
}



String FileSystemTreeIterator::getType() const
{
	if (currentAttribute.isEmpty() == false)
	{
		if (currentAttribute == DIRECTORY_ATTRIBUTE_NAME)
		{
			return "bool";
		}
		else if (currentAttribute == SIZE_ATTRIBUTE_NAME)
		{
			return "int";
		}
		else
		{
			BL_ASSERT_NEVER_REACHED
			return Empty();
		}
	}
	else
	{
		return constFileSystem->isDirectory(currentPath) ? DIRECTORY_TYPE : FILE_TYPE;
	}
}



bool FileSystemTreeIterator::isDefaultValue() const
{
	return false;
}



void FileSystemTreeIterator::setDefaultValue() const
{
}



const Enumeration<String>& FileSystemTreeIterator::getValueRange() const
{
	static const EmptyEnumeration<String> emptyStringEnumeration;
	return emptyStringEnumeration;
}



void FileSystemTreeIterator::push()
{
	stateStack.push(State(currentPath, currentAttribute));
}



void FileSystemTreeIterator::pop(bool restorePosition, bool restoreStack)
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



int FileSystemTreeIterator::getAttributeCount() const
{
	return 2;
}



int FileSystemTreeIterator::getAttributePosition() const
{
	if (currentAttribute == DIRECTORY_ATTRIBUTE_NAME)
	{
		return DIRECTORY_ATTRIBUTE_POSITION;
	}
	else if (currentAttribute == SIZE_ATTRIBUTE_NAME)
	{
		return SIZE_ATTRIBUTE_POSITION;
	}
	else
	{
		return -1;
	}
}



bool FileSystemTreeIterator::moveToAttribute(int attributePosition)
{
	switch (attributePosition)
	{
		case DIRECTORY_ATTRIBUTE_POSITION:
			currentAttribute = DIRECTORY_ATTRIBUTE_NAME;
			return true;

		case SIZE_ATTRIBUTE_POSITION:
			currentAttribute = SIZE_ATTRIBUTE_NAME;
			return true;

		default:
			return false;
	}
}



bool FileSystemTreeIterator::moveToAttribute(const String& attributeName)
{
	if (attributeName == DIRECTORY_ATTRIBUTE_NAME || attributeName == SIZE_ATTRIBUTE_NAME)
	{
		currentAttribute = attributeName;
		return true;
	}
	else
	{
		return false;
	}
}



bool FileSystemTreeIterator::hasParent() const
{
	return currentPath.isEmpty() == false || isAttribute() == true;
}



bool FileSystemTreeIterator::moveToParent()
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



bool FileSystemTreeIterator::canHaveChildNodes() const
{
	return constFileSystem->isDirectory(currentPath);
}



bool FileSystemTreeIterator::hasChildNodes() const
{
	return constFileSystem->isDirectory(currentPath) == true && constFileSystem->isEmpty(currentPath) == false;
}



bool FileSystemTreeIterator::hasChildNode(const String& childName) const
{
	if (constFileSystem->isDirectory(currentPath) == false)
	{
		return false;
	}

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



int FileSystemTreeIterator::getChildNodeCount() const
{
	if (constFileSystem->isDirectory(currentPath) == true)
	{
		Counter<String> counter;
		constFileSystem->enumFileNames(counter, currentPath, enumHiddenFiles, enumSystemFiles);
		return counter.getCount();
	}
	else
	{
		return 0;
	}
}



int FileSystemTreeIterator::getChildNodePosition() const
{
	if (currentPath.isEmpty() == false)
	{
		String parentPath = getParentPath();
		String currentNodeName = getCurrentNodeName();
		
		Finder<String> finder(currentNodeName);
		constFileSystem->enumFileNames(finder, parentPath, enumHiddenFiles, enumSystemFiles);
		if (finder.hasResult() == true)
		{
			return finder.getIndex();
		}
	}

	return -1;
}



bool FileSystemTreeIterator::moveToChildNode(int childPosition)
{
	if (constFileSystem->isDirectory(currentPath) == false)
	{
		return false;
	}

	ValueAtIndexFinder<String> valueAtIndexFinder(childPosition);
	constFileSystem->enumFileNames(valueAtIndexFinder, currentPath, enumHiddenFiles, enumSystemFiles);
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



bool FileSystemTreeIterator::moveToChildNode(const String& childName)
{
	if (constFileSystem->isDirectory(currentPath) == false)
	{
		return false;
	}

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

	if (constFileSystem->exists(newPath) == true)
	{
		currentPath = newPath;
		return true;
	}
	else
	{
		return false;
	}
}



void FileSystemTreeIterator::enumChildNodeNames(const Enumerator<String>& enumerator) const
{
	if (constFileSystem->isDirectory(currentPath) == true)
	{
		constFileSystem->enumFileNames(enumerator, currentPath, enumHiddenFiles, enumSystemFiles);
	}
}



String FileSystemTreeIterator::getCurrentNodeName() const
{
	int length = currentPath.getLength();
	if (currentPath.endsWith('/') == true) --length;
	int slashPos = currentPath.findLast('/', 0, length);
	return currentPath.subString(slashPos+1, length-slashPos-1);
}



String FileSystemTreeIterator::getParentPath() const
{
	BL_ASSERT(currentPath.isEmpty() == false);
	int length = currentPath.getLength();
	if (currentPath.endsWith('/') == true) --length;
	int slashPos = currentPath.findLast('/', 0, length);
	return currentPath.subString(0, slashPos+1);
}



} // namespace Files
} // namespace BaseLib
