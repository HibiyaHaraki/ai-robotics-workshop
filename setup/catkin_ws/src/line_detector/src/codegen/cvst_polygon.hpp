/*
* Copyright 2007-2019 The MathWorks, Inc.
*/

//-----------------------------------------------------------------------------
#ifndef TOINTCOORDINATE_H
#define TOINTCOORDINATE_H
template<class T>
inline T ToIntCoordinate(real_T val) { return(val>=0? (T)(val+0.5): (T)(val-0.5)); }
template<class T>
inline T ToIntCoordinate(real32_T val) { return(val>=0? (T)(val+0.5F): (T)(val-0.5F)); }
template<class T>
inline T ToIntCoordinate(int8_T val) { return((T)val); }
template<class T>
inline T ToIntCoordinate(uint8_T val) { return((T)val); }
template<class T>
inline T ToIntCoordinate(int16_T val) { return((T)val); }
template<class T>
inline T ToIntCoordinate(uint16_T val) { return((T)val); }
template<class T>
inline T ToIntCoordinate(int32_T val) { return((T)val); }
template<class T>
inline T ToIntCoordinate(uint32_T val) { return((T)val); }
#endif
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
#ifndef MODE_DRAW_H
#define MODE_DRAW_H
    // Image is in one port or three ports
    #define MODE_PORT_ONE       boolean_T
    #define MODE_PORT_RGB       int_T

    // Use anti-aliasing or not
    #define MODE_ALG_DIRECT     boolean_T
    #define MODE_ALG_ANTIALIAS  int_T

    // Fill shape or not
    #define MODE_INT_EMPTY      boolean_T
    #define MODE_INT_FILLED     int_T
#endif
//-----------------------------------------------------------------------------

/******************************************************************************
  This algorithm implements the classic scanline polygon filling algorithm.

  How to use this class:

  Per simulation:
    s.1. Call Reset().
    s.2. If the edges are static, which means both the TForms and ROIs are static
         Call IniPolygon(true) for all polygons.

    Per video frame:
      f.1. Call Reset().

      Per polygon: IsMorePolygon()
        p.1. Call IniPolygon() (same as IniPolygon(false)).
        p.2. Call MoveToColumn() to the first valid column or the column you want.

        Per column: 
          
          Per separator (separation of foreground and background pixels):
              IsMoreSeparator()
            r.1. Call GetAndAdvanceSeparator()

          c.1. NextColumn()

      f.2. Call NextPolygon() or NextPolygonWithRewind()

******************************************************************************/

#ifndef POLYGON_H
#define POLYGON_H

#ifndef EDGE_INDEX_H
    #define EDGE_INDEX_H
    typedef enum {
        EDGE_ERR = 0,
        EDGE_ROW,
        EDGE_COL,
        EDGE_COL_END,
        EDGE_ERR_THRESH,
        EDGE_STEP_LOW,
        EDGE_STEP_HIGH,
        EDGE_ERR_LOW,
        EDGE_ERR_HIGH,
        EDGE_LEN
    } EDGE_INDEX;
#endif

#ifndef PIX_INDEX_H
    #define PIX_INDEX_H
    typedef enum {
        PT_ROW = 0,
        PT_COL = 1,
        PT_X   = 0,
        PT_Y   = 1,
        PT_LEN = 2
    } PT_INDEX;
#endif

// Macros with prefix "SUBPIX" are used for anti-aliasing
//-----------------------------------------------------------------------------
#ifndef SUBPIX_BIT_H
#define SUBPIX_BIT_H
    #define SUBPIX_BIT      3
    #define SUBPIX_BIT2     6
    #define SUBPIX_HALFLEN  4
    #define SUBPIX_LEN      8
    #define SUBPIX_SIZE     64
#endif
//-----------------------------------------------------------------------------
 
template<class T, class PT, class MODE_ALG>
class Polygon
{
public:
    void NextColumn(void) { MoveToColumn(mActiveCol+1); };
    void MoveToColumn(T col);
    T GetFirstCol(void);
    T GetLastCol(void);

    boolean_T IsMoreSeparator(void) {
        return(mActiveEdgeIdx < mLastActiveEdgeIdx);
    };

    T GetAndAdvanceSeparator(void) {
        T val = mEdge[mActiveEdgeIdx+EDGE_ROW];
        mActiveEdgeIdx += EDGE_LEN;
        return(val); 
    };

