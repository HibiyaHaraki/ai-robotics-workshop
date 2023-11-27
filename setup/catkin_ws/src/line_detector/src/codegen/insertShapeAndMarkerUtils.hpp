//
//  insertShapeAndMarkerUtils.hpp
//  libmwvision
//
//  This file contains utilities used by visionInsertShape and visionInsertMarker.
//
//  Copyright 2019 The MathWorks, Inc.

#include <cmath>
#include <algorithm>
#include <cstring>
#include "cvstDraw.hpp"

enum {
    SHAPE_RECTANGLE = 1,
    SHAPE_LINE = 2,
    SHAPE_POLYGON = 3,
    SHAPE_CIRCLE = 4
};

enum {
    SHAPE_IDX = 0,
    FILL_SHAPE_IDX,
    LINE_W_IDX,
    OPAC_IDX,
    SMOOTH_EDGES_IDX,
    IMG_DT_IDX,
    IMG_IDX,
    PTS_IDX,
    COLOR_IDX
};

enum {
    MARKER_CIRCLE   = 1,
    MARKER_XMARK    = 2,
    MARKER_PLUS     = 3,
    MARKER_STAR     = 4,
    MARKER_SQUARE   = 5
};

enum {
    MARKER_IDX = 0,
    MARKER_IMG_DT_IDX,
    MARKER_SIZE_IDX,
    MARKER_IMG_IDX,
    MARKER_PTS_IDX,
    MARKER_COLOR_IDX
};


boolean_T checkAntiAlias(const int32_T shape, boolean_T isAntiAlias);

boolean_T isLineWidthApplicable(const int32_T shape, boolean_T isFillShape);

boolean_T useFillShapePolygonCodeX(const int32_T shape, boolean_T isFillShape, boolean_T mimicFillPoly);

boolean_T isLineOrNonFilledPolygon(const int32_T shape, boolean_T isFillShape);

void drawShapes(DrawBase **drawBaseP2P, boolean_T isFillShape, boolean_T isAntiAlias, int32_T shape,
        int32_T lineWidth, int_T numRow, int_T numCol);

template<typename T>
        inline T getRowDimen(T numDimen, const T* dimens)
{
    const T idx(1);
    return(idx >= numDimen ? 1 : dimens[idx]);
}

template<typename T>
        inline T getColDimen(T numDimen, const T* dimens)
{
    const T idx(0);
    return(idx >= numDimen ? 1 : dimens[idx]);
}

template<typename T>
        boolean_T CheckDataDimen(T numDimen, const T* dimens,
        T dimLen, T& numCount)
{
    boolean_T isValid = false;
    T numRow = getRowDimen(numDimen, dimens);
    T numCol = getColDimen(numDimen, dimens);
    if (numRow == dimLen) {
        isValid = true;
        numCount = numCol;
    }
    else if (numRow == 1 && numCol == dimLen) {
        isValid = true;
        numCount = numRow;
    }
    return(isValid);
}

template<typename T>
        boolean_T CheckDataDimenEven(T numDimen, const T* dimens,
        T minNumRow, T& numCount,
        T& numSubCount)
{
    boolean_T isValid = false;
    T numRow = getRowDimen(numDimen, dimens);
    T numCol = getColDimen(numDimen, dimens);
    
    if (numRow >= minNumRow && !(numRow & 0x1)) {
        isValid = true;
        numCount = numCol;
        numSubCount = numRow >> 1;
    }
    else if (numRow == 1 && numCol >= minNumRow && !(numCol & 0x1)) {
        isValid = true;
        numCount = numRow;
        numSubCount = numCol >> 1;
    }
    return(isValid);
}

