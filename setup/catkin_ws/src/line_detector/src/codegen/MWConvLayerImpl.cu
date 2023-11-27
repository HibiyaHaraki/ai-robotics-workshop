#include "MWConvLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"
#include <cassert>
#include <cstdio>
 MWConvLayerImpl::MWConvLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int filt_H, int filt_W, int numGrps, int numChnls, int numFilts, int 
FshVHIJMRAhtQirYPlZd, int GDRXdUDklKFEYEfifhIH, int 
ClEhcJFlvGCgiavziIag, int CZNYmBcNFSZWvaCklqeM, int 
CufLFODQDXTAPyRqYodN, int DCdZnqpcBnvXVgEsLBnz, int 
AuqaQHxmPQSyYRemQvyX, int AzTsxYcYjIEJsGQbeYHm, const 
char* xHViLEwTujGGrPZZgmbF, const char* KCudOrFMfgCzUPMcdePX) : 
MWCNNLayerImpl(layer, ntwk_impl) , vpXxoeEhdEosLSsYXkNG(NULL) , JCaothdxtQBQxaaitLio(NULL) , 
TfsmDFpPPOscKZifVzSQ(NULL) , BHuHNDGoRwGRouCxeMbw(filt_H) , BLjrjqvCcCommiXWQLjs 
(filt_W) , BuyZFXzwOMxcePIbCLfl (numGrps) , BkwhtPQUCQKchmmimoXs (numChnls) , 
BlRIQPyqJZORKENzSdYf (numFilts) , 
AdmgfUbRAfzFeYHxSnQr(AuqaQHxmPQSyYRemQvyX) , 
AwZQzUhuWVLGrWgLHRuM(AzTsxYcYjIEJsGQbeYHm) , 
CTCbzQMDaLxINPbODdng(ClEhcJFlvGCgiavziIag) , 
CLOUhPjbgggWoXHTtmjC(CZNYmBcNFSZWvaCklqeM) , 
CpMjJjtGOeWOzwxpAAQP(CufLFODQDXTAPyRqYodN) , 
CqtPRJvHlGJFssiPzsOm(DCdZnqpcBnvXVgEsLBnz) , 
FrpxvsDMwwgbpqHXWxmN(FshVHIJMRAhtQirYPlZd) , 
FwLnexHgxHRquTKmNpoa(GDRXdUDklKFEYEfifhIH) , 
IbSWJNMuIiKbocfQKqXb((CTCbzQMDaLxINPbODdng != CLOUhPjbgggWoXHTtmjC) 
|| (CpMjJjtGOeWOzwxpAAQP != CqtPRJvHlGJFssiPzsOm)) { dMxIKDGTITyhdLqIHBLA = 
ntwk_impl; CUDNN_CALL(cudnnCreateConvolutionDescriptor(&NZjOkZPwLzQsdEVkwMcX)); 
CUDNN_CALL(cudnnCreateFilterDescriptor(&QhTesEEIHwhNmHSeYbRR)); 
CUDNN_CALL(cudnnCreateTensorDescriptor(&JwxFdqOKggeawILBfGgg));  MWCNNLayer* 
convLayer = getLayer(); MWTensorBase* ipTensor = convLayer->getInputTensor(0); 
if (IbSWJNMuIiKbocfQKqXb) { TfsmDFpPPOscKZifVzSQ = new MWTensor<float>(-1, 
-1, -1, -1, -1, NULL, getLayer(), 0); if (!TfsmDFpPPOscKZifVzSQ) { 
MWCNNLayerImpl::throwAllocationError(__LINE__ , __FILE__); } 
CUDNN_CALL(cudnnCreateTensorDescriptor(&YCSvyQZBWMDYQXHtyVai)); } else { 
TfsmDFpPPOscKZifVzSQ = ipTensor; } assert(TfsmDFpPPOscKZifVzSQ != NULL); int 
NbunkIVaMPVYgAQHXXYd; int NldNILHvuQqQPSAHXxdT; if 
(IbSWJNMuIiKbocfQKqXb) { NbunkIVaMPVYgAQHXXYd = 0;  
NldNILHvuQqQPSAHXxdT = 0; } else { NbunkIVaMPVYgAQHXXYd = 
CTCbzQMDaLxINPbODdng; NldNILHvuQqQPSAHXxdT = CpMjJjtGOeWOzwxpAAQP; } 
bYBVtTnVUuGDUlaTmmHp = CTCbzQMDaLxINPbODdng; cQBKlCKXxecGPJrXBXdk = CpMjJjtGOeWOzwxpAAQP;
#if (CUDNN_MAJOR <= 5)
 { if ((AdmgfUbRAfzFeYHxSnQr != 1) && (AwZQzUhuWVLGrWgLHRuM != 1)){ 
printf("Dilated Convolution only supported for cuDNN 6 or greater "); throw 
std::runtime_error("Unsupported Dilation Factor"); } 
CUDNN_CALL(cudnnSetConvolution2dDescriptor(NZjOkZPwLzQsdEVkwMcX, 
NbunkIVaMPVYgAQHXXYd, NldNILHvuQqQPSAHXxdT, FrpxvsDMwwgbpqHXWxmN, 
FwLnexHgxHRquTKmNpoa, 1, 1, CUDNN_CROSS_CORRELATION));  }
#else
 { CUDNN_CALL(cudnnSetConvolution2dDescriptor(NZjOkZPwLzQsdEVkwMcX, 
NbunkIVaMPVYgAQHXXYd, NldNILHvuQqQPSAHXxdT, FrpxvsDMwwgbpqHXWxmN, 
FwLnexHgxHRquTKmNpoa, AdmgfUbRAfzFeYHxSnQr, AwZQzUhuWVLGrWgLHRuM, 
CUDNN_CROSS_CORRELATION, CUDNN_DATA_FLOAT)); }
#endif
#if (FP16_ENABLED == 1 && ( CUDNN_MAJOR > 7 || (CUDNN_MAJOR == 7 && CUDNN_MINOR >= 2) ))
 CUDNN_CALL(cudnnSetConvolutionMathType(NZjOkZPwLzQsdEVkwMcX, CUDNN_TENSOR_OP_MATH_ALLOW_CONVERSION));
#endif
 if (BuyZFXzwOMxcePIbCLfl > 1){ 
CUDNN_CALL(cudnnSetConvolutionGroupCount(NZjOkZPwLzQsdEVkwMcX, 
BuyZFXzwOMxcePIbCLfl)); } int euppfEoiaoCTcVgRPVhA = 
BkwhtPQUCQKchmmimoXs*BuyZFXzwOMxcePIbCLfl; int fSbUUBgjKRbNXrHrlOLo = 
BlRIQPyqJZORKENzSdYf*BuyZFXzwOMxcePIbCLfl; 
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
loadWeights(xHViLEwTujGGrPZZgmbF); loadBias(KCudOrFMfgCzUPMcdePX); 
createAndAddDescriptor(getLayer()->getOutputTensor()->getSourcePortIndex()); } 
void MWConvLayerImpl::propagateSize() { MWTensorBase* ipTensor = 
getLayer()->getInputTensor(0); int inputH; int inputW; if 
(IbSWJNMuIiKbocfQKqXb) { inputH = ipTensor->getHeight() + 
CTCbzQMDaLxINPbODdng + CLOUhPjbgggWoXHTtmjC; inputW = ipTensor->getWidth() + 
CpMjJjtGOeWOzwxpAAQP + CqtPRJvHlGJFssiPzsOm; } else { inputH = 
ipTensor->getHeight(); inputW = ipTensor->getWidth(); } 
TfsmDFpPPOscKZifVzSQ->setHeight(inputH); TfsmDFpPPOscKZifVzSQ->setWidth(inputW); 
TfsmDFpPPOscKZifVzSQ->setChannels(ipTensor->getChannels()); 
TfsmDFpPPOscKZifVzSQ->setBatchSize(ipTensor->getBatchSize()); 
TfsmDFpPPOscKZifVzSQ->setSequenceLength(ipTensor->getSequenceLength()); 
assert(TfsmDFpPPOscKZifVzSQ->getSequenceLength() == 1); if 
(IbSWJNMuIiKbocfQKqXb) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(YCSvyQZBWMDYQXHtyVai, CUDNN_TENSOR_NCHW, 
CUDNN_DATA_FLOAT, TfsmDFpPPOscKZifVzSQ->getBatchSize(), TfsmDFpPPOscKZifVzSQ->getChannels(), 
TfsmDFpPPOscKZifVzSQ->getHeight(), TfsmDFpPPOscKZifVzSQ->getWidth())); } else { 
YCSvyQZBWMDYQXHtyVai = MWCNNLayerImpl::getCuDNNDescriptor(TfsmDFpPPOscKZifVzSQ); } 
MWTensorBase* opTensor = getLayer()->getOutputTensor(0); 
cudnnTensorDescriptor_t* desc = getDescriptor(opTensor->getSourcePortIndex()); 
assert(desc); setDescriptor<float>(*desc, static_cast<MWTensor<float>*>(opTensor));
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
 size_t tnTPxeDjBsqLAPkJcPJX = 0; 
