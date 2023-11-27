/*
* Copyright 2007-2011 The MathWorks, Inc.
*/

#ifndef SCANLINE_H
#define SCANLINE_H

#include "cvst_polygon.hpp"

template<class T, class PT, class MODE_ALG>
class ScanLineBase
{ 
public:
    boolean_T IsMoreScanLine(void)     { return(mActiveCol <= mLastOutCol); };
    boolean_T IsMoreForeScanLine(void) { return(mActiveCol <= mLastValidCol); };
    void GetScanLine(boolean_T& isForeground, T& col, T& firstRow, T& lastRow);

    boolean_T IsMoreLayer(void) { return(mPolygon->IsMorePolygon()); };
    virtual void NextLayer(void) = 0;
    virtual void IniLayer(void) = 0;

    boolean_T IsClipped(void) { return(mIsClipped); };
    virtual void Reset(void) = 0;
    virtual class Polygon<T,PT,MODE_ALG>* GetPolygonBdy(void) = 0;

    void UpdateViewPort(T firstRow, T firstCol, T lastRow, T lastCol)
    {
        mFirstOutRow         = firstRow;
        mFirstOutCol         = firstCol;
        mLastOutRow          = lastRow;
        mLastOutCol          = lastCol;
        mFirstValidRow       = firstRow;
        mLastValidRow        = lastRow;
        mFirstOutRowMinusOne = firstRow - 1;
        mLastOutRowPlusOne   = lastRow + 1;
    }

    void UpdatePolygonNumbers(T numPolygon, T numPtPerPolygon, T sizePt)
    {
       mPolygon->UpdatePolygonNumbers(numPolygon, numPtPerPolygon, sizePt);
    }

    ScanLineBase(Polygon<T,PT,MODE_ALG>* polygon, T firstRow, T firstCol, T lastRow, T lastCol);

    virtual ~ScanLineBase()
    { 
       delete mPolygon; 
       mPolygon = NULL;
    };

protected:
    virtual void IniStates(void) = 0;
    virtual void NextColumn(void) = 0;

protected:
    Polygon<T,PT,MODE_ALG>* mPolygon;

    T mFirstOutRow;
    T mFirstOutCol;
    T mLastOutRow;
    T mLastOutCol;
    T mFirstOutRowMinusOne;
    T mLastOutRowPlusOne;

    T mFirstValidCol;
    T mFirstValidRow;
    T mLastValidCol;
    T mLastValidRow;
    T mActiveCol;
    T mLastSeparator;

    boolean_T mIsForeground;
    boolean_T mIsClipped;
    boolean_T mHasInputPixBeforeOutput;
    boolean_T mHasInputPixBelowOutput;
};

template<class T, class PT, class MODE_ALG>
ScanLineBase<T,PT,MODE_ALG>::ScanLineBase(Polygon<T,PT,MODE_ALG>* polygon, T firstRow, T firstCol, T lastRow, T lastCol)
: mPolygon(polygon),
  mFirstOutRow(firstRow),
  mFirstOutCol(firstCol),
  mLastOutRow(lastRow),
  mLastOutCol(lastCol),
  mFirstOutRowMinusOne(firstRow-1),
  mLastOutRowPlusOne(lastRow+1)
{
}

