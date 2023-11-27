/* Copyright 2020 The MathWorks, Inc. */

#ifndef __FC_LAYER_IMPL_HPP
#define __FC_LAYER_IMPL_HPP

#include "MWCNNLayerImpl.hpp"

class MWCNNLayer;
class MWTargetNetworkImpl;

//FullyConnectedLayer
class MWFCLayerImpl: public MWCNNLayerImpl
{
public:
    int CDJtexcMbXMWAmnNZsNf;
private:
    int BHuHNDGoRwGRouCxeMbw;
    int BLjrjqvCcCommiXWQLjs;
    int CCKWXUFWgrbBMjwfpOBN;
    float* vpXxoeEhdEosLSsYXkNG;
    float* wJyXsrUCMgxdIKVIJSyx;
    float* JCaothdxtQBQxaaitLio;

    int xHiBGayUfxIpXKkCTDNU;

public:
    MWFCLayerImpl(MWCNNLayer*, MWTargetNetworkImpl*, int, int, const char*, const char*);
    ~MWFCLayerImpl();

    void predict();
    void cleanup();
    void propagateSize();
    void postSetup();

private:
    
    void loadWeights(const char*);
    void loadBias(const char*);
    void prepareWeights();

private:
    cudnnTensorDescriptor_t       JwxFdqOKggeawILBfGgg;
};

#endif
