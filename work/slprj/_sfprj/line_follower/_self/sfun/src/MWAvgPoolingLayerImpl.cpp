#include "MWAvgPoolingLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include <memory>
 MWAvgPoolingLayerImpl::MWAvgPoolingLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int FwLnexHgxHRquTKmNpoa, int HJHXkKmgFxxIOsIvRRnF, int 
HtQBsWTCGEkpylRklilw, int IAlDgIFcchbwRGBSfVfA, int DSsxcjIrUgZCKZovyNQf, int 
CpMjJjtGOeWOzwxpAAQP, int FeVcBgtQmTLtmnNcJGMY, int FrpxvsDMwwgbpqHXWxmN, 
int , const char* ) : MWCNNLayerImpl(layer, ntwk_impl) , 
FwLnexHgxHRquTKmNpoa(FwLnexHgxHRquTKmNpoa) , HJHXkKmgFxxIOsIvRRnF(HJHXkKmgFxxIOsIvRRnF) , 
HtQBsWTCGEkpylRklilw(HtQBsWTCGEkpylRklilw) , IAlDgIFcchbwRGBSfVfA(IAlDgIFcchbwRGBSfVfA) 
, DSsxcjIrUgZCKZovyNQf(DSsxcjIrUgZCKZovyNQf) , 
CpMjJjtGOeWOzwxpAAQP(CpMjJjtGOeWOzwxpAAQP) , 
FeVcBgtQmTLtmnNcJGMY(FeVcBgtQmTLtmnNcJGMY) , 
FrpxvsDMwwgbpqHXWxmN(FrpxvsDMwwgbpqHXWxmN) { } 
MWAvgPoolingLayerImpl::~MWAvgPoolingLayerImpl() { } void 
MWAvgPoolingLayerImpl::propagateSize() { clearLayerMapsAndVectors(); 
MWMkldnnUtils::reorderInputsTo(this); MWCNNLayer* avgpoolLayer = getLayer(); 
MWTensorBase* ipTensor = avgpoolLayer->getInputTensor(0); MWTensorBase* 
opTensor = avgpoolLayer->getOutputTensor(0); if ((FwLnexHgxHRquTKmNpoa == -1) && 
(HJHXkKmgFxxIOsIvRRnF == -1)) { FwLnexHgxHRquTKmNpoa = ipTensor->getHeight(); 
HJHXkKmgFxxIOsIvRRnF = ipTensor->getWidth(); } int n = ipTensor->getBatchSize(); 
int c = ipTensor->getChannels(); int h = ipTensor->getHeight(); int w = 
ipTensor->getWidth(); dnnl::memory::dims pool_usr_tz = {n, c, h, w}; 
dnnl::memory::dims pool_dst_tz = {n, c, opTensor->getHeight(), 
opTensor->getWidth()}; dnnl::memory::dims pool_kernel = {FwLnexHgxHRquTKmNpoa, 
HJHXkKmgFxxIOsIvRRnF}; dnnl::memory::dims GsZlHFuhbvjLtRMDjXnW = 
{HtQBsWTCGEkpylRklilw, IAlDgIFcchbwRGBSfVfA}; dnnl::memory::dims 
GnxRkpzrPZimKtYYHSuG = {DSsxcjIrUgZCKZovyNQf, FeVcBgtQmTLtmnNcJGMY}; 
dnnl::memory::dims GeeOVBfQrpMacIFBLKOo = {CpMjJjtGOeWOzwxpAAQP, 
FrpxvsDMwwgbpqHXWxmN}; auto pool_dst_md = dnnl::memory::desc({pool_dst_tz}, 
dnnl::memory::data_type::f32, dnnl::memory::format_tag::any); pool_d = 
std::unique_ptr<dnnl::pooling_forward::desc>(new dnnl::pooling_forward::desc( 
dnnl::prop_kind::forward_inference, 
dnnl::algorithm::pooling_avg_include_padding, 
getReorderedIpMemory()->get_desc(), pool_dst_md, GsZlHFuhbvjLtRMDjXnW, 
pool_kernel, GnxRkpzrPZimKtYYHSuG, GeeOVBfQrpMacIFBLKOo)); pool_pd = 
std::unique_ptr<dnnl::pooling_forward::primitive_desc>( new 
dnnl::pooling_forward::primitive_desc(*pool_d, *euppfEoiaoCTcVgRPVhA->eng)); 
setLayerMemory(std::make_shared<dnnl::memory>(pool_pd->dst_desc(), 
*euppfEoiaoCTcVgRPVhA->eng)); pool = std::unique_ptr<dnnl::pooling_forward>(new 
dnnl::pooling_forward(*pool_pd)); pipeline.push_back(*pool); 
pipeline_memory_args.push_back( {{DNNL_ARG_FROM, *getReorderedIpMemory()}, 
{DNNL_ARG_TO, *getLayerMemory()}}); } void MWAvgPoolingLayerImpl::predict() { 
auto s = dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline.size() == 
pipeline_memory_args.size()); for (int i = 0; i < pipeline.size(); i++) { 
pipeline[i].execute(s, pipeline_memory_args[i]); }
#if MW_POOL_TAP
 reorderedLayerOutputTap(0);
#endif
 return; }