/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_DefaultTreeLeaf_h
#define BaseLib_Trees_DefaultTreeLeaf_h



#include "BaseLib/Trees/TreeNode.h"



namespace BaseLib {
namespace Trees {



class BL_EXPORT DefaultTreeLeaf : public TreeNode {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::DefaultTreeLeaf, TreeNode);

	virtual bool isLeafType() const;

	virtual int getChildCountIncludingHiddenChildren() const;
	virtual TreeNode* getChild(int index);
	virtual void addChild(TreeNode* newChild);
	virtual void insertChild(TreeNode* newChild, int index);
	virtual TreeNode* removeChild(int index);
	virtual TreeNode* replaceChild(int index, TreeNode* newChild);

};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_DefaultTreeLeaf_h

