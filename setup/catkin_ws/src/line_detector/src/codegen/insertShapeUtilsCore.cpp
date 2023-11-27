// //////////////////////////////////////////////////////////////////////////////
// //
// // APIs for interfaces for insertShapeUtils that are used for codegeneration
// // Copyright 2019-2020 The MathWorks, Inc.
// //
// //////////////////////////////////////////////////////////////////////////////

#ifndef COMPILE_FOR_VISION_BUILTINS

#include "insertShapeUtilsCore_api.hpp"
#include "insertShapeAndMarkerUtils.hpp"

void constructDrawBaseObjectShape(void **ptr2dbObjPtr)
{
    DrawBase **drawBaseP2P;
    drawBaseP2P = new DrawBase *[2];
    *ptr2dbObjPtr = drawBaseP2P;
}
void getPositionDataPointer(void **ptr2positionPtr, void* pts, uint32_T dim1, uint32_T dim2 )
{
    uint32_T numPTs = dim1*dim2;
    int32_T* posPtr = new int32_T[numPTs];
    if (posPtr != NULL) {
        memcpy(posPtr, pts, numPTs * sizeof(int32_T));
    }
    *ptr2positionPtr = posPtr;
}
void deletePositionDataPointer(void* positionPtr) {
    if (positionPtr != NULL) {
        delete[](static_cast<int32_T*>(positionPtr));
        positionPtr = NULL;
    }
}

void getColorDataPointer_single(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 )
{
    uint32_T numPTs = dim1*dim2;
    real32_T* posPtr = new real32_T[numPTs];
    if (posPtr != NULL) {
        memcpy(posPtr, pts, numPTs * sizeof(real32_T));
    }
    *ptr2colorPtr = posPtr;
}

void getColorDataPointer_double(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 )
{
    uint32_T numPTs = dim1*dim2;
    real_T* posPtr = new real_T[numPTs];
    if (posPtr != NULL) {
        memcpy(posPtr, pts, numPTs * sizeof(real_T));
    }
    *ptr2colorPtr = posPtr;
}

void getColorDataPointer_uint8(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 )
{
    uint32_T numPTs = dim1*dim2;
    uint8_T* posPtr = new uint8_T[numPTs];
    if (posPtr != NULL) {
        memcpy(posPtr, pts, numPTs * sizeof(uint8_T));
    }
    *ptr2colorPtr = posPtr;
}

void getColorDataPointer_uint16(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 )
{
    uint32_T numPTs = dim1*dim2;
    uint16_T* posPtr = new uint16_T[numPTs];
    if (posPtr != NULL) {
        memcpy(posPtr, pts, numPTs * sizeof(uint16_T));
    }
    *ptr2colorPtr = posPtr;
}

void getColorDataPointer_int16(void **ptr2colorPtr, void* pts, uint32_T dim1, uint32_T dim2 )
{
    uint32_T numPTs = dim1*dim2;
    int16_T* posPtr = new int16_T[numPTs];
    if (posPtr != NULL) {
        memcpy(posPtr, pts, numPTs * sizeof(int16_T));
    }
    *ptr2colorPtr = posPtr;
}


void deleteColorDataPointer_single(void* colorPtr) {
    if (colorPtr != NULL) {
        delete[](static_cast<real32_T*>(colorPtr));
        colorPtr = NULL;
    }
}

void deleteColorDataPointer_double(void* colorPtr) {
    if (colorPtr != NULL) {
        delete[](static_cast<real_T*>(colorPtr));
        colorPtr = NULL;
    }
}

void deleteColorDataPointer_uint8(void* colorPtr) {
    if (colorPtr != NULL) {
        delete[](static_cast<uint8_T*>(colorPtr));
        colorPtr = NULL;
    }
}

void deleteColorDataPointer_uint16(void* colorPtr) {
    if (colorPtr != NULL) {
        delete[](static_cast<uint16_T*>(colorPtr));
        colorPtr = NULL;
    }
}

void deleteColorDataPointer_int16(void* colorPtr) {
    if (colorPtr != NULL) {
        delete[](static_cast<int16_T*>(colorPtr));
        colorPtr = NULL;
    }
}