    T GetSeparator(void) {
        T val = mEdge[mActiveEdgeIdx+EDGE_ROW];
        return(val); 
    };

    void Reset(void) { 
        mIdxEdgeStart = 0;
        mIdxPolygon = 0;
        ResetStates();
    };

    boolean_T IsMorePolygon(void) 
    { 
        return(mIdxEdgeStart < mNumPolygon*mNumPtPerPolygon*EDGE_LEN); 
    };

    void NextPolygon(void) 
    { 
        mIdxEdgeStart += mNumPtPerPolygon*EDGE_LEN;

        if(mIdxPolygon >= mSizePt/mNumPtPerPolygon - 1) {
            mIdxPolygon = 0;
        }
        else {
            mIdxPolygon++;
        }
    };

    void NextPolygonWithRewind(void) 
    {
        NextPolygon();
        if(!IsMorePolygon()) Reset();
    };

    void IniPolygon(boolean_T isForced=false);

    void UpdatePolygonNumbers(T numPolygon, T numPtPerPolygon, T sizePt)
    {
       mNumPolygon = numPolygon;
       mNumPtPerPolygon = numPtPerPolygon;
       mSizePt = sizePt;
    }

    // sizePt is the same as numPtPerPolygon for Apply Geometric Transformation block
    // This class must still operate in both new/old coordinate system
    // since its clients require that.
    Polygon(const PT* pt, PT* ptDW, T* edge, T* edgeBk, int_T numPolygon, 
        int_T numPtPerPolygon, int_T sizePt, boolean_T foldPtDW, boolean_T useNewCoords = true)
      : mPt(pt),
        mPtDW(ptDW),
        mEdge(edge),
        mEdgeBk(edgeBk),
        mNumPolygon(numPolygon),
        mNumPtPerPolygon(numPtPerPolygon), // NOTE: ABC: numPtPerPolygon==num point pairs (x,y) for a single shape Polygon
                                           // for isThickLineOrNonFilledThickPolygon, numSubShape is doubled and passed here
                                           // thick or non-thick line/polygon:  numSubShape is the number of points ((x,y) pair) in each row of point port
                                           // so if it s 3 point thick line, numSubShape=3 and numPtPerPolygon=3*2 (=6 (x,y) pairs for a polygon)
        mSizePt(sizePt),
        mFoldPtDW(foldPtDW),
        mUseNewCoords(useNewCoords)
    {
        Reset();
    };

private:
    boolean_T ConvertVerticesToEdges();

    boolean_T IsPolygonStaticAndSingle(void) 
    { 
        return(mEdgeBk!=NULL && mNumPolygon==1); 
    };

    inline int_T idxRow(int_T idxPolygon, int_T idxPoint)
    {
        if(mUseNewCoords) {
            return((idxPoint * PT_LEN + 1) * mNumPolygon + idxPolygon);
        }
        else {
            return((idxPolygon * mNumPtPerPolygon + idxPoint) * PT_LEN + PT_ROW);
        }
    }

    inline int_T idxCol(int_T idxPolygon, int_T idxPoint)
    {
        if(mUseNewCoords) {
            return(idxPoint * PT_LEN * mNumPolygon + idxPolygon);
        }
        else {
            return((idxPolygon * mNumPtPerPolygon + idxPoint) * PT_LEN + PT_COL);
        }
    }

    inline int_T idxNextPoint(int_T idx)
    {
        if(mUseNewCoords) {
            return(idx + PT_LEN * mNumPolygon);
        }
        else {
            return(idx + PT_LEN);
        }
    }

    inline T getCoordinate(int_T idx)
    {
        if(mUseNewCoords) {
            return(ToIntCoordinate<T>(mPt[idx]) - 1);
        }
        else {
            return(ToIntCoordinate<T>(mPt[idx]));
        }
    }

    void ResetStates(void)
    {
        mNumEdge           = 0;
        mActiveCol         = 0;  
        mNumActiveEdge     = 0;
        mActiveEdgeIdx     = 0;
        mLastActiveEdgeIdx = 0;
    };

    void SortEdges(int_T idxStart, int_T num, int_T idxSort);

