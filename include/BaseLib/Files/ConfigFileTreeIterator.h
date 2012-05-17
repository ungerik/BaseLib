/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_ConfigFileTreeIterator_h
#define BaseLib_ConfigFileTreeIterator_h



#include "BaseLib/Files/ConfigFile.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Streams/OutputStream.h"
#include "BaseLib/Containers/StringMap.h"
#include "BaseLib/Containers/Stack.h"
#include "BaseLib/Trees/AbstractTreeIterator.h"
#include "BaseLib/Strings/NumberFormat.h"



namespace BaseLib {
namespace Files {



using BaseLib::Strings::String;
using BaseLib::Strings::NumberFormat;
using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
using BaseLib::Containers::StringMap;
using BaseLib::Containers::Enumeration;
using BaseLib::Containers::Stack;



class BL_EXPORT ConfigFileTreeIterator : public BaseLib::Trees::AbstractTreeIterator {
public:

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Files::ConfigFileTreeIterator, BaseLib::Trees::AbstractTreeIterator);

	ConfigFileTreeIterator(ConfigFile* forConfigFile, const NumberFormat* useNumberFormat = NumberFormat::getDefault());
	ConfigFileTreeIterator(const ConfigFile* forConstConfigFile, const NumberFormat* useNumberFormat = NumberFormat::getDefault());

	inline bool isConfigFileConst() const
	{
		return configFile == NULL;
	}

	inline void makeConfigFileConst()
	{
		configFile = NULL;
	}

	virtual AbstractTreeIterator* clone() const;
	virtual bool operator ==(const AbstractTreeIterator& right) const;
	virtual bool isAttribute() const;
	virtual String getName() const;
	virtual String getNamespace() const;
	virtual bool hasMetaTag(const String& metaTag) const;
	virtual bool isReadable() const;
	virtual bool isWriteable() const;
	virtual InputStream* createInputStream() const;
	virtual OutputStream* createOutputStream() const;
	virtual String getValue() const;
	virtual void setValue(const String& newValue) const;
	virtual String getValueOfAttribute(const String& attributeName) const;
	virtual void setValueOfAttribute(const String& attributeName, const String& newValue) const;
	virtual String getType() const;
	virtual bool isDefaultValue() const;
	virtual void setDefaultValue() const;
	virtual const Enumeration<String>& getValueRange() const;
	virtual void push();
	virtual void pop(bool restorePosition = true, bool restoreStack = true);
	virtual int getAttributeCount() const; // uses parent-node if current is attribute
	virtual int getAttributePosition() const;
	virtual bool moveToAttribute(int attributePosition);
	virtual bool moveToAttribute(const String& attributeName);
	virtual bool hasParent() const;
	virtual bool moveToParent();
	virtual int getChildNodeCount() const; // uses parent-node if current is attribute
	virtual int getChildNodePosition() const; // uses parent-node if current is attribute
	virtual bool moveToChildNode(int childPosition); // uses parent-node if current is attribute

private:

	const ConfigFile* constConfigFile;
	ConfigFile* configFile;
	const NumberFormat* numberFormat;
	String currentKey;
	Stack<String> stateStack;
};



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_ConfigFileTreeIterator_h
