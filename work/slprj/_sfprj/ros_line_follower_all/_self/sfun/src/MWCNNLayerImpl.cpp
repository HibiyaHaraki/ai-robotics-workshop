#include "MWCNNLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include <memory>
#include <cassert>
#include <cstring>
#include <cstdio>
 MWCNNLayerImpl::MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : cCXqPFPPcoHzYMDpnUxQ(layer) , euppfEoiaoCTcVgRPVhA(ntwk_impl) { } 
std::shared_ptr<dnnl::memory> MWCNNLayerImpl::getLayerMemory(int index) { if 
(layerMemory.size() >= 1) { std::map<int, 
std::shared_ptr<dnnl::memory>>::iterator it = layerMemory.find(index); return 
it->second; } else { return nullptr; } } std::shared_ptr<dnnl::memory> 
MWCNNLayerImpl::getReorderedIpMemory(int index) { if (reorderLayerMemory.size() 
>= 1) { std::map<int, std::shared_ptr<dnnl::memory>>::iterator it = 
reorderLayerMemory.find(index); return it->second; } else { return nullptr; } } 
std::shared_ptr<dnnl::reorder> MWCNNLayerImpl::getReorderPrim(int index) { if 
(reorderPrim.size() >= 1) { std::map<int, 
std::shared_ptr<dnnl::reorder>>::iterator it = reorderPrim.find(index); return 
it->second; } else { return nullptr; } } void 
MWCNNLayerImpl::setLayerMemory(std::shared_ptr<dnnl::memory> other, int index) 
{ layerMemory[index] = other; } void 
MWCNNLayerImpl::setReorderPrim(std::shared_ptr<dnnl::reorder> other, int index) 
{ reorderPrim[index] = other; } void 
MWCNNLayerImpl::setReorderLayerMemory(std::shared_ptr<dnnl::memory> other, int 
index) { reorderLayerMemory[index] = other; } template <class T> void 
MWCNNLayerImpl::allocateOutputData(int outIdx) { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(outIdx); MWTensor<T>* opTensor = 
static_cast<MWTensor<T>*>(opTensorBase); int outBufIndex = 
opTensor->getopBufIndex(); bool bufferReuse = outBufIndex >= 0; int inIdx = 
getLayer()->getInPlaceIndex(outIdx); bool inPlace = inIdx != -1; 
if(!bufferReuse){  if(inPlace){  
opTensor->setData((T*)getReorderedIpMemory(inIdx)->get_data_handle()); } else{  
int fSbUUBgjKRbNXrHrlOLo = 
static_cast<int>(this->getLayerMemory()->get_desc().get_size() / sizeof(T)); 
opTensor->setData((T*)calloc(fSbUUBgjKRbNXrHrlOLo, sizeof(T))); } } else{  
assert(opTensorBase->isFloat()); assert(!inPlace); 
static_cast<MWTensor<float>*>(opTensorBase) 
->setData(euppfEoiaoCTcVgRPVhA->memBuffer[outBufIndex]); } 
MWMkldnnUtils::getLayerMemoryPrimitive(opTensor)->set_data_handle(opTensor->getData()); 
} template void MWCNNLayerImpl::allocateOutputData<float>(int); template void 
MWCNNLayerImpl::allocateOutputData<signed char>(int); template <class T> void 
MWCNNLayerImpl::deallocateOutputData(int outIdx) { MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(outIdx); MWTensor<T>* opTensor = 
static_cast<MWTensor<T>*>(opTensorBase); bool doBufReleaseFlag = 
opTensor->getopBufIndex() < 0 && getLayer()->getInPlaceIndex(outIdx) == -1; T* 
opDataBuf = opTensor->getData(); if (opDataBuf) { if (doBufReleaseFlag) { 
free(opDataBuf); } opTensor->setData((T*)NULL); } return; } template void 
MWCNNLayerImpl::deallocateOutputData<float>(int); template void 
MWCNNLayerImpl::deallocateOutputData<signed char>(int); void 
MWCNNLayerImpl::clearLayerMapsAndVectors() { reorderLayerMemory.clear(); 
reorderPrim.clear(); pipeline.clear(); pipeline_memory_args.clear(); 
pipeline_weights_memory_args.clear(); pipeline_weights.clear(); }
#if MW_LAYERS_TAP
 int tap_count = 0; void mw_interm_tap(float* inp, int size, int count) { FILE* 
fp; int i; std::string fileName{"taps/mw_interm_tap_"};
#define TXT_FILE 1
#if TXT_FILE
 fileName = fileName + std::to_string(count) + ".txt"; fp = 
fopen(fileName.c_str(), "w"); if (fp == NULL) { std::string errmsg = 
std::string("Error opening text file .Create taps folder to open") + fileName; 
printf("Error! Unable to open file %s\n", fileName); throw 
std::runtime_error(errmsg.c_str()); } for (i = 0; i < size; i++) { fprintf(fp, 
"%f\n", inp[i]); }
#else
 fileName = fileName + std::to_string(count) + ".bin"; fp = 
fopen(fileName.c_str(), "wb"); if (fp == NULL) { std::string errmsg = 
std::string("Error opening binary file .Create taps folder to open") + 
fileName; printf("Error! Unable to open file %s\n", fileName); throw 
std::runtime_error(errmsg.c_str()); } fwrite(inp, 4, size, fp);
#endif
 fclose(fp); } void MWCNNLayerImpl::reorderedLayerOutputTap(int portIndex) { 
MWTensorBase* opTensorBase = getLayer()->getOutputTensor(portIndex); 
MWTensor<float>* opTensor = static_cast<MWTensor<float>*>(opTensorBase); 
MWCNNLayerImpl* layerImpl = cCXqPFPPcoHzYMDpnUxQ->getImpl(); int layerOutputSize = 
opTensor->getBatchSize() * opTensor->getSequenceLength() * 
opTensor->getChannels() * opTensor->getHeight() * opTensor->getWidth(); float* 
layerData = (float*)calloc(layerOutputSize, sizeof(float)); 
std::shared_ptr<dnnl::memory> currentLayerMemory = 
MWMkldnnUtils::getLayerMemoryPrimitive(opTensor); bool isMemPrimitiveNC = 
MWMkldnnUtils::checkformatType(currentLayerMemory->get_desc(), opTensor, 
dnnl::memory::format_tag::nc); bool isMemPrimitiveNCHW = 
MWMkldnnUtils::checkformatType( currentLayerMemory->get_desc(), opTensor, 
dnnl::memory::format_tag::nchw); bool isMemPrimitiveTNC = 
MWMkldnnUtils::checkformatType( currentLayerMemory->get_desc(), opTensor, 
dnnl::memory::format_tag::tnc); auto s = 
dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); if (!(isMemPrimitiveNC || 
isMemPrimitiveNCHW || isMemPrimitiveTNC)) { 
MWMkldnnUtils::configureReorder(layerImpl, opTensor, 
dnnl::memory::format_tag::nchw); pipeline.clear(); 
pipeline_memory_args.clear(); pipeline_memory_args.push_back( {{DNNL_ARG_FROM, 
*MWMkldnnUtils::getLayerMemoryPrimitive(opTensor)}, {DNNL_ARG_TO, 
*getReorderedIpMemory()}}); pipeline.push_back(*layerImpl->getReorderPrim()); 
assert(pipeline.size() == pipeline_memory_args.size()); pipeline[0].execute(s, 
pipeline_memory_args[0]); memcpy(layerData, 
(float*)layerImpl->getReorderedIpMemory()->get_data_handle(), layerOutputSize * 
sizeof(float)); } else { memcpy(layerData, opTensor->getData(), layerOutputSize 
* sizeof(float)); } mw_interm_tap(layerData, layerOutputSize, tap_count++); if 
(layerData) { free(layerData); layerData = NULL; } }
#endif