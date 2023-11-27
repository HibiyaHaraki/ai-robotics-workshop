#include "MWConvLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
#include "MWCNNLayer.hpp"
#include "MWTensorBase.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include <memory>
#include <cassert>
#include <cstring>
#include <stdio.h>
#include <iostream>
#if MW_CONV_TAP
 extern int tap_count; extern void mw_interm_tap(float* inp, int size, int count);
#endif
 MWConvLayerImpl::MWConvLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl, int filt_H, int filt_W, int numGrps, int numChnls, int numFilts, int 
HtQBsWTCGEkpylRklilw, int IAlDgIFcchbwRGBSfVfA, int DSsxcjIrUgZCKZovyNQf, int 
CpMjJjtGOeWOzwxpAAQP, int FeVcBgtQmTLtmnNcJGMY, int FrpxvsDMwwgbpqHXWxmN, 
int AIXLuRgdeiqpaCehGSYD, int ATEikvMQPqBefhJzjzhc, const char* 
zzWugmJRYlNEuAzHMpeQ, const char* OVOphSOolqRQDDoKPwxy) : 
MWCNNLayerImpl(layer, ntwk_impl) , AwZQzUhuWVLGrWgLHRuM(filt_H) , 
AzTsxYcYjIEJsGQbeYHm(filt_W) , CGbFsczkgkhjcHoCKzBx(numGrps) , 
AIXLuRgdeiqpaCehGSYD(AIXLuRgdeiqpaCehGSYD) , 
ATEikvMQPqBefhJzjzhc(ATEikvMQPqBefhJzjzhc) , 
DSsxcjIrUgZCKZovyNQf(DSsxcjIrUgZCKZovyNQf) , 
CpMjJjtGOeWOzwxpAAQP(CpMjJjtGOeWOzwxpAAQP) , 
FeVcBgtQmTLtmnNcJGMY(FeVcBgtQmTLtmnNcJGMY) , 
FrpxvsDMwwgbpqHXWxmN(FrpxvsDMwwgbpqHXWxmN) , 
HtQBsWTCGEkpylRklilw(HtQBsWTCGEkpylRklilw) , IAlDgIFcchbwRGBSfVfA(IAlDgIFcchbwRGBSfVfA) 
{ int eybNKlJCSDUvsznWynwK = numChnls * numFilts * CGbFsczkgkhjcHoCKzBx * 
AwZQzUhuWVLGrWgLHRuM * AzTsxYcYjIEJsGQbeYHm; veFyKKHbdqBIvQLYBqfF = 
(float*)calloc(eybNKlJCSDUvsznWynwK, sizeof(float)); NMMfJylfQjiIUAKhXCJb = 
(float*)calloc(numFilts * CGbFsczkgkhjcHoCKzBx, sizeof(float)); 
loadWeights(zzWugmJRYlNEuAzHMpeQ, eybNKlJCSDUvsznWynwK); 
loadBias(OVOphSOolqRQDDoKPwxy, numFilts); auto weights_md = 
CGbFsczkgkhjcHoCKzBx > 1 ? dnnl::memory::desc({{CGbFsczkgkhjcHoCKzBx, numFilts, 
numChnls, AwZQzUhuWVLGrWgLHRuM, AzTsxYcYjIEJsGQbeYHm}, 
dnnl::memory::data_type::f32, dnnl::memory::format_tag::goihw}) : 
dnnl::memory::desc({{numFilts, numChnls, AwZQzUhuWVLGrWgLHRuM, 
AzTsxYcYjIEJsGQbeYHm}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::oihw}); weights = std::shared_ptr<dnnl::memory>( new 
dnnl::memory(weights_md, *euppfEoiaoCTcVgRPVhA->eng, veFyKKHbdqBIvQLYBqfF)); auto 
bias_md = with_bias ? dnnl::memory::desc({{numFilts * CGbFsczkgkhjcHoCKzBx}, 
dnnl::memory::data_type::f32, dnnl::memory::format_tag::x}) : 
dnnl::memory::desc({{}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::x}); bias = with_bias ? 
std::shared_ptr<dnnl::memory>( new dnnl::memory(bias_md, 
*euppfEoiaoCTcVgRPVhA->eng, NMMfJylfQjiIUAKhXCJb)) : std::shared_ptr<dnnl::memory>(new 
dnnl::memory(bias_md, *euppfEoiaoCTcVgRPVhA->eng)); conv_weights_md = 
CGbFsczkgkhjcHoCKzBx > 1 ? std::unique_ptr<dnnl::memory::desc>(new 
dnnl::memory::desc( {CGbFsczkgkhjcHoCKzBx, numFilts, numChnls, 
AwZQzUhuWVLGrWgLHRuM, AzTsxYcYjIEJsGQbeYHm}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::any)) : std::unique_ptr<dnnl::memory::desc>(new 
dnnl::memory::desc( {numFilts, numChnls, AwZQzUhuWVLGrWgLHRuM, 
AzTsxYcYjIEJsGQbeYHm}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::any)); conv_bias_md = 
std::unique_ptr<dnnl::memory::desc>( new dnnl::memory::desc({numFilts * 
CGbFsczkgkhjcHoCKzBx}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::any)); reorderedWeightsDesc = weights->get_desc(); } 
void MWConvLayerImpl::propagateSize() { clearLayerMapsAndVectors(); MWCNNLayer* 
convLayer = getLayer(); MWTensorBase* ipTensor = convLayer->getInputTensor(0); 
MWTensorBase* opTensor = convLayer->getOutputTensor(0); int n = 
ipTensor->getBatchSize(); int c = ipTensor->getChannels(); int h = 
ipTensor->getHeight(); int w = ipTensor->getWidth(); int num_filts = 
opTensor->getChannels(); conv_src_md = std::unique_ptr<dnnl::memory::desc>(new 
dnnl::memory::desc( {n, c, h, w}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::any)); conv_dst_md = 
std::unique_ptr<dnnl::memory::desc>( new dnnl::memory::desc({n, num_filts, 
opTensor->getHeight(), opTensor->getWidth()}, dnnl::memory::data_type::f32, 
dnnl::memory::format_tag::any)); conv_d = with_bias ? 
std::unique_ptr<dnnl::convolution_forward::desc>(new 
dnnl::convolution_forward::desc( dnnl::prop_kind::forward_inference, 
dnnl::algorithm::convolution_direct, *conv_src_md, *conv_weights_md, 
*conv_bias_md, *conv_dst_md, {HtQBsWTCGEkpylRklilw, IAlDgIFcchbwRGBSfVfA}, 
{AIXLuRgdeiqpaCehGSYD - 1, ATEikvMQPqBefhJzjzhc - 1}, 
{DSsxcjIrUgZCKZovyNQf, FeVcBgtQmTLtmnNcJGMY}, {CpMjJjtGOeWOzwxpAAQP, 
FrpxvsDMwwgbpqHXWxmN})) : std::unique_ptr<dnnl::convolution_forward::desc>(new 
dnnl::convolution_forward::desc( dnnl::prop_kind::forward_inference, 
dnnl::algorithm::convolution_direct, *conv_src_md, *conv_weights_md, 
*conv_dst_md, {HtQBsWTCGEkpylRklilw, IAlDgIFcchbwRGBSfVfA}, 
{AIXLuRgdeiqpaCehGSYD - 1, ATEikvMQPqBefhJzjzhc - 1}, 
{DSsxcjIrUgZCKZovyNQf, FeVcBgtQmTLtmnNcJGMY}, {CpMjJjtGOeWOzwxpAAQP, 
FrpxvsDMwwgbpqHXWxmN})); conv_pd = 
std::unique_ptr<dnnl::convolution_forward::primitive_desc>( new 
dnnl::convolution_forward::primitive_desc(*conv_d, *euppfEoiaoCTcVgRPVhA->eng)); 
conv_src_memory = MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor); if 
(dnnl::memory::desc(conv_pd->src_desc()) != 
MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor)->get_desc()) { conv_src_memory 
= std::make_shared<dnnl::memory>(conv_pd->src_desc(), 
*euppfEoiaoCTcVgRPVhA->eng); conv_reorder_src = std::unique_ptr<dnnl::reorder>( 
new dnnl::reorder(*MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor), 
*conv_src_memory)); pipeline_memory_args.push_back( {{DNNL_ARG_FROM, 
*MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor)}, {DNNL_ARG_TO, 
*conv_src_memory}}); pipeline.push_back(*conv_reorder_src); } 
setReorderLayerMemory(conv_src_memory); if 
(dnnl::memory::desc(conv_pd->weights_desc()) != weights->get_desc()) { if 
(conv_pd->weights_desc() != reorderedWeightsDesc) { conv_weights_memory = 
std::make_shared<dnnl::memory>(conv_pd->weights_desc(), 
*euppfEoiaoCTcVgRPVhA->eng); conv_reorder_weights = 
std::unique_ptr<dnnl::reorder>(new dnnl::reorder(*weights, 
*conv_weights_memory)); pipeline_weights_memory_args.push_back( 
{{DNNL_ARG_FROM, *weights}, {DNNL_ARG_TO, *conv_weights_memory}}); 
pipeline_weights.push_back(*conv_reorder_weights); auto s = 
dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline_weights.size() == 
pipeline_weights_memory_args.size()); for (int i = 0; i < 
pipeline_weights.size(); i++) { pipeline_weights[i].execute(s, 
pipeline_weights_memory_args[i]); } reorderedWeightsDesc = 
conv_pd->weights_desc(); } } else{ conv_weights_memory = weights; } 
setLayerMemory(std::make_shared<dnnl::memory>(conv_pd->dst_desc(), 
*euppfEoiaoCTcVgRPVhA->eng)); conv = 
std::unique_ptr<dnnl::convolution_forward>(new 
dnnl::convolution_forward(*conv_pd)); if (with_bias) { 
pipeline_memory_args.push_back({{DNNL_ARG_SRC, *conv_src_memory}, 
{DNNL_ARG_WEIGHTS, *conv_weights_memory}, {DNNL_ARG_BIAS, *bias}, 
{DNNL_ARG_DST, *getLayerMemory()}}); } else { 
pipeline_memory_args.push_back({{DNNL_ARG_SRC, *conv_src_memory}, 
{DNNL_ARG_WEIGHTS, *conv_weights_memory}, {DNNL_ARG_DST, *getLayerMemory()}}); 
} pipeline.push_back(*conv); return; } void MWConvLayerImpl::predict() { auto s 
= dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline.size() == 
pipeline_memory_args.size()); for (int i = 0; i < pipeline.size(); i++) { 
pipeline[i].execute(s, pipeline_memory_args[i]); }
#if MW_CONV_TAP
 reorderedLayerOutputTap(0);
