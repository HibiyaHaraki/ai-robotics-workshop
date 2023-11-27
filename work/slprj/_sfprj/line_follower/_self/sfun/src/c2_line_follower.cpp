/* Include files */

#include "line_follower_sfun.h"
#include "c2_line_follower.h"
#include "mwmathutil.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

#include <cstring>

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
const int32_T CALL_EVENT = -1;

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static emlrtRSInfo c2_emlrtRSI = { 2,  /* lineNo */
  "Controller/Deep Learning Based Regressor/Predict/MLFB",/* fcnName */
  "#line_follower:385:306"             /* pathName */
};

static emlrtRSInfo c2_b_emlrtRSI = { 1,/* lineNo */
  "deepNetwork",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2021a\\toolbox\\nnet\\deep_blocks\\+deep\\+blocks\\+internal\\deepNetwork.p"/* pathName */
};

static emlrtRSInfo c2_c_emlrtRSI = { 69,/* lineNo */
  "loadDeepLearningNetwork",           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2021a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\loadDeepLearningNetwork.m"/* pathName */
};

static emlrtRSInfo c2_d_emlrtRSI = { 1,/* lineNo */
  "loadDeepLearningNetwork",           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2021a\\toolbox\\shared\\dlcoder_base\\dlcoder_base\\+coder\\+internal\\loadDeepLearningNetwork.p"/* pathName */
};

static emlrtRSInfo c2_e_emlrtRSI = { 1,/* lineNo */
  "DeepLearningNetwork",               /* fcnName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@DeepLearningN"
  "etwork\\DeepLearningNetwork.p"      /* pathName */
};

static emlrtRSInfo c2_f_emlrtRSI = { 1,/* lineNo */
  "predict",                           /* fcnName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@DeepLearningN"
  "etwork\\predict.p"                  /* pathName */
};

static emlrtRSInfo c2_g_emlrtRSI = { 1,/* lineNo */
  "permuteImageInput",                 /* fcnName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\+internal\\+ioh"
  "andling\\+cnn\\@InputDataPreparer\\permuteImageInput.p"/* pathName */
};

static emlrtBCInfo c2_emlrtBCI = { 1,  /* iFirst */
  3,                                   /* iLast */
  1,                                   /* lineNo */
  1,                                   /* colNo */
  "",                                  /* aName */
  "transposeHWDims",                   /* fName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@coderNetworkU"
  "tils\\transposeHWDims.p",           /* pName */
  3                                    /* checkKind */
};

static emlrtDCInfo c2_emlrtDCI = { 1,  /* lineNo */
  1,                                   /* colNo */
  "transposeHWDims",                   /* fName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@coderNetworkU"
  "tils\\transposeHWDims.p",           /* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo c2_b_emlrtBCI = { 1,/* iFirst */
  3,                                   /* iLast */
  1,                                   /* lineNo */
  1,                                   /* colNo */
  "",                                  /* aName */
  "transposeHWDims",                   /* fName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@coderNetworkU"
  "tils\\transposeHWDims.p",           /* pName */
  0                                    /* checkKind */
};

/* Function Declarations */
static void initialize_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void initialize_params_c2_line_follower(SFc2_line_followerInstanceStruct *
  chartInstance);
static void enable_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void disable_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void c2_update_jit_animation_state_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance);
static void c2_do_animation_call_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance);
static void ext_mode_exec_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance);
static void set_sim_state_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_st);
static void sf_gateway_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void mdl_start_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void mdl_terminate_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void mdl_setup_runtime_resources_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance);
static void mdl_cleanup_runtime_resources_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance);
static void initSimStructsc2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance);
static void c2_DeepLearningNetwork_setup(SFc2_line_followerInstanceStruct
  *chartInstance, c2_mynet_new0_line_follower0 *c2_obj);
static void c2_DeepLearningNetwork_predict(SFc2_line_followerInstanceStruct
  *chartInstance, const emlrtStack *c2_sp, c2_mynet_new0_line_follower0 *c2_obj,
  uint8_T c2_varargin_1[172800], real32_T c2_varargout_1[2]);
static void c2_emlrt_marshallIn(SFc2_line_followerInstanceStruct *chartInstance,
  const mxArray *c2_b_out_1_predict, const char_T *c2_identifier, real32_T c2_y
  [2]);
static void c2_b_emlrt_marshallIn(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real32_T c2_y[2]);
static uint8_T c2_c_emlrt_marshallIn(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_line_follower, const char_T
  *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_chart_data_browse_helper(SFc2_line_followerInstanceStruct
  *chartInstance, int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T
  *c2_isValueTooBig);
static void init_dsm_address_info(SFc2_line_followerInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc2_line_followerInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
  emlrtStack c2_st = { NULL,           /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  c2_st.tls = chartInstance->c2_fEmlrtCtx;
  emlrtLicenseCheckR2012b(&c2_st, (const char_T *)"neural_network_toolbox", 2);
  sim_mode_is_external(chartInstance->S);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_network_not_empty = false;
  chartInstance->c2_is_active_c2_line_follower = 0U;
}

static void initialize_params_c2_line_follower(SFc2_line_followerInstanceStruct *
  chartInstance)
{
}

static void enable_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_jit_animation_state_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance)
{
}

static void c2_do_animation_call_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance)
{
  sfDoAnimationWrapper(chartInstance->S, false, true);
  sfDoAnimationWrapper(chartInstance->S, false, false);
}

static void ext_mode_exec_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance)
{
  const mxArray *c2_b_y = NULL;
  const mxArray *c2_c_y = NULL;
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(2, 1), false);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", *chartInstance->c2_out_1_predict, 1,
    0U, 1U, 0U, 2, 1, 2), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y",
    &chartInstance->c2_is_active_c2_line_follower, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_st)
{
  const mxArray *c2_u;
  int32_T c2_i;
  real32_T c2_fv[2];
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
                      "out_1_predict", c2_fv);
  for (c2_i = 0; c2_i < 2; c2_i++) {
    (*chartInstance->c2_out_1_predict)[c2_i] = c2_fv[c2_i];
  }

  chartInstance->c2_is_active_c2_line_follower = c2_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 1)),
     "is_active_c2_line_follower");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

static void sf_gateway_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
  c2_mynet_new0_line_follower0 *c2_b_iobj_0;
  c2_mynet_new0_line_follower0 *c2_iobj_0;
  c2_mynet_new0_line_follower0 *c2_net;
  c2_mynet_new0_line_follower0 *c2_obj;
  c2_mynet_new0_line_follower0 *c2_this;
  emlrtStack c2_b_st;
  emlrtStack c2_c_st;
  emlrtStack c2_st = { NULL,           /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  int32_T c2_i;
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_i3;
  real32_T c2_fv[2];
  c2_st.tls = chartInstance->c2_fEmlrtCtx;
  c2_b_st.prev = &c2_st;
  c2_b_st.tls = c2_st.tls;
  c2_c_st.prev = &c2_b_st;
  c2_c_st.tls = c2_b_st.tls;
  chartInstance->c2_JITTransitionAnimation[0] = 0U;
  _sfTime_ = sf_get_time(chartInstance->S);
  for (c2_i = 0; c2_i < 172800; c2_i++) {
    covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 0U, (real_T)
                      (*chartInstance->c2_in_1)[c2_i]);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 4U, 0, 0);
  for (c2_i1 = 0; c2_i1 < 172800; c2_i1++) {
    chartInstance->c2_r.f1[c2_i1] = (*chartInstance->c2_in_1)[c2_i1];
  }

  chartInstance->c2_inputs[0] = chartInstance->c2_r;
  c2_b_st.site = &c2_emlrtRSI;
  if (!chartInstance->c2_network_not_empty) {
    c2_c_st.site = &c2_b_emlrtRSI;
    c2_iobj_0 = &chartInstance->c2_network;
    c2_b_iobj_0 = c2_iobj_0;
    c2_obj = c2_b_iobj_0;
    c2_net = c2_obj;
    c2_this = c2_net;
    c2_net = c2_this;
    c2_DeepLearningNetwork_setup(chartInstance, c2_net);
    chartInstance->c2_network_not_empty = true;
  }

  c2_c_st.site = &c2_b_emlrtRSI;
  c2_DeepLearningNetwork_predict(chartInstance, &c2_c_st,
    &chartInstance->c2_network, chartInstance->c2_inputs[0].f1, c2_fv);
  for (c2_i2 = 0; c2_i2 < 2; c2_i2++) {
    (*chartInstance->c2_out_1_predict)[c2_i2] = c2_fv[c2_i2];
  }

  c2_do_animation_call_c2_line_follower(chartInstance);
  for (c2_i3 = 0; c2_i3 < 2; c2_i3++) {
    covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 1U, (real_T)
                      (*chartInstance->c2_out_1_predict)[c2_i3]);
  }
}

