#include "MWInputLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "dnnl.hpp"
#include <memory>
 MWInputLayerImpl::MWInputLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) { } void 
MWInputLayerImpl::propagateSize() { MWTensorBase* ipTensor = 
getLayer()->getInputTensor(0); dnnl::memory::dims layerMemoryDimensions = 
{ipTensor->getBatchSize(), ipTensor->getChannels(), ipTensor->getHeight(), 
ipTensor->getWidth()}; auto layerMemoryDescriptor = dnnl::memory::desc( 
layerMemoryDimensions, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::nchw); setLayerMemory( 
std::make_shared<dnnl::memory>(layerMemoryDescriptor, 
*euppfEoiaoCTcVgRPVhA->eng)); return; } void MWInputLayerImpl::predict() {
#if MW_INPUT_TAP
 reorderedLayerOutputTap(0);
#endif
 }