#endif
 return; } MWConvLayerImpl::~MWConvLayerImpl() { } void 
MWConvLayerImpl::cleanup() { if (veFyKKHbdqBIvQLYBqfF) { free(veFyKKHbdqBIvQLYBqfF); 
veFyKKHbdqBIvQLYBqfF = NULL; } if (NMMfJylfQjiIUAKhXCJb) { free(NMMfJylfQjiIUAKhXCJb); NMMfJylfQjiIUAKhXCJb = 
NULL; } return; } void MWConvLayerImpl::loadWeights(const char* 
SGsAudmgjmvcUXzzrUtf, int eybNKlJCSDUvsznWynwK) { FILE* SUleyRyvAggTFnSdxLru = 
MWCNNLayer::openBinaryFile(SGsAudmgjmvcUXzzrUtf); 
MWCNNLayer::call_fread(veFyKKHbdqBIvQLYBqfF, sizeof(float), eybNKlJCSDUvsznWynwK, 
SUleyRyvAggTFnSdxLru, SGsAudmgjmvcUXzzrUtf); fclose(SUleyRyvAggTFnSdxLru); return; } void 
MWConvLayerImpl::loadBias(const char* SGsAudmgjmvcUXzzrUtf, int 
CDJtexcMbXMWAmnNZsNf) { float* NZjOkZPwLzQsdEVkwMcX = NMMfJylfQjiIUAKhXCJb; FILE* 
SUleyRyvAggTFnSdxLru = MWCNNLayer::openBinaryFile(SGsAudmgjmvcUXzzrUtf); int 
eybNKlJCSDUvsznWynwK = CDJtexcMbXMWAmnNZsNf * CGbFsczkgkhjcHoCKzBx;  
MWCNNLayer::call_fread(NZjOkZPwLzQsdEVkwMcX, sizeof(float), eybNKlJCSDUvsznWynwK, 
SUleyRyvAggTFnSdxLru, SGsAudmgjmvcUXzzrUtf); fclose(SUleyRyvAggTFnSdxLru); return; }