static void mdl_start_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
}

static void mdl_terminate_c2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
}

static void mdl_setup_runtime_resources_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance)
{
  static const uint32_T c2_decisionTxtEndIdx = 0U;
  static const uint32_T c2_decisionTxtStartIdx = 0U;
  setLegacyDebuggerFlag(chartInstance->S, false);
  setDebuggerFlag(chartInstance->S, true);
  setDataBrowseFcn(chartInstance->S, (void *)&c2_chart_data_browse_helper);
  chartInstance->c2_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c2_RuntimeVar,
    &chartInstance->c2_IsDebuggerActive,
    &chartInstance->c2_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c2_mlFcnLineNumber, &chartInstance->c2_IsHeatMapPresent, 0);
  sim_mode_is_external(chartInstance->S);
  covrtCreateStateflowInstanceData(chartInstance->c2_covrtInstance, 1U, 0U, 1U,
    4U);
  covrtChartInitFcn(chartInstance->c2_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c2_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c2_decisionTxtStartIdx, &c2_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c2_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c2_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 4U, 0U, 0U,
                     "eML_blk_kernel", 0, -1, 266);
}

static void mdl_cleanup_runtime_resources_c2_line_follower
  (SFc2_line_followerInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c2_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c2_covrtInstance);
}

static void initSimStructsc2_line_follower(SFc2_line_followerInstanceStruct
  *chartInstance)
{
}

