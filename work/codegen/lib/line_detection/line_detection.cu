//
// File: line_detection.cu
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

// Include Files
#include "line_detection.h"
#include "DeepLearningNetwork.h"
#include "line_detection_data.h"
#include "line_detection_initialize.h"
#include "line_detection_internal_types.h"
#include "predict.h"
#include "MWCudaDimUtility.hpp"
#include "MWLaunchParametersUtilities.hpp"
#include "insertShapeUtilsCore_api.hpp"
#include <cmath>

// Variable Definitions
static mynet_new0_0 lineDetObj;

static bool lineDetObj_not_empty;

// Function Declarations
static __global__ void
line_detection_kernel1(const unsigned char I_data[], const int I_size[3],
                       const int img_size[3], const int b_I_size,
                       const int plast, unsigned char img_data[2764800]);

static __global__ void line_detection_kernel10(const double aux1_data[1440],
                                               const int in_rows,
                                               const double scale_idx_0,
                                               const double kwidthRow,
                                               double ipRowIndices_data[2880],
                                               double rowWeights_data[2880]);

static __global__ void line_detection_kernel11(const int plast,
                                               double ipColIndices_data[9280]);

static __global__ void line_detection_kernel12(const int plast,
                                               double colWeights_data[9280]);

static __global__ void line_detection_kernel13(const double aux2_data[2560],
                                               const int in_cols,
                                               const double scale_idx_1,
                                               const double kwidthCol,
                                               double ipColIndices_data[9280],
                                               double colWeights_data[9280]);

static __global__ void
line_detection_kernel14(const double rowWeights_data[2880],
                        double rowWeightsTotal[180]);

static __global__ void
line_detection_kernel15(const double rowWeights_data[2880], const int in_rows,
                        double rowWeightsTotal[180]);

static __global__ void
line_detection_kernel16(const double colWeights_data[9280],
                        double colWeightsTotal[320]);

static __global__ void
line_detection_kernel17(const double colWeights_data[9280], const int in_rows,
                        double colWeightsTotal[320]);

static __global__ void line_detection_kernel18(const int img_size[3],
                                               int partialResize_size[3]);

static __global__ void line_detection_kernel19(
    const double colWeightsTotal[320], const double colWeights_data[9280],
    const unsigned char img_data[2764800], const double ipColIndices_data[9280],
    const int img_size[3], const int partialResize_size[3],
    const double kwidthCol, const int plast,
    unsigned char partialResize_data[691200]);

static __global__ void line_detection_kernel2(const unsigned char I_data[],
                                              const int I_size,
                                              unsigned char img_data[2764800]);

static __global__ void line_detection_kernel20(
    const double rowWeightsTotal[180], const double rowWeights_data[2880],
    const unsigned char partialResize_data[691200],
    const int partialResize_size[3], const double ipRowIndices_data[2880],
    const double kwidthRow, unsigned char out[172800]);

static __global__ void line_detection_kernel21(const int img_size[3],
                                               int partialResize_size[3]);

static __global__ void line_detection_kernel22(
    const double rowWeightsTotal[180], const double rowWeights_data[2880],
    const unsigned char img_data[2764800], const int img_size[3],
    const double ipRowIndices_data[2880], const int partialResize_size[3],
    const double kwidthRow, const int plast,
    unsigned char partialResize_data[691200]);

static __global__ void line_detection_kernel23(
    const double colWeightsTotal[320], const double colWeights_data[9280],
    const unsigned char partialResize_data[691200],
    const int partialResize_size[3], const double ipColIndices_data[9280],
    const double kwidthCol, unsigned char out[172800]);

static __global__ void line_detection_kernel24(const short sz[3],
                                               int positionOut_data[4]);

static __global__ void line_detection_kernel25(const short sz[3],
                                               int positionOut_data[4]);

static __global__ void line_detection_kernel26(const int plast,
                                               const float predictedPosNorm[2],
                                               int positionOut_data[4],
                                               float predictedPos[2]);

static __global__ void line_detection_kernel27(const int img_size[3],
                                               short sz[3]);

static __global__ void line_detection_kernel28(const int sz,
                                               unsigned char img_data[2764800]);

static __global__ void
line_detection_kernel29(const short pixCountSize,
                        unsigned char pixCount_data[1280]);

static __global__ void
line_detection_kernel3(const unsigned char img_data[2764800],
                       const int img_size[3], const int b_img_size[3],
                       const int plast, const int in_rows,
                       unsigned char b_img_data[2764800]);

static __global__ void line_detection_kernel30(const unsigned char color[3],
                                               unsigned char b_color[3]);

static __global__ void line_detection_kernel31(const float predictedPos[2],
                                               int positionOut[3]);

static __global__ void line_detection_kernel32(int positionOut[3]);

static __global__ void line_detection_kernel33(const short tmpRGB_size[3],
                                               short sz[3]);

static __global__ void line_detection_kernel34(const int sz,
                                               unsigned char img_data[2764800]);

static __global__ void
line_detection_kernel35(const short pixCountSize,
                        unsigned char pixCount_data[1280]);

static __global__ void line_detection_kernel36(const unsigned char color[3],
                                               unsigned char b_color[3]);

static __global__ void
line_detection_kernel37(const unsigned char img_data[2764800],
                        const short out_size[3], const int Iout_size[3],
                        const int b_out_size, const int c_out_size,
                        unsigned char Iout_data[]);

static __global__ void
line_detection_kernel38(const unsigned char img_data[2764800],
                        const short out_size[3], const short b_out_size[3],
                        const int plast, const int in_rows,
                        unsigned char b_img_data[2764800]);

static __global__ void
line_detection_kernel39(const unsigned char img_data[2764800],
                        const int tmpRGB_size, unsigned char Iout_data[]);

static __global__ void
line_detection_kernel4(const unsigned char img_data[2764800],
                       const int img_size, unsigned char b_img_data[2764800]);

static __global__ void line_detection_kernel5(const int img_size[3],
                                              short sz[3]);

static __global__ void line_detection_kernel6(const int in_rows,
                                              const int plast,
                                              double aux1_data[1440]);

static __global__ void line_detection_kernel7(const int in_cols,
                                              const int plast,
                                              double aux2_data[2560]);

static __global__ void line_detection_kernel8(const int plast,
                                              double ipRowIndices_data[2880]);

static __global__ void line_detection_kernel9(const int plast,
                                              double rowWeights_data[2880]);

// Function Definitions
//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char I_data[]
//                const int I_size[3]
//                const int img_size[3]
//                const int b_I_size
//                const int plast
//                unsigned char img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel1(
    const unsigned char I_data[], const int I_size[3], const int img_size[3],
    const int b_I_size, const int plast, unsigned char img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = 3UL * ((static_cast<unsigned long>(b_I_size) + 1UL) *
                   (static_cast<unsigned long>(plast - 1) + 1UL)) -
            1UL;
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    unsigned long tmpIndex;
    int colIndices;
    int k;
    int rowIndices;
    colIndices = static_cast<int>(idx % 3UL);
    tmpIndex = (idx - static_cast<unsigned long>(colIndices)) / 3UL;
    rowIndices = static_cast<int>(tmpIndex %
                                  (static_cast<unsigned long>(b_I_size) + 1UL));
    tmpIndex = (tmpIndex - static_cast<unsigned long>(rowIndices)) /
               (static_cast<unsigned long>(b_I_size) + 1UL);
    k = static_cast<int>(tmpIndex);
    img_data[((static_cast<int>(static_cast<short>(k + 1)) +
               img_size[0] *
                   (static_cast<int>(static_cast<short>(rowIndices + 1)) - 1)) +
              img_size[0] * img_size[1] * colIndices) -
             1] = I_data
        [(colIndices +
          3 * (static_cast<int>(static_cast<short>(rowIndices + 1)) - 1)) +
         3 * I_size[1] * (static_cast<int>(static_cast<short>(k + 1)) - 1)];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double aux1_data[1440]
