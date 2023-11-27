#include "MWElementwiseAffineLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWMkldnnUtils.hpp"
#include "dnnl.hpp"
#include <memory>
#include <math.h>
#include <cassert>
#include <cstdio>
#include <algorithm>
 MWElementwiseAffineLayerImpl::MWElementwiseAffineLayerImpl(MWCNNLayer* layer, 
MWTargetNetworkImpl* ntwk_impl, int scale_H, int scale_W, int scale_C, int 
offset_H, int offset_W, int offset_C, bool isClipped, int lowerbound, int 
upperbound, const char* scale_file, const char* offset_file) : 
MWCNNLayerImpl(layer, ntwk_impl) , intermediateOp(NULL) , 
sRECVoNNtDdcBOWgDyar(scale_H) , sxuOMwKXOKfuExclRaSe(scale_W) , 
rSmEWccbJFfPGddhPemm(scale_C) , jLyhrFjMmVnNjoeDJCwH(offset_H) , 
jhFUWlztBndwjbXwYNaJ(offset_W) , iPqBiFnIJMxelVhQBZex(offset_C) , 
bMAyVFGSPDjmUbziYLAy(isClipped) , enPbWLzEmxYCBmzGJutZ(lowerbound) , 
vIWQzNvYZSuxmOTVDFhU(upperbound) { long int shEncNmxJsMuJKwbrwok = (long 
int)(sRECVoNNtDdcBOWgDyar * sxuOMwKXOKfuExclRaSe * rSmEWccbJFfPGddhPemm); long int 
jaqKGCwoANNDMHgAsehk = (long int)(jLyhrFjMmVnNjoeDJCwH * jhFUWlztBndwjbXwYNaJ * 
iPqBiFnIJMxelVhQBZex); qWwjVYwfnvEnFKlgpqwA = (float*)calloc(shEncNmxJsMuJKwbrwok, 
sizeof(float)); hnewnpwgzKmOdualajhn = (float*)calloc(jaqKGCwoANNDMHgAsehk, 
sizeof(float)); loadScale(scale_file); loadOffset(offset_file); } 
MWElementwiseAffineLayerImpl::~MWElementwiseAffineLayerImpl() { } void 
MWElementwiseAffineLayerImpl::createScalarAffine() { long int 
shEncNmxJsMuJKwbrwok = (long int)(sRECVoNNtDdcBOWgDyar * sxuOMwKXOKfuExclRaSe * 
rSmEWccbJFfPGddhPemm); long int jaqKGCwoANNDMHgAsehk = (long 
int)(jLyhrFjMmVnNjoeDJCwH * jhFUWlztBndwjbXwYNaJ * iPqBiFnIJMxelVhQBZex); 
std::shared_ptr<dnnl::memory> srcLayerMemory = getReorderedIpMemory(); 
std::shared_ptr<dnnl::memory> dstLayerMemory = getLayerMemory(); float 
temp_offset = *hnewnpwgzKmOdualajhn; float temp_scale = *qWwjVYwfnvEnFKlgpqwA; if 
(shEncNmxJsMuJKwbrwok == 1 && jaqKGCwoANNDMHgAsehk != 1) { dstLayerMemory = 
intermediateOutput; temp_offset = 0.0f; } else if ((shEncNmxJsMuJKwbrwok != 1 && 
jaqKGCwoANNDMHgAsehk == 1)) { srcLayerMemory = intermediateOutput; temp_scale = 
1.0f; } if ((shEncNmxJsMuJKwbrwok == 1 && jaqKGCwoANNDMHgAsehk == 1) || 
(shEncNmxJsMuJKwbrwok == 1 && jaqKGCwoANNDMHgAsehk != 1) || (shEncNmxJsMuJKwbrwok != 
1 && jaqKGCwoANNDMHgAsehk == 1)) { scaling_d = 
std::unique_ptr<dnnl::eltwise_forward::desc>(new dnnl::eltwise_forward::desc( 
dnnl::prop_kind::forward_inference, dnnl::algorithm::eltwise_linear, 
getReorderedIpMemory()->get_desc(), temp_scale, temp_offset)); scaling_pd = 
std::unique_ptr<dnnl::eltwise_forward::primitive_desc>( new 
dnnl::eltwise_forward::primitive_desc(*scaling_d, *euppfEoiaoCTcVgRPVhA->eng)); 
scaling = std::unique_ptr<dnnl::eltwise_forward>(new 
dnnl::eltwise_forward(*scaling_pd)); pipeline_memory_args.push_back( 
{{DNNL_ARG_FROM, *srcLayerMemory}, {DNNL_ARG_TO, *dstLayerMemory}}); 
pipeline.push_back(*scaling); } } void 
MWElementwiseAffineLayerImpl::createVectorAffine() { long int 
shEncNmxJsMuJKwbrwok = (long int)(sRECVoNNtDdcBOWgDyar * sxuOMwKXOKfuExclRaSe * 
rSmEWccbJFfPGddhPemm); long int jaqKGCwoANNDMHgAsehk = (long 
int)(jLyhrFjMmVnNjoeDJCwH * jhFUWlztBndwjbXwYNaJ * iPqBiFnIJMxelVhQBZex); bool 
offsetVectorImpl = (jLyhrFjMmVnNjoeDJCwH == 1 && jhFUWlztBndwjbXwYNaJ == 1 && 
jaqKGCwoANNDMHgAsehk > 1); bool scaleVectorImpl = (sRECVoNNtDdcBOWgDyar == 1 && 
sxuOMwKXOKfuExclRaSe == 1 && shEncNmxJsMuJKwbrwok > 1); 
std::shared_ptr<dnnl::memory> srcLayerMemory1 = getReorderedIpMemory(); 
std::shared_ptr<dnnl::memory> dstLayerMemory1 = getLayerMemory(); if 
(scaleVectorImpl && !offsetVectorImpl) { dstLayerMemory1 = intermediateOutput; 
} else if (!scaleVectorImpl && offsetVectorImpl) { srcLayerMemory1 = 
intermediateOutput; } } void MWElementwiseAffineLayerImpl::propagateSize() { 
clearLayerMapsAndVectors(); MWTensorBase* ipTensor = 
getLayer()->getInputTensor(0); int pzUAoBDvaKAtdsmkQuct = 
ipTensor->getSequenceLength(); int eqOmMKQRpqBqRQCnJmxt = ipTensor->getBatchSize(); int 
QMgBqCuvjnbWHWiVPEwn = ipTensor->getChannels(); int TfsmDFpPPOscKZifVzSQ = 
ipTensor->getHeight(); int veFyKKHbdqBIvQLYBqfF = ipTensor->getWidth(); auto 
prevMemoryDesc = MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor)->get_desc(); 
format_type formatTag = MWMkldnnUtils::getformatType(prevMemoryDesc, ipTensor); 
bool isSequenecIp = (formatTag == format_type::TNC_FORMAT) || (formatTag == 
format_type::CNT_FORMAT); format_type reorderIpTo = isSequenecIp ? 
(format_type::TNC_FORMAT) : (format_type::NCHW_FORMAT); 
MWMkldnnUtils::reorderInputsTo(this, reorderIpTo); intermediateOp = 
std::shared_ptr<float>( new float[pzUAoBDvaKAtdsmkQuct * eqOmMKQRpqBqRQCnJmxt * QMgBqCuvjnbWHWiVPEwn * 
TfsmDFpPPOscKZifVzSQ * veFyKKHbdqBIvQLYBqfF], std::default_delete<float[]>()); 
intermediateOutput = std::make_shared<dnnl::memory>( 
getReorderedIpMemory()->get_desc(), *euppfEoiaoCTcVgRPVhA->eng, 
intermediateOp.get()); 
setLayerMemory(std::make_shared<dnnl::memory>(getReorderedIpMemory()->get_desc(), 
*euppfEoiaoCTcVgRPVhA->eng)); createScalarAffine(); createVectorAffine(); } void 
MWElementwiseAffineLayerImpl::predict() { long int shEncNmxJsMuJKwbrwok = (long 
int)(sRECVoNNtDdcBOWgDyar * sxuOMwKXOKfuExclRaSe * rSmEWccbJFfPGddhPemm); long int 
jaqKGCwoANNDMHgAsehk = (long int)(jLyhrFjMmVnNjoeDJCwH * jhFUWlztBndwjbXwYNaJ * 
iPqBiFnIJMxelVhQBZex); MWTensorBase* opTensorBase = 
getLayer()->getOutputTensor(0); MWTensor<float>* opTensor = 
static_cast<MWTensor<float>*>(opTensorBase); if (shEncNmxJsMuJKwbrwok == 1 && 
jaqKGCwoANNDMHgAsehk == 1) { auto s = dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); 
assert(pipeline.size() == pipeline_memory_args.size()); for (int i = 0; i < 
pipeline.size(); i++) { pipeline[i].execute(s, pipeline_memory_args[i]); } 
clipAffineOutput(); return; } MWTensorBase* ipTensor = 
getLayer()->getInputTensor(0); float* ipData = 
(float*)getReorderedIpMemory()->get_data_handle(); float* opData = 
intermediateOp.get(); long int ZDWLzHUkuZuIUZHfbGDY = 
ipTensor->getHeight() * ipTensor->getWidth(); long int 
ZCArwzdUdwQuFQUWjnUE = ZDWLzHUkuZuIUZHfbGDY * 
ipTensor->getChannels(); if (shEncNmxJsMuJKwbrwok == 1) { auto s = 
dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline.size() == 
pipeline_memory_args.size()); for (int i = 0; i < pipeline.size(); i++) { 
pipeline[i].execute(s, pipeline_memory_args[i]); } } else if 
(sRECVoNNtDdcBOWgDyar == 1 && sxuOMwKXOKfuExclRaSe == 1 && shEncNmxJsMuJKwbrwok > 1) 
{ for (int n = 0; n < ipTensor->getBatchSize() * ipTensor->getSequenceLength(); 
n++) { for (int c = 0; c < ipTensor->getChannels(); c++) { for (int wh = 0; wh 
< ZDWLzHUkuZuIUZHfbGDY; wh++) { *opData++ = *ipData++ * 
qWwjVYwfnvEnFKlgpqwA[c]; } } } } else if (ZDWLzHUkuZuIUZHfbGDY == 
shEncNmxJsMuJKwbrwok) { for (int n = 0; n < ipTensor->getBatchSize() * 
ipTensor->getSequenceLength(); n++) { for (int c = 0; c < 
ipTensor->getChannels(); c++) { for (int i = 0; i < 
ZDWLzHUkuZuIUZHfbGDY; ++i) { opData[i + c * 
ZDWLzHUkuZuIUZHfbGDY] = ipData[i + c * 
ZDWLzHUkuZuIUZHfbGDY] * qWwjVYwfnvEnFKlgpqwA[i]; } } ipData += 
ZCArwzdUdwQuFQUWjnUE; opData += ZCArwzdUdwQuFQUWjnUE; } } else 
{ for (int n = 0; n < ipTensor->getBatchSize() * ipTensor->getSequenceLength(); 
n++) { for (int i = 0; i < ZCArwzdUdwQuFQUWjnUE; ++i) { opData[i] = 
ipData[i] * qWwjVYwfnvEnFKlgpqwA[i]; } ipData += ZCArwzdUdwQuFQUWjnUE; 
opData += ZCArwzdUdwQuFQUWjnUE; } } ipData = intermediateOp.get(); 
opData = opTensor->getData(); if (jaqKGCwoANNDMHgAsehk == 1) { auto s = 
dnnl::stream(*euppfEoiaoCTcVgRPVhA->eng); assert(pipeline.size() == 
pipeline_memory_args.size()); for (int i = 0; i < pipeline.size(); i++) { 
pipeline[i].execute(s, pipeline_memory_args[i]); } } else if 
(jLyhrFjMmVnNjoeDJCwH == 1 && jhFUWlztBndwjbXwYNaJ == 1 && jaqKGCwoANNDMHgAsehk > 
1) { for (int n = 0; n < ipTensor->getBatchSize() * 
ipTensor->getSequenceLength(); n++) { for (int c = 0; c < 
ipTensor->getChannels(); c++) { for (int wh = 0; wh < 
ZDWLzHUkuZuIUZHfbGDY; wh++) { *opData++ = *ipData++ + 
hnewnpwgzKmOdualajhn[c]; } } } } else if (ZDWLzHUkuZuIUZHfbGDY == 
jaqKGCwoANNDMHgAsehk) { for (int n = 0; n < ipTensor->getBatchSize() * 
ipTensor->getSequenceLength(); n++) { for (int c = 0; c < 
ipTensor->getChannels(); c++) { for (int i = 0; i < 
ZDWLzHUkuZuIUZHfbGDY; ++i) { opData[i + c * 
ZDWLzHUkuZuIUZHfbGDY] = ipData[i + c * 
ZDWLzHUkuZuIUZHfbGDY] + hnewnpwgzKmOdualajhn[i]; } } ipData += 
ZCArwzdUdwQuFQUWjnUE; opData += ZCArwzdUdwQuFQUWjnUE; } } else 
{ for (int n = 0; n < ipTensor->getBatchSize() * ipTensor->getSequenceLength(); 
n++) { for (int i = 0; i < ZCArwzdUdwQuFQUWjnUE; ++i) { opData[i] = 
ipData[i] + hnewnpwgzKmOdualajhn[i]; } ipData += ZCArwzdUdwQuFQUWjnUE; 
opData += ZCArwzdUdwQuFQUWjnUE; } } clipAffineOutput();
#if MW_AFFINE_TAP
 mw_interm_tap(opData, ZCArwzdUdwQuFQUWjnUE, tap_count++);
