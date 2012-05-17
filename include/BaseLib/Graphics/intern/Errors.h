/******************************************************************************
                                      
Developed and Copyright (c) by       
                                      
Erik Unger          
                                      
Contact: erik@erikunger.com
                                      
******************************************************************************/

#ifndef BaseLib_Graphics_Errors_h
#define BaseLib_Graphics_Errors_h


#include "BaseLib/ErrorHandling.h"
//using namespace BaseLib::ErrorHandling;

#define PIXELBUFFER_NOT_RESIZEABLE ( String("PixelBuffer is not resizeable !") + SYSTEM_ERROR + ERROR_AT )
#define FILE_NOT_FOUND(f) ( String("File: \"") + String(f) + String("\" not found !") + ERROR_AT )
#define LOAD_JPEG_ERROR(f, e) ( String("Error at loading JPEG-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define SAVE_JPEG_ERROR(f, e) ( String("Error at saving JPEG-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define PIXELFORMAT_NOT_JPEG_COMPATBLE(p) ( String("Pixelformat \"") + String(p) + String("\" is not JPEG compatible !") + ERROR_AT )
#define FILE_IS_NOT_A_PNG(f)( String("File: \"") + String(f) + String("\" is not a PNG !") + ERROR_AT )
#define LOAD_PNG_ERROR(f, e) ( String("Error at loading PNG-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define SAVE_PNG_ERROR(f, e) ( String("Error at saving PNG-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define PIXELFORMAT_NOT_PNG_COMPATBLE(p) ( String("Pixelformat \"") + String(p) + String("\" is not PNG compatible !") + ERROR_AT )
#define ILLEGAL_COMPRESSION_LEVEL(l) ( String("Compression level of: ") + String::createFrom(l) + String(" is out of the valid range of 0.0 - 1.0 !") + SYSTEM_ERROR + ERROR_AT) 
#define ILLEGAL_COMPRESSION_QUALITY(l) ( String("Compression quality of: ") + String::createFrom(l) + String(" is out of the valid range of 0.0 - 1.0 !") + SYSTEM_ERROR + ERROR_AT) 
#define PIXELFORMAT_NOT_TGA_COMPATBLE(p) ( String("Pixelformat \"") + String(p) + String("\" is not TGA compatible !") + ERROR_AT )
#define CANT_LOAD_COLORMAP_TGA_FORMAT(f) ( String("Can't load color-map format of TGA file: \"") + String(f) + String("\" !") + ERROR_AT )
#define CANT_OPEN_FILE(f) ( String("Can't open file: \"") + String(f) + String("\" !") + ERROR_AT )
#define LOAD_TGA_ERROR(f, e) ( String("Error at loading TGA-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define SAVE_TGA_ERROR(f, e) ( String("Error at saving TGA-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define UNSUPPORTED_FILE_TYPE(f) ( String("Unsupported file-type: \"") + String(f) + String("\" !") + ERROR_AT )
#define LOAD_PBF_ERROR(f, e) ( String("Error at loading PBF-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define SAVE_PBF_ERROR(f, e) ( String("Error at saving PBF-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define LOAD_BT_ERROR(f, e) ( String("Error at loading BT-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define SAVE_BT_ERROR(f, e) ( String("Error at saving BT-file: \"") + String(f) + String("\" ! ") + String(e) + String(" !") + ERROR_AT )
#define PIXEL_AREA_OUT_OF_RANGE ( String("Pixel-area out of range!") + ERROR_AT )
#define ILLEGAL_FLOATING_POINT_COMPONENT_SIZE(s) ( String("Illegal floating-point component size (only 32 supported): ") + String::createFrom(s) + String(" !") + ERROR_AT)


#endif // #ifndef BaseLib_Graphics_Errors_h