template<typename T>
        boolean_T CheckAndGetNumShape(int32_T shape, T numDimen, const T* dimens,
        int_T* pNumShape = NULL, int_T* pNumSubShape = NULL)
{
    boolean_T isValid = false;
    int_T numShape = 0;
    int_T numSubShape = 0;
    
    if (numDimen <= 2)
    {
        switch (shape)
        {
            case SHAPE_RECTANGLE:
                isValid = CheckDataDimen(numDimen, dimens, 4, numShape);
                break;
                
            case SHAPE_LINE:
                isValid = CheckDataDimenEven(numDimen, dimens, 4, numShape, numSubShape);
                break;
                
            case SHAPE_POLYGON:
                isValid = CheckDataDimenEven(numDimen, dimens, 6, numShape, numSubShape);
                break;
                
            case SHAPE_CIRCLE:
                isValid = CheckDataDimen(numDimen, dimens, 3, numShape);
                break;
                
            default:
                isValid = false;
        }
    }
    
    // Copy the data to the output argument if the point is not NULL.
    if (pNumShape)    *pNumShape = numShape;
    if (pNumSubShape) *pNumSubShape = numSubShape;
    return(isValid);
}


template<typename T>
        boolean_T CheckAndGetNumMarker(int32_T shape, T numDimen, const T* dimens,
        int_T* pNumShape = NULL, int_T* pNumSubShape = NULL)
{
    boolean_T isValid = false;
    int_T numShape = 0;
    int_T numSubShape = 0;
    
    if (numDimen <= 2)
    {
        switch (shape)
        {
            case MARKER_CIRCLE:
            case MARKER_XMARK:
            case MARKER_PLUS:
            case MARKER_STAR:
            case MARKER_SQUARE:
                // xxx WJ
                isValid = CheckDataDimen(numDimen, dimens, 2, numShape);
                break;
                
            default:
                isValid = false;
        }
    }
    
    // Copy the data to the output argument if the point is not NULL.
    if (pNumShape)    *pNumShape = numShape;
    if (pNumSubShape) *pNumSubShape = numSubShape;
    return(isValid);
}


