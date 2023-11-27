#include "MWFusedConvReLULayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"
#include <cassert>
#include <cstdio>
 MWFusedConvReLULayerImpl::MWFusedConvReLULayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int filt_H, int filt_W, int numGrps, int 
numChnls, int numFilts, int FshVHIJMRAhtQirYPlZd, int 
GDRXdUDklKFEYEfifhIH, int ClEhcJFlvGCgiavziIag, int 
CZNYmBcNFSZWvaCklqeM, int CufLFODQDXTAPyRqYodN, int 
DCdZnqpcBnvXVgEsLBnz, int AuqaQHxmPQSyYRemQvyX, int 
AzTsxYcYjIEJsGQbeYHm, int eybNKlJCSDUvsznWynwK, const char* 
xHViLEwTujGGrPZZgmbF, const char* KCudOrFMfgCzUPMcdePX) : 
MWCNNLayerImpl(layer, ntwk_impl) , vpXxoeEhdEosLSsYXkNG(NULL) , JCaothdxtQBQxaaitLio(NULL) , 
URgvgDXnZskIYGdtimcU(NULL) , XCnEVUzxqcNgsuUbRonz(NULL) , 
GFienSVKLlDQuZeqAdLC(NULL) , HoqiuUUuJnXGkfDodicJ(NULL) , 
BHuHNDGoRwGRouCxeMbw(filt_H) , BLjrjqvCcCommiXWQLjs (filt_W) , 
BuyZFXzwOMxcePIbCLfl (numGrps) , BkwhtPQUCQKchmmimoXs (numChnls) , 
BlRIQPyqJZORKENzSdYf (numFilts) , FrpxvsDMwwgbpqHXWxmN(FshVHIJMRAhtQirYPlZd) 
, FwLnexHgxHRquTKmNpoa(GDRXdUDklKFEYEfifhIH) , 
CTCbzQMDaLxINPbODdng(ClEhcJFlvGCgiavziIag) , 
CLOUhPjbgggWoXHTtmjC(CZNYmBcNFSZWvaCklqeM) , 
CpMjJjtGOeWOzwxpAAQP(CufLFODQDXTAPyRqYodN) , 
CqtPRJvHlGJFssiPzsOm(DCdZnqpcBnvXVgEsLBnz) , 
AdmgfUbRAfzFeYHxSnQr(AuqaQHxmPQSyYRemQvyX) , 
AwZQzUhuWVLGrWgLHRuM(AzTsxYcYjIEJsGQbeYHm) , 
fxxCPKTclxXPxrdMAkwi(eybNKlJCSDUvsznWynwK) , 
IbSWJNMuIiKbocfQKqXb((CTCbzQMDaLxINPbODdng != CLOUhPjbgggWoXHTtmjC) 
|| (CpMjJjtGOeWOzwxpAAQP != CqtPRJvHlGJFssiPzsOm)) {
#if (CUDNN_MAJOR < 6)
 throw std::runtime_error("Fused ConvReLU Layer only supported for cuDNN 6 or greater");
#else
 dMxIKDGTITyhdLqIHBLA = ntwk_impl; 
CUDNN_CALL(cudnnCreateConvolutionDescriptor(&NZjOkZPwLzQsdEVkwMcX)); 
CUDNN_CALL(cudnnCreateFilterDescriptor(&QhTesEEIHwhNmHSeYbRR)); 
CUDNN_CALL(cudnnCreateTensorDescriptor(&JwxFdqOKggeawILBfGgg));  
CUDNN_CALL(cudnnCreateActivationDescriptor(&oJUVMnJggjhEdQLWzIUC)); 
MWTensorBase* ipTensor_conv = getLayer()->getInputTensor(0); int 
NbunkIVaMPVYgAQHXXYd = CTCbzQMDaLxINPbODdng; int 
NldNILHvuQqQPSAHXxdT = CpMjJjtGOeWOzwxpAAQP; if 
(IbSWJNMuIiKbocfQKqXb) { NbunkIVaMPVYgAQHXXYd = 0; 
NldNILHvuQqQPSAHXxdT = 0; URgvgDXnZskIYGdtimcU = new MWTensor<float>(-1, 
-1, -1, -1, -1, NULL, getLayer(), 0); if (!URgvgDXnZskIYGdtimcU) { 
MWCNNLayerImpl::throwAllocationError(__LINE__ , __FILE__); } 
CUDNN_CALL(cudnnCreateTensorDescriptor(&YCSvyQZBWMDYQXHtyVai)); } else { 
URgvgDXnZskIYGdtimcU = ipTensor_conv; } assert(URgvgDXnZskIYGdtimcU != NULL); 
bYBVtTnVUuGDUlaTmmHp = CTCbzQMDaLxINPbODdng; cQBKlCKXxecGPJrXBXdk = 
CpMjJjtGOeWOzwxpAAQP; 
CUDNN_CALL(cudnnSetConvolution2dDescriptor(NZjOkZPwLzQsdEVkwMcX, 
NbunkIVaMPVYgAQHXXYd, NldNILHvuQqQPSAHXxdT, FrpxvsDMwwgbpqHXWxmN, 
FwLnexHgxHRquTKmNpoa, AdmgfUbRAfzFeYHxSnQr, AwZQzUhuWVLGrWgLHRuM, 
CUDNN_CROSS_CORRELATION, CUDNN_DATA_FLOAT));
#if (FP16_ENABLED == 1 && ( CUDNN_MAJOR > 7 || (CUDNN_MAJOR == 7 && CUDNN_MINOR >= 2) ))
 CUDNN_CALL(cudnnSetConvolutionMathType(NZjOkZPwLzQsdEVkwMcX, CUDNN_TENSOR_OP_MATH_ALLOW_CONVERSION));
#endif
 if (BuyZFXzwOMxcePIbCLfl > 1){ 
CUDNN_CALL(cudnnSetConvolutionGroupCount(NZjOkZPwLzQsdEVkwMcX, 
BuyZFXzwOMxcePIbCLfl)); } 
CUDNN_CALL(cudnnSetActivationDescriptor(oJUVMnJggjhEdQLWzIUC, 
CUDNN_ACTIVATION_RELU, CUDNN_NOT_PROPAGATE_NAN, 0)); int 
euppfEoiaoCTcVgRPVhA = BkwhtPQUCQKchmmimoXs*BuyZFXzwOMxcePIbCLfl; int 
fSbUUBgjKRbNXrHrlOLo = BlRIQPyqJZORKENzSdYf*BuyZFXzwOMxcePIbCLfl; 
CUDNN_CALL(cudnnSetFilter4dDescriptor(QhTesEEIHwhNmHSeYbRR, CUDNN_DATA_FLOAT, 
CUDNN_TENSOR_NCHW, fSbUUBgjKRbNXrHrlOLo, 
euppfEoiaoCTcVgRPVhA/BuyZFXzwOMxcePIbCLfl, BHuHNDGoRwGRouCxeMbw, 
BLjrjqvCcCommiXWQLjs)); 
CUDNN_CALL(cudnnSetTensor4dDescriptor(JwxFdqOKggeawILBfGgg, CUDNN_TENSOR_NCHW, 
CUDNN_DATA_FLOAT, 1, fSbUUBgjKRbNXrHrlOLo, 1, 1)); int weightSize = 
BkwhtPQUCQKchmmimoXs*fSbUUBgjKRbNXrHrlOLo*BHuHNDGoRwGRouCxeMbw*BLjrjqvCcCommiXWQLjs; 
CUDA_CALL(cudaMalloc((void**)&vpXxoeEhdEosLSsYXkNG, sizeof(float)*weightSize)); 
CUDA_CALL(cudaMalloc((void**)&JCaothdxtQBQxaaitLio, 
sizeof(float)*fSbUUBgjKRbNXrHrlOLo)); 
loadWeights(xHViLEwTujGGrPZZgmbF); loadBias(KCudOrFMfgCzUPMcdePX); createAndAddDescriptor(getLayer()->getOutputTensor(0)->getSourcePortIndex());
#endif
 } MWFusedConvReLULayerImpl::~MWFusedConvReLULayerImpl() { } void 
