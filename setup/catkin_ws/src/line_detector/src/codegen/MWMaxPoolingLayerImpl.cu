#include "MWMaxPoolingLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
 void __global__ MWSetDyForBackPropImpl(float * PfisSEEWDaQFynnzlcin, const int 
fOpFYwKNwIfWjnPzNuob); void __global__ doMWMaxPoolingLayerImpl(float * 
UpnEytIWGokwbTFkBcSx, float * UdmcwaUkepxfZrpdpcAN, const int 
BdqURaHPmdnfzvtUvocl); MWMaxPoolingLayerImpl::MWMaxPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int DSsxcjIrUgZCKZovyNQf,  int 
EvebzoroiuKkIxwjkGnD,  int FshVHIJMRAhtQirYPlZd,  int 
GDRXdUDklKFEYEfifhIH, int ClEhcJFlvGCgiavziIag, int 
CZNYmBcNFSZWvaCklqeM,  int CufLFODQDXTAPyRqYodN, int 
DCdZnqpcBnvXVgEsLBnz, bool GLovsOhUpzOJhKgXUAJY, int 
nlIRrOJaFuVaywxOqOyb, const char* ABtNoHVrQOgivJIJagNR,  int 
fSKMHAqIghbYYgyIpNDw) : MWCNNLayerImpl(layer, ntwk_impl) , 
BRSPqxNffoBYKqpSVHne(GLovsOhUpzOJhKgXUAJY) , UpnEytIWGokwbTFkBcSx(0) 
, PfisSEEWDaQFynnzlcin(0) , DRzwhbNPpftRRIXXfHzd(DSsxcjIrUgZCKZovyNQf) , 
EfvWctmlsWAPsxXgdKWf(EvebzoroiuKkIxwjkGnD) , 
DGzdAcREJHGXjyRzNjJV(DSsxcjIrUgZCKZovyNQf) , 
ECTnqgWHyHCHCLBZlffd(EvebzoroiuKkIxwjkGnD) , 
CTCbzQMDaLxINPbODdng(ClEhcJFlvGCgiavziIag) , 
CLOUhPjbgggWoXHTtmjC(CZNYmBcNFSZWvaCklqeM) , 
CpMjJjtGOeWOzwxpAAQP(CufLFODQDXTAPyRqYodN) , 
CqtPRJvHlGJFssiPzsOm(DCdZnqpcBnvXVgEsLBnz) , 
FrpxvsDMwwgbpqHXWxmN(FshVHIJMRAhtQirYPlZd) , 
FwLnexHgxHRquTKmNpoa(GDRXdUDklKFEYEfifhIH) , 
pFoPPXxxFRbjXXxQWItv(std::pow(2, 
nlIRrOJaFuVaywxOqOyb)) , 
vjDFlBZzKvbpPseAtMBP(std::string{"INT8x4"}.compare(ABtNoHVrQOgivJIJagNR) 
== 0) , fXhhiexIRPLyKXApPmmy(fSKMHAqIghbYYgyIpNDw) {  
CUDNN_CALL(cudnnCreatePoolingDescriptor(&mtolGPkUMBYDlSSqrRzc)); 
createAndAddDescriptor(getLayer()->getOutputTensor(0)->getSourcePortIndex()); 
CUDNN_CALL(cudnnCreateTensorDescriptor(&DqxLTLaJwwgQqmrtCDuu));  } 
MWMaxPoolingLayerImpl::~MWMaxPoolingLayerImpl() { } void 
MWMaxPoolingLayerImpl::propagateSize() {  MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(0); MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0); if ((DRzwhbNPpftRRIXXfHzd == -1) && 
(EfvWctmlsWAPsxXgdKWf == -1)) { DGzdAcREJHGXjyRzNjJV = 
ipTensorBase->getHeight(); ECTnqgWHyHCHCLBZlffd = ipTensorBase->getWidth(); } int 
muwRQxtWMMXAPxSuMYBw = CTCbzQMDaLxINPbODdng; int 
nDsbARncmIrIaLubvLVZ = CpMjJjtGOeWOzwxpAAQP; 
CUDNN_CALL(cudnnSetPooling2dDescriptor(mtolGPkUMBYDlSSqrRzc, CUDNN_POOLING_MAX, 
CUDNN_NOT_PROPAGATE_NAN, DGzdAcREJHGXjyRzNjJV, ECTnqgWHyHCHCLBZlffd, 
muwRQxtWMMXAPxSuMYBw, nDsbARncmIrIaLubvLVZ, FrpxvsDMwwgbpqHXWxmN, 
FwLnexHgxHRquTKmNpoa)); cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensorBase->getSourcePortIndex()); assert(desc); if 
(ipTensorBase->isInt8()) { if (vjDFlBZzKvbpPseAtMBP) { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(DqxLTLaJwwgQqmrtCDuu, 
CUDNN_TENSOR_NCHW_VECT_C,  CUDNN_DATA_INT8x4,  ipTensorBase->getBatchSize(),  
ipTensorBase->getChannels(),  ipTensorBase->getHeight(),  
ipTensorBase->getWidth())  ); MWCNNLayerImpl::setDescriptorForINT8(*desc, 
static_cast<MWTensor<signed char>*>(opTensorBase), CUDNN_DATA_INT8x4, 
CUDNN_TENSOR_NCHW_VECT_C);  } else { 
CUDNN_CALL(cudnnSetTensor4dDescriptor(DqxLTLaJwwgQqmrtCDuu, 
CUDNN_TENSOR_NCHW, CUDNN_DATA_INT8, ipTensorBase->getBatchSize(), 
ipTensorBase->getChannels(), ipTensorBase->getHeight(), 
ipTensorBase->getWidth())); MWCNNLayerImpl::setDescriptorForINT8(*desc, 
static_cast<MWTensor<signed char>*>(opTensorBase), CUDNN_DATA_INT8, 
CUDNN_TENSOR_NCHW); } } else { setDescriptor<float>(*desc, 
static_cast<MWTensor<float>*>(opTensorBase)); } } void 
MWMaxPoolingLayerImpl::allocate() { MWCNNLayer* maxpoolLayer = getLayer(); 
MWTensorBase* ipTensor = maxpoolLayer->getInputTensor(0); MWTensorBase* 
opTensor = maxpoolLayer->getOutputTensor(0); if (BRSPqxNffoBYKqpSVHne){ const 
int edQOkUJIZbwzEeIcCLzG = ipTensor->getNumElements(); 
CUDA_CALL(cudaMalloc((void**)&UpnEytIWGokwbTFkBcSx, 
sizeof(float)*edQOkUJIZbwzEeIcCLzG)); const int fOpFYwKNwIfWjnPzNuob = 
opTensor->getNumElements(); CUDA_CALL(cudaMalloc((void**)&PfisSEEWDaQFynnzlcin, 
sizeof(float)*fOpFYwKNwIfWjnPzNuob)); int tGsvtyAVkrDznETdweDC = 
(fOpFYwKNwIfWjnPzNuob < 1024) ? fOpFYwKNwIfWjnPzNuob : 1024; int 
KZWeXiYFmdpQdsgidKeG = (fOpFYwKNwIfWjnPzNuob + tGsvtyAVkrDznETdweDC - 
1)/tGsvtyAVkrDznETdweDC; 
MWSetDyForBackPropImpl<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( PfisSEEWDaQFynnzlcin, fOpFYwKNwIfWjnPzNuob); } } void 
MWMaxPoolingLayerImpl::deallocate() { if (UpnEytIWGokwbTFkBcSx){ 
CUDA_FREE_CALL(UpnEytIWGokwbTFkBcSx); UpnEytIWGokwbTFkBcSx = 
NULL; } if (PfisSEEWDaQFynnzlcin){ CUDA_FREE_CALL(PfisSEEWDaQFynnzlcin); PfisSEEWDaQFynnzlcin = 
NULL; }  } void MWMaxPoolingLayerImpl::predict() { MWCNNLayer* maxpoolLayer = 
getLayer(); MWTensorBase* ipTensorBase = maxpoolLayer->getInputTensor(0); 
MWTensorBase* opTensorBase = maxpoolLayer->getOutputTensor(0); 
cudnnTensorDescriptor_t* desc = 
getDescriptor(opTensorBase->getSourcePortIndex()); assert(desc); 
cudnnTensorDescriptor_t YCSvyQZBWMDYQXHtyVai; if (opTensorBase->isInt8()) { 
YCSvyQZBWMDYQXHtyVai = DqxLTLaJwwgQqmrtCDuu; MWTensor<signed char>* ipTensor = 
static_cast<MWTensor<signed char>*>(ipTensorBase); MWTensor<signed char>* 
opTensor = static_cast<MWTensor<signed char>*>(opTensorBase); 
CUDNN_CALL(cudnnPoolingForward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
mtolGPkUMBYDlSSqrRzc, &pFoPPXxxFRbjXXxQWItv, YCSvyQZBWMDYQXHtyVai, 
ipTensor->getData(), getZeroPtr(), *desc, opTensor->getData())); } else { 
YCSvyQZBWMDYQXHtyVai = MWCNNLayerImpl::getCuDNNDescriptor(ipTensorBase); 
MWTensor<float>* ipTensor = static_cast<MWTensor<float>*>(ipTensorBase); 
MWTensor<float>* opTensor = static_cast<MWTensor<float>*>(opTensorBase); 
CUDNN_CALL(cudnnPoolingForward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
mtolGPkUMBYDlSSqrRzc, getOnePtr(), YCSvyQZBWMDYQXHtyVai, ipTensor->getData(), 
getZeroPtr(), *desc, opTensor->getData())); if (BRSPqxNffoBYKqpSVHne) { 
CUDNN_CALL(cudnnPoolingBackward(*dMxIKDGTITyhdLqIHBLA->getCudnnHandle(), 
mtolGPkUMBYDlSSqrRzc, getOnePtr(), *desc, opTensor->getData(), *desc, 
PfisSEEWDaQFynnzlcin, YCSvyQZBWMDYQXHtyVai, ipTensor->getData(), getZeroPtr(), 
YCSvyQZBWMDYQXHtyVai, UpnEytIWGokwbTFkBcSx)); int edQOkUJIZbwzEeIcCLzG = 
ipTensor->getNumElements(); int tGsvtyAVkrDznETdweDC = 
(edQOkUJIZbwzEeIcCLzG < 1024) ? edQOkUJIZbwzEeIcCLzG : 1024; int 
KZWeXiYFmdpQdsgidKeG = (edQOkUJIZbwzEeIcCLzG + tGsvtyAVkrDznETdweDC - 
1)/tGsvtyAVkrDznETdweDC; 
doMWMaxPoolingLayerImpl<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( UpnEytIWGokwbTFkBcSx, 
static_cast<MWTensor<float>*>(maxpoolLayer->getOutputTensor(1))->getData(), 
edQOkUJIZbwzEeIcCLzG); }  } return; } void MWMaxPoolingLayerImpl::cleanup() { 
CUDNN_CALL(cudnnDestroyPoolingDescriptor(mtolGPkUMBYDlSSqrRzc)); MWTensorBase* 
opTensorBase = getLayer()->getOutputTensor(0);  if (opTensorBase->isInt8()) { 
CUDNN_CALL(cudnnDestroyTensorDescriptor(DqxLTLaJwwgQqmrtCDuu)); } } float* 
MWMaxPoolingLayerImpl::getIndexData()  { return 
static_cast<MWTensor<float>*>(getLayer()->getOutputTensor(1))->getData(); } 
void __global__ __launch_bounds__(1024) MWSetDyForBackPropImpl(float * 
PfisSEEWDaQFynnzlcin, const int fOpFYwKNwIfWjnPzNuob) { for(int i = blockDim.x * 
blockIdx.x + threadIdx.x; i < fOpFYwKNwIfWjnPzNuob; i+= blockDim.x*gridDim.x) { 
PfisSEEWDaQFynnzlcin[i] = i+1; } } void __global__ __launch_bounds__(1024) 
doMWMaxPoolingLayerImpl(float * UpnEytIWGokwbTFkBcSx, float * 
UdmcwaUkepxfZrpdpcAN, const int BdqURaHPmdnfzvtUvocl) { for(int i = blockDim.x * 
blockIdx.x + threadIdx.x; i < BdqURaHPmdnfzvtUvocl; i+= blockDim.x*gridDim.x) { if 
(static_cast<int>(UpnEytIWGokwbTFkBcSx[i]) != 0){ 
UdmcwaUkepxfZrpdpcAN[static_cast<int>(UpnEytIWGokwbTFkBcSx[i])-1] = 
i; } } }