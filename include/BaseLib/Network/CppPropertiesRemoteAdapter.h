/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef CppPropertiesRemoteAdapter_h
#define CppPropertiesRemoteAdapter_h


/*
#include "AmazonasCppProperties.h"


class AMAZONAS CppPropertiesRemoteAdapter : public AbstractCppProperties {
public:

	CppPropertiesRemoteAdapter(AbstractCppProperties* newTarget);

    virtual const std::string getProperty(const std::string& propertyName, int index = 0) const;
    virtual int getPropertyInt(const std::string& propertyName, int index = 0) const;
    virtual bool getPropertyBool(const std::string& propertyName, int index = 0) const;
    virtual float getPropertyFloat(const std::string& propertyName, int index = 0) const;

	virtual void setProperty(const std::string& propertyName, const std::string& propertyValue, int index = 0);
    virtual void setPropertyInt(const std::string& propertyName, int propertyValue, int index = 0);
    virtual void setPropertyBool(const std::string& propertyName, bool propertyValue, int index = 0);
    virtual void setPropertyFloat(const std::string& propertyName, float propertyValue, int index = 0);

    virtual int getAggregationMemberCount() const;
	virtual const std::string getAggregationMemberName(int aggregationMemberIndex) const;

    virtual int getPropertyCount() const;
    virtual const std::string getPropertyName(int propertyIndex) const;
    virtual const std::string getPropertyType(const std::string& propertyName) const;

    virtual bool isInvisibleInPropertyExplorer(const std::string& propertyName) const;
    virtual bool isArrayProperty(const std::string& propertyName) const;
    virtual bool isPropertyArraySizeReadOnly(const std::string& propertyName) const;
    virtual int getPropertyArraySize(const std::string& propertyName) const;
    virtual void setPropertyArraySize(const std::string& propertyName, int newArraySize);
	virtual const std::string getPropertyDescription(const std::string& propertyName) const;
    virtual void setPropertyDescription(const std::string& propertyName, const std::string& newDescription) const;

    virtual int getPropertyEnumNameCount(const std::string& propertyName) const;
    virtual const std::string getPropertyEnumName(const std::string& propertyName, int index) const;

protected:

	AbstractCppProperties* target;
};

*/

#endif // #ifndef CppPropertiesRemoteAdapter_h