const mxArray *sf_c2_line_follower_get_eml_resolved_functions_info()
{
  const mxArray *c2_nameCaptureInfo = NULL;
  const char_T *c2_data[48] = {
    "789ced9ddb8f23d95dc7bdd1ae3659d8dd49206413603559f601b1daa1dbedbe384ff1dd6e5fda77b77b3bda2e978fedb2ebd675f14d48b478da170442ca6521"
    "28231269034240564440a488205ee01f009e501e5824947f202f20caae3a3d55ddee2e4f574dcdf1e9df4fdaf5947fdd757ee79ceaefa7ce3df442aef8422814",
    "7a2d64da07279f5a7ebe6afcf7b2f1df03ebfb4f859c76d5ff82f5d9b15dbf6cfbf997422f5efe9efde7ffc0fa6425514353cdbc1019015dfe665712389111b5"
    "fa4c462105a9123f46dda5a7c7f1a8ce09a866bf282dae84b4cd7579b1702dfe9d18207654d3859032509f44c8db2f2ecbe35f6cf90dd9f2fbe29ae5816cd7f6",
    "f27870c5ff5eee38f5b5b70546e3998e2249dadba79a24f11d697aaa0e1805754fbb3c2b7591f27e875191f3e29de5bf4fdfe18c125444863fe525a69b44482e"
    "20461139b15f42da4452468f645bbea61ef3f54b2ef9c2fe15712cbfc7715c788ce38b2e7160ffb28c1edd14cd9378f08def1acf639778b0ffbd5ce26b89af9c",
    "9615a9af304292d198d362ac5e88c54f6bba2c4b8a5666d811d347ea6935bc15de666e7d1c54f35764fc2be6cfbcdfe5dfd718a58f34153f235f5d5100a72b1f"
    "155c1e67b6fcdaf3f1fa9ae561ff7cd9f1f39f0e7d647cf9e627ffb6fc91a0d2bb78e9ad4f824c0fdbf34acfebdff9afdc90de832bfef6f1341cd3c2e969bed5",
    "1fa8f1f1ce7ee3584f3c89a37c431cb6906f8d2364bbb6c711d4fd69e580ec315fafd9ae57e50bfb55a459c997967007fd07fd07fd07fd07fd77fa374dff3fe3"
    "922fec67199eaf214dc7e981fe83fe83fe83fe83fe3bfd41ebff99c77cbd7463be4c8f6a693ee83de83de83de83de8bdd3bf69effbafdbae57e50bfb17effb0d",
    "b9cb68a8a619ff03fd07fd07fd0f203dd07f7fee0ffaefadbf7fa1ff5564bcfd9bf20ffa0ffa0ffa1f407aa0fffedc1ff47f75be7ec1255fd86ff5f7d7b8b999"
    "53d07fd07fd07fd07fd07fa77fd3e67d7ed6255fd82f2b4836e26f2256939485dc59df03078003c001e00070c0e90f9a031f78ccd7975df285fd668e1246847d",
    "24962451d345a6c32343ff64a4681cc26b2e800bc005e0027001b8e0f46f1a177ed3255fd8efe042711a531466b60a0fc005e0027001b8005c70fa376ddce055"
    "dbf5aa7c617fff729dd8516718827601e83fe87f10e981fefb737fd0ffd5f97ac5255fd86fa850ee68f1fa6f750c81fe83fe83fe83fe83fe3bfd9b366efc0597",
    "7c613fbbd89b292d293574ae239145587d8103c001e000700038e0f46f5a3bc07ebd2a5ff8f3493bc08041b55402fd07fd07fd07fd07fd77fa374dffd71d0798"
    "1821e44459d7624a5f0d413f10e83fe87f10e981fefb737fd0ffd5f95a77fdd84461e422a35dae1c00fd07fd07fd07fd07fd77fa83d6ff0b8ff9fa924bbeb07f",
    "ccf0dc62f7202b86b4a424784655b9deccf4030f8007c003e001f0c0e9dfb4f6c0bafd41860a2d01b0383d00fa8340ff41ff83490ff4df9ffbd3aaff171ef3b5"
    "6e7bc0b15eac204d9052976a9aa2b3d69171c003e001f00078003c70fa378d07ebeaafb5bfd0728878b1c9dc629a50028d19def2030f8007c003e001f0c0e9df",
    "b4fea175d78d29b6bda6432172f5ffe71ee3f9964b3cd8ff5eee8818003ca91bd07dd07dd33e7f437a0faef8d3e1217b508aee09db3b9d5a3a7aa4752b83a310"
    "e83ee9ba1fd47b016b8d0ac7c4aefdb81962f5ffd31edfffbfe7120ff693a4ffabeb68f9b804a65fe51f07cc83effecedf04991eb64de5c1ba7fefbdd2a01ce9",
    "a74f66d389324c2752f5e276af94041ed0ce8375df176423768ed5aee2805a1e7cd7251eec2789072bebc8c401b53c087de5f33f08343dcb68e701d7dfd10bc5"
    "e8b9d6d4f3e9d9414141a5ea200d3c209d07671ef3f5e91bf3657af03b27a9baefb51fe81b2ef1603f49ba8feb64f120d0aaf3f0de6f9adf3a5f124789c37cbf",
    "5c3faa8be3add8c1b42ae72a19d079d275de6bffffbaebc51856e3c68cc649a2b9711ca9ba8f6f7cd7783e748907fb49d27d5bdd3cc2cf03adfa1f7af5bffe3a"
    "d0f42ca35dff879d397f9c3f88b7229370f7586cc672bb7904e3bfc4ebff99c77cbd6cbb76e6cbbcb2fa1288d57bafeff95f778907fb49d27bab4ed67a0e3656",
    "e7a13f67697eebbc9adb5272fbd5527d18ed975ac949493c3ed6e2a0f3a4ebfc85c77cadbb0e6071ae70d9d497c58c4f5dd524a1c0cc9042f87ed15efbf9bfef"
    "120ff693c4819beb2ab879407ff97f01f7ff7cccff5e90e961a39d0bbade2c724a247b30da9926e6c9a83c49edef41ff0ff15c08eabc615b1f83b961a8f53da9",
    "3cf0da0ff41d9778b09f241e5cab23e349a1b67d00fd404bf39b033cdfc97199fae134da9c7439559d88095e030e0007ac4fa7c6248003d627b91c4804ca0158"
    "17f06cd30b8a037bf1745ee5cb913e3b8e8badf4764a6f0c5598070a1cb03e9d7d0fd01e209103d7ea88e2f600cc0b32cd6f0ea4e4716267672a1422692d36ad",
    "6606bbddcc24051c209d03671ef3e536ff13ef1f4aaadedfc7f99fb84e829cff09effbcf36bda0745e6ee667f5e1e0e8508886d15e235e6a347806e6ff10aff3"
    "b2c77c7dc6255fd8af222d26b20349b1ae69d5fd6fbac483fd24e9fe65dd50fc7e0ff3814cf35df70ffb5569a72908ddd96122cf2bf1795f6f81ee13affb1f78",
    "ccd7db2ef9c27e59523543e358a4aa47ba26eb5a5daa224d57c484f1a2d997148e35b7842395076f78ecf7f9d8251eec278907ebd4195e2800bcf0293dcb68e7"
    "8510abcfe71d75bcbb3fccd5fa427f6f903ad2a03f0878617d5afb863611ab498aa13e3546907994969498730119f082205eac5167c00b9fd3b36c5379b1ee7e",
    "3183dab8332b46d46aeeb83dd1630783c6766b1e025ed0ce8bdf70c917f6e37da60543b76ec105b5bcf8814b3cd84f202f6eab33fad721032f96e677fb22afee"
    "e78ef60a71465427b176a9a5c526d9521678413a2fbc3e1fbfec922fecb7b4a75a2a2510cf9bdd1ba110b97cf0ba2eedcf5ce2c17e02f9e0a823683ff89c9e65",
    "b4f320959a8891fdd1fee1b0b1d5adf251bedc1b74617c827a1eac3d7e656a4d9113b90ea3b1033c1995561e6ce2fed4abeb88eefda98107a6f9fdf79ee94ca2"
    "e1c479b731cea66ab54e7a5a4a36b6605d02f13cc0fd0177cdd7abb6eb55f9c27ef9ca9a045239806f7cd778fec4251eec278c038eb508f6f238b3e5d79e0fd0",
    "ff35d3b38c76fde7a2d99e966da972fa50e9ee9423f3dd7405c69fc9d7ffa0c69b166b9e622bf6aa209503f7f17c82957544390f607d9a697ef3e0a82174a60d"
    "a6a6cac7d3ceb9b287127a750cfbd911cf03afed81d76cd7abf285fd4ead2197035edb03df768907fbc9e500e5fd41b05fd1d2fcd6ff447158e9745421721899",
    "4fbb850e13d1a4348c1753afffeb9e5b60db0361794dabfe6fe2b905b6baa17ebe10bcff9be6b7fe47ca11b6b73bd83d513bd20eb73f8b0c5207b06e997efd7f"
    "dd76bd2a5fd8af22cd4abec6cd914aadfeffa94b3cd84f92fe5fa91b38cfc0cff42ca35dffd38916cfee85d3895d4e1a0af2e840294e23301e40bcfe7b7d3e3e",
    "e7922fec37342627cabab65018fb4675b472e0b14b3cd84f1807aed45170e71700079e6d7a4171a07d5c3d89ed30e1ce5ef428bfdf2b6cede7d37bd00e209e03"
    "c1ad4b5eee8760d79955c3c4c472e17eae4b76af335857e0737a96d1ce8b72a5546f4d2349516889c59369ba1d4debcd0cf082745e5c78ccd743977c61ff0aed",
    "716ca54c2a271e78e4c45fb9c483fd8473e2eab6d7c007bfd2b36c53f9b0ee3cc2f8c92197d01a893d864931a593f9d67e0ee921e003e97cf03aaef08b2ef9c2"
    "7e9951546493605279e0b53fe98f5de2c17ea27860ab1b681ff89c9e65b4eb7f79d03dee4d225c629f3f188c6be72799fdec4108f49f74fdbff098af872ef9c2",
    "fea5c62cdf38d58411661f89b6ae09681f90c7835bea8ae6f601cc3b32cdeffea37a65ae758a4c6c9c48ed0af1d194ad148f10f41f011faccf5b3527017cd818"
    "3e24800f7ea6878d763e6cf5746577220ffad9522e9eab1c0af9a8c2c37834f57cf835977c61ff75cdb1baac13648f437be5c35fb8c483fd64f3e1495dd1debf",
    "047c30cd6f3eec15eb958376ba309db195ddaec00c9949838775cbc007ebf346cd217c9e12f0c15957b4f301c61f4cf37d1fec189fa94de27bdaee562fd7568a"
    "7c4b4fc2bea7e4f321a8f1294394eca12424b1c7f543e472e13eee73b4b28e609f235fd3c3463b0ff6e468b25ccc0f7481d3f773c5a361442bf5609f0be27970",
    "e1315f7eebf099c7785eb45d3be3313dac518af6f4f02fde35bdc737a6e7f4bf972346f6573e1241e9d39b9f04acf72fbdf54990e961a35defdbc7d3704c0ba7"
    "a7f9567fa0c6c73bfb8d639da2f77fd005a72e787dae3eeb521ed8bf8ccf4abda171bc6a7def571c5f708903fb4d5e5d8fc6afe763fdfdf09ecbf3712de3a7d7",
    "be09763fbcfff859c0dcf89f8f0e824c0f1beddca8d61994cb552b954ea99e2c1e76f34aaf4bd3b80270c3c98d0b5b7eef521ebfee521ed8bfece35ef46e2b05"
    "a3d56385d16414237e4e0c91c70fafe3107fee1207f63faffea6eb00b9b586e8df5fef7ffff3e320d3c3463b4f923be15e3f32159ba593582d2cecf5333d2d0b",
    "ed106a798275e2aee561bf5e551ef85396649d6734b42889fa4c46a4f123b8f60731fcb8522374efc70dbc30cdef7149a69d4393fa14c5e7b9b1de91f6642daf"
    "9742c00b5a7911d8b9cf4811740d254aa5266235495994c8e27bdab8f1d8250eec27881b2b6a86def18ed0b77f04e31d21ffdb197d55ee9fec8e84d44c394ff6",
    "66f34cb69a6133c00d5ab9e1b59db1eefedf9ac288aa2ca928db4a72824a1d2f483f07f43a2faed408edf3a1a09db134bf79b15d6e46d1acd3df1ef572ad9472"
    "9ed079714ed139d0c00b7fc7397ed5a53cb09f5313baaa4942bc10ab25189eef187949894c8747dda59f347e789d57fb914b1cd84f0e3f6ea9218325305eee4f",
    "7ad868e7083fd6ca83ca3032ea4f04719c9c55aabdc90cc637a8e54850ed0e4e2da2e96234d65a99411a37ee5fbbe34a8d04dcee005e3cdbf482e245b4de4433"
    "2e25cf678dd2e161277db8576a66283a6f0878f1bc78712423b158c66d0de0c5f3e785a346a09fcad7f4b0d1ce8b44578b2766c3edfcc1fc649498f1c9435e11",
    "a07d412d2f821a0f57509f5335a4249121525d24b21c5a2ee5a08d1b8f5de2c07e72b8b1aa66603c1cb861dabaf3a83869bb5be0346ea8e4f29c38d463d9fcd1"
    "4e08b801dc585d1eebaeff33a2ac2f63c5d33cadef69e306e9e7615fe7c6b59aa1fa3c6c686f98e6777ba3a608a54641da89ef2763e170aa32ab6c47eb19e006",
    "addcf0da3fb5ee794797ea54e03a8b6bd278f1738f717ccb250eec279017468dd07b5e3670c234dfd7f5a5b403f67c3eec977bc9ea44d46b4c4e29c33a71e0c4"
    "0de561bf5e551ef8931d20769496941a27e83c278e48e384d7e762f3d6f55dad1158d7e7677ad868e7c571e57cd88ea0582bd25626c23ca96b7a2603f36d8117",
    "3794c7abb6eb55e581fd46940d913bd7518911167d51b4f1e2439738b09f1c5e386a04f60df1393d6cb4f3821fa6d46da52d4ecb93ed6a34c5f4b913ad97065e"
    "002f5697c72b2ee581fd469465230b255d30af49e385d77ea86fb8c481fd44f1c2aa11aacfc9034e2ccd6f4e64cb896945381f0cf22d1ef5c4422b5bedc760bc",
    "02387143793c05270acc0c293973d91e7082044e5835029c004e3c2d2726d170ac5498d55a03a464b45abbbba3281af43f01276e288fa7e87f325549eca2c5b3"
    "4c1a27ee65ffd3931a81fe279fd3c3463b2f2a6536be2335f9442a230bcaa8a28ee72735e87fa2961741e9b51165cdc802eae68eb04a712c226f5f29dacfdb5b",
    "c98d553503ebf67c4d0f1bedfce04727fd626c2b8f2aba50cb33bbdb6a6db80fed0d6af97161cbef5dcae34d97f2c0fe31c3735d464345464b733c8a89dd26a3"
    "708b15c6e60038691ca1fd3cefeb1cb9bd86683fcf1b78629aeff36d7b5a6ce7a8361e8cc29de3f07caf319fa1318c7350cb13afcfd51b2ee581fdcbd99d8646",
    "b58c38d2929265f85e4e94758d348e786d8f7ccf250eec27872337d50cccbff5333d6cb4f3235b65e3c31c3f4f1e74bad50a1b67d5c3c332f003f8714379f8a5"
    "db67778ce3aadd1407b6e0d767908289abdfc0b9af7ea6878d763ed07eeeebd90df77f563a447b7a3fbd637ab8bee62ee961ff7b8d85cc1e8928a9706374f98f",
    "87ef3e2c32daa065889e7a5a5bcae5c309a70d1ea6c6489949223acd891a5244863f4d4882a08b9c363bcd705a56ef9c32dcbb8ad491348e55df5da8a63a90e4"
    "d32551859988b4f745347924309a33bf6737e4d7afbffb9f26fe3d501d955ff9e63f07991e36da7574a8a23c77c816bbdbbbbbe3e13036acb45b3a453a1adc7b",
    "3629edf0dbf76383f7eca74b0fdeb3e13dfb3ef381f6f76ce083930f17b6fcdea53cbee4521ed8dfe5ad481f0923be2b8ad6474ce64cfff3e284d7750a7fe492"
    "1ef63f534e18ad019ee9983f607f262e0bfdf41db3b84f2f4b3de871de56d0fdf4bffbfb1f06991e36daf930c8cdf8633e96eff7f7b78f77b32325a9a53a149d",
    "0fe1550fbe7ec3fd1f5cf13f2f3eaceaa8978d9fe558cdb11fe785c772f8a24b3960bfd96e581195e5dfd4f6c36397f4b07f53c66bce6cf9b5e76353f7f5be78"
    "e92dd8d73be43f1fdac7d3704c0ba7a7f9567fa0c6c73bfb8d639da2f320800fa605b59ff7724ac922f76505c946d08af53d8ee30f3dc6f1db2e7160bfc929ce",
    "eab47fc4490346ecf246213d628dc6ccf528717c6f78e4c8dfb9c487fdcf8723efe00231fe75592286d368697cf55a999c5efb26c0f34c039f27f45b0ffe36c8"
    "f4b0d1ce975a6a6bb07538e119b9c78e060d09a5f74a53e00bf0e54a39accb970ea3b18332d3bdd426ebfbfbc297bf77890ffb9fd3f3f27480b9569914ef1b0e",
    "7c599aeffb70f4766be89cafa4e25beddcd1203c6df5876a06f8027c7196c3ba7c919122e81aca0946dc4b59b2be07be38fd1bc1976b95496fff58e85f7ff6df"
    "81a66719ed7c5127acc6ef25fa4ab3d6e8f3f5c468972de429dab703f8629aecb11c5eb35daf2a07ec5faec25a6a518d9ba3fbc3951fbac487fd1bc1156725d2",
    "7d2e1eb45b96e6f779aafdf67c502c1d7726d5c35935cbb0b981d00e87802bb471e5c26339ac3d2e7f29496a5a529a8c3233023311b3b44de1cc438f9cf9894b"
    "7cd8bf619cb952a9d04f06bc316ddd764cf99c8f0b2d21aad477b666cd7ca4bbd31eecc33c30ea7813543bc6102815413be65a7c1bd58e715622b4637c4c0f1b",
    "ed5c51cbc938b79599c406f36dee3cdc8c367af2098cef53c715d275fdec8ef15db59be2c306f3c4609e5890e961a39d23304fecf6fbd3c21158dffe74e9e17c"
    "c3fa766779b8e918ac6f7fb6e9c1fa767fee1fdc7b648a142cac5cb7f665ce7a795cbe4c1639915b4e0e85f6c7153fb43fa0fd11647ad868e70ceded0f9817ba",
    "debc50689f3c5d7ad03e81f6c97de606b44f6ebfff7d699f00379e2e3de0067003b8412f37bcea02e9e744af0207cbf07cd936e6612f0fafcfd5e75cca03fb8f"
    "746de5062c7ef5a36db9c481fdb7f7a35d8fd2aff9bfffe0121ff693d7af75bd4c4eaf7f45fff9e3add80f834c0f1bedbcd173d9a924e72bd38c543e50f285a6",
    "9e8c57b3c01be08db7f68811a4a9528b19a46949b1e2b937bcf94797f8b09fc07ed115c0b9a136691e4f01de2ccdeff58d2749a1d7ab70720ac5d034ba93e5fa"
    "99f346087803bcf1f65c5d55a802335b3671ee0b6f7eec121ff66f266f96b549f73a14e0cdd2fcd68508bf976eab7c45ecf109bd516b27b7b6954a0878432b6f",
    "f0f55dcbe355dbf5aaf2c07e874285368733f7789da31b67802f3ea6876d53f9b26eff199bae69052927275b8561bc1797947e649281f11a6af9e2f5b97ac3a5"
    "3cb0df083281c60cdf44ac26294f446a5338e3b53df31397f8b07f6338b3b236e9ddaf25f44fdf87f9c821ff795368760adbfd76a1b51f498ff4682cd311d536",
    "45fb4e026f9ce511e078cd52a196739f6d2d9bfbc21beac66b56d526c5e335c01bd3fce6cda1221fe78f3b279c109b8d0e0f53a30ad3e953b43f18f0c6591e41"
    "cd47b32fb53105ca1907edbcf9914b7cd8bf19bcb95e9b419f4b0cfbea3fdbf4821aafd9daed25b347d17cbb93a9651acd6eb1182bc543c01b5a7943bace9fdd",
    "31beab76537cd8609e33cc7386719a67d78ea17d9e7370ebf837643da6a91d970b3281374e03de006f8037c09bbbde1ffa3f9eaeff03f60178baf470be611f00"
    "6779b8e91dec03f06cd3837d00fcb93fb457d66baf00379e2e3de0067003b8411f37fe1fb9cbb4e8",
    "" };

  c2_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&c2_data[0], 154272U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_DeepLearningNetwork_setup(SFc2_line_followerInstanceStruct
  *chartInstance, c2_mynet_new0_line_follower0 *c2_obj)
{
  c2_mynet_new0_line_follower0 *c2_b_obj;
  c2_obj->setup();
}

static void c2_DeepLearningNetwork_predict(SFc2_line_followerInstanceStruct
  *chartInstance, const emlrtStack *c2_sp, c2_mynet_new0_line_follower0 *c2_obj,
  uint8_T c2_varargin_1[172800], real32_T c2_varargout_1[2])
{
  c2_mynet_new0_line_follower0 *c2_b_obj;
  c2_cell_wrap_10 c2_outdata[1];
  c2_cell_wrap_12 c2_outMiniBatchGroup[1];
  c2_cell_wrap_4 c2_b_r;
  emlrtStack c2_b_st;
  emlrtStack c2_c_st;
  emlrtStack c2_st;
  real_T c2_b_p;
  int32_T c2_c_p;
  int32_T c2_d_p;
  int32_T c2_i;
  int32_T c2_i1;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_p;
  real32_T c2_miniBatch[2];
  c2_st.prev = c2_sp;
  c2_st.tls = c2_sp->tls;
  c2_b_st.prev = &c2_st;
  c2_b_st.tls = c2_st.tls;
  c2_c_st.prev = &c2_b_st;
  c2_c_st.tls = c2_b_st.tls;
  for (c2_i = 0; c2_i < 172800; c2_i++) {
    c2_b_r.f1[c2_i] = c2_varargin_1[c2_i];
  }

  chartInstance->c2_dataInputs[0] = c2_b_r;
  for (c2_i1 = 0; c2_i1 < 172800; c2_i1++) {
    chartInstance->c2_dataInputsSingle[0].f1[c2_i1] = (real32_T)
      chartInstance->c2_dataInputs[0].f1[c2_i1];
  }

  for (c2_i2 = 0; c2_i2 < 172800; c2_i2++) {
    chartInstance->c2_inMiniBatch[c2_i2] = chartInstance->c2_dataInputsSingle[0]
      .f1[c2_i2];
  }

  for (c2_i3 = 0; c2_i3 < 172800; c2_i3++) {
    chartInstance->c2_dataInputsSingle[0].f1[c2_i3] =
      chartInstance->c2_inMiniBatch[c2_i3];
  }

  c2_st.site = &c2_f_emlrtRSI;
  for (c2_i4 = 0; c2_i4 < 172800; c2_i4++) {
    chartInstance->c2_inMiniBatch[c2_i4] = chartInstance->c2_dataInputsSingle[0]
      .f1[c2_i4];
  }

  c2_b_st.site = &c2_f_emlrtRSI;
  c2_c_st.site = &c2_g_emlrtRSI;
  for (c2_p = 0; c2_p < 3; c2_p++) {
    c2_b_p = 1.0 + (real_T)c2_p;
    if (c2_b_p != (real_T)(int32_T)muDoubleScalarFloor(c2_b_p)) {
      emlrtIntegerCheckR2012b(c2_b_p, &c2_emlrtDCI, &c2_c_st);
    }

    c2_i5 = (int32_T)c2_b_p;
    if ((c2_i5 < 1) || (c2_i5 > 3)) {
      emlrtDynamicBoundsCheckR2012b(c2_i5, 1, 3, &c2_b_emlrtBCI, &c2_c_st);
    }

    c2_c_p = c2_i5 - 1;
    for (c2_i8 = 0; c2_i8 < 320; c2_i8++) {
      for (c2_i10 = 0; c2_i10 < 180; c2_i10++) {
        chartInstance->c2_plane[c2_i10 + 180 * c2_i8] =
          chartInstance->c2_inMiniBatch[(c2_i10 + 180 * c2_i8) + 57600 * c2_c_p];
      }
    }

    if (c2_b_p != (real_T)(int32_T)muDoubleScalarFloor(c2_b_p)) {
      emlrtIntegerCheckR2012b(c2_b_p, &c2_emlrtDCI, &c2_c_st);
    }

    c2_i11 = (int32_T)c2_b_p;
    if ((c2_i11 < 1) || (c2_i11 > 3)) {
      emlrtDynamicBoundsCheckR2012b(c2_i11, 1, 3, &c2_emlrtBCI, &c2_c_st);
    }

    c2_d_p = c2_i11 - 1;
    for (c2_i12 = 0; c2_i12 < 180; c2_i12++) {
      for (c2_i13 = 0; c2_i13 < 320; c2_i13++) {
        chartInstance->c2_inMiniBatchGroup[0].f1[(c2_i13 + 320 * c2_i12) + 57600
          * c2_d_p] = chartInstance->c2_plane[c2_i12 + 180 * c2_i13];
      }
    }
  }

  c2_st.site = &c2_f_emlrtRSI;
  c2_b_obj = c2_obj;
  memcpy(c2_obj->getInputDataPointer(0), chartInstance->c2_inMiniBatchGroup[0].
         f1, c2_obj->getLayerOutputSize(0, 0));
  c2_obj->predict(chartInstance);
  memcpy(c2_outMiniBatchGroup[0].f1, c2_obj->getLayerOutput(25, 0),
         c2_obj->getLayerOutputSize(25, 0));
  c2_st.site = &c2_f_emlrtRSI;
  for (c2_i6 = 0; c2_i6 < 2; c2_i6++) {
    c2_miniBatch[c2_i6] = c2_outMiniBatchGroup[0].f1[c2_i6];
  }

  for (c2_i7 = 0; c2_i7 < 2; c2_i7++) {
    c2_outdata[0].f1[c2_i7] = c2_miniBatch[c2_i7];
  }

  for (c2_i9 = 0; c2_i9 < 2; c2_i9++) {
    c2_varargout_1[c2_i9] = c2_outdata[0].f1[c2_i9];
  }
}

static void c2_emlrt_marshallIn(SFc2_line_followerInstanceStruct *chartInstance,
  const mxArray *c2_b_out_1_predict, const char_T *c2_identifier, real32_T c2_y
  [2])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = const_cast<const char_T *>(c2_identifier);
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_out_1_predict),
                        &c2_thisId, c2_y);
  sf_mex_destroy(&c2_b_out_1_predict);
}

