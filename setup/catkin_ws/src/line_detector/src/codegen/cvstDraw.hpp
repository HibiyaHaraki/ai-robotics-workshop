/*
* Copyright 2008-2019 The MathWorks, Inc.
*/

#ifndef CVSTDRAW_HPP
#define CVSTDRAW_HPP

#ifdef SUPPORTS_PRAGMA_ONCE
# pragma once
#endif

#include <math.h>
#include <cstddef>
#include "vision_defines.h"
#include "cvst_polygon_scanline.hpp"

//-----------------------------------------------------------------------------
typedef enum {
    PARALLEL_TO_NO_AXIS = 0,
    PARALLEL_TO_Y_AXIS,
    PARALLEL_TO_X_AXIS   
} Paral_T;

typedef enum {
    BBOX_ROW = 0,
    BBOX_COL,
    BBOX_NUMROW,
    BBOX_NUMCOL,
    BBOX_LEN
} BBOX_INDEX;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef enum {
    PT_ROW1 = 0,
    PT_COL1,
    PT_ROW2,
    PT_COL2,
    PT_LEN2
} PT_INDEX2;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef enum {
    VIEWPORT_FIRSTROW = 0,
    VIEWPORT_FIRSTCOL,
    VIEWPORT_LASTROW,
    VIEWPORT_LASTCOL,
    VIEWPORT_LEN
} VIEWPORT_INDEX;
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
typedef enum {
    CIRCLE_ROW = 0,
    CIRCLE_COL,
    CIRCLE_RADIUS,
    CIRCLE_LEN
} CIRCLE_INDEX;
//-----------------------------------------------------------------------------
typedef struct 
{
    int x;
    int y;
} XY_T;
//-----------------------------------------------------------------------------
// Image is in one port or three ports
#define MODE_PORT_ONE       boolean_T
#define MODE_PORT_RGB       int_T

// Use anti-aliasing or not
#define MODE_ALG_DIRECT     boolean_T
#define MODE_ALG_ANTIALIAS  int_T

// Fill shape or not
#define MODE_INT_EMPTY      boolean_T
#define MODE_INT_FILLED     int_T
//-----------------------------------------------------------------------------

typedef enum {
    LINE_HORIZONTAL = 0,
    LINE_VERTICAL,
    LINE_UP45DEGREE,
    LINE_DOWN45DEGREE
} LINE_MODE;
//-----------------------------------------------------------------------------

//==========================

inline void cast(real_T *out, int_T outIdx, const real_T *in){out[outIdx] = in[0];}
inline void cast(uint8_T *out, int_T outIdx, const uint8_T *in){out[outIdx] = in[0];}
inline void cast(uint16_T *out, int_T outIdx, const uint16_T *in){out[outIdx] = in[0];}
inline void cast(int16_T *out, int_T outIdx, const int16_T *in){out[outIdx] = in[0];}

inline
void cast(real32_T *out, int_T outIdx, const real32_T *in)
{
    out[outIdx] = in[0];
}

inline
void cast(uint8_T *out, int_T outIdx, const real32_T *in)
{
    out[outIdx] = (uint8_T)in[0];
}

inline
void cast(uint16_T *out, int_T outIdx, const real32_T *in)
{
    out[outIdx] = (uint16_T)in[0];
}

inline
void cast(int16_T *out, int_T outIdx, const real32_T *in)
{
    out[outIdx] = (int16_T)in[0];
}
        
void multiplyEqual(real_T *out, int_T outIdx, const real_T *in, int_T inIdx);

void multiplyEqual(real32_T *out, int_T outIdx, const real32_T *in, int_T inIdx);

void multiplyEqual(uint8_T *out, int_T outIdx, const real32_T *in, int_T inIdx);

void multiplyEqual(uint16_T *out, int_T outIdx, const real32_T *in, int_T inIdx);

void multiplyEqual(int16_T *out, int_T outIdx, const real32_T *in, int_T inIdx);

//=============================================================================
//-----------------------------------------------------------------------------
template<class T, class MODE_ALG>
class BresenhamLine
{
public:
    void Initialize(T* line, T numRow) 
    {
        T rangeRow = AbsoluteValue(line[PT_ROW2] - line[PT_ROW1]);
        T rangeCol = AbsoluteValue(line[PT_COL2] - line[PT_COL1]);

        if(rangeRow > rangeCol) {
            mInStep = 1;
            mOutStep = numRow;
        }
        else {
            mInStep = numRow;
            mOutStep = 1;
            SwapValues(line[PT_ROW1], line[PT_COL1]);
            SwapValues(line[PT_ROW2], line[PT_COL2]);
        }

        if(line[PT_ROW1] > line[PT_ROW2]) {
            SwapValues(line[PT_ROW1], line[PT_ROW2]);
            SwapValues(line[PT_COL1], line[PT_COL2]);
        }

        mInRange = line[PT_ROW2] - line[PT_ROW1];
        if(line[PT_COL1] <= line[PT_COL2]) {
            mDelta = 1;
            mOutRange = line[PT_COL2] - line[PT_COL1];
        }
        else {
            mDelta = -1;
            mOutRange = line[PT_COL1] - line[PT_COL2];
        }

        mIn = line[PT_ROW1];
        mInMax = line[PT_ROW2];
        mOut = line[PT_COL1];
        mErr = -((mInRange + 1) / 2);

        // mIdxPix and mIdxDelta are used only for MODE_ALG_DIRECT
        mIdxPix = mIn * mInStep + mOut * mOutStep;
        mIdxDelta = mDelta * mOutStep + mInStep;
    }

    inline boolean_T IsInRange(void) {
        return(mIn <= mInMax); 
    }

    inline boolean_T IsHorizontal(void) {
        return(mInStep != 1);
    }

    inline T GetPosition(void) { 
        return(mOut);
    }

    inline T GetIdxPix(void) {
        return(mIdxPix);
    }

    inline T CalculateIndex(T in, T out)
    {
        return(in*mInStep+out*mOutStep);
    }

    inline void MoveToNextPosition(void)
    {
        MoveToNextPosition((MODE_ALG)0);
    }

private:
    inline void MoveToNextPosition(MODE_ALG_DIRECT)
    {
        mErr += mOutRange;
        if(mErr >= 0) {
            mErr -= mInRange;
            mIdxPix += mIdxDelta;
        }
        else {
            mIdxPix += mInStep;
        }
        mIn ++;
    }

    inline void MoveToNextPosition(MODE_ALG_ANTIALIAS)
    {
        mErr += mOutRange;
        if(mErr >= 0) {
            mOut += mDelta;
            mErr -= mInRange;
        }
        mIn ++;
    }

private:
    inline T AbsoluteValue(T val) { return(val>=0? val: -val); }
    inline void SwapValues(T& val1, T& val2) { T tmp=val1; val1=val2; val2=tmp; }

private:
    T mIn;
    T mInMax;
    T mOut;
    T mInStep;
    T mOutStep;
    T mInRange;
    T mOutRange;
    T mErr;
    T mDelta;

    // Used only for MODE_ALG_DIRECT
    T mIdxPix;
    T mIdxDelta;
}; // end of the Bresenham line drawing algorithm
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
typedef enum {
    CIRCLE_CLOCKWISE = 0,
    CIRCLE_COUNTERCLOCKWISE,
    CIRCLE_OUTOFRANGE
} CIRCLE_STATUS;

template<class T>
class MidPointFullCircle
{
public:
    MidPointFullCircle() {
        //Initialize(0);
    }

    void Initialize(T radius) {
        mStatus = CIRCLE_CLOCKWISE;
        mErr = 1-radius;
        mRow = radius;
        mCol = 0;
        mColDif = 0;
        mRowDif = -2*radius;
    }

    inline boolean_T IsInRange(void) {
        return(mStatus != CIRCLE_OUTOFRANGE); 
    }

    inline T GetRow(void) { 
        return(mStatus==CIRCLE_CLOCKWISE? mRow: mCol);
    }