    void CopyEdge(T* edgeSrc, T* edgeDst, int_T idxStart, int_T num) { 
        for(int_T i=idxStart; i<idxStart+num*EDGE_LEN; i++) {
            edgeDst[i] = edgeSrc[i]; 
        }
    };

    void UpsamplePoints(T&, T&, T&, T&, MODE_ALG_DIRECT)
    {
         
    }

    void UpsamplePoints(T& rowStart, T& colStart, T& rowEnd, T& colEnd, MODE_ALG_ANTIALIAS)
    {
        // This mode is used for anti-aliasing in the Draw Shapes and Draw Markers blocks
        rowStart = (rowStart << SUBPIX_BIT) + SUBPIX_HALFLEN;
        colStart = (colStart << SUBPIX_BIT) + SUBPIX_HALFLEN;
        rowEnd   = (rowEnd   << SUBPIX_BIT) + SUBPIX_HALFLEN;
        colEnd   = (colEnd   << SUBPIX_BIT) + SUBPIX_HALFLEN;
    }

private:
    void BresenhamLineIni(int_T idxStart, T rowStart, T colStart, T rowEnd, T colEnd);
    void BresenhamLineNextColumn(int_T idxStart);
    void BresenhamLineStepBack(int_T idxStart) { mEdge[idxStart+EDGE_COL_END]--; };
    boolean_T BresenhamLineMerge(int_T idx1, int_T idx2);

private:
    // Set at initialization
    const PT* const mPt;      // Size is mNumPtPerPolygon
          PT* const mPtDW;    // Size is mNumPtPerPolygon
          T*  const mEdge;    // Size is mNumPtPerPolygon*mNumPolygon*sizeof(EDGE)
          T*  const mEdgeBk;  // If not NULL, size is the same as mEdge

    int_T mNumPolygon;
    int_T mNumPtPerPolygon;
    int_T mSizePt;
    boolean_T mFoldPtDW;

    const boolean_T mUseNewCoords;

    int_T mIdxPolygon;        // The starting index of the points for the current polygon
    int_T mIdxEdgeStart;      // The starting index of the edges for the current polygon
    int_T mNumEdge;           // Number of edge in the current polygon
    T     mActiveCol;  

    // Run time values
    int_T mNumActiveEdge;
    int_T mActiveEdgeIdx;
    int_T mLastActiveEdgeIdx;
};

template<class T, class PT, class MODE_ALG>
void Polygon<T,PT,MODE_ALG>::IniPolygon(boolean_T isForce)
{
    ResetStates();

    if(isForce) {
        // Initialize and backup all polygons if they are static
        ConvertVerticesToEdges();
        if(mEdgeBk != NULL) {
            CopyEdge(mEdge, mEdgeBk, mIdxEdgeStart, mNumPtPerPolygon);
        }
    }
    else {
        if(mEdgeBk != NULL){
            // Restore the edges from the backup memory
            CopyEdge(mEdgeBk, mEdge, mIdxEdgeStart, mNumPtPerPolygon);

            // The edge number was not saved so has to be calculated again.
            int_T idxStart = mIdxEdgeStart;
            for(mNumEdge=0; mNumEdge<mNumPtPerPolygon; mNumEdge++) {
                if(mEdge[idxStart+EDGE_COL] > mEdge[idxStart+EDGE_COL_END]) break;
                idxStart += EDGE_LEN;
            }
        }
        else {
            // Otherwise, compute the edges dynamically
            ConvertVerticesToEdges();
        }
    }
}

template<class T, class PT, class MODE_ALG>
T Polygon<T,PT,MODE_ALG>::GetFirstCol(void)
{
    int_T i, idx;
    idx = mIdxEdgeStart + EDGE_COL;
    T firstCol = mEdge[idx];
    for(i=1; i<mNumEdge; i++) {
        idx += EDGE_LEN;
        if(firstCol > mEdge[idx]) {
            firstCol = mEdge[idx];
        }
    }
    return(firstCol);
}

template<class T, class PT, class MODE_ALG>
T Polygon<T,PT,MODE_ALG>::GetLastCol(void)
{
    int_T i, idx;
    idx = mIdxEdgeStart + EDGE_COL_END;
    T lastCol = mEdge[idx];
    for(i=1; i<mNumEdge; i++) {
        idx += EDGE_LEN;
        if(lastCol < mEdge[idx]) {
            lastCol = mEdge[idx];
        }
    }
    return(lastCol);
}

