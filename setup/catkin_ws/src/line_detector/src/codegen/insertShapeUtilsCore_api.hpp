/* Copyright 2019-2020 The MathWorks, Inc. */

#ifndef _INSERTSHAPEUTILSCORE_API_HPP
#define _INSERTSHAPEUTILSCORE_API_HPP

#include "vision_defines.h"

/* Declarations of Insert Shape APIs */

EXTERN_C LIBMWCVSTRT_API
        void constructDrawBaseObjectShape(void **ptr2dbObjPtr);

EXTERN_C LIBMWCVSTRT_API
        void getPositionDataPointer(void **ptr2positionPtr, void* pts, uint32_T dim1, uint32_T dim2 );

EXTERN_C LIBMWCVSTRT_API
        void deletePositionDataPointer(void* positionPtr);

EXTERN_C LIBMWCVSTRT_API
        void getColorDataPointer_single(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 );

EXTERN_C LIBMWCVSTRT_API
        void deleteColorDataPointer_single(void* colorPtr);

EXTERN_C LIBMWCVSTRT_API
        void getColorDataPointer_double(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 );

EXTERN_C LIBMWCVSTRT_API
        void deleteColorDataPointer_double(void* colorPtr);
EXTERN_C LIBMWCVSTRT_API
        void getColorDataPointer_uint8(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 );

EXTERN_C LIBMWCVSTRT_API
        void deleteColorDataPointer_uint8(void* colorPtr);
EXTERN_C LIBMWCVSTRT_API
        void getColorDataPointer_uint16(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 );

EXTERN_C LIBMWCVSTRT_API
        void deleteColorDataPointer_uint16(void* colorPtr);
EXTERN_C LIBMWCVSTRT_API
        void getColorDataPointer_int16(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 );

EXTERN_C LIBMWCVSTRT_API
        void deleteColorDataPointer_int16(void* colorPtr);


EXTERN_C LIBMWCVSTRT_API
        boolean_T initialiseDrawbaseShape(void *ptrObj, const int i, int32_T shape);

EXTERN_C LIBMWCVSTRT_API
        void instantiateDrawBaseShape_single(void *ptrObj, void *rgbOut, void *rgbIn, void *pts,
        void *fillColor, double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias,
        int_T numRow, int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2,
        int_T numFillColor, boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter);

EXTERN_C LIBMWCVSTRT_API
        void instantiateDrawBaseShape_double(void *ptrObj, void *rgbOut, void *rgbIn, void *pts,
        void *fillColor, double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias,
        int_T numRow, int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2,
        int_T numFillColor, boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter);

EXTERN_C LIBMWCVSTRT_API
        void instantiateDrawBaseShape_uint8(void *ptrObj, void *rgbOut, void *rgbIn, void *pts,
        void *fillColor, double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias,
        int_T numRow, int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2,
        int_T numFillColor, boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter);

EXTERN_C LIBMWCVSTRT_API
        void instantiateDrawBaseShape_uint16(void *ptrObj, void *rgbOut, void *rgbIn, void *pts,
        void *fillColor, double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias,
        int_T numRow, int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2,
        int_T numFillColor, boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter);

EXTERN_C LIBMWCVSTRT_API
        void instantiateDrawBaseShape_int16(void *ptrObj, void *rgbOut, void *rgbIn, void *pts,
        void *fillColor, double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias,
        int_T numRow, int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2,
        int_T numFillColor, boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter);

EXTERN_C LIBMWCVSTRT_API
        void mDrawShapes(void *ptrObj, boolean_T isFillShape, boolean_T isAntiAlias, int32_T shape,
        int32_T lineWidth, int_T numRow, int_T numCol);

EXTERN_C LIBMWCVSTRT_API
        void deallocateMemoryShape(void *ptrObj);

#endif