    inline void MoveToNextColumn(void)
    {
        T rowPre = mRow;
        // isContinue is used only for CIRCLE_COUNTERCLOCKWISE case
        boolean_T isContinue;

        switch(mStatus) {
        case CIRCLE_CLOCKWISE:
            if(mErr >= 0) {
                mRow --;
                mRowDif += 2;
                mErr += mRowDif;
            }
            mCol ++;
            mColDif += 2;
            mErr += (mColDif + 1);

            if(mCol < mRow) {
                break;
            }
            else { // Change direction to counter-clockwise
                mErr = mErr - 4 * mCol + 2 * mRow;
                mStatus = CIRCLE_COUNTERCLOCKWISE;

                if(mCol > mRow) {
                    rowPre = mRow;
                }
                else if(rowPre == mRow) {
                    rowPre = mRow - 1;
                }
                else { // col=row && row!=rowPre: No need to move further
                    break;
                }
            }

        case CIRCLE_COUNTERCLOCKWISE:
            isContinue = (mCol >= 0);
            while(isContinue) {
                if(mErr < 0) {
                    mErr += (2 - mRowDif);
                    mRow ++;
                    mRowDif -= 2;
                }
                mCol --;
                mColDif -= 2;
                mErr += (1 - mColDif);
                isContinue = (mRow == rowPre && mCol >= 0);
            }

            if (mCol < 0) {
                mStatus = CIRCLE_OUTOFRANGE;
            }

        default: // CIRCLE_OUTOFRANGE, just to silent compiler
            ;
        }
    }

private:
    CIRCLE_STATUS mStatus;
    T mErr;
    T mRow;
    T mCol;
    T mColDif;
    T mRowDif;
}; // end of the mid-point full circle algorithm
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class PT, class VT>
boolean_T FindLineInViewPort(const VT* viewPort, const PT* inLine, VT* outLine)
{
    // OutCode bit masks used for Cohen-Sutherland line clipping 
    const uint32_T VIOLATE_CMIN = 1;
    const uint32_T VIOLATE_CMAX = 2;
    const uint32_T VIOLATE_RMIN = 4;
    const uint32_T VIOLATE_RMAX = 8;
    const int32_T  INT30_VAL    = 1<<30;

    // Compute Cohen-Sutherland-style outcodes for clipping endpoints A and B 
    int32_T i, temp, dr, dc;
    uint32_T OutCode1, OutCode2;
    boolean_T visited1 = false;
    boolean_T visited2 = false;

    for(i=0; i<PT_LEN2; i++) outLine[i] = ToIntCoordinate<VT>(inLine[i]);

    boolean_T done = false;
    boolean_T isInBound =false;
    while (!done)
    {
        // Keep looping until both points completely clipped
        // Use goto/label to suppress warnings from "while(1)", and
        //   to gain faster code (fewer instructions in critical loop)
        //
        OutCode1 = 0;  // setting these individually leads to shorter code 
        OutCode2 = 0;

        // Determine viewport violations:  
        if(outLine[PT_ROW1] < viewPort[VIEWPORT_FIRSTROW])       OutCode1 |= VIOLATE_RMIN; 
        else if(outLine[PT_ROW1] > viewPort[VIEWPORT_LASTROW])   OutCode1 |= VIOLATE_RMAX; 

        if(outLine[PT_ROW2] < viewPort[VIEWPORT_FIRSTROW])       OutCode2 |= VIOLATE_RMIN; 
        else if(outLine[PT_ROW2] > viewPort[VIEWPORT_LASTROW])   OutCode2 |= VIOLATE_RMAX; 

        if(outLine[PT_COL1] < viewPort[VIEWPORT_FIRSTCOL])       OutCode1 |= VIOLATE_CMIN; 
        else if(outLine[PT_COL1] > viewPort[VIEWPORT_LASTCOL])   OutCode1 |= VIOLATE_CMAX; 

        if(outLine[PT_COL2] < viewPort[VIEWPORT_FIRSTCOL])       OutCode2 |= VIOLATE_CMIN; 
        else if(outLine[PT_COL2] > viewPort[VIEWPORT_LASTCOL])   OutCode2 |= VIOLATE_CMAX; 

        if (!(OutCode1 | OutCode2)) {
            done = true;
            isInBound = true; //return(1); // Line falls completely within bounds                            
        }
        else if (OutCode1 & OutCode2) {  
            done = true;
            isInBound = false; //return(0); // Line falls completely out of bounds 
        }
        else if (OutCode1 != 0) {  // Clip 1st point; if it's in-bounds, clip 2nd point 
            // Clip A 
            //===vv Part-1 vv======
            if (visited1) {
                outLine[PT_ROW1] = ToIntCoordinate<VT>(inLine[PT_ROW1]);
                outLine[PT_COL1] = ToIntCoordinate<VT>(inLine[PT_COL1]);
            }

            dr = outLine[PT_ROW2] - outLine[PT_ROW1];
            dc = outLine[PT_COL2] - outLine[PT_COL1];

            if ((dr > INT30_VAL || dr < -INT30_VAL) ||
                (dc > INT30_VAL || dc < -INT30_VAL) ){
                done = true;
                isInBound = false;
                visited1 = true;
            }
            else if (OutCode1 & VIOLATE_RMIN) { // violated RMin 
                // Clip A to minimum row 
                temp = (viewPort[VIEWPORT_FIRSTROW] - outLine[PT_ROW1]) * dc;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dr >= 0)) || ((temp < 0) && (dr < 0)))
                    outLine[PT_COL1] += ((((temp << 1)/dr)+1)/2);// perform rounding operation 
                else
                    outLine[PT_COL1] += ((((temp << 1)/dr)-1)/2);

                outLine[PT_ROW1] = viewPort[VIEWPORT_FIRSTROW];
                visited1 = true;
            }
            else if (OutCode1 & VIOLATE_RMAX) {                 // violated RMax 
                temp = (viewPort[VIEWPORT_LASTROW] - outLine[PT_ROW1]) * dc;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dr >= 0)) || ((temp < 0) && (dr < 0)))
                    outLine[PT_COL1] += ((((temp << 1)/dr)+1)/2);// perform rounding operation 
                else
                    outLine[PT_COL1] += ((((temp << 1)/dr)-1)/2);

                outLine[PT_ROW1] = viewPort[VIEWPORT_LASTROW];
                visited1 = true;
            }
            else if (OutCode1 & VIOLATE_CMIN) { // violated CMin 
                temp = (viewPort[VIEWPORT_FIRSTCOL] - outLine[PT_COL1]) * dr;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dc >= 0)) || ((temp < 0) && (dc < 0)))
                    outLine[PT_ROW1] += ((((temp << 1)/dc)+1)/2); // perform rounding operation 
                else
                    outLine[PT_ROW1] += ((((temp << 1)/dc)-1)/2);

                outLine[PT_COL1] = viewPort[VIEWPORT_FIRSTCOL];
                visited1 = true;
            }
            else { // must be: if (OutCode1 & VIOLATE_CMAX)   // violated CMax 
                temp = (viewPort[VIEWPORT_LASTCOL] - outLine[PT_COL1])*dr;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dc >= 0)) || ((temp < 0) && (dc < 0)))
                    outLine[PT_ROW1] += ((((temp << 1)/dc)+1)/2);// perform rounding operation 
                else
                    outLine[PT_ROW1] += ((((temp << 1)/dc)-1)/2);

                outLine[PT_COL1] = viewPort[VIEWPORT_LASTCOL];
                visited1 = true;
            }
            //===^^ Part-1 ^^======
        } 
        else {
            // Clip B 
            //===vv Part-2 vv======
            if (visited2) {
                outLine[PT_ROW2] = ToIntCoordinate<VT>(inLine[PT_ROW2]);
                outLine[PT_COL2] = ToIntCoordinate<VT>(inLine[PT_COL2]);
            }

            dr = outLine[PT_ROW2] - outLine[PT_ROW1];
            dc = outLine[PT_COL2] - outLine[PT_COL1];
            if ((dr > INT30_VAL || dr < -INT30_VAL) ||
                (dc > INT30_VAL || dc < -INT30_VAL) ){
                done = true;
                isInBound = false;
                visited2 = true;
            }
            else if (OutCode2 & VIOLATE_RMIN) {
                temp = (viewPort[VIEWPORT_FIRSTROW] - outLine[PT_ROW2]) * dc;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dr >= 0)) || ((temp < 0) && (dr < 0)))
                    outLine[PT_COL2] += ((((temp << 1)/dr)+1)/2);
                else
                    outLine[PT_COL2] += ((((temp << 1)/dr)-1)/2); // perform rounding operation 

                outLine[PT_ROW2] = viewPort[VIEWPORT_FIRSTROW];
                visited2 = true;
            }
            else if (OutCode2 & VIOLATE_RMAX) {
                temp = (viewPort[VIEWPORT_LASTROW] - outLine[PT_ROW2]) * dc;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dr >= 0)) || ((temp < 0) && (dr < 0)))
                    outLine[PT_COL2] += ((((temp << 1)/dr)+1)/2);
                else
                    outLine[PT_COL2] += ((((temp << 1)/dr)-1)/2);// perform rounding operation 

                outLine[PT_ROW2] = viewPort[VIEWPORT_LASTROW];
                visited2 = true;
            }
            else if (OutCode2 & VIOLATE_CMIN) {
                temp = (viewPort[VIEWPORT_FIRSTCOL] - outLine[PT_COL2]) * dr;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dc >= 0)) || ((temp < 0) && (dc < 0)))
                    outLine[PT_ROW2] += ((((temp << 1)/dc)+1)/2);
                else
                    outLine[PT_ROW2] += ((((temp << 1)/dc)-1)/2); // perform rounding operation 

                outLine[PT_COL2] = viewPort[VIEWPORT_FIRSTCOL];
                visited2 = true; 
            }
            else { // must be: if (OutCode2 & VIOLATE_CMAX) 
                temp = (viewPort[VIEWPORT_LASTCOL] - outLine[PT_COL2]) * dr;
                if (temp > INT30_VAL || temp < -INT30_VAL) {
                    done = true;
                    isInBound = false;
                }
                else if (((temp >= 0) && (dc >= 0)) || ((temp < 0) && (dc < 0)))
                    outLine[PT_ROW2] += ((((temp << 1)/dc)+1)/2);
                else
                    outLine[PT_ROW2] += ((((temp << 1)/dc)-1)/2); // perform rounding operation 

                outLine[PT_COL2] = viewPort[VIEWPORT_LASTCOL];
                visited2 = true; 
            }
            //===^^ Part-2 ^^======
        }
    }//endWhile
    return(isInBound);
}
//=============================================================================


//=============================================================================
//-----------------------------------------------------------------------------
// List of arguments. They must be consistent with the class members and 
// s-functions.
//-----------------------------------------------------------------------------

#define DRAW_COMM_ARG1_LIST \
        DT* image, \
        DT* imageG, \
        DT* imageB, \
        int32_T numRow, \
        int32_T numCol, \
        int32_T numColor, \
        DT* fillColor, \
        int32_T numFillColor, \
        PT* size, \
        int32_T numShape, \
        int32_T numSubShape, \
        int32_T *lineWidthPtr, \
        boolean_T isLine, \
        boolean_T isNonFilledPolygon, \
        boolean_T isAntiAlias, \
        OpDT* opacity, \
        int32_T numOpacity, \
        uint8_T* pixCount, \
        DT* fillColorSrc, \
        OpDT* opacitySrc


#define DRAW_COMM_VALUE_LIST \
        image, \
        imageG, \
        imageB, \
        numRow, \
        numCol, \
        numColor, \
        fillColor, \
        numFillColor, \
        size, \
        numShape, \
        numSubShape, \
        lineWidthPtr, \
        isLine, \
        isNonFilledPolygon, \
        isAntiAlias, \
        opacity, \
        numOpacity, \
        pixCount, \
        fillColorSrc, \
        opacitySrc

//=============================================================================


//=============================================================================
// Interface class
//-----------------------------------------------------------------------------
class DrawBase
{
public:
    // Main process procedure
    virtual void ProcessStep() = 0;

    // Clean up
    virtual void CleanUp() = 0;

    virtual ~DrawBase() {};

    // Update parameters
    // Override if necessary
    virtual void UpdateImageBoundary(int32_T , int32_T ) {};
    virtual void UpdateViewPort(int32_T* ) {};
    virtual void UpdateNumFillColor(int32_T ) {};
    virtual void UpdateNumOpacity(int32_T ) {};
    virtual void UpdateNumShape(int32_T ) {};
    virtual void UpdateNumSubShape(int32_T ) {};
    virtual void UpdateFillColor(void* ) {};
    virtual void UpdateFillColorSrc(void* ) {};
    virtual void UpdateOpacity(void* ) {};
    virtual void UpdateOpacitySrc(void* ) {};
    virtual void UpdateLineWidthSrc(int32_T* ) {};	
    virtual void UpdateSize(void* ) {};
    virtual void UpdateFillColorOpacity(boolean_T isConvertFillColorOnly=false) = 0;
};
//=============================================================================


//=============================================================================
// DrawCommon class holds the data and utility functions that are used in all 
// shapes.
//-----------------------------------------------------------------------------
// DT and BT: Datatype and bucket type for image
// PT: Datatype for shape (line, rectangle, polygon, circle, or markers)
// VT: Coordinate used for computation
//-----------------------------------------------------------------------------
// Formulae for output pixel value calculation:
// Non-anti-aliasing mode:
//    - Shape is not filled:
//      output = fillColor
//
//    - Shape is filled:
//      output = input * (1 - opacity) + fillColor * opacity
//             = input * oneMinusOpacity + fillColorAdd
//      where fillColorAdd = opacity * fillColor,
//            oneMinusOpacity = 1 - opacity
//      Note: fillColorAdd and oneMinusOpacity were computed outside the class 
//            and was passed in under the names of "fillColor" and "opacity".
//
// Anti-aliasing mode:
//      output = (fillColor - input) * opacity * count / max_count + input
//      where opacity is 1 when the shape is not filled,
//      count is the number of sub-pixels in the shape and max_count is the
//      number of sub-pixels in a pixel.
//
//-----------------------------------------------------------------------------