template<class DT, class BT, class PT, class VT, class OpDT, class OpBT>
        DrawBase* InstantiateShape(DT *rgbOut, PT *pts, DT *fillColor, OpDT *opacity, int32_T *lineWidthArr,
        int32_T shape, boolean_T isAntiAlias, int_T numRow, int_T numCol, int_T numColor, int_T numDimens,
        int_T* dimens, int_T numFillColor, boolean_T isFillShape, boolean_T mimicFillPoly, uint8_T *pixCount)
{
    DrawBase* drawBase = NULL;
    int_T numShape, numSubShape;
    
    // Only for thick or non-thick line/polygon:  numSubShape is the number of points ((x,y) pair)
    //in each row of point port
    CheckAndGetNumShape(shape, numDimens, dimens, &numShape, &numSubShape);
    
    int32_T numOpacity = 1;
    isAntiAlias = checkAntiAlias(shape, isAntiAlias);
    
    DT* image = rgbOut;								//Pointer to first element of entire image
    DT* imageG = image + (numCol * numRow * 1);		//Pointer to first element of green channel of image
    DT* imageB = image + (numCol * numRow * 2);		//Pointer to first element of blue channel of image
    
    PT* size = NULL;                     // Only used in Draw Markers block
    PT* ptsOrPtsDW = NULL;
    PT *ptsDW = (PT *)malloc((numShape*numSubShape * 4)*(sizeof(PT)));
    
    DT *fillColorSrc = fillColor;		// Same as fillColor
    OpDT *opacitySrc = opacity;			// Same as Opacity
    int32_T *lineWidthPtr = (isLineWidthApplicable(shape, isFillShape)) ? lineWidthArr : NULL;
    
    boolean_T isLine = (shape == SHAPE_LINE);
    boolean_T isNonFilledPolygon = ((shape == SHAPE_POLYGON) && (!isFillShape));
    
    // Instantiate class for Rectangle
    if (shape == SHAPE_RECTANGLE)
    {
        if (isFillShape) {
            drawBase = (DrawBase*)new
                    DrawFilledRectangleAnySize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE>(
                    DRAW_COMM_VALUE_LIST, pts);
        }
        else {
            drawBase = (DrawBase*)new
                    DrawRectangleAnySize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE>(
                    DRAW_COMM_VALUE_LIST, pts);
        }
    }
    
    // Instantiate class for Thick line or Polygon
    else if ((shape == SHAPE_POLYGON) || ((shape == SHAPE_LINE) && mimicFillPoly))
    {
        if (useFillShapePolygonCodeX(shape, isFillShape, mimicFillPoly)) {
            ptsOrPtsDW = (isLineOrNonFilledPolygon(shape, isFillShape) && mimicFillPoly) ? ptsDW : pts;
            boolean_T foldPtDW = false;
            int numPtPerPolygon = numSubShape;
            if (isLineOrNonFilledPolygon(shape, isFillShape) && mimicFillPoly) {
                numPtPerPolygon *= 2;// 2 for double points
                // for line: line to polygon points,
                // for polygon, inner and outer polygon points)
                if (shape == SHAPE_POLYGON) foldPtDW = true;
            }
            
            int32_T *polygonEdge = (int32_T*)malloc((numShape*numPtPerPolygon*EDGE_LEN) * sizeof(int32_T));
            int32_T *polygonEdgeBk = NULL;
            
            // "NOTE: THICK:" thick or non-thick line/polygon:
            // numSubShape is the number of points ((x,y) pair) in each row of point port
            // since to draw thick line or polygon, we need to double the number of points
            // representing polygon points
            // we multiply numSubShape by 2 to get numPtPerPolygon
            if (isAntiAlias) {
                Polygon<int32_T, PT, MODE_ALG_ANTIALIAS>* polygon
                        = new Polygon<int32_T, PT, MODE_ALG_ANTIALIAS>(
                        ptsOrPtsDW, ptsDW, polygonEdge, polygonEdgeBk, 
                        numShape, numPtPerPolygon, numShape*numPtPerPolygon, foldPtDW);
                
                ScanLineBase<int32_T, PT, MODE_ALG_ANTIALIAS>* scanline
                        = (ScanLineBase<int32_T, PT, MODE_ALG_ANTIALIAS>*)
                        new ScanLine<int32_T, PT, MODE_ALG_ANTIALIAS>(
                        polygon, 0, 0, numRow*SUBPIX_LEN - 1, numCol*SUBPIX_LEN - 1);
                
                drawBase = (DrawBase*)new
                        DrawFilledPolygon<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_ALG_ANTIALIAS>(
                        DRAW_COMM_VALUE_LIST, scanline, pts, ptsDW);
            }
            else {
                Polygon<int32_T, PT, MODE_ALG_DIRECT>*
                        polygon = new Polygon<int32_T, PT, MODE_ALG_DIRECT>(
                        ptsOrPtsDW, ptsDW, polygonEdge, polygonEdgeBk,
                        numShape, numPtPerPolygon, numShape*numPtPerPolygon, foldPtDW);
                
                ScanLineBase<int32_T, PT, MODE_ALG_DIRECT>*
                        scanline = (ScanLineBase<int32_T, PT, MODE_ALG_DIRECT>*)
                        new ScanLine<int32_T, PT, MODE_ALG_DIRECT>(polygon, 0, 0, numRow - 1, numCol - 1);
                
                drawBase = (DrawBase*)new
                        DrawFilledPolygon<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_ALG_DIRECT>(
                        DRAW_COMM_VALUE_LIST, scanline, pts, ptsDW);
            }
        }
        
        else {
            if (isAntiAlias) {
                drawBase = (DrawBase*)new
                        DrawPolygon<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_ALG_ANTIALIAS>(
                        DRAW_COMM_VALUE_LIST, pts, ptsDW);//remove ptsDW from here
            }
            else {
                drawBase = (DrawBase*)new
                        DrawPolygon<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_ALG_DIRECT>(
                        DRAW_COMM_VALUE_LIST, pts, ptsDW);//remove ptsDW from here
            }
        }
        
    }    
    // Instantiate class for Thin Line (Line Width < 1)
    else if (shape == SHAPE_LINE)
    {
        if (isAntiAlias) {
            drawBase = (DrawBase*)new
                    DrawAnyLine<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_ALG_ANTIALIAS>(
                    DRAW_COMM_VALUE_LIST, pts, ptsDW);//remove ptsDW from here
        }
        else {
            drawBase = (DrawBase*)new
                    DrawAnyLine<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_ALG_DIRECT>(
                    DRAW_COMM_VALUE_LIST, pts, ptsDW);//remove ptsDW from here
        }
    }
    
    // Instantiate class for Circle
    else if (shape == SHAPE_CIRCLE)
    {
        if (isAntiAlias) {
            if (isFillShape) {
                drawBase = (DrawBase*)new
                        DrawCircleAnySize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_INT_FILLED,
                        MODE_ALG_ANTIALIAS>(DRAW_COMM_VALUE_LIST, pts);
            }
            else {
                drawBase = (DrawBase*)new
                        DrawCircleAnySize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_INT_EMPTY,
                        MODE_ALG_ANTIALIAS>(DRAW_COMM_VALUE_LIST, pts);
            }
        }
        else {
            if (isFillShape) {
                drawBase = (DrawBase*)new
                        DrawCircleAnySize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_INT_FILLED,
                        MODE_ALG_DIRECT>(DRAW_COMM_VALUE_LIST, pts);
            }
            else {
                drawBase = (DrawBase*)new
                        DrawCircleAnySize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_INT_EMPTY,
                        MODE_ALG_DIRECT>(DRAW_COMM_VALUE_LIST, pts);
            }
        }
    }
    // no 'if else' for MARKER_CIRCLE,MARKER_XMARK,MARKER_PLUS,MARKER_STAR,MARKER_SQUARE
    
    return(drawBase);
}

