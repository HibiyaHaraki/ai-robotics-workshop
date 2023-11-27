/* Copyright 2020 The MathWorks, Inc. */

#ifndef __MAX_POOLING_LAYER_IMPL_HPP
#define __MAX_POOLING_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

//MaxPooling2DLayer
class MWMaxPoolingLayerImpl: public MWCNNLayerImpl
{
public:
    //Create MaxPooling2DLayer with PoolSize = [ PoolH PoolW ]
    //                                Stride = [ StrideH StrideW ]
    //                               Padding = [ PaddingH_T PaddingH_B PaddingW_L PaddingW_R ]
    MWMaxPoolingLayerImpl(MWCNNLayer *, MWTargetNetworkImpl*, int, int, int, int, int, int, int, int, bool, int, const char*, int);
    ~MWMaxPoolingLayerImpl();

    void predict();
    void cleanup();
    void propagateSize();
    void allocate();
    void deallocate();
    float* getIndexData();
    
public:
    int DRzwhbNPpftRRIXXfHzd;
    int EfvWctmlsWAPsxXgdKWf;
    int DGzdAcREJHGXjyRzNjJV;
    int ECTnqgWHyHCHCLBZlffd;

    int CTCbzQMDaLxINPbODdng;
    int CLOUhPjbgggWoXHTtmjC;
    int CpMjJjtGOeWOzwxpAAQP;
    int CqtPRJvHlGJFssiPzsOm;

    int FrpxvsDMwwgbpqHXWxmN;
    int FwLnexHgxHRquTKmNpoa;

    bool BRSPqxNffoBYKqpSVHne;
    
private:
    float* UpnEytIWGokwbTFkBcSx;
    float* PfisSEEWDaQFynnzlcin;
    int fXhhiexIRPLyKXApPmmy;
    cudnnPoolingDescriptor_t mtolGPkUMBYDlSSqrRzc;
    float pFoPPXxxFRbjXXxQWItv;
    bool vjDFlBZzKvbpPseAtMBP;
    cudnnTensorDescriptor_t DqxLTLaJwwgQqmrtCDuu;
};

#endif