template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_INT>
class DrawCommon : public DrawBase
{
public:
    DrawCommon(DRAW_COMM_ARG1_LIST)
      : mImage(image),
        mImageG(imageG),
        mImageB(imageB),
        mNumColor(numColor),
        mNumRow(numRow),
        mNumCol(numCol),
        mNumPixInOnePlane(numRow*numCol),
        mFillColor(fillColor),
        mNumFillColor(numFillColor),
        mSize(size),
        mNumShape(numShape),
        mNumSubShape(numSubShape),
        mLineWidthPtr(lineWidthPtr),
        mIsLine(isLine), 
        mIsNonFilledPolygon(isNonFilledPolygon), 
        mIsAntiAlias(isAntiAlias),
        mOpacity(opacity),
        mNumOpacity(numOpacity),
        mPixCount(pixCount),
        mFillColorSrc(fillColorSrc),
        mOpacitySrc(opacitySrc)
    {
        InitializeViewPort(numRow, numCol);
        UpdateViewPortSub();
    };

    virtual ~DrawCommon() 
	{
		//Memory allocated using mxMalloc and mxCalloc gets deallocated by MATLAB
		//CleanUp();  
	}

    virtual void CleanUp()
    {
	    delete[] mFillColor; mFillColor = NULL;
		delete[] mOpacity; mOpacity = NULL;
		delete[] mLineWidthPtr; mLineWidthPtr = NULL;
		delete[] mPixCount;
    }

    virtual void UpdateImageBoundary(int32_T numRow, int32_T numCol) 
    { 
        InitializeViewPort(numRow, numCol);
        UpdateViewPortSub();
        mNumRow = numRow;
        mNumCol = numCol;
        mNumPixInOnePlane = numRow * numCol;
    }

    virtual void UpdateViewPort(int32_T* bbox) 
    { 
        InitializeViewPort(mNumRow, mNumCol);
        FindVisibleArea(bbox, mViewPort);
        UpdateViewPortSub();
    }

    virtual void UpdateNumFillColor(int32_T numFillColor)
    {
        mNumFillColor = numFillColor;
    }

    virtual void UpdateNumShape(int32_T numShape)
    {
        mNumShape = numShape;
    }

    virtual void UpdateNumSubShape(int32_T numSubShape)
    {
        mNumSubShape = numSubShape;
    }

    virtual void UpdateNumOpacity(int32_T numOpacity)
    {
        mNumOpacity = numOpacity;
    }

    virtual void UpdateSize(void* ptr)
    {
        mSize = (PT*)ptr;
      
    }

    virtual void UpdateLineWidthSrc(int32_T* ptr)
    {
        mLineWidthPtr = (int32_T*)ptr;
    }

    virtual void UpdateFillColorOpacity(boolean_T isConvertFillColorOnly=false)
    {
        int_T idx, idxColor, idxFillColor = 0, idxOpacity = 0;
        int_T idxFillColorStart = GetClrIdx(0);
		OpDT tempVar1(0);
		DT tempVar2(0);

        // mFillColor = mFillColorSrc * mOpacitySrc
        for(idx=0; idx<mNumFillColor; idx++) {
            int_T idxFillColorAdd = GetClrIdx(idx);
            idxFillColor = idxFillColorStart;
            for(idxColor=0; idxColor<mNumColor; idxColor++) {
                mFillColor[idxFillColorAdd]  = mFillColorSrc[idxFillColor];

                // mFillColor[idxFillColorAdd] *= mOpacitySrc[idxOpacity];
				tempVar1 = mOpacitySrc[idxOpacity];
				tempVar1 *= mFillColor[idxFillColorAdd];
                //mFillColor[idxFillColorAdd] = tempVar1;
                cast(mFillColor, idxFillColorAdd, &tempVar1);

                idxFillColor    = GetNextSubClrIdx(idxFillColor);
                idxFillColorAdd = GetNextSubClrIdx(idxFillColorAdd);
            }
            idxOpacity ++;

            if(IsMoreClr(idxFillColorStart)) {
                idxFillColorStart = GetNextClrIdx(idxFillColorStart);
            }
            else {
                idxFillColorStart = GetClrIdx(0);
            }

            if(idxOpacity >= mNumOpacity) {
                idxOpacity = 0;
            }
        }

        tempVar2 = 1;
        if(!isConvertFillColorOnly) {
            // mOpacity = 1 - mOpacity
            for(idxOpacity=0; idxOpacity<mNumOpacity; idxOpacity++) {
				tempVar1 = tempVar2;
				tempVar1 -= mOpacitySrc[idxOpacity];
                mOpacity[idxOpacity] = tempVar1;
            }
        }
    }

    // Utility functions used to update the fill color and opacity indices
protected:
    inline void ResetFillColorOpacityIndices()
    {       
        mIdxFillColor = 0;
        mIdxOpacity = 0;
    }

    inline void MoveToNextFillColor()
    {
        if(IsMoreClr(mIdxFillColor)) {
            mIdxFillColor = GetNextClrIdx(mIdxFillColor);
        }
        else {
            mIdxFillColor = GetClrIdx(0);
        }
    }

    inline void MoveToNextOpacity()
    {
        MoveToNextOpacity((MODE_INT)0);
    }

protected:
    inline void PlotOnePixel(int_T idxFillColorStart, VT idxPix)
    {
        this->PlotOnePixel(idxFillColorStart, idxPix, (MODE_PORT)0);
    }

    inline void PlotPixelsCheckRange(int_T idxFillColorStart, VT col, VT row)
    {
        if(    col>=mViewPort[VIEWPORT_FIRSTCOL] 
            && col<=mViewPort[VIEWPORT_LASTCOL] 
            && row>=mViewPort[VIEWPORT_FIRSTROW] 
            && row<=mViewPort[VIEWPORT_LASTROW]) {
                VT idxPix = col * mNumRow + row;
                this->PlotOnePixel(idxFillColorStart, idxPix);
        }
    }

protected:
    inline void PlotSubPixels(int_T col, int_T firstRow, int_T lastRow, 
        int_T idxFillColorStart, int_T idxOpacity=0)
    {
        this->PlotSubPixels(col, firstRow, lastRow, idxFillColorStart, idxOpacity, (MODE_PORT)0);
    }

    inline void PlotSubPixels(int_T idxPix, uint8_T subPixCount, 
        int_T idxFillColorStart, int_T idxOpacity=0)
    {
        this->PlotSubPixels(idxPix, subPixCount, idxFillColorStart, idxOpacity, (MODE_PORT)0);
    }

protected:
    inline void PlotVerticalLine(int_T idxOpacity, int_T idxFillColorStart, 
        VT col, VT firstRow, VT lastRow)
    {
        this->PlotVerticalLine(idxOpacity, idxFillColorStart, col, firstRow, lastRow, (MODE_PORT)0);
    }

    inline void PlotVerticalLineCheckRange(int_T idxOpacity, int_T idxFillColorStart, 
        VT col, VT firstRow, VT lastRow)
    {
        if(col>=mViewPort[VIEWPORT_FIRSTCOL] && col<=mViewPort[VIEWPORT_LASTCOL]) {
            VT firstValidRow = Max(firstRow, mViewPort[VIEWPORT_FIRSTROW]);
            VT lastValidRow  = Min(lastRow, mViewPort[VIEWPORT_LASTROW]);
            if(firstValidRow <= lastValidRow) {
                this->PlotVerticalLine(idxOpacity, idxFillColorStart, col, firstValidRow, lastValidRow);
            }
        }
    }

protected:
    inline void CountSubPixel(int_T min, int_T max, int_T first, int_T last, 
        int_T& firstOut, int_T& lastOut, int subpix_bit = SUBPIX_BIT, int subpix_len = SUBPIX_LEN)
    {
        int_T firstDown, lastDown, row;

        if(last > min && first < max) { // Make sure there are some valid sub-pixels
           if(first < min) first = min;
           if(last > max)  last = max;

           firstDown = first >> subpix_bit;
           lastDown = last >> subpix_bit;
           if(firstOut > firstDown) firstOut = firstDown;
           if(lastOut < lastDown)   lastOut = lastDown;
           if(lastDown > firstDown) {
               mPixCount[firstDown] += (uint8_T)(((firstDown + 1) << subpix_bit) - first);
               mPixCount[lastDown]  += (uint8_T)(last - (lastDown << subpix_bit) + 1);
               for(row=firstDown+1; row<lastDown; row++) {
                   mPixCount[row] += (uint8_T)subpix_len;
               }
           }
           else if(lastDown == firstDown){
               mPixCount[firstDown] += (uint8_T)(last - first + 1);
           }
        }
    }

    template<class T1, class T2>
    inline void FindVisibleAreaKeepCoordinate(const T1* rect, T2* view)
    {
        view[VIEWPORT_FIRSTROW] 
            = Max((T2)mViewPort[VIEWPORT_FIRSTROW], 
                  ToIntCoordinate<T2>(rect[BBOX_ROW]));
        
        view[VIEWPORT_FIRSTCOL]
            = Max((T2)mViewPort[VIEWPORT_FIRSTCOL], 
                  ToIntCoordinate<T2>(rect[BBOX_COL]));
        
        view[VIEWPORT_LASTROW]
            = Min((T2)(mViewPort[VIEWPORT_LASTROW]), 
                  ToIntCoordinate<T2>(rect[BBOX_ROW]+rect[BBOX_NUMROW]-1));
        
        view[VIEWPORT_LASTCOL]
            = Min((T2)(mViewPort[VIEWPORT_LASTCOL]), 
                  ToIntCoordinate<T2>(rect[BBOX_COL]+rect[BBOX_NUMCOL]-1));
    }

    template<class T1, class T2>
    inline void FindVisibleArea(const T1* rect, T2* view)
    {
        // Convert the XYWH rect to RCHW 0-based spec used by the rest of the code
        view[VIEWPORT_FIRSTROW] 
            = Max((T2)mViewPort[VIEWPORT_FIRSTROW], 
                  ToIntCoordinate<T2>(rect[1])-1);
        
        view[VIEWPORT_FIRSTCOL]
            = Max((T2)mViewPort[VIEWPORT_FIRSTCOL], 
                  ToIntCoordinate<T2>(rect[0])-1);
        
        view[VIEWPORT_LASTROW]
            = Min((T2)(mViewPort[VIEWPORT_LASTROW]), 
                  ToIntCoordinate<T2>(rect[1]+rect[3]-2));
        
        view[VIEWPORT_LASTCOL]
            = Min((T2)(mViewPort[VIEWPORT_LASTCOL]), 
                  ToIntCoordinate<T2>(rect[0]+rect[2]-2));
    }

// Implementation of the opacity index updating functions
private:
    inline void MoveToNextOpacity(MODE_INT_EMPTY)
    {
        // Do nothing
    }

