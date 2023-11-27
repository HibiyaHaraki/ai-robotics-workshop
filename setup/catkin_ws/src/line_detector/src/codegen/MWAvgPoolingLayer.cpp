/* Copyright 2020 The MathWorks, Inc. */

#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"
#include "MWAvgPoolingLayer.hpp"
#include "MWAvgPoolingLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"

#include <cmath>

// Template type T1 is the input data type and will always be signed char or float 
// Template type T2 is the output data type and this can be either signed char or float

template void MWAvgPoolingLayer::createAvgPoolingLayer<signed char, signed char>(MWTargetNetworkImpl*,
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

template void MWAvgPoolingLayer::createAvgPoolingLayer<float, float>(MWTargetNetworkImpl*,
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

// Create AvgPooling2DLayer with PoolSize = [ PoolH PoolW ]
//                                Stride = [ StrideH StrideW ]
//                               Padding = [ PaddingH_T PaddingH_T_B PaddingW_L PaddingW_R ]
template <typename T1, typename T2>
void MWAvgPoolingLayer::createAvgPoolingLayer(MWTargetNetworkImpl* ntwk_impl,
                                              MWTensorBase* m_in,
                                              int m_PoolH,
                                              int m_PoolW,
                                              int m_StrideH,
                                              int m_StrideW,
                                              int m_PaddingH_T,
                                              int m_PaddingH_B,
                                              int m_PaddingW_L,
                                              int m_PaddingW_R,
                                              int m_scalingFactorAlpha1,
                                              const char* m_accelerationMode,
                                              int /*m_numOutputs*/, 
                                              int outbufIdx) {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    setInputTensor(m_in);
    allocateOutputTensor<T2>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    strideH = m_StrideH;
    strideW = m_StrideW;

    poolH = m_PoolH;
    poolW = m_PoolW;

    isGlobalAveragePooling = (poolH == -1) && (poolW == -1);

    paddingH_T = m_PaddingH_T;
    paddingH_B = m_PaddingH_B;
    paddingW_L = m_PaddingW_L;
    paddingW_R = m_PaddingW_R;
    accelerationMode = m_accelerationMode;    

    m_impl = new MWAvgPoolingLayerImpl(this, ntwk_impl, m_PoolH, m_PoolW, m_StrideH, m_StrideW, m_PaddingH_T, m_PaddingH_B,
        m_PaddingW_L, m_PaddingW_R, m_scalingFactorAlpha1, m_accelerationMode);

#else
    setInputTensor(m_in);

    // Global Average Pooling case
    if ((m_PoolH == -1) && (m_PoolW == -1)) {
        m_PoolH = getInputTensor()->getHeight();
        m_PoolW = getInputTensor()->getWidth();
    }

    int outputH =
        ((getInputTensor()->getHeight() - m_PoolH + m_PaddingH_T + m_PaddingH_B) / m_StrideH) + 1;
    int outputW =
        ((getInputTensor()->getWidth() - m_PoolW + m_PaddingW_L + m_PaddingW_R) / m_StrideW) + 1;

    int numOutputFeatures = getInputTensor()->getChannels();
    allocateOutputTensor<T2>(outputH, outputW, numOutputFeatures,
                                getInputTensor()->getBatchSize(),
                                getInputTensor()->getSequenceLength(), NULL);
    assert(getOutputTensor()->getSequenceLength() == 1);

    m_impl = new MWAvgPoolingLayerImpl(this, ntwk_impl, m_PoolH, m_PoolW, m_StrideH, m_StrideW,
                                       m_PaddingH_T, m_PaddingH_B, m_PaddingW_L, m_PaddingW_R,
                                       outbufIdx);
#endif
}

void MWAvgPoolingLayer::propagateSize() {
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_ARMNEON) || defined(MW_TARGET_TYPE_MKLDNN)
    // Global Average Pooling case
    if (isGlobalAveragePooling) {
        poolH = getInputTensor()->getHeight();
        poolW = getInputTensor()->getWidth();
    }

    int outputH = ((getInputTensor()->getHeight() - poolH + paddingH_T + paddingH_B) / strideH) + 1;
    int outputW = ((getInputTensor()->getWidth() - poolW + paddingW_L + paddingW_R) / strideW) + 1;

    assert(getInputTensor()->getSequenceLength() == 1);

    bool isINT8x4 =
        getOutputTensor()->isInt8() && std::string{"INT8x4"}.compare(accelerationMode) == 0;

    int mult4_featureMap = isINT8x4 ? static_cast<int>(std::ceil((float)getInputTensor()->getChannels() / 4) * 4)
                                       : getInputTensor()->getChannels();

    resizeOutputTensor(outputH, outputW, mult4_featureMap,
                       getInputTensor()->getBatchSize(), getInputTensor()->getSequenceLength());

    m_impl->propagateSize();
#endif
}