MWFusedConvReLULayerImpl::propagateSize() {
#if (CUDNN_MAJOR >= 6)
 MWTensorBase* ipTensor_conv = getLayer()->getInputTensor(0); int inputH; int 
inputW; if (IbSWJNMuIiKbocfQKqXb) { inputH = 
ipTensor_conv->getHeight() + CTCbzQMDaLxINPbODdng + CLOUhPjbgggWoXHTtmjC; 
inputW = ipTensor_conv->getWidth() + CpMjJjtGOeWOzwxpAAQP + 
CqtPRJvHlGJFssiPzsOm; } else { inputH = ipTensor_conv->getHeight(); inputW = 
ipTensor_conv->getWidth(); } URgvgDXnZskIYGdtimcU->setHeight(inputH); 
URgvgDXnZskIYGdtimcU->setWidth(inputW); 
URgvgDXnZskIYGdtimcU->setChannels(ipTensor_conv->getChannels()); 
URgvgDXnZskIYGdtimcU->setBatchSize(ipTensor_conv->getBatchSize()); 
URgvgDXnZskIYGdtimcU->setSequenceLength(ipTensor_conv->getSequenceLength()); 
assert(URgvgDXnZskIYGdtimcU->getSequenceLength() == 1); if 
(IbSWJNMuIiKbocfQKqXb) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(YCSvyQZBWMDYQXHtyVai, CUDNN_TENSOR_NCHW, 
CUDNN_DATA_FLOAT, URgvgDXnZskIYGdtimcU->getBatchSize(), 
URgvgDXnZskIYGdtimcU->getChannels(), URgvgDXnZskIYGdtimcU->getHeight(), 
URgvgDXnZskIYGdtimcU->getWidth())); } else { YCSvyQZBWMDYQXHtyVai = 
MWCNNLayerImpl::getCuDNNDescriptor(URgvgDXnZskIYGdtimcU); } 
assert(BkwhtPQUCQKchmmimoXs == 
URgvgDXnZskIYGdtimcU->getChannels()/BuyZFXzwOMxcePIbCLfl); MWTensorBase* opTensor 
= getLayer()->getOutputTensor(0); cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensor->getSourcePortIndex()); assert(desc); 
setDescriptor<float>(*desc, static_cast<MWTensor<float>*>(opTensor));
#if (CUDNN_MAJOR < 7)
 { 
CUDNN_CALL(cudnnGetConvolutionForwardAlgorithm(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, QhTesEEIHwhNmHSeYbRR, NZjOkZPwLzQsdEVkwMcX, *desc, 
CUDNN_CONVOLUTION_FWD_PREFER_FASTEST, 0, &NNhshzQGJHLSGjDiVerE)); }
#else
 { const int maxAlgoCount(3); int returnedAlgoCount(-1); 
cudnnConvolutionFwdAlgoPerf_t perf_results[maxAlgoCount]; 
CUDNN_CALL(cudnnGetConvolutionForwardAlgorithm_v7(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, QhTesEEIHwhNmHSeYbRR, NZjOkZPwLzQsdEVkwMcX, *desc, 
maxAlgoCount, &returnedAlgoCount, perf_results)); NNhshzQGJHLSGjDiVerE = 
perf_results[0].algo; }
#endif
 if (CUDNN_VERSION < 7402) fixConvAlgo(); size_t tnTPxeDjBsqLAPkJcPJX = 0; 
