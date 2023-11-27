#include "MWFCLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"
 MWFCLayerImpl::MWFCLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int XVcMnvCXvZpKICKIjgZi, int lsqeARVLtpJTWezgnTkg, const char* 
xHViLEwTujGGrPZZgmbF,  const char* KCudOrFMfgCzUPMcdePX) : 
MWCNNLayerImpl(layer, ntwk_impl)  , 
CCKWXUFWgrbBMjwfpOBN(XVcMnvCXvZpKICKIjgZi) , 
CDJtexcMbXMWAmnNZsNf(lsqeARVLtpJTWezgnTkg) , vpXxoeEhdEosLSsYXkNG(NULL) , 
wJyXsrUCMgxdIKVIJSyx(NULL) , JCaothdxtQBQxaaitLio(NULL) , 
xHiBGayUfxIpXKkCTDNU(false) { 
CUDNN_CALL(cudnnCreateTensorDescriptor(&JwxFdqOKggeawILBfGgg)); 
createAndAddDescriptor(getLayer()->getOutputTensor(0)->getSourcePortIndex()); 
CUDA_CALL(cudaMalloc((void**)&vpXxoeEhdEosLSsYXkNG, 
sizeof(float)*CCKWXUFWgrbBMjwfpOBN*CDJtexcMbXMWAmnNZsNf)); 
CUDA_CALL(cudaMalloc((void**)&JCaothdxtQBQxaaitLio, 
sizeof(float)*CDJtexcMbXMWAmnNZsNf)); wJyXsrUCMgxdIKVIJSyx = 
MALLOC_CALL(sizeof(float)*CCKWXUFWgrbBMjwfpOBN*CDJtexcMbXMWAmnNZsNf); 
loadWeights(xHViLEwTujGGrPZZgmbF); loadBias(KCudOrFMfgCzUPMcdePX); } 
MWFCLayerImpl::~MWFCLayerImpl() { } void MWFCLayerImpl::propagateSize() { 
MWCNNLayer* fcLayer = getLayer(); MWTensorBase* opTensor = 
fcLayer->getOutputTensor(0); cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensor->getSourcePortIndex()); assert(desc); 
setDescriptor<float>(*desc, static_cast<MWTensor<float>*>(opTensor)); if 
(opTensor->getSequenceLength() == 1) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(JwxFdqOKggeawILBfGgg, CUDNN_TENSOR_NCHW, 
CUDNN_DATA_FLOAT, 1, CDJtexcMbXMWAmnNZsNf, 1, 1)); } else { int dims[5] 
= {1, 1, CDJtexcMbXMWAmnNZsNf, 1, 1}; int strides[5]; 
MWTensorBase::getStrides(dims, 5, strides); 
CUDNN_CALL(cudnnSetTensorNdDescriptor(JwxFdqOKggeawILBfGgg, CUDNN_DATA_FLOAT, 5, 
dims, strides)); } } void MWFCLayerImpl::loadWeights(const char* 
QVgVGfoCXYiYXzPhvVPX) {  FILE* QwUuNuQNtlPXrIwRNiSZ = 
MWCNNLayer::openBinaryFile(QVgVGfoCXYiYXzPhvVPX); assert(QwUuNuQNtlPXrIwRNiSZ); int 
dkLDkRwCBjeybwDHbKiE = CCKWXUFWgrbBMjwfpOBN*CDJtexcMbXMWAmnNZsNf;  
MWCNNLayer::call_fread(wJyXsrUCMgxdIKVIJSyx, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, QVgVGfoCXYiYXzPhvVPX); fclose(QwUuNuQNtlPXrIwRNiSZ); } void 
MWFCLayerImpl::prepareWeights() { if (!xHiBGayUfxIpXKkCTDNU) { int 
dkLDkRwCBjeybwDHbKiE = CCKWXUFWgrbBMjwfpOBN*CDJtexcMbXMWAmnNZsNf; 
MWCNNLayer* fcLayer = getLayer(); MWTensorBase* ipTensor = 
fcLayer->getInputTensor(0); if( ipTensor->getHeight() != 1 && 
ipTensor->getWidth() != 1 ) { float* LgxABSJPBXdCozJkFqTg = 
MALLOC_CALL(sizeof(float)*ipTensor->getHeight()*ipTensor->getWidth()); for(int 
k=0; k<dkLDkRwCBjeybwDHbKiE/ipTensor->getHeight()/ipTensor->getWidth(); k++) { 
for(int i=0; i<ipTensor->getHeight()*ipTensor->getWidth(); i++) 
LgxABSJPBXdCozJkFqTg[i]=wJyXsrUCMgxdIKVIJSyx[k*ipTensor->getHeight()*ipTensor->getWidth()+i]; 
for(int j=0; j<ipTensor->getHeight(); j++) for(int i=0; i<ipTensor->getWidth(); 
i++) 
wJyXsrUCMgxdIKVIJSyx[k*ipTensor->getHeight()*ipTensor->getWidth()+j*ipTensor->getWidth()+i]=LgxABSJPBXdCozJkFqTg[j+i*ipTensor->getHeight()]; 
} free(LgxABSJPBXdCozJkFqTg); } CUDA_CALL(cudaMemcpy(vpXxoeEhdEosLSsYXkNG, 
wJyXsrUCMgxdIKVIJSyx, sizeof(float)*dkLDkRwCBjeybwDHbKiE, 
cudaMemcpyHostToDevice)); free(wJyXsrUCMgxdIKVIJSyx); 
wJyXsrUCMgxdIKVIJSyx = NULL; xHiBGayUfxIpXKkCTDNU = true; } } void 
MWFCLayerImpl::loadBias(const char* QVgVGfoCXYiYXzPhvVPX) { MWCNNLayer* fcLayer 
= getLayer(); MWTensorBase* opTensor = fcLayer->getOutputTensor(0); FILE* 
QwUuNuQNtlPXrIwRNiSZ = MWCNNLayer::openBinaryFile(QVgVGfoCXYiYXzPhvVPX); 
assert(QwUuNuQNtlPXrIwRNiSZ); int dkLDkRwCBjeybwDHbKiE = CDJtexcMbXMWAmnNZsNf;  
float* LgxABSJPBXdCozJkFqTg = MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, QVgVGfoCXYiYXzPhvVPX); CUDA_CALL(cudaMemcpy(JCaothdxtQBQxaaitLio, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice)); 
free(LgxABSJPBXdCozJkFqTg); fclose(QwUuNuQNtlPXrIwRNiSZ); } void 
MWFCLayerImpl::postSetup() { prepareWeights(); } void MWFCLayerImpl::predict() 
{ MWCNNLayer* fcLayer = getLayer(); MWTensorBase* ipTensorBase = 
fcLayer->getInputTensor(0); MWTensorBase* opTensorBase = 
fcLayer->getOutputTensor(0); MWTensor<float>* ipTensor = 
static_cast<MWTensor<float>*>(ipTensorBase); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); int numOutputRows = 
opTensor->getChannels(); int numOutputCols = 
ipTensor->getBatchSize()*ipTensor->getSequenceLength(); int innerDimension = 
ipTensor->getHeight()*ipTensor->getWidth()*ipTensor->getChannels(); int 
UVzBVEOIylFjkSgHwFMp=1; int UWAGLbDcvybdWBtshhsr=1; if(opTensor->getBatchSize() == 1 && 
opTensor->getSequenceLength() == 1) { CUDA_CALL(cudaMemcpy(opTensor->getData(), 
JCaothdxtQBQxaaitLio, sizeof(float)*numOutputRows, cudaMemcpyDeviceToDevice)); 
CUBLAS_CALL(cublasSgemv(*dMxIKDGTITyhdLqIHBLA->getCublasHandle(), CUBLAS_OP_T, 
innerDimension, numOutputRows, getOnePtr(), vpXxoeEhdEosLSsYXkNG, innerDimension, 
ipTensor->getData(), UVzBVEOIylFjkSgHwFMp, getOnePtr(), opTensor->getData(), 
UWAGLbDcvybdWBtshhsr)); } else { 
CUBLAS_CALL(cublasSgemm(*dMxIKDGTITyhdLqIHBLA->getCublasHandle(), CUBLAS_OP_T, 
CUBLAS_OP_N, numOutputRows, numOutputCols, innerDimension, getOnePtr(), 
vpXxoeEhdEosLSsYXkNG, innerDimension, ipTensor->getData(), innerDimension, 
getZeroPtr(), opTensor->getData(), numOutputRows)); cudnnTensorDescriptor_t* 
desc = getDescriptor(opTensor->getSourcePortIndex()); assert(desc); 
CUDNN_CALL(cudnnAddTensor(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), getOnePtr(), 
JwxFdqOKggeawILBfGgg, JCaothdxtQBQxaaitLio, getOnePtr(), *desc, opTensor->getData())); } 
return; } void MWFCLayerImpl::cleanup() { if (vpXxoeEhdEosLSsYXkNG) { 
CUDA_FREE_CALL(vpXxoeEhdEosLSsYXkNG); vpXxoeEhdEosLSsYXkNG = NULL; } 
CUDNN_CALL(cudnnDestroyTensorDescriptor(JwxFdqOKggeawILBfGgg)); if 
(JCaothdxtQBQxaaitLio) { CUDA_FREE_CALL(JCaothdxtQBQxaaitLio); JCaothdxtQBQxaaitLio = NULL; } }