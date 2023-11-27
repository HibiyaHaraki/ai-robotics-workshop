//
// File: line_detection.h
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 08-Apr-2021 15:32:32
//

#ifndef LINE_DETECTION_H
#define LINE_DETECTION_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void line_detection(const unsigned char I_data[], const int I_size[3],
                           float predictedPosNorm[2], unsigned char Iout_data[],
                           int Iout_size[3]);

void line_detection_init();

#endif
//
// File trailer for line_detection.h
//
// [EOF]
//