CUDNN_CALL(cudnnGetConvolutionForwardWorkspaceSize(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, QhTesEEIHwhNmHSeYbRR, NZjOkZPwLzQsdEVkwMcX, *desc, 
NNhshzQGJHLSGjDiVerE, &tnTPxeDjBsqLAPkJcPJX)); if( tnTPxeDjBsqLAPkJcPJX > 
*dMxIKDGTITyhdLqIHBLA->getProposedWorkSpaceSize() ) { 
dMxIKDGTITyhdLqIHBLA->setProposedWorkSpaceSize(tnTPxeDjBsqLAPkJcPJX); }
#endif
 } void MWFusedConvReLULayerImpl::allocate() { MWTensorBase* ipTensor_conv = 
getLayer()->getInputTensor(0); if (IbSWJNMuIiKbocfQKqXb) { float* 
newInput; int inputH = ipTensor_conv->getHeight() + CTCbzQMDaLxINPbODdng + 
CLOUhPjbgggWoXHTtmjC; int inputW = ipTensor_conv->getWidth() + 
CpMjJjtGOeWOzwxpAAQP + CqtPRJvHlGJFssiPzsOm; int paddedSize = 
ipTensor_conv->getBatchSize() * ipTensor_conv->getChannels() * inputH * inputW; 
CUDA_CALL(cudaMalloc((void**)&newInput, sizeof(float)*paddedSize)); 
CUDA_CALL(cudaMemset(newInput, 0, sizeof(float)*paddedSize)); 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->setData(newInput); } 
XCnEVUzxqcNgsuUbRonz = 
static_cast<MWTensor<float>*>(getLayer()->getOutputTensor(0))->getData(); 
setalpha2Ptr(getZeroPtr()); int numInputs = getLayer()->getNumInputs(); if 
(numInputs == 2) { setalpha2Ptr(getOnePtr()); XCnEVUzxqcNgsuUbRonz = 
static_cast<MWTensor<float>*>(getLayer()->getInputTensor(1))->getData(); } if 
(static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData() == 
XCnEVUzxqcNgsuUbRonz){ int xInputTensorSize = 
getLayer()->getInputTensor(0)->getNumElements(); 
CUDA_CALL(cudaMalloc((void**)&GFienSVKLlDQuZeqAdLC, sizeof(float) * 
xInputTensorSize)); } } void MWFusedConvReLULayerImpl::deallocate() { if 
(URgvgDXnZskIYGdtimcU != getLayer()->getInputTensor(0)) { 
assert(IbSWJNMuIiKbocfQKqXb); 
CUDA_FREE_CALL(static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData()); 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->setData((float*)NULL); } if 
(GFienSVKLlDQuZeqAdLC){ CUDA_FREE_CALL(GFienSVKLlDQuZeqAdLC); 
GFienSVKLlDQuZeqAdLC = NULL;  }  } void 
MWFusedConvReLULayerImpl::predict() { MWCNNLayer* fusedConvReluLayer = 
getLayer(); MWTensorBase* ipTensorBase = fusedConvReluLayer->getInputTensor(); 
MWTensorBase* opTensorBase = fusedConvReluLayer->getOutputTensor(); 
MWTensor<float>* ipTensor = static_cast<MWTensor<float>*>(ipTensorBase); 
MWTensor<float>* opTensor = static_cast<MWTensor<float>*>(opTensorBase); if 
(URgvgDXnZskIYGdtimcU != fusedConvReluLayer->getInputTensor()) { 
CUDA_CALL(cudaMemset(static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData(), 
0, sizeof(float)*URgvgDXnZskIYGdtimcU->getNumElements())); 
MWCNNLayerImpl::padInput(ipTensor->getData(), ipTensor->getHeight(), 
ipTensor->getWidth(), ipTensor->getChannels(), URgvgDXnZskIYGdtimcU->getHeight(), 
URgvgDXnZskIYGdtimcU->getWidth(), bYBVtTnVUuGDUlaTmmHp, cQBKlCKXxecGPJrXBXdk, 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData(), 
ipTensor->getNumElements()); } cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensor->getSourcePortIndex()); assert(desc);
#if (CUDNN_MAJOR >= 6)
 assert(opTensor->getData() != 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData() || 
(getLayer()->getNumInputs() == 2)); float* rIcMzXptfYweLArNRnBw; if 
(static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData() == 
XCnEVUzxqcNgsuUbRonz){ CUDA_CALL(cudaMemcpy(GFienSVKLlDQuZeqAdLC, 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData(), sizeof(float) * 
opTensorBase->getNumElements(), cudaMemcpyDeviceToDevice)); 
rIcMzXptfYweLArNRnBw = GFienSVKLlDQuZeqAdLC; }else{ 
rIcMzXptfYweLArNRnBw = 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData(); } 
CUDNN_CALL(cudnnConvolutionBiasActivationForward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
getOnePtr(), YCSvyQZBWMDYQXHtyVai, rIcMzXptfYweLArNRnBw, 
QhTesEEIHwhNmHSeYbRR, vpXxoeEhdEosLSsYXkNG, NZjOkZPwLzQsdEVkwMcX, NNhshzQGJHLSGjDiVerE, 
dMxIKDGTITyhdLqIHBLA->getWorkSpace(), 
*dMxIKDGTITyhdLqIHBLA->getAllocatedWorkSpaceSize(), getalpha2Ptr(),  *desc,  
XCnEVUzxqcNgsuUbRonz,  JwxFdqOKggeawILBfGgg, JCaothdxtQBQxaaitLio, oJUVMnJggjhEdQLWzIUC, 
*desc, opTensor->getData()));
#endif
 } void MWFusedConvReLULayerImpl::cleanup() { 
CUDNN_CALL(cudnnDestroyConvolutionDescriptor(NZjOkZPwLzQsdEVkwMcX)); 
CUDNN_CALL(cudnnDestroyFilterDescriptor(QhTesEEIHwhNmHSeYbRR)); 
CUDNN_CALL(cudnnDestroyActivationDescriptor(oJUVMnJggjhEdQLWzIUC)); if 
(vpXxoeEhdEosLSsYXkNG) { CUDA_FREE_CALL(vpXxoeEhdEosLSsYXkNG); vpXxoeEhdEosLSsYXkNG = NULL; } 
CUDNN_CALL(cudnnDestroyTensorDescriptor(JwxFdqOKggeawILBfGgg)); if 
(JCaothdxtQBQxaaitLio) { CUDA_FREE_CALL(JCaothdxtQBQxaaitLio); JCaothdxtQBQxaaitLio = NULL; } if 
(URgvgDXnZskIYGdtimcU != getLayer()->getInputTensor(0)) { 
assert(IbSWJNMuIiKbocfQKqXb); 
CUDNN_CALL(cudnnDestroyTensorDescriptor(YCSvyQZBWMDYQXHtyVai)); } } void 
MWFusedConvReLULayerImpl::loadWeights(const char* QVgVGfoCXYiYXzPhvVPX) { FILE* 
QwUuNuQNtlPXrIwRNiSZ = MWCNNLayer::openBinaryFile(QVgVGfoCXYiYXzPhvVPX); 
assert(QwUuNuQNtlPXrIwRNiSZ); int dkLDkRwCBjeybwDHbKiE = 
BkwhtPQUCQKchmmimoXs*BuyZFXzwOMxcePIbCLfl*BlRIQPyqJZORKENzSdYf*BHuHNDGoRwGRouCxeMbw*BLjrjqvCcCommiXWQLjs; 
 float* LgxABSJPBXdCozJkFqTg = MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, QVgVGfoCXYiYXzPhvVPX); CUDA_CALL(cudaMemcpy(vpXxoeEhdEosLSsYXkNG, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice));
