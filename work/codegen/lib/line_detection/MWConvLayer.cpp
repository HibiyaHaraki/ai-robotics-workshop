/* Copyright 2018-2019 The MathWorks, Inc. */

#include "MWConvLayer.hpp"
#include "MWConvLayerImpl.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWTensorBase.hpp"
#include "MWCNNLayer.hpp"

//Create Convolution2DLayer with  FilterSize = [r s]
//                               NumChannels = c
//                                NumFilters = k
//                                    Stride = [ StrideH StrideW ]
//                                   Padding = [ PaddingH PaddingW ]
//                            DilationFactor = [dilationFactorH dilationFactorW]
//g is for number of groups.
//g = 2 if NumChannels == [c c] and NumFilters == [k k].
//g = 1 otherwise.
//NNT does not support any other cases.
void MWConvLayer::createConvLayer(MWTargetNetworkImpl* ntwk_impl,
                                  MWTensorBase* m_in,
                                  int m_FilterH,
                                  int m_FilterW,
                                  int m_NumChannels,
                                  int m_NumFilters,
                                  int m_StrideH,
                                  int m_StrideW,
                                  int m_PaddingH_T,
                                  int m_PaddingH_B,
                                  int m_PaddingW_L,
                                  int m_PaddingW_R,
                                  int m_DilationFactorH,
                                  int m_DilationFactorW,
                                  int m_NumGroups,
                                  const char* m_weights_file,
                                  const char* m_bias_file,
                                  int outbufIdx)
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    setInputTensor(m_in);

    numFilters = m_NumFilters;
    numGroups = m_NumGroups;
    
    strideH = m_StrideH;
    strideW = m_StrideW;

    filterH = m_FilterH;
    filterW = m_FilterW;

    dilationFactorH = m_DilationFactorH;
    dilationFactorW = m_DilationFactorW;

    paddingH_T = m_PaddingH_T;
    paddingH_B = m_PaddingH_B;
    paddingW_L = m_PaddingW_L;
    paddingW_R = m_PaddingW_R;

    allocateOutputTensor<float>(-1, -1, -1, -1, -1, NULL);

    getOutputTensor(0)->setopBufIndex(outbufIdx);

    m_impl = new MWConvLayerImpl(this,
                                 ntwk_impl,
                                 m_FilterH,
                                 m_FilterW,
                                 m_NumGroups,
                                 m_NumChannels,
                                 m_NumFilters,
                                 m_StrideH,
                                 m_StrideW,
                                 m_PaddingH_T,
                                 m_PaddingH_B,
                                 m_PaddingW_L,
                                 m_PaddingW_R,
                                 m_DilationFactorH,
                                 m_DilationFactorW,
                                 m_weights_file,
                                 m_bias_file);
    
#else
    setInputTensor(m_in);

    int m_filterH_temp = ((m_FilterH-1)*m_DilationFactorH)+1;
    int m_filterW_temp = ((m_FilterW-1)*m_DilationFactorW)+1;
    int outputH = ((getInputTensor()->getHeight()- m_filterH_temp + m_PaddingH_B + m_PaddingH_T)/m_StrideH) + 1;
    int outputW = ((getInputTensor()->getWidth()- m_filterW_temp + m_PaddingW_L + m_PaddingW_R)/m_StrideW) + 1;

    // allocate output tensor
    allocateOutputTensor<float>(outputH,
                                outputW,
                                m_NumFilters*m_NumGroups,
                                getInputTensor()->getBatchSize(),
                                getInputTensor()->getSequenceLength(),
                                NULL);
    assert(getOutputTensor()->getSequenceLength() == 1);

    m_impl = new MWConvLayerImpl(this,
                                 ntwk_impl,
                                 m_FilterH,
                                 m_FilterW,
                                 m_NumGroups,
                                 m_NumChannels,
                                 m_NumFilters,
                                 m_StrideH,
                                 m_StrideW,
                                 m_PaddingH_T,
                                 m_PaddingH_B,
                                 m_PaddingW_L,
                                 m_PaddingW_R,
                                 m_DilationFactorH,
                                 m_DilationFactorW,
                                 m_weights_file,
                                 m_bias_file,
                                 outbufIdx);
#endif
}

void MWConvLayer::propagateSize()
{
#if defined(MW_TARGET_TYPE_CUDNN) || defined(MW_TARGET_TYPE_MKLDNN) || defined(MW_TARGET_TYPE_ARMNEON)
    int filterH_temp = ((filterH-1)*dilationFactorH)+1;
    int filterW_temp = ((filterW-1)*dilationFactorW)+1;
    
    int outputH = ((getInputTensor()->getHeight() - filterH_temp + paddingH_B + paddingH_T)/strideH) + 1;
    int outputW = ((getInputTensor()->getWidth() - filterW_temp + paddingW_L + paddingW_R)/strideW) + 1;

    // allocate output tensor
    resizeOutputTensor(outputH,
                       outputW,
                       numFilters*numGroups,
                       getInputTensor()->getBatchSize(),
                       getInputTensor()->getSequenceLength());
    
    assert(getOutputTensor()->getSequenceLength() == 1);

    m_impl->propagateSize();
#endif
}
    