static void c2_b_emlrt_marshallIn(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId,
  real32_T c2_y[2])
{
  int32_T c2_i;
  real32_T c2_fv[2];
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_fv, 0, 1, 0U, 1, 0U, 2, 1, 2);
  for (c2_i = 0; c2_i < 2; c2_i++) {
    c2_y[c2_i] = c2_fv[c2_i];
  }

  sf_mex_destroy(&c2_u);
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_b_is_active_c2_line_follower, const char_T
  *c2_identifier)
{
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_y;
  c2_thisId.fIdentifier = const_cast<const char_T *>(c2_identifier);
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_line_follower), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_line_follower);
  return c2_y;
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_line_followerInstanceStruct
  *chartInstance, const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_u;
  uint8_T c2_y;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b_u, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_b_u;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_chart_data_browse_helper(SFc2_line_followerInstanceStruct
  *chartInstance, int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T
  *c2_isValueTooBig)
{
  *c2_mxData = NULL;
  *c2_mxData = NULL;
  *c2_isValueTooBig = 0U;
  switch (c2_ssIdNumber) {
   case 4U:
    *c2_isValueTooBig = 1U;
    break;

   case 5U:
    sf_mex_assign(c2_mxData, sf_mex_create("mxData",
      *chartInstance->c2_out_1_predict, 1, 0U, 1U, 0U, 2, 1, 2), false);
    break;
  }
}

