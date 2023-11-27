#include "MWAvgPoolingLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"
 MWAvgPoolingLayerImpl::MWAvgPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int DSsxcjIrUgZCKZovyNQf, int 
EvebzoroiuKkIxwjkGnD, int FshVHIJMRAhtQirYPlZd, int GDRXdUDklKFEYEfifhIH, 
int ClEhcJFlvGCgiavziIag, int CZNYmBcNFSZWvaCklqeM, int 
CufLFODQDXTAPyRqYodN, int DCdZnqpcBnvXVgEsLBnz, int 
nlIRrOJaFuVaywxOqOyb, const char* ABtNoHVrQOgivJIJagNR) : 
MWCNNLayerImpl(layer, ntwk_impl) , TfsmDFpPPOscKZifVzSQ(NULL) , 
DRzwhbNPpftRRIXXfHzd(DSsxcjIrUgZCKZovyNQf) , 
EfvWctmlsWAPsxXgdKWf(EvebzoroiuKkIxwjkGnD) , 
DGzdAcREJHGXjyRzNjJV(DSsxcjIrUgZCKZovyNQf) , 
ECTnqgWHyHCHCLBZlffd(EvebzoroiuKkIxwjkGnD) , 
FrpxvsDMwwgbpqHXWxmN(FshVHIJMRAhtQirYPlZd) , 
FwLnexHgxHRquTKmNpoa(GDRXdUDklKFEYEfifhIH) , 
CTCbzQMDaLxINPbODdng(ClEhcJFlvGCgiavziIag) , 
CLOUhPjbgggWoXHTtmjC(CZNYmBcNFSZWvaCklqeM) , 
CpMjJjtGOeWOzwxpAAQP(CufLFODQDXTAPyRqYodN) , 
CqtPRJvHlGJFssiPzsOm(DCdZnqpcBnvXVgEsLBnz) , 
IbSWJNMuIiKbocfQKqXb((CTCbzQMDaLxINPbODdng != CLOUhPjbgggWoXHTtmjC) 
|| (CpMjJjtGOeWOzwxpAAQP != CqtPRJvHlGJFssiPzsOm)) , 
muwRQxtWMMXAPxSuMYBw(ClEhcJFlvGCgiavziIag) , 
nDsbARncmIrIaLubvLVZ(CufLFODQDXTAPyRqYodN) , 
pFoPPXxxFRbjXXxQWItv(std::pow(2, 
nlIRrOJaFuVaywxOqOyb)) , 
vjDFlBZzKvbpPseAtMBP(std::string{"INT8x4"}.compare(ABtNoHVrQOgivJIJagNR) 
== 0){ CUDNN_CALL(cudnnCreatePoolingDescriptor(&mtolGPkUMBYDlSSqrRzc)); 
MWTensorBase* ipTensor = getLayer()->getInputTensor(0); if 
(IbSWJNMuIiKbocfQKqXb) { assert(ipTensor->isFloat()); 
muwRQxtWMMXAPxSuMYBw = 0;  nDsbARncmIrIaLubvLVZ = 0; 
TfsmDFpPPOscKZifVzSQ = new MWTensor<float>(-1, -1, -1, -1, -1, NULL, getLayer(), 0); 
if (!TfsmDFpPPOscKZifVzSQ) { MWCNNLayerImpl::throwAllocationError(__LINE__ , 
__FILE__); } CUDNN_CALL(cudnnCreateTensorDescriptor(&YCSvyQZBWMDYQXHtyVai));  } 
else { TfsmDFpPPOscKZifVzSQ = ipTensor;  } assert(TfsmDFpPPOscKZifVzSQ != NULL); 
MWTensorBase* opTensorBase = getLayer()->getOutputTensor(0); 
createAndAddDescriptor(opTensorBase->getSourcePortIndex()); if 
(opTensorBase->isInt8()) { 
CUDNN_CALL(cudnnCreateTensorDescriptor(&JABfZsGuaCAmcRcqOYEO)); } } 
MWAvgPoolingLayerImpl::~MWAvgPoolingLayerImpl() { } void 
MWAvgPoolingLayerImpl::propagateSize() { MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(0); MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0);  if ((DRzwhbNPpftRRIXXfHzd == -1) && 
(EfvWctmlsWAPsxXgdKWf == -1)) { DGzdAcREJHGXjyRzNjJV = 
ipTensorBase->getHeight(); ECTnqgWHyHCHCLBZlffd = ipTensorBase->getWidth(); } int 
inputH; int inputW; if (IbSWJNMuIiKbocfQKqXb) { inputH = 
ipTensorBase->getHeight() + CTCbzQMDaLxINPbODdng + CLOUhPjbgggWoXHTtmjC;  
inputW = ipTensorBase->getWidth() + CpMjJjtGOeWOzwxpAAQP + 
CqtPRJvHlGJFssiPzsOm; } else { inputH = ipTensorBase->getHeight(); inputW = 
ipTensorBase->getWidth(); } TfsmDFpPPOscKZifVzSQ->setHeight(inputH); 
TfsmDFpPPOscKZifVzSQ->setWidth(inputW); 
TfsmDFpPPOscKZifVzSQ->setChannels(ipTensorBase->getChannels()); 
TfsmDFpPPOscKZifVzSQ->setBatchSize(ipTensorBase->getBatchSize()); 
TfsmDFpPPOscKZifVzSQ->setSequenceLength(ipTensorBase->getSequenceLength()); 
assert(TfsmDFpPPOscKZifVzSQ->getSequenceLength() == 1); 
CUDNN_CALL(cudnnSetPooling2dDescriptor(mtolGPkUMBYDlSSqrRzc,  
CUDNN_POOLING_AVERAGE_COUNT_INCLUDE_PADDING,  CUDNN_NOT_PROPAGATE_NAN,  
DGzdAcREJHGXjyRzNjJV,  ECTnqgWHyHCHCLBZlffd,  muwRQxtWMMXAPxSuMYBw,  
nDsbARncmIrIaLubvLVZ,  FrpxvsDMwwgbpqHXWxmN,  FwLnexHgxHRquTKmNpoa));  
cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensorBase->getSourcePortIndex()); assert(desc); if 
(opTensorBase->isInt8()) { if (vjDFlBZzKvbpPseAtMBP) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(JABfZsGuaCAmcRcqOYEO, 
CUDNN_TENSOR_NCHW_VECT_C,  CUDNN_DATA_INT8x4,  ipTensorBase->getBatchSize(),  
ipTensorBase->getChannels(),  ipTensorBase->getHeight(),  
ipTensorBase->getWidth())  ); MWCNNLayerImpl::setDescriptorForINT8(*desc, 
static_cast<MWTensor<signed char>*>(opTensorBase), CUDNN_DATA_INT8x4, 
CUDNN_TENSOR_NCHW_VECT_C );  } else { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(JABfZsGuaCAmcRcqOYEO, 
CUDNN_TENSOR_NCHW, CUDNN_DATA_INT8, ipTensorBase->getBatchSize(), 
ipTensorBase->getChannels(), ipTensorBase->getHeight(), 
ipTensorBase->getWidth())); MWCNNLayerImpl::setDescriptorForINT8(*desc, 
static_cast<MWTensor<signed char>*>(opTensorBase), CUDNN_DATA_INT8, 
CUDNN_TENSOR_NCHW); } } else { if (IbSWJNMuIiKbocfQKqXb) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(YCSvyQZBWMDYQXHtyVai, CUDNN_TENSOR_NCHW, 
CUDNN_DATA_FLOAT, TfsmDFpPPOscKZifVzSQ->getBatchSize(), TfsmDFpPPOscKZifVzSQ->getChannels(), 
TfsmDFpPPOscKZifVzSQ->getHeight(), TfsmDFpPPOscKZifVzSQ->getWidth())); } else { 
YCSvyQZBWMDYQXHtyVai = MWCNNLayerImpl::getCuDNNDescriptor(TfsmDFpPPOscKZifVzSQ); }  
setDescriptor<float>(*desc, static_cast<MWTensor<float>*>(opTensorBase)); } } 
void MWAvgPoolingLayerImpl::allocate() { MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(0); if (IbSWJNMuIiKbocfQKqXb) { float* 
newInput; int inputH = ipTensorBase->getHeight() + CTCbzQMDaLxINPbODdng + 
CLOUhPjbgggWoXHTtmjC;  int inputW = ipTensorBase->getWidth() + 
CpMjJjtGOeWOzwxpAAQP + CqtPRJvHlGJFssiPzsOm; int paddedSize = 
ipTensorBase->getBatchSize() * ipTensorBase->getChannels() * inputH * inputW; 
CUDA_CALL(cudaMalloc((void**)&newInput, sizeof(float)*paddedSize)); 
CUDA_CALL(cudaMemset(newInput, 0, sizeof(float)*paddedSize)); 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->setData(newInput); } } void 
MWAvgPoolingLayerImpl::deallocate() { if (TfsmDFpPPOscKZifVzSQ != 
getLayer()->getInputTensor(0)) { assert(IbSWJNMuIiKbocfQKqXb); 
CUDA_FREE_CALL(static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData()); 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->setData((float*)NULL); } } void 
MWAvgPoolingLayerImpl::predict() { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0); MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(0); cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensorBase->getSourcePortIndex()); assert(desc); if 
(opTensorBase->isInt8()) { assert(!IbSWJNMuIiKbocfQKqXb); 
MWTensor<signed char>* opTensor = static_cast<MWTensor<signed 
char>*>(opTensorBase); 
CUDNN_CALL(cudnnPoolingForward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
mtolGPkUMBYDlSSqrRzc, &pFoPPXxxFRbjXXxQWItv, 
JABfZsGuaCAmcRcqOYEO, static_cast<MWTensor<signed 
char>*>(TfsmDFpPPOscKZifVzSQ)->getData(), getZeroPtr(), *desc, opTensor->getData())); 
}else{ MWTensor<float>* ipTensor = static_cast<MWTensor<float>*>(ipTensorBase); 
MWTensor<float>* opTensor = static_cast<MWTensor<float>*>(opTensorBase); if 
(TfsmDFpPPOscKZifVzSQ != ipTensorBase) { 
CUDA_CALL(cudaMemset(static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), 
0, sizeof(float)*TfsmDFpPPOscKZifVzSQ->getNumElements())); 
MWCNNLayerImpl::padInput(ipTensor->getData(), ipTensor->getHeight(), 
ipTensor->getWidth(), ipTensor->getChannels(), TfsmDFpPPOscKZifVzSQ->getHeight(), 
TfsmDFpPPOscKZifVzSQ->getWidth(), CTCbzQMDaLxINPbODdng, CpMjJjtGOeWOzwxpAAQP, 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), 
ipTensor->getNumElements()); } assert(opTensor->getData() != 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData()); 
CUDNN_CALL(cudnnPoolingForward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
mtolGPkUMBYDlSSqrRzc, getOnePtr(), YCSvyQZBWMDYQXHtyVai, 
static_cast<MWTensor<float>*>(TfsmDFpPPOscKZifVzSQ)->getData(), getZeroPtr(), *desc, 
opTensor->getData())); } } void MWAvgPoolingLayerImpl::cleanup() { 
CUDNN_CALL(cudnnDestroyPoolingDescriptor(mtolGPkUMBYDlSSqrRzc)); if 
(TfsmDFpPPOscKZifVzSQ != getLayer()->getInputTensor(0)) { 
assert(IbSWJNMuIiKbocfQKqXb); 
CUDNN_CALL(cudnnDestroyTensorDescriptor(YCSvyQZBWMDYQXHtyVai)); } MWTensorBase* 
opTensorBase = getLayer()->getOutputTensor(0); if (opTensorBase->isInt8()) { 
CUDNN_CALL(cudnnDestroyTensorDescriptor(JABfZsGuaCAmcRcqOYEO)); }  }