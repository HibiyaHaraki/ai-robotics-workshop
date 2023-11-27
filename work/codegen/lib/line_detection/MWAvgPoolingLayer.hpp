/* Copyright 2020 The MathWorks, Inc. */

#ifndef __AVG_POOLING_LAYER_HPP
#define __AVG_POOLING_LAYER_HPP

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

// AvgPooling2DLayer
class MWAvgPoolingLayer : public MWCNNLayer {
  public:
    MWAvgPoolingLayer()
        : isGlobalAveragePooling(false) {
    }
    ~MWAvgPoolingLayer() {
    }

    template <typename T1, typename T2>
    void createAvgPoolingLayer(MWTargetNetworkImpl*,
                               MWTensorBase*,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               int,
                               const char*,
                               int,
                               int);
    void propagateSize();

    int strideH;
    int strideW;

    int poolH;
    int poolW;

    int paddingH_T;
    int paddingH_B;
    int paddingW_L;
    int paddingW_R;

    bool isGlobalAveragePooling;
    const char* accelerationMode;    
};

#endif
