#include "MWOutputLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include <memory>
 class MWTensorBase; MWOutputLayerImpl::MWOutputLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) { } 
MWOutputLayerImpl::~MWOutputLayerImpl() { } void 
MWOutputLayerImpl::propagateSize() { clearLayerMapsAndVectors(); MWTensorBase* 
ipTensor = getLayer()->getInputTensor(0); auto prevMemoryDesc = 
MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor)->get_desc(); format_type 
formatTag = MWMkldnnUtils::getformatType(prevMemoryDesc, ipTensor); bool 
isSequenceIp = (formatTag == format_type::TNC_FORMAT) || (formatTag == 
format_type::CNT_FORMAT); format_type reorderIpTo = isSequenceIp ? 
(format_type::TNC_FORMAT) : (format_type::NCHW_FORMAT); 
MWMkldnnUtils::reorderInputsTo(this, reorderIpTo); 
setLayerMemory(std::make_shared<dnnl::memory>(getReorderedIpMemory()->get_desc(), 
*euppfEoiaoCTcVgRPVhA->eng)); } void MWOutputLayerImpl::predict() { MWCNNLayer* 
outputLayer = getLayer(); int WIxRBCJtmETvfxpuRuus = 
outputLayer->getInPlaceIndex(0); assert(WIxRBCJtmETvfxpuRuus != -1); auto s = 
dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline.size() == 
pipeline_memory_args.size()); for (int i = 0; i < pipeline.size(); i++) { 
pipeline[i].execute(s, pipeline_memory_args[i]); } }