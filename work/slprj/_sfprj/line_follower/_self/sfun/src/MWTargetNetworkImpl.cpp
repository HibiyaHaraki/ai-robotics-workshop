#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWOutputLayer.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWOutputLayerImpl.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include "MWCustomLayerForMKLDNN.hpp"
#include <cstring>
#include <vector>
#include <map>
#include <memory>
 void MWTargetNetworkImpl::allocate(int numBufsToAlloc, MWCNNLayer* layers[], 
int numLayers, int numPermuteBufs) { numBufs = numBufsToAlloc; int 
maxCustomLayerBufSize = -1; for (int i = 0; i < numLayers; i++) { if 
(layers[i]->isCustomLayer()) { int layerBufSize = 
dynamic_cast<MWCustomLayerForMKLDNN*>(layers[i])->getMaxBufSize(); 
maxCustomLayerBufSize = (maxCustomLayerBufSize < layerBufSize) ? layerBufSize : 
maxCustomLayerBufSize; } } if (maxCustomLayerBufSize > 0 && numPermuteBufs > 0) 
{ for (int i = 0; i < numBufs; i++) { olKGEIcsxmLSoMhRhEtP.push_back(new 
float[maxCustomLayerBufSize]); } } int maxBufSize = maxCustomLayerBufSize; for 
(int i = 0; i < numLayers; i++) { if ((layers[i]->getImpl() != NULL) && 
(dynamic_cast<MWOutputLayer*>(layers[i]) == NULL)) { int layerBufSize = 
(int)(layers[i]->getImpl()->getLayerMemory()->get_desc().get_size() / 
sizeof(float)); maxBufSize = (maxBufSize < layerBufSize) ? layerBufSize : 
maxBufSize; } } for (int i = 0; i < numBufs; i++) { memBuffer.push_back(new 
float[maxBufSize]); } } void 
MWTargetNetworkImpl::setReorderPrim(std::shared_ptr<dnnl::reorder> other) { 
reorderPrim = other; } void 
MWTargetNetworkImpl::setReorderLayerMemory(std::shared_ptr<dnnl::memory> other) 
{ reorderLayerMemory = other; } void MWTargetNetworkImpl::preSetup() { eng = 
std::unique_ptr<dnnl::engine>(new dnnl::engine(dnnl::engine::kind::cpu, 0)); 
Cpu cpu; isAVX512 = cpu.has(Cpu::tAVX512F); } float* 
MWTargetNetworkImpl::getLayerOutput(MWCNNLayer* layers[], int layerIndex, int 
portIndex) { MWTensorBase* opTensor = 
layers[layerIndex]->getOutputTensor(portIndex); float* opData = 
getLayerActivation(opTensor); return opData; } std::shared_ptr<dnnl::memory> 
MWTargetNetworkImpl::getReorderLayerMemory() { return reorderLayerMemory; } 
std::shared_ptr<dnnl::reorder> MWTargetNetworkImpl::getReorderPrim() { return 
reorderPrim; } float* MWTargetNetworkImpl::getLayerActivation(MWTensorBase* 
opTensorBase) { MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); MWCNNLayer* layer = 
opTensor->getOwner(); MWCNNLayerImpl* layerImpl = layer->getImpl(); if 
(layerImpl == NULL && !layer->isCustomLayer()) { return 
getLayerActivation(opTensor->getOwner()->getInputTensor()); } else { if 
(dynamic_cast<MWOutputLayerImpl*>(layerImpl)) { return opTensor->getData(); } 
else { std::shared_ptr<dnnl::memory> currentLayerMemory = 
MWMkldnnUtils::getLayerMemoryPrimitive(opTensor); auto currentLayerMemoryDesc = 
currentLayerMemory->get_desc(); format_type formatTag = 
MWMkldnnUtils::getformatType(currentLayerMemoryDesc, opTensor); if 
(MWMkldnnUtils::isReorderNeeded(formatTag) || (formatTag == 
format_type::NCHW8C_FORMAT)) { MWMkldnnUtils::TargetImplconfigureReorder(this, 
opTensor, dnnl::memory::format_tag::nchw); std::vector<dnnl::primitive> 
activationsPipeline; std::vector<std::unordered_map<int, dnnl::memory>> 
activationsPipeline_memory_args; 
activationsPipeline.push_back(*this->getReorderPrim()); auto s = 
dnnl::stream(*eng); activationsPipeline_memory_args.push_back( {{DNNL_ARG_FROM, 
*MWMkldnnUtils::getLayerMemoryPrimitive(opTensor)}, {DNNL_ARG_TO, 
*this->getReorderLayerMemory()}}); assert(activationsPipeline.size() == 
activationsPipeline_memory_args.size()); for (int i = 0; i < 
activationsPipeline.size(); i++) { activationsPipeline[i].execute(s, 
activationsPipeline_memory_args[i]); } float* activationsOutput = 
static_cast<float*>(this->getReorderLayerMemory()->get_data_handle()); return 
activationsOutput; } return opTensor->getData(); } } } void 
MWTargetNetworkImpl::deallocate() { for (int i = 0; i < memBuffer.size(); i++) 
{ if (memBuffer[i] != nullptr) { delete[] memBuffer[i]; } } memBuffer.clear(); 
for (int i = 0; i < olKGEIcsxmLSoMhRhEtP.size(); i++) { if 
(olKGEIcsxmLSoMhRhEtP[i] != nullptr) { delete[] 
olKGEIcsxmLSoMhRhEtP[i]; } } olKGEIcsxmLSoMhRhEtP.clear(); } void 
MWTargetNetworkImpl::cleanup() { } float* MWTargetNetworkImpl::getBufferPtr(int 
bufferIndex) { assert(bufferIndex < numBufs); return memBuffer[bufferIndex]; } 
float* MWTargetNetworkImpl::getPermuteBuffer(int bufferIndex) { 
assert(bufferIndex < olKGEIcsxmLSoMhRhEtP.size()); return 
olKGEIcsxmLSoMhRhEtP[bufferIndex]; }