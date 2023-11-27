//
// File: _coder_line_detection_api.h
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

#ifndef _CODER_LINE_DETECTION_API_H
#define _CODER_LINE_DETECTION_API_H

// Include Files
#include "emlrt.h"
#include "tmwtypes.h"
#include <algorithm>
#include <cstring>

// Variable Declarations
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

// Function Declarations
void line_detection(uint8_T I_data[], int32_T I_size[3],
                    real32_T predictedPosNorm[2], uint8_T Iout_data[],
                    int32_T Iout_size[3]);

void line_detection_api(const mxArray *const prhs[1], int32_T nlhs,
                        const mxArray *plhs[2]);

void line_detection_atexit();

void line_detection_initialize();

void line_detection_terminate();

void line_detection_xil_shutdown();

void line_detection_xil_terminate();

#endif
//
// File trailer for _coder_line_detection_api.h
//
// [EOF]
//