template<class T, class PT, class MODE_ALG>
void Polygon<T,PT,MODE_ALG>::MoveToColumn(T col)
{
    int_T i, j, numEdge, idxOld, idxNew, numActiveEdge;

    // Compact the valid edges to the top of the list and addvance them
    // to the requested column.
    idxNew = mIdxEdgeStart;
    idxOld = mIdxEdgeStart;
    mLastActiveEdgeIdx = mIdxEdgeStart;
    numEdge = 0;
    numActiveEdge = 0;
    for(i=0; i<mNumEdge; i++) {
        if(mEdge[idxOld+EDGE_COL_END] >= col) {
            if(mEdge[idxOld+EDGE_COL] <= col) {
                while(mEdge[idxOld+EDGE_COL] < col) {
                    BresenhamLineNextColumn(idxOld);
                }
                mLastActiveEdgeIdx += EDGE_LEN;
                numActiveEdge++;
            }
            if(idxOld != idxNew) {
                for(j=0; j<EDGE_LEN; j++) {
                    mEdge[idxNew+j] = mEdge[idxOld+j];
                }
            }
            idxNew += EDGE_LEN;
            numEdge++;
        }
        idxOld += EDGE_LEN;
    }
    mNumEdge = numEdge;

    // Sort edges
    SortEdges(mIdxEdgeStart, numActiveEdge, EDGE_ROW);
    mActiveEdgeIdx = mIdxEdgeStart;
    mActiveCol = col;
}

