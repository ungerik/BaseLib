/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Trees/TreeIteratorFactory.h"
#include "BaseLib/intern/Errors.h"

#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/Reflection/PropertiesTreeIterator.h"
#include "BaseLib/Files/FileSystemTreeIterator.h"
#include "BaseLib/Files/ConfigFileTreeIterator.h"



namespace BaseLib {
namespace Trees {



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(TreeNode* forTreeNode, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Trees::TreeNode::Iterator(forTreeNode, String(), useNumberFormat);
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(const TreeNode* forTreeNode, const NumberFormat* useNumberFormat)
{
	BL_ASSERT_NEVER_REACHED
	return NULL; ///
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(BaseLib::Reflection::Object* forObject, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Reflection::PropertiesTreeIterator(forObject, useNumberFormat);
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(const BaseLib::Reflection::Object* forObject, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Reflection::PropertiesTreeIterator(forObject, useNumberFormat);
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(BaseLib::Files::AbstractFileSystem* forFileSystem, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Files::FileSystemTreeIterator(forFileSystem, false, false, useNumberFormat);
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(const BaseLib::Files::AbstractFileSystem* forFileSystem, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Files::FileSystemTreeIterator(forFileSystem, false, false, useNumberFormat);
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(BaseLib::Files::ConfigFile* forConfigFile, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Files::ConfigFileTreeIterator(forConfigFile, useNumberFormat);
}



AbstractTreeIterator* TreeIteratorFactory::createAbstractTreeIterator(const BaseLib::Files::ConfigFile* forConfigFile, const NumberFormat* useNumberFormat)
{
	return new BaseLib::Files::ConfigFileTreeIterator(forConfigFile, useNumberFormat);
}





} // namespace Trees
} // namespace BaseLib