// mRowEndValid and mRowStartValid are the combination of view port and input boundary.
template<class T, class PT, class MODE_ALG>
void ScanLineBase<T,PT,MODE_ALG>::GetScanLine(boolean_T& isForeground, T& col, T& firstRow, T& lastRow)
{
    isForeground = mIsForeground;
    col = mActiveCol; 
    bool countTwice = false;
    if(mActiveCol >= mFirstValidCol && mActiveCol <= mLastValidCol) {
        if(mPolygon->IsMoreSeparator()) {
            T curSeparator = mPolygon->GetAndAdvanceSeparator();
            if(curSeparator == mLastSeparator) {
                // When the current separator equals the last separator we
                // are at a vertex. We need to check whether multiple
                // polygons share the same vertex. If they do, duplicate
                // separators can appear after the vertex when the polygon
                // is degenerate.  The following while loop will skip the
                // duplicated ones.  See geck #728605 and #1002628 for
                // details.

                if(mPolygon->IsMoreSeparator()) {
                    T nextSeparator = mPolygon->GetSeparator();
                    while(curSeparator == nextSeparator) {
                        countTwice = true;
                        curSeparator = mPolygon->GetAndAdvanceSeparator();
                        if(mPolygon->IsMoreSeparator()) {
                            nextSeparator = mPolygon->GetSeparator();
                        }
                        else {
                            // no more edges below current separator
                            // don't count the vertex twice, otherwise
                            // you'll fill outside the polygon.
                            countTwice = false;
                            break;
                        }
                    }
                }
            }
            if(mIsForeground) {
                firstRow = mLastSeparator;
                if(curSeparator <= mLastOutRow) {
                    lastRow = curSeparator;
                    mLastSeparator = curSeparator;
                }
                else {
                    lastRow = mLastOutRow;
                    if(mHasInputPixBelowOutput) mIsClipped = true;
                    mLastSeparator = mLastOutRow;
                }
            }
            else { // The first or middle scanlines
                firstRow = mLastSeparator + 1;
                if(curSeparator > mFirstOutRow && curSeparator <= mLastOutRow) {
                    lastRow = curSeparator - 1;
                    mLastSeparator = curSeparator;
                }
                else if(curSeparator <= mFirstOutRow){
                    lastRow = mFirstOutRowMinusOne; 
                    mLastSeparator = mFirstOutRow;
                    if(mHasInputPixBeforeOutput) mIsClipped = true;
                }
                else { // curSeparator > mLastOutRow
                    lastRow = mLastOutRow;
                    mLastSeparator = mLastOutRowPlusOne;
                    if(mHasInputPixBelowOutput) mIsClipped = true;
                }
            }

            if (!countTwice)
                mIsForeground = !mIsForeground;
        }
        else { // The last scanline
            // Must be background
            isForeground = false;
            firstRow = mLastSeparator + 1;
            lastRow = mLastOutRow;

            // Move to the next column and reset states
            NextColumn();
            IniStates();
            mActiveCol ++;
        }
    }
    else {
        firstRow = mFirstOutRow;
        lastRow = mLastOutRow;
        mActiveCol ++;
    }

    // Make sure the string is in valid range
    if (firstRow < mFirstOutRow) {
        firstRow = mFirstOutRow;
    }

    if (lastRow  > mLastOutRow)  {
        lastRow = mLastOutRow;
    }
    else if (lastRow < firstRow) {
        lastRow = firstRow - 1;
    }
}


//*****************************************************************************
//*****************************************************************************
template<class T, class PT, class MODE_ALG>
class ScanLine: ScanLineBase<T,PT,MODE_ALG>
{
public:
    virtual void IniLayer(void);

    virtual void NextLayer(void) {
        this->mPolygon->NextPolygon();
    };

    virtual void Reset(void)
    {
        this->mIsClipped = false;
        this->mPolygon->Reset();
    };

    class Polygon<T,PT,MODE_ALG>* GetPolygonBdy(void) { return(this->mPolygon); };

    ScanLine(Polygon<T,PT,MODE_ALG>* polygonBdy, T firstRow, T firstCol, T lastRow, T lastCol)
      : ScanLineBase<T,PT,MODE_ALG>(polygonBdy, firstRow, firstCol, lastRow, lastCol)
    {
        this->mHasInputPixBeforeOutput = true;
        this->mHasInputPixBelowOutput  = true;
        this->mFirstValidRow = this->mFirstOutRow;
        this->mLastValidRow  = this->mLastOutRow;
    };

private:
    virtual void IniStates(void)
    {
        this->mIsForeground = false;
        this->mLastSeparator = this->mFirstOutRowMinusOne;
    };

    virtual void NextColumn(void) 
    {
        this->mPolygon->NextColumn();
    };
};

template<class T, class PT, class MODE_ALG>
void ScanLine<T,PT,MODE_ALG>::IniLayer(void)
{
    this->mPolygon->IniPolygon();

    this->mFirstValidCol = this->mPolygon->GetFirstCol();
    if(this->mFirstValidCol < this->mFirstOutCol) {
        this->mFirstValidCol = this->mFirstOutCol;
        this->mIsClipped = true;
    }

    this->mLastValidCol = this->mPolygon->GetLastCol();
    if(this->mLastValidCol > this->mLastOutCol) {
        this->mLastValidCol = this->mLastOutCol;
        this->mIsClipped = true;
    }

    this->mPolygon->MoveToColumn(this->mFirstValidCol);
    this->mActiveCol = this->mFirstOutCol;
    IniStates();
}

