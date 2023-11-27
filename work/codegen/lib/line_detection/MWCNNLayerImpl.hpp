/* Copyright 2017-2020 The MathWorks, Inc. */

#ifndef CNN_API_IMPL
#define CNN_API_IMPL

#include "MWTensorBase.hpp"
#include "MWTensor.hpp"
#include "MWCNNLayer.hpp"

#include <cudnn.h>
#include <cublas_v2.h>
#include <map>
#include <cassert>

class MWTargetNetworkImpl;

#define CUDA_CALL(status) cuda_call_line_file(status, __LINE__, __FILE__)
#define MALLOC_CALL(msize) malloc_call_line_file(msize, __LINE__, __FILE__)
#define CUDNN_CALL(status) cudnn_call_line_file(status, __LINE__, __FILE__)
#define CUBLAS_CALL(status) cublas_call_line_file(status, __LINE__, __FILE__)
#define CUDA_FREE_CALL(buf) call_cuda_free(buf, __LINE__, __FILE__)

//#define RANDOM
#ifdef RANDOM
#include <curand.h>
#define CURAND_CALL(status) curand_call_line_file(status, __LINE__, __FILE__)
#endif

void cuda_call_line_file(cudaError_t, const int, const char*);
void cudnn_call_line_file(cudnnStatus_t, const int, const char*);
float* malloc_call_line_file(size_t, const int, const char*);
const char* cublasGetErrorString(cublasStatus_t);
void cublas_call_line_file(cublasStatus_t, const int, const char*);

void throw_cuda_error(cudaError_t rlQsibXJSWJVnUVpdNeL, const int bERCRkGjpaKXMNComoYl, const char *QTXuPiGKeBUnmRzhlIDp);

template <class T>
void call_cuda_free(T* mem, const int bERCRkGjpaKXMNComoYl, const char* QTXuPiGKeBUnmRzhlIDp) {
    if (!mem) {
        return;
    }

    cudaError_t rlQsibXJSWJVnUVpdNeL = cudaFree(mem);

    if ((rlQsibXJSWJVnUVpdNeL != cudaSuccess) && (rlQsibXJSWJVnUVpdNeL != cudaErrorCudartUnloading)) {
        throw_cuda_error(rlQsibXJSWJVnUVpdNeL, bERCRkGjpaKXMNComoYl, QTXuPiGKeBUnmRzhlIDp);
    } 
}

#ifdef RANDOM
void curand_call_line_file(curandStatus_t, const int, const char*);
#endif


class MWCNNLayerImpl {
  public:
    MWCNNLayerImpl(MWCNNLayer* layer, MWTargetNetworkImpl* ntwk_impl);
    virtual ~MWCNNLayerImpl();
    virtual void predict() = 0;
    virtual void cleanup() = 0;
    virtual void propagateSize() = 0;
    virtual void allocate() {
    }

    template <class T>
    void allocateOutputData(int);

    virtual void deallocate() {
    }

    template <class T>
    void deallocateOutputData(int);

    virtual void postSetup() {
    }
    template <typename T>
    T* getData(int index = 0);
    MWCNNLayer* getLayer() {
        return bDTIjtxZiSHtjwzgEluE;
    }
    MWTargetNetworkImpl* getTargetNetworkImpl() {
        return dMxIKDGTITyhdLqIHBLA;
    }

  protected:
    MWCNNLayer* bDTIjtxZiSHtjwzgEluE;
    std::map<int, cudnnTensorDescriptor_t*> kqftrrQBBOgGsrDSkIUk; // output descriptors
    MWTargetNetworkImpl* dMxIKDGTITyhdLqIHBLA;

    float PmFfARVzoHVAYkfpuvqK;
    float PQjbchiGbyJfmpiqPpOC;
    float OwortPcLToImGdYFtbSF;

    float* getZeroPtr();   // Get the pointer to a zero value parameter
    float* getOnePtr();    // Get the pointer to a one value parameter
    float* getNegOnePtr(); // Get the pointer to a negative one value parameter

  protected:
    template <class T>
    static void setDescriptor(cudnnTensorDescriptor_t&, MWTensor<T>*);

    template <class T>
    static cudnnDataType_t getCuDNNDataType();

    cudnnTensorDescriptor_t* getDescriptor(int);
    cudnnTensorDescriptor_t* createAndAddDescriptor(int);

    virtual float* offsetOutputPointer(float* initialPointer, int) {return initialPointer;}
    virtual signed char* offsetOutputPointer(signed char* initialPointer, int) {return initialPointer;}

  public:
    static void padInput(float*, int, int, int, int, int, int, int, float*, int);
    static void padInput(signed char*, int, int, int, int, int, int, int, signed char*, int);    
    static void
    fillOutputBuffer(signed char*, int, int, int, int, int, int, int, signed char*, int, int);
    static cudnnTensorDescriptor_t getCuDNNDescriptor(MWTensorBase*);
    static void throwAllocationError(const int, const char*);

    static void setDescriptorForINT8(cudnnTensorDescriptor_t&, MWTensor<signed char>*, cudnnDataType_t, cudnnTensorFormat_t);    
};

#endif