    inline void MoveToNextOpacity(MODE_INT_FILLED)
    {
        mIdxOpacity ++;
        if(mIdxOpacity >= mNumOpacity) {
            mIdxOpacity = 0;
        }
    }

private:
    inline void PlotOnePixel(int_T idxFillColorStart, VT idxPixStart, MODE_PORT_ONE)
    {
        int_T idxFillColor = idxFillColorStart;
        VT idxPix = idxPixStart;
        for(int_T idxColor=0; idxColor<mNumColor; idxColor++) {
            mImage[idxPix] = mFillColor[idxFillColor];
            idxPix += mNumPixInOnePlane;
            idxFillColor = GetNextSubClrIdx(idxFillColor);
        }
    }

    inline void PlotOnePixel(int_T idxFillColor, VT idxPix, MODE_PORT_RGB)
    {
        mImage[idxPix]  = mFillColor[idxFillColor];
        idxFillColor = GetNextSubClrIdx(idxFillColor);
        mImageG[idxPix] = mFillColor[idxFillColor];
        idxFillColor = GetNextSubClrIdx(idxFillColor);
        mImageB[idxPix] = mFillColor[idxFillColor];
    }

private:
    inline void PlotVerticalLine(int_T idxOpacity, int_T idxFillColorStart, 
        VT col, VT firstRow, VT lastRow, MODE_PORT_ONE)
    {
        int_T idxFillColor = idxFillColorStart;
        VT idxPixStart = col * mNumRow + firstRow;
        for(int_T idxColor=0; idxColor<mNumColor; idxColor++) {

            PlotVerticalLineOneColor(mImage, idxOpacity, idxFillColor, 
                idxPixStart, firstRow, lastRow);

            idxPixStart += mNumPixInOnePlane;
            idxFillColor = GetNextSubClrIdx(idxFillColor);
        }
    }

    inline void PlotVerticalLine(int_T idxOpacity, int_T idxFillColor, 
        VT col, VT firstRow, VT lastRow, MODE_PORT_RGB)
    {
        VT idxPixStart = col * mNumRow + firstRow;

        PlotVerticalLineOneColor(mImage,  idxOpacity, idxFillColor,   
            idxPixStart, firstRow, lastRow);

        idxFillColor = GetNextSubClrIdx(idxFillColor);
        PlotVerticalLineOneColor(mImageG, idxOpacity, idxFillColor, 
            idxPixStart, firstRow, lastRow);

        idxFillColor = GetNextSubClrIdx(idxFillColor);
        PlotVerticalLineOneColor(mImageB, idxOpacity, idxFillColor, 
            idxPixStart, firstRow, lastRow);
    }

    inline void PlotVerticalLineOneColor(DT* image, int_T idxOpacity, int_T idxFillColor, 
        VT idxPixStart, VT firstRow, VT lastRow)
    {
        int lineWidthV = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];
        bool isPureFill = true;
        if (this->mIsLine && (lineWidthV>1)){
            isPureFill = false;
        }
        else if (this->mIsNonFilledPolygon && (lineWidthV>1)){
            isPureFill = false;
        }

        VT idxPix = idxPixStart;
        for(VT i=firstRow; i<=lastRow; i++) {
            if (isPureFill) {
                multiplyEqual(image, idxPix, mOpacity, idxOpacity);	//image[idxPix] *= mOpacity[idxOpacity];
                image[idxPix] += mFillColor[idxFillColor];
            }			
            else{
                image[idxPix] = mFillColor[idxFillColor];
            }    
            idxPix ++;
        }
    }

private:
    inline void PlotSubPixels(int_T col, int_T firstRow, int_T lastRow, 
        int_T idxFillColorStart, int_T idxOpacity, MODE_PORT_ONE) 
    {
        int_T idxFillColor, idxColor, idxPixStart;

        idxFillColor = idxFillColorStart;
        idxPixStart = col * mNumRow + firstRow;
        for(idxColor=0; idxColor<mNumColor; idxColor++) {

            PlotSubPixelsOneColor(mImage, idxPixStart, firstRow, lastRow, 
                idxFillColor, idxOpacity);

            idxPixStart += mNumPixInOnePlane;
            idxFillColor = GetNextSubClrIdx(idxFillColor);
        }
    }

    inline void PlotSubPixels(int_T col, int_T firstRow, int_T lastRow, 
        int_T idxFillColorStart, int_T idxOpacity, MODE_PORT_RGB)
    {
        VT idxPixStart = col * mNumRow + firstRow;

        PlotSubPixelsOneColor(mImage,  idxPixStart, firstRow, lastRow, 
            idxFillColorStart, idxOpacity);

        idxFillColorStart = GetNextSubClrIdx(idxFillColorStart);
        PlotSubPixelsOneColor(mImageG, idxPixStart, firstRow, lastRow,
            idxFillColorStart, idxOpacity);

        idxFillColorStart = GetNextSubClrIdx(idxFillColorStart);
        PlotSubPixelsOneColor(mImageB, idxPixStart, firstRow, lastRow,
            idxFillColorStart, idxOpacity);
    }

    inline void PlotSubPixelsOneColor(DT* image, int_T idxPixStart, 
        int_T firstRow, int_T lastRow, int_T idxFillColor, int_T idxOpacity) 
    {
        VT idxPix = idxPixStart;
        for(VT row=firstRow; row<=lastRow; row++) {
            PlotOneSubPixelOneColor(image, idxPix, 
                mPixCount[row], idxFillColor, idxOpacity);
            idxPix ++;
        }
    }

    inline void PlotSubPixels(int_T idxPix, uint8_T subPixCount, int_T idxFillColorStart, 
        int_T idxOpacity, MODE_PORT_ONE) 
    {
        int_T idxFillColor, idxColor;

        idxFillColor = idxFillColorStart;
        for(idxColor=0; idxColor<mNumColor; idxColor++) {
            PlotOneSubPixelOneColor(mImage, idxPix, subPixCount, idxFillColor, idxOpacity);
            idxPix += mNumPixInOnePlane;
            idxFillColor = GetNextSubClrIdx(idxFillColor);
        }
    }

    inline void PlotSubPixels(int_T idxPix, uint8_T subPixCount, 
        int_T idxFillColorStart, int_T idxOpacity, MODE_PORT_RGB)
    {
        PlotOneSubPixelOneColor(mImage,  idxPix, subPixCount, 
            idxFillColorStart,   idxOpacity);

        idxFillColorStart = GetNextSubClrIdx(idxFillColorStart);
        PlotOneSubPixelOneColor(mImageG, idxPix, subPixCount, 
            idxFillColorStart, idxOpacity);

        idxFillColorStart = GetNextSubClrIdx(idxFillColorStart);
        PlotOneSubPixelOneColor(mImageB, idxPix, subPixCount, 
            idxFillColorStart, idxOpacity);
    }

    inline void PlotOneSubPixelOneColor(DT* image, int_T idxPix, uint8_T subPixCount,
        int_T idxFillColor, int_T idxOpacity) 
    {
		// called from DrawFilledPolygon, DrawFilledCircle
        int lineWidthV = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];
		OpDT tempVar1(0);
		DT tempVar2(0);

        bool isPureFill = true;
        if (this->mIsLine && (lineWidthV>1)){
            isPureFill = false;
        }
        else if (this->mIsNonFilledPolygon && (lineWidthV>1)){
            isPureFill = false;
        }

        if(subPixCount == SUBPIX_SIZE) {
            // Formula:
            // ImgOut = (FillColor - ImgIn) * Opacity + ImgIn
			tempVar1 = mFillColor[idxFillColor];
			tempVar1 -= image[idxPix];
            if (isPureFill)
                ApplyOpacity(&tempVar1, 0, idxOpacity, (MODE_INT)0);
			tempVar1 += image[idxPix];
            //image[idxPix]  = (DT)tempVar1;
            cast(image, idxPix, &tempVar1);
        }
        else {
            // Formula:
            // ImgOut = (FillColor - ImgIn) * Opacity * Count / SUBPIX_SIZE + ImgIn
			tempVar1 = mFillColor[idxFillColor];
			tempVar1 -= image[idxPix];
            if (isPureFill)
                ApplyOpacity(&tempVar1, 0, idxOpacity, (MODE_INT)0);//AA CIRCLE needs it, NonAA circle must skip it
                                                                  //AA Line   must skip it it, NonAA line  must skip it > because not pure FilledPolygon
            tempVar2  = (BT)subPixCount;
			tempVar1 *= tempVar2;
            if (this->mIsAntiAlias)          // if (isAntiAliasMode)
                DownScale(tempVar1);//AA CIRCLE needs it, NonAA circle must skip it
                                      //AA Line   needs it, NonAA line  must skip it 
            // true as it is in alias mode
			tempVar1 += image[idxPix];
            //image[idxPix]  = (DT)tempVar1;
            cast(image, idxPix, &tempVar1);
        }
    }

private:
 inline void ApplyOpacity(OpDT*, VT, VT, MODE_INT_EMPTY)
    {
        // Do nothing.
    }
    inline void ApplyOpacity(OpDT* image, VT idxImage, VT idxOpacity, MODE_INT_FILLED)
    {
        image[idxImage] *= mOpacity[idxOpacity];
    }

private: 
    inline void DownScale(real_T& val)   { val /= SUBPIX_SIZE; };
    inline void DownScale(real32_T& val) { val /= SUBPIX_SIZE; };
   
    template<class T>
    inline T Min(T a, T b) { return(a<=b? a: b); }

    template<class T>
    inline T Max(T a, T b) { return(a>=b? a: b); }

    template<class T1, class T2, class T3>
    inline void ClipRectangles(const T1* viewport, const T2* rect2, T3* outRect)
    {
        T3 bboxEnd;

        outRect[BBOX_ROW] = Max((T3)viewport[VIEWPORT_FIRSTROW], 
            ToIntCoordinate<T3>(rect2[BBOX_ROW]));

        outRect[BBOX_COL] = Max((T3)viewport[VIEWPORT_FIRSTCOL], 
            ToIntCoordinate<T3>(rect2[BBOX_COL]));

        bboxEnd = Min((T3)(viewport[VIEWPORT_LASTROW])+1, 
            ToIntCoordinate<T3>(rect2[BBOX_ROW]+rect2[BBOX_NUMROW]));

        outRect[BBOX_NUMROW] = bboxEnd - outRect[BBOX_ROW];

        bboxEnd = Min((T3)(viewport[VIEWPORT_LASTCOL])+1, 
            ToIntCoordinate<T3>(rect2[BBOX_COL]+rect2[BBOX_NUMCOL]));

        outRect[BBOX_NUMCOL] = bboxEnd - outRect[BBOX_COL];
    }

    template<class T>
    inline void BBoxToViewPort(T* rect)
    {
        rect[VIEWPORT_LASTROW] = rect[BBOX_ROW] + rect[BBOX_NUMROW] - 1;
        rect[VIEWPORT_LASTCOL] = rect[BBOX_COL] + rect[BBOX_NUMCOL] - 1;
    }

