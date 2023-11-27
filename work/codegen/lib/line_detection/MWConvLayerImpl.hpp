/* Copyright 2018 The MathWorks, Inc. */

#ifndef _MW_CUDNN_CONV_LAYER_IMPL_
#define _MW_CUDNN_CONV_LAYER_IMPL_

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

/**
 * Codegen class for Convolution layer implementation
 */
class MWConvLayerImpl : public MWCNNLayerImpl
{   
  private:
    
    int BHuHNDGoRwGRouCxeMbw;          
    int BLjrjqvCcCommiXWQLjs;          

    int BuyZFXzwOMxcePIbCLfl;
    int BkwhtPQUCQKchmmimoXs;
    int BlRIQPyqJZORKENzSdYf;

    int AdmgfUbRAfzFeYHxSnQr;
    int AwZQzUhuWVLGrWgLHRuM;

    int CTCbzQMDaLxINPbODdng;
    int CLOUhPjbgggWoXHTtmjC;
    int CpMjJjtGOeWOzwxpAAQP;
    int CqtPRJvHlGJFssiPzsOm;

    int FrpxvsDMwwgbpqHXWxmN;
    int FwLnexHgxHRquTKmNpoa;  

    float* vpXxoeEhdEosLSsYXkNG;
    float* JCaothdxtQBQxaaitLio;

    // for temporary pre-padded input for asymmetric padding
    MWTensorBase* TfsmDFpPPOscKZifVzSQ;
    int bYBVtTnVUuGDUlaTmmHp;
    int cQBKlCKXxecGPJrXBXdk;

    bool IbSWJNMuIiKbocfQKqXb;

  public:
    
    MWConvLayerImpl(MWCNNLayer* layer,
                    MWTargetNetworkImpl* ntwk_impl,
                    int filt_H,
                    int filt_W,
                    int numGrps,
                    int numChannels,
                    int numFilts,
                    int FrpxvsDMwwgbpqHXWxmN,
                    int FwLnexHgxHRquTKmNpoa,
                    int CTCbzQMDaLxINPbODdng,
                    int CLOUhPjbgggWoXHTtmjC,
                    int CpMjJjtGOeWOzwxpAAQP,
                    int CqtPRJvHlGJFssiPzsOm,
                    int AdmgfUbRAfzFeYHxSnQr,
                    int AwZQzUhuWVLGrWgLHRuM,
                    const char* xHViLEwTujGGrPZZgmbF,
                    const char* KCudOrFMfgCzUPMcdePX);
    
    ~MWConvLayerImpl(){}

    void predict();
    void cleanup();
    void postSetup();
    void propagateSize();
    void allocate();
    void deallocate();
    
  private:
    
    void loadWeights(const char*);
    void loadBias(const char*);
    void getConvAlgoTuned();
    void getConvAlgoWorkSpaceLimit();
		
  private:
    
    cudnnConvolutionDescriptor_t  NZjOkZPwLzQsdEVkwMcX;
    cudnnConvolutionFwdAlgo_t     NNhshzQGJHLSGjDiVerE;

    cudnnFilterDescriptor_t       QhTesEEIHwhNmHSeYbRR;
    cudnnTensorDescriptor_t       JwxFdqOKggeawILBfGgg;

    cudnnTensorDescriptor_t       YCSvyQZBWMDYQXHtyVai;

};

#endif
