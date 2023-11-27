/* Copyright 2017-2020 The MathWorks, Inc. */

#ifndef CNN_API_IMPL
#define CNN_API_IMPL

#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"

#include "dnnl.hpp"

#include <cstring>
#include <map>
#include <vector>
#include <unordered_map>
#include "dnnl.hpp"

class MWTargetNetworkImpl;

/*If MW_LAYERS_TAP is enabled, it will tap layer wise output */
#define MW_LAYERS_TAP 0

#if MW_LAYERS_TAP
extern int tap_count;
extern void mw_interm_tap(float* inp, int size, int count);


#define MW_INPUT_TAP 1
#define MW_CONV_TAP 1
#define MW_RELU_TAP 1
#define MW_NORM_TAP 1
#define MW_POOL_TAP 1
#define MW_UNPOOL_TAP 1
#define MW_FC_TAP 1
#define MW_SFMX_TAP 1
#define MW_ADDITION_TAP 1
#define MW_CONCAT_TAP 1
#define MW_TRANSPOSEDCONV_TAP 1
#define MW_SCALING_TAP 1
#define MW_CROP2D_TAP 1
#define MW_YOLOREORG_TAP 1
#define MW_YOLOEXTRACT_TAP 1
#define MW_SIGMOID_TAP 1
#define MW_EXP_TAP 1
#define MW_YOLOSFMAX_TAP 1
#define MW_FLATTEN_CSTYLE_TAP 1
#define MW_TANH_TAP 1
#define MW_ZEROPAD_TAP 1
#define MW_FLATTEN_TAP 1
#define MW_SPLIT_LAYER 1
#define MW_AFFINE_TAP 1
#define MW_SSDMERGE_TAP 1
#define MW_ELU_TAP 1
#define MW_LSTM_TAP 1
#define MW_SEQIP_TAP 1
#define MW_FLATTEN_TAP 1
#else
#define MW_INPUT_TAP 0
#define MW_CONV_TAP 0
#define MW_RELU_TAP 0
#define MW_NORM_TAP 0
#define MW_POOL_TAP 0
#define MW_UNPOOL_TAP 0
#define MW_FC_TAP 0
#define MW_SFMX_TAP 0
#define MW_ADDITION_TAP 0
#define MW_CONCAT_TAP 0
#define MW_TRANSPOSEDCONV_TAP 0
#define MW_SCALING_TAP 0
#define MW_CROP2D_TAP 0
#define MW_YOLOREORG_TAP 0
#define MW_YOLOEXTRACT_TAP 0
#define MW_SIGMOID_TAP 0
#define MW_EXP_TAP 0
#define MW_YOLOSFMAX_TAP 0
#define MW_FLATTEN_CSTYLE_TAP 0
#define MW_TANH_TAP 0
#define MW_ZEROPAD_TAP 0
#define MW_FLATTEN_TAP 0
#define MW_SPLIT_LAYER 0
#define MW_AFFINE_TAP 0
#define MW_SSDMERGE_TAP 0
#define MW_ELU_TAP 0
#define MW_LSTM_TAP 0
#define MW_SEQIP_TAP 0
#define MW_FLATTEN_TAP 0
#endif

class MWCNNLayerImpl {
  public:
    MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* ntwk_impl);
    virtual ~MWCNNLayerImpl() {
    }
    virtual void predict() {
    }
    virtual void cleanup() {
    }
    virtual void postSetup() {
    }
    virtual void propagateSize() = 0;
    virtual void allocate() {
    }
    virtual void deallocate() {
    }

    template <class T>
    void allocateOutputData(int);

    template <class T>
    void deallocateOutputData(int);

  public:
    MWCNNLayer* getLayer() {
        return cCXqPFPPcoHzYMDpnUxQ;
    }
    std::shared_ptr<dnnl::memory> getLayerMemory(int index = 0);
    void setLayerMemory(std::shared_ptr<dnnl::memory> other, int index = 0);

    std::shared_ptr<dnnl::memory> getReorderedIpMemory(int index = 0);

    std::shared_ptr<dnnl::reorder> getReorderPrim(int index = 0);

    MWTargetNetworkImpl* getTargetImpl() {
        return euppfEoiaoCTcVgRPVhA;
    }
    void setReorderLayerMemory(std::shared_ptr<dnnl::memory> other, int index = 0);
    void setReorderPrim(std::shared_ptr<dnnl::reorder> other, int index = 0);
    void reorderedLayerOutputTap(int);
    void clearLayerMapsAndVectors();

    std::vector<dnnl::primitive>& getPipeline() {
        return pipeline;
    }
    std::vector<std::unordered_map<int, dnnl::memory>>& getArgumentsPipeline() {
        return pipeline_memory_args;
    }

  protected:
    MWCNNLayer* cCXqPFPPcoHzYMDpnUxQ;
    MWTargetNetworkImpl* euppfEoiaoCTcVgRPVhA;

    /*mkldnn related config params*/
    std::map<int, std::shared_ptr<dnnl::memory>> layerMemory;
    std::map<int, std::shared_ptr<dnnl::memory>> reorderLayerMemory;
    std::map<int, std::shared_ptr<dnnl::reorder>> reorderPrim; // to handle the reorder

    std::vector<dnnl::primitive> pipeline;

    std::vector<std::unordered_map<int, dnnl::memory>> pipeline_memory_args;
    std::vector<std::unordered_map<int, dnnl::memory>> pipeline_weights_memory_args;
    std::vector<dnnl::primitive> pipeline_weights;
};

#endif