private:
    inline void InitializeViewPort(int32_T numRow, int32_T numCol)
    {
        mViewPort[VIEWPORT_FIRSTROW] = 0;
        mViewPort[VIEWPORT_FIRSTCOL] = 0;
        mViewPort[VIEWPORT_LASTROW]  = numRow - 1;
        mViewPort[VIEWPORT_LASTCOL]  = numCol - 1;
    }

    inline void UpdateViewPortSub()
    {
        mViewPortSub[VIEWPORT_FIRSTROW] 
            = (mViewPort[VIEWPORT_FIRSTROW] << SUBPIX_BIT);

        mViewPortSub[VIEWPORT_FIRSTCOL]
            = (mViewPort[VIEWPORT_FIRSTCOL] << SUBPIX_BIT);

        mViewPortSub[VIEWPORT_LASTROW]
            = ((mViewPort[VIEWPORT_LASTROW] + 1) << SUBPIX_BIT) - 1;

        mViewPortSub[VIEWPORT_LASTCOL]
            = ((mViewPort[VIEWPORT_LASTCOL] + 1) << SUBPIX_BIT) - 1;
    }

    inline int_T GetClrIdx(int_T idx);
    inline int_T GetNextClrIdx(int_T idx);
    inline int_T GetNextSubClrIdx(int_T idx);
    inline int_T IsMoreClr(int_T idx);

protected:
    DT* mImage;

    // Green and blue chanels are used only in RGB mode
    DT* mImageG;
    DT* mImageB;

    // Other information
    const int32_T mNumColor;
    int32_T mNumRow;
    int32_T mNumCol;
    int32_T mNumPixInOnePlane;

    // FillColor equals to the user-input value when the shape is not filled;
    // and equals to the user-input value times (user input) opacity otherwise.
    DT* mFillColor;
    int32_T mNumFillColor;

    PT* mSize;

    // Basic shape information
    int32_T mNumShape;
    int32_T mNumSubShape;
    int32_T *mLineWidthPtr;
    boolean_T mIsLine;
    boolean_T mIsNonFilledPolygon;
    boolean_T mIsAntiAlias;
    // Opacity equals to the user-input value when the shape is not filled;
    // and equals to one minus user-input value otherwise.
    OpDT* mOpacity;
    int32_T mNumOpacity;

    // Length of mSubPixCount equals to the larger value of row number
    // and column number.
    uint8_T* const mPixCount; 

    DT* mFillColorSrc;
    OpDT* mOpacitySrc;

    int_T mIdxFillColor;
    int_T mIdxOpacity;

    // Visible area
    int32_T mViewPort[VIEWPORT_LEN];

    // Visible area - used only for MODE_ALG_ANTIALIAS
    int32_T mViewPortSub[VIEWPORT_LEN];

};

template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_INT>
inline int_T DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT>::GetClrIdx(int_T idx)
{
    return idx;
}

template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_INT>
inline int_T DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT>::GetNextClrIdx(int_T idx)
{
    return(idx + 1);
}

template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_INT>
inline int_T DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT>::GetNextSubClrIdx(int_T idx)
{
    return(idx + mNumFillColor);
}

template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_INT>
inline int_T DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT>::IsMoreClr(int_T idx)
{
    return(idx < mNumColor * (mNumFillColor - 1));
}

//=============================================================================

////////////////////////////////////////////////////////////////////////////////
// Helper for handling points and coordinate system choice
////////////////////////////////////////////////////////////////////////////////
template<class PT, class VT>
void getPoint(PT *ptBuf, int_T idxROI, 
              int32_T numShapes, VT &row, VT &col)
{
    // Convert from 1-based X,Y to 0-based R,C
    row = ToIntCoordinate<VT>(ptBuf[numShapes + idxROI])-1;
    col = ToIntCoordinate<VT>(ptBuf[idxROI])-1;
}

//=============================================================================
// DrawFilledRectangle class draws a filled rectangle 
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT>
class DrawFilledRectangle : public DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT_FILLED>
{
public:
    DrawFilledRectangle(
        DRAW_COMM_ARG1_LIST)
      : DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT_FILLED>(DRAW_COMM_VALUE_LIST)
    {
    }

    void ProcessOneShape()
    {
        int32_T viewport[VIEWPORT_LEN];
        this->FindVisibleAreaKeepCoordinate(mRect, viewport);

        if(viewport[VIEWPORT_FIRSTROW]<=viewport[VIEWPORT_LASTROW]
            && viewport[VIEWPORT_FIRSTCOL]<= viewport[VIEWPORT_LASTCOL]) {

            for(VT col=viewport[VIEWPORT_FIRSTCOL]; col<=viewport[VIEWPORT_LASTCOL]; col++) {
                this->PlotVerticalLine(this->mIdxOpacity, this->mIdxFillColor, col, 
                    viewport[VIEWPORT_FIRSTROW], viewport[VIEWPORT_LASTROW]);
            }
        }
    }

protected:
    VT mRect[BBOX_LEN];
}; // End of DrawFilledRectangle
//=============================================================================

//=============================================================================
// DrawFilledRectangleAnySize class draws a set of filled rectangles of
// arbitrary size.
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT>
class DrawFilledRectangleAnySize : public DrawFilledRectangle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT>
{
public:
    DrawFilledRectangleAnySize(
        DRAW_COMM_ARG1_LIST,
        const PT* rects)
      : DrawFilledRectangle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT>(DRAW_COMM_VALUE_LIST),
        mRectAll(rects)
    {
    }

    virtual ~DrawFilledRectangleAnySize() {}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++) {
            this->mRect[BBOX_ROW]    = ToIntCoordinate<VT>(mRectAll[idxROI+BBOX_COL*this->mNumShape]) - 1;
            this->mRect[BBOX_COL]    = ToIntCoordinate<VT>(mRectAll[idxROI+BBOX_ROW*this->mNumShape]) - 1;
            this->mRect[BBOX_NUMROW] = ToIntCoordinate<VT>(mRectAll[idxROI+BBOX_NUMCOL*this->mNumShape]);
            this->mRect[BBOX_NUMCOL] = ToIntCoordinate<VT>(mRectAll[idxROI+BBOX_NUMROW*this->mNumShape]);
            
            this->ProcessOneShape();
            
            this->MoveToNextFillColor();
            this->MoveToNextOpacity();
        }
    }

private:
    const PT* const mRectAll;
}; // End of DrawFilledRectangleAnySize
//=============================================================================

//=============================================================================
// DrawFilledSquareFixedSize class draws a set of filled squares of the same
// size.
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT>
class DrawFilledSquareFixedSize : public DrawFilledRectangle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT>
{
public:
    DrawFilledSquareFixedSize(
        DRAW_COMM_ARG1_LIST,
        PT* pts)
      : DrawFilledRectangle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT>(DRAW_COMM_VALUE_LIST),
        mPtsAll(pts)
    {
    }

    virtual ~DrawFilledSquareFixedSize() {}

    virtual void ProcessStep()
    {
        VT size = ToIntCoordinate<VT>(this->mSize[0]);
        this->ResetFillColorOpacityIndices();
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++) 
        {
            VT row, col;
            getPoint(mPtsAll, idxROI, this->mNumShape, row, col);


            this->mRect[BBOX_ROW]    = row - size;
            this->mRect[BBOX_COL]    = col - size;


            this->mRect[BBOX_NUMROW] = 2 * size + 1;
            this->mRect[BBOX_NUMCOL] = this->mRect[BBOX_NUMROW];

            this->ProcessOneShape();

            this->MoveToNextFillColor();
            this->MoveToNextOpacity();
        }
    }

private:
    const PT* const mPtsAll;
}; // End of DrawFilledSquareFixedSize
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawFilledPolygon : public DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT_FILLED>
{
public:
    DrawFilledPolygon(
        DRAW_COMM_ARG1_LIST,
        ScanLineBase<VT,PT,MODE_ALG>* scanline,
        PT* pts,
        PT* ptsDW)
      : DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT_FILLED>(DRAW_COMM_VALUE_LIST),
        mScanLine(scanline),
        mPts(pts),
        mPtsDW(ptsDW)
    {
    }

    virtual ~DrawFilledPolygon()
    {
        delete(mScanLine);
        mScanLine = NULL;
    }

    virtual void ProcessStep()
    {
        ProcessStep(MODE_ALG(0));
    }

protected:
    ScanLineBase<VT,PT,MODE_ALG>* mScanLine;

private:
    const PT* const mPts;
    PT* mPtsDW;

#include "cvstThickLinePolygonVertices_sim.hpp"

private:
    void ProcessStep(MODE_ALG_DIRECT) // for DrawFilledPolygon 
    {
        boolean_T isForeground;
        int_T col, firstRow, lastRow;
        int lineWidthV = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];

        if (this->mIsLine && (lineWidthV>1)){
            convertLinePts2PolygonPts();
        }
        else if (this->mIsNonFilledPolygon && (lineWidthV>1)){
            converPolygonPts2TwoPolygonPts();
        }

        mScanLine->Reset();

        mScanLine->UpdateViewPort(
            this->mViewPort[VIEWPORT_FIRSTROW], this->mViewPort[VIEWPORT_FIRSTCOL], 
            this->mViewPort[VIEWPORT_LASTROW],  this->mViewPort[VIEWPORT_LASTCOL]);
        // "NOTE: A:" thick or non-thick line/polygon:  it is the number of points ((x,y) pair) in each row of point port
        // since to draw thick line or polygon, we need to double the number of points representing polygon points
        //   we multiply by 2 here
        int_T numShape_new = this->mNumSubShape; 
        if ((this->mIsLine || this->mIsNonFilledPolygon) && (lineWidthV>1)) numShape_new *= 2; 
        mScanLine->UpdatePolygonNumbers(this->mNumShape, numShape_new, this->mNumShape * numShape_new);

        this->ResetFillColorOpacityIndices();
        while(mScanLine->IsMoreLayer()) {
            mScanLine->IniLayer();
            while(mScanLine->IsMoreForeScanLine()) {
                mScanLine->GetScanLine(isForeground, col, firstRow, lastRow);
                if(isForeground) {
                    this->PlotVerticalLine(this->mIdxOpacity, this->mIdxFillColor, col, firstRow, lastRow);
                }
            }

            this->MoveToNextFillColor();
            this->MoveToNextOpacity();

            mScanLine->NextLayer();
        }
    }

    void ProcessStep(MODE_ALG_ANTIALIAS)
    {
        boolean_T isForeground, isContinue;
        int_T row, col, firstRow, lastRow, colOut, colBoundary;
        int_T firstRowOut, lastRowOut;
         
        int lineWidthV = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];

        if (this->mIsLine && (lineWidthV>1)){
            convertLinePts2PolygonPts();
        }
        else if (this->mIsNonFilledPolygon && (lineWidthV>1)){
            converPolygonPts2TwoPolygonPts();
        }
         
        for(row=0; row<this->mNumRow; row++) this->mPixCount[row] = 0;

        mScanLine->Reset();

        mScanLine->UpdateViewPort(
            this->mViewPortSub[VIEWPORT_FIRSTROW], this->mViewPortSub[VIEWPORT_FIRSTCOL], 
            this->mViewPortSub[VIEWPORT_LASTROW],  this->mViewPortSub[VIEWPORT_LASTCOL]);
        // see "NOTE: A:" above
        int_T numShape_new = this->mNumSubShape;
        if ((this->mIsLine || this->mIsNonFilledPolygon) && (lineWidthV>1)) numShape_new *= 2;
        // 
        mScanLine->UpdatePolygonNumbers(this->mNumShape, numShape_new, this->mNumShape * numShape_new);

        this->ResetFillColorOpacityIndices();
        while(mScanLine->IsMoreLayer()) {
            mScanLine->IniLayer();
            col = mScanLine->GetPolygonBdy()->GetFirstCol();
            colOut = col >> SUBPIX_BIT;
            colBoundary = ((colOut + 1) << SUBPIX_BIT) - 1;
            firstRowOut = this->mNumRow;
            lastRowOut = 0;
            isContinue = mScanLine->IsMoreForeScanLine();
            while(isContinue) {
                mScanLine->GetScanLine(isForeground, col, firstRow, lastRow);
                if(isForeground) {
                    this->CountSubPixel(
                        this->mViewPortSub[VIEWPORT_FIRSTROW],
                        this->mViewPortSub[VIEWPORT_LASTROW], 
                        firstRow, lastRow, firstRowOut, lastRowOut);
                }

                isContinue = mScanLine->IsMoreForeScanLine();

                // When the last sub-pixel column has been completely procssed,
                // draw the polygon.
                if((col == colBoundary || !isContinue)
                    && lastRow >= this->mViewPortSub[VIEWPORT_LASTROW]) {

                    this->PlotSubPixels(colOut, firstRowOut, lastRowOut,
                        this->mIdxFillColor, this->mIdxOpacity);

                    for(row=firstRowOut; row<=lastRowOut; row++) this->mPixCount[row] = 0;

                    // Step into the next column
                    colOut ++;
                    colBoundary += SUBPIX_LEN;
                    firstRowOut = this->mNumRow;
                    lastRowOut = 0;
                }
            }

            this->MoveToNextFillColor();
            this->MoveToNextOpacity();

            mScanLine->NextLayer();
        }
    }
}; // End of DrawFilledPolygon
//=============================================================================


