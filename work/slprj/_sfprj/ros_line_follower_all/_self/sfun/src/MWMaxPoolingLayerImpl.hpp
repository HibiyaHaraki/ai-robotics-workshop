/* Copyright 2020 The MathWorks, Inc. */

#ifndef __MAX_POOLING_LAYER_IMPL_HPP
#define __MAX_POOLING_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"
#include "dnnl.hpp"
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

class MWMaxPoolingLayerImpl : public MWCNNLayerImpl {
  public:
    // Create MaxPooling2DLayer with PoolSize = [ PoolH PoolW ]
    //                                Stride = [ StrideH StrideW ]
    //                               Padding = [ PaddingH_T PaddingH_B PaddingW_L PaddingW_R ]
    MWMaxPoolingLayerImpl(MWCNNLayer*,
                          MWTargetNetworkImpl*,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          bool,
                          int,
                          const char*,
                          int);
    ~MWMaxPoolingLayerImpl();


  public:
    void predict();
    float* getIndexData();
    void propagateSize();

    std::shared_ptr<dnnl::pooling_forward::primitive_desc> getPoolPrimitiveDesc();

    dnnl::memory::dims getPoolKernel();
    dnnl::memory::dims getPoolStrides();
    dnnl::memory::dims getPoolPadTL();
    dnnl::memory::dims getPoolPadBR();


  private:
    /*mkldnn configurations*/

    float* WOJynDmqVUPWjAGVIuMQ; // indices output
    int fhikqqlnUKCjleVKDqiG;
    bool BLjrjqvCcCommiXWQLjs;

    int FwLnexHgxHRquTKmNpoa;
    int HJHXkKmgFxxIOsIvRRnF;
    int HtQBsWTCGEkpylRklilw;
    int IAlDgIFcchbwRGBSfVfA;
    int DSsxcjIrUgZCKZovyNQf;
    int CpMjJjtGOeWOzwxpAAQP;
    int FeVcBgtQmTLtmnNcJGMY;
    int FrpxvsDMwwgbpqHXWxmN;
    int fjfzkUfcCOqjrkAVGfuc;

    dnnl::memory::dims GFienSVKLlDQuZeqAdLC;
    dnnl::memory::dims GsZlHFuhbvjLtRMDjXnW;
    dnnl::memory::dims GnxRkpzrPZimKtYYHSuG;
    dnnl::memory::dims GeeOVBfQrpMacIFBLKOo;

    /*mkldnn primitives to handle the reorder for optimization purpose*/
    std::shared_ptr<dnnl::pooling_forward::desc> pool_d;
    std::shared_ptr<dnnl::pooling_forward::primitive_desc> pool_pd;
    std::shared_ptr<dnnl::pooling_forward::primitive> pool;
};

#endif