#if 0
 printf("%s loaded. Size = %d. %f\n", QVgVGfoCXYiYXzPhvVPX, dkLDkRwCBjeybwDHbKiE, LgxABSJPBXdCozJkFqTg[0]);
#endif
 free(LgxABSJPBXdCozJkFqTg); fclose(QwUuNuQNtlPXrIwRNiSZ); return; } void 
MWFusedConvReLULayerImpl::loadBias(const char* QVgVGfoCXYiYXzPhvVPX) { FILE* 
QwUuNuQNtlPXrIwRNiSZ = MWCNNLayer::openBinaryFile(QVgVGfoCXYiYXzPhvVPX); 
assert(QwUuNuQNtlPXrIwRNiSZ); int dkLDkRwCBjeybwDHbKiE = 
BuyZFXzwOMxcePIbCLfl*BlRIQPyqJZORKENzSdYf;  float* LgxABSJPBXdCozJkFqTg = 
MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, QVgVGfoCXYiYXzPhvVPX); CUDA_CALL(cudaMemcpy(JCaothdxtQBQxaaitLio, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice)); 
free(LgxABSJPBXdCozJkFqTg); fclose(QwUuNuQNtlPXrIwRNiSZ); return; } void 
MWFusedConvReLULayerImpl::postSetup() { if (dMxIKDGTITyhdLqIHBLA->getAutoTune()) 
{ getConvAlgoTuned(); } else { getConvAlgoWorkSpaceLimit(); } } void 
MWFusedConvReLULayerImpl::getConvAlgoTuned() { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); cudnnConvolutionFwdAlgoPerf_t 
perf_results[3]; cudnnTensorDescriptor_t* desc = 
getDescriptor(getLayer()->getOutputTensor()->getSourcePortIndex()); 
assert(desc); int returnedAlgoCount; 
CUDNN_CALL(cudnnFindConvolutionForwardAlgorithmEx(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, 
static_cast<MWTensor<float>*>(URgvgDXnZskIYGdtimcU)->getData(), 
QhTesEEIHwhNmHSeYbRR, vpXxoeEhdEosLSsYXkNG, NZjOkZPwLzQsdEVkwMcX, *desc, 
opTensor->getData(), 3, &returnedAlgoCount, &perf_results[0], 
dMxIKDGTITyhdLqIHBLA->getWorkSpace(), 
*dMxIKDGTITyhdLqIHBLA->getAllocatedWorkSpaceSize())); NNhshzQGJHLSGjDiVerE = 
perf_results[0].algo; if (CUDNN_VERSION < 7402) fixConvAlgo(); } void 
MWFusedConvReLULayerImpl::getConvAlgoWorkSpaceLimit() { 
cudnnTensorDescriptor_t* desc = 
getDescriptor(getLayer()->getOutputTensor()->getSourcePortIndex()); assert(desc);
#if (CUDNN_MAJOR < 8)
 
CUDNN_CALL(cudnnGetConvolutionForwardAlgorithm(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, QhTesEEIHwhNmHSeYbRR, NZjOkZPwLzQsdEVkwMcX, *desc, 
CUDNN_CONVOLUTION_FWD_SPECIFY_WORKSPACE_LIMIT, 
*dMxIKDGTITyhdLqIHBLA->getAllocatedWorkSpaceSize(), &NNhshzQGJHLSGjDiVerE));
#else
 int maxAlgoCount(-1); 
CUDNN_CALL(cudnnGetConvolutionForwardAlgorithmMaxCount(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
&maxAlgoCount)); int returnedAlgoCount(-1); 
std::vector<cudnnConvolutionFwdAlgoPerf_t> perf_results(maxAlgoCount);  
CUDNN_CALL(cudnnGetConvolutionForwardAlgorithm_v7(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, QhTesEEIHwhNmHSeYbRR, NZjOkZPwLzQsdEVkwMcX, *desc, 
maxAlgoCount, &returnedAlgoCount, &perf_results[0])); 
cudnnConvolutionFwdAlgoPerf_t nextFastest; bool algoFound(false); for (int i = 
0; i < returnedAlgoCount; ++i) { nextFastest = perf_results[i]; if 
(nextFastest.memory <= *dMxIKDGTITyhdLqIHBLA->getAllocatedWorkSpaceSize()) { 
NNhshzQGJHLSGjDiVerE = nextFastest.algo; algoFound = true; break; } } assert(algoFound);
#endif
 if (CUDNN_VERSION < 7402) fixConvAlgo(); } void 
MWFusedConvReLULayerImpl::fixConvAlgo() { int inputH = 
URgvgDXnZskIYGdtimcU->getHeight(); int inputW = URgvgDXnZskIYGdtimcU->getWidth(); 
if (NNhshzQGJHLSGjDiVerE == CUDNN_CONVOLUTION_FWD_ALGO_FFT && (inputH > 64 || 
inputW > 64)) { NNhshzQGJHLSGjDiVerE = CUDNN_CONVOLUTION_FWD_ALGO_IMPLICIT_GEMM; 
} }