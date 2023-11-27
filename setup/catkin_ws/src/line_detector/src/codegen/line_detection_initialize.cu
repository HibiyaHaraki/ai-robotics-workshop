//
// File: line_detection_initialize.cu
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 08-Apr-2021 15:32:32
//

// Include Files
#include "line_detection_initialize.h"
#include "line_detection.h"
#include "line_detection_data.h"

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void line_detection_initialize()
{
  line_detection_init();
  cudaGetLastError();
  isInitialized_line_detection = true;
}

//
// File trailer for line_detection_initialize.cu
//
// [EOF]
//