//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT,
    class MODE_PORT, class MODE_INT, class MODE_ALG>
class DrawCircle : public DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT>
{
public:
    DrawCircle(
        DRAW_COMM_ARG1_LIST)
      : DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT>(DRAW_COMM_VALUE_LIST)
    {
    }

    void ProcessOneShape()
    {
        if(mRadius>=0 
            && mRowCtr>=this->mViewPort[VIEWPORT_FIRSTROW]-mRadius 
            && mRowCtr<=this->mViewPort[VIEWPORT_LASTROW]+mRadius
            && mColCtr>=this->mViewPort[VIEWPORT_FIRSTCOL]-mRadius
            && mColCtr<=this->mViewPort[VIEWPORT_LASTCOL]+mRadius) {

            this->ProcessOneShape(mRowCtr, mColCtr, mRadius, (MODE_INT)0, (MODE_ALG)0);
        }
    }

private: 

    void ProcessOneShape(VT rowCtr, VT colCtr, VT radius, MODE_INT_EMPTY, MODE_ALG_DIRECT)
    {
        int lineWidthV = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];
        // 'mLineWidthPtr == null' means insertMarker
        if (lineWidthV == 1) 
        {
            VT row, col, err, rowDif, colDif;

            err = 1 - radius;
            rowDif = 0;
            colDif = -2 * radius;
            row = 0;
            col = radius;

            while(row <= col || (radius==1 && row<=1)) {
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr-row, rowCtr-col);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr-row, rowCtr+col);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr+row, rowCtr-col);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr+row, rowCtr+col);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr-col, rowCtr-row);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr-col, rowCtr+row);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr+col, rowCtr-row);
                this->PlotPixelsCheckRange(this->mIdxFillColor, colCtr+col, rowCtr+row);

                if(err >= 0) {
                    col --;
                    colDif += 2;
                    err += colDif;
                }
                rowDif += 2;
                err += (rowDif + 1);

                row ++;
            }
        }
        else
        {
            ProcessOneShape(rowCtr, colCtr, radius, (MODE_INT_EMPTY)0, (MODE_ALG_ANTIALIAS)0);
        }
    }

    void ProcessOneShape(VT rowCtr, VT colCtr, VT radius, 
        MODE_INT_FILLED, MODE_ALG_DIRECT)
    {
        VT row, col, err, colNext, rowDif, colDif;

        err = 1 - radius;
        rowDif = 0;
        colDif = -2 * radius;
        row = 0;
        col = radius;

        this->PlotVerticalLineCheckRange(this->mIdxOpacity, this->mIdxFillColor, 
            colCtr, rowCtr-radius, rowCtr+radius);

        if(err >= 0) {
            col --;
            colDif += 2;
            err += colDif;
        }
        row ++;
        rowDif += 2;
        err += (rowDif + 1);
        colNext = col;

        while(row <= col || (radius==1 && row<=1)) {
            this->PlotVerticalLineCheckRange(this->mIdxOpacity, this->mIdxFillColor, 
                colCtr-row, rowCtr-col, rowCtr+col);

            this->PlotVerticalLineCheckRange(this->mIdxOpacity, this->mIdxFillColor, 
                colCtr+row, rowCtr-col, rowCtr+col);

            if(err >= 0) {
                colNext --;
                colDif += 2;
                err += colDif;
            }
            rowDif += 2;
            err += (rowDif + 1);

            if((col!=colNext && row<col) || col==row+1) {
                this->PlotVerticalLineCheckRange(this->mIdxOpacity, this->mIdxFillColor, 
                    colCtr-col, rowCtr-row, rowCtr+row);

                this->PlotVerticalLineCheckRange(this->mIdxOpacity, this->mIdxFillColor, 
                    colCtr+col, rowCtr-row, rowCtr+row);
            }

            row ++;
            col = colNext;
        }
    }

    void ProcessOneShape(VT rowCtr, VT colCtr, VT radius, 
        MODE_INT_FILLED, MODE_ALG_ANTIALIAS)
    {
        VT rowCtrSub, colCtrSub, radiusSub, colCount;
        VT firstRowOut, lastRowOut, colOut;
        VT rowExtSub;
        VT minRowSub, maxRowSub;
        boolean_T isContinue;

        // Downsampling will be done by floor(), 
        // so the pixel center is at SUBPIX_HALFLEN.
        rowCtrSub = (rowCtr << SUBPIX_BIT) + SUBPIX_HALFLEN;
        colCtrSub = (colCtr << SUBPIX_BIT) + SUBPIX_HALFLEN;
        radiusSub = radius << SUBPIX_BIT;

        minRowSub = this->mViewPort[VIEWPORT_FIRSTROW] << SUBPIX_BIT;
        maxRowSub = ((this->mViewPort[VIEWPORT_LASTROW] + 1) << SUBPIX_BIT) - 1;

        colCount = SUBPIX_HALFLEN;
        colOut = 0;
        firstRowOut = this->mNumRow;
        lastRowOut = 0;

        MidPointFullCircle<VT> extCircle;
        extCircle.Initialize(radiusSub);

        for(rowExtSub=0; rowExtSub<this->mNumRow; rowExtSub++) this->mPixCount[rowExtSub] = 0;

        isContinue = extCircle.IsInRange();
        while(isContinue) {
            colCount --;

            rowExtSub = extCircle.GetRow();

            this->CountSubPixel(minRowSub, maxRowSub, 
                rowCtrSub-rowExtSub-1, rowCtrSub+rowExtSub, firstRowOut, lastRowOut);

            extCircle.MoveToNextColumn();

            isContinue = extCircle.IsInRange();
            if(colCount == 0 || !isContinue) {
                DrawLineAndResetStates(colCtr, colOut, firstRowOut, lastRowOut);
                colCount = SUBPIX_LEN;
                firstRowOut = this->mNumRow;
                lastRowOut = 0;
                colOut ++;
            }
        }
    }

    void ProcessOneShape(VT rowCtr, VT colCtr, VT radius, 
        MODE_INT_EMPTY, MODE_ALG_ANTIALIAS)
    {
        VT rowCtrSub, colCtrSub, radiusSub, colCount;
        VT firstRowOut, lastRowOut, colOut;
        VT rowExtSub, rowIntSub;
        VT minRowSub, maxRowSub;
        VT radiusSubInt;
        boolean_T isContinue;

        int subpix_bit = SUBPIX_BIT;
        int subpix_halflen = SUBPIX_HALFLEN;
        int COL_COUNT = SUBPIX_HALFLEN;
        int subpix_len = SUBPIX_LEN;
        int ctrOffsetAA = SUBPIX_HALFLEN;
		int symmetryOffsetAA = 0;

        if (!this->mIsAntiAlias)
        {
            subpix_bit     = 0;
            subpix_halflen = 1;
            subpix_len     = 1;
            COL_COUNT = 1;
            ctrOffsetAA = 0;
			symmetryOffsetAA = 1;
        }

        // Circle with line width (i.e., thickness) (non-filled, anti-aliased)
        int lineWidth = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];
        VT halfLineWidth = (lineWidth/2);
        VT radiusNew = radius + halfLineWidth;// for even thickness, inside it's 1 pixel more.
                                              // if we want outside to be 1 pixel thicker, we will use 
                                              // (this->mLineWidth+1)/2
        int_T lineWidth_decim = ((lineWidth -1 ) << subpix_bit); // '-1' so that lineWidth_decim=0 when lineWidth=1;
        int_T fillCtrOffsetAA = 0;
        int_T divFactor = 0;

        // Downsampling will be done by floor(), 
        // so the pixel center is at SUBPIX_HALFLEN.
        rowCtrSub = (rowCtr << subpix_bit) + ctrOffsetAA;
        colCtrSub = (colCtr << subpix_bit) + ctrOffsetAA;
        radiusSub = radiusNew << subpix_bit;

        minRowSub = this->mViewPort[VIEWPORT_FIRSTROW] << subpix_bit;
        maxRowSub = ((this->mViewPort[VIEWPORT_LASTROW] + 1) << subpix_bit) - 1;

        colCount = COL_COUNT;
        colOut = 0;
        firstRowOut = this->mNumRow;
        lastRowOut = 0;

        MidPointFullCircle<VT> extCircle;
        MidPointFullCircle<VT> intCircle;

        if (this->mIsAntiAlias) {
            extCircle.Initialize(radiusSub + SUBPIX_HALFLEN - 1);
            radiusSubInt = radiusSub - SUBPIX_HALFLEN - 1 - lineWidth_decim;
            if (radiusSubInt <= -1) radiusSubInt = -1;
            intCircle.Initialize(radiusSubInt);
            divFactor = 1;
        }
        else{
            // for even lineWidth, more pixels on outside side of center line
            // we get the same behavior in rectangle
            extCircle.Initialize(radiusSub);
            radiusSubInt = radiusSub-lineWidth;
            if (radiusSubInt < 0) {radiusSubInt = 0; fillCtrOffsetAA = 1;}
            intCircle.Initialize(radiusSubInt);
            divFactor = 0;
        }

        for(rowExtSub=0; rowExtSub<this->mNumRow; rowExtSub++) this->mPixCount[rowExtSub] = 0;

        isContinue = extCircle.IsInRange();
        while(isContinue) {
            colCount --;

            rowExtSub = extCircle.GetRow();
            if(intCircle.IsInRange()) {
                rowIntSub = intCircle.GetRow();

                this->CountSubPixel(minRowSub, maxRowSub, 
                    rowCtrSub-rowExtSub-1+symmetryOffsetAA, rowCtrSub-rowIntSub-2+symmetryOffsetAA+fillCtrOffsetAA, 
                    firstRowOut, lastRowOut, subpix_bit, subpix_len);

                this->CountSubPixel(minRowSub, maxRowSub, 
                    rowCtrSub+rowIntSub+1, rowCtrSub+rowExtSub, 
                    firstRowOut, lastRowOut, subpix_bit, subpix_len);

                intCircle.MoveToNextColumn();
            }
            else { 
                this->CountSubPixel(minRowSub, maxRowSub, 
                    rowCtrSub-rowExtSub-1+symmetryOffsetAA, rowCtrSub+rowExtSub, 
                    firstRowOut, lastRowOut, subpix_bit, subpix_len);
            }
            extCircle.MoveToNextColumn();

            isContinue = extCircle.IsInRange();

            if(colCount == 0 || !isContinue) {
                DrawLineAndResetStates(colCtr, colOut, firstRowOut, lastRowOut, divFactor);
                colCount = subpix_len;
                firstRowOut = this->mNumRow;
                lastRowOut = 0;
                colOut ++;
            }
        }
    }

    void DrawLineAndResetStates(VT colCtr, VT colOut, VT& firstRowOut, VT& lastRowOut, int divFactor = 1)
    {
        VT i, col;
        if(colOut==0) {
            for(i=firstRowOut; i<=lastRowOut; i++) {
                this->mPixCount[i] <<= divFactor;
            }
        }
        else {
            col = colCtr + colOut;
            if(    col>=this->mViewPort[VIEWPORT_FIRSTCOL] 
                && col<=this->mViewPort[VIEWPORT_LASTCOL]) {
                this->PlotSubPixels(col, firstRowOut, lastRowOut, this->mIdxFillColor, this->mIdxOpacity);
            }
        }

        col = colCtr - colOut;
        if(    col>=this->mViewPort[VIEWPORT_FIRSTCOL] 
            && col<=this->mViewPort[VIEWPORT_LASTCOL]) {
            this->PlotSubPixels(col, firstRowOut, lastRowOut, this->mIdxFillColor, this->mIdxOpacity);
        }

        for(i=firstRowOut; i<=lastRowOut; i++) this->mPixCount[i] = 0;
        firstRowOut = this->mNumRow;
        lastRowOut = 0;
    }

