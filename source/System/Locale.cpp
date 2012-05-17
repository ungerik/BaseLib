/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/System/Locale.h"
#ifndef BL_NO_ICU



#include "BaseLib/ErrorHandling.h"
#include <unicode/uloc.h>
#include <unicode/ucal.h>



BaseLib::Strings::String getIcuError(UErrorCode errorCode);



namespace BaseLib {
namespace System {



using namespace BaseLib::ErrorHandling;



String Locale::getDefault()
{
	return String(uloc_getDefault());
}



void Locale::setDefault(const String& locale)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	uloc_setDefault(locale.getChar8CString(), &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



void Locale::enumAvailableLocales(const Enumerator<String>& enumerator)
{
	const int count = uloc_countAvailable();
	for (int i = 0; i < count; ++i)
	{
		enumerator.enumerate(uloc_getAvailable(i));
	}
}



void Locale::enumIsoLanguages(const Enumerator<String>& enumerator)
{
	const char* const* languages = uloc_getISOLanguages();
	const char* language = languages[0];
	for (int i = 0; language != NULL; ++i, language = languages[i])
	{
		enumerator.enumerate(language);
	}
}



void Locale::enumIsoCountries(const Enumerator<String>& enumerator)
{
	const char* const* languages = uloc_getISOCountries();
	const char* language = languages[0];
	for (int i = 0; language != NULL; ++i, language = languages[i])
	{
		enumerator.enumerate(language);
	}
}

	
	
void Locale::enumCountryTimeZones(const String& iso3166TwoLetterCountryCode, const Enumerator<String>& enumerator)
{
	UErrorCode errorCode = U_ZERO_ERROR;
	UEnumeration* enumeration = ucal_openCountryTimeZones(iso3166TwoLetterCountryCode.getChar8CString(), &errorCode);
	if (enumeration != NULL)
	{
		for (const char16 * s = uenum_unext(enumeration, NULL, &errorCode); s != NULL; s = uenum_unext(enumeration, NULL, &errorCode))
		{
			enumerator.enumerate(s);
		}
		uenum_close(enumeration);
	}
	else
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
}



BL_DEFINE_REFLECTION_BASE_CLASS(Locale)
{
	registerProperty("id", &Locale::getId, &Locale::setId);
	registerProperty("language", &Locale::getLanguage);
	registerProperty("script", &Locale::getScript);
	registerProperty("country", &Locale::getCountry);
	registerProperty("variant", &Locale::getVariant);
	registerProperty("name", &Locale::getName);
	registerProperty("iso3Language", &Locale::getIso3Language);
	registerProperty("iso3Country", &Locale::getIso3Country); 
	registerProperty("parent", &Locale::getParent);
	registerProperty("baseName", &Locale::getBaseName);
}



Locale::Locale(const String& id)
	: BaseLib::Reflection::Object()
	, localeId(id.isEmpty() == false ? id : getDefault())
{
}



Locale::operator String() const
{
	return localeId;
}



Locale& Locale::operator =(const String& right)
{
	setId(right.isEmpty() == false ? right : getDefault());
	return *this;
}



String Locale::getId() const
{
	return localeId;
}



void Locale::setId(const String& newId)
{
	localeId = newId;
}



bool Locale::operator ==(const Locale& right) const
{
	UErrorCode errorCode = U_ZERO_ERROR;

	char leftBuffer[256];
	const int leftLength = uloc_canonicalize(localeId.getChar8CString(), leftBuffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
		return false;
	}

	char rightBuffer[256];
	const int rightLength = uloc_canonicalize(right.operator String().getChar8CString(), rightBuffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
		return false;
	}

	if (leftLength == rightLength)
	{
		for (int i = 0; i < leftLength; ++i)
		{
			if (leftBuffer[i] != rightBuffer[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}



String Locale::getLanguage() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getLanguage(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getScript() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getScript(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getCountry() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getCountry(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getVariant() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getVariant(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getName() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getName(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getIso3Language() const
{	
	return String(uloc_getISO3Language(localeId.getChar8CString()));
}



String Locale::getIso3Country() const
{	
	return String(uloc_getISO3Country(localeId.getChar8CString()));
}



String Locale::getDisplayLanguage(const String& displayLocale) const
{	
	const char* usedDisplayLocale = displayLocale.isEmpty() == false ? displayLocale.getChar8CString() : localeId.getChar8CString();
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = uloc_getDisplayLanguage(localeId.getChar8CString(), usedDisplayLocale, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getDisplayScript(const String& displayLocale) const
{	
	const char* usedDisplayLocale = displayLocale.isEmpty() == false ? displayLocale.getChar8CString() : localeId.getChar8CString();
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = uloc_getDisplayScript(localeId.getChar8CString(), usedDisplayLocale, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getDisplayCountry(const String& displayLocale) const
{	
	const char* usedDisplayLocale = displayLocale.isEmpty() == false ? displayLocale.getChar8CString() : localeId.getChar8CString();
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = uloc_getDisplayCountry(localeId.getChar8CString(), usedDisplayLocale, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getDisplayVariant(const String& displayLocale) const
{	
	const char* usedDisplayLocale = displayLocale.isEmpty() == false ? displayLocale.getChar8CString() : localeId.getChar8CString();
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = uloc_getDisplayVariant(localeId.getChar8CString(), usedDisplayLocale, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getDisplayName(const String& displayLocale) const
{	
	const char* usedDisplayLocale = displayLocale.isEmpty() == false ? displayLocale.getChar8CString() : localeId.getChar8CString();
	UErrorCode errorCode = U_ZERO_ERROR;
	char16 buffer[256];
	const int resultLength = uloc_getDisplayName(localeId.getChar8CString(), usedDisplayLocale, buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getParent() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getParent(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



String Locale::getBaseName() const
{	
	UErrorCode errorCode = U_ZERO_ERROR;
	char buffer[256];
	const int resultLength = uloc_getBaseName(localeId.getChar8CString(), buffer, 256, &errorCode);
	if (U_FAILURE(errorCode))
	{
		resultError(getIcuError(errorCode) + ERROR_AT);
	}
	return String(buffer, resultLength);
}



void Locale::enumCountryTimeZones(const Enumerator<String>& enumerator)
{
	enumCountryTimeZones(getIso3Country(), enumerator);
}



} // namespace System
} // namespace BaseLib



#endif // #ifndef BL_NO_ICU
