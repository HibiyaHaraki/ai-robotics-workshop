/* Copyright 2020 The MathWorks, Inc. */

#ifndef __AVG_POOLING_LAYER_IMPL_HPP
#define __AVG_POOLING_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"
#include "dnnl.hpp"
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// AvgPooling2DLayer
class MWAvgPoolingLayerImpl : public MWCNNLayerImpl {
  public:
    MWAvgPoolingLayerImpl(MWCNNLayer*,
                          MWTargetNetworkImpl*,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          const char*);
    ~MWAvgPoolingLayerImpl();

    void predict();
    void propagateSize();

  private:
    int FwLnexHgxHRquTKmNpoa;
    int HJHXkKmgFxxIOsIvRRnF;
    int HtQBsWTCGEkpylRklilw;
    int IAlDgIFcchbwRGBSfVfA;
    int DSsxcjIrUgZCKZovyNQf;
    int CpMjJjtGOeWOzwxpAAQP;
    int FeVcBgtQmTLtmnNcJGMY;
    int FrpxvsDMwwgbpqHXWxmN;
    
    /*mkldnn primitives to handle the reorder for optimization purpose*/
    std::unique_ptr<dnnl::pooling_forward::desc> pool_d;
    std::unique_ptr<dnnl::pooling_forward::primitive_desc> pool_pd;
    std::unique_ptr<dnnl::pooling_forward::primitive> pool;
};

#endif
