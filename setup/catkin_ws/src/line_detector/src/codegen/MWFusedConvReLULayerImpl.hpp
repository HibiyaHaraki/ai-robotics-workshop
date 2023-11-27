/* Copyright 2018 The MathWorks, Inc. */

#ifndef __FUSED_CONV_RELU_LAYER_IMPL_HPP
#define __FUSED_CONV_RELU_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

class MWFusedConvReLULayerImpl: public MWCNNLayerImpl
{

private:
    int BHuHNDGoRwGRouCxeMbw;           //Filter height for CONV and FC
    int BLjrjqvCcCommiXWQLjs;            //Filter width for CONV and FC

    int BuyZFXzwOMxcePIbCLfl;
    int BkwhtPQUCQKchmmimoXs;
    int BlRIQPyqJZORKENzSdYf;

    int FrpxvsDMwwgbpqHXWxmN;
    int FwLnexHgxHRquTKmNpoa;
    int CTCbzQMDaLxINPbODdng;
    int CLOUhPjbgggWoXHTtmjC;
    int CpMjJjtGOeWOzwxpAAQP;
    int CqtPRJvHlGJFssiPzsOm;
    int AdmgfUbRAfzFeYHxSnQr;
    int AwZQzUhuWVLGrWgLHRuM;

    int fxxCPKTclxXPxrdMAkwi;

    float* vpXxoeEhdEosLSsYXkNG;
    float* JCaothdxtQBQxaaitLio;
    MWTensorBase* URgvgDXnZskIYGdtimcU; // for pre-padded input
    int bYBVtTnVUuGDUlaTmmHp;
    int cQBKlCKXxecGPJrXBXdk;

    float* XCnEVUzxqcNgsuUbRonz;

    float* HoqiuUUuJnXGkfDodicJ; // Scaling factor for addition

    bool IbSWJNMuIiKbocfQKqXb;

    // Temporary buffer for Xinput, CuDNN 8 upgrade
    float* GFienSVKLlDQuZeqAdLC;    
    
public:
    MWFusedConvReLULayerImpl(MWCNNLayer*, MWTargetNetworkImpl*,
                             int, int,
                             int, int, int,
                             int, int,
                             int, int, int, int,
                             int, int,
                             int,
                             const char*, const char*);
    ~MWFusedConvReLULayerImpl();

    void predict();
    void cleanup();
    void propagateSize();
    void allocate();
    void deallocate();
    void postSetup();

private:
    void loadWeights(const char*);
    void loadBias(const char*);
    void getConvAlgoTuned();
    void getConvAlgoWorkSpaceLimit();
    void fixConvAlgo(); // g1916490

    void setalpha2Ptr(float* alpha2){ HoqiuUUuJnXGkfDodicJ = alpha2;}
    float* getalpha2Ptr() {return HoqiuUUuJnXGkfDodicJ;}


private:
    cudnnConvolutionDescriptor_t  NZjOkZPwLzQsdEVkwMcX;
    cudnnConvolutionFwdAlgo_t     NNhshzQGJHLSGjDiVerE;

    cudnnFilterDescriptor_t       QhTesEEIHwhNmHSeYbRR;
    cudnnTensorDescriptor_t       JwxFdqOKggeawILBfGgg;

    cudnnTensorDescriptor_t      YCSvyQZBWMDYQXHtyVai;

    cudnnActivationDescriptor_t   oJUVMnJggjhEdQLWzIUC;

};

#endif
