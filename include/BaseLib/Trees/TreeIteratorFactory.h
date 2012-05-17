/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_TreeIteratorFactory_h
#define BaseLib_Trees_TreeIteratorFactory_h



#include "BaseLib/Trees/TreeIterator.h"



namespace BaseLib {

	namespace Reflection {
		class Object;
	}

	namespace Files {
		class AbstractFileSystem;
		class ConfigFile;
	}
}



namespace BaseLib {
namespace Trees {



class TreeNode;
using BaseLib::Strings::NumberFormat;



class BL_EXPORT TreeIteratorFactory : public StaticClass {
public:


	// Common:

	template<class T>
	static inline TreeIterator createTreeIterator(T& forTarget, const NumberFormat* useNumberFormat)
	{
		return TreeIterator(createAbstractTreeIterator(forTarget, useNumberFormat));
	}

	template<class T>
	static inline TreeIterator createTreeIterator(const T& forTarget, const NumberFormat* useNumberFormat)
	{
		return TreeIterator(createAbstractTreeIterator(forTarget, useNumberFormat));
	}

	template<class T>
	static inline TreeIterator createTreeIterator(T* forTarget, const NumberFormat* useNumberFormat)
	{
		return TreeIterator(createAbstractTreeIterator(forTarget, useNumberFormat));
	}

	template<class T>
	static inline TreeIterator createTreeIterator(const T* forTarget, const NumberFormat* useNumberFormat)
	{
		return TreeIterator(createAbstractTreeIterator(forTarget, useNumberFormat));
	}



	// BaseLib::Trees::TreeNode:

	static inline AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Trees::TreeNode& forTreeNode, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forTreeNode, useNumberFormat);
	}

	static inline AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Trees::TreeNode& forTreeNode, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forTreeNode, useNumberFormat);
	}

	static AbstractTreeIterator* createAbstractTreeIterator(TreeNode* forTreeNode, const NumberFormat* useNumberFormat);
	static AbstractTreeIterator* createAbstractTreeIterator(const TreeNode* forTreeNode, const NumberFormat* useNumberFormat);



	// BaseLib::Reflection::Object:

	static inline AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Reflection::Object& forObject, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forObject, useNumberFormat);
	}

	static inline AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Reflection::Object& forObject, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forObject, useNumberFormat);
	}

	static AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Reflection::Object* forObject, const NumberFormat* useNumberFormat);
	static AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Reflection::Object* forObject, const NumberFormat* useNumberFormat);



	// BaseLib::Files::FileSystem:
	
	static inline AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Files::AbstractFileSystem& forFileSystem, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forFileSystem, useNumberFormat);
	}

	static inline AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Files::AbstractFileSystem& forFileSystem, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forFileSystem, useNumberFormat);
	}

	static AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Files::AbstractFileSystem* forFileSystem, const NumberFormat* useNumberFormat);
	static AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Files::AbstractFileSystem* forFileSystem, const NumberFormat* useNumberFormat);


	
	// BaseLib::Files::ConfigFile:

	static inline AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Files::ConfigFile& forConfigFile, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forConfigFile, useNumberFormat);
	}

	static inline AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Files::ConfigFile& forConfigFile, const NumberFormat* useNumberFormat)
	{
		return createAbstractTreeIterator(&forConfigFile, useNumberFormat);
	}

	static AbstractTreeIterator* createAbstractTreeIterator(BaseLib::Files::ConfigFile* forConfigFile, const NumberFormat* useNumberFormat);
	static AbstractTreeIterator* createAbstractTreeIterator(const BaseLib::Files::ConfigFile* forConfigFile, const NumberFormat* useNumberFormat);

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_TreeIteratorFactory_h


