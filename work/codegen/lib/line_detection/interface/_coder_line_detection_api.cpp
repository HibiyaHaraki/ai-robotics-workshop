//
// File: _coder_line_detection_api.cpp
//
// GPU Coder version                    : 2.1
// CUDA/C/C++ source code generated on  : 11-Nov-2021 11:08:16
//

// Include Files
#include "_coder_line_detection_api.h"
#include "_coder_line_detection_mex.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131610U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "line_detection",                                     // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

// Function Declarations
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               uint8_T **ret_data, int32_T ret_size[3]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_I,
                             const char_T *identifier, uint8_T **y_data,
                             int32_T y_size[3]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             uint8_T **y_data, int32_T y_size[3]);

static const mxArray *emlrt_marshallOut(const real32_T u[2]);

static const mxArray *emlrt_marshallOut(const uint8_T u_data[],
                                        const int32_T u_size[3]);

// Function Definitions
//
// Arguments    : const emlrtStack *sp
//                const mxArray *src
//                const emlrtMsgIdentifier *msgId
//                uint8_T **ret_data
//                int32_T ret_size[3]
// Return Type  : void
//
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId,
                               uint8_T **ret_data, int32_T ret_size[3])
{
  static const int32_T dims[3]{3, 1280, 720};
  int32_T iv[3];
  const boolean_T bv[3]{false, true, true};
  emlrtCheckVsBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"uint8",
                            false, 3U, (void *)&dims[0], &bv[0], &iv[0]);
  ret_size[0] = iv[0];
  ret_size[1] = iv[1];
  ret_size[2] = iv[2];
  *ret_data = (uint8_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *b_I
//                const char_T *identifier
//                uint8_T **y_data
//                int32_T y_size[3]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_I,
                             const char_T *identifier, uint8_T **y_data,
                             int32_T y_size[3])
{
  emlrtMsgIdentifier thisId;
  uint8_T *b;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(b_I), &thisId, &b, y_size);
  *y_data = b;
  emlrtDestroyArray(&b_I);
}

//
// Arguments    : const emlrtStack *sp
//                const mxArray *u
//                const emlrtMsgIdentifier *parentId
//                uint8_T **y_data
//                int32_T y_size[3]
// Return Type  : void
//
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId,
                             uint8_T **y_data, int32_T y_size[3])
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y_data, y_size);
  emlrtDestroyArray(&u);
}

//
// Arguments    : const real32_T u[2]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const real32_T u[2])
{
  static const int32_T iv[2]{0, 0};
  static const int32_T iv1[2]{1, 2};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(2, (const void *)&iv[0], mxSINGLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &iv1[0], 2);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const uint8_T u_data[]
//                const int32_T u_size[3]
// Return Type  : const mxArray *
//
static const mxArray *emlrt_marshallOut(const uint8_T u_data[],
                                        const int32_T u_size[3])
{
  static const int32_T iv[3]{0, 0, 0};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(3, (const void *)&iv[0], mxUINT8_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u_data[0]);
  emlrtSetDimensions((mxArray *)m, &u_size[0], 3);
  emlrtAssign(&y, m);
  return y;
}

//
// Arguments    : const mxArray * const prhs[1]
//                int32_T nlhs
//                const mxArray *plhs[2]
// Return Type  : void
//
void line_detection_api(const mxArray *const prhs[1], int32_T nlhs,
                        const mxArray *plhs[2])
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  int32_T I_size[3];
  int32_T Iout_size[3];
  real32_T(*predictedPosNorm)[2];
  uint8_T(*I_data)[2764800];
  uint8_T(*Iout_data)[2764800];
  st.tls = emlrtRootTLSGlobal;
  predictedPosNorm = (real32_T(*)[2])mxMalloc(sizeof(real32_T[2]));
  Iout_data = (uint8_T(*)[2764800])mxMalloc(sizeof(uint8_T[2764800]));
  // Marshall function inputs
  emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "I", (uint8_T **)&I_data, I_size);
  // Invoke the target function
  line_detection(*I_data, I_size, *predictedPosNorm, *Iout_data, Iout_size);
  // Marshall function outputs
  plhs[0] = emlrt_marshallOut(*predictedPosNorm);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(*Iout_data, Iout_size);
  }
}

//
// Arguments    : void
// Return Type  : void
//
void line_detection_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  line_detection_xil_terminate();
  line_detection_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void line_detection_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

//
// Arguments    : void
// Return Type  : void
//
void line_detection_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

//
// File trailer for _coder_line_detection_api.cpp
//
// [EOF]
//
