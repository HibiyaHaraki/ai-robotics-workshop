/* Copyright 2019-2020 The MathWorks, Inc. */

// MKLDNN specific implementation of the Custom Layer Base Class
#include "MWCustomLayerForMKLDNN.hpp"
#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"
#include "MWTargetNetworkImpl.hpp"
#include "MWMkldnnUtils.hpp"

#include <cstring>

MWCustomLayerForMKLDNN::MWCustomLayerForMKLDNN()
    : m_ntwkImpl(NULL) {
    m_isCustomLayer = true;
}

void MWCustomLayerForMKLDNN::setupLayer(MWTargetNetworkImpl* targetImpl) {
    m_ntwkImpl = targetImpl;
}

void MWCustomLayerForMKLDNN::cleanup() {
    this->MWCNNLayer::cleanup();
    this->cleanupLayer();
}

void MWCustomLayerForMKLDNN::allocate() {
    for (size_t iOut = 0; iOut < getNumOutputs(); iOut++) {
        MWTensorBase* opTensor = getOutputTensor(iOut);
        static_cast<MWTensor<float>*>(opTensor)->setData(
            m_ntwkImpl->getBufferPtr(opTensor->getopBufIndex()));
        this->setCustomLayerMemoryData(opTensor);
    }
}

void MWCustomLayerForMKLDNN::deallocate() {
    for (size_t iOut = 0; iOut < getNumOutputs(); iOut++) {
        static_cast<MWTensor<float>*>(getOutputTensor(iOut))->setData((float*)NULL);
    }
}

void MWCustomLayerForMKLDNN::layerMemoryReorder(MWTensorBase* ipTensor, int bufIndex) {

    // get the layer memory by recursing towards source till a layer memory is found
    std::shared_ptr<dnnl::memory> srcLayerImplMemory =
        MWMkldnnUtils::getLayerMemoryPrimitive(ipTensor);

    // get the custom layer memory
    std::shared_ptr<dnnl::memory> customLayerMemory = getCustomLayerMemory(ipTensor);

    // execute reorder operation if required
    if (srcLayerImplMemory->get_desc() != customLayerMemory->get_desc()) {

        customLayerMemory->set_data_handle(m_ntwkImpl->getPermuteBuffer(bufIndex));
        // reordering does not happen inplace
        // initialize the memory with a new buffer

        auto s = dnnl::stream(*m_ntwkImpl->eng);
        dnnl::reorder layerMemoryReorderPrim =
            dnnl::reorder(*srcLayerImplMemory, *customLayerMemory);
        layerMemoryReorderPrim.execute(s, *srcLayerImplMemory, *customLayerMemory);
    } else {
        // if no reordering is required copy the input data to permute buffer
        // in predict call, we always use permute buffer when layerMemoryReorder() is invoked
        memcpy(m_ntwkImpl->getPermuteBuffer(bufIndex),
               static_cast<MWTensor<float>*>(ipTensor)->getData(),
               sizeof(float) * ipTensor->getNumElements());
    }
}

void MWCustomLayerForMKLDNN::createLayerMemory(MWTensorBase* aTensor,
                                               MWTensorBase::DIMSLABEL implLayout[]) {

    // we only create a new custom layer memory if one does not already exist in the map

    if (!getCustomLayerMemory(aTensor)) {
        // create a new custom layer memory for the tensor, if a layer memory does not already exist
        // specfifying the strides directly as ncwh/hwcn format_tag does not exist

        const int size = 4;
        int outDims[size];
        MWTensorBase::DIMSLABEL srcLayout[size] = {MWTensorBase::N, MWTensorBase::C,
                                                   MWTensorBase::H, MWTensorBase::W};
        aTensor->getDimsByLayout(implLayout, size, outDims);

        int strides[size];
        MWTensorBase::getTransformStrides(srcLayout, implLayout, outDims, size, strides);

        dnnl::memory::dims layerMemoryStrides = {strides[0], strides[1], strides[2], strides[3]};
        dnnl::memory::dims layerMemoryDimensions = {aTensor->getBatchSize(),
                                                      aTensor->getChannels(), aTensor->getHeight(),
                                                      aTensor->getWidth()};
        // memory dimensions always need to be in NCHW format, even if memory format is different
        // srcLayout is hence NCHW always

        dnnl::memory::desc layerMemoryDescriptor = dnnl::memory::desc(
            layerMemoryDimensions, dnnl::memory::data_type::f32, layerMemoryStrides);

        std::shared_ptr<dnnl::memory> layerMemory =
            std::make_shared<dnnl::memory>(layerMemoryDescriptor, *m_ntwkImpl->eng,
                                             static_cast<MWTensor<float>*>(aTensor)->getData());

        // populate the custom layer memory map
        setCustomLayerMemory(aTensor, layerMemory);

        // update the max buffer size for memory
        int bufSize = (int)(layerMemory->get_desc().get_size() / sizeof(float));
        maxBufSize = (maxBufSize < bufSize) ? bufSize : maxBufSize;

    }
}

std::shared_ptr<dnnl::memory> MWCustomLayerForMKLDNN::getCustomLayerMemory(
    MWTensorBase* aTensor) {

    if (!m_customLayerMemory.empty()) {
        std::map<MWTensorBase*, std::shared_ptr<dnnl::memory>>::iterator it =
            m_customLayerMemory.find(aTensor);
        if (it != m_customLayerMemory.end()) {
            return it->second;
        }
    }

    return nullptr;
}

void MWCustomLayerForMKLDNN::setCustomLayerMemory(MWTensorBase* aTensor,
                                                  std::shared_ptr<dnnl::memory> aLayerMemory) {
    // check that we are not over-writing memory
    if (m_customLayerMemory.find(aTensor) == m_customLayerMemory.end()) {
        m_customLayerMemory[aTensor] = aLayerMemory;
    } else {
        assert(m_customLayerMemory[aTensor] == aLayerMemory);
    }
}

void MWCustomLayerForMKLDNN::setCustomLayerMemoryData(MWTensorBase* aTensor) {
    // get the custom layer memory primitive
    std::shared_ptr<dnnl::memory> customLayerMemory = getCustomLayerMemory(aTensor);

    // set the layer memory data
    customLayerMemory->set_data_handle(static_cast<MWTensor<float>*>(aTensor)->getData());
}

int MWCustomLayerForMKLDNN::getMaxBufSize() {
    return maxBufSize;
}

MWCustomLayerForMKLDNN::~MWCustomLayerForMKLDNN() {
}
