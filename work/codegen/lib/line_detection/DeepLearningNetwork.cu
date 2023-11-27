//
// File: DeepLearningNetwork.cu
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

// Include Files
#include "DeepLearningNetwork.h"
#include "line_detection_internal_types.h"
#include "MWAvgPoolingLayer.hpp"
#include "MWCNNLayer.hpp"
#include "MWConvLayer.hpp"
#include "MWElementwiseAffineLayer.hpp"
#include "MWFCLayer.hpp"
#include "MWFusedConvReLULayer.hpp"
#include "MWInputLayer.hpp"
#include "MWMaxPoolingLayer.hpp"
#include "MWOutputLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensor.hpp"
#include "MWTensorBase.hpp"
#include <cstdio>

// Named Constants
const char *errorString{
    "Abnormal termination due to: %s.\nError in %s (line %d)."};

// Function Declarations
static void checkCleanupCudaError(cudaError_t errCode, const char *file,
                                  unsigned int line);

// Function Definitions
//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::allocate()
{
  this->targetImpl->allocate(921600, 3);
  for (int idx{0}; idx < 26; idx++) {
    this->layers[idx]->allocate();
  }
  (static_cast<MWTensor<float> *>(this->inputTensors[0]))
      ->setData(this->layers[0]->getLayerOutput(0));
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::cleanup()
{
  this->deallocate();
  for (int idx{0}; idx < 26; idx++) {
    this->layers[idx]->cleanup();
  }
  if (this->targetImpl) {
    this->targetImpl->cleanup();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::deallocate()
{
  this->targetImpl->deallocate();
  for (int idx{0}; idx < 26; idx++) {
    this->layers[idx]->deallocate();
  }
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::postsetup()
{
  this->targetImpl->postSetup(this->layers, this->numLayers);
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::resetState()
{
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::setSize()
{
  for (int idx{0}; idx < 26; idx++) {
    this->layers[idx]->propagateSize();
  }
  this->allocate();
  this->postsetup();
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::setup()
{
  if (this->isInitialized) {
    this->resetState();
  } else {
    this->isInitialized = true;
    this->targetImpl->preSetup();
    this->targetImpl->setAutoTune(true);
    (static_cast<MWInputLayer *>(this->layers[0]))
        ->createInputLayer(this->targetImpl, this->inputTensors[0], 180, 320, 3,
                           0, "", 0);
    (static_cast<MWElementwiseAffineLayer *>(this->layers[1]))
        ->createElementwiseAffineLayer(
            this->targetImpl, this->layers[0]->getOutputTensor(0), 1, 1, 3, 1,
            1, 3, false, 1, 1,
            "./codegen/lib/line_detection/cnn_mynet_new0_0_data_scale.bin",
            "./codegen/lib/line_detection/cnn_mynet_new0_0_data_offset.bin", 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[2]))
        ->createFusedConvReLULayer(
            this->targetImpl, 1, this->layers[1]->getOutputTensor(0), 7, 7, 3,
            64, 2, 2, 3, 3, 3, 3, 1, 1, 1,
            "./codegen/lib/line_detection/cnn_mynet_new0_0_conv1_w.bin",
            "./codegen/lib/line_detection/cnn_mynet_new0_0_conv1_b.bin", 1);
    (static_cast<MWMaxPoolingLayer *>(this->layers[3]))
        ->createMaxPoolingLayer<float, float>(
            this->targetImpl, this->layers[2]->getOutputTensor(0), 3, 3, 2, 2,
            1, 1, 1, 1, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[4]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[3]->getOutputTensor(0), 3, 3,
                                   64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2a_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2a_branch2a_b.bin",
                                   1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[5]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[4]->getOutputTensor(0),
                                   this->layers[3]->getOutputTensor(0), 3, 3,
                                   64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2a_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2a_branch2b_b.bin",
                                   2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[6]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[5]->getOutputTensor(0), 3, 3,
                                   64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2b_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2b_branch2a_b.bin",
                                   0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[7]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[6]->getOutputTensor(0),
                                   this->layers[5]->getOutputTensor(0), 3, 3,
                                   64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2b_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res2b_branch2b_b.bin",
                                   1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[8]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[7]->getOutputTensor(0), 3, 3,
                                   64, 128, 2, 2, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3a_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3a_branch2a_b.bin",
                                   0);
    (static_cast<MWConvLayer *>(this->layers[9]))
        ->createConvLayer(
            this->targetImpl, this->layers[7]->getOutputTensor(0), 1, 1, 64,
            128, 2, 2, 0, 0, 0, 0, 1, 1, 1,
            "./codegen/lib/line_detection/cnn_mynet_new0_0_res3a_branch1_w.bin",
            "./codegen/lib/line_detection/cnn_mynet_new0_0_res3a_branch1_b.bin",
            2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[10]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[8]->getOutputTensor(0),
                                   this->layers[9]->getOutputTensor(0), 3, 3,
                                   128, 128, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3a_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3a_branch2b_b.bin",
                                   1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[11]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[10]->getOutputTensor(0), 3, 3,
                                   128, 128, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3b_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3b_branch2a_b.bin",
                                   0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[12]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[11]->getOutputTensor(0),
                                   this->layers[10]->getOutputTensor(0), 3, 3,
                                   128, 128, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3b_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res3b_branch2b_b.bin",
                                   2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[13]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[12]->getOutputTensor(0), 3, 3,
                                   128, 256, 2, 2, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4a_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4a_branch2a_b.bin",
                                   0);
    (static_cast<MWConvLayer *>(this->layers[14]))
        ->createConvLayer(
            this->targetImpl, this->layers[12]->getOutputTensor(0), 1, 1, 128,
            256, 2, 2, 0, 0, 0, 0, 1, 1, 1,
            "./codegen/lib/line_detection/cnn_mynet_new0_0_res4a_branch1_w.bin",
            "./codegen/lib/line_detection/cnn_mynet_new0_0_res4a_branch1_b.bin",
            1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[15]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[13]->getOutputTensor(0),
                                   this->layers[14]->getOutputTensor(0), 3, 3,
                                   256, 256, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4a_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4a_branch2b_b.bin",
                                   2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[16]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[15]->getOutputTensor(0), 3, 3,
                                   256, 256, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4b_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4b_branch2a_b.bin",
                                   0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[17]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[16]->getOutputTensor(0),
                                   this->layers[15]->getOutputTensor(0), 3, 3,
                                   256, 256, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4b_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res4b_branch2b_b.bin",
                                   1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[18]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[17]->getOutputTensor(0), 3, 3,
                                   256, 512, 2, 2, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5a_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5a_branch2a_b.bin",
                                   0);
    (static_cast<MWConvLayer *>(this->layers[19]))
        ->createConvLayer(
            this->targetImpl, this->layers[17]->getOutputTensor(0), 1, 1, 256,
            512, 2, 2, 0, 0, 0, 0, 1, 1, 1,
            "./codegen/lib/line_detection/cnn_mynet_new0_0_res5a_branch1_w.bin",
            "./codegen/lib/line_detection/cnn_mynet_new0_0_res5a_branch1_b.bin",
            2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[20]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[18]->getOutputTensor(0),
                                   this->layers[19]->getOutputTensor(0), 3, 3,
                                   512, 512, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5a_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5a_branch2b_b.bin",
                                   1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[21]))
        ->createFusedConvReLULayer(this->targetImpl, 1,
                                   this->layers[20]->getOutputTensor(0), 3, 3,
                                   512, 512, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5b_branch2a_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5b_branch2a_b.bin",
                                   0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[22]))
        ->createFusedConvReLULayer(this->targetImpl, 2,
                                   this->layers[21]->getOutputTensor(0),
                                   this->layers[20]->getOutputTensor(0), 3, 3,
                                   512, 512, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5b_branch2b_w.bin",
                                   "./codegen/lib/line_detection/"
                                   "cnn_mynet_new0_0_res5b_branch2b_b.bin",
                                   2);
    (static_cast<MWAvgPoolingLayer *>(this->layers[23]))
        ->createAvgPoolingLayer<float, float>(
            this->targetImpl, this->layers[22]->getOutputTensor(0), -1, -1, 1,
            1, 0, 0, 0, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFCLayer *>(this->layers[24]))
        ->createFCLayer(
            this->targetImpl, this->layers[23]->getOutputTensor(0), 512, 2,
            "./codegen/lib/line_detection/cnn_mynet_new0_0_new_fc_w.bin",
            "./codegen/lib/line_detection/cnn_mynet_new0_0_new_fc_b.bin", 1);
    (static_cast<MWOutputLayer *>(this->layers[25]))
        ->createOutputLayer(this->targetImpl,
                            this->layers[24]->getOutputTensor(0), 1);
    this->outputTensors[0] = this->layers[25]->getOutputTensor(0);
    this->setSize();
  }
}

//
// Arguments    : cudaError_t errCode
//                const char *file
//                unsigned int line
// Return Type  : void
//
static void checkCleanupCudaError(cudaError_t errCode, const char *file,
                                  unsigned int line)
{
  if ((errCode != cudaSuccess) && (errCode != cudaErrorCudartUnloading)) {
    printf(errorString, cudaGetErrorString(errCode), file, line);
  }
}

//
// Arguments    : void
// Return Type  : int
//
int mynet_new0_0::getBatchSize()
{
  return this->inputTensors[0]->getBatchSize();
}

//
// Arguments    : int b_index
// Return Type  : float *
//
float *mynet_new0_0::getInputDataPointer(int b_index)
{
  return (static_cast<MWTensor<float> *>(this->inputTensors[b_index]))
      ->getData();
}

//
// Arguments    : void
// Return Type  : float *
//
float *mynet_new0_0::getInputDataPointer()
{
  return (static_cast<MWTensor<float> *>(this->inputTensors[0]))->getData();
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : float *
//
float *mynet_new0_0::getLayerOutput(int layerIndex, int portIndex)
{
  return this->layers[layerIndex]->getLayerOutput(portIndex);
}

//
// Arguments    : int layerIndex
//                int portIndex
// Return Type  : int
//
int mynet_new0_0::getLayerOutputSize(int layerIndex, int portIndex)
{
  return this->layers[layerIndex]
             ->getOutputTensor(portIndex)
             ->getNumElements() *
         sizeof(float);
}

//
// Arguments    : int b_index
// Return Type  : float *
//
float *mynet_new0_0::getOutputDataPointer(int b_index)
{
  return (static_cast<MWTensor<float> *>(this->outputTensors[b_index]))
      ->getData();
}

//
// Arguments    : void
// Return Type  : float *
//
float *mynet_new0_0::getOutputDataPointer()
{
  return (static_cast<MWTensor<float> *>(this->outputTensors[0]))->getData();
}

//
// Arguments    : void
// Return Type  : ::mynet_new0_0
//
mynet_new0_0::mynet_new0_0()
{
  this->numLayers = 26;
  this->isInitialized = false;
  this->targetImpl = 0;
  this->layers[0] = new MWInputLayer;
  this->layers[0]->setName("data");
  this->layers[1] = new MWElementwiseAffineLayer;
  this->layers[1]->setName("data_normalization");
  this->layers[1]->setInPlaceIndex(0, 0);
  this->layers[2] = new MWFusedConvReLULayer;
  this->layers[2]->setName("conv1_conv1_relu");
  this->layers[3] = new MWMaxPoolingLayer;
  this->layers[3]->setName("pool1");
  this->layers[4] = new MWFusedConvReLULayer;
  this->layers[4]->setName("res2a_branch2a_res2a_branch2a_relu");
  this->layers[5] = new MWFusedConvReLULayer;
  this->layers[5]->setName("res2a_branch2b_res2a_relu");
  this->layers[6] = new MWFusedConvReLULayer;
  this->layers[6]->setName("res2b_branch2a_res2b_branch2a_relu");
  this->layers[7] = new MWFusedConvReLULayer;
  this->layers[7]->setName("res2b_branch2b_res2b_relu");
  this->layers[8] = new MWFusedConvReLULayer;
  this->layers[8]->setName("res3a_branch2a_res3a_branch2a_relu");
  this->layers[9] = new MWConvLayer;
  this->layers[9]->setName("res3a_branch1");
  this->layers[10] = new MWFusedConvReLULayer;
  this->layers[10]->setName("res3a_branch2b_res3a_relu");
  this->layers[11] = new MWFusedConvReLULayer;
  this->layers[11]->setName("res3b_branch2a_res3b_branch2a_relu");
  this->layers[12] = new MWFusedConvReLULayer;
  this->layers[12]->setName("res3b_branch2b_res3b_relu");
  this->layers[13] = new MWFusedConvReLULayer;
  this->layers[13]->setName("res4a_branch2a_res4a_branch2a_relu");
  this->layers[14] = new MWConvLayer;
  this->layers[14]->setName("res4a_branch1");
  this->layers[15] = new MWFusedConvReLULayer;
  this->layers[15]->setName("res4a_branch2b_res4a_relu");
  this->layers[16] = new MWFusedConvReLULayer;
  this->layers[16]->setName("res4b_branch2a_res4b_branch2a_relu");
  this->layers[17] = new MWFusedConvReLULayer;
  this->layers[17]->setName("res4b_branch2b_res4b_relu");
  this->layers[18] = new MWFusedConvReLULayer;
  this->layers[18]->setName("res5a_branch2a_res5a_branch2a_relu");
  this->layers[19] = new MWConvLayer;
  this->layers[19]->setName("res5a_branch1");
  this->layers[20] = new MWFusedConvReLULayer;
  this->layers[20]->setName("res5a_branch2b_res5a_relu");
  this->layers[21] = new MWFusedConvReLULayer;
  this->layers[21]->setName("res5b_branch2a_res5b_branch2a_relu");
  this->layers[22] = new MWFusedConvReLULayer;
  this->layers[22]->setName("res5b_branch2b_res5b_relu");
  this->layers[23] = new MWAvgPoolingLayer;
  this->layers[23]->setName("pool5");
  this->layers[24] = new MWFCLayer;
  this->layers[24]->setName("new_fc");
  this->layers[25] = new MWOutputLayer;
  this->layers[25]->setName("regressionoutput");
  this->layers[25]->setInPlaceIndex(0, 0);
  this->targetImpl = new MWTargetNetworkImpl;
  this->inputTensors[0] = new MWTensor<float>;
  this->inputTensors[0]->setHeight(180);
  this->inputTensors[0]->setWidth(320);
  this->inputTensors[0]->setChannels(3);
  this->inputTensors[0]->setBatchSize(1);
  this->inputTensors[0]->setSequenceLength(1);
}

//
// Arguments    : void
// Return Type  : void
//
mynet_new0_0::~mynet_new0_0()
{
  this->cleanup();
  checkCleanupCudaError(cudaGetLastError(), __FILE__, __LINE__);
  for (int idx{0}; idx < 26; idx++) {
    delete this->layers[idx];
  }
  if (this->targetImpl) {
    delete this->targetImpl;
  }
  delete this->inputTensors[0];
}

//
// Arguments    : void
// Return Type  : void
//
void mynet_new0_0::predict()
{
  for (int idx{0}; idx < 26; idx++) {
    this->layers[idx]->predict();
  }
}

//
// Arguments    : mynet_new0_0 *obj
// Return Type  : void
//
namespace coder {
void DeepLearningNetwork_setup(mynet_new0_0 *obj)
{
  obj->setup();
}

} // namespace coder

//
// File trailer for DeepLearningNetwork.cu
//
// [EOF]
//
