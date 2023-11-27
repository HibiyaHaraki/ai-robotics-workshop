/*
* Copyright 2007-2011 The MathWorks, Inc.
*/

#ifndef CVSTTHICKLINEPOLYGONVERTICES_SIM_HPP
#define CVSTTHICKLINEPOLYGONVERTICES_SIM_HPP	

int nearest(OpDT x) {
	OpDT tmp = x - floor(x);
	int output;

	if ((-0.5<tmp) && (tmp<0.5)) {
		output = static_cast<int>(floor(x));
	}
	else {
		output = static_cast<int>(floor(x + 0.5));
	}
	return output;
}

//----------Divide---------------

inline
void lclDSPFixptDivide(real_T & quot, const real_T & num, const real_T & denom)
{ 
    quot = (real_T)num / denom; 
}

inline
void lclDSPFixptDivide(real32_T & quot, const real32_T & num, const real32_T & denom)
{ 
    quot = (real32_T)num / denom; 
}

//----------SQRT---------------

inline
void lclDSPFixptSqrt(real_T& out, const real_T in)
{
    out = sqrt((real_T)in);
}

inline
void lclDSPFixptSqrt(real32_T& out, const real32_T in)
{
    out = sqrt((real32_T)in);
}

//----------Integer assignment-------

inline
void lclAssign(real_T& out, const int in)
{
    out = in;
}

