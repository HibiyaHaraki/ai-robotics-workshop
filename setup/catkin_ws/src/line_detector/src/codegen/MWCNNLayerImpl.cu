#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <stdexcept>
#ifdef RANDOM
#include <curand.h>
 curandGenerator_t RQSttSyDKXCHDWSijmNk; void 
curand_call_line_file(curandStatus_t rlQsibXJSWJVnUVpdNeL, const int 
bERCRkGjpaKXMNComoYl, const char *QTXuPiGKeBUnmRzhlIDp) { if (rlQsibXJSWJVnUVpdNeL != 
CURAND_STATUS_SUCCESS) { char buffer[100]; int numElem = sprintf(buffer, 
"%d at line: %d, file: %s\n", rlQsibXJSWJVnUVpdNeL, bERCRkGjpaKXMNComoYl, 
QTXuPiGKeBUnmRzhlIDp); throw std::runtime_error(buffer); } }
#endif
 float* malloc_call_line_file(size_t msize, const int bERCRkGjpaKXMNComoYl, const 
char *QTXuPiGKeBUnmRzhlIDp) { float * mem = (float*)malloc(msize); if (!mem) { char 
buffer[100]; int numElem = sprintf(buffer, "%s at line: %d, file: %s\n", 
"Memory allocation failed. ", bERCRkGjpaKXMNComoYl, QTXuPiGKeBUnmRzhlIDp); throw 
std::runtime_error(buffer); } return mem; } void 
cuda_call_line_file(cudaError_t rlQsibXJSWJVnUVpdNeL, const int bERCRkGjpaKXMNComoYl, 
const char *QTXuPiGKeBUnmRzhlIDp) { if (rlQsibXJSWJVnUVpdNeL != cudaSuccess) { 
throw_cuda_error(rlQsibXJSWJVnUVpdNeL, bERCRkGjpaKXMNComoYl, QTXuPiGKeBUnmRzhlIDp);  } } 
void throw_cuda_error(cudaError_t rlQsibXJSWJVnUVpdNeL, const int bERCRkGjpaKXMNComoYl, 
const char *QTXuPiGKeBUnmRzhlIDp) { char buffer[100]; int numElem = sprintf(buffer, 
"Cuda Error %d(%s) at line: %d, file: %s\n", rlQsibXJSWJVnUVpdNeL, 
cudaGetErrorString(rlQsibXJSWJVnUVpdNeL), bERCRkGjpaKXMNComoYl, QTXuPiGKeBUnmRzhlIDp); 
rlQsibXJSWJVnUVpdNeL = cudaGetLastError();  throw std::runtime_error(buffer);  } 
void cudnn_call_line_file(cudnnStatus_t rlQsibXJSWJVnUVpdNeL, const int 
bERCRkGjpaKXMNComoYl, const char *QTXuPiGKeBUnmRzhlIDp) { if (rlQsibXJSWJVnUVpdNeL != 
CUDNN_STATUS_SUCCESS) { char buffer[100]; int numElem = sprintf(buffer, 
"CuDNN Error %d(%s) at line: %d, file: %s\n", rlQsibXJSWJVnUVpdNeL, 
cudnnGetErrorString(rlQsibXJSWJVnUVpdNeL), bERCRkGjpaKXMNComoYl, QTXuPiGKeBUnmRzhlIDp); 
throw std::runtime_error(buffer); } } const char* 
cublasGetErrorString(cublasStatus_t rlQsibXJSWJVnUVpdNeL) { 
switch(rlQsibXJSWJVnUVpdNeL) { case CUBLAS_STATUS_SUCCESS: return 
"CUBLAS_STATUS_SUCCESS"; case CUBLAS_STATUS_NOT_INITIALIZED: return 
"CUBLAS_STATUS_NOT_INITIALIZED"; case CUBLAS_STATUS_ALLOC_FAILED: return 
"CUBLAS_STATUS_ALLOC_FAILED"; case CUBLAS_STATUS_INVALID_VALUE: return 
"CUBLAS_STATUS_INVALID_VALUE";  case CUBLAS_STATUS_ARCH_MISMATCH: return 
"CUBLAS_STATUS_ARCH_MISMATCH";  case CUBLAS_STATUS_MAPPING_ERROR: return 
"CUBLAS_STATUS_MAPPING_ERROR"; case CUBLAS_STATUS_EXECUTION_FAILED: return 
"CUBLAS_STATUS_EXECUTION_FAILED";  case CUBLAS_STATUS_INTERNAL_ERROR: return 
"CUBLAS_STATUS_INTERNAL_ERROR";  case CUBLAS_STATUS_NOT_SUPPORTED: return 
"CUBLAS_STATUS_NOT_SUPPORTED";  case CUBLAS_STATUS_LICENSE_ERROR: return 
"CUBLAS_STATUS_LICENSE_ERROR";  } return "unknown error"; } void 
cublas_call_line_file(cublasStatus_t rlQsibXJSWJVnUVpdNeL, const int 
bERCRkGjpaKXMNComoYl, const char *QTXuPiGKeBUnmRzhlIDp) { if (rlQsibXJSWJVnUVpdNeL != 
CUBLAS_STATUS_SUCCESS) { char buffer[100]; int numElem = sprintf(buffer, 
"CuBlas Error %d(%s) at line: %d, file: %s\n", rlQsibXJSWJVnUVpdNeL, 
cublasGetErrorString(rlQsibXJSWJVnUVpdNeL), bERCRkGjpaKXMNComoYl, QTXuPiGKeBUnmRzhlIDp); 
throw std::runtime_error(buffer); } } 
MWCNNLayerImpl::MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : PmFfARVzoHVAYkfpuvqK(0.0), PQjbchiGbyJfmpiqPpOC(1.0), 
OwortPcLToImGdYFtbSF(-1.0), bDTIjtxZiSHtjwzgEluE(layer), 
dMxIKDGTITyhdLqIHBLA(ntwk_impl) { } MWCNNLayerImpl::~MWCNNLayerImpl() { 
for(std::map<int, cudnnTensorDescriptor_t*>::iterator it = 
kqftrrQBBOgGsrDSkIUk.begin(); it != kqftrrQBBOgGsrDSkIUk.end(); ++it) { 
CUDNN_CALL(cudnnDestroyTensorDescriptor(*it->second)); delete it->second; 
it->second = 0; } } template <class T> void 
MWCNNLayerImpl::allocateOutputData(int outIdx) { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(outIdx); bool bufferReuse = 
opTensorBase->getopBufIndex() >= 0; if (bufferReuse) { 
assert(opTensorBase->isFloat()); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); float* buffer = 
dMxIKDGTITyhdLqIHBLA->memBuffer[opTensor->getopBufIndex()]; int inIdx = 
getLayer()->getInPlaceIndex(outIdx); if (inIdx != -1) { MWTensor<float>* 
ipTensor = static_cast<MWTensor<float>*>(getLayer()->getInputTensor(inIdx)); 
buffer = ipTensor->getData(); assert(buffer); } float* opPointer = 
offsetOutputPointer(buffer, outIdx); assert(opPointer); 
opTensor->setData(opPointer); } else { int inIdx = 
getLayer()->getInPlaceIndex(outIdx); if (inIdx != -1) { MWTensor<T>* ipTensor = 
static_cast<MWTensor<T>*>(getLayer()->getInputTensor(inIdx)); MWTensor<T>* 
opTensor = static_cast<MWTensor<T>*>(opTensorBase); T* ipData = 
ipTensor->getData(); assert(ipData); T* opPointer = offsetOutputPointer(ipData, 
outIdx); assert(opPointer); opTensor->setData(opPointer); } else { MWTensor<T>* 
opTensor = static_cast<MWTensor<T>*>(opTensorBase); T* ONvcEjLBnVNUdjMKOAwF;  
CUDA_CALL(cudaMalloc((void**)&ONvcEjLBnVNUdjMKOAwF, 
sizeof(T)*opTensor->getNumElements())); opTensor->setData(ONvcEjLBnVNUdjMKOAwF); } } 
} template void MWCNNLayerImpl::allocateOutputData<float>(int); template void 
MWCNNLayerImpl::allocateOutputData<signed char>(int); template <class T> void 
MWCNNLayerImpl::deallocateOutputData(int outIdx) { 
if(getLayer()->getInPlaceIndex(outIdx) == -1) { MWTensor<T>* opTensor = 
static_cast<MWTensor<T>*>(getLayer()->getOutputTensor(outIdx)); T* data = 
opTensor->getData(); CUDA_FREE_CALL(data); } } template void 
MWCNNLayerImpl::deallocateOutputData<float>(int); template void 
MWCNNLayerImpl::deallocateOutputData<signed char>(int); float* 
MWCNNLayerImpl::getZeroPtr() { return &PmFfARVzoHVAYkfpuvqK; } float* 
MWCNNLayerImpl::getOnePtr() { return &PQjbchiGbyJfmpiqPpOC; } float* 
MWCNNLayerImpl::getNegOnePtr() { return &OwortPcLToImGdYFtbSF; } 
cudnnTensorDescriptor_t* MWCNNLayerImpl::createAndAddDescriptor(int index) { 
std::map<int, cudnnTensorDescriptor_t*>::iterator it = 
kqftrrQBBOgGsrDSkIUk.find(index); assert(it == kqftrrQBBOgGsrDSkIUk.end()); 
cudnnTensorDescriptor_t* newDescriptor = new cudnnTensorDescriptor_t; if 
(!newDescriptor) { MWCNNLayerImpl::throwAllocationError(__LINE__ , __FILE__); } 
kqftrrQBBOgGsrDSkIUk[index] = newDescriptor; 
CUDNN_CALL(cudnnCreateTensorDescriptor(newDescriptor)); return newDescriptor; } 
cudnnTensorDescriptor_t* MWCNNLayerImpl::getDescriptor(int index) {  
std::map<int, cudnnTensorDescriptor_t*>::iterator it = 
kqftrrQBBOgGsrDSkIUk.find(index); if (it != kqftrrQBBOgGsrDSkIUk.end()) { 
return it->second; } else { return NULL; } } template <class T> void 
MWCNNLayerImpl::setDescriptor(cudnnTensorDescriptor_t& desc, MWTensor<T>* 
tensor) { if (tensor->getSequenceLength() == 1) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(desc, CUDNN_TENSOR_NCHW, 
MWCNNLayerImpl::getCuDNNDataType<T>(), tensor->getBatchSize(),  
tensor->getChannels(),  tensor->getHeight(),  tensor->getWidth()));  } else { 
int dims[5] = {tensor->getSequenceLength(), tensor->getBatchSize(), 
tensor->getChannels(), tensor->getHeight(), tensor->getWidth()}; int 
strides[5]; MWTensorBase::getStrides(dims, 5, strides); 
CUDNN_CALL(cudnnSetTensorNdDescriptor(desc, 
MWCNNLayerImpl::getCuDNNDataType<T>(), 5, dims, strides)); }  } template void 
MWCNNLayerImpl::setDescriptor<float>(cudnnTensorDescriptor_t&, 
MWTensor<float>*); template void MWCNNLayerImpl::setDescriptor<signed 
char>(cudnnTensorDescriptor_t&, MWTensor<signed char>*); template <> 
cudnnDataType_t MWCNNLayerImpl::getCuDNNDataType<float>() { return 
CUDNN_DATA_FLOAT; } template <> cudnnDataType_t 
MWCNNLayerImpl::getCuDNNDataType<signed char>() { return CUDNN_DATA_INT8; } 
cudnnTensorDescriptor_t MWCNNLayerImpl::getCuDNNDescriptor(MWTensorBase* 
tensor) { MWCNNLayer* layer = tensor->getOwner(); MWCNNLayerImpl* impl = 
layer->getImpl(); if(impl) { cudnnTensorDescriptor_t* desc = 
impl->getDescriptor(tensor->getSourcePortIndex()); if (desc == NULL) { 
impl->createAndAddDescriptor(tensor->getSourcePortIndex()); desc = 
impl->getDescriptor(tensor->getSourcePortIndex()); assert(desc);  } if 
(tensor->isFloat()) { MWCNNLayerImpl::setDescriptor<float>(*desc, 
static_cast<MWTensor<float>*>(tensor)); } else { assert(tensor->isInt8()); 
MWCNNLayerImpl::setDescriptor<signed char>(*desc, static_cast<MWTensor<signed 
char>*>(tensor)); } return *desc; } else { cudnnTensorDescriptor_t 
tmpDescriptor; CUDNN_CALL(cudnnCreateTensorDescriptor(&tmpDescriptor)); if 
(tensor->isFloat()) { MWCNNLayerImpl::setDescriptor<float>(tmpDescriptor, 
static_cast<MWTensor<float>*>(tensor)); } else { assert(tensor->isInt8()); 
MWCNNLayerImpl::setDescriptor<signed char>(tmpDescriptor, 
static_cast<MWTensor<signed char>*>(tensor)); } return tmpDescriptor; } } void 
__global__ __launch_bounds__(1024) padInputImpl(float* in, int inputH, int 
inputW, int inputCh, int outputH, int outputW, int offsetH, int offsetW, float* 
out, int inputElems) { for(int i = blockDim.x * blockIdx.x + threadIdx.x; i < 
inputElems; i+= blockDim.x*gridDim.x) { int idxB = i/(inputH*inputW*inputCh); 
int rem = (i - idxB*(inputH*inputW*inputCh)); int idxCh = rem/(inputH*inputW); 
int rem1 = rem - idxCh*(inputH*inputW); int idxH = rem1/inputW; int idxCol = 
rem1 - idxH*inputW; if ((idxH < inputH) && (idxCol < inputW)) { int outputR = 
idxH + offsetH; int outputCol = idxCol + offsetW; int outputCh = inputCh; 
out[idxB*(outputH*outputW*outputCh) + idxCh*(outputH*outputW) + 
outputR*(outputW) + outputCol] = in[i]; } } } void 
MWCNNLayerImpl::padInput(float* TfsmDFpPPOscKZifVzSQ, int WIxRBCJtmETvfxpuRuus, int 
WerBmCOBWhvoFbdqfitc, int VenwEUlYwOBrwLVUhgUH, int lHtftnmGBvlSSoGOXVui, int 
lkGLRakytrdNuJCcpYWt, int gWETwFdWHfKuelmlKNCC, int hDaNSVZAofAENeIAiWEw, float* 
jmcFOAbZArjGDNhshSro, int eqOmMKQRpqBqRQCnJmxt) { int tGsvtyAVkrDznETdweDC = 
(eqOmMKQRpqBqRQCnJmxt + 31)/32 * 32; tGsvtyAVkrDznETdweDC = 
(tGsvtyAVkrDznETdweDC < 1024) ? tGsvtyAVkrDznETdweDC : 1024; int 
KZWeXiYFmdpQdsgidKeG = (eqOmMKQRpqBqRQCnJmxt + tGsvtyAVkrDznETdweDC - 
1)/tGsvtyAVkrDznETdweDC; padInputImpl<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>(TfsmDFpPPOscKZifVzSQ, WIxRBCJtmETvfxpuRuus, 
WerBmCOBWhvoFbdqfitc, VenwEUlYwOBrwLVUhgUH, lHtftnmGBvlSSoGOXVui, lkGLRakytrdNuJCcpYWt, 
gWETwFdWHfKuelmlKNCC, hDaNSVZAofAENeIAiWEw, jmcFOAbZArjGDNhshSro, eqOmMKQRpqBqRQCnJmxt); } 
void __global__ __launch_bounds__(1024) fillOutputBufferImpl(signed char* in, 
int inputH, int inputW, int inputCh, int outputH, int outputW, int offsetH, int 
offsetW, signed char* out, int inputElems, int outputCh) { for(int i = 
blockDim.x * blockIdx.x + threadIdx.x; i < inputElems; i+= 
blockDim.x*gridDim.x) { int idxB = i/(inputH*inputW*inputCh); int rem = (i - 
idxB*(inputH*inputW*inputCh)); int idxCh = rem/(inputH*inputW); int rem1 = rem 
- idxCh*(inputH*inputW); int idxH = rem1/inputW; int idxCol = rem1 - 
idxH*inputW; if ((idxH < inputH) && (idxCol < inputW)) { int outputR = idxH + 
offsetH; int outputCol = idxCol + offsetW; *(out + 
idxB*(outputH*outputW*outputCh) + idxCh*(outputH*outputW) + outputR*(outputW) + 
outputCol) = *(in + i); } } } void MWCNNLayerImpl::fillOutputBuffer(signed 
char* TfsmDFpPPOscKZifVzSQ, int WIxRBCJtmETvfxpuRuus, int WerBmCOBWhvoFbdqfitc, int 
VenwEUlYwOBrwLVUhgUH, int lHtftnmGBvlSSoGOXVui, int lkGLRakytrdNuJCcpYWt, int 
gWETwFdWHfKuelmlKNCC, int hDaNSVZAofAENeIAiWEw, signed char* jmcFOAbZArjGDNhshSro, int 
eqOmMKQRpqBqRQCnJmxt, int kkqTyvjYvRFtTOyQUwrF) { int tGsvtyAVkrDznETdweDC 
= (eqOmMKQRpqBqRQCnJmxt < 1024) ? eqOmMKQRpqBqRQCnJmxt : 1024; int 
KZWeXiYFmdpQdsgidKeG = (eqOmMKQRpqBqRQCnJmxt + tGsvtyAVkrDznETdweDC - 
1)/tGsvtyAVkrDznETdweDC; fillOutputBufferImpl<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>(TfsmDFpPPOscKZifVzSQ, WIxRBCJtmETvfxpuRuus, 
WerBmCOBWhvoFbdqfitc, VenwEUlYwOBrwLVUhgUH, lHtftnmGBvlSSoGOXVui, lkGLRakytrdNuJCcpYWt, 
gWETwFdWHfKuelmlKNCC, hDaNSVZAofAENeIAiWEw, jmcFOAbZArjGDNhshSro, eqOmMKQRpqBqRQCnJmxt, 
kkqTyvjYvRFtTOyQUwrF); } void MWCNNLayerImpl::throwAllocationError(const int 
line, const char * file) { char buffer[200]; int numElem = sprintf(buffer, 
"Failed to allocate memory at %d, file %s\n", line, file); throw 
std::runtime_error(buffer); } void 
MWCNNLayerImpl::setDescriptorForINT8(cudnnTensorDescriptor_t& desc, 
MWTensor<signed char>* tensor, cudnnDataType_t dataType, cudnnTensorFormat_t 
dataFormat) { CUDNN_CALL(cudnnSetTensor4dDescriptor(desc, dataFormat, dataType, 
tensor->getBatchSize(),  tensor->getChannels(),  tensor->getHeight(),  
tensor->getWidth()));  }