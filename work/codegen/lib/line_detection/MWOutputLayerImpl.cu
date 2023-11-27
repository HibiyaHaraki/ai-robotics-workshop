#include "MWOutputLayerImpl.hpp"
#include "MWCNNLayerImpl.hpp"
 class MWCNNLayer; class MWTargetNetworkImpl; 
MWOutputLayerImpl::MWOutputLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* 
ntwk_impl) : MWCNNLayerImpl(layer, ntwk_impl) { } 
MWOutputLayerImpl::~MWOutputLayerImpl() { } void 
MWOutputLayerImpl::propagateSize() { } void MWOutputLayerImpl::predict() { } 
void MWOutputLayerImpl::cleanup() { }