void c2_mynet_new0_line_follower0::allocate()
{
  int32_T c2_idx;
  this->targetImpl->allocate(3, this->layers, this->numLayers, 0);
  for (c2_idx = 0; c2_idx < 26; c2_idx++) {
    this->layers[c2_idx]->allocate();
  }

  (static_cast<MWTensor<real32_T> *>(this->inputTensors[0]))->setData
    (this->layers[0]->getLayerOutput(0));
}

void c2_mynet_new0_line_follower0::postsetup()
{
  this->targetImpl->postSetup();
}

c2_mynet_new0_line_follower0::c2_mynet_new0_line_follower0()
{
  this->numLayers = 26;
  this->isInitialized = false;
  this->targetImpl = 0;
  this->layers[0] = new MWInputLayer;
  this->layers[0]->setName("data");
  this->layers[1] = new MWElementwiseAffineLayer;
  this->layers[1]->setName("data_normalization");
  this->layers[1]->setInPlaceIndex(0, 0);
  this->layers[2] = new MWFusedConvReLULayer;
  this->layers[2]->setName("conv1_conv1_relu");
  this->layers[3] = new MWMaxPoolingLayer;
  this->layers[3]->setName("pool1");
  this->layers[4] = new MWFusedConvReLULayer;
  this->layers[4]->setName("res2a_branch2a_res2a_branch2a_relu");
  this->layers[5] = new MWFusedConvReLULayer;
  this->layers[5]->setName("res2a_branch2b_res2a_relu");
  this->layers[5]->setInPlaceIndex(0, 1);
  this->layers[6] = new MWFusedConvReLULayer;
  this->layers[6]->setName("res2b_branch2a_res2b_branch2a_relu");
  this->layers[7] = new MWFusedConvReLULayer;
  this->layers[7]->setName("res2b_branch2b_res2b_relu");
  this->layers[7]->setInPlaceIndex(0, 1);
  this->layers[8] = new MWFusedConvReLULayer;
  this->layers[8]->setName("res3a_branch2a_res3a_branch2a_relu");
  this->layers[9] = new MWConvLayer;
  this->layers[9]->setName("res3a_branch1");
  this->layers[10] = new MWFusedConvReLULayer;
  this->layers[10]->setName("res3a_branch2b_res3a_relu");
  this->layers[10]->setInPlaceIndex(0, 1);
  this->layers[11] = new MWFusedConvReLULayer;
  this->layers[11]->setName("res3b_branch2a_res3b_branch2a_relu");
  this->layers[12] = new MWFusedConvReLULayer;
  this->layers[12]->setName("res3b_branch2b_res3b_relu");
  this->layers[12]->setInPlaceIndex(0, 1);
  this->layers[13] = new MWFusedConvReLULayer;
  this->layers[13]->setName("res4a_branch2a_res4a_branch2a_relu");
  this->layers[14] = new MWConvLayer;
  this->layers[14]->setName("res4a_branch1");
  this->layers[15] = new MWFusedConvReLULayer;
  this->layers[15]->setName("res4a_branch2b_res4a_relu");
  this->layers[15]->setInPlaceIndex(0, 1);
  this->layers[16] = new MWFusedConvReLULayer;
  this->layers[16]->setName("res4b_branch2a_res4b_branch2a_relu");
  this->layers[17] = new MWFusedConvReLULayer;
  this->layers[17]->setName("res4b_branch2b_res4b_relu");
  this->layers[17]->setInPlaceIndex(0, 1);
  this->layers[18] = new MWFusedConvReLULayer;
  this->layers[18]->setName("res5a_branch2a_res5a_branch2a_relu");
  this->layers[19] = new MWConvLayer;
  this->layers[19]->setName("res5a_branch1");
  this->layers[20] = new MWFusedConvReLULayer;
  this->layers[20]->setName("res5a_branch2b_res5a_relu");
  this->layers[20]->setInPlaceIndex(0, 1);
  this->layers[21] = new MWFusedConvReLULayer;
  this->layers[21]->setName("res5b_branch2a_res5b_branch2a_relu");
  this->layers[22] = new MWFusedConvReLULayer;
  this->layers[22]->setName("res5b_branch2b_res5b_relu");
  this->layers[22]->setInPlaceIndex(0, 1);
  this->layers[23] = new MWAvgPoolingLayer;
  this->layers[23]->setName("pool5");
  this->layers[24] = new MWFCLayer;
  this->layers[24]->setName("new_fc");
  this->layers[25] = new MWOutputLayer;
  this->layers[25]->setName("regressionoutput");
  this->layers[25]->setInPlaceIndex(0, 0);
  this->targetImpl = new MWTargetNetworkImpl;
  this->inputTensors[0] = new MWTensor<real32_T>;
  this->inputTensors[0]->setHeight(180);
  this->inputTensors[0]->setWidth(320);
  this->inputTensors[0]->setChannels(3);
  this->inputTensors[0]->setBatchSize(1);
  this->inputTensors[0]->setSequenceLength(1);
}

