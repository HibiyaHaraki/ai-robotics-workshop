#include "MWCNNLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWMkldnnUtils.hpp"
#include "MWCustomLayerForMKLDNN.hpp"
#include "dnnl.hpp"
#include <cassert>
#include <cstring>
#include <cstdio>
 void MWMkldnnUtils::configureReorder(MWCNNLayerImpl* layerImpl, MWTensorBase* 
srcTensor, format_type dstDataFormat, int index) { 
std::shared_ptr<dnnl::memory> ipLayerMemory = 
MWMkldnnUtils::getLayerMemoryPrimitive(srcTensor); dnnl::memory::dims 
layerMemoryDimensions; if (dstDataFormat == format_type::TNC_FORMAT) { 
layerMemoryDimensions = {srcTensor->getSequenceLength(), 
srcTensor->getBatchSize(), srcTensor->getChannels()}; } else { 
layerMemoryDimensions = {srcTensor->getBatchSize() * 
srcTensor->getSequenceLength(), srcTensor->getChannels(), 
srcTensor->getHeight(), srcTensor->getWidth()}; } dnnl::memory::desc 
layerMemoryDescriptor; if(dstDataFormat != format_type::NCWH_FORMAT){ 
dnnl::memory::format_tag formatTag = 
MWMkldnnUtils::getMKLDNNFormatTag(dstDataFormat); layerMemoryDescriptor = 
dnnl::memory::desc(layerMemoryDimensions, dnnl::memory::data_type::f32, 
formatTag); }else{  assert(dstDataFormat == format_type::NCWH_FORMAT); const 
int size = 4; int outDims_nchw[size]; int strides_nchw[size]; 
MWTensorBase::DIMSLABEL NCWHLayout[size] = {MWTensorBase::N, MWTensorBase::C, 
MWTensorBase::W, MWTensorBase::H}; MWTensorBase::DIMSLABEL srcLayout[size] = 
{MWTensorBase::N, MWTensorBase::C, MWTensorBase::H, MWTensorBase::W}; 
srcTensor->getDimsByLayout(NCWHLayout, size, outDims_nchw); 
MWTensorBase::getTransformStrides(srcLayout, NCWHLayout, outDims_nchw, size, 
strides_nchw); dnnl::memory::dims layerMemoryStrides = {strides_nchw[0], 
strides_nchw[1], strides_nchw[2], strides_nchw[3]}; layerMemoryDescriptor = 
dnnl::memory::desc( layerMemoryDimensions, dnnl::memory::data_type::f32, 
layerMemoryStrides); } layerImpl->setReorderLayerMemory( 
std::make_shared<dnnl::memory>(layerMemoryDescriptor, 
*(layerImpl->getTargetImpl())->eng), index); layerImpl->setReorderPrim( 
std::make_shared<dnnl::reorder>(*ipLayerMemory, 
*layerImpl->getReorderedIpMemory(index)), index); } void 
MWMkldnnUtils::TargetImplconfigureReorder(MWTargetNetworkImpl* targetImpl, 
MWTensorBase* srcTensor, dnnl::memory::format_tag dstDataFormat) { 
std::shared_ptr<dnnl::memory> ipLayerMemory = 
MWMkldnnUtils::getLayerMemoryPrimitive(srcTensor); dnnl::memory::dims 
layerMemoryDimensions = {srcTensor->getBatchSize() * 
srcTensor->getSequenceLength(), srcTensor->getChannels(), 
srcTensor->getHeight(), srcTensor->getWidth()}; auto layerMemoryDescriptor = 
dnnl::memory::desc(layerMemoryDimensions, dnnl::memory::data_type::f32, 
dstDataFormat); targetImpl->setReorderLayerMemory( 
std::make_shared<dnnl::memory>(layerMemoryDescriptor, *(targetImpl)->eng)); 
targetImpl->setReorderPrim( std::make_shared<dnnl::reorder>(*ipLayerMemory, 
*targetImpl->getReorderLayerMemory())); } format_type 
MWMkldnnUtils::getformatType(dnnl::memory::desc inputdesc, MWTensorBase* 
srcTensor) { dnnl::memory::dims layerMemoryDimensionsNC = { 
srcTensor->getSequenceLength() * srcTensor->getBatchSize(), 
srcTensor->getChannels() * srcTensor->getHeight() * srcTensor->getWidth()}; 
dnnl::memory::dims layerMemoryDimensions = { srcTensor->getSequenceLength() * 
srcTensor->getBatchSize(), srcTensor->getChannels(), srcTensor->getHeight(), 
srcTensor->getWidth()}; dnnl::memory::dims layerMemoryDimensionsTNC = { 
srcTensor->getSequenceLength(), srcTensor->getBatchSize(), 
srcTensor->getChannels()}; auto layerMemoryDescriptorNC = dnnl::memory::desc( 
layerMemoryDimensionsNC, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::nc); if (inputdesc == layerMemoryDescriptorNC) { 
return format_type::NC_FORMAT; } auto layerMemoryDescriptorNCHW = 
dnnl::memory::desc( layerMemoryDimensions, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::nchw); if (inputdesc == layerMemoryDescriptorNCHW) { 
return format_type::NCHW_FORMAT; } auto layerMemoryDescriptorNHWC = 
dnnl::memory::desc( layerMemoryDimensions, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::nhwc); if (inputdesc == layerMemoryDescriptorNHWC) { 
return format_type::NHWC_FORMAT; } auto layerMemoryDescriptorNCHW8C = 
dnnl::memory::desc( layerMemoryDimensions, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::nChw8c); if (inputdesc == 
layerMemoryDescriptorNCHW8C) { return format_type::NCHW8C_FORMAT; } auto 
layerMemoryDescriptorNCHW16C = dnnl::memory::desc( layerMemoryDimensions, 
dnnl::memory::data_type::f32, dnnl::memory::format_tag::nChw16c); if (inputdesc 
== layerMemoryDescriptorNCHW16C) { return format_type::NCHW16C_FORMAT; } const 
int size = 4; int outDims_nchw[size]; int strides_nchw[size]; 
MWTensorBase::DIMSLABEL NCWHLayout[size] = {MWTensorBase::N, MWTensorBase::C, 
MWTensorBase::W, MWTensorBase::H}; MWTensorBase::DIMSLABEL srcLayout[size] = 
{MWTensorBase::N, MWTensorBase::C, MWTensorBase::H, MWTensorBase::W}; 
srcTensor->getDimsByLayout(NCWHLayout, size, outDims_nchw); 
MWTensorBase::getTransformStrides(srcLayout, NCWHLayout, outDims_nchw, size, 
strides_nchw); dnnl::memory::dims layerMemoryStrides = {strides_nchw[0], 
strides_nchw[1], strides_nchw[2], strides_nchw[3]}; auto 
layerMemoryDescriptorNCWH = dnnl::memory::desc( layerMemoryDimensions, 
dnnl::memory::data_type::f32, layerMemoryStrides); if (inputdesc == 
layerMemoryDescriptorNCWH) { return format_type::NCWH_FORMAT; } 
MWTensorBase::DIMSLABEL HWCNLayout[size] = {MWTensorBase::H, MWTensorBase::W, 
MWTensorBase::C, MWTensorBase::N}; srcTensor->getDimsByLayout(HWCNLayout, size, 
outDims_nchw); MWTensorBase::getTransformStrides(srcLayout, HWCNLayout, 
outDims_nchw, size, strides_nchw); layerMemoryStrides = {strides_nchw[0], 
strides_nchw[1], strides_nchw[2], strides_nchw[3]}; auto 
layerMemoryDescriptorHWCN = dnnl::memory::desc( layerMemoryDimensions, 
dnnl::memory::data_type::f32, layerMemoryStrides); if (inputdesc == 
layerMemoryDescriptorHWCN) { return format_type::HWCN_FORMAT; } auto 
layerMemoryDescriptorTNC = dnnl::memory::desc( layerMemoryDimensionsTNC, 
dnnl::memory::data_type::f32, dnnl::memory::format_tag::tnc); if (inputdesc == 
layerMemoryDescriptorTNC) { return format_type::TNC_FORMAT; } const int 
size_tnc = 3; int outDims_tnc[size_tnc]; int strides_tnc[size_tnc]; 
MWTensorBase::DIMSLABEL TNCLayout[size_tnc] = {MWTensorBase::C, 
MWTensorBase::N, MWTensorBase::S}; MWTensorBase::DIMSLABEL 
srcLayout_tnc[size_tnc] = {MWTensorBase::S, MWTensorBase::N, MWTensorBase::C}; 
srcTensor->getDimsByLayout(TNCLayout, size_tnc, outDims_tnc); 
MWTensorBase::getTransformStrides(srcLayout_tnc, TNCLayout, outDims_tnc, 
size_tnc, strides_tnc); layerMemoryStrides = {strides_tnc[0], strides_tnc[1], 
strides_tnc[2]}; auto layerMemoryDescriptorCNT = dnnl::memory::desc( 
layerMemoryDimensionsTNC, dnnl::memory::data_type::f32, layerMemoryStrides); if 
(inputdesc == layerMemoryDescriptorCNT) { return format_type::CNT_FORMAT; } 
return format_type::UNKNOWN_FORMAT; } bool 
MWMkldnnUtils::checkformatType(dnnl::memory::desc inputdesc, MWTensorBase* 
srcTensor, dnnl::memory::format_tag dstDataFormat) { dnnl::memory::dims 
layerMemoryDimensions = { srcTensor->getSequenceLength() * 
srcTensor->getBatchSize(), srcTensor->getChannels(), srcTensor->getHeight(), 
srcTensor->getWidth()}; if (dstDataFormat == dnnl::memory::format_tag::nc) { 
layerMemoryDimensions = { srcTensor->getSequenceLength() * 
srcTensor->getBatchSize(), srcTensor->getChannels() * srcTensor->getHeight() * 
srcTensor->getWidth()}; } else if (dstDataFormat == 
dnnl::memory::format_tag::tnc) { layerMemoryDimensions = 
{srcTensor->getSequenceLength(), srcTensor->getBatchSize(), 
srcTensor->getChannels()}; } auto layerMemoryDescriptor = 
dnnl::memory::desc(layerMemoryDimensions, dnnl::memory::data_type::f32, 
dstDataFormat); bool isformatMatched = (layerMemoryDescriptor == inputdesc); 
return isformatMatched; } std::shared_ptr<dnnl::memory> 
MWMkldnnUtils::getLayerMemoryPrimitive(MWTensorBase* aTensor) { auto 
owningLayer = aTensor->getOwner(); auto owningLayerImpl = 
owningLayer->getImpl(); if (owningLayerImpl == NULL) { if 
(owningLayer->isCustomLayer()) { return 
dynamic_cast<MWCustomLayerForMKLDNN*>(owningLayer) 
->getCustomLayerMemory(aTensor); } else { int inIndex = 
owningLayer->getInPlaceIndex(aTensor->getSourcePortIndex()); bool 
isInplaceLayer = (inIndex != -1); bool isSingleIpLayer = 
(owningLayer->getNumInputs() == 1); assert(isSingleIpLayer || isInplaceLayer); 
if (isSingleIpLayer) { return 
MWMkldnnUtils::getLayerMemoryPrimitive(owningLayer->getInputTensor(0)); } else{ 
return 
MWMkldnnUtils::getLayerMemoryPrimitive(owningLayer->getInputTensor(inIndex)); } 
} } else { auto layerMemory = 
owningLayerImpl->getLayerMemory(aTensor->getSourcePortIndex()); if 
(layerMemory) { return layerMemory; } else { assert(owningLayer->getNumInputs() 
== 1); return 
MWMkldnnUtils::getLayerMemoryPrimitive(owningLayer->getInputTensor(0)); } } } 
bool MWMkldnnUtils::isReorderNeeded(format_type formatTag) { return ((formatTag 
!= format_type::NC_FORMAT) && (formatTag != format_type::NCHW_FORMAT) && 
(formatTag != format_type::TNC_FORMAT) && (formatTag != 
format_type::NCHW8C_FORMAT)); } void 
MWMkldnnUtils::reorderInputsTo(MWCNNLayerImpl* layerImpl, format_type 
formatTag) { if (formatTag == format_type::OPTIMAL_FORMAT) {  bool isAVX512 = 
layerImpl->getTargetImpl()->isAVX512; formatTag = isAVX512 ? 
format_type::NCHW16C_FORMAT : format_type::NCHW8C_FORMAT; for (int k = 0; k < 
layerImpl->getLayer()->getNumInputs(); k++) { MWTensorBase* srcTensork = 
layerImpl->getLayer()->getInputTensor(static_cast<int>(k)); auto 
prevMemoryDesck = 
MWMkldnnUtils::getLayerMemoryPrimitive(srcTensork)->get_desc(); format_type 
ipFormatTag = MWMkldnnUtils::getformatType(prevMemoryDesck, srcTensork); 
assert(ipFormatTag != format_type::NC_FORMAT);  if ((isAVX512 && ipFormatTag != 
format_type::NCHW16C_FORMAT) || (!isAVX512 && (ipFormatTag != 
format_type::NCHW8C_FORMAT))) { if (ipFormatTag == format_type::TNC_FORMAT || 
ipFormatTag == format_type::CNT_FORMAT) {  formatTag = format_type::TNC_FORMAT; 
break; } else if ((isAVX512 && srcTensork->getChannels() % 16 <= 8 && 
srcTensork->getChannels() % 16 != 0) || (!isAVX512 && srcTensork->getChannels() 
% 8 <= 4 && srcTensork->getChannels() % 8 != 0)) { formatTag = 
format_type::NCHW_FORMAT; break; } } } } for (int k = 0; k < 
layerImpl->getLayer()->getNumInputs(); k++) { MWTensorBase* srcTensork = 
layerImpl->getLayer()->getInputTensor(static_cast<int>(k)); auto 
prevMemoryDesck = 
MWMkldnnUtils::getLayerMemoryPrimitive(srcTensork)->get_desc(); format_type 
ipFormatTag = MWMkldnnUtils::getformatType(prevMemoryDesck, srcTensork); 
format_type prevformatTag; if ((ipFormatTag != formatTag)) {  
MWMkldnnUtils::configureReorder(layerImpl, srcTensork, formatTag, k); 
layerImpl->getPipeline().push_back(*(layerImpl->getReorderPrim(k))); 
layerImpl->getArgumentsPipeline().push_back( {{DNNL_ARG_FROM, 
*MWMkldnnUtils::getLayerMemoryPrimitive(srcTensork)}, {DNNL_ARG_TO, 
*(layerImpl->getReorderedIpMemory(k))}}); ipFormatTag = formatTag; } else { 
layerImpl->setReorderLayerMemory(MWMkldnnUtils::getLayerMemoryPrimitive(srcTensork), 
k); } if (k > 0) { assert(prevformatTag == ipFormatTag); } prevformatTag = 
ipFormatTag; } } dnnl::memory::format_tag 
MWMkldnnUtils::getMKLDNNFormatTag(format_type formatType) { assert((formatType 
== format_type::NCHW_FORMAT) || (formatType == format_type::NHWC_FORMAT) || 
(formatType == format_type::NCHW8C_FORMAT) || (formatType == 
format_type::NCHW16C_FORMAT) || (formatType == format_type::TNC_FORMAT)); 
switch (formatType) { case format_type::NCHW_FORMAT: return 
dnnl::memory::format_tag::nchw; case format_type::NHWC_FORMAT: return 
dnnl::memory::format_tag::nhwc; case format_type::NCHW8C_FORMAT: return 
dnnl::memory::format_tag::nChw8c; case format_type::NCHW16C_FORMAT: return 
dnnl::memory::format_tag::nChw16c; default: assert(formatType == 
format_type::TNC_FORMAT); return dnnl::memory::format_tag::tnc; } }