protected:
    VT mRowCtr;
    VT mColCtr;
    VT mRadius;
}; // End of DrawCircle
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, 
    class MODE_PORT, class MODE_INT, class MODE_ALG>
class DrawCircleAnySize : public DrawCircle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT,MODE_ALG>
{
public:
    DrawCircleAnySize(
        DRAW_COMM_ARG1_LIST,
        PT* circles)
      : DrawCircle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT,MODE_ALG>(DRAW_COMM_VALUE_LIST),
        mCircles(circles)
    {
    }

    virtual ~DrawCircleAnySize() {}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            // Convert X,Y center to R,C coordinates
            this->mRowCtr = ToIntCoordinate<VT>(mCircles[idxROI+this->mNumShape])-1;
            this->mColCtr = ToIntCoordinate<VT>(mCircles[idxROI])-1;
            this->mRadius = ToIntCoordinate<VT>(mCircles[idxROI+2*this->mNumShape]);

            this->ProcessOneShape();
            this->MoveToNextFillColor();
            this->MoveToNextOpacity();
        }
    }

private:
    const PT* const mCircles;
}; // End of DrawCircleAnySize
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, 
    class MODE_PORT, class MODE_INT, class MODE_ALG>
class DrawCircleFixedSize : public DrawCircle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT,MODE_ALG>
{
public:
    DrawCircleFixedSize(
        DRAW_COMM_ARG1_LIST,
        PT* ctrs)
      : DrawCircle<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT,MODE_ALG>(DRAW_COMM_VALUE_LIST),
        mCtrs(ctrs)
    {           
    }
    virtual ~DrawCircleFixedSize() {}

    virtual void ProcessStep()
    {
         int size = this->mSize[0];
        this->ResetFillColorOpacityIndices();
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            getPoint(mCtrs, idxROI,
                     this->mNumShape, this->mRowCtr, this->mColCtr);
            this->mRadius = ToIntCoordinate<VT>(size);
            this->ProcessOneShape();

            this->MoveToNextFillColor();
            this->MoveToNextOpacity();
        }
    }

