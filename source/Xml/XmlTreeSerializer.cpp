/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Xml/XmlTreeSerializer.h"
#include "BaseLib/Buffers/BinaryFileBuffer.h"
#include "BaseLib/Streams/BinaryOutputStream.h"
#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/intern/Errors.h"
#include "BaseLib/Files/LocalFile.h"


namespace BaseLib {
namespace Xml {


using namespace BaseLib::ErrorHandling;
using namespace BaseLib::Buffers;
using namespace BaseLib::Streams;
using namespace BaseLib::Files;
using BaseLib::Containers::Enumeration;



inline void indentLine(const OutputStream& outputStream, int indent)
{
	for (int i = 0; i < indent; ++i)
	{
		outputStream << '\t';
	}
}


void XmlTreeSerializer::saveTree(const TreeNode* treeNode, const OutputStream& outputStream, int indent, const NumberFormat* numberFormat)
{
	if (checkArgumentNotNull(NAME_VALUE(treeNode)) == true)
	{
		if (treeNode->hasMetaTag(NON_SERIALIZEABLE) == false)
		{
			indentLine(outputStream, indent);
			String nodeName = treeNode->getName();
			if (nodeName.findFirst("::") != String::END)
			{
				nodeName.searchAndReplace("::", ":");
			}
			outputStream << '<' << nodeName;

			bool hasData = false;
			const Enumeration<String>& attributeNames = treeNode->getAttributeNames();
			foreach (Enumeration<String>::Iterator, i, attributeNames)
			{
				if (treeNode->hasAttributeMetaTag(*i, NON_SERIALIZEABLE) == false && treeNode->isAttributeDefault(*i) == false)
				{
					if (*i == "data")
					{
						hasData = true;
					}
					else
					{
						const String value = treeNode->getAttribute(*i, numberFormat);
						const char8 quote = value.findFirst('\'') == String::END ? '\'' : '"';
						outputStream << ' ' << *i << '=' << quote << value << quote;
					}
				}
			}

			const int childCount = treeNode->getChildCount();
			if (childCount == 0 && hasData == false)
			{
				outputStream << " />" << newLine;
			}
			else
			{
				outputStream << '>' << newLine;
				if (hasData == true)
				{
					outputStream << treeNode->getAttribute("data", numberFormat);
				}
				for (int i = 0; i < childCount; ++i)
				{
					saveTree(treeNode->getChild(i), outputStream, indent+1, numberFormat);
				}
				indentLine(outputStream, indent);
				outputStream << "</" << nodeName << '>' << newLine;
			}
		}
	}
}



void XmlTreeSerializer::saveTreeAsFile(const TreeNode* treeNode, const String& fileName, bool unicode, const NumberFormat* numberFormat)
{
	LocalFile::removeIfExists(fileName);
	BinaryFileBuffer fileBuffer(fileName, false, true);
	BinaryOutputStream outputStream(fileBuffer);
	if (unicode == true)
	{
		outputStream.setStringEncoding(BinaryStreamEncoding::CHAR16);
		outputStream << "<?xml version='1.0' encoding='UTF-16' ?>" << newLine;
	}
	else
	{
		outputStream.setStringEncoding(BinaryStreamEncoding::CHAR8);
		outputStream << "<?xml version='1.0' encoding='UTF-8' ?>" << newLine;
	}
	saveTree(treeNode, outputStream, 0, numberFormat);
	fileBuffer.close();
}



void XmlTreeSerializer::saveTree(const TreeIterator& treeIterator, const OutputStream& outputStream, int indent, const NumberFormat* numberFormat)
{
	TreeIterator iterator = treeIterator;
	if (iterator.hasMetaTag(NON_SERIALIZEABLE) == false)
	{
		if (iterator.isAttribute() == true)
		{
			iterator.moveToParent();
		}

		indentLine(outputStream, indent);
		String nodeName = iterator.getName();
		if (nodeName.findFirst("::") != String::END)
		{
			nodeName.searchAndReplace("::", ":");
		}
		outputStream << '<' << nodeName;

		bool hasData = false;
		const int attributeCount = iterator.getAttributeCount();
		for (int i = 0; i < attributeCount; ++i)
		{
			iterator.moveToAttribute(i);

			if (iterator.hasMetaTag(NON_SERIALIZEABLE) == false && iterator.isDefaultValue() == false)
			{
				if (iterator.getName() == "data")
				{
					hasData = true;
				}
				else
				{
					const String value = iterator.getValue();
					const char8 quote = value.findFirst('\'') == String::END ? '\'' : '"';
					outputStream << ' ' << iterator.getName() << '=' << quote << value << quote;
				}
			}

			iterator.moveToParent();
		}

		const int childCount = iterator.getChildNodeCount();
		if (childCount == 0 && hasData == false)
		{
			outputStream << " />" << newLine;
		}
		else
		{
			outputStream << '>' << newLine;
			if (hasData == true)
			{
				outputStream << iterator.getValueOfAttribute("data");
			}
			for (int i = 0; i < childCount; ++i)
			{
				iterator.moveToChildNode(i);
				saveTree(iterator, outputStream, indent+1, numberFormat);
				iterator.moveToParent();
			}
			indentLine(outputStream, indent);
			outputStream << "</" << nodeName << '>' << newLine;
		}
	}
}



void XmlTreeSerializer::saveTreeAsFile(const TreeIterator& treeIterator, const String& fileName, bool unicode, const NumberFormat* numberFormat)
{
	LocalFile::removeIfExists(fileName);
	BinaryFileBuffer fileBuffer(fileName, false, true);
	BinaryOutputStream outputStream(fileBuffer);
	if (unicode == true)
	{
		outputStream.setStringEncoding(BinaryStreamEncoding::CHAR16);
		outputStream << "<?xml version='1.0' encoding='UTF-16' ?>" << newLine;
	}
	else
	{
		outputStream.setStringEncoding(BinaryStreamEncoding::CHAR8);
		outputStream << "<?xml version='1.0' encoding='UTF-8' ?>" << newLine;
	}
	saveTree(treeIterator, outputStream, 0, numberFormat);
	fileBuffer.close();
}



} // namespace Xml
} // namespace BaseLib
