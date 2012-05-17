/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_DefaultTreeNode_h
#define BaseLib_Trees_DefaultTreeNode_h



#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/Containers/Array.h"



namespace BaseLib {
namespace Trees {



using BaseLib::Containers::Array;



class BL_EXPORT DefaultTreeNode : public TreeNode {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::DefaultTreeNode, TreeNode);

	virtual int getChildCountIncludingHiddenChildren() const;
	virtual TreeNode* getChild(int index);
	virtual void addChild(TreeNode* newChild);
	virtual void insertChild(TreeNode* newChild, int index);
	virtual TreeNode* removeChild(int index);
	virtual TreeNode* replaceChild(int index, TreeNode* newChild);
	virtual bool isSubTreeHidden() const;

protected:

	typedef Array<TreeNode*> Children;
	Children children;
	bool hideSubTree;

	DefaultTreeNode(bool subTreeIsHidden);
};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_DefaultTreeNode_h

