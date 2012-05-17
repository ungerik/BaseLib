/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Files_FileSystemTreeIterator_h
#define BaseLib_Files_FileSystemTreeIterator_h



#include "BaseLib/Files/AbstractFileSystem.h"
#include "BaseLib/Streams/InputStream.h"
#include "BaseLib/Trees/AbstractTreeIterator.h"
#include "BaseLib/Containers/Stack.h"
#include "BaseLib/Strings/NumberFormat.h"



namespace BaseLib {
namespace Files {



using BaseLib::Strings::String;
using BaseLib::Strings::NumberFormat;
using BaseLib::Streams::InputStream;
using BaseLib::Streams::OutputStream;
using BaseLib::Containers::Enumeration;
using BaseLib::Containers::Stack;



/**
*/
class BL_EXPORT FileSystemTreeIterator : public BaseLib::Trees::AbstractTreeIterator {
public:

	static const String FILE_TYPE;
	static const String DIRECTORY_TYPE;

	BL_DECLARE_REFLECTION_BASELIB_CLASS(BaseLib::Files::FileSystemTreeIterator, BaseLib::Trees::AbstractTreeIterator);

	FileSystemTreeIterator(AbstractFileSystem* forFileSystem, bool enumHiddenFiles = false, bool enumSystemFiles = false, const NumberFormat* useNumberFormat = NumberFormat::getDefault());
	FileSystemTreeIterator(const AbstractFileSystem* forConstFileSystem, bool enumHiddenFiles = false, bool enumSystemFiles = false, const NumberFormat* useNumberFormat = NumberFormat::getDefault());

	inline bool isFileSystemConst() const
	{
		return fileSystem == NULL;
	}

	inline void makeFileSystemConst()
	{
		fileSystem = NULL;
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
	virtual bool canHaveChildNodes() const;
	virtual bool hasChildNodes() const;
	virtual bool hasChildNode(const String& childName) const; // uses parent-node if current is attribute
	virtual int getChildNodeCount() const;
	virtual int getChildNodePosition() const;
	virtual bool moveToChildNode(int childPosition);
	virtual bool moveToChildNode(const String& childName);
	virtual void enumChildNodeNames(const Enumerator<String>& enumerator) const;

private:

	enum Attributes {
		DIRECTORY_ATTRIBUTE_POSITION,
		SIZE_ATTRIBUTE_POSITION
	};

	const AbstractFileSystem* constFileSystem;
	AbstractFileSystem* fileSystem;
	const NumberFormat* numberFormat;
	String currentPath; // starts without '/'
	String currentAttribute;
	bool enumHiddenFiles;
	bool enumSystemFiles;

	struct State {
		String path;
		String attribute;
		State(const String& newPath = Empty(), const String& newAttribute = Empty())
			: path(newPath)
			, attribute(newAttribute)
		{
		}
	};

	Stack<State> stateStack;

	String getCurrentNodeName() const;
	String getParentPath() const;
};



} // namespace Files
} // namespace BaseLib



#endif // #ifndef BaseLib_Files_FileSystemTreeIterator_h