CUDNN_CALL(cudnnGetConvolutionForwardWorkspaceSize( 
*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), YCSvyQZBWMDYQXHtyVai, 
QhTesEEIHwhNmHSeYbRR, NZjOkZPwLzQsdEVkwMcX, *desc, NNhshzQGJHLSGjDiVerE, 
&tnTPxeDjBsqLAPkJcPJX)); if (tnTPxeDjBsqLAPkJcPJX > 
*dMxIKDGTITyhdLqIHBLA->getProposedWorkSpaceSize()) { 
dMxIKDGTITyhdLqIHBLA->setProposedWorkSpaceSize(tnTPxeDjBsqLAPkJcPJX); } } void 
MWConvLayerImpl::allocate() { MWTensorBase* ipTensor = 
getLayer()->getInputTensor(0); if (IbSWJNMuIiKbocfQKqXb) { float* 
newInput; int inputH = ipTensor->getHeight() + CTCbzQMDaLxINPbODdng + 
CLOUhPjbgggWoXHTtmjC; int inputW = ipTensor->getWidth() + 
CpMjJjtGOeWOzwxpAAQP + CqtPRJvHlGJFssiPzsOm; int paddedSize = 
ipTensor->getBatchSize() * ipTensor->getChannels() * inputH * inputW; 
CUDA_CALL(cudaMalloc((void**)&newInput, sizeof(float)*paddedSize)); 
CUDA_CALL(cudaMemset(newInput, 0, sizeof(float)*paddedSize)); 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->setData(newInput); } } void 
MWConvLayerImpl::deallocate() { if (TfsmDFpPPOscKZifVzSQ != 
getLayer()->getInputTensor(0)) { assert(IbSWJNMuIiKbocfQKqXb); 
CUDA_FREE_CALL(static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData()); 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->setData((float*)NULL); } } void 
MWConvLayerImpl::predict() { MWCNNLayer* convLayer = getLayer(); MWTensorBase* 
ipTensorBase = convLayer->getInputTensor(); MWTensorBase* opTensorBase = 
convLayer->getOutputTensor(); MWTensor<float>* ipTensor = 
static_cast<MWTensor<float>*>(ipTensorBase); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); if (TfsmDFpPPOscKZifVzSQ != 
convLayer->getInputTensor()) { 
CUDA_CALL(cudaMemset(static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), 
0, sizeof(float)*TfsmDFpPPOscKZifVzSQ->getNumElements()));  
MWCNNLayerImpl::padInput(ipTensor->getData(), ipTensor->getHeight(), 
ipTensor->getWidth(), ipTensor->getChannels(), TfsmDFpPPOscKZifVzSQ->getHeight(), 
TfsmDFpPPOscKZifVzSQ->getWidth(), bYBVtTnVUuGDUlaTmmHp, cQBKlCKXxecGPJrXBXdk, 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), 
ipTensor->getNumElements()); } assert(opTensor->getData() != 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData()); 
cudnnTensorDescriptor_t* desc = getDescriptor(opTensor->getSourcePortIndex()); 
assert(desc); 
CUDNN_CALL(cudnnConvolutionForward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
getOnePtr(), YCSvyQZBWMDYQXHtyVai, 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), QhTesEEIHwhNmHSeYbRR, 
vpXxoeEhdEosLSsYXkNG, NZjOkZPwLzQsdEVkwMcX, NNhshzQGJHLSGjDiVerE, 
dMxIKDGTITyhdLqIHBLA->getWorkSpace(), 
*dMxIKDGTITyhdLqIHBLA->getAllocatedWorkSpaceSize(), getZeroPtr(), *desc, 
opTensor->getData())); 
CUDNN_CALL(cudnnAddTensor(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), getOnePtr(), 
JwxFdqOKggeawILBfGgg, JCaothdxtQBQxaaitLio, getOnePtr(), *desc, opTensor->getData())); } 
void MWConvLayerImpl::cleanup() { 
CUDNN_CALL(cudnnDestroyConvolutionDescriptor(NZjOkZPwLzQsdEVkwMcX)); 
CUDNN_CALL(cudnnDestroyFilterDescriptor(QhTesEEIHwhNmHSeYbRR)); if 
(vpXxoeEhdEosLSsYXkNG) { CUDA_FREE_CALL(vpXxoeEhdEosLSsYXkNG); vpXxoeEhdEosLSsYXkNG = NULL; } 
CUDNN_CALL(cudnnDestroyTensorDescriptor(JwxFdqOKggeawILBfGgg)); if 
(JCaothdxtQBQxaaitLio) { CUDA_FREE_CALL(JCaothdxtQBQxaaitLio); JCaothdxtQBQxaaitLio = NULL; } if 
(TfsmDFpPPOscKZifVzSQ != getLayer()->getInputTensor(0)) { 
assert(IbSWJNMuIiKbocfQKqXb); 
CUDNN_CALL(cudnnDestroyTensorDescriptor(YCSvyQZBWMDYQXHtyVai)); } } void 
MWConvLayerImpl::loadWeights(const char* QVgVGfoCXYiYXzPhvVPX) {  FILE* 
QwUuNuQNtlPXrIwRNiSZ = MWCNNLayer::openBinaryFile(QVgVGfoCXYiYXzPhvVPX); 
assert(QwUuNuQNtlPXrIwRNiSZ); int dkLDkRwCBjeybwDHbKiE = 
BkwhtPQUCQKchmmimoXs*BlRIQPyqJZORKENzSdYf*BuyZFXzwOMxcePIbCLfl*BHuHNDGoRwGRouCxeMbw*BLjrjqvCcCommiXWQLjs; 
 float* LgxABSJPBXdCozJkFqTg = MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, QVgVGfoCXYiYXzPhvVPX); CUDA_CALL(cudaMemcpy(vpXxoeEhdEosLSsYXkNG, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice)); 
