/* Copyright 2018 The MathWorks, Inc. */

#ifndef _MW_CONV_LAYER_
#define _MW_CONV_LAYER_

#include "MWCNNLayer.hpp"

class MWTargetNetworkImpl;
class MWTensorBase;

/**
 * Codegen class for Convolution layer
 */

class MWConvLayer: public MWCNNLayer
{
  public :
    
    MWConvLayer(){}
    ~MWConvLayer(){}
    void createConvLayer(MWTargetNetworkImpl* ntwk_impl,
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
                         int,
                         int,
                         int,
                         int,
                         const char*,
                         const char*,
                         int);
    void propagateSize();

  private:
    int strideH;
    int strideW;
    
    int filterH;
    int filterW;

    int dilationFactorH;
    int dilationFactorW;

    int paddingH_T;
    int paddingH_B;
    int paddingW_L;
    int paddingW_R;

    int numFilters;
    int numGroups;
};

#endif
