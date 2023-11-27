
///////////////////////////////////////////////////////////////////////////////
// This file contains helpers for cvstDraw


//  Copyright 2019 The MathWorks, Inc.
///////////////////////////////////////////////////////////////////////////////

#include "cvstDraw.hpp"

void multiplyEqual(real_T *out, int_T outIdx, const real_T *in, int_T inIdx)
{
    out[outIdx] *= in[inIdx];
}

void multiplyEqual(real32_T *out, int_T outIdx, const real32_T *in, int_T inIdx)
{
    out[outIdx] *= in[inIdx];
}

void multiplyEqual(uint8_T *out, int_T outIdx, const real32_T *in, int_T inIdx)
{
    real32_T tmp = out[outIdx];
    tmp *= (real32_T)in[inIdx];
    out[outIdx] = (uint8_T)tmp;
}

void multiplyEqual(uint16_T *out, int_T outIdx, const real32_T *in, int_T inIdx)
{
    real32_T tmp = out[outIdx];
    tmp *= (real32_T)in[inIdx];
    out[outIdx] = (uint16_T)tmp;
}

void multiplyEqual(int16_T *out, int_T outIdx, const real32_T *in, int_T inIdx)
{
    real32_T tmp = out[outIdx];
    tmp *= (real32_T)in[inIdx];
    out[outIdx] = (uint16_T)tmp;
}