template<class T, class PT, class MODE_ALG>
boolean_T Polygon<T,PT,MODE_ALG>::ConvertVerticesToEdges()
{
    // regular is false when drawing Unfilled Polygon with linkWidth>1
    // in this case, the pointDW conatins point of two polygons- outside and inside
    // so here pointDW is split in the middle; first half for outside polygon
    //                                         second half for inside polygon
    int_T i, idxRow1, idxCol1, idxRow2, idxCol2, idxTmp;
    int_T idxEdgeCur, idxEdgePre, numEdge, numUniquePix;
    boolean_T isDecreasing, isSwapped;
    int mNumPtPerPolygon_new;
    int loopEndIdx;
    if (!mFoldPtDW){
        mNumPtPerPolygon_new = mNumPtPerPolygon;// see "NOTE: ABC"
        loopEndIdx = 1;
    }
    else{ // need folding polygons		
        mNumPtPerPolygon_new = mNumPtPerPolygon/2;
        loopEndIdx = 2;
    }

    numEdge = 0;
    idxEdgePre = mIdxEdgeStart;
    idxEdgeCur = mIdxEdgeStart;

    int idxTmpArray[2] = {mNumPtPerPolygon_new - 1, mNumPtPerPolygon - 1};
    int idxInitArray[2] = {0, mNumPtPerPolygon_new};
    bool prevEdgeIsVertical = false;
    bool firstEdgeIsVertical = false;
    for (int ii=0;ii<loopEndIdx;ii++)
    { 		
		
        idxTmp = idxTmpArray[ii];
        idxRow1 = idxRow(mIdxPolygon, idxTmp);
        idxCol1 = idxCol(mIdxPolygon, idxTmp);
        idxTmp--;
        idxCol2 = idxCol(mIdxPolygon, idxTmp);
        numUniquePix = mNumPtPerPolygon_new;
        // added protection for g1141342
        while((idxCol2>=0) && (getCoordinate(idxCol1) == getCoordinate(idxCol2))) {
            idxTmp--;
            idxCol2 = idxCol(mIdxPolygon, idxTmp);
            numUniquePix--;
        }

        // added protection for g1141342
        if (idxCol2<0) idxCol2 = 0;

        // whether column value decreases
        isDecreasing = getCoordinate(idxCol2) > getCoordinate(idxCol1);

        idxTmp = idxInitArray[ii];
        idxRow2 = idxRow(mIdxPolygon, idxTmp);
        idxCol2 = idxCol(mIdxPolygon, idxTmp);

        // g1193142
        // cache whether previous or first edge is vertical. This is used to 
        // avoid merging 2 horizontal edges separated by a vertical line.
        prevEdgeIsVertical = false;
        firstEdgeIsVertical = getCoordinate(idxCol1) == getCoordinate(idxCol2);

        // loop through vertices to compute edges
        for(i=0; i<numUniquePix; i++) {
            // Valid edge doesn't include vertical line
            if(getCoordinate(idxCol1) != getCoordinate(idxCol2)) {
                if(getCoordinate(idxCol1) < getCoordinate(idxCol2)) {
                    isSwapped = false;
                }
                else {
                    isSwapped = true;
                    idxTmp  = idxRow1;
                    idxRow1 = idxRow2;
                    idxRow2 = idxTmp;
                    idxTmp  = idxCol1;
                    idxCol1 = idxCol2;
                    idxCol2 = idxTmp;
                }

                BresenhamLineIni(idxEdgeCur, getCoordinate(idxRow1), 
                    getCoordinate(idxCol1), getCoordinate(idxRow2), 
                    getCoordinate(idxCol2));

                // Here we shorten one of the edges when 2 consecutive edges
                // are increasing or decreasing. This prevents a vertex to be
                // counted twice during the scanline filling operation in
                // vip_polygon_scanline. A consequence of this is that when
                // there is a vertical edge between 2 edges we see a thinner
                // vertical line for cases when the edge is the top edge and we
                // traverse the edges in a counter-clockwise manner. However,
                // because we only traverse edge by edge, we don't know whether
                // there is an edge above us or below us so we cannot prevent
                // the thinner edge from appearing. If we did prevent the
                // shortening in this case we would end up filling outside the
                // polygon or not filling the inside in some sections depending
                // on the other edge positions. See g1006488 for an example.
                
                if(!isDecreasing && !isSwapped) {  
                    // Keep increasing, don't include the starting point
                    BresenhamLineNextColumn(idxEdgeCur);
                }
                else if(isDecreasing && isSwapped) { 
                    // Keep decreasing, don't include the ending point
                    BresenhamLineStepBack(idxEdgeCur);
                }
                isDecreasing = isSwapped;
			
                if(prevEdgeIsVertical || !BresenhamLineMerge(idxEdgePre, idxEdgeCur)) 
                {					
                    idxEdgePre = idxEdgeCur;
                    numEdge ++;
                }				
					
                idxEdgeCur = idxEdgePre + EDGE_LEN;

                if(!isSwapped) {
                    idxRow1 = idxRow2;
                    idxCol1 = idxCol2;
                }
                idxRow2 = idxNextPoint(idxRow1);
                idxCol2 = idxNextPoint(idxCol1);
                prevEdgeIsVertical = false;
            }
            else {
                prevEdgeIsVertical = true;
                // Ignore the current ending point
                idxRow1  = idxRow2;
                idxCol1  = idxCol2;
                idxRow2 = idxNextPoint(idxRow2);
                idxCol2 = idxNextPoint(idxCol2);
            }
        }
    } // end of for loop

	if(!firstEdgeIsVertical)
	{
            // only merge if edges not separated by vertical line
            if(BresenhamLineMerge(mIdxEdgeStart, idxEdgePre)) {
                numEdge --;
                idxEdgeCur -= EDGE_LEN;
            }
	}

    // Set all other edges to invalid
    for(i=numEdge; i<mNumPtPerPolygon; i++) {
        mEdge[idxEdgeCur+EDGE_COL]     = 1;
        mEdge[idxEdgeCur+EDGE_COL_END] = 0;
        idxEdgeCur += EDGE_LEN;
    }

    // Sort all edges according to column values
    SortEdges(mIdxEdgeStart, numEdge, EDGE_COL);

    mNumEdge = numEdge;
    return(numEdge >= 2);
}

template<class T, class PT, class MODE_ALG>
void Polygon<T,PT,MODE_ALG>::SortEdges(int_T idxStart, int_T num, int_T idxSort)
{
    int_T i, j, idx1, idx2;
    T  edgeTmp;
    boolean_T hasChange = true;

    while(hasChange) {
        idx1 = idxStart;
        idx2 = idx1 + EDGE_LEN;
        hasChange = false;
        for(i=1; i<num; i++) {
            if(mEdge[idx1+idxSort] > mEdge[idx2+idxSort]) {
                hasChange = true;
                // Swap edge1 and edge2
                for(j=0; j<EDGE_LEN; j++) {
                    edgeTmp = mEdge[idx1+j];
                    mEdge[idx1+j] = mEdge[idx2+j];
                    mEdge[idx2+j] = edgeTmp;
                }
            }
            idx1 = idx2;
            idx2 += EDGE_LEN;
        }
    }
}

