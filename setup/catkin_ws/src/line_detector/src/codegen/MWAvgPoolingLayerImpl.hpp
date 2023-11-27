/* Copyright 2020 The MathWorks, Inc. */

#ifndef __AVG_POOLING_LAYER_IMPL_HPP
#define __AVG_POOLING_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

//AvgPooling2DLayer
class MWAvgPoolingLayerImpl : public MWCNNLayerImpl
{
public:
    //Create AvgPooling2DLayer with PoolSize = [ PoolH PoolW ]
    //                                Stride = [ StrideH StrideW ]
    //                               Padding = [ PaddingH_T PaddingH_B PaddingW_L PaddingW_R ]
    MWAvgPoolingLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, int, int, int, int, int, int, int, const char*);
    ~MWAvgPoolingLayerImpl();

    void predict();
    void cleanup();
    void propagateSize();
    void allocate();
    void deallocate();

  public:
    int DRzwhbNPpftRRIXXfHzd;
    int EfvWctmlsWAPsxXgdKWf;
    int DGzdAcREJHGXjyRzNjJV;
    int ECTnqgWHyHCHCLBZlffd; 
    int FrpxvsDMwwgbpqHXWxmN; 
    int FwLnexHgxHRquTKmNpoa; 
    int CTCbzQMDaLxINPbODdng; 
    int CLOUhPjbgggWoXHTtmjC;
    int CpMjJjtGOeWOzwxpAAQP;
    int CqtPRJvHlGJFssiPzsOm;
    
private:
    cudnnPoolingDescriptor_t      mtolGPkUMBYDlSSqrRzc;
    int muwRQxtWMMXAPxSuMYBw;
    int nDsbARncmIrIaLubvLVZ;
    
    cudnnTensorDescriptor_t       YCSvyQZBWMDYQXHtyVai;
    // for temporary pre-padded input for asymmetric padding
    MWTensorBase* TfsmDFpPPOscKZifVzSQ; 
    int cCXqPFPPcoHzYMDpnUxQ;
    int cAUupmktEnGPfLHyWfFm;
    bool IbSWJNMuIiKbocfQKqXb;
    float pFoPPXxxFRbjXXxQWItv;
    bool vjDFlBZzKvbpPseAtMBP;
    cudnnTensorDescriptor_t JABfZsGuaCAmcRcqOYEO;
};

#endif
