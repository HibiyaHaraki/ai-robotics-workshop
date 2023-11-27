#include "MWMaxPoolingLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include <memory>
 MWMaxPoolingLayerImpl::MWMaxPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int FwLnexHgxHRquTKmNpoa, int HJHXkKmgFxxIOsIvRRnF, int 
HtQBsWTCGEkpylRklilw, int IAlDgIFcchbwRGBSfVfA, int DSsxcjIrUgZCKZovyNQf, int 
CpMjJjtGOeWOzwxpAAQP, int FeVcBgtQmTLtmnNcJGMY, int FrpxvsDMwwgbpqHXWxmN, 
bool JgLfgHrHMEMmMYTettJF, int , const char* , int fjfzkUfcCOqjrkAVGfuc) : 
MWCNNLayerImpl(layer, ntwk_impl) , 
BLjrjqvCcCommiXWQLjs(JgLfgHrHMEMmMYTettJF) , 
FwLnexHgxHRquTKmNpoa(FwLnexHgxHRquTKmNpoa) , HJHXkKmgFxxIOsIvRRnF(HJHXkKmgFxxIOsIvRRnF) , 
DSsxcjIrUgZCKZovyNQf(DSsxcjIrUgZCKZovyNQf) , 
CpMjJjtGOeWOzwxpAAQP(CpMjJjtGOeWOzwxpAAQP) , 
FeVcBgtQmTLtmnNcJGMY(FeVcBgtQmTLtmnNcJGMY) , 
FrpxvsDMwwgbpqHXWxmN(FrpxvsDMwwgbpqHXWxmN) , 
HtQBsWTCGEkpylRklilw(HtQBsWTCGEkpylRklilw) , IAlDgIFcchbwRGBSfVfA(IAlDgIFcchbwRGBSfVfA) 
, fjfzkUfcCOqjrkAVGfuc(fjfzkUfcCOqjrkAVGfuc) { } 
MWMaxPoolingLayerImpl::~MWMaxPoolingLayerImpl() { } float* 
MWMaxPoolingLayerImpl::getIndexData() { return WOJynDmqVUPWjAGVIuMQ; } 
std::shared_ptr<dnnl::pooling_forward::primitive_desc> 
MWMaxPoolingLayerImpl::getPoolPrimitiveDesc() { return pool_pd; } 
dnnl::memory::dims MWMaxPoolingLayerImpl::getPoolKernel() { return 
GFienSVKLlDQuZeqAdLC; } dnnl::memory::dims 
MWMaxPoolingLayerImpl::getPoolStrides() { return GsZlHFuhbvjLtRMDjXnW; } 
dnnl::memory::dims MWMaxPoolingLayerImpl::getPoolPadTL() { return 
GnxRkpzrPZimKtYYHSuG; } dnnl::memory::dims 
MWMaxPoolingLayerImpl::getPoolPadBR() { return GeeOVBfQrpMacIFBLKOo; } void 
createMaxpoolingIndicesPrimitive( dnnl::memory::desc pool_dst_md, 
std::shared_ptr<dnnl::pooling_forward::desc> pool_d, 
std::shared_ptr<dnnl::pooling_forward::primitive_desc>& pool_pd, 
std::shared_ptr<dnnl::memory> srcMemory, std::shared_ptr<dnnl::memory>& 
layerMemory, std::shared_ptr<dnnl::memory>& indices_Memory, 
std::shared_ptr<dnnl::pooling_forward::primitive>& pool, dnnl::memory::dims 
GFienSVKLlDQuZeqAdLC, dnnl::memory::dims GsZlHFuhbvjLtRMDjXnW, 
dnnl::memory::dims GnxRkpzrPZimKtYYHSuG, dnnl::memory::dims 
GeeOVBfQrpMacIFBLKOo) { pool_d = std::make_shared<dnnl::pooling_forward::desc>( 
dnnl::prop_kind::forward_training, dnnl::algorithm::pooling_max, 
srcMemory->get_desc(), pool_dst_md, GsZlHFuhbvjLtRMDjXnW, GFienSVKLlDQuZeqAdLC, 
GnxRkpzrPZimKtYYHSuG, GeeOVBfQrpMacIFBLKOo); pool_pd = 
std::make_shared<dnnl::pooling_forward::primitive_desc>(*pool_d, 
srcMemory->get_engine()); layerMemory = 
std::make_shared<dnnl::memory>(pool_pd->dst_desc(), srcMemory->get_engine()); 
indices_Memory = std::make_shared<dnnl::memory>(pool_pd->workspace_desc(), 
srcMemory->get_engine()); pool = 
std::make_shared<dnnl::pooling_forward>(*pool_pd); } void 
createMaxpoolingPrimitive(dnnl::memory::desc pool_dst_md, 
std::shared_ptr<dnnl::pooling_forward::desc> pool_d, 
std::shared_ptr<dnnl::pooling_forward::primitive_desc>& pool_pd, 
std::shared_ptr<dnnl::memory> srcMemory, std::shared_ptr<dnnl::memory>& 
layerMemory, std::shared_ptr<dnnl::pooling_forward::primitive>& pool, 
dnnl::memory::dims GFienSVKLlDQuZeqAdLC, dnnl::memory::dims 
GsZlHFuhbvjLtRMDjXnW, dnnl::memory::dims GnxRkpzrPZimKtYYHSuG, 
dnnl::memory::dims GeeOVBfQrpMacIFBLKOo) { pool_d = 
std::make_shared<dnnl::pooling_forward::desc>( 
dnnl::prop_kind::forward_inference, dnnl::algorithm::pooling_max, 
srcMemory->get_desc(), pool_dst_md, GsZlHFuhbvjLtRMDjXnW, GFienSVKLlDQuZeqAdLC, 
GnxRkpzrPZimKtYYHSuG, GeeOVBfQrpMacIFBLKOo); pool_pd = 
std::make_shared<dnnl::pooling_forward::primitive_desc>(*pool_d, 
srcMemory->get_engine()); layerMemory = 
std::make_shared<dnnl::memory>(pool_pd->dst_desc(), srcMemory->get_engine()); 
pool = std::make_shared<dnnl::pooling_forward>(*pool_pd); } void 
MWMaxPoolingLayerImpl::propagateSize() { clearLayerMapsAndVectors(); 
MWCNNLayer* maxPoolLayer = getLayer(); MWTensorBase* ipTensor = 
maxPoolLayer->getInputTensor(); MWTensorBase* opTensor = 
maxPoolLayer->getOutputTensor(); MWMkldnnUtils::reorderInputsTo(this); int n = 
ipTensor->getBatchSize(); int c = ipTensor->getChannels(); int h = 
ipTensor->getHeight(); int w = ipTensor->getWidth(); dnnl::memory::dims 
pool_usr_tz = {n, c, h, w}; dnnl::memory::dims pool_dst_tz = {n, c, 
opTensor->getHeight(), opTensor->getWidth()}; GFienSVKLlDQuZeqAdLC = 
{FwLnexHgxHRquTKmNpoa, HJHXkKmgFxxIOsIvRRnF}; GsZlHFuhbvjLtRMDjXnW = 
{HtQBsWTCGEkpylRklilw, IAlDgIFcchbwRGBSfVfA}; GnxRkpzrPZimKtYYHSuG = 
{DSsxcjIrUgZCKZovyNQf, FeVcBgtQmTLtmnNcJGMY}; GeeOVBfQrpMacIFBLKOo = 
{CpMjJjtGOeWOzwxpAAQP, FrpxvsDMwwgbpqHXWxmN}; auto pool_dst_md = 
dnnl::memory::desc({pool_dst_tz}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::any); if (BLjrjqvCcCommiXWQLjs) { 
createMaxpoolingIndicesPrimitive(pool_dst_md, pool_d, pool_pd, 
getReorderedIpMemory(), layerMemory[0], layerMemory[1], pool, 
GFienSVKLlDQuZeqAdLC, GsZlHFuhbvjLtRMDjXnW, GnxRkpzrPZimKtYYHSuG, 
GeeOVBfQrpMacIFBLKOo); fhikqqlnUKCjleVKDqiG = 
static_cast<int>(getLayerMemory(1)->get_desc().get_size() / sizeof(float)); 
pipeline_memory_args.push_back({{DNNL_ARG_FROM, *getReorderedIpMemory()}, 
{DNNL_ARG_DST, *layerMemory[0]}, {DNNL_ARG_WORKSPACE, *layerMemory[1]}}); } 
else { createMaxpoolingPrimitive(pool_dst_md, pool_d, pool_pd, 
getReorderedIpMemory(), layerMemory[0], pool, GFienSVKLlDQuZeqAdLC, 
GsZlHFuhbvjLtRMDjXnW, GnxRkpzrPZimKtYYHSuG, GeeOVBfQrpMacIFBLKOo); 
pipeline_memory_args.push_back( {{DNNL_ARG_FROM, *getReorderedIpMemory()}, 
{DNNL_ARG_DST, *layerMemory[0]}}); } pipeline.push_back(*pool); return; } void 
MWMaxPoolingLayerImpl::predict() { auto s = 
dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline.size() == 
pipeline_memory_args.size()); for (int i = 0; i < pipeline.size(); i++) { 
pipeline[i].execute(s, pipeline_memory_args[i]); }
#if MW_POOL_TAP
 reorderedLayerOutputTap(0);
#endif
 return; }