void c2_mynet_new0_line_follower0::deallocate()
{
  int32_T c2_idx;
  this->targetImpl->deallocate();
  for (c2_idx = 0; c2_idx < 26; c2_idx++) {
    this->layers[c2_idx]->deallocate();
  }
}

void c2_mynet_new0_line_follower0::setSize()
{
  int32_T c2_idx;
  for (c2_idx = 0; c2_idx < 26; c2_idx++) {
    this->layers[c2_idx]->propagateSize();
  }

  this->allocate();
  this->postsetup();
}

void c2_mynet_new0_line_follower0::resetState()
{
}

void c2_mynet_new0_line_follower0::setup()
{
  if (this->isInitialized) {
    this->resetState();
  } else {
    this->isInitialized = true;
    this->targetImpl->preSetup();
    (static_cast<MWInputLayer *>(this->layers[0]))->createInputLayer
      (this->targetImpl, this->inputTensors[0], 180, 320, 3, 0, "", 0);
    (static_cast<MWElementwiseAffineLayer *>(this->layers[1]))
      ->createElementwiseAffineLayer(this->targetImpl, this->layers[0]
      ->getOutputTensor(0), 1, 1, 3, 1, 1, 3, false, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_data_scale.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_data_offset.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[2]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[1]
      ->getOutputTensor(0), 7, 7, 3, 64, 2, 2, 3, 3, 3, 3, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_conv1_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_conv1_b.bin", 1);
    (static_cast<MWMaxPoolingLayer *>(this->layers[3]))->createMaxPoolingLayer<
      real32_T, real32_T>(this->targetImpl, this->layers[2]->getOutputTensor(0),
                          3, 3, 2, 2, 1, 1, 1, 1, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[4]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[3]
      ->getOutputTensor(0), 3, 3, 64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2a_branch2a_b.bin",
      1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[5]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[4]
      ->getOutputTensor(0), this->layers[3]->getOutputTensor(0), 3, 3, 64, 64, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[6]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[5]
      ->getOutputTensor(0), 3, 3, 64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2b_branch2a_b.bin",
      1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[7]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[6]
      ->getOutputTensor(0), this->layers[5]->getOutputTensor(0), 3, 3, 64, 64, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res2b_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[8]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[7]
      ->getOutputTensor(0), 3, 3, 64, 128, 2, 2, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3a_branch2a_b.bin",
      1);
    (static_cast<MWConvLayer *>(this->layers[9]))->createConvLayer
      (this->targetImpl, this->layers[7]->getOutputTensor(0), 1, 1, 64, 128, 2,
       2, 0, 0, 0, 0, 1, 1, 1,
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
       "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3a_branch1_w.bin",
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
       "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3a_branch1_b.bin",
       2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[10]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[8]
      ->getOutputTensor(0), this->layers[9]->getOutputTensor(0), 3, 3, 128, 128,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[11]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[10]
      ->getOutputTensor(0), 3, 3, 128, 128, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3b_branch2a_b.bin",
      0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[12]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[11]
      ->getOutputTensor(0), this->layers[10]->getOutputTensor(0), 3, 3, 128, 128,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res3b_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[13]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[12]
      ->getOutputTensor(0), 3, 3, 128, 256, 2, 2, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4a_branch2a_b.bin",
      0);
    (static_cast<MWConvLayer *>(this->layers[14]))->createConvLayer
      (this->targetImpl, this->layers[12]->getOutputTensor(0), 1, 1, 128, 256, 2,
       2, 0, 0, 0, 0, 1, 1, 1,
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
       "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4a_branch1_w.bin",
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
       "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4a_branch1_b.bin",
       1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[15]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[13]
      ->getOutputTensor(0), this->layers[14]->getOutputTensor(0), 3, 3, 256, 256,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[16]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[15]
      ->getOutputTensor(0), 3, 3, 256, 256, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4b_branch2a_b.bin",
      0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[17]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[16]
      ->getOutputTensor(0), this->layers[15]->getOutputTensor(0), 3, 3, 256, 256,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res4b_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[18]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[17]
      ->getOutputTensor(0), 3, 3, 256, 512, 2, 2, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5a_branch2a_b.bin",
      0);
    (static_cast<MWConvLayer *>(this->layers[19]))->createConvLayer
      (this->targetImpl, this->layers[17]->getOutputTensor(0), 1, 1, 256, 512, 2,
       2, 0, 0, 0, 0, 1, 1, 1,
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
       "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5a_branch1_w.bin",
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
       "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5a_branch1_b.bin",
       2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[20]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[18]
      ->getOutputTensor(0), this->layers[19]->getOutputTensor(0), 3, 3, 512, 512,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[21]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[20]
      ->getOutputTensor(0), 3, 3, 512, 512, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5b_branch2a_b.bin",
      0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[22]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[21]
      ->getOutputTensor(0), this->layers[20]->getOutputTensor(0), 3, 3, 512, 512,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_res5b_branch2b_b.bin",
      -1);
    (static_cast<MWAvgPoolingLayer *>(this->layers[23]))->createAvgPoolingLayer<
      real32_T, real32_T>(this->targetImpl, this->layers[22]->getOutputTensor(0),
                          -1, -1, 1, 1, 0, 0, 0, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFCLayer *>(this->layers[24]))->createFCLayer(this->targetImpl,
      this->layers[23]->getOutputTensor(0), 512, 2,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_new_fc_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\line_foll"
      "ower\\_self\\sfun\\src\\cnn_mynet_new0_line_follower0_new_fc_b.bin", 1);
    (static_cast<MWOutputLayer *>(this->layers[25]))->createOutputLayer
      (this->targetImpl, this->layers[24]->getOutputTensor(0), -1);
    this->outputTensors[0] = this->layers[25]->getOutputTensor(0);
    this->setSize();
  }
}

void c2_mynet_new0_line_follower0::predict(SFc2_line_followerInstanceStruct
  *chartInstance)
{
  int32_T c2_idx;
  for (c2_idx = 0; c2_idx < 26; c2_idx++) {
    this->layers[c2_idx]->predict();
  }
}

void c2_mynet_new0_line_follower0::cleanup()
{
  int32_T c2_idx;
  this->deallocate();
  for (c2_idx = 0; c2_idx < 26; c2_idx++) {
    this->layers[c2_idx]->cleanup();
  }

  if (this->targetImpl) {
    this->targetImpl->cleanup();
  }
}

real32_T *c2_mynet_new0_line_follower0::getLayerOutput(int32_T c2_layerIndex,
  int32_T c2_portIndex)
{
  return this->targetImpl->getLayerOutput(this->layers, c2_layerIndex,
    c2_portIndex);
}

int32_T c2_mynet_new0_line_follower0::getLayerOutputSize(int32_T c2_layerIndex,
  int32_T c2_portIndex)
{
  return this->layers[c2_layerIndex]->getOutputTensor(c2_portIndex)
    ->getNumElements() * sizeof(real32_T);
}

real32_T *c2_mynet_new0_line_follower0::getInputDataPointer(int32_T c2_index)
{
  return (static_cast<MWTensor<real32_T> *>(this->inputTensors[c2_index]))
    ->getData();
}

real32_T *c2_mynet_new0_line_follower0::getInputDataPointer()
{
  return (static_cast<MWTensor<real32_T> *>(this->inputTensors[0]))->getData();
}

real32_T *c2_mynet_new0_line_follower0::getOutputDataPointer(int32_T c2_index)
{
  return (static_cast<MWTensor<real32_T> *>(this->outputTensors[c2_index]))
    ->getData();
}

real32_T *c2_mynet_new0_line_follower0::getOutputDataPointer()
{
  return (static_cast<MWTensor<real32_T> *>(this->outputTensors[0]))->getData();
}

int32_T c2_mynet_new0_line_follower0::getBatchSize()
{
  return this->inputTensors[0]->getBatchSize();
}

c2_mynet_new0_line_follower0::~c2_mynet_new0_line_follower0()
{
  int32_T c2_idx;
  this->cleanup();
  for (c2_idx = 0; c2_idx < 26; c2_idx++) {
    delete this->layers[c2_idx];
  }

  if (this->targetImpl) {
    delete this->targetImpl;
  }

  delete this->inputTensors[0];
}

static void init_dsm_address_info(SFc2_line_followerInstanceStruct
  *chartInstance)
{
}

static void init_simulink_io_address(SFc2_line_followerInstanceStruct
  *chartInstance)
{
  chartInstance->c2_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_in_1 = (uint8_T (*)[172800])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_out_1_predict = (real32_T (*)[2])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c2_line_follower_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2109848502U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1491459499U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1823528010U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3261538637U);
}

