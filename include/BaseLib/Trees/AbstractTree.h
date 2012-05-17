/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_AbstractTree_h
#define BaseLib_Trees_AbstractTree_h



#include "BaseLib/Trees/TreeIterator.h"
#include "BaseLib/Containers/StringMap.h"



namespace BaseLib {
namespace Trees {



using BaseLib::Strings::NumberFormat;



class BL_EXPORT AbstractTree {
public:

	virtual ~AbstractTree();

	virtual TreeIterator getTreeIteratorForRootNode() const = 0;

	virtual bool canCreateNodes() const;
	virtual bool canRemoveNodes() const;
	virtual bool canRenameNodes() const;
	virtual bool canMoveNodes() const;
	virtual bool canCopyNodes() const;

	virtual void createNode(const AbstractTreeIterator& parentPath, const String& name, bool leaf = false);
	virtual void removeNode(const AbstractTreeIterator& nodePath);
	virtual void renameNode(const AbstractTreeIterator& nodePath, const String& newName);
	virtual void moveNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath);
	virtual void copyNode(const AbstractTreeIterator& nodePath, const AbstractTreeIterator& newParentPath);

	void createNode(const String& parentPath, const String& name, bool leaf = false);
	void removeNode(const String& nodePath);
	void renameNode(const String& nodePath, const String& newName);
	void moveNode(const String& nodePath, const String& newParentPath);
	void copyNode(const String& nodePath, const String& newParentPath);

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_AbstractTree_h