boolean_T initialiseDrawbaseShape(void *ptrObj, const int i, int32_T shape)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    boolean_T isInitialise = false;
    if (((shape == SHAPE_RECTANGLE) || (shape == SHAPE_CIRCLE))
    && i != 0) {
        drawBaseP2P[i] = NULL;         
        isInitialise = true;
    }
    return isInitialise;
}

void instantiateDrawBaseShape_single(void *ptrObj, void *rgbOut, void *rgbIn, void *pts, void *fillColor,
        double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias, int_T numRow,
        int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2, int_T numFillColor,
        boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    //Copy the inputImage to outImage
    int_T numPixels = numCol*numRow*3;
    memcpy(rgbOut, rgbIn, numPixels * sizeof(real32_T));
    
    //Get the values of opacity and lineWidth
    real32_T *opacity = (real32_T *)malloc(sizeof(real32_T));
    opacity[0] = (real32_T)(mOpacity);
    int32_T *lineWidthArr = (int32_T*)malloc(1 * sizeof(int32_T));
    lineWidthArr[0] = (int32_T)mLineWidthArr;
    int_T dimens[2] = {(int_T)dimens1,(int_T)dimens2 };
    
    //Instantiate the drawBase Object for Shape
    drawBaseP2P[objCounter] = InstantiateShape<real32_T, real32_T, int32_T, int32_T, real32_T, real32_T>
            (static_cast<real32_T*>(rgbOut), static_cast<int32_T*>(pts), static_cast<real32_T*>(fillColor),
            opacity, lineWidthArr, shape, isAntiAlias, numRow, numCol, numColor, numDimens, dimens, numFillColor,
            isFillShape, mimicFillPoly, static_cast<uint8_T*>(pixCount));
    
}

void instantiateDrawBaseShape_double(void *ptrObj, void *rgbOut, void *rgbIn, void *pts, void *fillColor,
        double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias, int_T numRow, int_T numCol,
        int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2, int_T numFillColor,
        boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    
    //Copy the inputImage to outImage
    int_T numPixels = numCol*numRow*3;
    memcpy(rgbOut, rgbIn, numPixels * sizeof(real_T));
    
    // Get the values of opacity and lineWidth
    real_T *opacity = (real_T *)malloc(sizeof(real_T));
    opacity[0] = (real_T)(mOpacity);
    int32_T *lineWidthArr = (int32_T*)malloc(1 * sizeof(int32_T));
    lineWidthArr[0] = (int32_T)mLineWidthArr;
    int_T dimens[2] = {(int_T)dimens1,(int_T)dimens2 };
    
    //Instantiate the drawBase Object for Shape
    drawBaseP2P[objCounter] = InstantiateShape<real_T, real_T, int32_T, int32_T, real_T, real_T>
            (static_cast<real_T*>(rgbOut), static_cast<int32_T*>(pts), static_cast<real_T*>(fillColor),
            opacity, lineWidthArr, shape, isAntiAlias, numRow, numCol, numColor, numDimens, dimens,
            numFillColor, isFillShape, mimicFillPoly, static_cast<uint8_T*>(pixCount));
}

void instantiateDrawBaseShape_uint8(void *ptrObj, void *rgbOut, void *rgbIn, void *pts, void *fillColor,
        double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias, int_T numRow, int_T numCol,
        int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2, int_T numFillColor,
        boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    
    //Copy the inputImage to outImage
    int_T numPixels = numCol*numRow*3;
    memcpy(rgbOut, rgbIn, numPixels * sizeof(uint8_T));
    
    // Get the values of opacity and lineWidth
    real32_T *opacity = (real32_T *)malloc(sizeof(real32_T));
    opacity[0] = (real32_T)(mOpacity);
    int32_T *lineWidthArr = (int32_T*)malloc(1 * sizeof(int32_T));
    lineWidthArr[0] = (int32_T)mLineWidthArr;
    int_T dimens[2] = {(int_T)dimens1,(int_T)dimens2 };
    
    //Instantiate the drawBase Object for Shape
    drawBaseP2P[objCounter] = InstantiateShape<uint8_T, uint8_T, int32_T, int32_T, real32_T, real32_T>
            (static_cast<uint8_T*>(rgbOut), static_cast<int32_T*>(pts), static_cast<uint8_T*>(fillColor),
            opacity, lineWidthArr, shape, isAntiAlias, numRow, numCol, numColor, numDimens, dimens,
            numFillColor, isFillShape, mimicFillPoly,  static_cast<uint8_T*>(pixCount));
}