mxArray *sf_c2_line_follower_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString("dltargets.mkldnn.mkldnnApi"));
  return(mxcell3p);
}

mxArray *sf_c2_line_follower_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("#__setup__");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_line_follower_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = sf_mex_decode(
    "eNrdmMtOwkAUhlujxg13kEtY8AQ+g4gSibQSlbBu6NA0lJmmM+Wy43FdunRpL1ymxwrBDclpMml"
    "mcjJ/vjmnc/5UUXuaEjzZYKwrinIdvG+CoSrxcyXNb6X1MP5LORx/AeLvpfjLlPisFJ/fzA3TfG"
    "e+NyZd2yE8Xlse0VWB7vMR3QrQDefaqD23Bow5NrX6xop4d2PX3ez3eSZu90Tu/+hqo46uS8CYe"
    "HNANxfzMjrfA4f7fJ+Jd30i7+CIbhPoNiPeJ4fMCBULm5P2ZGJTIpc3qnxngG4m4u924PeM5R6r"
    "Ad1azOtzYoZF/kb6wx06pjzngW4+4u5R1xcJXtz9SjOWf/QrLNwFoFuIuF99ISda2g93fX8Qypn"
    "3YHCyrW8sfasOdOtpfqw3cx2Qbyx1XgK6paRPSZBjynsL6LYO+JXtIeC/3zZ+JaXecfvU375FPg"
    "JMeS8D3TLwL5Ab9z0PfAziez7dx0l+RmLHxF0EusXEf4dkwjFxV4FuNfZxhmcRoROxYN50B4+/r"
    "2lTx6R0KGyHI+1rDaDbiOvc54LNolLvMk976T/q+v4AfgBpfmvj"
    );
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_line_follower(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiDmYGJgYAPRQMzEAAGsUD4jVIwRLs4CF1cA4pLKglSQeHFRsmcKkM5LzAXzE0s"
    "rPPPS8sHmWzAgzGfDYj4jkvmcUHEI+GBPmX4RB5B+ByT9LFj08yLpF4Dy80tL4g3jC4pSUzKTS6"
    "DhBAsv8t2j4ECZfoj9AQT8I4XmHxA/szg+Mbkksyw1PtkoPiczLzU+LT8nJ788tQhhLggAANVVH"
    "ik="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_line_follower_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "swhAJoC4LrjMqCtjOgF6MSG";
}

