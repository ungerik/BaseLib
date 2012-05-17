/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_DefaultTree_h
#define BaseLib_Trees_DefaultTree_h



#include "BaseLib/Trees/AbstractTree.h"



namespace BaseLib {
namespace Trees {



class BL_EXPORT DefaultTree : public AbstractTree {
public:

	explicit DefaultTree(const TreeIterator& rootTreeIterator); // copy by value
	explicit DefaultTree(AbstractTreeIterator* rootAbstractTreeIterator); // takes ownership

	virtual TreeIterator getTreeIteratorForRootNode() const;

protected:

	TreeIterator treeIteratorForRootNode;
};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_DefaultTree_h

