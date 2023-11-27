#include "MWElementwiseAffineLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWKernelHeaders.hpp"
#include <math.h>
#include <cassert>
#include <cstdio>
 MWElementwiseAffineLayerImpl::MWElementwiseAffineLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int scale_H, int scale_W, int scale_C, int 
offset_H, int offset_W, int offset_C, bool isClipped, int lowerbound, int 
upperbound, const char* qWwjVYwfnvEnFKlgpqwA, const char* 
iADjqLChtuDbEWfMYFLp) : MWCNNLayerImpl(layer, ntwk_impl), 
pvpNsgGssdTxeVoFIkXI(NULL), gNROjwaqhxDPvBWUCUcQ(NULL), pzUAoBDvaKAtdsmkQuct(scale_H), 
qEXwbWWsnOADJeTXfRVa(scale_W), pxmnUEWGnfCxJNuDkXAo(scale_C), 
hljcfGWsvZXJZNrImpJB(offset_H), hvqKUzPqCuUJRfoNlbwW(offset_W), 
hKyfKjPACkOBDvLdESxH(offset_C), ZinudJuZuGitiNTsJpBR(isClipped), 
bUVPfnrJhLfHzOLUUrKk(lowerbound), veFyKKHbdqBIvQLYBqfF(upperbound) { 
CUDA_CALL(cudaMalloc((void**)&pvpNsgGssdTxeVoFIkXI, 
sizeof(float)*pzUAoBDvaKAtdsmkQuct*qEXwbWWsnOADJeTXfRVa*pxmnUEWGnfCxJNuDkXAo)); 
CUDA_CALL(cudaMalloc((void**)&gNROjwaqhxDPvBWUCUcQ, 
sizeof(float)*hljcfGWsvZXJZNrImpJB*hvqKUzPqCuUJRfoNlbwW*hKyfKjPACkOBDvLdESxH));  
loadScale(qWwjVYwfnvEnFKlgpqwA); loadOffset(iADjqLChtuDbEWfMYFLp); } 
MWElementwiseAffineLayerImpl::~MWElementwiseAffineLayerImpl() { } void 
MWElementwiseAffineLayerImpl::propagateSize() { } void 
MWElementwiseAffineLayerImpl::predict() { MWTensorBase* ipTensorBase = 
getLayer()->getInputTensor(0); MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0); MWTensor<float>* ipTensor = 
static_cast<MWTensor<float>*>(ipTensorBase); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); int WprSrhAStKGxyXeoxETy = 
ipTensor->getHeight(); int XCLDbxHBtWRStETWIkId = ipTensor->getWidth(); int 
WmXADZOqdcQvtBUvFerh = ipTensor->getChannels(); long int 
YeIFysyIXePEVfpcANol = WprSrhAStKGxyXeoxETy*XCLDbxHBtWRStETWIkId; long 
int YOWMnLKOMqAODXiVNoGy = 
YeIFysyIXePEVfpcANol*WmXADZOqdcQvtBUvFerh; long int 
YNmJhGSUszJKxsodxiuV = ipTensor->getNumElements(); long int sFIUeCwGDlfadqOrGZHC = 
((YNmJhGSUszJKxsodxiuV + 31) / 32) * 32; int tGsvtyAVkrDznETdweDC = 
(sFIUeCwGDlfadqOrGZHC < 1024) ? sFIUeCwGDlfadqOrGZHC : 1024; long int 
KZWeXiYFmdpQdsgidKeG = (YNmJhGSUszJKxsodxiuV + tGsvtyAVkrDznETdweDC - 
1) / tGsvtyAVkrDznETdweDC; long int qBTcAwVGZERyCjGYByPe = 
pzUAoBDvaKAtdsmkQuct * qEXwbWWsnOADJeTXfRVa * pxmnUEWGnfCxJNuDkXAo; long int 
hnewnpwgzKmOdualajhn = hljcfGWsvZXJZNrImpJB * hvqKUzPqCuUJRfoNlbwW * 
hKyfKjPACkOBDvLdESxH; assert(qBTcAwVGZERyCjGYByPe <= YNmJhGSUszJKxsodxiuV); 
assert(hnewnpwgzKmOdualajhn <= YNmJhGSUszJKxsodxiuV); if (qBTcAwVGZERyCjGYByPe == 
1) { scale_scalar_kernel<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( ipTensor->getData(),  opTensor->getData(), 
pvpNsgGssdTxeVoFIkXI, YNmJhGSUszJKxsodxiuV); } else if (pzUAoBDvaKAtdsmkQuct == 1 && 
qEXwbWWsnOADJeTXfRVa == 1 && qBTcAwVGZERyCjGYByPe > 1) { 
scale_vector_kernel<<<KZWeXiYFmdpQdsgidKeG, tGsvtyAVkrDznETdweDC>>>( 
ipTensor->getData(),  opTensor->getData(), pvpNsgGssdTxeVoFIkXI, 
YeIFysyIXePEVfpcANol, YOWMnLKOMqAODXiVNoGy, 
YNmJhGSUszJKxsodxiuV); } else if (YOWMnLKOMqAODXiVNoGy == 
qBTcAwVGZERyCjGYByPe) {  scale_tensor3d_kernel<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( ipTensor->getData(),  opTensor->getData(), 
pvpNsgGssdTxeVoFIkXI,  YOWMnLKOMqAODXiVNoGy, YNmJhGSUszJKxsodxiuV); } else 
{ scale_matrix2d_kernel<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( ipTensor->getData(),  opTensor->getData(), 
pvpNsgGssdTxeVoFIkXI,  YeIFysyIXePEVfpcANol, YNmJhGSUszJKxsodxiuV); } if 
(hnewnpwgzKmOdualajhn == 1) { offset_scalar_kernel<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( opTensor->getData(),  opTensor->getData(), 
gNROjwaqhxDPvBWUCUcQ, YNmJhGSUszJKxsodxiuV, ZinudJuZuGitiNTsJpBR, 
bUVPfnrJhLfHzOLUUrKk, veFyKKHbdqBIvQLYBqfF); } else if (hljcfGWsvZXJZNrImpJB 
== 1 && hvqKUzPqCuUJRfoNlbwW == 1 && hnewnpwgzKmOdualajhn > 1) { 
offset_vector_kernel<<<KZWeXiYFmdpQdsgidKeG, tGsvtyAVkrDznETdweDC>>>( 
opTensor->getData(),  opTensor->getData(), gNROjwaqhxDPvBWUCUcQ, 
YeIFysyIXePEVfpcANol, YOWMnLKOMqAODXiVNoGy, 
YNmJhGSUszJKxsodxiuV, ZinudJuZuGitiNTsJpBR, bUVPfnrJhLfHzOLUUrKk, 
veFyKKHbdqBIvQLYBqfF); } else if (YOWMnLKOMqAODXiVNoGy == 
hnewnpwgzKmOdualajhn) { offset_tensor3d_kernel<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( opTensor->getData(),  opTensor->getData(), 
gNROjwaqhxDPvBWUCUcQ, YOWMnLKOMqAODXiVNoGy, YNmJhGSUszJKxsodxiuV, 
ZinudJuZuGitiNTsJpBR, bUVPfnrJhLfHzOLUUrKk, veFyKKHbdqBIvQLYBqfF); } else { 
offset_matrix2d_kernel<<<KZWeXiYFmdpQdsgidKeG, 
tGsvtyAVkrDznETdweDC>>>( opTensor->getData(),  opTensor->getData(), 
gNROjwaqhxDPvBWUCUcQ, YeIFysyIXePEVfpcANol, YNmJhGSUszJKxsodxiuV, 
ZinudJuZuGitiNTsJpBR, bUVPfnrJhLfHzOLUUrKk, veFyKKHbdqBIvQLYBqfF); } return; 
} void MWElementwiseAffineLayerImpl::cleanup() { if (pvpNsgGssdTxeVoFIkXI) { 
CUDA_FREE_CALL(pvpNsgGssdTxeVoFIkXI); pvpNsgGssdTxeVoFIkXI = NULL; } if 
(gNROjwaqhxDPvBWUCUcQ) { CUDA_FREE_CALL(gNROjwaqhxDPvBWUCUcQ); gNROjwaqhxDPvBWUCUcQ = 
NULL; }  } void MWElementwiseAffineLayerImpl::loadScale(const char* 
qWwjVYwfnvEnFKlgpqwA) { FILE* QwUuNuQNtlPXrIwRNiSZ = 
MWCNNLayer::openBinaryFile(qWwjVYwfnvEnFKlgpqwA); assert(QwUuNuQNtlPXrIwRNiSZ); long 
int dkLDkRwCBjeybwDHbKiE = pzUAoBDvaKAtdsmkQuct*qEXwbWWsnOADJeTXfRVa*pxmnUEWGnfCxJNuDkXAo; 
float* LgxABSJPBXdCozJkFqTg = MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, qWwjVYwfnvEnFKlgpqwA); CUDA_CALL(cudaMemcpy(pvpNsgGssdTxeVoFIkXI, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice)); 
free(LgxABSJPBXdCozJkFqTg); fclose(QwUuNuQNtlPXrIwRNiSZ);  } void 
MWElementwiseAffineLayerImpl::loadOffset(const char* iADjqLChtuDbEWfMYFLp) { 
FILE* QwUuNuQNtlPXrIwRNiSZ = MWCNNLayer::openBinaryFile(iADjqLChtuDbEWfMYFLp); 
assert(QwUuNuQNtlPXrIwRNiSZ); long int dkLDkRwCBjeybwDHbKiE = 
hljcfGWsvZXJZNrImpJB*hvqKUzPqCuUJRfoNlbwW*hKyfKjPACkOBDvLdESxH; float* 
LgxABSJPBXdCozJkFqTg = MALLOC_CALL(sizeof(float)*dkLDkRwCBjeybwDHbKiE); 
MWCNNLayer::call_fread(LgxABSJPBXdCozJkFqTg, sizeof(float), dkLDkRwCBjeybwDHbKiE, 
QwUuNuQNtlPXrIwRNiSZ, iADjqLChtuDbEWfMYFLp); CUDA_CALL(cudaMemcpy(gNROjwaqhxDPvBWUCUcQ, 
LgxABSJPBXdCozJkFqTg, sizeof(float)*dkLDkRwCBjeybwDHbKiE, cudaMemcpyHostToDevice)); 
free(LgxABSJPBXdCozJkFqTg); fclose(QwUuNuQNtlPXrIwRNiSZ);  }