/* Copyright 2019-2020 The MathWorks, Inc. */

// Target Specific (MKLDNN) header for Custom Layer Base Class
#ifndef CUSTOM_LAYER_MKLDNN_HPP
#define CUSTOM_LAYER_MKLDNN_HPP

#include "MWCNNLayer.hpp"
#include <map>
#include "dnnl.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

class MWCustomLayerForMKLDNN : public MWCNNLayer {

  public:
    MWCustomLayerForMKLDNN();
    ~MWCustomLayerForMKLDNN();

    std::shared_ptr<dnnl::memory> getCustomLayerMemory(MWTensorBase* aTensor);
    int getMaxBufSize();
    void allocate();
    void deallocate();
    void cleanup();

  private:
    std::map<MWTensorBase*, std::shared_ptr<dnnl::memory>> m_customLayerMemory;
    void setCustomLayerMemory(MWTensorBase* aTensor, std::shared_ptr<dnnl::memory> aLayerMemory);
    int maxBufSize = -1;

  protected:
    MWTargetNetworkImpl* m_ntwkImpl;

    void setupLayer(MWTargetNetworkImpl*);
    void createLayerMemory(MWTensorBase* aTensor,
                           MWTensorBase::DIMSLABEL implLayout[]);
    void setCustomLayerMemoryData(MWTensorBase* aTensor);
    void layerMemoryReorder(MWTensorBase* srcTensor, int bufIndex);

    virtual void cleanupLayer(){};
};

#endif