template<class T, class PT, class MODE_ALG>
inline boolean_T Polygon<T,PT,MODE_ALG>::BresenhamLineMerge(int_T idx1, int_T idx2)
{
    boolean_T isValid = false;
    if(idx1 != idx2) {
        if(    mEdge[idx1+EDGE_STEP_LOW]  == mEdge[idx2+EDGE_STEP_LOW]
            && mEdge[idx1+EDGE_STEP_HIGH] == mEdge[idx2+EDGE_STEP_HIGH]
            && mEdge[idx1+EDGE_ERR_LOW]   == mEdge[idx2+EDGE_ERR_LOW]
            && mEdge[idx1+EDGE_ERR_HIGH]  == mEdge[idx2+EDGE_ERR_HIGH]) {
                if(mEdge[idx2+EDGE_COL] == mEdge[idx1+EDGE_COL_END] + 1) {
                    mEdge[idx1+EDGE_COL_END] = mEdge[idx2+EDGE_COL_END];
                    isValid = true;
                }
                else if(mEdge[idx1+EDGE_COL] == mEdge[idx2+EDGE_COL_END] + 1) {
                    mEdge[idx1+EDGE_ROW] = mEdge[idx2+EDGE_ROW];
                    mEdge[idx1+EDGE_COL] = mEdge[idx2+EDGE_COL];
                    isValid = true;
                }
            }
    }
    return(isValid);
}

// colEnd > colStart
template<class T, class PT, class MODE_ALG>
void Polygon<T,PT,MODE_ALG>::BresenhamLineIni(int_T idxStart, T rowStart, T colStart, T rowEnd, T colEnd)
{
    UpsamplePoints(rowStart, colStart, rowEnd, colEnd, MODE_ALG(0));

    T numCols = colEnd - colStart;
    T numRows =(rowEnd >= rowStart? rowEnd-rowStart: rowStart-rowEnd);
    mEdge[idxStart+EDGE_ERR] = 0;
    mEdge[idxStart+EDGE_ROW] = rowStart;
    mEdge[idxStart+EDGE_COL] = colStart;
    mEdge[idxStart+EDGE_COL_END] = colEnd;

    mEdge[idxStart+EDGE_STEP_HIGH] = 0;
    mEdge[idxStart+EDGE_ERR_HIGH] = numRows;
    while(mEdge[idxStart+EDGE_ERR_HIGH] >= 0){
        mEdge[idxStart+EDGE_STEP_HIGH] ++;
        mEdge[idxStart+EDGE_ERR_HIGH] -= numCols;
    }
    mEdge[idxStart+EDGE_STEP_LOW] = mEdge[idxStart+EDGE_STEP_HIGH] - 1;
    mEdge[idxStart+EDGE_ERR_LOW] = mEdge[idxStart+EDGE_ERR_HIGH] + numCols;
    mEdge[idxStart+EDGE_ERR_THRESH] = numCols - (mEdge[idxStart + EDGE_ERR_LOW]<<1);

    if(rowStart > rowEnd) {
        mEdge[idxStart+EDGE_STEP_LOW] = -mEdge[idxStart+EDGE_STEP_LOW];
        mEdge[idxStart+EDGE_STEP_HIGH] = -mEdge[idxStart+EDGE_STEP_HIGH];
    }
}

// May add col checking to this function
template<class T, class PT, class MODE_ALG>
void Polygon<T,PT,MODE_ALG>::BresenhamLineNextColumn(int_T idxStart)
{
    mEdge[idxStart+EDGE_COL] ++;
    if(mEdge[idxStart+EDGE_ERR]<<1 > mEdge[idxStart+EDGE_ERR_THRESH]) {
        mEdge[idxStart+EDGE_ERR] += mEdge[idxStart+EDGE_ERR_HIGH];
        mEdge[idxStart+EDGE_ROW] += mEdge[idxStart+EDGE_STEP_HIGH];
    }
    else {
        mEdge[idxStart+EDGE_ERR] += mEdge[idxStart+EDGE_ERR_LOW];
        mEdge[idxStart+EDGE_ROW] += mEdge[idxStart+EDGE_STEP_LOW];
    }
}


#endif
