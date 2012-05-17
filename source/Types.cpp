/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#include "BaseLib/Types.h"
#include <float.h>
#include <limits.h>



namespace BaseLib {



const bool8 BOOL8_MIN = false;
const bool8 BOOL8_MAX = true;
const bool16 BOOL16_MIN = false;
const bool16 BOOL16_MAX = true;
const bool32 BOOL32_MIN = false;
const bool32 BOOL32_MAX = true;
const bool64 BOOL64_MIN = false;
const bool64 BOOL64_MAX = true;

const float32 FLOAT32_MIN = FLT_MIN;
const float32 FLOAT32_MAX = FLT_MAX;
const float64 FLOAT64_MIN = DBL_MIN;
const float64 FLOAT64_MAX = DBL_MAX;

const uint UINT_MIN = 0;
//#const uint UINT_MAX = UINT_MAX;
const pint PINT_MIN = INT_MIN;
const pint PINT_MAX = INT_MAX;
const puint PUINT_MIN = 0;
const puint PUINT_MAX = UINT_MAX;

const byte BYTE_MIN = 0;
const byte BYTE_MAX = 0xff;

const char8 CHAR8_MIN = 0;
const char8 CHAR8_MAX = 127;
//const uchar8 UCHAR8_MIN = '\0';
//const uchar8 UCHAR8_MAX = '\0xff';
const char16 CHAR16_MIN = 0;
const char16 CHAR16_MAX = 0xffff;
const char32 CHAR32_MIN = 0;
const char32 CHAR32_MAX = 0xffffffff;

const int8 INT8_MIN = -128;
const int8 INT8_MAX = 127;
const uint8 UINT8_MIN = 0;
const uint8 UINT8_MAX = 255;

const int16 INT16_MIN = SHRT_MIN;
const int16 INT16_MAX = SHRT_MAX;
const uint16 UINT16_MIN = 0;
const uint16 UINT16_MAX = USHRT_MAX;

const int32 INT32_MIN = INT_MIN;
const int32 INT32_MAX = INT_MAX;
const uint32 UINT32_MIN = 0;
const uint32 UINT32_MAX = UINT_MAX;

const int64 INT64_MIN = _I64_MIN;
const int64 INT64_MAX = _I64_MAX;
const uint64 UINT64_MIN = 0;
const uint64 UINT64_MAX = _UI64_MAX;



} // namespace BaseLib
