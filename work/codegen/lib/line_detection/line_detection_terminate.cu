//
// File: line_detection_terminate.cu
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

// Include Files
#include "line_detection_terminate.h"
#include "line_detection_data.h"
#include <cstdio>

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void line_detection_terminate()
{
  cudaError_t errCode;
  errCode = cudaGetLastError();
  if (errCode != cudaSuccess) {
    fprintf(stderr, "ERR[%d] %s:%s\n", errCode, cudaGetErrorName(errCode),
            cudaGetErrorString(errCode));
    exit(errCode);
  }
  isInitialized_line_detection = false;
}

//
// File trailer for line_detection_terminate.cu
//
// [EOF]
//
