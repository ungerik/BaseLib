/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_BTFormat_h
#define BaseLib_Graphics_BTFormat_h



#include "BaseLib/Types.h"



namespace BaseLib {
namespace Graphics {



#pragma pack(1)



struct BTHeader {
	static const char8 ID[];

	char8 id[10]; // "binterr1.3" A marker which indicates that this is a BT 1.3 file
	uint32 columns; // Width (east-west) dimension of the height grid
	uint32 rows; // Height (north-south) dimension of the height grid
	uint16 dataSize; // Bytes per elevation grid point, either 2 or 4
	bool16 floatingPoint; // If 1, the data consists of floating point values (float), otherwise they are integers
	uint16 horizontalUnits; // 0: Degrees, 1: Meters, 2: Feet (international foot = .3048 meters), 3: Feet (U.S. survey foot = 1200/3937 meters)
	int16 utmZone; // Indicates the UTM zone (1-60) if the file is in UTM.  Negative zone numbers are used for the southern hemisphere
	int16 datum; // Indicates the Datum, see Datum Values below
	double leftExtent; // The extents are specified in the coordinate space specified by the UTM flag/zone fields.  If UTM is false, they are ordinary geographic (latitude-longitude) values.
	double rightExtent;
	double bottomExtent;
	double topExtent;
	bool16 externalProjection; // 0: Projection is fully described by this header, 1: Projection is specified in a external .prj file
	float scale; // Vertical units in meters, usually 1.0.  The value 0.0 should be interpreted as 1.0 to allow for backward compatibility
	int8 unused[190]; // Bytes of value 0 are used to pad the rest of the header

	/*
		The Datum field should be one of the following values,
		which are the same as those used by the USGS Projection Library.
		-2 NO_DATUM 11 HU_TZU_SHAN
		-1 UNKNOWN_DATUM 12 INDIAN
		0 ADINDAN 13 NAD27
		1 ARC1950 14 NAD83
		2 ARC1960 15 OLD_HAWAIIAN_MEAN
		3 AUSTRALIAN_GEODETIC_1966 16 OMAN
		4 AUSTRALIAN_GEODETIC_1984 17 ORDNANCE_SURVEY_1936
		5 CAMP_AREA_ASTRO 18 PUERTO_RICO
		6 CAPE 19 PULKOVO_1942
		7 EUROPEAN_DATUM_1950 20 PROVISIONAL_S_AMERICAN_1956
		8 EUROPEAN_DATUM_1979 21 TOKYO
		9 GEODETIC_DATUM_1949 22 WGS_72
		10 HONG_KONG_1963 23 WGS_84
	*/
};



#pragma pack()



} // namespace Graphics
} // namespace BaseLib



#endif // #ifndef BaseLib_Graphics_BTFormat_h
