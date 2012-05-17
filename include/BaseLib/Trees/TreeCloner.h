/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Xml_TreeCloner_h
#define BaseLib_Xml_TreeCloner_h



#include "BaseLib/Trees/TreeNode.h"
#include "BaseLib/Trees/DataTreeNode.h"



namespace BaseLib {
namespace Trees {



class BL_EXPORT TreeCloner : public TreeNode::AbstractFactory {
public:
	
	TreeCloner(const TreeNode* newSourceRootNode, CreateNodeFunctionPointer createNodeFunctionPointer = &DataTreeNode::create, const String& exceptAttributeWithName = Empty(), const NumberFormat* useNumberFormat = &NumberFormat::getEnglish());
	TreeCloner(const TreeNode* newSourceRootNode, CreateNodeFunctor& newCreateNodeFunctor, const String& exceptAttributeWithName = Empty(), const NumberFormat* useNumberFormat = &NumberFormat::getEnglish());

protected:
	
	const TreeNode* sourceRootNode;
	const String exceptAttribute;

	virtual bool buildTreeImplementation(bool ignoreText);

	bool cloneNode(const TreeNode* sourceNode);
};



} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Xml_TreeCloner_h
