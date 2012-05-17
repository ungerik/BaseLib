/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_XmlTreeSerializer_h
#define BaseLib_Xml_XmlTreeSerializer_h



#include "BaseLib/Trees/TreeNode.h"
//#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/Streams/OutputStream.h"



namespace BaseLib {
	namespace Trees {
		class TreeIterator;
	}
}



namespace BaseLib {
namespace Xml {



using BaseLib::Trees::TreeNode;
using BaseLib::Trees::TreeIterator;
using BaseLib::Strings::String;
using BaseLib::Strings::NumberFormat;
using BaseLib::Streams::OutputStream;



class BL_EXPORT XmlTreeSerializer : public StaticClass {
public:
	
	static const String NON_SERIALIZEABLE;

	static void saveTree(const TreeNode* treeNode, const OutputStream& outputStream, int indent = 0, const NumberFormat* numberFormat = &NumberFormat::getEnglish());
	static void saveTreeAsFile(const TreeNode* treeNode, const String& fileName, bool unicode = false, const NumberFormat* numberFormat = &NumberFormat::getEnglish());

	static void saveTree(const TreeIterator& treeIterator, const OutputStream& outputStream, int indent = 0, const NumberFormat* numberFormat = &NumberFormat::getEnglish());
	static void saveTreeAsFile(const TreeIterator& treeIterator, const String& fileName, bool unicode = false, const NumberFormat* numberFormat = &NumberFormat::getEnglish());

};



} // namespace Xml
} // namespace BaseLib



#endif // #ifndef BaseLib_Xml_XmlTreeSerializer_h