void instantiateDrawBaseShape_uint16(void *ptrObj, void *rgbOut, void *rgbIn, void *pts, void *fillColor,
        double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias, int_T numRow,
        int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2, int_T numFillColor,
        boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    //Copy the inputImage to outImage
    int_T numPixels = numCol*numRow*3;
    memcpy(rgbOut, rgbIn, numPixels * sizeof(uint16_T));
    
    // Get the values of opacity and lineWidth
    real32_T *opacity = (real32_T *)malloc(sizeof(real32_T));
    opacity[0] = (real32_T)(mOpacity);
    int32_T *lineWidthArr = (int32_T*)malloc(1 * sizeof(int32_T));
    lineWidthArr[0] = (int32_T)mLineWidthArr;
    int_T dimens[2] = {(int_T)dimens1,(int_T)dimens2 };
    
    //Instantiate the drawBase Object for Shape
    drawBaseP2P[objCounter] = InstantiateShape<uint16_T, uint16_T, int32_T, int32_T, real32_T, real32_T>
            (static_cast<uint16_T*>(rgbOut), static_cast<int32_T*>(pts), static_cast<uint16_T*>(fillColor),
            opacity, lineWidthArr, shape, isAntiAlias, numRow, numCol, numColor, numDimens, dimens, numFillColor,
            isFillShape, mimicFillPoly, static_cast<uint8_T*>(pixCount));
    
}

void instantiateDrawBaseShape_int16(void *ptrObj, void *rgbOut, void *rgbIn, void *pts, void *fillColor,
        double mOpacity, int32_T mLineWidthArr, int32_T shape, boolean_T isAntiAlias, int_T numRow,
        int_T numCol, int_T numColor, int_T numDimens, int32_T dimens1, int32_T dimens2, int_T numFillColor,
        boolean_T isFillShape, boolean_T mimicFillPoly, void* pixCount, int objCounter)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    //Copy the inputImage to outImage
    int_T numPixels = numCol*numRow*3;
    memcpy(rgbOut, rgbIn, numPixels * sizeof(int16_T));
    
    // Get the values of opacity and lineWidth
    real32_T *opacity = (real32_T *)malloc(sizeof(real32_T));
    opacity[0] = (real32_T)(mOpacity);
    int32_T *lineWidthArr = (int32_T*)malloc(1 * sizeof(int32_T));
    lineWidthArr[0] = (int32_T)mLineWidthArr;
    int_T dimens[2] = {(int_T)dimens1,(int_T)dimens2 };
    
    //Instantiate the drawBase Object for Shape
    drawBaseP2P[objCounter] = InstantiateShape<int16_T, int16_T, int32_T, int32_T, real32_T, real32_T>
            (static_cast<int16_T*>(rgbOut), static_cast<int32_T*>(pts), static_cast<int16_T*>(fillColor),
            opacity, lineWidthArr, shape, isAntiAlias, numRow, numCol, numColor, numDimens, dimens, numFillColor,
            isFillShape, mimicFillPoly,  static_cast<uint8_T*>(pixCount));
}



void mDrawShapes(void *ptrObj, boolean_T isFillShape, boolean_T isAntiAlias, int32_T shape,
        int32_T lineWidth, int_T numRow, int_T numCol)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    drawShapes(drawBaseP2P, isFillShape, isAntiAlias, shape, lineWidth, numRow, numCol);
}

void deallocateMemoryShape(void *ptrObj)
{
    DrawBase **drawBaseP2P = (DrawBase **)ptrObj;
    if (drawBaseP2P)
    {
        if (drawBaseP2P[0]) {
            delete drawBaseP2P[0];
        }
        if (drawBaseP2P[1]) {
            delete drawBaseP2P[1];
        }
        delete[] drawBaseP2P;
    }
}

#endif
