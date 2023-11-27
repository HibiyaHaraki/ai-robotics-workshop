//
// File: _coder_line_detection_mex.h
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

#ifndef _CODER_LINE_DETECTION_MEX_H
#define _CODER_LINE_DETECTION_MEX_H

// Include Files
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

// Function Declarations
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS();

void unsafe_line_detection_mexFunction(int32_T nlhs, mxArray *plhs[2],
                                       int32_T nrhs, const mxArray *prhs[1]);

#endif
//
// File trailer for _coder_line_detection_mex.h
//
// [EOF]
//