//*****************************************************************************
//*****************************************************************************
template<class T, class PT, class MODE_ALG>
class ScanLineROI : public ScanLineBase<T,PT,MODE_ALG>
{
public:
    virtual void NextLayer(void) {
        this->mPolygonBdy->NextPolygonWithRewind();
        this->mPolygon->NextPolygon();
    };

    virtual void Reset(void);
    virtual void IniLayer(void);

    class Polygon<T,PT,MODE_ALG>* GetPolygonROI(void) { return(this->mPolygon); };
    class Polygon<T,PT,MODE_ALG>* GetPolygonBdy(void) { return(this->mPolygonBdy); };
    
    ScanLineROI(Polygon<T,PT,MODE_ALG>* polygonROI, Polygon<T,PT,MODE_ALG>* polygonBdy, T firstRow, T firstCol, T lastRow, T lastCol)
      : ScanLineBase<T,PT,MODE_ALG>(polygonROI, firstRow, firstCol, lastRow, lastCol),
      mPolygonBdy(polygonBdy)
    {
    };

    ~ScanLineROI() 
    { 
       delete mPolygonBdy;
       mPolygonBdy = NULL;
    };

private:
    virtual void IniStates(void);

    virtual void NextColumn(void) 
    {
        this->mPolygon->NextColumn();
        this->mPolygonBdy->NextColumn();
    };

private:
    Polygon<T,PT,MODE_ALG>* mPolygonBdy;
};

template<class T, class PT, class MODE_ALG>
void ScanLineROI<T,PT,MODE_ALG>::Reset()
{
    this->mIsClipped = false;
    this->mPolygonBdy->Reset();
    this->mPolygon->Reset();
}

template<class T, class PT, class MODE_ALG>
void ScanLineROI<T,PT,MODE_ALG>::IniLayer(void)
{
    T colBdy, colROI;

    this->mPolygonBdy->IniPolygon(true);
    this->mPolygon->IniPolygon(true);

    colBdy = this->mPolygonBdy->GetFirstCol();
    colROI = this->mPolygon->GetFirstCol();
    this->mFirstValidCol = (colBdy>=colROI? colBdy: colROI);
    if(this->mFirstValidCol < this->mFirstOutCol) {
        this->mFirstValidCol = this->mFirstOutCol;
        this->mIsClipped = true;
    }

    colBdy = this->mPolygonBdy->GetLastCol();
    colROI = this->mPolygon->GetLastCol();
    this->mLastValidCol  = (colBdy<=colROI? colBdy: colROI);
    if(this->mLastValidCol > this->mLastOutCol) {
        this->mLastValidCol = this->mLastOutCol;
        this->mIsClipped = true;
    }

    this->mPolygonBdy->MoveToColumn(this->mFirstValidCol);
    this->mPolygon->MoveToColumn(this->mFirstValidCol);

    this->mActiveCol = this->mFirstOutCol;

    IniStates();
}

template<class T, class PT, class MODE_ALG>
void ScanLineROI<T,PT,MODE_ALG>::IniStates(void)
{
    // Initialize states
    this->mIsForeground = false;
    this->mLastSeparator = this->mFirstOutRowMinusOne;

    this->mFirstValidRow = this->mPolygonBdy->GetAndAdvanceSeparator();
    if(this->mFirstValidRow >= this->mFirstOutRow) {
        this->mHasInputPixBeforeOutput = false;
    }
    else {
        this->mHasInputPixBeforeOutput = true;
        this->mFirstValidRow = this->mFirstOutRow;
    }

    this->mLastValidRow = this->mPolygonBdy->GetAndAdvanceSeparator();
    if(this->mLastValidRow <= this->mLastOutRow) {
        this->mHasInputPixBelowOutput = false;
    }
    else {
        this->mHasInputPixBelowOutput = true;
        this->mLastValidRow = this->mLastOutRow;
    }
}


#endif