fclose(QwUuNuQNtlPXrIwRNiSZ); free(LgxABSJPBXdCozJkFqTg); } void 
MWConvLayerImpl::loadBias(const char* QVgVGfoCXYiYXzPhvVPX) { FILE* 
QwUuNuQNtlPXrIwRNiSZ = MWCNNLayer::openBinaryFile(QVgVGfoCXYiYXzPhvVPX);  
assert(QwUuNuQNtlPXrIwRNiSZ); int dkLDkRwCBjeybwDHbKiE = 
BlRIQPyqJZORKENzSdYf*BuyZFXzwOMxcePIbCLfl;  float* LgxABSJPBXdCozJkFqTg = 
MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, QVgVGfoCXYiYXzPhvVPX); CUDA_CALL(cudaMemcpy(JCaothdxtQBQxaaitLio, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice)); 
free(LgxABSJPBXdCozJkFqTg); fclose(QwUuNuQNtlPXrIwRNiSZ); } void 
MWConvLayerImpl::postSetup() { if (dMxIKDGTITyhdLqIHBLA->getAutoTune()) { 
getConvAlgoTuned(); } else { getConvAlgoWorkSpaceLimit(); } } void 
MWConvLayerImpl::getConvAlgoTuned() { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); cudnnConvolutionFwdAlgoPerf_t 
perf_results[3]; cudnnTensorDescriptor_t* desc = 
getDescriptor(getLayer()->getOutputTensor()->getSourcePortIndex()); 
assert(desc); int returnedAlgoCount; 
CUDNN_CALL(cudnnFindConvolutionForwardAlgorithmEx(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
YCSvyQZBWMDYQXHtyVai, static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), 
QhTesEEIHwhNmHSeYbRR, vpXxoeEhdEosLSsYXkNG, NZjOkZPwLzQsdEVkwMcX, *desc, 
opTensor->getData(), 3, &returnedAlgoCount, &perf_results[0], 
dMxIKDGTITyhdLqIHBLA->getWorkSpace(), 
*dMxIKDGTITyhdLqIHBLA->getAllocatedWorkSpaceSize())); NNhshzQGJHLSGjDiVerE = 
perf_results[0].algo; } void MWConvLayerImpl::getConvAlgoWorkSpaceLimit() { 
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
 }