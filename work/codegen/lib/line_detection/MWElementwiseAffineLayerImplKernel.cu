#include "MWKernelHeaders.hpp"
#include <math.h>
#include <stdio.h>
 void __global__ __launch_bounds__(1024) scale_scalar_kernel(float* 
inputBuffer, float* outputBuffer, float* pvpNsgGssdTxeVoFIkXI, long int 
YNmJhGSUszJKxsodxiuV) {  for (long int idx = blockDim.x * blockIdx.x + 
threadIdx.x; idx < YNmJhGSUszJKxsodxiuV; idx += blockDim.x * gridDim.x) {  
outputBuffer[idx] = pvpNsgGssdTxeVoFIkXI[0]*inputBuffer[idx]; } } void __global__ 
__launch_bounds__(1024) scale_vector_kernel(float* inputBuffer, float* 
outputBuffer, float* pvpNsgGssdTxeVoFIkXI, double YeIFysyIXePEVfpcANol, 
double YOWMnLKOMqAODXiVNoGy, long int YNmJhGSUszJKxsodxiuV) {  for 
(long int idx = blockDim.x * blockIdx.x + threadIdx.x; idx < 
YNmJhGSUszJKxsodxiuV; idx += blockDim.x * gridDim.x) { double batchIdx = 
floor(idx / YOWMnLKOMqAODXiVNoGy); double i_batch = idx - (batchIdx * 
YOWMnLKOMqAODXiVNoGy); double channelIdx = floor(i_batch / 
YeIFysyIXePEVfpcANol); outputBuffer[idx] = 
pvpNsgGssdTxeVoFIkXI[static_cast<long int>(channelIdx)]*inputBuffer[idx]; } } void 
__global__ __launch_bounds__(1024) scale_matrix2d_kernel(float* inputBuffer, 
float* outputBuffer, float* pvpNsgGssdTxeVoFIkXI, double 
YeIFysyIXePEVfpcANol, long int YNmJhGSUszJKxsodxiuV) {  for (long int 
idx = blockDim.x * blockIdx.x + threadIdx.x; idx < YNmJhGSUszJKxsodxiuV; idx += 
blockDim.x * gridDim.x) { double totalChannelIdx = floor(idx / 
YeIFysyIXePEVfpcANol); double i_channel = idx - (totalChannelIdx * 
YeIFysyIXePEVfpcANol); outputBuffer[idx] = 
pvpNsgGssdTxeVoFIkXI[static_cast<long int>(i_channel)]*inputBuffer[idx]; } } void 
__global__ __launch_bounds__(1024) scale_tensor3d_kernel(float* inputBuffer, 
float* outputBuffer, float* pvpNsgGssdTxeVoFIkXI, double 
YOWMnLKOMqAODXiVNoGy, long int YNmJhGSUszJKxsodxiuV) {  for (long int 
idx = blockDim.x * blockIdx.x + threadIdx.x; idx < YNmJhGSUszJKxsodxiuV; idx += 
blockDim.x * gridDim.x) { double batchIdx = floor(idx / 
YOWMnLKOMqAODXiVNoGy); double i_batch = idx - (batchIdx * 
YOWMnLKOMqAODXiVNoGy); outputBuffer[idx] = 
pvpNsgGssdTxeVoFIkXI[static_cast<long int>(i_batch)]*inputBuffer[idx]; } }  void 
__global__ __launch_bounds__(1024) offset_scalar_kernel(float* inputBuffer, 
float* outputBuffer, float* gNROjwaqhxDPvBWUCUcQ, long int YNmJhGSUszJKxsodxiuV, 
bool ZinudJuZuGitiNTsJpBR, int bUVPfnrJhLfHzOLUUrKk, int 
veFyKKHbdqBIvQLYBqfF) {  for (long int idx = blockDim.x * blockIdx.x + 
threadIdx.x; idx < YNmJhGSUszJKxsodxiuV; idx += blockDim.x * gridDim.x) { float 
out = inputBuffer[idx] + gNROjwaqhxDPvBWUCUcQ[0]; if (ZinudJuZuGitiNTsJpBR){ out = 
out > veFyKKHbdqBIvQLYBqfF ? veFyKKHbdqBIvQLYBqfF : out; out = out < 
bUVPfnrJhLfHzOLUUrKk ? bUVPfnrJhLfHzOLUUrKk : out; } outputBuffer[idx] = out; 
} } void __global__ __launch_bounds__(1024) offset_vector_kernel(float* 
inputBuffer, float* outputBuffer, float* gNROjwaqhxDPvBWUCUcQ,  double 
YeIFysyIXePEVfpcANol, double YOWMnLKOMqAODXiVNoGy, long int 
YNmJhGSUszJKxsodxiuV, bool ZinudJuZuGitiNTsJpBR, int bUVPfnrJhLfHzOLUUrKk, int 
veFyKKHbdqBIvQLYBqfF) {  for (long int idx = blockDim.x * blockIdx.x + 
threadIdx.x; idx < YNmJhGSUszJKxsodxiuV; idx += blockDim.x * gridDim.x) { 
double batchIdx = floor(idx / YOWMnLKOMqAODXiVNoGy); double i_batch = 
idx - (batchIdx * YOWMnLKOMqAODXiVNoGy); double channelIdx = 
floor(i_batch / YeIFysyIXePEVfpcANol); float out = inputBuffer[idx] + 
gNROjwaqhxDPvBWUCUcQ[static_cast<long int>(channelIdx)]; if 
(ZinudJuZuGitiNTsJpBR){ out = out > veFyKKHbdqBIvQLYBqfF ? 
veFyKKHbdqBIvQLYBqfF : out; out = out < bUVPfnrJhLfHzOLUUrKk ? 
bUVPfnrJhLfHzOLUUrKk : out; } outputBuffer[idx] = out; } } void __global__ 
__launch_bounds__(1024) offset_matrix2d_kernel(float* inputBuffer, float* 
outputBuffer, float* gNROjwaqhxDPvBWUCUcQ, double YeIFysyIXePEVfpcANol, 
long int YNmJhGSUszJKxsodxiuV, bool ZinudJuZuGitiNTsJpBR, int 
bUVPfnrJhLfHzOLUUrKk, int veFyKKHbdqBIvQLYBqfF) {  for (long int idx = 
blockDim.x * blockIdx.x + threadIdx.x; idx < YNmJhGSUszJKxsodxiuV; idx += 
blockDim.x * gridDim.x) { double totalChannelIdx = floor(idx / 
YeIFysyIXePEVfpcANol); double i_channel = idx - (totalChannelIdx * 
YeIFysyIXePEVfpcANol); float out = inputBuffer[idx] + 
gNROjwaqhxDPvBWUCUcQ[static_cast<long int>(i_channel)]; if (ZinudJuZuGitiNTsJpBR){ 
out = out > veFyKKHbdqBIvQLYBqfF ? veFyKKHbdqBIvQLYBqfF : out; out = out < 
bUVPfnrJhLfHzOLUUrKk ? bUVPfnrJhLfHzOLUUrKk : out; } outputBuffer[idx] = out; 
} } void __global__ __launch_bounds__(1024) offset_tensor3d_kernel(float* 
inputBuffer, float* outputBuffer, float* gNROjwaqhxDPvBWUCUcQ, double 
YOWMnLKOMqAODXiVNoGy, long int YNmJhGSUszJKxsodxiuV, bool 
ZinudJuZuGitiNTsJpBR, int bUVPfnrJhLfHzOLUUrKk, int veFyKKHbdqBIvQLYBqfF) {  
for (long int idx = blockDim.x * blockIdx.x + threadIdx.x; idx < 
YNmJhGSUszJKxsodxiuV; idx += blockDim.x * gridDim.x) { double batchIdx = 
floor(idx / YOWMnLKOMqAODXiVNoGy); double i_batch = idx - (batchIdx * 
YOWMnLKOMqAODXiVNoGy); float out = inputBuffer[idx] + 
gNROjwaqhxDPvBWUCUcQ[static_cast<long int>(i_batch)]; if (ZinudJuZuGitiNTsJpBR){ 
out = out > veFyKKHbdqBIvQLYBqfF ? veFyKKHbdqBIvQLYBqfF : out; out = out < 
bUVPfnrJhLfHzOLUUrKk ? bUVPfnrJhLfHzOLUUrKk : out; } outputBuffer[idx] = out; 
} } 