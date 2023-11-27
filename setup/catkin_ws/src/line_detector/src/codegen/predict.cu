//
// File: predict.cu
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 08-Apr-2021 15:32:32
//

// Include Files
#include "predict.h"
#include "DeepLearningNetwork.h"
#include "line_detection_internal_types.h"
#include "MWCudaDimUtility.hpp"

// Type Definitions
struct cell_wrap_13 {
  float f1[2];
};

struct cell_wrap_9 {
  float f1[172800];
};

struct cell_wrap_12 {
  float f1[172800];
};

// Function Declarations
static __global__ void
DeepLearningNetwork_predict_kernel40(const unsigned char varargin_1[172800],
                                     cell_wrap_9 dataInputsSingle[1]);

static __global__ void
DeepLearningNetwork_predict_kernel41(const cell_wrap_9 dataInputsSingle[1],
                                     cell_wrap_12 inMiniBatchGroup[1]);

static __global__ void
DeepLearningNetwork_predict_kernel42(const cell_wrap_13 outMiniBatchGroup[1],
                                     float varargout_1[2]);

// Function Definitions
//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char varargin_1[172800]
//                cell_wrap_9 dataInputsSingle[1]
// Return Type  : void
//
static __global__
    __launch_bounds__(512, 1) void DeepLearningNetwork_predict_kernel40(
        const unsigned char varargin_1[172800], cell_wrap_9 dataInputsSingle[1])
{
  unsigned long threadId;
  int i;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  i = static_cast<int>(threadId);
  if (i < 172800) {
    dataInputsSingle[0].f1[i] = static_cast<float>(varargin_1[i]);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const cell_wrap_9 dataInputsSingle[1]
//                cell_wrap_12 inMiniBatchGroup[1]
// Return Type  : void
//
static __global__
    __launch_bounds__(512, 1) void DeepLearningNetwork_predict_kernel41(
        const cell_wrap_9 dataInputsSingle[1], cell_wrap_12 inMiniBatchGroup[1])
{
  unsigned long threadId;
  int i;
  int i1;
  int p;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  i = static_cast<int>(threadId % 320UL);
  threadId = (threadId - static_cast<unsigned long>(i)) / 320UL;
  i1 = static_cast<int>(threadId % 180UL);
  threadId = (threadId - static_cast<unsigned long>(i1)) / 180UL;
  p = static_cast<int>(threadId);
  if ((static_cast<int>((static_cast<int>(p < 3)) &&
                        (static_cast<int>(i1 < 180)))) &&
      (static_cast<int>(i < 320))) {
    inMiniBatchGroup[0].f1[(i + 320 * i1) + 57600 * p] =
        dataInputsSingle[0].f1[(i1 + 180 * i) + 57600 * p];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const cell_wrap_13 outMiniBatchGroup[1]
//                float varargout_1[2]
// Return Type  : void
//
static __global__
    __launch_bounds__(32, 1) void DeepLearningNetwork_predict_kernel42(
        const cell_wrap_13 outMiniBatchGroup[1], float varargout_1[2])
{
  unsigned long threadId;
  int i;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  i = static_cast<int>(threadId);
  if (i < 2) {
    varargout_1[i] = outMiniBatchGroup[0].f1[i];
  }
}

//
// Arguments    : mynet_new0_0 *obj
//                const unsigned char varargin_1[172800]
//                float varargout_1[2]
// Return Type  : void
//
namespace coder {
void DeepLearningNetwork_predict(mynet_new0_0 *obj,
                                 const unsigned char varargin_1[172800],
                                 float varargout_1[2])
{
  cell_wrap_12(*gpu_inMiniBatchGroup)[1];
  cell_wrap_13(*gpu_outMiniBatchGroup)[1];
  cell_wrap_9(*gpu_dataInputsSingle)[1];
  float(*gpu_varargout_1)[2];
  unsigned char(*gpu_varargin_1)[172800];
  cudaMalloc(&gpu_varargout_1, 8UL);
  cudaMalloc(&gpu_outMiniBatchGroup, 8UL);
  cudaMalloc(&gpu_inMiniBatchGroup, 691200UL);
  cudaMalloc(&gpu_dataInputsSingle, 691200UL);
  cudaMalloc(&gpu_varargin_1, 172800UL);
  cudaMemcpy(*gpu_varargin_1, varargin_1, 172800UL, cudaMemcpyHostToDevice);
  DeepLearningNetwork_predict_kernel40<<<dim3(338U, 1U, 1U),
                                         dim3(512U, 1U, 1U)>>>(
      *gpu_varargin_1, *gpu_dataInputsSingle);
  DeepLearningNetwork_predict_kernel41<<<dim3(338U, 1U, 1U),
                                         dim3(512U, 1U, 1U)>>>(
      *gpu_dataInputsSingle, *gpu_inMiniBatchGroup);
  cudaMemcpy(obj->getInputDataPointer(0), (*gpu_inMiniBatchGroup)[0].f1,
             obj->getLayerOutputSize(0, 0), cudaMemcpyDeviceToDevice);
  obj->predict();
  cudaMemcpy((*gpu_outMiniBatchGroup)[0].f1, obj->getLayerOutput(25, 0),
             obj->getLayerOutputSize(25, 0), cudaMemcpyDeviceToDevice);
  DeepLearningNetwork_predict_kernel42<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_outMiniBatchGroup, *gpu_varargout_1);
  cudaMemcpy(varargout_1, *gpu_varargout_1, 8UL, cudaMemcpyDeviceToHost);
  cudaFree(*gpu_varargin_1);
  cudaFree(*gpu_dataInputsSingle);
  cudaFree(*gpu_inMiniBatchGroup);
  cudaFree(*gpu_outMiniBatchGroup);
  cudaFree(*gpu_varargout_1);
}

} // namespace coder

//
// File trailer for predict.cu
//
// [EOF]
//
