/* Copyright 2018 The MathWorks, Inc. */

#ifndef _MW_CONV_LAYER_API_IMPL
#define _MW_CONV_LAYER_API_IMPL

#include "MWCNNLayerImpl.hpp"
#include "dnnl.hpp"
#include <vector>
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// Convolution2DWCNNLayer
class MWConvLayerImpl : public MWCNNLayerImpl
{   
  private:   

    float* veFyKKHbdqBIvQLYBqfF;
    float* NMMfJylfQjiIUAKhXCJb;   
    int AwZQzUhuWVLGrWgLHRuM;           // Filter height for CONV and FC
    int AzTsxYcYjIEJsGQbeYHm;            // Filter width for CONV and FC
    int CGbFsczkgkhjcHoCKzBx;
    int AIXLuRgdeiqpaCehGSYD;
    int ATEikvMQPqBefhJzjzhc;
    int DSsxcjIrUgZCKZovyNQf;
    int CpMjJjtGOeWOzwxpAAQP;
    int FeVcBgtQmTLtmnNcJGMY;
    int FrpxvsDMwwgbpqHXWxmN;
    int HtQBsWTCGEkpylRklilw;
    int IAlDgIFcchbwRGBSfVfA;
    bool with_bias = true;
		
public:
    MWConvLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, int, int, int,  int, int, int, int, int, int, int, int, const char*, const char*);
    ~MWConvLayerImpl();

    void predict();
    void propagateSize();
    void cleanup();
    
  private:
    void loadWeights(const char*, int);
    void loadBias(const char*, int);

    //ConvLayer related config params
    std::shared_ptr<dnnl::memory> weights;
    std::shared_ptr<dnnl::memory> bias;

    dnnl::memory::desc reorderedWeightsDesc;	
    
    std::unique_ptr<dnnl::memory::desc> conv_src_md;
    std::unique_ptr<dnnl::memory::desc> conv_weights_md;
    std::unique_ptr<dnnl::memory::desc> conv_bias_md;
    std::unique_ptr<dnnl::memory::desc> conv_dst_md;
    
    /*reorder related settings*/
    std::shared_ptr<dnnl::memory> conv_src_memory;
    std::shared_ptr<dnnl::memory> conv_weights_memory;
    
    std::unique_ptr<dnnl::reorder> conv_reorder_src;
    std::unique_ptr<dnnl::reorder> conv_reorder_weights;
    
    std::unique_ptr<dnnl::convolution_forward::desc> conv_d;
    std::unique_ptr<dnnl::convolution_forward::primitive_desc> conv_pd;
    std::unique_ptr<dnnl::convolution_forward::primitive> conv;
    
};
    
#endif