template<class DT, class BT, class PT, class VT, class OpDT, class OpBT>
        DrawBase* InstantiateMarker(DT *rgbOut, PT *pts, OpDT *opacity, DT *fillColor,
        int32_T markerShape, int32_T markerSize, int_T numRow, int_T numCol, int_T numColor,
        int_T numFillColor, int_T numDimens, int_T* dimens, uint8_T *pixCount)
{
    DrawBase* drawBase = NULL;
    int_T  numShape, numSubShape;
    
    CheckAndGetNumMarker(markerShape, numDimens, dimens, &numShape, &numSubShape);
    
    int32_T shape = markerShape;
    int32_T numOpacity = 1;
    
    boolean_T isAntiAlias = false;
    boolean_T isLine = false;
    boolean_T isNonFilledPolygon = false;
    
    DT* image = rgbOut;								//Pointer to first element of entire image
    DT* imageG = image + (numCol * numRow * 1);		//Pointer to first element of green channel of image
    DT* imageB = image + (numCol * numRow * 2);		//Pointer to first element of blue channel of image
    
    PT* size = &markerSize;
    DT *fillColorSrc = fillColor;		// Same as fillColor
    OpDT *opacitySrc = opacity;			// Same as Opacity
    int32_T *lineWidthPtr = NULL;
    
    switch(shape)
    {
        // Instantiate class for Square Marker
        case MARKER_SQUARE:
            drawBase = (DrawBase*)new
                    DrawSquareFixedSize<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT_ONE>(
                    DRAW_COMM_VALUE_LIST, pts);
            break;
            // Instantiate class for Circle Marker
        case MARKER_CIRCLE:
            drawBase = (DrawBase*)new
                    DrawCircleFixedSize<DT, BT, PT, VT, OpDT, OpBT, MODE_PORT_ONE, MODE_INT_EMPTY,
                    MODE_ALG_DIRECT>(DRAW_COMM_VALUE_LIST, pts);
            
            break;
            // Instantiate class for XMark Marker
        case MARKER_XMARK:
            drawBase = (DrawBase*)new
                    DrawXMarkFixedSize<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT_ONE,MODE_ALG_DIRECT>(
                    DRAW_COMM_VALUE_LIST, pts);
            break;
            // Instantiate class for Plus Marker
        case MARKER_PLUS:
            drawBase = (DrawBase*)new
                    DrawPlusFixedSize<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT_ONE>(
                    DRAW_COMM_VALUE_LIST, pts);
            break;
            // Instantiate class for Star Marker
        case MARKER_STAR:
            drawBase = (DrawBase*)new
                    DrawStarFixedSize<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT_ONE,MODE_ALG_DIRECT>(
                    DRAW_COMM_VALUE_LIST, pts);
        default:
            ;
    }
    
    return(drawBase);
}
