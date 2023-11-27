//
// File: predict.h
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

#ifndef PREDICT_H
#define PREDICT_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

class mynet_new0_0;

// Function Declarations
namespace coder {
void DeepLearningNetwork_predict(mynet_new0_0 *obj,
                                 const unsigned char varargin_1[172800],
                                 float varargout_1[2]);

}

#endif
//
// File trailer for predict.h
//
// [EOF]
//