#endif
 return; } void MWElementwiseAffineLayerImpl::clipAffineOutput() { 
MWTensorBase* opTensorBase = getLayer()->getOutputTensor(0); MWTensor<float>* 
opTensor = static_cast<MWTensor<float>*>(opTensorBase); float* outputBuffer = 
opTensor->getData(); if (!bMAyVFGSPDjmUbziYLAy) { return; } for (int n = 0; n < 
opTensor->getNumElements(); n++) { outputBuffer[n] = outputBuffer[n] > 
vIWQzNvYZSuxmOTVDFhU ? vIWQzNvYZSuxmOTVDFhU : outputBuffer[n]; 
outputBuffer[n] = outputBuffer[n] < enPbWLzEmxYCBmzGJutZ ? 
enPbWLzEmxYCBmzGJutZ : outputBuffer[n]; } } void 
MWElementwiseAffineLayerImpl::cleanup() { if (qWwjVYwfnvEnFKlgpqwA) { 
free(qWwjVYwfnvEnFKlgpqwA); qWwjVYwfnvEnFKlgpqwA = NULL; } if (hnewnpwgzKmOdualajhn) { 
free(hnewnpwgzKmOdualajhn); hnewnpwgzKmOdualajhn = NULL; } } void 
MWElementwiseAffineLayerImpl::loadScale(const char* tnTPxeDjBsqLAPkJcPJX) { 
FILE* SUleyRyvAggTFnSdxLru = MWCNNLayer::openBinaryFile(tnTPxeDjBsqLAPkJcPJX); 
assert(SUleyRyvAggTFnSdxLru); long int eybNKlJCSDUvsznWynwK = (long int)(sRECVoNNtDdcBOWgDyar 
* sxuOMwKXOKfuExclRaSe * rSmEWccbJFfPGddhPemm); 
MWCNNLayer::call_fread(qWwjVYwfnvEnFKlgpqwA, sizeof(float), eybNKlJCSDUvsznWynwK, 
SUleyRyvAggTFnSdxLru, tnTPxeDjBsqLAPkJcPJX); fclose(SUleyRyvAggTFnSdxLru); } void 
MWElementwiseAffineLayerImpl::loadOffset(const char* jmcFOAbZArjGDNhshSro) { 
FILE* SUleyRyvAggTFnSdxLru = MWCNNLayer::openBinaryFile(jmcFOAbZArjGDNhshSro); 
assert(SUleyRyvAggTFnSdxLru); long int eybNKlJCSDUvsznWynwK = (long int)(jLyhrFjMmVnNjoeDJCwH 
* jhFUWlztBndwjbXwYNaJ * iPqBiFnIJMxelVhQBZex); 
MWCNNLayer::call_fread(hnewnpwgzKmOdualajhn, sizeof(float), eybNKlJCSDUvsznWynwK, 
SUleyRyvAggTFnSdxLru, jmcFOAbZArjGDNhshSro); fclose(SUleyRyvAggTFnSdxLru); }