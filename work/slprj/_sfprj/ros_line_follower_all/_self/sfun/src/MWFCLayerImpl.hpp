/* Copyright 2020 The MathWorks, Inc. */

#ifndef __FC_LAYER_IMPL_HPP
#define __FC_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"
#include "dnnl.hpp"
#include <memory>

class MWCNNLayer;
class MWTargetNetworkImpl;

// FullyConnectedLayer
class MWFCLayerImpl : public MWCNNLayerImpl {

  public:
    MWFCLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, const char*, const char*);
    ~MWFCLayerImpl();

    void predict();
    void propagateSize();
    void cleanup();

  private:
    void loadWeights(const char*, int);
    void loadBias(const char*, int);
    void prepareWeights();

    float* veFyKKHbdqBIvQLYBqfF;
    float* NMMfJylfQjiIUAKhXCJb;

    std::shared_ptr<dnnl::memory::desc> weights_md;
    std::shared_ptr<dnnl::memory::desc> bias_md;

    std::shared_ptr<dnnl::memory> weights;
    std::shared_ptr<dnnl::memory> bias;

    std::shared_ptr<dnnl::memory> fc_src_memory;
    std::shared_ptr<dnnl::memory> fc_weights_memory;

    std::unique_ptr<dnnl::reorder> fc_reorder_src;
    std::unique_ptr<dnnl::reorder> fc_reorder_weights;

    std::unique_ptr<dnnl::inner_product_forward::desc> ip_d;
    std::unique_ptr<dnnl::inner_product_forward::primitive_desc> ip_pd;
    std::unique_ptr<dnnl::inner_product_forward::primitive> ip;
};

#endif
