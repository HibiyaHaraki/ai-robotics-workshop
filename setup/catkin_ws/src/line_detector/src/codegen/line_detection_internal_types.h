//
// File: line_detection_internal_types.h
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 08-Apr-2021 15:32:32
//

#ifndef LINE_DETECTION_INTERNAL_TYPES_H
#define LINE_DETECTION_INTERNAL_TYPES_H

// Include Files
#include "line_detection_types.h"
#include "rtwtypes.h"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"

// Type Definitions
class mynet_new0_0 {
public:
  mynet_new0_0();
  void setSize();
  void resetState();
  void setup();
  void predict();
  void cleanup();
  float *getLayerOutput(int layerIndex, int portIndex);
  int getLayerOutputSize(int layerIndex, int portIndex);
  float *getInputDataPointer(int b_index);
  float *getInputDataPointer();
  float *getOutputDataPointer(int b_index);
  float *getOutputDataPointer();
  int getBatchSize();
  ~mynet_new0_0();

private:
  void allocate();
  void postsetup();
  void deallocate();
  int numLayers;
  bool isInitialized;
  MWTensorBase *inputTensors[1];
  MWTensorBase *outputTensors[1];
  MWCNNLayer *layers[26];
  MWTargetNetworkImpl *targetImpl;
};

#endif
//
// File trailer for line_detection_internal_types.h
//
// [EOF]
//
