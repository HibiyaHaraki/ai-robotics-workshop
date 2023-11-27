
///////////////////////////////////////////////////////////////////////////////
// This file contains helpers to run Insert Shape And Marker Utils functions. 

//  Copyright 2019 The MathWorks, Inc.
///////////////////////////////////////////////////////////////////////////////

#include "insertShapeAndMarkerUtils.hpp"

boolean_T checkAntiAlias(const int32_T shape, boolean_T isAntiAlias)
{
    if (shape == SHAPE_RECTANGLE) {
        isAntiAlias = false; // rectangles have no antialiasing property
        return isAntiAlias;
    }
    else {
        return isAntiAlias;
    }
}

boolean_T isLineWidthApplicable(const int32_T shape, boolean_T isFillShape)
{
    boolean_T isLineWApplicable = false;
    
    if (shape == SHAPE_LINE)
        isLineWApplicable = true;
    else if (!isFillShape)
        isLineWApplicable = true;
    
    return isLineWApplicable;
}

boolean_T useFillShapePolygonCodeX(const int32_T shape, boolean_T isFillShape, boolean_T mimicFillPoly)
{
    boolean_T useFillShapePolygon = false;
    
    if (shape == SHAPE_POLYGON) {
        if (isFillShape) {
            useFillShapePolygon = true;
        }
        else { // not fill shape
            if (mimicFillPoly) useFillShapePolygon = true;
        }
    }
    else if ((shape == SHAPE_LINE) && mimicFillPoly)
        useFillShapePolygon = true;
    
    return useFillShapePolygon;
}

boolean_T isLineOrNonFilledPolygon(const int32_T shape, boolean_T isFillShape)
{
    
    boolean_T isValid = ((shape == SHAPE_LINE) ||
            ((shape == SHAPE_POLYGON) && (!isFillShape)));
    return isValid;
}

void copyInputImageToOutput(void *rgbOut, const void *rgbIn, size_t numBytes)
{
    memcpy(rgbOut, rgbIn, numBytes);
}

void drawShapes( DrawBase **drawBaseP2P, boolean_T isFillShape, boolean_T isAntiAlias, int32_T shape, int32_T lineWidth,
        int_T numRow, int_T numCol)
{
    // Check antialiasing property
    isAntiAlias = checkAntiAlias(shape, isAntiAlias);
    
    // Check if Shape is Line or Non-Filled polygon
    int fcnIdx = 0;
    if (isLineOrNonFilledPolygon(shape, isFillShape)) {
        int32_T *lineWidthPtr = (isLineWidthApplicable(shape, isFillShape)) ? &lineWidth : NULL;
        if (lineWidthPtr[0] > 1) fcnIdx = 1;
        
    }
    if (drawBaseP2P[fcnIdx]) {
        const boolean_T isGetMaxSize = false;
        int_T numShape = 0, numFillColor = 0;
        
        const boolean_T isPtsVarSize = false;			// always set to false
        const boolean_T isFillColorVarSize = false;		// always set to false
        
        if (isFillShape && !isAntiAlias) {
            drawBaseP2P[fcnIdx]->UpdateFillColorOpacity();
        }
        
        // Draw the shapes
        if ((!isPtsVarSize || (isPtsVarSize && numShape > 0))
        && (!isFillColorVarSize || (isFillColorVarSize && numFillColor > 0))
        && (numRow > 0 && numCol > 0)) {
            drawBaseP2P[fcnIdx]->ProcessStep();
            
        }
    }    
}