//                const int in_rows
//                const double scale_idx_0
//                const double kwidthRow
//                double ipRowIndices_data[2880]
//                double rowWeights_data[2880]
// Return Type  : void
//
static __global__ __launch_bounds__(192, 1) void line_detection_kernel10(
    const double aux1_data[1440], const int in_rows, const double scale_idx_0,
    const double kwidthRow, double ipRowIndices_data[2880],
    double rowWeights_data[2880])
{
  unsigned long threadId;
  int rowIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  rowIdx = static_cast<int>(threadId);
  if (rowIdx < 180) {
    int colIndices;
    colIndices = static_cast<int>(ceil(kwidthRow));
    for (int k{0}; k < colIndices; k++) {
      double absx;
      double absx2;
      double sumVal;
      int b_y;
      int l;
      int rowIndices;
      sumVal = (static_cast<double>(rowIdx) + 1.0) / scale_idx_0 +
               0.5 * (1.0 - 1.0 / scale_idx_0);
      rowIndices = static_cast<int>(floor(sumVal - kwidthRow / 2.0));
      sumVal -= static_cast<double>(rowIndices + k) + 1.0;
      if (scale_idx_0 < 1.0) {
        sumVal *= scale_idx_0;
      }
      absx = fabs(sumVal);
      absx2 = absx * absx;
      sumVal = pow(absx, 3.0);
      sumVal = ((1.5 * sumVal - 2.5 * absx2) + 1.0) *
                   static_cast<double>(absx <= 1.0) +
               (((-0.5 * sumVal + 2.5 * absx2) - 4.0 * absx) + 2.0) *
                   static_cast<double>((static_cast<int>(1.0 < absx)) &&
                                       (static_cast<int>(absx <= 2.0)));
      if (scale_idx_0 < 1.0) {
        rowWeights_data[rowIdx + 180 * k] = scale_idx_0 * sumVal;
      } else {
        rowWeights_data[rowIdx + 180 * k] = sumVal;
      }
      b_y = in_rows << 1;
      rowIndices = (rowIndices + k) + 1;
      l = rowIndices - 1;
      if (b_y == 0) {
        if (rowIndices - 1 == 0) {
          l = 0;
        }
      } else if (rowIndices - 1 == 0) {
        l = 0;
      } else {
        l = static_cast<int>(fmod(static_cast<double>(rowIndices) - 1.0,
                                  static_cast<double>(b_y)));
        if ((static_cast<int>(l != 0)) &&
            (static_cast<int>(rowIndices - 1 < 0))) {
          l += b_y;
        }
      }
      ipRowIndices_data[rowIdx + 180 * k] = aux1_data[l];
    }
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int plast
//                double ipColIndices_data[9280]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel11(
    const int plast, double ipColIndices_data[9280])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(320 * plast - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    ipColIndices_data[oldIdx] = 0.0;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int plast
//                double colWeights_data[9280]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel12(
    const int plast, double colWeights_data[9280])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(320 * plast - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    colWeights_data[oldIdx] = 0.0;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double aux2_data[2560]
//                const int in_cols
//                const double scale_idx_1
//                const double kwidthCol
//                double ipColIndices_data[9280]
//                double colWeights_data[9280]
// Return Type  : void
//
static __global__ __launch_bounds__(320, 1) void line_detection_kernel13(
    const double aux2_data[2560], const int in_cols, const double scale_idx_1,
    const double kwidthCol, double ipColIndices_data[9280],
    double colWeights_data[9280])
{
  unsigned long threadId;
  int colIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  colIdx = static_cast<int>(threadId);
  if (colIdx < 320) {
    int rowIndices;
    rowIndices = static_cast<int>(ceil(kwidthCol));
    for (int k{0}; k < rowIndices; k++) {
      double absx;
      double absx2;
      double sumVal;
      int b_y;
      int colIndices;
      int l;
      sumVal = (static_cast<double>(colIdx) + 1.0) / scale_idx_1 +
               0.5 * (1.0 - 1.0 / scale_idx_1);
      colIndices = static_cast<int>(floor(sumVal - kwidthCol / 2.0));
      sumVal -= static_cast<double>(colIndices + k) + 1.0;
      if (scale_idx_1 < 1.0) {
        sumVal *= scale_idx_1;
      }
      absx = fabs(sumVal);
      absx2 = absx * absx;
      sumVal = pow(absx, 3.0);
      sumVal = ((1.5 * sumVal - 2.5 * absx2) + 1.0) *
                   static_cast<double>(absx <= 1.0) +
               (((-0.5 * sumVal + 2.5 * absx2) - 4.0 * absx) + 2.0) *
                   static_cast<double>((static_cast<int>(1.0 < absx)) &&
                                       (static_cast<int>(absx <= 2.0)));
      if (scale_idx_1 < 1.0) {
        colWeights_data[colIdx + 320 * k] = scale_idx_1 * sumVal;
      } else {
        colWeights_data[colIdx + 320 * k] = sumVal;
      }
      b_y = in_cols << 1;
      colIndices = (colIndices + k) + 1;
      l = colIndices - 1;
      if (b_y == 0) {
        if (colIndices - 1 == 0) {
          l = 0;
        }
      } else if (colIndices - 1 == 0) {
        l = 0;
      } else {
        l = static_cast<int>(fmod(static_cast<double>(colIndices) - 1.0,
                                  static_cast<double>(b_y)));
        if ((static_cast<int>(l != 0)) &&
            (static_cast<int>(colIndices - 1 < 0))) {
          l += b_y;
        }
      }
      ipColIndices_data[colIdx + 320 * k] = aux2_data[l];
    }
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double rowWeights_data[2880]
//                double rowWeightsTotal[180]
// Return Type  : void
//
static __global__ __launch_bounds__(192, 1) void line_detection_kernel14(
    const double rowWeights_data[2880], double rowWeightsTotal[180])
{
  unsigned long threadId;
  int colIndices;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  colIndices = static_cast<int>(threadId);
  if (colIndices < 180) {
    rowWeightsTotal[colIndices] = rowWeights_data[colIndices];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double rowWeights_data[2880]
//                const int in_rows
//                double rowWeightsTotal[180]
// Return Type  : void
//
static __global__ __launch_bounds__(192, 1) void line_detection_kernel15(
    const double rowWeights_data[2880], const int in_rows,
    double rowWeightsTotal[180])
{
  unsigned long threadId;
  int colIndices;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  colIndices = static_cast<int>(threadId);
  if (colIndices < 180) {
    rowWeightsTotal[colIndices] += rowWeights_data[in_rows + colIndices];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double colWeights_data[9280]
//                double colWeightsTotal[320]
// Return Type  : void
//
static __global__ __launch_bounds__(320, 1) void line_detection_kernel16(
    const double colWeights_data[9280], double colWeightsTotal[320])
{
  unsigned long threadId;
  int colIndices;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  colIndices = static_cast<int>(threadId);
  if (colIndices < 320) {
    colWeightsTotal[colIndices] = colWeights_data[colIndices];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double colWeights_data[9280]
//                const int in_rows
//                double colWeightsTotal[320]
// Return Type  : void
//
static __global__ __launch_bounds__(320, 1) void line_detection_kernel17(
    const double colWeights_data[9280], const int in_rows,
    double colWeightsTotal[320])
{
  unsigned long threadId;
  int colIndices;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  colIndices = static_cast<int>(threadId);
  if (colIndices < 320) {
    colWeightsTotal[colIndices] += colWeights_data[in_rows + colIndices];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int img_size[3]
//                int partialResize_size[3]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel18(
    const int img_size[3], int partialResize_size[3])
{
  unsigned long threadId;
  int tmpIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  tmpIdx = static_cast<int>(threadId);
  if (tmpIdx < 1) {
    partialResize_size[0] = img_size[0];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double colWeightsTotal[320]
//                const double colWeights_data[9280]
//                const unsigned char img_data[2764800]
//                const double ipColIndices_data[9280]
//                const int img_size[3]
//                const int partialResize_size[3]
//                const double kwidthCol
//                const int plast
//                unsigned char partialResize_data[691200]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel19(
    const double colWeightsTotal[320], const double colWeights_data[9280],
    const unsigned char img_data[2764800], const double ipColIndices_data[9280],
    const int img_size[3], const int partialResize_size[3],
    const double kwidthCol, const int plast,
    unsigned char partialResize_data[691200])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = 3UL * (320UL * (static_cast<unsigned long>(plast - 1) + 1UL)) - 1UL;
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    double sumVal;
    unsigned long tmpIndex;
    int colIdx;
    int colIndices;
    int rowIdx;
    int rowIndices;
    unsigned char u;
    rowIndices = static_cast<int>(idx % 3UL);
    tmpIndex = (idx - static_cast<unsigned long>(rowIndices)) / 3UL;
    colIdx = static_cast<int>(tmpIndex % 320UL);
    tmpIndex = (tmpIndex - static_cast<unsigned long>(colIdx)) / 320UL;
    rowIdx = static_cast<int>(tmpIndex);
    sumVal = 0.0;
    colIndices = static_cast<int>(ceil(kwidthCol));
    for (int l{0}; l < colIndices; l++) {
      sumVal +=
          static_cast<double>(
              img_data[(rowIdx + img_size[0] *
                                     (static_cast<int>(
                                          ipColIndices_data[colIdx + 320 * l]) -
                                      1)) +
                       img_size[0] * img_size[1] * rowIndices]) *
          (colWeights_data[colIdx + 320 * l] / colWeightsTotal[colIdx]);
    }
    sumVal = round(sumVal);
    if (sumVal < 256.0) {
      if (sumVal >= 0.0) {
        u = static_cast<unsigned char>(sumVal);
      } else {
        u = static_cast<unsigned char>(0U);
      }
    } else if (sumVal >= 256.0) {
      u = MAX_uint8_T;
    } else {
      u = static_cast<unsigned char>(0U);
    }
    partialResize_data[(rowIdx + partialResize_size[0] * colIdx) +
                       partialResize_size[0] * 320 * rowIndices] = u;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char I_data[]
//                const int I_size
//                unsigned char img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel2(
    const unsigned char I_data[], const int I_size,
    unsigned char img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(I_size);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    img_data[oldIdx] = I_data[oldIdx];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double rowWeightsTotal[180]
//                const double rowWeights_data[2880]
//                const unsigned char partialResize_data[691200]
//                const int partialResize_size[3]
//                const double ipRowIndices_data[2880]
//                const double kwidthRow
//                unsigned char out[172800]
// Return Type  : void
//
static __global__ __launch_bounds__(512, 1) void line_detection_kernel20(
    const double rowWeightsTotal[180], const double rowWeights_data[2880],
    const unsigned char partialResize_data[691200],
    const int partialResize_size[3], const double ipRowIndices_data[2880],
    const double kwidthRow, unsigned char out[172800])
{
  unsigned long threadId;
  int colIdx;
  int rowIdx;
  int rowIndices;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  rowIndices = static_cast<int>(threadId % 3UL);
  threadId = (threadId - static_cast<unsigned long>(rowIndices)) / 3UL;
  rowIdx = static_cast<int>(threadId % 180UL);
  threadId = (threadId - static_cast<unsigned long>(rowIdx)) / 180UL;
  colIdx = static_cast<int>(threadId);
  if ((static_cast<int>((static_cast<int>(colIdx < 320)) &&
                        (static_cast<int>(rowIdx < 180)))) &&
      (static_cast<int>(rowIndices < 3))) {
    double sumVal;
    int colIndices;
    unsigned char u;
    sumVal = 0.0;
    colIndices = static_cast<int>(ceil(kwidthRow));
    for (int l{0}; l < colIndices; l++) {
      sumVal +=
          static_cast<double>(
              partialResize_data[((static_cast<int>(
                                       ipRowIndices_data[rowIdx + 180 * l]) +
                                   partialResize_size[0] * colIdx) +
                                  partialResize_size[0] * 320 * rowIndices) -
                                 1]) *
          (rowWeights_data[rowIdx + 180 * l] / rowWeightsTotal[rowIdx]);
    }
    sumVal = round(sumVal);
    if (sumVal < 256.0) {
      if (sumVal >= 0.0) {
        u = static_cast<unsigned char>(sumVal);
      } else {
        u = static_cast<unsigned char>(0U);
      }
    } else if (sumVal >= 256.0) {
      u = MAX_uint8_T;
    } else {
      u = static_cast<unsigned char>(0U);
    }
    out[(rowIdx + 180 * colIdx) + 57600 * rowIndices] = u;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int img_size[3]
//                int partialResize_size[3]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel21(
    const int img_size[3], int partialResize_size[3])
{
  unsigned long threadId;
  int tmpIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  tmpIdx = static_cast<int>(threadId);
  if (tmpIdx < 1) {
    partialResize_size[1] = img_size[1];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double rowWeightsTotal[180]
//                const double rowWeights_data[2880]
//                const unsigned char img_data[2764800]
//                const int img_size[3]
//                const double ipRowIndices_data[2880]
//                const int partialResize_size[3]
//                const double kwidthRow
//                const int plast
//                unsigned char partialResize_data[691200]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel22(
    const double rowWeightsTotal[180], const double rowWeights_data[2880],
    const unsigned char img_data[2764800], const int img_size[3],
    const double ipRowIndices_data[2880], const int partialResize_size[3],
    const double kwidthRow, const int plast,
    unsigned char partialResize_data[691200])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = 3UL * (180UL * (static_cast<unsigned long>(plast - 1) + 1UL)) - 1UL;
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    double sumVal;
    unsigned long tmpIndex;
    int colIdx;
    int colIndices;
    int rowIdx;
    int rowIndices;
    unsigned char u;
    rowIndices = static_cast<int>(idx % 3UL);
    tmpIndex = (idx - static_cast<unsigned long>(rowIndices)) / 3UL;
    rowIdx = static_cast<int>(tmpIndex % 180UL);
    tmpIndex = (tmpIndex - static_cast<unsigned long>(rowIdx)) / 180UL;
    colIdx = static_cast<int>(tmpIndex);
    sumVal = 0.0;
    colIndices = static_cast<int>(ceil(kwidthRow));
    for (int l{0}; l < colIndices; l++) {
      sumVal +=
          static_cast<double>(
              img_data[((static_cast<int>(ipRowIndices_data[rowIdx + 180 * l]) +
                         img_size[0] * colIdx) +
                        img_size[0] * img_size[1] * rowIndices) -
                       1]) *
          (rowWeights_data[rowIdx + 180 * l] / rowWeightsTotal[rowIdx]);
    }
    sumVal = round(sumVal);
    if (sumVal < 256.0) {
      if (sumVal >= 0.0) {
        u = static_cast<unsigned char>(sumVal);
      } else {
        u = static_cast<unsigned char>(0U);
      }
    } else if (sumVal >= 256.0) {
      u = MAX_uint8_T;
    } else {
      u = static_cast<unsigned char>(0U);
    }
    partialResize_data[(rowIdx + 180 * colIdx) +
                       180 * partialResize_size[1] * rowIndices] = u;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const double colWeightsTotal[320]
//                const double colWeights_data[9280]
//                const unsigned char partialResize_data[691200]
//                const int partialResize_size[3]
//                const double ipColIndices_data[9280]
//                const double kwidthCol
//                unsigned char out[172800]
// Return Type  : void
//
static __global__ __launch_bounds__(512, 1) void line_detection_kernel23(
    const double colWeightsTotal[320], const double colWeights_data[9280],
    const unsigned char partialResize_data[691200],
    const int partialResize_size[3], const double ipColIndices_data[9280],
    const double kwidthCol, unsigned char out[172800])
{
  unsigned long threadId;
  int colIdx;
  int rowIdx;
  int rowIndices;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  rowIndices = static_cast<int>(threadId % 3UL);
  threadId = (threadId - static_cast<unsigned long>(rowIndices)) / 3UL;
  rowIdx = static_cast<int>(threadId % 180UL);
  threadId = (threadId - static_cast<unsigned long>(rowIdx)) / 180UL;
  colIdx = static_cast<int>(threadId);
  if ((static_cast<int>((static_cast<int>(colIdx < 320)) &&
                        (static_cast<int>(rowIdx < 180)))) &&
      (static_cast<int>(rowIndices < 3))) {
    double sumVal;
    int colIndices;
    unsigned char u;
    sumVal = 0.0;
    colIndices = static_cast<int>(ceil(kwidthCol));
    for (int l{0}; l < colIndices; l++) {
      sumVal +=
          static_cast<double>(
              partialResize_data
                  [(rowIdx + 180 * (static_cast<int>(
                                        ipColIndices_data[colIdx + 320 * l]) -
                                    1)) +
                   180 * partialResize_size[1] * rowIndices]) *
          (colWeights_data[colIdx + 320 * l] / colWeightsTotal[colIdx]);
    }
    sumVal = round(sumVal);
    if (sumVal < 256.0) {
      if (sumVal >= 0.0) {
        u = static_cast<unsigned char>(sumVal);
      } else {
        u = static_cast<unsigned char>(0U);
      }
    } else if (sumVal >= 256.0) {
      u = MAX_uint8_T;
    } else {
      u = static_cast<unsigned char>(0U);
    }
    out[(rowIdx + 180 * colIdx) + 57600 * rowIndices] = u;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const short sz[3]
//                int positionOut_data[4]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel24(
    const short sz[3], int positionOut_data[4])
{
  unsigned long threadId;
  int tmpIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  tmpIdx = static_cast<int>(threadId);
  if (tmpIdx < 1) {
    positionOut_data[0] = static_cast<int>(
        roundf(static_cast<float>(static_cast<double>(sz[1]) / 2.0)));
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const short sz[3]
//                int positionOut_data[4]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel25(
    const short sz[3], int positionOut_data[4])
{
  unsigned long threadId;
  int tmpIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  tmpIdx = static_cast<int>(threadId);
  if (tmpIdx < 1) {
    positionOut_data[1] = static_cast<int>(sz[0]);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int plast
//                const float predictedPosNorm[2]
//                int positionOut_data[4]
//                float predictedPos[2]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel26(
    const int plast, const float predictedPosNorm[2], int positionOut_data[4],
    float predictedPos[2])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 2) {
    float f;
    int rowIndices;
    f = (predictedPosNorm[oldIdx] + 1.0F) / 2.0F * static_cast<float>(plast);
    predictedPos[oldIdx] = f;
    f = roundf(f);
    if (f < 2.14748365E+9F) {
      if (f >= -2.14748365E+9F) {
        rowIndices = static_cast<int>(f);
      } else {
        rowIndices = MIN_int32_T;
      }
    } else if (f >= 2.14748365E+9F) {
      rowIndices = MAX_int32_T;
    } else {
      rowIndices = 0;
    }
    positionOut_data[oldIdx + 2] = rowIndices;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int img_size[3]
//                short sz[3]
// Return Type  : void
//
static __global__
    __launch_bounds__(32, 1) void line_detection_kernel27(const int img_size[3],
                                                          short sz[3])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 3) {
    sz[oldIdx] = static_cast<short>(img_size[oldIdx]);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int sz
//                unsigned char img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel28(
    const int sz, unsigned char img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(sz);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    img_data[oldIdx] = static_cast<unsigned char>(0U);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const short pixCountSize
//                unsigned char pixCount_data[1280]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel29(
    const short pixCountSize, unsigned char pixCount_data[1280])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(static_cast<int>(pixCountSize) - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    pixCount_data[oldIdx] = static_cast<unsigned char>(0U);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char img_data[2764800]
//                const int img_size[3]
//                const int b_img_size[3]
//                const int plast
//                const int in_rows
//                unsigned char b_img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel3(
    const unsigned char img_data[2764800], const int img_size[3],
    const int b_img_size[3], const int plast, const int in_rows,
    unsigned char b_img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = (static_cast<unsigned long>(plast) + 1UL) *
                ((static_cast<unsigned long>(in_rows) + 1UL) * 3UL) -
            1UL;
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    unsigned long tmpIndex;
    int colIndices;
    int oldIdx;
    int rowIndices;
    rowIndices =
        static_cast<int>(idx % (static_cast<unsigned long>(plast) + 1UL));
    tmpIndex = (idx - static_cast<unsigned long>(rowIndices)) /
               (static_cast<unsigned long>(plast) + 1UL);
    colIndices = static_cast<int>(tmpIndex %
                                  (static_cast<unsigned long>(in_rows) + 1UL));
    tmpIndex = (tmpIndex - static_cast<unsigned long>(colIndices)) /
               (static_cast<unsigned long>(in_rows) + 1UL);
    oldIdx = static_cast<int>(tmpIndex);
    b_img_data[(rowIndices + b_img_size[0] * colIndices) +
               b_img_size[0] * b_img_size[1] * oldIdx] =
        img_data[(rowIndices + img_size[0] * colIndices) +
                 img_size[0] * img_size[1] * (2 - oldIdx)];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char color[3]
//                unsigned char b_color[3]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel30(
    const unsigned char color[3], unsigned char b_color[3])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 3) {
    b_color[oldIdx] = color[oldIdx];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const float predictedPos[2]
//                int positionOut[3]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel31(
    const float predictedPos[2], int positionOut[3])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 2) {
    float f;
    int rowIndices;
    f = roundf(predictedPos[oldIdx]);
    if (f < 2.14748365E+9F) {
      if (f >= -2.14748365E+9F) {
        rowIndices = static_cast<int>(f);
      } else {
        rowIndices = MIN_int32_T;
      }
    } else if (f >= 2.14748365E+9F) {
      rowIndices = MAX_int32_T;
    } else {
      rowIndices = 0;
    }
    positionOut[oldIdx] = rowIndices;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                int positionOut[3]
// Return Type  : void
//
static __global__
    __launch_bounds__(32, 1) void line_detection_kernel32(int positionOut[3])
{
  unsigned long threadId;
  int tmpIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  tmpIdx = static_cast<int>(threadId);
  if (tmpIdx < 1) {
    positionOut[2] = 5;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const short tmpRGB_size[3]
//                short sz[3]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel33(
    const short tmpRGB_size[3], short sz[3])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 3) {
    sz[oldIdx] = tmpRGB_size[oldIdx];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int sz
//                unsigned char img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel34(
    const int sz, unsigned char img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(sz);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    img_data[oldIdx] = static_cast<unsigned char>(0U);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const short pixCountSize
//                unsigned char pixCount_data[1280]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel35(
    const short pixCountSize, unsigned char pixCount_data[1280])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(static_cast<int>(pixCountSize) - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    pixCount_data[oldIdx] = static_cast<unsigned char>(0U);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char color[3]
//                unsigned char b_color[3]
// Return Type  : void
//
static __global__ __launch_bounds__(32, 1) void line_detection_kernel36(
    const unsigned char color[3], unsigned char b_color[3])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 3) {
    b_color[oldIdx] = color[oldIdx];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char img_data[2764800]
//                const short out_size[3]
//                const int Iout_size[3]
//                const int b_out_size
//                const int c_out_size
//                unsigned char Iout_data[]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel37(
    const unsigned char img_data[2764800], const short out_size[3],
    const int Iout_size[3], const int b_out_size, const int c_out_size,
    unsigned char Iout_data[])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = (static_cast<unsigned long>(b_out_size) + 1UL) *
                ((static_cast<unsigned long>(c_out_size) + 1UL) * 3UL) -
            1UL;
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    unsigned long tmpIndex;
    int colIndices;
    int k;
    int rowIndices;
    colIndices =
        static_cast<int>(idx % (static_cast<unsigned long>(b_out_size) + 1UL));
    tmpIndex = (idx - static_cast<unsigned long>(colIndices)) /
               (static_cast<unsigned long>(b_out_size) + 1UL);
    rowIndices = static_cast<int>(
        tmpIndex % (static_cast<unsigned long>(c_out_size) + 1UL));
    tmpIndex = (tmpIndex - static_cast<unsigned long>(rowIndices)) /
               (static_cast<unsigned long>(c_out_size) + 1UL);
    k = static_cast<int>(tmpIndex);
    Iout_data[(k + 3 * rowIndices) + 3 * Iout_size[1] * colIndices] =
        img_data[(colIndices + static_cast<int>(out_size[0]) * rowIndices) +
                 static_cast<int>(out_size[0]) * static_cast<int>(out_size[1]) *
                     (2 - k)];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char img_data[2764800]
//                const short out_size[3]
//                const short b_out_size[3]
//                const int plast
//                const int in_rows
//                unsigned char b_img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel38(
    const unsigned char img_data[2764800], const short out_size[3],
    const short b_out_size[3], const int plast, const int in_rows,
    unsigned char b_img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = (static_cast<unsigned long>(plast) + 1UL) *
                ((static_cast<unsigned long>(in_rows) + 1UL) * 3UL) -
            1UL;
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    unsigned long tmpIndex;
    int colIndices;
    int oldIdx;
    int rowIndices;
    rowIndices =
        static_cast<int>(idx % (static_cast<unsigned long>(plast) + 1UL));
    tmpIndex = (idx - static_cast<unsigned long>(rowIndices)) /
               (static_cast<unsigned long>(plast) + 1UL);
    colIndices = static_cast<int>(tmpIndex %
                                  (static_cast<unsigned long>(in_rows) + 1UL));
    tmpIndex = (tmpIndex - static_cast<unsigned long>(colIndices)) /
               (static_cast<unsigned long>(in_rows) + 1UL);
    oldIdx = static_cast<int>(tmpIndex);
    b_img_data[(rowIndices + static_cast<int>(b_out_size[0]) * colIndices) +
               static_cast<int>(b_out_size[0]) *
                   static_cast<int>(b_out_size[1]) * oldIdx] =
        img_data[(rowIndices + static_cast<int>(out_size[0]) * colIndices) +
                 static_cast<int>(out_size[0]) * static_cast<int>(out_size[1]) *
                     (2 - oldIdx)];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char img_data[2764800]
//                const int tmpRGB_size
//                unsigned char Iout_data[]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel39(
    const unsigned char img_data[2764800], const int tmpRGB_size,
    unsigned char Iout_data[])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(tmpRGB_size);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    Iout_data[oldIdx] = img_data[oldIdx];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const unsigned char img_data[2764800]
//                const int img_size
//                unsigned char b_img_data[2764800]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel4(
    const unsigned char img_data[2764800], const int img_size,
    unsigned char b_img_data[2764800])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(img_size);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    b_img_data[oldIdx] = img_data[oldIdx];
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int img_size[3]
//                short sz[3]
// Return Type  : void
//
static __global__
    __launch_bounds__(32, 1) void line_detection_kernel5(const int img_size[3],
                                                         short sz[3])
{
  unsigned long threadId;
  int oldIdx;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  oldIdx = static_cast<int>(threadId);
  if (oldIdx < 3) {
    // img = imrotate(img,180);
    sz[oldIdx] = static_cast<short>(img_size[oldIdx]);
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int in_rows
//                const int plast
//                double aux1_data[1440]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel6(
    const int in_rows, const int plast, double aux1_data[1440])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(plast - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int colIndices;
    colIndices = static_cast<int>(idx);
    if (colIndices + 1 <= in_rows) {
      aux1_data[colIndices] = static_cast<double>(colIndices) + 1.0;
    } else {
      aux1_data[colIndices] =
          (static_cast<double>(plast - colIndices) - 1.0) + 1.0;
    }
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int in_cols
//                const int plast
//                double aux2_data[2560]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel7(
    const int in_cols, const int plast, double aux2_data[2560])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(plast - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int colIndices;
    colIndices = static_cast<int>(idx);
    if (colIndices + 1 <= in_cols) {
      aux2_data[colIndices] = static_cast<double>(colIndices) + 1.0;
    } else {
      aux2_data[colIndices] =
          (static_cast<double>(plast - colIndices) - 1.0) + 1.0;
    }
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int plast
//                double ipRowIndices_data[2880]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel8(
    const int plast, double ipRowIndices_data[2880])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(180 * plast - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    ipRowIndices_data[oldIdx] = 0.0;
  }
}

//
// Arguments    : dim3 blockArg
//                dim3 gridArg
//                const int plast
//                double rowWeights_data[2880]
// Return Type  : void
//
static __global__ __launch_bounds__(1024, 1) void line_detection_kernel9(
    const int plast, double rowWeights_data[2880])
{
  unsigned long loopEnd;
  unsigned long threadId;
  unsigned long threadStride;
  threadId = static_cast<unsigned long>(mwGetGlobalThreadIndexInXDimension());
  threadStride = mwGetTotalThreadsLaunched();
  loopEnd = static_cast<unsigned long>(180 * plast - 1);
  for (unsigned long idx{threadId}; idx <= loopEnd; idx += threadStride) {
    int oldIdx;
    oldIdx = static_cast<int>(idx);
    rowWeights_data[oldIdx] = 0.0;
  }
}

//
// Copyright 2020 The MathWorks, Inc.
//
// Arguments    : const unsigned char I_data[]
//                const int I_size[3]
//                float predictedPosNorm[2]
//                unsigned char Iout_data[]
//                int Iout_size[3]
// Return Type  : void
//
void line_detection(const unsigned char I_data[], const int I_size[3],
                    float predictedPosNorm[2], unsigned char Iout_data[],
                    int Iout_size[3])
{
  static const unsigned char b_color[3]{MAX_uint8_T, 0U, 0U};
  static unsigned char b_img_data[2764800];
  static unsigned char img_data[2764800];
  void *b_colPtr;
  void *b_posPtr;
  void *b_ptrObj;
  void *colPtr;
  void *posPtr;
  void *ptrObj;
  dim3 block;
  dim3 grid;
  double(*gpu_colWeights_data)[9280];
  double(*gpu_ipColIndices_data)[9280];
  double(*gpu_ipRowIndices_data)[2880];
  double(*gpu_rowWeights_data)[2880];
  double(*gpu_aux2_data)[2560];
  double(*gpu_aux1_data)[1440];
  double(*gpu_colWeightsTotal)[320];
  double(*gpu_rowWeightsTotal)[180];
  double kwidthCol;
  double kwidthRow;
  double scale_idx_0;
  double scale_idx_1;
  float(*gpu_predictedPos)[2];
  float(*gpu_predictedPosNorm)[2];
  int positionOut_data[4];
  int(*gpu_positionOut_data)[4];
  int b_img_size[3];
  int img_size[3];
  int positionOut[3];
  int(*b_gpu_img_size)[3];
  int(*gpu_I_size)[3];
  int(*gpu_Iout_size)[3];
  int(*gpu_img_size)[3];
  int(*gpu_partialResize_size)[3];
  int(*gpu_positionOut)[3];
  int colWeights_size[2];
  int rowWeights_size[2];
  int in_cols;
  int plast;
  short b_out_size[3];
  short out_size[3];
  short sz[3];
  short tmpRGB_size[3];
  short(*b_gpu_out_size)[3];
  short(*gpu_out_size)[3];
  short(*gpu_sz)[3];
  short(*gpu_tmpRGB_size)[3];
  short numCol;
  short numRow;
  short pixCountSize;
  unsigned char(*b_gpu_img_data)[2764800];
  unsigned char(*gpu_img_data)[2764800];
  unsigned char(*gpu_partialResize_data)[691200];
  unsigned char out[172800];
  unsigned char(*gpu_out)[172800];
  unsigned char pixCount_data[1280];
  unsigned char(*gpu_pixCount_data)[1280];
  unsigned char color[3];
  unsigned char(*b_gpu_color)[3];
  unsigned char(*gpu_color)[3];
  unsigned char *gpu_I_data;
  unsigned char *gpu_Iout_data;
  bool b_img_data_dirtyOnCpu;
  bool b_img_data_dirtyOnGpu;
  bool exitg1;
  bool img_data_dirtyOnCpu;
  bool img_data_dirtyOnGpu;
  bool isInitialise;
  bool pixCount_data_dirtyOnCpu;
  bool pixCount_data_dirtyOnGpu;
  bool validLaunchParams;
  if (!isInitialized_line_detection) {
    line_detection_initialize();
  }
  cudaMalloc(&gpu_Iout_data, 2764800U * sizeof(unsigned char));
  cudaMalloc(&gpu_Iout_size, 12UL);
  cudaMalloc(&b_gpu_out_size, 6UL);
  cudaMalloc(&gpu_out_size, 6UL);
  cudaMalloc(&gpu_tmpRGB_size, 6UL);
  cudaMalloc(&gpu_positionOut, 12UL);
  cudaMalloc(&b_gpu_color, 3UL);
  cudaMalloc(&gpu_color, 3UL);
  cudaMalloc(&gpu_pixCount_data, 1280UL);
  cudaMalloc(&gpu_predictedPos, 8UL);
  cudaMalloc(&gpu_predictedPosNorm, 8UL);
  cudaMalloc(&gpu_positionOut_data, 16UL);
  cudaMalloc(&gpu_out, 172800UL);
  cudaMalloc(&gpu_partialResize_data, 691200UL);
  cudaMalloc(&gpu_partialResize_size, 12UL);
  cudaMalloc(&gpu_colWeightsTotal, 2560UL);
  cudaMalloc(&gpu_rowWeightsTotal, 1440UL);
  cudaMalloc(&gpu_colWeights_data, 74240UL);
  cudaMalloc(&gpu_ipColIndices_data, 74240UL);
  cudaMalloc(&gpu_rowWeights_data, 23040UL);
  cudaMalloc(&gpu_ipRowIndices_data, 23040UL);
  cudaMalloc(&gpu_aux2_data, 20480UL);
  cudaMalloc(&gpu_aux1_data, 11520UL);
  cudaMalloc(&gpu_sz, 6UL);
  cudaMalloc(&b_gpu_img_data, 2764800UL);
  cudaMalloc(&b_gpu_img_size, 12UL);
  cudaMalloc(&gpu_img_size, 12UL);
  cudaMalloc(&gpu_I_size, 12UL);
  cudaMalloc(&gpu_img_data, 2764800UL);
  cudaMalloc(&gpu_I_data, 2764800U * sizeof(unsigned char));
  pixCount_data_dirtyOnGpu = false;
  b_img_data_dirtyOnGpu = false;
  img_data_dirtyOnGpu = false;
  pixCount_data_dirtyOnCpu = false;
  b_img_data_dirtyOnCpu = false;
  img_data_dirtyOnCpu = false;
  if (!lineDetObj_not_empty) {
    coder::DeepLearningNetwork_setup(&lineDetObj);
    lineDetObj_not_empty = true;
  }
  //  Convert image data format OpenCV BGR to MATLAB compatible RGB image format
  //  Convert image data format OpenCV BGR to MATLAB compatible RGB image format
  //  Copyright 2020 The MathWorks, Inc.
  isInitialise = true;
  if ((I_size[1] != 0) && (I_size[2] != 0)) {
    plast = 0;
    in_cols = 1;
    exitg1 = false;
    while ((!exitg1) && (in_cols < 4)) {
      if (I_size[3 - in_cols] != 1) {
        if (plast > 4 - in_cols) {
          isInitialise = false;
          exitg1 = true;
        } else {
          plast = 4 - in_cols;
          in_cols++;
        }
      } else {
        in_cols++;
      }
    }
  }
  if (isInitialise) {
    img_size[0] = I_size[2];
    img_size[1] = I_size[1];
    isInitialise = true;
    in_cols = I_size[1] * I_size[2] * 3 - 1;
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(in_cols + 1L), &grid, &block, 1024U, 65535U);
    if (validLaunchParams) {
      cudaMemcpy(gpu_I_data, I_data,
                 3 * (I_size[1] * I_size[2]) * sizeof(unsigned char),
                 cudaMemcpyHostToDevice);
      line_detection_kernel2<<<grid, block>>>(gpu_I_data, in_cols,
                                              *gpu_img_data);
      img_data_dirtyOnGpu = true;
    }
  } else {
    img_size[0] = I_size[2];
    img_size[1] = I_size[1];
    isInitialise = true;
    plast = I_size[2];
    in_cols = I_size[1] - 1;
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(3L *
                            (((I_size[1] - 1) + 1L) * ((I_size[2] - 1) + 1L))),
        &grid, &block, 1024U, 65535U);
    if (validLaunchParams) {
      cudaMemcpy(gpu_I_data, I_data,
                 3 * (I_size[1] * I_size[2]) * sizeof(unsigned char),
                 cudaMemcpyHostToDevice);
      cudaMemcpy(*gpu_I_size, I_size, 12UL, cudaMemcpyHostToDevice);
      cudaMemcpy(*gpu_img_size, img_size, 12UL, cudaMemcpyHostToDevice);
      isInitialise = false;
      line_detection_kernel1<<<grid, block>>>(gpu_I_data, *gpu_I_size,
                                              *gpu_img_size, in_cols, plast,
                                              *gpu_img_data);
      img_data_dirtyOnGpu = true;
    }
  }
  plast = img_size[0] - 1;
  in_cols = img_size[1] - 1;
  b_img_size[0] = img_size[0];
  b_img_size[1] = img_size[1];
  validLaunchParams = mwGetLaunchParameters1D(
      static_cast<double>(((img_size[0] - 1) + 1L) *
                          (((img_size[1] - 1) + 1L) * 3L)),
      &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    if (isInitialise) {
      cudaMemcpy(*gpu_img_size, img_size, 12UL, cudaMemcpyHostToDevice);
    }
    cudaMemcpy(*b_gpu_img_size, b_img_size, 12UL, cudaMemcpyHostToDevice);
    line_detection_kernel3<<<grid, block>>>(*gpu_img_data, *gpu_img_size,
                                            *b_gpu_img_size, plast, in_cols,
                                            *b_gpu_img_data);
    b_img_data_dirtyOnGpu = true;
  }
  img_size[0] = b_img_size[0];
  img_size[1] = b_img_size[1];
  img_size[2] = 3;
  in_cols = b_img_size[0] * b_img_size[1] * 3 - 1;
  validLaunchParams = mwGetLaunchParameters1D(static_cast<double>(in_cols + 1L),
                                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel4<<<grid, block>>>(*b_gpu_img_data, in_cols,
                                            *gpu_img_data);
    img_data_dirtyOnGpu = true;
  }
  // img = imrotate(img,180);
  cudaMemcpy(*gpu_img_size, img_size, 12UL, cudaMemcpyHostToDevice);
  line_detection_kernel5<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(*gpu_img_size,
                                                                  *gpu_sz);
  //  Resize
  scale_idx_0 = 180.0 / static_cast<double>(img_size[0]);
  scale_idx_1 = 320.0 / static_cast<double>(img_size[1]);
  plast = img_size[0] << 1;
  validLaunchParams = mwGetLaunchParameters1D(
      static_cast<double>((plast - 1) + 1L), &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel6<<<grid, block>>>(img_size[0], plast, *gpu_aux1_data);
  }
  plast = img_size[1] << 1;
  validLaunchParams = mwGetLaunchParameters1D(
      static_cast<double>((plast - 1) + 1L), &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel7<<<grid, block>>>(img_size[1], plast, *gpu_aux2_data);
  }
  if (scale_idx_0 < 1.0) {
    kwidthRow = 4.0 / scale_idx_0;
  } else {
    kwidthRow = 4.0;
  }
  plast = static_cast<int>(std::ceil(kwidthRow));
  validLaunchParams =
      mwGetLaunchParameters1D(static_cast<double>((180 * plast - 1) + 1L),
                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel8<<<grid, block>>>(plast, *gpu_ipRowIndices_data);
  }
  plast = static_cast<int>(std::ceil(kwidthRow));
  rowWeights_size[1] = plast;
  validLaunchParams =
      mwGetLaunchParameters1D(static_cast<double>((180 * plast - 1) + 1L),
                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel9<<<grid, block>>>(plast, *gpu_rowWeights_data);
  }
  line_detection_kernel10<<<dim3(1U, 1U, 1U), dim3(192U, 1U, 1U)>>>(
      *gpu_aux1_data, img_size[0], scale_idx_0, kwidthRow,
      *gpu_ipRowIndices_data, *gpu_rowWeights_data);
  if (scale_idx_1 < 1.0) {
    kwidthCol = 4.0 / scale_idx_1;
  } else {
    kwidthCol = 4.0;
  }
  plast = static_cast<int>(std::ceil(kwidthCol));
  validLaunchParams =
      mwGetLaunchParameters1D(static_cast<double>((320 * plast - 1) + 1L),
                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel11<<<grid, block>>>(plast, *gpu_ipColIndices_data);
  }
  plast = static_cast<int>(std::ceil(kwidthCol));
  colWeights_size[1] = plast;
  validLaunchParams =
      mwGetLaunchParameters1D(static_cast<double>((320 * plast - 1) + 1L),
                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel12<<<grid, block>>>(plast, *gpu_colWeights_data);
  }
  line_detection_kernel13<<<dim3(1U, 1U, 1U), dim3(320U, 1U, 1U)>>>(
      *gpu_aux2_data, img_size[1], scale_idx_1, kwidthCol,
      *gpu_ipColIndices_data, *gpu_colWeights_data);
  plast = rowWeights_size[1];
  line_detection_kernel14<<<dim3(1U, 1U, 1U), dim3(192U, 1U, 1U)>>>(
      *gpu_rowWeights_data, *gpu_rowWeightsTotal);
  for (in_cols = 0; in_cols <= plast - 2; in_cols++) {
    line_detection_kernel15<<<dim3(1U, 1U, 1U), dim3(192U, 1U, 1U)>>>(
        *gpu_rowWeights_data, (in_cols + 1) * 180, *gpu_rowWeightsTotal);
  }
  plast = colWeights_size[1];
  line_detection_kernel16<<<dim3(1U, 1U, 1U), dim3(320U, 1U, 1U)>>>(
      *gpu_colWeights_data, *gpu_colWeightsTotal);
  for (in_cols = 0; in_cols <= plast - 2; in_cols++) {
    line_detection_kernel17<<<dim3(1U, 1U, 1U), dim3(320U, 1U, 1U)>>>(
        *gpu_colWeights_data, (in_cols + 1) * 320, *gpu_colWeightsTotal);
  }
  if (!(scale_idx_0 > scale_idx_1)) {
    line_detection_kernel21<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
        *gpu_img_size, *gpu_partialResize_size);
    plast = img_size[1];
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(3L * (180L * ((img_size[1] - 1) + 1L))), &grid,
        &block, 1024U, 65535U);
    if (validLaunchParams) {
      line_detection_kernel22<<<grid, block>>>(
          *gpu_rowWeightsTotal, *gpu_rowWeights_data, *gpu_img_data,
          *gpu_img_size, *gpu_ipRowIndices_data, *gpu_partialResize_size,
          kwidthRow, plast, *gpu_partialResize_data);
    }
    line_detection_kernel23<<<dim3(338U, 1U, 1U), dim3(512U, 1U, 1U)>>>(
        *gpu_colWeightsTotal, *gpu_colWeights_data, *gpu_partialResize_data,
        *gpu_partialResize_size, *gpu_ipColIndices_data, kwidthCol, *gpu_out);
  } else {
    line_detection_kernel18<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
        *gpu_img_size, *gpu_partialResize_size);
    plast = img_size[0];
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(3L * (320L * ((img_size[0] - 1) + 1L))), &grid,
        &block, 1024U, 65535U);
    if (validLaunchParams) {
      line_detection_kernel19<<<grid, block>>>(
          *gpu_colWeightsTotal, *gpu_colWeights_data, *gpu_img_data,
          *gpu_ipColIndices_data, *gpu_img_size, *gpu_partialResize_size,
          kwidthCol, plast, *gpu_partialResize_data);
    }
    line_detection_kernel20<<<dim3(338U, 1U, 1U), dim3(512U, 1U, 1U)>>>(
        *gpu_rowWeightsTotal, *gpu_rowWeights_data, *gpu_partialResize_data,
        *gpu_partialResize_size, *gpu_ipRowIndices_data, kwidthRow, *gpu_out);
  }
  //  pass in input
  cudaMemcpy(out, *gpu_out, 172800UL, cudaMemcpyDeviceToHost);
  coder::DeepLearningNetwork_predict(&lineDetObj, out, predictedPosNorm);
  cudaMemcpy(sz, *gpu_sz, 6UL, cudaMemcpyDeviceToHost);
  //  Visualize
  line_detection_kernel24<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_sz, *gpu_positionOut_data);
  line_detection_kernel25<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_sz, *gpu_positionOut_data);
  cudaMemcpy(*gpu_predictedPosNorm, predictedPosNorm, 8UL,
             cudaMemcpyHostToDevice);
  line_detection_kernel26<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      static_cast<int>(sz[1]), *gpu_predictedPosNorm, *gpu_positionOut_data,
      *gpu_predictedPos);
  numRow = static_cast<short>(img_size[0]);
  numCol = static_cast<short>(img_size[1]);
  line_detection_kernel27<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_img_size, *gpu_sz);
  cudaMemcpy(sz, *gpu_sz, 6UL, cudaMemcpyDeviceToHost);
  tmpRGB_size[0] = sz[0];
  tmpRGB_size[1] = sz[1];
  tmpRGB_size[2] = 3;
  in_cols = sz[0] * sz[1] * 3 - 1;
  validLaunchParams = mwGetLaunchParameters1D(static_cast<double>(in_cols + 1L),
                                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel28<<<grid, block>>>(in_cols, *b_gpu_img_data);
    b_img_data_dirtyOnGpu = true;
  }
  if (img_size[0] > img_size[1]) {
    pixCountSize = static_cast<short>(img_size[0]);
  } else {
    pixCountSize = static_cast<short>(img_size[1]);
  }
  validLaunchParams =
      mwGetLaunchParameters1D(static_cast<double>((pixCountSize - 1) + 1L),
                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    line_detection_kernel29<<<grid, block>>>(pixCountSize, *gpu_pixCount_data);
    pixCount_data_dirtyOnGpu = true;
  }
  ptrObj = NULL;
  constructDrawBaseObjectShape(&ptrObj);
  posPtr = NULL;
  cudaMemcpy(positionOut_data, *gpu_positionOut_data, 16UL,
             cudaMemcpyDeviceToHost);
  getPositionDataPointer(&posPtr, &positionOut_data[0], 4U, 1U);
  cudaMemcpy(*gpu_color, b_color, 3UL, cudaMemcpyHostToDevice);
  line_detection_kernel30<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_color, *b_gpu_color);
  colPtr = NULL;
  cudaMemcpy(color, *b_gpu_color, 3UL, cudaMemcpyDeviceToHost);
  getColorDataPointer_uint8(&colPtr, &color[0], 1U, 3U);
  isInitialise = initialiseDrawbaseShape(ptrObj, 0, 2);
  if (!isInitialise) {
    if (b_img_data_dirtyOnGpu) {
      cudaMemcpy(b_img_data, *b_gpu_img_data, 2764800UL,
                 cudaMemcpyDeviceToHost);
    }
    if (img_data_dirtyOnGpu) {
      cudaMemcpy(img_data, *gpu_img_data, 2764800UL, cudaMemcpyDeviceToHost);
    }
    if (pixCount_data_dirtyOnGpu) {
      cudaMemcpy(pixCount_data, *gpu_pixCount_data, 1280UL,
                 cudaMemcpyDeviceToHost);
    }
    instantiateDrawBaseShape_uint8(
        ptrObj, &b_img_data[0], &img_data[0], posPtr, colPtr, 0.6, 5, 2, true,
        numRow, numCol, 3, 2, 4, 1, 1, false, false, &pixCount_data[0], 0);
    pixCount_data_dirtyOnGpu = false;
    pixCount_data_dirtyOnCpu = true;
    img_data_dirtyOnGpu = false;
    img_data_dirtyOnCpu = true;
    b_img_data_dirtyOnGpu = false;
    b_img_data_dirtyOnCpu = true;
  }
  isInitialise = initialiseDrawbaseShape(ptrObj, 1, 2);
  if (!isInitialise) {
    if (b_img_data_dirtyOnGpu) {
      cudaMemcpy(b_img_data, *b_gpu_img_data, 2764800UL,
                 cudaMemcpyDeviceToHost);
    }
    if (img_data_dirtyOnGpu) {
      cudaMemcpy(img_data, *gpu_img_data, 2764800UL, cudaMemcpyDeviceToHost);
    }
    if (pixCount_data_dirtyOnGpu) {
      cudaMemcpy(pixCount_data, *gpu_pixCount_data, 1280UL,
                 cudaMemcpyDeviceToHost);
    }
    instantiateDrawBaseShape_uint8(
        ptrObj, &b_img_data[0], &img_data[0], posPtr, colPtr, 0.6, 5, 2, true,
        numRow, numCol, 3, 2, 4, 1, 1, false, true, &pixCount_data[0], 1);
    b_img_data_dirtyOnGpu = false;
    b_img_data_dirtyOnCpu = true;
    pixCount_data_dirtyOnGpu = false;
    pixCount_data_dirtyOnCpu = true;
    img_data_dirtyOnGpu = false;
    img_data_dirtyOnCpu = true;
  }
  mDrawShapes(ptrObj, false, true, 2, 5, static_cast<int>(numRow),
              static_cast<int>(numCol));
  deallocateMemoryShape(ptrObj);
  deletePositionDataPointer(posPtr);
  deleteColorDataPointer_uint8(colPtr);
  line_detection_kernel31<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_predictedPos, *gpu_positionOut);
  line_detection_kernel32<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_positionOut);
  numRow = tmpRGB_size[0];
  numCol = tmpRGB_size[1];
  cudaMemcpy(*gpu_tmpRGB_size, tmpRGB_size, 6UL, cudaMemcpyHostToDevice);
  line_detection_kernel33<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_tmpRGB_size, *gpu_sz);
  cudaMemcpy(sz, *gpu_sz, 6UL, cudaMemcpyDeviceToHost);
  out_size[0] = sz[0];
  out_size[1] = sz[1];
  in_cols = sz[0] * sz[1] * 3 - 1;
  validLaunchParams = mwGetLaunchParameters1D(static_cast<double>(in_cols + 1L),
                                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    if (img_data_dirtyOnCpu) {
      cudaMemcpy(*gpu_img_data, img_data, 2764800UL, cudaMemcpyHostToDevice);
    }
    line_detection_kernel34<<<grid, block>>>(in_cols, *gpu_img_data);
    img_data_dirtyOnCpu = false;
    img_data_dirtyOnGpu = true;
  }
  if (tmpRGB_size[0] > tmpRGB_size[1]) {
    pixCountSize = tmpRGB_size[0];
  } else {
    pixCountSize = tmpRGB_size[1];
  }
  validLaunchParams =
      mwGetLaunchParameters1D(static_cast<double>((pixCountSize - 1) + 1L),
                              &grid, &block, 1024U, 65535U);
  if (validLaunchParams) {
    if (pixCount_data_dirtyOnCpu) {
      cudaMemcpy(*gpu_pixCount_data, pixCount_data, 1280UL,
                 cudaMemcpyHostToDevice);
    }
    line_detection_kernel35<<<grid, block>>>(pixCountSize, *gpu_pixCount_data);
    pixCount_data_dirtyOnGpu = true;
  }
  b_ptrObj = NULL;
  constructDrawBaseObjectShape(&b_ptrObj);
  b_posPtr = NULL;
  cudaMemcpy(positionOut, *gpu_positionOut, 12UL, cudaMemcpyDeviceToHost);
  getPositionDataPointer(&b_posPtr, &positionOut[0], 1U, 3U);
  cudaMemcpy(*b_gpu_color, color, 3UL, cudaMemcpyHostToDevice);
  line_detection_kernel36<<<dim3(1U, 1U, 1U), dim3(32U, 1U, 1U)>>>(
      *gpu_color, *b_gpu_color);
  b_colPtr = NULL;
  cudaMemcpy(color, *b_gpu_color, 3UL, cudaMemcpyDeviceToHost);
  getColorDataPointer_uint8(&b_colPtr, &color[0], 1U, 3U);
  isInitialise = initialiseDrawbaseShape(b_ptrObj, 0, 4);
  if (!isInitialise) {
    if (img_data_dirtyOnGpu) {
      cudaMemcpy(img_data, *gpu_img_data, 2764800UL, cudaMemcpyDeviceToHost);
    }
    if (b_img_data_dirtyOnGpu) {
      cudaMemcpy(b_img_data, *b_gpu_img_data, 2764800UL,
                 cudaMemcpyDeviceToHost);
    }
    if (pixCount_data_dirtyOnGpu) {
      cudaMemcpy(pixCount_data, *gpu_pixCount_data, 1280UL,
                 cudaMemcpyDeviceToHost);
    }
    instantiateDrawBaseShape_uint8(
        b_ptrObj, &img_data[0], &b_img_data[0], b_posPtr, b_colPtr, 1.0, 1, 4,
        true, numRow, numCol, 3, 2, 1, 3, 1, true, false, &pixCount_data[0], 0);
    pixCount_data_dirtyOnGpu = false;
    b_img_data_dirtyOnGpu = false;
    b_img_data_dirtyOnCpu = true;
    img_data_dirtyOnGpu = false;
    img_data_dirtyOnCpu = true;
  }
  isInitialise = initialiseDrawbaseShape(b_ptrObj, 1, 4);
  if (!isInitialise) {
    if (img_data_dirtyOnGpu) {
      cudaMemcpy(img_data, *gpu_img_data, 2764800UL, cudaMemcpyDeviceToHost);
    }
    if (b_img_data_dirtyOnGpu) {
      cudaMemcpy(b_img_data, *b_gpu_img_data, 2764800UL,
                 cudaMemcpyDeviceToHost);
    }
    if (pixCount_data_dirtyOnGpu) {
      cudaMemcpy(pixCount_data, *gpu_pixCount_data, 1280UL,
                 cudaMemcpyDeviceToHost);
    }
    instantiateDrawBaseShape_uint8(
        b_ptrObj, &img_data[0], &b_img_data[0], b_posPtr, b_colPtr, 1.0, 1, 4,
        true, numRow, numCol, 3, 2, 1, 3, 1, true, true, &pixCount_data[0], 1);
    b_img_data_dirtyOnCpu = true;
    img_data_dirtyOnCpu = true;
  }
  mDrawShapes(b_ptrObj, true, true, 4, 1, static_cast<int>(numRow),
              static_cast<int>(numCol));
  deallocateMemoryShape(b_ptrObj);
  deletePositionDataPointer(b_posPtr);
  deleteColorDataPointer_uint8(b_colPtr);
  //  Convert image data format to OpenCV compatible image format
  //  Convert image data format to OpenCV compatible image format
  //  Copyright 2020 The MathWorks, Inc.
  isInitialise = true;
  if ((out_size[0] != 0) && (out_size[1] != 0)) {
    plast = 0;
    in_cols = 1;
    exitg1 = false;
    while ((!exitg1) && (in_cols < 4)) {
      tmpRGB_size[0] = out_size[0];
      tmpRGB_size[1] = out_size[1];
      tmpRGB_size[2] = 3;
      if (tmpRGB_size[3 - in_cols] != 1) {
        if (plast > 4 - in_cols) {
          isInitialise = false;
          exitg1 = true;
        } else {
          plast = 4 - in_cols;
          in_cols++;
        }
      } else {
        in_cols++;
      }
    }
  }
  if (isInitialise) {
    plast = out_size[0] - 1;
    in_cols = out_size[1] - 1;
    b_out_size[0] = out_size[0];
    b_out_size[1] = out_size[1];
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(((out_size[0] - 1) + 1L) *
                            (((out_size[1] - 1) + 1L) * 3L)),
        &grid, &block, 1024U, 65535U);
    if (validLaunchParams) {
      if (img_data_dirtyOnCpu) {
        cudaMemcpy(*gpu_img_data, img_data, 2764800UL, cudaMemcpyHostToDevice);
      }
      cudaMemcpy(*gpu_out_size, out_size, 6UL, cudaMemcpyHostToDevice);
      cudaMemcpy(*b_gpu_out_size, b_out_size, 6UL, cudaMemcpyHostToDevice);
      if (b_img_data_dirtyOnCpu) {
        cudaMemcpy(*b_gpu_img_data, b_img_data, 2764800UL,
                   cudaMemcpyHostToDevice);
      }
      line_detection_kernel38<<<grid, block>>>(*gpu_img_data, *gpu_out_size,
                                               *b_gpu_out_size, plast, in_cols,
                                               *b_gpu_img_data);
      b_img_data_dirtyOnCpu = false;
    }
    Iout_size[0] = 3;
    Iout_size[1] = out_size[1];
    Iout_size[2] = out_size[0];
    in_cols = 3 * out_size[1] * out_size[0] - 1;
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(in_cols + 1L), &grid, &block, 1024U, 65535U);
    if (validLaunchParams) {
      if (b_img_data_dirtyOnCpu) {
        cudaMemcpy(*b_gpu_img_data, b_img_data, 2764800UL,
                   cudaMemcpyHostToDevice);
      }
      line_detection_kernel39<<<grid, block>>>(*b_gpu_img_data, in_cols,
                                               gpu_Iout_data);
      cudaMemcpy(Iout_data, gpu_Iout_data,
                 3 * (Iout_size[1] * Iout_size[2]) * sizeof(unsigned char),
                 cudaMemcpyDeviceToHost);
    }
  } else {
    Iout_size[0] = 3;
    Iout_size[1] = out_size[1];
    Iout_size[2] = out_size[0];
    in_cols = out_size[1] - 1;
    plast = out_size[0] - 1;
    validLaunchParams = mwGetLaunchParameters1D(
        static_cast<double>(((out_size[0] - 1) + 1L) *
                            (((out_size[1] - 1) + 1L) * 3L)),
        &grid, &block, 1024U, 65535U);
    if (validLaunchParams) {
      if (img_data_dirtyOnCpu) {
        cudaMemcpy(*gpu_img_data, img_data, 2764800UL, cudaMemcpyHostToDevice);
      }
      cudaMemcpy(*gpu_out_size, out_size, 6UL, cudaMemcpyHostToDevice);
      cudaMemcpy(*gpu_Iout_size, Iout_size, 12UL, cudaMemcpyHostToDevice);
      line_detection_kernel37<<<grid, block>>>(*gpu_img_data, *gpu_out_size,
                                               *gpu_Iout_size, plast, in_cols,
                                               gpu_Iout_data);
      cudaMemcpy(Iout_data, gpu_Iout_data,
                 3 * (Iout_size[1] * Iout_size[2]) * sizeof(unsigned char),
                 cudaMemcpyDeviceToHost);
    }
  }
  cudaFree(gpu_I_data);
  cudaFree(*gpu_img_data);
  cudaFree(*gpu_I_size);
  cudaFree(*gpu_img_size);
  cudaFree(*b_gpu_img_size);
  cudaFree(*b_gpu_img_data);
  cudaFree(*gpu_sz);
  cudaFree(*gpu_aux1_data);
  cudaFree(*gpu_aux2_data);
  cudaFree(*gpu_ipRowIndices_data);
  cudaFree(*gpu_rowWeights_data);
  cudaFree(*gpu_ipColIndices_data);
  cudaFree(*gpu_colWeights_data);
  cudaFree(*gpu_rowWeightsTotal);
  cudaFree(*gpu_colWeightsTotal);
  cudaFree(*gpu_partialResize_size);
  cudaFree(*gpu_partialResize_data);
  cudaFree(*gpu_out);
  cudaFree(*gpu_positionOut_data);
  cudaFree(*gpu_predictedPosNorm);
  cudaFree(*gpu_predictedPos);
  cudaFree(*gpu_pixCount_data);
  cudaFree(*gpu_color);
  cudaFree(*b_gpu_color);
  cudaFree(*gpu_positionOut);
  cudaFree(*gpu_tmpRGB_size);
  cudaFree(*gpu_out_size);
  cudaFree(*b_gpu_out_size);
  cudaFree(*gpu_Iout_size);
  cudaFree(gpu_Iout_data);
}

//
// Copyright 2020 The MathWorks, Inc.
//
// Arguments    : void
// Return Type  : void
//
void line_detection_init()
{
  lineDetObj_not_empty = false;
}

//
// File trailer for line_detection.cu
//
// [EOF]
//