private:
    const PT* const mCtrs;
}; // End of DrawCircleFixedSize
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawLine : public DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT_EMPTY>
{
public:
    DrawLine(
        DRAW_COMM_ARG1_LIST)
      : DrawCommon<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_INT_EMPTY>(DRAW_COMM_VALUE_LIST)
    {
    }

    virtual ~DrawLine() {}

    void ProcessOneShape()
    {
        ProcessOneShape((MODE_ALG)0);
    }

    void ProcessOneShape(MODE_ALG_DIRECT)
    {
        VT idxPix;
        boolean_T isContinue;
        VT line[PT_LEN2];
        if(FindLineInViewPort(this->mViewPort, mLine, line)) {
            mBresenham.Initialize(line, this->mNumRow);
            isContinue = mBresenham.IsInRange();
            while(isContinue) {
                idxPix = mBresenham.GetIdxPix();
                mBresenham.MoveToNextPosition();
                isContinue = mBresenham.IsInRange();
                this->PlotOnePixel(this->mIdxFillColor, idxPix);
            }
        }
    }

    void ProcessOneShape(MODE_ALG_ANTIALIAS)
    {
        VT idx, in, pos, colCount, firstPos, lastPos, idxPix;
        boolean_T isContinue;
        VT line[PT_LEN2], minPosition, maxPosition;

        mLine[PT_ROW1] = (mLine[PT_ROW1] << SUBPIX_BIT) + SUBPIX_HALFLEN;
        mLine[PT_ROW2] = (mLine[PT_ROW2] << SUBPIX_BIT) + SUBPIX_HALFLEN;
        mLine[PT_COL1] = (mLine[PT_COL1] << SUBPIX_BIT) + SUBPIX_HALFLEN;
        mLine[PT_COL2] = (mLine[PT_COL2] << SUBPIX_BIT) + SUBPIX_HALFLEN;

        if(FindLineInViewPort(this->mViewPortSub, mLine, line)) {
            mBresenham.Initialize(line, this->mNumRow);
            if(mBresenham.IsHorizontal()) {
                minPosition = this->mViewPortSub[VIEWPORT_FIRSTROW];
                maxPosition = this->mViewPortSub[VIEWPORT_LASTROW];
            }
            else {
                minPosition = this->mViewPortSub[VIEWPORT_FIRSTCOL];
                maxPosition = this->mViewPortSub[VIEWPORT_LASTCOL];
            }

            VT maxPix = (this->mNumRow>=this->mNumCol ? this->mNumRow : this->mNumCol);
            firstPos = maxPix;
            lastPos = 0;
            in = (line[PT_ROW1] >> SUBPIX_BIT);
            colCount = ((in + 1) << SUBPIX_BIT) - line[PT_ROW1];

            for(idx=0; idx<maxPix; idx++) {
                this->mPixCount[idx] = 0;
            }

            isContinue = mBresenham.IsInRange();
            while(isContinue) {
                colCount --;
                pos = mBresenham.GetPosition();
                mBresenham.MoveToNextPosition();
                isContinue = mBresenham.IsInRange();

                // Skip the last sub-pixels so as to make symmetric 
                // starting and ending points
                if(isContinue) {
                    this->CountSubPixel(minPosition, maxPosition, 
                        pos-SUBPIX_HALFLEN, pos+SUBPIX_HALFLEN-1, firstPos, lastPos);
                }

                if(colCount == 0 || !isContinue) {
                    for(pos=firstPos; pos<=lastPos; pos++) {
                        idxPix = mBresenham.CalculateIndex(in, pos);
                        this->PlotSubPixels(idxPix, this->mPixCount[pos], this->mIdxFillColor);
                        this->mPixCount[pos] = 0;
                    }
                    colCount = SUBPIX_LEN;
                    firstPos = maxPix;
                    lastPos = 0;
                    in ++;
                }
            }
        }
    }

protected:
    VT mLine[PT_LEN2];

private:
    BresenhamLine<VT,MODE_ALG> mBresenham;
}; // End of DrawLine
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawAnyLine : public DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>
{
public:
    DrawAnyLine(
        DRAW_COMM_ARG1_LIST,
        PT* lines,
        PT* linesdw)
      : DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>(DRAW_COMM_VALUE_LIST),
        mLineAll(lines),
        mLineAlldw(linesdw)// remove this
    {
    }

    virtual ~DrawAnyLine() 
	{
		//delete[] mLineAlldw;
		//mLineAlldw = NULL;
	}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();

        int_T idxStart = 0;
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++) {
            for(int_T idxLine=0; idxLine<this->mNumSubShape-1; idxLine++)
            {
                this->mLine[PT_ROW1] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN+1)*this->mNumShape])-1;
                this->mLine[PT_COL1] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN  )*this->mNumShape])-1;
                this->mLine[PT_ROW2] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN+3)*this->mNumShape])-1;
                this->mLine[PT_COL2] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN+2)*this->mNumShape])-1;
                    
                if(this->mLine[PT_ROW1] != this->mLine[PT_ROW2]
                    || this->mLine[PT_COL1] != this->mLine[PT_COL2]) {
                    this->ProcessOneShape();
                }
                idxStart += PT_LEN;
            }

            idxStart += PT_LEN;
            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mLineAll;
    PT* mLineAlldw;// remove this
}; // End of DrawAnyLine
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawPolygon : public DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>
{
public:
    DrawPolygon(
        DRAW_COMM_ARG1_LIST,
        PT* lines,
        PT* linesdw)//remove this
      : DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>(DRAW_COMM_VALUE_LIST),
        mLineAll(lines),
        mLineAlldw(linesdw)//remove this
    {
    }

    virtual ~DrawPolygon()
	{
		//delete[] mLineAlldw;
		//mLineAlldw = NULL;
	}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();

        int_T idxStart = 0;
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            for(int_T idxLine=0; idxLine<this->mNumSubShape; idxLine++)
            {
                this->mLine[PT_ROW1] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN+1)*this->mNumShape])-1;
                this->mLine[PT_COL1] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN  )*this->mNumShape])-1;
                
                if(idxLine<this->mNumSubShape-1) 
                {
                    this->mLine[PT_ROW2] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN+3)*this->mNumShape])-1;
                    this->mLine[PT_COL2] = ToIntCoordinate<VT>(mLineAll[idxROI+(idxLine*PT_LEN+2)*this->mNumShape])-1;
                }
                else
                {
                    int_T idxFirst = idxROI;
                    this->mLine[PT_ROW2] = ToIntCoordinate<VT>(mLineAll[idxFirst+this->mNumShape])-1;
                    this->mLine[PT_COL2] = ToIntCoordinate<VT>(mLineAll[idxFirst])-1;
                }

                if(this->mLine[PT_ROW1] != this->mLine[PT_ROW2] 
                    || this->mLine[PT_COL1] != this->mLine[PT_COL2]) {
                    this->ProcessOneShape();
                }
                idxStart += PT_LEN;
            }

            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mLineAll;
    PT* mLineAlldw;//remove this

}; // End of DrawPolygon
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawMarkerLine : public DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>
{
public:
    DrawMarkerLine(
        DRAW_COMM_ARG1_LIST)
      : DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>(DRAW_COMM_VALUE_LIST)
    {
        
    }

    void ProcessOneShape()
    {
        ProcessOneShape((MODE_ALG)0);
    }

    void ProcessOneShape(MODE_ALG_ANTIALIAS)
    {
        DrawLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>::ProcessOneShape((MODE_ALG_ANTIALIAS)0);
    }

    void ProcessOneShape(MODE_ALG_DIRECT)
    {
        VT in, min, max, step, idxPix;
        VT line[PT_LEN2];      
        if(FindLineInViewPort(this->mViewPort, this->mLine, line)) {

            switch(mMode) {
            case LINE_HORIZONTAL:
                min = line[PT_COL1];
                max = line[PT_COL2];
                step = this->mNumRow;
                break;

            case LINE_VERTICAL:
                min = line[PT_ROW1];
                max = line[PT_ROW2];
                step = 1;
                break;

            case LINE_UP45DEGREE:
                min = line[PT_ROW1];
               
                max = line[PT_ROW2];
                step = this->mNumRow+1;
                break;

            case LINE_DOWN45DEGREE:
                min = line[PT_ROW1];
                max = line[PT_ROW2];
                step = 1-this->mNumRow;
                break;

            default:
                min  = 0;
                max  = 0;
                step = 1;
            }

            // Loop
            idxPix = line[PT_COL1] * this->mNumRow + line[PT_ROW1];
            for(in=min; in<=max; in++) {
                this->PlotOnePixel(this->mIdxFillColor, idxPix);
                idxPix += step;
            }
        }
    }

protected:
    LINE_MODE mMode;
}; // End of DrawMarkerLine
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT>
class DrawRectangleAnySize
    : public DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG_DIRECT>
{
public:
    DrawRectangleAnySize(
        DRAW_COMM_ARG1_LIST,
        PT* bboxes)
      : DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG_DIRECT>(DRAW_COMM_VALUE_LIST),
        mBBoxes(bboxes)
    {
    }

    virtual ~DrawRectangleAnySize() {}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();

        int lineWidthV = (this->mLineWidthPtr == NULL)? 1 : this->mLineWidthPtr[0];
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            VT firstRow, firstCol, lastRow, lastCol;

            // Convert XYWH to RCHW
            firstRow = ToIntCoordinate<VT>(mBBoxes[idxROI+this->mNumShape])-1;
            firstCol = ToIntCoordinate<VT>(mBBoxes[idxROI])-1;
            
            lastRow  = ToIntCoordinate<VT>
                (mBBoxes[idxROI+3*this->mNumShape]) + firstRow - 1;
            
            lastCol  = ToIntCoordinate<VT>
                (mBBoxes[idxROI+2*this->mNumShape]) + firstCol - 1;
            
            
            // Reactangle 
            // readjust so that for thick line, center line of the rectangle 
            // is at the location [x y w h]
            
            if (lineWidthV>1)
            {
               // for even lineWidth, more pixels on outside side of center line
               // we get the same behavior in circle
               VT halfLineWidth = (lineWidthV/2);

               firstRow -= halfLineWidth;
               lastRow  += halfLineWidth;
               firstCol -= halfLineWidth;
               lastCol  += halfLineWidth;
            }
             
            if(firstRow <= lastRow && firstCol <= lastCol) {
                
                for (int ii=0; ii<lineWidthV; ii++)
                {
                    // Top boundary
                    this->mLine[PT_ROW1] = firstRow+ii;
                    this->mLine[PT_COL1] = firstCol;
                    this->mLine[PT_ROW2] = firstRow+ii;
                    this->mLine[PT_COL2] = lastCol;
                    this->mMode = LINE_HORIZONTAL;
                    this->ProcessOneShape();

                    // Left boundary
                    this->mLine[PT_ROW1] = firstRow;
                    this->mLine[PT_COL1] = firstCol+ii;
                    this->mLine[PT_ROW2] = lastRow;
                    this->mLine[PT_COL2] = firstCol+ii;
                    this->mMode = LINE_VERTICAL;
                    this->ProcessOneShape();

                    // Bottom boundary
                    this->mLine[PT_ROW1] = lastRow-ii;
                    this->mLine[PT_COL1] = firstCol;
                    this->mLine[PT_ROW2] = lastRow-ii;
                    this->mLine[PT_COL2] = lastCol;
                    this->mMode = LINE_HORIZONTAL;
                    this->ProcessOneShape();

                    // Right boundary
                    this->mLine[PT_ROW1] = firstRow;
                    this->mLine[PT_COL1] = lastCol-ii;
                    this->mLine[PT_ROW2] = lastRow;
                    this->mLine[PT_COL2] = lastCol-ii;
                    this->mMode = LINE_VERTICAL;
                    this->ProcessOneShape();
                }
            }
            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mBBoxes;
}; // End of DrawRectangleAnySize
//=============================================================================


//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT>
class DrawSquareFixedSize
    : public DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG_DIRECT>
{
public:
    DrawSquareFixedSize(
        DRAW_COMM_ARG1_LIST,
        PT* pts)
      : DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG_DIRECT>(DRAW_COMM_VALUE_LIST),
        mPts(pts)
    {
    }

    virtual ~DrawSquareFixedSize() {}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();
        
        VT size = ToIntCoordinate<VT>(this->mSize[0]);
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            VT row, col;
            getPoint(mPts, idxROI,
                     this->mNumShape, row, col);

            // Top boundary
            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row - size;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_HORIZONTAL;
            this->ProcessOneShape();

            // Left boundary
            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col - size;
            this->mMode = LINE_VERTICAL;
            this->ProcessOneShape();

            // Bottom boundary
            this->mLine[PT_ROW1] = row + size;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_HORIZONTAL;
            this->ProcessOneShape();

            // Right boundary
            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col + size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_VERTICAL;
            this->ProcessOneShape();

            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mPts;
}; // End of DrawSquareFixedSize
//=============================================================================

//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT>
class DrawPlusFixedSize 
    : public DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG_DIRECT>
{
public:
    DrawPlusFixedSize(
        DRAW_COMM_ARG1_LIST,
        PT* pts)
      : DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG_DIRECT>(DRAW_COMM_VALUE_LIST),
        mPts(pts)
    {
    }

    virtual ~DrawPlusFixedSize() {}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();

        VT size = ToIntCoordinate<VT>(this->mSize[0]);
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++) 
        {
            VT row, col;
            getPoint(mPts, idxROI,  
                     this->mNumShape, row, col);
           
            this->mLine[PT_ROW1] = row;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_HORIZONTAL;
            this->ProcessOneShape();

            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col;
            this->mMode = LINE_VERTICAL;
            this->ProcessOneShape();

            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mPts;
}; // End of DrawPlusFixedSize
//=============================================================================


//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawXMarkFixedSize : public DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>
{
public:
    DrawXMarkFixedSize(
        DRAW_COMM_ARG1_LIST,
        PT* pts)
      : DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>(DRAW_COMM_VALUE_LIST),
        mPts(pts)
    {
    }

    virtual ~DrawXMarkFixedSize() {}

    virtual void ProcessStep()
    {               
        this->ResetFillColorOpacityIndices();
         VT size = ToIntCoordinate<VT>(this->mSize[0]);
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            VT row, col;
            getPoint(mPts, idxROI,  
                     this->mNumShape, row, col);  
            // Top boundary
            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_UP45DEGREE;
            this->ProcessOneShape();
            // Left boundary
            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col + size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col - size;
            this->mMode = LINE_DOWN45DEGREE;
            this->ProcessOneShape();

            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mPts;
}; // End of DrawXMarkFixedSize
//=============================================================================


//=============================================================================
//-----------------------------------------------------------------------------
template<class DT, class BT, class PT, class VT, class OpDT, class OpBT, class MODE_PORT, class MODE_ALG>
class DrawStarFixedSize : public DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>
{
public:
    DrawStarFixedSize(
        DRAW_COMM_ARG1_LIST,
        PT* pts)
      : DrawMarkerLine<DT,BT,PT,VT,OpDT,OpBT,MODE_PORT,MODE_ALG>(DRAW_COMM_VALUE_LIST),
        mPts(pts)
    {
    }

    virtual ~DrawStarFixedSize() {}

    virtual void ProcessStep()
    {
        this->ResetFillColorOpacityIndices();

        VT size = ToIntCoordinate<VT>(this->mSize[0]);
        for(int_T idxROI=0; idxROI<this->mNumShape; idxROI++)
        {
            VT row, col;
            getPoint(mPts, idxROI,
                     this->mNumShape, row, col);

            this->mLine[PT_ROW1] = row;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_HORIZONTAL;
            this->ProcessOneShape();

            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col - size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col + size;
            this->mMode = LINE_UP45DEGREE;
            this->ProcessOneShape();

            this->mLine[PT_ROW1] = row - size;
            this->mLine[PT_COL1] = col + size;
            this->mLine[PT_ROW2] = row + size;
            this->mLine[PT_COL2] = col - size;
            this->mMode = LINE_DOWN45DEGREE;
            this->ProcessOneShape();

            this->MoveToNextFillColor();
        }
    }

private:
    const PT* const mPts;
}; // End of DrawStarFixedSize
//=============================================================================

#endif

