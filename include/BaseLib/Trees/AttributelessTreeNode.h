/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Trees_AttributelessTreeNode_h
#define BaseLib_Trees_AttributelessTreeNode_h



#include "BaseLib/Trees/DefaultTreeNode.h"
#include "BaseLib/Containers/StringMap.h"
#include <set>



namespace BaseLib {
namespace Trees {



using BaseLib::Containers::StringMap;



class BL_EXPORT AttributelessTreeNode : public DefaultTreeNode {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Trees::AttributelessTreeNode, DefaultTreeNode);

	AttributelessTreeNode(const String& nodeName, bool subTreeIsHidden = false);

	virtual String getName() const;

	virtual const Enumeration<String>& getAttributeNames() const;
	virtual bool isAttributeReadable(const String& attributeName) const;
	virtual bool isAttributeWriteable(const String& attributeName) const;
	virtual bool getAttributeIfAvailable(const String& attributeName, String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault()) const;
	virtual void setAttribute(const String& attributeName, const String& attributeValue, const NumberFormat* numberFormat = NumberFormat::getDefault());
	virtual bool hasAttribute(const String& attributeName) const;
	virtual bool hasMetaTag(const String& metaTag) const;
	virtual bool hasAttributeMetaTag(const String& attributeName, const String& metaTag) const;
	void addMetaTag(const String& metaTag);
	void removeMetaTag(const String& metaTag);
	void addAttributeMetaTag(const String& attributeName, const String& metaTag);
	void removeAttributeMetaTag(const String& attributeName, const String& metaTag);
	virtual String getAttributeType(const String& attributeName) const;
	virtual bool isAttributeDefault(const String& attributeName) const;
	virtual void setAttributeToDefault(const String& attributeName);
	virtual const Enumeration<String>& getAttributeValueRange(const String& attributeName) const;

protected:

	String name;
};




} // namespace Trees
} // namespace BaseLib



#endif // #ifndef BaseLib_Trees_AttributelessTreeNode_h