static void sf_opaque_initialize_c2_line_follower(void *chartInstanceVar)
{
  initialize_params_c2_line_follower((SFc2_line_followerInstanceStruct*)
    chartInstanceVar);
  initialize_c2_line_follower((SFc2_line_followerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c2_line_follower(void *chartInstanceVar)
{
  enable_c2_line_follower((SFc2_line_followerInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_line_follower(void *chartInstanceVar)
{
  disable_c2_line_follower((SFc2_line_followerInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_line_follower(void *chartInstanceVar)
{
  sf_gateway_c2_line_follower((SFc2_line_followerInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_line_follower(SimStruct* S)
{
  return get_sim_state_c2_line_follower((SFc2_line_followerInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_line_follower(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c2_line_follower((SFc2_line_followerInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c2_line_follower(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_line_followerInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_line_follower_optimization_info();
    }

    mdl_cleanup_runtime_resources_c2_line_follower
      ((SFc2_line_followerInstanceStruct*) chartInstanceVar);
    ((SFc2_line_followerInstanceStruct*) chartInstanceVar)->
      ~SFc2_line_followerInstanceStruct();
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c2_line_follower(void *chartInstanceVar)
{
  mdl_start_c2_line_follower((SFc2_line_followerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_mdl_terminate_c2_line_follower(void *chartInstanceVar)
{
  mdl_terminate_c2_line_follower((SFc2_line_followerInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_line_follower((SFc2_line_followerInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_line_follower(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  sf_warn_if_symbolic_dimension_param_changed(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_line_follower((SFc2_line_followerInstanceStruct*)
      sf_get_chart_instance_ptr(S));
    initSimStructsc2_line_follower((SFc2_line_followerInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c2_line_follower_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [26] = {
    "eNrtWEtv20YQpg03SIDG8KFAgKBAdWsPceHYUlH0kNqWrESFVRuVnVwEEEtyJK5N7jK7S8nqvcf",
    "+hN4D9NhLUSBBcnB/Q2+9t5cc21tnqYdlmpT8QAPLGwI0teTs7HzzzczO2pqr1S28FvEuPLKsW/",
    "i8jfe81b8+GIznxu7++wXr08H4R5zE4nCXCBJKa+LFSAjfgeRBrChnNdbimWKUtUAAc1E24kLla",
    "ZM0jAPKDqsxc7U++cynrt/weRx4mziXeDss6KG2KFa7qKdCBbiqCuApX/C47VcD0h5ZLFS37IN7",
    "KONwEgQJqhFH2ixZjwNFowC2jsCtMakIWixPbGsooqCsjnJhaqSyMRTkYRRQwjLR+kQ2IEIHK9i",
    "PPPy7EysElRZzfSLUJvikA3KbHiY6OYO0Tirxg0MZUVxQEmyFQVlPPGvbboD21LkHwQSHoG2bAs",
    "hhxClT+fw3qoh0ixEngAo4cTtfWwOex5r8pxS6IHL91irzDgjShh2Wu2jikK2jhK1RlJwVUzSEp",
    "0RsuMifBC83ejFyZIMgT7CHM/LEIAFZk3uCdtC9udrisKYjc1rKxGGfbDlNLNG21YFJLIy0VV1W",
    "JkEgc8X2eLQNHQgSrRWiyGSxvtZsOSmpt8fRwTq887MhZhSJH4iVOfNoJl2dlEBSd77FwnJa0o2",
    "l4mEZg7eyvX3281mxGlMgWsSFrCogCJWAPkvcm6/No1Jzj4JolUrMyxLuR8g0KUu2YlbpcnGIPp",
    "lQRE4gaEZzBUPZRi4xE/YlJs0kMc3lNDmXuD54usDQAOqYNiib4ROpS9sG5l2Hql4FpCtolMFqj",
    "FmHZWhLB1Qvgn12yHiXVQUPG4Ma33cvAEYbEYyy9ibWL9Gr4upZVOj9bMU62c8+PMd+NpyXfn42",
    "pmcuQ4819kyve2d+8rrz+GtuMG99bN7d1DoLqXlabgnvn/+998vxny9e/P2D9dv3q3/9dJX1f52",
    "/2P6/OBh/PCy0o8TpnIlXLftkzK6FDP33xvQvDcay6298w8vFbXFQf15WBzvt6hf1xuNE3+0p9s",
    "6n7B2+L+iKj1GWxKdwa96gMdFjEve3a63/yzF7b03xx53B+/719uurzf9oPR0PWf66m/KXHvNY2",
    "Q/tSIBHXZWK48vbU1i/2vz++rtT8NxP4bmf7PM20dUDbHfVxjoAdosHAR/1BYtXyLv382Z73pyB",
    "+M6zj73redY7nndVfBfdz6+b/MqEOmql5JeuMY6r9ln/t/wf1sX6oU8G40ejI0/Zp4GX0f0OPmM",
    "r28r6el35ejBZ/kFK/p8p+/3vqTjV4/JXzR0GFTw5w+hHYblQJ8p/hgch2WxgowleoUuVX8DDmO",
    "hxBs3k6MZI0MTzSIjHSNVrPqbqSew0CV0W3OGKunJZn6Skz6Om/tGUQSQOmrZs6cepzgJfQtBq6",
    "tNXE/vDpsuYHfYYKJtBd+V0F7JiC5Alx3YEYa6/Smznc4eyPv63U/C/TOF/OZP4Xc46D4ewzeW9",
    "aybvXRN5XyOZvE/D/yaF/81M4veIIjZvtSSoAffG1fvVUd47F8n71yn8r2eXf+mSADTy8+B+lcL",
    "9aiZx4zu75Y7v70bG+wX6mxvFe9dE3klmX2skfrP5dwzn37kI/8cp/Mcze74Z4jf0fLfqXKr+3U",
    "T+u6bzb2L+r10u/28ifuP/z2Hi/r9meP+zdrn+5+bgdwyPf8fs88+aY3j+O2aff4qG9z9Fw/ufo",
    "uH1r2h4/1c0fP8vkvfxb/L+XzS8/y8a3v8VHbP5Lxm+/5UMr/8lw+t/yfD6XzK8/pfO1v//AMb2",
    "bwI=",
    ""
  };

  static char newstr [1805] = "";
  newstr[0] = '\0';
  for (i = 0; i < 26; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c2_line_follower(SimStruct *S)
{
  const char* newstr = sf_c2_line_follower_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(3004692907U));
  ssSetChecksum1(S,(2829639621U));
  ssSetChecksum2(S,(3120596459U));
  ssSetChecksum3(S,(2649371258U));
}

static void mdlRTW_c2_line_follower(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c2_line_follower(SimStruct *S)
{
  SFc2_line_followerInstanceStruct *chartInstance;
  chartInstance = (SFc2_line_followerInstanceStruct *)utMalloc(sizeof
    (SFc2_line_followerInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_line_followerInstanceStruct));
  chartInstance = new (chartInstance) SFc2_line_followerInstanceStruct;
  chartInstance->chartInfo.chartInstance = chartInstance;
  if (ssGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME && ssGetOffsetTime(S, 0) ==
      0 && ssGetNumContStates(ssGetRootSS(S)) > 0 &&
      !supportsLegacyBehaviorForPersistentVarInContinuousTime(S)) {
    sf_error_out_about_continuous_sample_time_with_persistent_vars(S);
  }

  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_line_follower;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c2_line_follower;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c2_line_follower;
  chartInstance->chartInfo.mdlTerminate =
    sf_opaque_mdl_terminate_c2_line_follower;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c2_line_follower;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_line_follower;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_line_follower;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c2_line_follower;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c2_line_follower;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c2_line_follower;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_line_follower;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_line_follower;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->chartInfo.chartStateSetterFcn = NULL;
  chartInstance->chartInfo.chartStateGetterFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0,
    chartInstance->c2_JITStateAnimation,
    chartInstance->c2_JITTransitionAnimation);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c2_line_follower(chartInstance);
}

void c2_line_follower_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c2_line_follower(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_line_follower(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_line_follower(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_line_follower_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
