/* Copyright 2017-2020 The MathWorks, Inc. */

#ifndef CNN_NTWK_IMPL
#define CNN_NTWK_IMPL

#include "dnnl.hpp"
#include <vector>

class MWCNNLayer;
class MWTensorBase;

#define MW_TARGET_TYPE_MKLDNN 1

class MWTargetNetworkImpl {
  public:
    MWTargetNetworkImpl()
        : numBufs(0) {
    }
    ~MWTargetNetworkImpl() {
    }
    void allocate(int numBufsToAlloc, MWCNNLayer* layers[], int numLayers, int numPermuteBufs);
    void deallocate();
    void preSetup();
    void postSetup() {
    }
    void cleanup();

    std::vector<float*> memBuffer;
    float* getLayerOutput(MWCNNLayer* layers[], int layerIndex, int portIndex);
    float* getLayerActivation(MWTensorBase*);
    int numBufs;

    std::unique_ptr<dnnl::engine> eng;
    float* getBufferPtr(int bufferIndex);

    void setReorderLayerMemory(std::shared_ptr<dnnl::memory> other);
    void setReorderPrim(std::shared_ptr<dnnl::reorder> other);
    std::shared_ptr<dnnl::memory> getReorderLayerMemory();
    std::shared_ptr<dnnl::reorder> getReorderPrim();

    float* getPermuteBuffer(int index); // used for input reordering for custom layers

    bool isAVX512;

  private:
    std::shared_ptr<dnnl::memory> reorderLayerMemory;
    std::shared_ptr<dnnl::reorder> reorderPrim; // to handle the reorder
    std::vector<float*> olKGEIcsxmLSoMhRhEtP;
};
#endif