inline
void lclAssign(real32_T& out, const int in)
{
    out = (real32_T)in;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void getLineParams(int whereNormal, int x1, int y1, int x2, int y2, int halfLineWidth, OpDT *paramObj, Paral_T &parallelTo_XorYaxis)
{
    // whereNormal: -1 : normal is at left point (x1,y1)
    //               0 : no need to get normal's info
    //              +1 : normal is at right point (x2,y2)

    // NOTE : LINEXYZ
    // Line1: y = mx + c1
    //	 paramObj[0] = slope (m)
    //	 paramObj[1] = y-intercept (c1)
    // Line2: parallel to Line1 and  with distance HalfLineWidth: y = mx + c11
    //   paramObj[2] = y-intercept of parallel line with distance HalfLineWidth (c11)
    // Line3: parallel to Line1 and  with distance -HalfLineWidth: y = mx + c12
    //   paramObj[3] = y-intercept of parallel line with distance -HalfLineWidth (c12)
    // Line4: perpendicular to Line1 that passes through (x1, y1): y = (-1/m)x + c13
    //   paramObj[4] = y-intercept of perpendicular line (c13)

    int32_T y1_M_y2 =  y1-y2;
    int32_T x1_M_x2 =  x1-x2;
	OpDT tempVar1(0), tempVar2(0), tempVar3(0);
    // m1, c1, c11, c12, c13 ==> all are in paramObj[0 to 4]

    // codegen uses paramObj[4]=0 to avoid warning

    if (x1_M_x2 == 0)
    {
        parallelTo_XorYaxis = PARALLEL_TO_Y_AXIS; // that means Line1, Line2 and Line3 are parallel to Y-axis
        // Line1: 'y = mx + c1' becomes 'x = x1'
        // paramObj[0] = m = INF => instead of storing inf, we pass flag enum_m_c_inf  = SLOPE_INF
        // codegen uses paramObj[0]=0 to avoid warning
        // paramObj[1] = c1 = meaningless => so we store x1 here
        lclAssign(paramObj[1], x1);// paramObj[1] = (int16_T)x1;			
        // Line2: parallel to Line1 and  with distance HalfLineWidth: 'y = mx + c11' becomes 'x = x1-halfLineWidth'
        // paramObj[2] = c11 = meaningless => so we store x1-halfLineWidth here
        lclAssign(paramObj[2], (x1-halfLineWidth));// paramObj[2] = (int16_T)(x1-halfLineWidth);
        // Line3: parallel to Line1 and  with distance -HalfLineWidth: 'y = mx + c12' becomes 'x = x1+halfLineWidth'
        // paramObj[32] = c12 = meaningless => so we store x1+halfLineWidth here
        lclAssign(paramObj[3], (x1+halfLineWidth));//paramObj[3] = (int16_T)(x1+halfLineWidth);
        // Line4: perpendicular to Line1 that passes through (x1, y1): y = (-1/m)x + c13 => y = (y1 (left normal) or y2 (right normal))
        //   paramObj[4] = c13
        if (whereNormal != 0)
        {
            if (whereNormal==-1){
                // normal is at left point (x1,y1)
                lclAssign(paramObj[4], y1);//paramObj[4] = (int16_T)y1;
            }
            else { //if (whereNormal==1)
                // normal is at right point (x2,y2)
                lclAssign(paramObj[4], y2);//paramObj[4] = (int16_T)y2;
            }
        }

    }
    else if (y1_M_y2 == 0)
    {
        parallelTo_XorYaxis = PARALLEL_TO_X_AXIS; // that means Line1, Line2 and Line3 are parallel to X-axis
        // Line1: 'y = mx + c1' becomes 'y = y1'
        // paramObj[0] = m = 0
        paramObj[0] = 0;
        // paramObj[1] = c1 = y1
        lclAssign(paramObj[1], y1);//paramObj[1] = (int16_T)y1;
        // Line2: parallel to Line1 and  with distance HalfLineWidth: 'y = mx + c11' becomes 'y = c11 = y1-halfLineWidth'
        // paramObj[2] = c11 = y1-halfLineWidth
        lclAssign(paramObj[2], (y1-halfLineWidth));//paramObj[2] = (int16_T)(y1-halfLineWidth);
        // Line3: parallel to Line1 and  with distance -HalfLineWidth: 'y = mx + c12' becomes 'y = c12 = y1+halfLineWidth'
        // paramObj[32] = c12 = meaningless => so we store x1+halfLineWidth here
        lclAssign(paramObj[3], (y1+halfLineWidth));//paramObj[3] = (int16_T)(y1+halfLineWidth);
        // Line4: perpendicular to Line1 that passes through (x1, y1): y = (-1/m)x + c13 => y = (x1 (left normal) or x2 (right normal))
        //   paramObj[4] = c13
        if (whereNormal != 0)
        {
            if (whereNormal==-1){
                // normal is at left point (x1,y1)
                lclAssign(paramObj[4], x1);//paramObj[4] = (int16_T)x1;
            }
            else { //if (whereNormal==1)
                // normal is at right point (x2,y2)
                lclAssign(paramObj[4], x2);//paramObj[4] = (int16_T)x2;
            }
        }

    }
    else
    {
        parallelTo_XorYaxis = PARALLEL_TO_NO_AXIS;
        // step-1: slope, m = (y1-y2)/(x1-x2) => paramObj[0]
        lclAssign(tempVar1, y1_M_y2);//tempVar1 = (int16_T)y1_M_y2;

        lclAssign(tempVar3, x1_M_x2);//tempVar3 = (int16_T)x1_M_x2;
        lclDSPFixptDivide(paramObj[0], tempVar1, tempVar3);

        // step-2: y intercept, c1 = y1-x1*m1;  => paramObj[1]
        lclAssign(tempVar1, x1);//tempVar1 = (int16_T)x1;
        tempVar1 *= paramObj[0]; // x1*m1
        lclAssign(paramObj[1], y1);//paramObj[1] = (int16_T)y1; // y1
        paramObj[1] -= tempVar1; // c1 = y1-x1*m1

        // step-3: to get c11, c12 and c13 first find hyptenuse, cot_theta and t/cos_theta
        //step-3.1: find hypotenuse
        {
            int32_T hypSQ = y1_M_y2*y1_M_y2 + x1_M_x2*x1_M_x2;
            //tempVar1 = sqrt(hypSQ);
            //tempVar3 = hypSQ;
            lclAssign(tempVar3, hypSQ);
            // 
            
            lclDSPFixptSqrt(tempVar2, tempVar3);
            tempVar1 = tempVar2;
        }
        //step-3.2: find cos_theta
        {
            // cos_theta = base/hyp; % cos(theta);
            lclAssign(paramObj[2], x1_M_x2);//paramObj[2]  = (int16_T)x1_M_x2;
            lclDSPFixptDivide(tempVar3, paramObj[2], tempVar1);
        }
        // step 3.2: find t/cos_theta
        {
            lclAssign(paramObj[2], halfLineWidth);//paramObj[2] = (int16_T)halfLineWidth;
            lclDSPFixptDivide(tempVar1, paramObj[2], tempVar3);
            tempVar3 = tempVar1;
        }
        // step 3.4: find c11 using c11 = c1 + (t/cos_theta);
        tempVar1 = paramObj[1]; //c1
        tempVar1  += tempVar3;//c1 + t_by_cos_theta
        paramObj[2] = tempVar1;

        // step 3.5: find c12 using c12 = c1 - (t/cos_theta);
        tempVar1 = paramObj[1]; //c1
        tempVar1  -= tempVar3;//c1 - t_by_cos_theta
        paramObj[3] = tempVar1;

        // step 3.6: find c13 using c13 = y1 +(1/m1)*x1 = (x1/m1) + y1
        if (whereNormal != 0)
        {
            int xN, yN;
            if (whereNormal==-1){
                // normal is at left point (x1,y1)
                xN = x1;
                yN = y1;
            }
            else { //if (whereNormal==1)
                // normal is at right point (x2,y2)
                xN = x2;
                yN = y2;
            }
            lclAssign(tempVar3, xN);//tempVar3 = (int16_T)xN;
            lclDSPFixptDivide(tempVar1, tempVar3, paramObj[0]); // x1_by_m1
            lclAssign(tempVar3, yN);//tempVar3 = (int16_T)yN;
            tempVar1 += tempVar3;
            paramObj[4] = tempVar1;
        }
    }
}	

boolean_T isValidPair(int x1, int y1, 
    int x2, int y2, 
    int x3, int y3, 
    OpDT *paramObj1, OpDT *paramObj2,
    Paral_T parallelTo_XorYaxis1, Paral_T parallelTo_XorYaxis2)
{
    // Let's say 1st_Paral_Line_12 = FIRST parallel line of (x1,y1) and (x2, y2)
    //           1st_Paral_Line_23 = FIRST parallel line of (x2,y2) and (x3, y3)
    // This function checks if 1st_Paral_Line_12 and 1st_Paral_Line_23 lie on 
    // the same side of the polyline[(x1,y1),(x2,y2),(x3,y3)]

    // center point: (x1, y1)
    // reference point: (x2, y2)
    // point on line m1, c11 => y = m1 * x +  c11 => point (0,c11)
    //   so first point: (0,c11)

    XY_T centerPt;
    XY_T refPt;   
    XY_T firstPt; 
    XY_T secondPt; 

    centerPt.x = x1; centerPt.y = y1;
    refPt.x    = x2; refPt.y    = y2;
    if (parallelTo_XorYaxis1 == PARALLEL_TO_Y_AXIS){
        // x1-halfLineWidth, y1 (or y2- same thing)
        firstPt.x  = nearest(paramObj1[2]);  firstPt.y  = y1;
    }
    else if (parallelTo_XorYaxis1 == PARALLEL_TO_X_AXIS){
        // x1 (or x2- same thing), y1-halfLineWidth,
        firstPt.x  = x1;  firstPt.y  = nearest(paramObj1[2]);
    }
    else {
        int c11 = nearest(paramObj1[2]);
        firstPt.x  = 0;  firstPt.y  = c11;
    }
    boolean_T firstPtOnRight = is_RightOfLine_CtrToRef(refPt, centerPt, firstPt);

    // center point: (x2, y2)
    // reference point: (x3, y3)
    // point on line m2, c21 => y = m2 * x +  c21 => point (0,c21)
    //   so first point: (0,c21)

    centerPt.x = x2; centerPt.y = y2;
    refPt.x    = x3; refPt.y    = y3;
    if (parallelTo_XorYaxis2 == PARALLEL_TO_Y_AXIS){
        // x1-halfLineWidth, y1 (or y2- same thing)
        secondPt.x  = nearest(paramObj2[2]);  secondPt.y  = y1;
    }
    else if (parallelTo_XorYaxis2 == PARALLEL_TO_X_AXIS){
        // x1 (or x2- same thing), y1-halfLineWidth,
        secondPt.x  = x1;  secondPt.y  = nearest(paramObj2[2]);
    }
    else {
        int c21 = nearest(paramObj2[2]);
        secondPt.x  = 0;  secondPt.y  = c21;
    }

    boolean_T secondPtOnRight = is_RightOfLine_CtrToRef(refPt, centerPt, secondPt);

    boolean_T is_Valid_Point = (firstPtOnRight == secondPtOnRight);
    return is_Valid_Point;
}

void findPointOfIntersectionNormal(boolean_T useC11_notC12, OpDT *paramObj, int &xi, int &yi, Paral_T parallelTo_XorYaxis)
{
	OpDT tempVar1(0), tempVar2(0), tempVar6(0);
	DT tempVar7(0);

	// when useC11_notC12 is true
    // Perpendicular line: y=(-1/m1)x + c13
    // Parallel Line-1:    y=m1 * x + c11 
    // that gives, x = m1(c13-c11)/(m1*m1+1), get y from above Line-1

    // when useC11_notC12 is false, replace c11 with c12 in all above lines


    // m1 = paramObj[0]; c1 = paramObj[1]; c11 = paramObj[2]; c12 = paramObj[3]; c13 = paramObj[4];
    if (parallelTo_XorYaxis == PARALLEL_TO_Y_AXIS)
    {
        // for c11, it is (x1-halfLineWidth, y1 or y2)
        // for c12, it is (x1+halfLineWidth, y1 or y2)
        xi = nearest(paramObj[useC11_notC12? 2 : 3]);
        yi = nearest(paramObj[4]);

    }
    else if (parallelTo_XorYaxis == PARALLEL_TO_X_AXIS)
    {
        // for c11, it is (x1 or x2, y1-halfLineWidth)
        // for c12, it is (x1 or x2, y1+halfLineWidth)
        xi = nearest(paramObj[4]);
        yi = nearest(paramObj[useC11_notC12? 2 : 3]);			
    }
    else
    {
		tempVar1 = paramObj[4]; //c13 
		tempVar1 -= paramObj[useC11_notC12? 2 : 3]; //c13-c11 or C13-c12
		tempVar1 *= paramObj[0];//m1(c13-c11)

        tempVar2 = paramObj[0];//m1  
        tempVar2 *= paramObj[0]; //m1 * m1
        tempVar7 = 1;
        tempVar2 += tempVar7;// m1*m1 + 1

        lclDSPFixptDivide(tempVar6, tempVar1, tempVar2);//m1(c13-c11)/(m1*m1+1)
        xi = nearest(tempVar6);

		tempVar1 = paramObj[0];//m1  
		tempVar1 *= tempVar6;//m1 * x  
		tempVar1 += paramObj[useC11_notC12? 2 : 3];//m1 * x + c11; or m1 * x + c12;
        yi = nearest(tempVar1);
    }
}

void findPointOfIntersection(boolean_T isFirstLine, OpDT *paramObj1, OpDT *paramObj2, int &xi, int &yi,
    Paral_T parallelTo_XorYaxis1, Paral_T parallelTo_XorYaxis2,
    int x2, int y2)//(m1, c11, c21, m2, c12, c22)
{
    int idx;
	OpDT tempVar1(0), tempVar2(0), tempVar6(0);
    
	if (isFirstLine)
        idx = 2;
    else
        idx = 3;

    boolean_T first_YaxisP = (parallelTo_XorYaxis1 == PARALLEL_TO_Y_AXIS);
    boolean_T second_YaxisP = (parallelTo_XorYaxis2 == PARALLEL_TO_Y_AXIS);		

    if (first_YaxisP && second_YaxisP){
        // For idx=2 (top parallel lines)                    // For idx=3 (bottom parallel lines)
        //=======================================================================================

        //                     Line-1: x = x1-halfLineWidth        Line-1: x = x1+halfLineWidth  (here x1=x2=x3)
        //                     Line-2: x = x2-halfLineWidth        Line-1: x = x2+halfLineWidth  (here x1=x2=x3)

        //                     Point of itersection:          Point of itersection:
        //                       x = x1-halfLineWidth;         x = x1+halfLineWidth; 
        //                       y = y2;                       y = y2; (get any arbitrary point in between y1 and y3; so picking y2)

        // idx = 2: xi = x2-halfLineWidth = x1 - halfLineWidth (here x1=x2)
        // idx = 3: xi = x2+halfLineWidth = x1 + halfLineWidth (here x1=x2)
        xi = nearest(paramObj1[idx]);
        yi = y2;
    }
    else if (first_YaxisP){
        // For idx=2 (top parallel lines)                    // For idx=3 (bottom parallel lines)
        //=======================================================================================

        //                     Line-1: x = x1-halfLineWidth        Line-1: x = x1+halfLineWidth  (here x1=x2)
        //                     Line-2: y=m2 * x + c21              Line-2: y=m2 * x + c22

        //                     Point of itersection:          Point of itersection:
        //                       x = x1-halfLineWidth;         x = x1+halfLineWidth; 
        //                       y = m2 * x + c21;             y = m2 * x + c22

        // idx = 2: xi = x1 - halfLineWidth (here x1=x2)
        // idx = 3: xi = x1 + halfLineWidth (here x1=x2)
        xi = nearest(paramObj1[idx]);
        //yi = paramObj2[0]*xi + paramObj2[idx];
        lclAssign(tempVar2, xi); // do not use tempVar2=(int16_T)xi
        tempVar2 *= paramObj2[0];
        tempVar2 += paramObj2[idx];	
        yi = nearest(tempVar2);
    }
    else if (second_YaxisP){
        // For idx=2 (top parallel lines)                    // For idx=3 (bottom parallel lines)
        //=======================================================================================

        //                     Line-1: y=m1 * x + c11              Line-1: y=m1 * x + c12
        //                     Line-2: x = x2-halfLineWidth        Line-2: x = x2+halfLineWidth  (here x2=x3)

        //                     Point of itersection:          Point of itersection:
        //                       x = x2-halfLineWidth;         x = x2+halfLineWidth; 
        //                       y = m1 * x + c11;             y = m1 * x + c12

        // idx = 2: xi = x2-halfLineWidth (here x1=x2)
        // idx = 3: xi = x2+halfLineWidth (here x1=x2)
        xi = nearest(paramObj2[idx]);
        //yi = paramObj1[0]*xi + paramObj1[idx];
        lclAssign(tempVar2, xi); // do not use tempVar2 = (int16_T)xi;
        tempVar2 *= paramObj1[0];
        tempVar2 += paramObj1[idx];	
        yi = nearest(tempVar2);
    }
    else{
        // For idx=2 (top parallel lines)                    // For idx=3 (bottom parallel lines)
        //=======================================================================================

        //                     Line-1: y=m1 * x + c11         Line-1: y=m1 * x + c12
        //                     Line-2: y=m2 * x + c21         Line-2: y=m2 * x + c22

        //                     Point of itersection:          Point of itersection:
        //                       x = (c21-c11)/(m1-m2);         x = (c22-c12)/(m1-m2);
        //                       y = m1 * x + c11;              y = m1 * x + c12;

        // m1 = paramObj1[0]; c11 = paramObj1[2];             c12 = paramObj1[3];
        // m2 = paramObj2[0]; c21 = paramObj2[2];             c22 = paramObj2[3];
		tempVar1 = paramObj2[idx]; //idx=2, c21       idx=3, c22
		tempVar1 -= paramObj1[idx];//idx=2, c21-c11   idx=3, c22-c12  

        tempVar2 = paramObj1[0];//m1 (for both idx=1,2)
        tempVar2 -= paramObj2[0];//m1-m2 (for both idx=1,2)

        tempVar6 = 0;
        if (tempVar2 == tempVar6){ // both have same slopes
            // take nearly middle point x = x2; y = m1 * x + c11 (or c12 for idx=3)
            xi = x2;
            //yi = paramObj1[0]*xi + paramObj1[idx];
            lclAssign(tempVar2, xi); // do not use tempVar2 = (int16_T)xi;
            tempVar2 *= paramObj1[0];
            tempVar2 += paramObj1[idx];	
            yi = nearest(tempVar2);
        }
        else{

            lclDSPFixptDivide(tempVar6, tempVar1, tempVar2);//idx=1, tempVar1 = (c21-c11)/(m1-m2);   idx=2, tempVar1 = (c22-c12)/(m1-m2);
            xi = nearest(tempVar6);

			tempVar1 = paramObj1[0];//m1 (for both idx=1,2)
			tempVar1 *= tempVar6;// m1 * x (for both idx=1,2)
			tempVar1 += paramObj1[idx];// idx=2, m1 * x + c11;   idx=3, m1 * x + c12
            yi = nearest(tempVar1);
        }
    }
}

boolean_T is_RightOfLine_CtrToRef(XY_T ref, XY_T center, XY_T b)
{
    // checks if point b is right of Line drawn from Center to Reference point
    // if (ref.x >= 0 && b.x < 0)
    //     isRight = true;
    // elseif (ref.x == 0 && b.x == 0)
    //     isRight = ref.y > b.y;
    // else

    boolean_T isRight;
    // compute the cross product of vectors (center -> ref) x (center -> b)
    int det = (ref.x-center.x) * (b.y-center.y) - (b.x - center.x) * (ref.y - center.y);
    if (det < 0) {
        isRight = true;
    }
    else if (det > 0) {
        isRight = false;
    }
    else { // (det == 0)
        // points ref and b are on the same line from the center
        // check which point is closer to the center
        int d1 = (ref.x-center.x) * (ref.x-center.x) + (ref.y-center.y) * (ref.y-center.y);
        int d2 = (b.x-center.x) * (b.x-center.x) + (b.y-center.y) * (b.y-center.y);
        isRight = d1 > d2;
    }

    return isRight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void convertLinePts2PolygonPts()
{
    int X1, Y1, X2, Y2;
    int jj, kk;
	OpDT tempVar1(0), tempVar2(0);
	OpDT tempVar4[] = { 0, 0, 0, 0, 0 };
	OpDT tempVar5[] = { 0, 0, 0, 0, 0 };

    Paral_T parallelTo_XorYaxis1 = PARALLEL_TO_NO_AXIS, parallelTo_XorYaxis2 = PARALLEL_TO_NO_AXIS;
    //const PT* mPts = mPts;
    // thick or non-thick line/polygon:  mNumSubShape is the number of points ((x,y) pair) in each row of point port
    int len = this->mNumSubShape*2; // length of each point input row (here shape is LINE)
    int pointDWLen = this->mNumSubShape*4;
    for (int mn = 0; mn < this->mNumShape; mn++)
    {
        int32_T x1 = ToIntCoordinate<VT>(mPts[mn])-1;             //mPts[mn + 0*mNumShape]
        int32_T y1 = ToIntCoordinate<VT>(mPts[mn+this->mNumShape])-1;   //mPts[mn + 1*mNumShape]
        int32_T x2 = ToIntCoordinate<VT>(mPts[mn+2*this->mNumShape])-1; //mPts[mn + 2*mNumShape]
        int32_T y2 = ToIntCoordinate<VT>(mPts[mn+3*this->mNumShape])-1; //mPts[mn + 3*mNumShape]

        int halfLineWidth = (this->mLineWidthPtr[0]/2);

        getLineParams(-1, x1, y1, x2, y2, halfLineWidth, tempVar4, parallelTo_XorYaxis1);// -1 means normal is at left point (x1,y1)
        // tempVar4[0] = m1, tempVar4[1] = c1, tempVar4[2] = c11, tempVar4[3] = c12, tempVar4[4] = c13
        // see "NOTE : LINEXYZ" for explanation of [m1 c1 c11 c12 c13]

        // (X1, Y1): point of intersection between line (m1, c11) and (-1/m1, c13)
        findPointOfIntersectionNormal(true, tempVar4, X1, Y1, parallelTo_XorYaxis1);// true means use c11
        jj = 0;
        mPtsDW[mn + (jj++)*this->mNumShape] = (PT)X1;
        mPtsDW[mn + (jj++)*this->mNumShape] = (PT)Y1;
        // (X2, Y2): point of intersection between line (m1, c12) and (-1/m1, c13)
        findPointOfIntersectionNormal(false, tempVar4, X2, Y2, parallelTo_XorYaxis1);// false means use c12
        kk = pointDWLen-1;
        mPtsDW[mn + (kk--)*this->mNumShape] = (PT)Y2;// note: this is Y2
        mPtsDW[mn + (kk--)*this->mNumShape] = (PT)X2;		
        if (len ==4) // special codepath for 2 point line
        {
            getLineParams(+1, x1, y1, x2, y2, halfLineWidth, tempVar4, parallelTo_XorYaxis1);// +1 means normal is at right point (x2,y2)
            // tempVar4[0] = m1, tempVar4[1] = c1, tempVar4[2] = c11, tempVar4[3] = c12, tempVar4[4] = c13
            // see "NOTE : LINEXYZ" for explanation of [m1 c1 c11 c12 c13]

            // (X1, Y1): point of intersection between line (m1, c11) and (-1/m1, c13)
            findPointOfIntersectionNormal(true, tempVar4, X1, Y1, parallelTo_XorYaxis1);// true means use c11

            mPtsDW[mn + (jj++)*this->mNumShape] = (PT)X1;
            mPtsDW[mn + (jj++)*this->mNumShape] = (PT)Y1;
            // (X2, Y2): point of intersection between line (m1, c12) and (-1/m1, c13)
            findPointOfIntersectionNormal(false, tempVar4, X2, Y2, parallelTo_XorYaxis1);// false means use c12

            mPtsDW[mn + (kk--)*this->mNumShape] = (PT)Y2;// note: this is Y2
            mPtsDW[mn + (kk--)*this->mNumShape] = (PT)X2;	
        }
        else
        {
            // for 2 point line, the following loop is not executed
            for (int ii=4;ii<len;ii+=2) 
            {
                int idx;
                if (ii<len){
                    idx = ii;
                }
                else {
                    // wrapping to first ones
                    idx = ii-len;
                }
                int x3 = ToIntCoordinate<VT>(mPts[mn + idx*this->mNumShape])-1;
                int y3 = ToIntCoordinate<VT>(mPts[mn + (idx+1)*this->mNumShape])-1;
                int rightNormal = 0; // no need to get normal's info (c13)
                if (ii==(len-2)) rightNormal = +1; // that measn get c13 which is normal at right end of line
                getLineParams(rightNormal, x2, y2, x3, y3, halfLineWidth, tempVar5, parallelTo_XorYaxis2);
                // tempVar5[0] = m2, tempVar5[1] = c2, tempVar5[2] = c21, tempVar5[3] = c22, tempVar5[4] = c23
                // see "NOTE : LINEXYZ" for explanation of [m2 c2 c21 c22 c23]

                // find if c11 goes with (c21  or c22)
                boolean_T isValidPairs = isValidPair(x1, y1, x2, y2, x3, y3, tempVar4, tempVar5, parallelTo_XorYaxis1, parallelTo_XorYaxis2);
                if (isValidPairs){
                    // no need to swap
                    // c11 pairs with c21, c12 pairs with c22
                    // that means, tempVar4[2] pairs with tempVar5[2]
                    //             tempVar4[3] pairs with tempVar5[3]
                    // c11_pair = c21;
                    // c12_pair = c22;
                }
                else {						
                    // c11_pair = c22 (after below swap it is c21);
                    // c12_pair = c21 (after below swap it is c22);
                    // swap tempVar5[2] and tempVar5[3]		
					tempVar1 = tempVar5[2];
                    tempVar2 = tempVar5[3];
                    tempVar5[2] = tempVar2;
                    tempVar5[3]	= tempVar1;
                }			

                // iPt1 = findPointOfIntersection(m1, c11, m2, c11_pair=c21);
                findPointOfIntersection(true, tempVar4, tempVar5, X1, Y1, parallelTo_XorYaxis1, parallelTo_XorYaxis2, x2, y2);// true means work on c11 and c21
                // iPt2 = findPointOfIntersection(m1, c12, m2, c12_pair=c22);
                findPointOfIntersection(false, tempVar4, tempVar5, X2, Y2, parallelTo_XorYaxis1, parallelTo_XorYaxis2, x2, y2);// false means work on c12 and c22
                // Save output
                mPtsDW[mn + (jj++)*this->mNumShape] = (PT)X1;
                mPtsDW[mn + (jj++)*this->mNumShape] = (PT)Y1;

                mPtsDW[mn + (kk--)*this->mNumShape] = (PT)Y2; // note: this is Y2
                mPtsDW[mn + (kk--)*this->mNumShape] = (PT)X2;

                // set values for next iteration
                x1 = x2;
                y1 = y2;

                x2 = x3;
                y2 = y3;

                tempVar4[0] = tempVar5[0]; // m1 = m2
                tempVar4[1] = tempVar5[1]; // c1 = c2;
                tempVar4[2] = tempVar5[2]; // c11 = c21
                tempVar4[3] = tempVar5[3]; // c12 = c22
                tempVar4[4] = tempVar5[4]; // c13 = c23

                parallelTo_XorYaxis1 = parallelTo_XorYaxis2;

            }

            // (X1, Y1): point of intersection between line (m1, c11) and (-1/m1, c13)
            findPointOfIntersectionNormal(true, tempVar4, X1, Y1, parallelTo_XorYaxis2);// true means work on c11 and c21
            mPtsDW[mn + (jj++)*this->mNumShape] = (PT)X1;
            mPtsDW[mn + (jj++)*this->mNumShape] = (PT)Y1;
            // (X2, Y2): point of intersection between line (m1, c12) and (-1/m1, c13)
            findPointOfIntersectionNormal(false, tempVar4, X2, Y2, parallelTo_XorYaxis2);// false means work on c12 and c22
            mPtsDW[mn + (kk--)*this->mNumShape] = (PT)Y2;// note: this is Y2
            mPtsDW[mn + (kk--)*this->mNumShape] = (PT)X2;	
        }

        //mPts += mNumSubShape*2;
        //mPtsDW += mNumSubShape*4;

    }// end of "for (int mn ..." (next shape)

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void converPolygonPts2TwoPolygonPts()
{
    int X1, Y1, X2, Y2;
    int jj, kk;
	OpDT tempVar1(0), tempVar2(0);
	OpDT tempVar4[] = { 0, 0, 0, 0, 0 };
	OpDT tempVar5[] = { 0, 0, 0, 0, 0 };

    Paral_T parallelTo_XorYaxis1 = PARALLEL_TO_NO_AXIS, parallelTo_XorYaxis2 = PARALLEL_TO_NO_AXIS;
    //const PT* mPts = mPts;
    // thick or non-thick line/polygon:  mNumSubShape is the number of points ((x,y) pair) in each row of point port
    int len = this->mNumSubShape*2; // length of each point input row (here shape is Polygon)
    int pointDWLen = this->mNumSubShape*4;
    for (int mn = 0; mn < this->mNumShape; mn++)
    {
        int32_T x1 = ToIntCoordinate<VT>(mPts[mn])-1;                   //mPts[mn + 0*mNumShape]
        int32_T y1 = ToIntCoordinate<VT>(mPts[mn+this->mNumShape])-1;   //mPts[mn + 1*mNumShape]
        int32_T x2 = ToIntCoordinate<VT>(mPts[mn+2*this->mNumShape])-1; //mPts[mn + 2*mNumShape]
        int32_T y2 = ToIntCoordinate<VT>(mPts[mn+3*this->mNumShape])-1; //mPts[mn + 3*mNumShape]

        int halfLineWidth = (this->mLineWidthPtr[0]/2);

        getLineParams(0, x1, y1, x2, y2, halfLineWidth, tempVar4, parallelTo_XorYaxis1);// 0 means no normal (neither at left point (x1,y1), nor at right point (x2,y2))
        // tempVar4[0] = m1, tempVar4[1] = c1, tempVar4[2] = c11, tempVar4[3] = c12, tempVar4[4] = c13
        // see "NOTE : LINEXYZ" for explanation of [m1 c1 c11 c12 c13]
        jj = 0;
        kk = pointDWLen/2;

        for (int ii=4;ii<len+4;ii+=2)
        {
            int idx;
            if (ii<len){
                idx = ii;
            }
            else {
                // wrapping to first ones
                idx = ii-len;
            }
            int x3 = ToIntCoordinate<VT>(mPts[mn + idx*this->mNumShape])-1;
            int y3 = ToIntCoordinate<VT>(mPts[mn + (idx+1)*this->mNumShape])-1;
            getLineParams(0, x2, y2, x3, y3, halfLineWidth, tempVar5, parallelTo_XorYaxis2);// 0 means no normal (neither at left point (x2,y2), nor at right point (x3,y3))
            // tempVar5[0] = m2, tempVar5[1] = c2, tempVar5[2] = c21, tempVar5[3] = c22, tempVar5[4] = c23
            // see "NOTE : LINEXYZ" for explanation of [m2 c2 c21 c22 c23]

            // find if c11 goes with (c21  or c22)
            boolean_T isValidPairs = isValidPair(x1, y1, x2, y2, x3, y3, tempVar4, tempVar5, parallelTo_XorYaxis1, parallelTo_XorYaxis2);
            if (isValidPairs){
                // no need to swap
                // c11 pairs with c21, c12 pairs with c22
                // that means, tempVar4[2] pairs with tempVar5[2]
                //             tempVar4[3] pairs with tempVar5[3]
                // c11_pair = c21;
                // c12_pair = c22;
            }
            else {
                // c11 pairs with c22, c12 pairs with c21
                // c11_pair = c22 (after below swap it is c21);
                // c12_pair = c21 (after below swap it is c22);
                // swap tempVar5[2] and tempVar5[3]		
				tempVar1 = tempVar5[2];
                tempVar2 = tempVar5[3];
                tempVar5[2] = tempVar2;
                tempVar5[3]	= tempVar1;
            }			

            // iPt1 = findPointOfIntersection(m1, c11, m2, c11_pair=c21);
            findPointOfIntersection(true, tempVar4, tempVar5, X1, Y1, parallelTo_XorYaxis1, parallelTo_XorYaxis2, x2, y2);// true means work on c11 and c21
            // iPt2 = findPointOfIntersection(m1, c12, m2, c12_pair=c22);
            findPointOfIntersection(false, tempVar4, tempVar5, X2, Y2, parallelTo_XorYaxis1, parallelTo_XorYaxis2, x2, y2);// false means work on c12 and c22
            // Save output
            mPtsDW[mn + (jj++)*this->mNumShape] = (PT)X1;
            mPtsDW[mn + (jj++)*this->mNumShape] = (PT)Y1;

            mPtsDW[mn + (kk++)*this->mNumShape] = (PT)X2; 
            mPtsDW[mn + (kk++)*this->mNumShape] = (PT)Y2;

            // set values for next iteration
            x1 = x2;
            y1 = y2;

            x2 = x3;
            y2 = y3;

            tempVar4[0] = tempVar5[0]; // m1 = m2
            tempVar4[1] = tempVar5[1]; // c1 = c2;
            tempVar4[2] = tempVar5[2]; // c11 = c21
            tempVar4[3] = tempVar5[3]; // c12 = c22
            tempVar4[4] = tempVar5[4]; // c13 = c23

            parallelTo_XorYaxis1 = parallelTo_XorYaxis2;
        }

        //mPts += mNumSubShape*2;
        //mPtsDW += mNumSubShape*4;

    }// end of "for (int mn ..." (next shape)
}

#endif
