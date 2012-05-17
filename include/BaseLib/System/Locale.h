/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_System_Locale_h
#define BaseLib_System_Locale_h



#include "BaseLib/Defines.h"
#ifndef BL_NO_ICU



#include "BaseLib/Reflection/Object.h"
#include "BaseLib/Functors/Enumerator.h"
#include "BaseLib/Strings/String.h"



namespace BaseLib {
namespace System {



using BaseLib::Strings::String;
using BaseLib::Functors::Enumerator;



class BL_EXPORT Locale : public BaseLib::Reflection::Object {
public:

	static const String CHINESE;
	static const String ENGLISH;
	static const String FRENCH;
	static const String GERMAN;
	static const String ITALIAN;
	static const String JAPANESE;
	static const String KOREAN;
	static const String SIMPLIFIED_CHINESE;
	static const String TRADITIONAL_CHINESE;
	static const String CANADA;
	static const String CANADA_FRENCH;
	static const String CHINA;
	static const String PRC;
	static const String FRANCE;
	static const String GERMANY;
	static const String ITALY;
	static const String JAPAN;
	static const String KOREA;
	static const String TAIWAN;
	static const String UK;
	static const String US;

	static String getDefault();
	static void setDefault(const String& id);

	static void enumAvailableLocales(const Enumerator<String>& enumerator);
	static void enumIsoLanguages(const Enumerator<String>& enumerator);
	static void enumIsoCountries(const Enumerator<String>& enumerator);
	static void enumCountryTimeZones(const String& iso3166TwoLetterCountryCode, const Enumerator<String>& enumerator);

	BL_DECLARE_REFLECTION_BASELIB_BASE_CLASS(BaseLib::System::Locale);

	Locale(const String& locale = getDefault());

	operator String() const;
	Locale& operator =(const String& right);

	bool operator ==(const Locale& right) const;
	inline bool operator !=(const Locale& right) const
	{
		return !operator ==(right);
	}

	String getId() const;
	void setId(const String& newId);

	String getLanguage() const;
	String getScript() const;
	String getCountry() const;
	String getVariant() const;
	String getName() const;
	String getIso3Language() const;
	String getIso3Country() const; 
	String getDisplayLanguage(const String& displayLocale = Empty()) const;
	String getDisplayScript(const String& displayLocale = Empty()) const;
	String getDisplayCountry(const String& displayLocale = Empty()) const;
	String getDisplayVariant(const String& displayLocale = Empty()) const;
	String getDisplayName(const String& displayLocale = Empty()) const;
	String getParent() const;
	String getBaseName() const;

	void enumCountryTimeZones(const Enumerator<String>& enumerator);

private:

	String localeId;

};



} // namespace System
} // namespace BaseLib



#endif // #ifndef BL_NO_ICU
#endif // #ifndef BaseLib_System_Locale_h


