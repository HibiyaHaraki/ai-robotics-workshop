/* Include files */

#include "ros_line_follower_all_sfun.h"
#include "c3_ros_line_follower_all.h"
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
static emlrtRSInfo c3_emlrtRSI = { 2,  /* lineNo */
  "Controller/Deep Learning Based Regressor/Predict/MLFB",/* fcnName */
  "#ros_line_follower_all:3955:306"    /* pathName */
};

static emlrtRSInfo c3_b_emlrtRSI = { 1,/* lineNo */
  "deepNetwork",                       /* fcnName */
  "C:\\Program Files\\MATLAB\\R2021a\\toolbox\\nnet\\deep_blocks\\+deep\\+blocks\\+internal\\deepNetwork.p"/* pathName */
};

static emlrtRSInfo c3_c_emlrtRSI = { 69,/* lineNo */
  "loadDeepLearningNetwork",           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2021a\\toolbox\\shared\\coder\\coder\\lib\\+coder\\loadDeepLearningNetwork.m"/* pathName */
};

static emlrtRSInfo c3_d_emlrtRSI = { 1,/* lineNo */
  "loadDeepLearningNetwork",           /* fcnName */
  "C:\\Program Files\\MATLAB\\R2021a\\toolbox\\shared\\dlcoder_base\\dlcoder_base\\+coder\\+internal\\loadDeepLearningNetwork.p"/* pathName */
};

static emlrtRSInfo c3_e_emlrtRSI = { 1,/* lineNo */
  "DeepLearningNetwork",               /* fcnName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@DeepLearningN"
  "etwork\\DeepLearningNetwork.p"      /* pathName */
};

static emlrtRSInfo c3_f_emlrtRSI = { 1,/* lineNo */
  "predict",                           /* fcnName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@DeepLearningN"
  "etwork\\predict.p"                  /* pathName */
};

static emlrtRSInfo c3_g_emlrtRSI = { 1,/* lineNo */
  "permuteImageInput",                 /* fcnName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\+internal\\+ioh"
  "andling\\+cnn\\@InputDataPreparer\\permuteImageInput.p"/* pathName */
};

static emlrtBCInfo c3_emlrtBCI = { 1,  /* iFirst */
  3,                                   /* iLast */
  1,                                   /* lineNo */
  1,                                   /* colNo */
  "",                                  /* aName */
  "transposeHWDims",                   /* fName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@coderNetworkU"
  "tils\\transposeHWDims.p",           /* pName */
  3                                    /* checkKind */
};

static emlrtDCInfo c3_emlrtDCI = { 1,  /* lineNo */
  1,                                   /* colNo */
  "transposeHWDims",                   /* fName */
  "C:\\ProgramData\\MATLAB\\SupportPackages\\R2021a\\toolbox\\shared\\dlcoder_base\\supportpackages\\shared_dl_targets\\+coder\\@coderNetworkU"
  "tils\\transposeHWDims.p",           /* pName */
  1                                    /* checkKind */
};

static emlrtBCInfo c3_b_emlrtBCI = { 1,/* iFirst */
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
static void initialize_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void initialize_params_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void enable_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void disable_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void c3_update_jit_animation_state_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void c3_do_animation_call_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void ext_mode_exec_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static const mxArray *get_sim_state_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void set_sim_state_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance, const mxArray *c3_st);
static void sf_gateway_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void mdl_start_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void mdl_terminate_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void mdl_cleanup_runtime_resources_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void initSimStructsc3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance);
static void c3_DeepLearningNetwork_setup
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance,
   c3_mynet_new0_ros_line_follower_all0 *c3_obj);
static void c3_DeepLearningNetwork_predict
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance, const emlrtStack
   *c3_sp, c3_mynet_new0_ros_line_follower_all0 *c3_obj, uint8_T c3_varargin_1
   [172800], real32_T c3_varargout_1[2]);
static void c3_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_b_out_1_predict, const char_T *c3_identifier,
  real32_T c3_y[2]);
static void c3_b_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real32_T c3_y[2]);
static uint8_T c3_c_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_ros_line_follower_all, const
  char_T *c3_identifier);
static uint8_T c3_d_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_chart_data_browse_helper(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, int32_T c3_ssIdNumber, const mxArray **c3_mxData, uint8_T
  *c3_isValueTooBig);
static void init_dsm_address_info(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  emlrtStack c3_st = { NULL,           /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  c3_st.tls = chartInstance->c3_fEmlrtCtx;
  emlrtLicenseCheckR2012b(&c3_st, (const char_T *)"neural_network_toolbox", 2);
  sim_mode_is_external(chartInstance->S);
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_network_not_empty = false;
  chartInstance->c3_is_active_c3_ros_line_follower_all = 0U;
}

static void initialize_params_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
}

static void enable_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_jit_animation_state_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
}

static void c3_do_animation_call_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  sfDoAnimationWrapper(chartInstance->S, false, true);
  sfDoAnimationWrapper(chartInstance->S, false, false);
}

static void ext_mode_exec_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
}

static const mxArray *get_sim_state_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  const mxArray *c3_b_y = NULL;
  const mxArray *c3_c_y = NULL;
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(2, 1), false);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", *chartInstance->c3_out_1_predict, 1,
    0U, 1U, 0U, 2, 1, 2), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y",
    &chartInstance->c3_is_active_c3_ros_line_follower_all, 3, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  int32_T c3_i;
  real32_T c3_fv[2];
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_u = sf_mex_dup(c3_st);
  c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                      "out_1_predict", c3_fv);
  for (c3_i = 0; c3_i < 2; c3_i++) {
    (*chartInstance->c3_out_1_predict)[c3_i] = c3_fv[c3_i];
  }

  chartInstance->c3_is_active_c3_ros_line_follower_all = c3_c_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
     "is_active_c3_ros_line_follower_all");
  sf_mex_destroy(&c3_u);
  sf_mex_destroy(&c3_st);
}

static void sf_gateway_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  c3_mynet_new0_ros_line_follower_all0 *c3_b_iobj_0;
  c3_mynet_new0_ros_line_follower_all0 *c3_iobj_0;
  c3_mynet_new0_ros_line_follower_all0 *c3_net;
  c3_mynet_new0_ros_line_follower_all0 *c3_obj;
  c3_mynet_new0_ros_line_follower_all0 *c3_this;
  emlrtStack c3_b_st;
  emlrtStack c3_c_st;
  emlrtStack c3_st = { NULL,           /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  int32_T c3_i;
  int32_T c3_i1;
  int32_T c3_i2;
  int32_T c3_i3;
  real32_T c3_fv[2];
  c3_st.tls = chartInstance->c3_fEmlrtCtx;
  c3_b_st.prev = &c3_st;
  c3_b_st.tls = c3_st.tls;
  c3_c_st.prev = &c3_b_st;
  c3_c_st.tls = c3_b_st.tls;
  chartInstance->c3_JITTransitionAnimation[0] = 0U;
  _sfTime_ = sf_get_time(chartInstance->S);
  for (c3_i = 0; c3_i < 172800; c3_i++) {
    covrtSigUpdateFcn(chartInstance->c3_covrtInstance, 0U, (real_T)
                      (*chartInstance->c3_in_1)[c3_i]);
  }

  chartInstance->c3_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c3_covrtInstance, 4U, 0, 0);
  for (c3_i1 = 0; c3_i1 < 172800; c3_i1++) {
    chartInstance->c3_r.f1[c3_i1] = (*chartInstance->c3_in_1)[c3_i1];
  }

  chartInstance->c3_inputs[0] = chartInstance->c3_r;
  c3_b_st.site = &c3_emlrtRSI;
  if (!chartInstance->c3_network_not_empty) {
    c3_c_st.site = &c3_b_emlrtRSI;
    c3_iobj_0 = &chartInstance->c3_network;
    c3_b_iobj_0 = c3_iobj_0;
    c3_obj = c3_b_iobj_0;
    c3_net = c3_obj;
    c3_this = c3_net;
    c3_net = c3_this;
    c3_DeepLearningNetwork_setup(chartInstance, c3_net);
    chartInstance->c3_network_not_empty = true;
  }

  c3_c_st.site = &c3_b_emlrtRSI;
  c3_DeepLearningNetwork_predict(chartInstance, &c3_c_st,
    &chartInstance->c3_network, chartInstance->c3_inputs[0].f1, c3_fv);
  for (c3_i2 = 0; c3_i2 < 2; c3_i2++) {
    (*chartInstance->c3_out_1_predict)[c3_i2] = c3_fv[c3_i2];
  }

  c3_do_animation_call_c3_ros_line_follower_all(chartInstance);
  for (c3_i3 = 0; c3_i3 < 2; c3_i3++) {
    covrtSigUpdateFcn(chartInstance->c3_covrtInstance, 1U, (real_T)
                      (*chartInstance->c3_out_1_predict)[c3_i3]);
  }
}

static void mdl_start_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
}

static void mdl_terminate_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
}

static void mdl_setup_runtime_resources_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  static const uint32_T c3_decisionTxtEndIdx = 0U;
  static const uint32_T c3_decisionTxtStartIdx = 0U;
  setLegacyDebuggerFlag(chartInstance->S, false);
  setDebuggerFlag(chartInstance->S, true);
  setDataBrowseFcn(chartInstance->S, (void *)&c3_chart_data_browse_helper);
  chartInstance->c3_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c3_RuntimeVar,
    &chartInstance->c3_IsDebuggerActive,
    &chartInstance->c3_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c3_mlFcnLineNumber, &chartInstance->c3_IsHeatMapPresent, 0);
  sim_mode_is_external(chartInstance->S);
  covrtCreateStateflowInstanceData(chartInstance->c3_covrtInstance, 1U, 0U, 1U,
    10U);
  covrtChartInitFcn(chartInstance->c3_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c3_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c3_decisionTxtStartIdx, &c3_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c3_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c3_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c3_covrtInstance, 4U, 0U, 0U,
                     "eML_blk_kernel", 0, -1, 274);
}

static void mdl_cleanup_runtime_resources_c3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c3_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c3_covrtInstance);
}

static void initSimStructsc3_ros_line_follower_all
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
}

const mxArray *sf_c3_ros_line_follower_all_get_eml_resolved_functions_info()
{
  const mxArray *c3_nameCaptureInfo = NULL;
  const char_T *c3_data[48] = {
    "789ced9ddb8f23d95dc7bdd1aed82cecee2410b2c9c26ab2ec0362b543b7db7d719ee2fbddedbbdbbd1d6d97cbc776d975ebbaf826245a3ced0b0221e5b22488"
    "11899480109015111029228817f807802794071609e51fc80b88b2ab4e4fb9dbeef274d5d41c9ffefda45d4ff9d75de777cea9fe7eeadc032f640a2f040281d7",
    "02a67d78faa9c5e7abc67f6f1aff3db0beff5460d9aefb5fb03edbb6eb376d3fff52e0c5abdfb3fffc1f589fac246a68a299172223a0abdfec48022732a2569b"
    "ca28a02055e247a8b3f074391ed5380155ed17c5f99590b4b9ae2ee6aef9bf637dc40eabba1050faea930879fbc55579fc8b2dbf015b7e5fdcb03c90edda5e1e",
    "0faef9dfcf9c24befa8ec0683cd35624497be74c9324be2d4dced43ea3a0ce598767a50e523e68332a5abe7877f1efb37739a3041591e1cf7889e9c41192f388"
    "51444eec1591369694e123d996af89cb7cfdb243beb07f451c8bef711c972ee3f882431cd8bf28a347eba279120fbef15de379ec100ff6bf9f897d35f6e5b392",
    "22f5144688331a735688d4f291e85955976549d14a0c3b647a483dab047782bbccad8f836afe8a8c7fc5fc990f3afc071aa3f490a6e267e42b2b0ae06ce5a382"
    "cbe3dc965f7b3e5edfb03cec9f6f2efdfccb8103e3cbb73ef9b7c58ff895dee54b6f7fe2677ad89e577a6effce7f754d7a0faef95b279360440b2627b966afaf",
    "46477b87f5133df6248ed29a386c21df1a47c0766d8fc3affbd3ca01d965be5eb35dafca17f6ab48b3922f2ee00efa0ffa0ffa0ffa0ffabfecdf36fdffb443be"
    "b09f6578be8a341da707fa0ffa0ffa0ffa0ffabfecf75bffcf5de6eba5b5f9323daaa5f9a0f7a0f7a0f7a0f7a0f7cbfe6d7bdf7fdd76bd2a5fd83f7fdfafcb1d",
    "464355cdf81fe83fe83fe8bf0fe981fe7b737fd07f77fdfd73fdaf20e3eddf947fd07fd07fd07f1fd203fdf7e6fea0ffabf3f58b0ef9c27eabbfbfcacdcc9c82"
    "fe83fe83fe83fe83fe2ffbb76ddee7671cf285fdb2826423fe0662354999cb9df53d700038001c000e000796fd7e73e04397f9fa9243beb0dfcc51cc88b087c4",
    "a2246abac8b47964e89f8c148d4378cd057001b8005c002e001796fddbc685df74c817f62f71a13089280a335d8507e0027001b8005c002e2cfbb76ddce055db"
    "f5aa7c617fef6a9dd8717b10807601e83fe8bf1fe981fe7b737fd0ffd5f97ac5215fd86fa850e678fefa6f750c81fe83fe83fe83fe83fe2ffbb76ddcf8f30ef9",
    "c27e76be37535252aae84247228bb0fa02078003c001e0007060d9bf6ded00fbf5aa7ce1cf27ed000306956211f41ff41ff41ff41ff47fd9bf6dfabfe938c0d8"
    "082123caba16517a6a00fa8140ff41fffd480ff4df9bfb83feafced7a6ebc7c60a231718ed6ae500e83fe83fe83fe83fe8ffb2df6ffdbf7499af2f3ae40bfb47",
    "0ccfcd770fb262484a4a8c675495eb4e4d3ff00078003c001e000f96fddbd61ed8b43fc850a10500e6a707407f10e83fe8bf3fe981fe7b737f5af5ffd265be36"
    "6d0f2cad17cb4b63a4d4a4aaa6e8ac75641cf00078003c001e000f96fddbc6834df5d7da5f6831443cdf646e3e4d2886460c6ff98107c003e001f00078b0ecdf",
    "b6fea14dd78d29b6bda6030172f5ffe72ee3f9a6433cd8ff7ee69818003ca91bd07dd07dd33eb726bd07d7fcc9e0803d2a860f84ddbd7635193ed63ae5fe7100"
    "749f74ddf7ebbd80b546852362c77edc0cb1faffb2cbf7ffef3ac483fd24e9ffea3a5a3c2ebee957e9c73ef3e03bbff3377ea6876d5b79b0e9df7bb7d82f857a",
    "c9d3e964ac0c92b144adb0db2dc68107b4f360d3f705d9889d63b5eb38a09607df718807fb49e2c1ca3a3271402d0f025ffedc0f7c4dcf32da79c0f5f6f47c21"
    "7ca135f45c727a945750b1d24f020f48e7c1b9cb7cbdbc365fa607bf7392aafb6efb81beee100ff693a4fbb84ee60f02ad3a0feffda679adf3457118cbe67aa5",
    "da714d1ced448e261539534e81ce93aef36efbff375d2fc6b01a3762344e12cd8de348d57d7ce3bbc6f391433cd84f92eedbeae6117e1e68d5ffc0abfff5d7be"
    "a66719edfa3f68cff893dc51b4191a073b27622392d9cf2118ff255effcf5de6eb17d6e6cbf4587d09c4eabddbf7fcaf39c483fd24e9bd55271b3d075babf3d0",
    "9fb330af755ecdec2899c34ab13608f78acdf8b8289e9c6851d079d275fed265be365d07303f57b864eacb7cc6a7ae6a929067a648217cbf68b7fdfcdf778807"
    "fb49e2c0fabaf26f1ed05ffe9fcffd3f1ff3bfe7677ad868e782ae370a9c124a1f0df726b1593c2c8f138707d0ff433c17fc3a6fd8d6c7606e186a7d4f2a0fdc",
    "f603fda9433cd84f120f6ed491f1a450db3e807ea08579cd019e6f67b8542d3b0937c61d4e55c7628cd78003c001eb73596362c001eb935c0ec47ce500ac0b78"
    "b6e9f9c581836832a7f2a5508f1d45c5667237a1d7072acc03050e589fcb7d0fd01e20910337ea88e2f600cc0b32cd6b0e24e4516c6f6f22e443492d32a9a4fa",
    "fb9dd438011c209d03e72ef3e534ff13ef1f4aaadedfc7f99fb84efc9cff09effbcf363dbf745e6ee4a6b541ff382b8483e8a01e2dd6eb3c03f37f88d779d965"
    "be3eed902fec57911611d9bea458d7b4eafe371ce2c17e9274ffaa6e287ebf87f940a679aefbd95e45da6b0842679a8de578253aebe94dd07de275ff4397f97a",
    "c7215fd82f4baa66681c8b54f558d7645dab4915a4e98a18335e347b92c2b1e69670a4f2e00d97fd3e1f3bc483fd24f160933ac30b0580171ea56719edbc1022"
    "b5d9acad8ef60f07996a4fe81df413c71af407012fac4f6bdfd00662354931d4a7ca08328f929212595e4006bc2088171bd419f0c2e3f42cdb565e6cba5f4cbf",
    "3a6a4f0b21b59239698df5c851bfbedb9c058017b4f3e2371cf285fd789f69c1d0ad5b70412d2f7ee0100ff613c88bdbea8cfe75c8c08b8579ddbec8a98799e3"
    "837c9411d571a4556c6a9171ba98065e90ce0bb7cfc7af38e40bfb2deda9148b31c4f366f74620402e1fdcae4bfb338778b09f403e2cd511b41f3c4ecf32da79",
    "90488cc5d0e1f0303ba8ef742a7c982f75fb1d189fa09e071b8f5f995a53e044aecd686c1f4f46a59507dbb83ff5ea3aa27b7f6ae081695effbda7dae3703076"
    "d1a98fd2896ab59d9c14e3f51d5897403c0f707fc05df3f5aaed7a55beb05fbeb62681540ee01bdf359e6f39c483fd847160692d82bd3cce6df9b5e703f47fc3",
    "f42ca35dffb970baaba59baa9ccc2a9dbd5268b69f2cc3f833f9faefd778d37ccd5364c55e15a472e03e9e4fb0b28e28e701ac4f33cd6b1e1cd785f6a4ce5455"
    "f964d2be500e504caf8c603f3be279e0b63df09aed7a55beb07f596bc8e580dbf6c0b71de2c17e723940797f10ec57b430aff53f561894db6d55086543b34927",
    "df66429a9484f162eaf57fd3730b6c7b202cae69d5ff6d3cb7c05637d4cf1782f77fd3bcd6ff5029c476f7fbfba76a5bdae30ea7a17ee208d62dd3afffafdbae"
    "57e50bfb55a459c957b91952a9d5ff3f718807fb49d2ff6b7503e71978999e65b4eb7f32d6e4d9836032b6cf4903411e1e29854908c60388d77fb7cfc7671df2",
    "85fd86c6644459d7e60a63dfa88e560e3c768807fb09e3c0b53af2effc02e0c0b34dcf2f0eb44e2aa7913d26d83e081fe70ebbf99dc35cf200da01c473c0bf75"
    "c98bfd10ec3ab36a9898582edccf75c9ce7506eb0a3c4ecf32da79512a176bcd49282e0a4db1703a49b6c249bd01e71c10cf8b4b97f97ae8902fec5fa13d4b5b",
    "2993ca89072e39f1570ef1603fe19cb8beed35f0c1abf42cdb563e6c3a8f307a9ae5625a3d76c03009a6783adb39cc203d007c209d0f6ec7157ec9215fd82f33"
    "8a8a6c124c2a0fdcf627fdb1433cd84f140f6c7503ed038fd3b38c76fd2ff53b27dd71888b1df247fd51f5e23475983e0a80fe93aeff972ef3f5d0215fd8bfd0",
    "98c51ba71a33c2ec21d1d63501ed03f278704b5dd1dc3e807947a679dd7f542bcfb47681898c62897d213a9cb0e5c23182fe23e083f579abe6c4800f5bc38718"
    "f0c1cbf4b0d1ce879daeaeec8fe57e2f5dcc4433e5ac900b2b3c8c4753cf875f73c817f6dfd41cabcb3a46f638b45b3efc85433cd84f361f9ed415edfd4bc007",
    "d3bce6c341a1563e6a25f393295bdeef08cc8019d77958b70c7cb03ed76a0ee1f394800fcb75453b1f60fcc134cff7c18ef0a9ea387aa0edef74332da5c037f5"
    "38ec7b4a3e1ffc1a9f3244c91e4a4c12bb5c2f402e17eee33e472beb08f639f2343d6cb4f3e0400ec74b855c5f1738fd3053381e84b46217f6b9209e07972ef3",
    "e5b50e9fbb8ce745dbf5723ca687354ad19e1efec5bba6f7786d7acbfef733c4c8feca47c22f7d7aeb139ff5fea5b73ff1333d6cb4eb7deb64128c68c1e424d7"
    "ecf5d5e868efb07ea253f4fe0fbab0ac0b6e9fabcf389407f62fe2b352af6b1caf5adf7b15c7e71de2c07e935737a3f1eaf9d87c3fbce7f27cdcc8f8d98d6ffc",
    "dd0fef3f7ee63337fee77b477ea6878d766e546a0cca642ae572bb588b17b29d9cd2edd034ae00dc58e6c6a52dbf77298f5f77280fec5ff471cf7bb795bcd1ea"
    "b1c268308a113f2706c8e387db71883f778803fb9f577fd34d80dc5a43f4efaff7bffff9b19fe961a39d27f1bd60b7179a888de269a41a140e7aa9ae96867608",
    "b53cc13a71d7f2b05faf2a0ffc294bb2ce331a9a97446d2a23d2f8e15ffb83187e5cab11baf7e3065e98e6f5b824d3caa0716d82a2b3cc486f4b07b296d38b01"
    "e005adbcf0eddc67a408ba8662c56203b19aa4cc4b64fe3d6ddc78ec1007f613c48d153543ef7847e0db3f82f18e80f7ed8c9e2af74ef7874262aa5cc4bbd359",
    "2a5d49b114ada7036e78dbced874ff6f4d6144559654946ec63941a58e17df728803fbc9e1c5b51aa17d3e14b43316e6352f764b8d309ab67bbbc36ea699502e"
    "623a2fce283a071a78e1ed38c79bb6eb55e581bfe3d498ae6a9210cd47aa3186e7db465e1222d3e65167e1278d1f6ee7d57ecf210eec27871fb7d490c112182f",
    "f7263d6cb473841f69a57e79101af6c682388a4fcb95ee780ae31bd472c4af7607a716d0643e1a6badcc208d1bf7afdd71ad467c6e77002f9e6d7a7ef1225c6b"
    "a029979067d37a319b6d27b307c5468aa2f3868017cf8b17c732120b25dcd6005e3c7f5e2cd508f453799a1e36da7911eb68d1d874b09b3b9a9d0e63533e9ee5",
    "1501da17d4f2c2aff17005f53855434a1c1922d54122cba1c5520edab8f1d8210eec27871bab6a06c6c3811ba66d3a8f8a93763b794ee3064a26c789033d92ce"
    "1def05801bc08dd5e5b1e9fa3f23cada22563ccdd3fa9e366e907e1ef64d6edca819aacfc386f686695eb737aa8a50ace7a5bde8613c120c26cad3f26eb806f3",
    "a8a8e586dbfea94dcf3bba52a73cd79e5f93c68b9fbb8ce39b0e71603f81bc306a84def3b28113a679beae2fa11db117b341afd48d57c6a25e65324a09d68903"
    "27d69487fd7a5579e04fb68fd8615252aa9ca0f39c38248d136e9f8bed5bd777bd46605d9f97e961a39d1727e58b412b8422cd504b190bb3b8aee9a914ccb705",
    "5eac298f576dd7abca03fb8d28eb2277a1a32223ccfba268e3c5470e71603f39bc58aa11d837c4e3f4b0d1ce0b7e905077959638298d772be104d3e34eb56e12"
    "7801bc585d1eaf389407f61b51968c2c1475c1bc268d176efba1beee1007f613c50bab46a83e270f38b130af39912ec52665e1a2dfcf3579d415f3cd74a51781",
    "f10ae0c49af2780a4ee499295232e6b23de004099cb06a0438019c785a4e8cc3c148313fad36fb484969d556674f5134e87f024eac298fa7e87f325549eca0f9"
    "b34c1a27ee65ffd3931a81fe278fd3c3463b2fca2536ba2735f85822250bcab0ac8e66a755e87fa296177ee9b51165d5c802ea648eb14a712c226f5f29dacfdb",
    "5bc98d553503ebf63c4d0f1bedfce087a7bd42642787caba50cd31fbbb6a757008ed0d6af97169cbef5dcae32d87f2c0fe11c3731d464305464b723c8a889d06"
    "a370f315c6e60038691ca1fd3cef9b1cb9bd86683fcf1b78629ae7f36dbb5a64efb83aea0f83ed93e0eca03e9ba2118c7350cb13b7cfd51b0ee581fd8bd99d86",
    "46358d3892929266f86e4694758d348eb86d8f7cd7210eec278723eb6a06e6df7a991e36daf991aeb0d141869fc58fda9d4a998db26a365b027e003fd6948757"
    "ba7d7ec738aedbba38b0f9bf3e83144c5cff06ce7df5323d6cb4f381f6735fcfd7dcff59e910ede9fdf48ee9e1fa9a39a487fdefd7e7327b2ca2b8c28dd0d53f",
    "1ebef7b0c068fda6217aea597521970fc79cd67f981821652a89e82c236a481119fe2c2609822e72daf42cc56969bd7dc670ef29525bd238567d6fae9a6a5f92"
    "cf164415a622d23e10d1f891c068cbf93d5f935faffeee7f1afb775f75547ee51bffec677ad868d7d1818a725c962d7476f7f747834164506e35758a74d4bff7",
    "6c52dae1b7efc706efd94f971ebc67c37bf67de603edefd9c087653e5cdaf27b97f2f8a24379607f87b7227d240cf98e285a1f119933fdcf8b136ed729fc9143"
    "7ad8ff4c3961b40678a66dfe80fd99b82af4b377cde23ebb2a75bfc7799b7ef7d3ffeeef7fe4677ad868e7433f33e54ff848aed73bdc3dd94f0f95b896685374",
    "3e845b3df8da9afb3fb8e67f5e7c58d5512f1b3fcbb1dad27e9c972ecbe10b0ee580fd66bb614554967f5bdb0f8f1dd2c3fe6d19af39b7e5d79e8f6dddd7fbf2"
    "a5b7615fef80f77c689d4c82112d989ce49abdbe1a1ded1dd64f748ace83003e98e6d77ede8b2925f3dc9714241b412bd6f7388e3f7419c76f3bc481fd26a738",
    "abd3fe1127f519b1c31b85f488351a3337a3c4f1bde192237fe7101ff63f1f8ebc8b0bc4f8d75589184ea3a5f1951b657276e31b1fcf33f57d9ed06f3df85b3f"
    "d3c3463b5faa899dfe4e76cc3372971df6eb124a1e1427c017e0cbb572d8942f6d4663fb25a673a54dd6f7f7852f7fef101ff63fa7e7e5e90073a33229de371c",
    "f8b230cff7e1e8ee57d1055f4e44775a99e37e70d2ec0d548ae6a1025f4cf38b2f3252045d4319c1887b214bd6f7c09765ff56f0e54665d2db3f16f8d79ffdb7"
    "afe959463b5fd431abf107b19ed2a8d67b7c2d36dc67f3398af6ed00be9826bb2c87d76cd7abca01fb17abb0165a54e566e8fe70e5870ef161ff567065b912e9",
    "3e170fda2d0bf3fa3cd55e6bd62f144fdae34a765a49336ca62fb48201e00a6d5cb974590e1b8fcb5f49929a949406a34c8dc04cc42c6c5b38f3d025677ee210"
    "1ff66f1967ae552af493016f4cdbb41d53bae0a34253082bb5bd9d692317eaecb5fa87300f8c3adef8d58e31044a45d08eb911df56b563962b11da311ea6878d",
    "76aea8a57894db498d23fdd92e77116c84eb5df914c6f7a9e30ae9ba7e7ec7f8aedbbaf8b0c13c319827e6677ad868e708cc13bbfdfeb47004d6b73f5d7a38df"
    "b0be7db93c9c740cd6b73fdbf4607dbb37f7f7ef3d32410a1656ae5bfb1267bd3c2e5e260b9cc82d268742fbe39a1fda1fd0fef0333d6cb47386f6f607cc0bdd",
    "6c5e28b44f9e2e3d689f40fbe43e7303da27b7dfffbeb44f801b4f971e7003b801dca0971b6e7581f473a25781836578be641bf3b09787dbe7eab30ee581fdc7"
    "bab6720316affad1761ce2c0fedbfbd16e46e9d5fcdf7f70880ffbc9ebd7ba59266737bfa2fffcf166e4877ea6878d76dee899f4449273e5494a2a1d29b97c43",
    "8f472b69e00df0c65d7bc408d254a9f90cd2a4a458f1dc1bdefca3437cd84f60bfe80ae0aca94d9ac75380370bf37a7de3695ce876cb9c9c40113409efa5b95e"
    "eaa21e00de006fdc3d57d7152acf4c174d9cfbc29b1f3bc487fddbc99b456dd2bd0e0578b330af7521c41f245b2a5f16bb7c4caf575bf19d5da51c00ded0ca1b",
    "7c7dd7f278d576bdaa3cb07f49a102dbc3997bbcced18933c0170fd3c3b6ad7cd9b4ff8c4d56b5bc9491e3cdfc20da8d4a4a2f344ec1780db57c71fb5cbde150"
    "1ed86f04194323866f205693942722b52d9c71db9ef989437cd8bf359c59599bf4eed712f8a7efc37ce480f7bcc937daf9dd5e2bdf3c0c25877a38926a8b6a8b",
    "a27d278137cbe5e1e378cd42a116739f6d2d9bfbc21beac66b56d526c5e335c01bd3bce64d56914f7227ed534e884c87d96c625866da3d8af60703de2c97875f"
    "f3d1ec4b6d4c815a8e8376defcc8213eecdf0ededcac4dbfcf25867df59f6d7a7e8dd7ecec77e3e9e370aed54e5553f546a7508814a301e00dadbc215de7cfef",
    "18df755b171f3698e70cf39c619ce6d9b563689fe7ecdf3afe2d598f696ac7d5824ce0cdb2016f8037c01be0cd5def0ffd1f4fd7ff01fb003c5d7a38dfb00fc0"
    "727938e91dec03f06cd3837d00bcb93fb457366baf00379e2e3de0067003b8411f37fe1fbf5eb08c",
    "" };

  c3_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&c3_data[0], 154272U, &c3_nameCaptureInfo);
  return c3_nameCaptureInfo;
}

static void c3_DeepLearningNetwork_setup
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance,
   c3_mynet_new0_ros_line_follower_all0 *c3_obj)
{
  c3_mynet_new0_ros_line_follower_all0 *c3_b_obj;
  c3_obj->setup();
}

static void c3_DeepLearningNetwork_predict
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance, const emlrtStack
   *c3_sp, c3_mynet_new0_ros_line_follower_all0 *c3_obj, uint8_T c3_varargin_1
   [172800], real32_T c3_varargout_1[2])
{
  c3_mynet_new0_ros_line_follower_all0 *c3_b_obj;
  c3_cell_wrap_10 c3_outdata[1];
  c3_cell_wrap_12 c3_outMiniBatchGroup[1];
  c3_cell_wrap_4 c3_b_r;
  emlrtStack c3_b_st;
  emlrtStack c3_c_st;
  emlrtStack c3_st;
  real_T c3_b_p;
  int32_T c3_c_p;
  int32_T c3_d_p;
  int32_T c3_i;
  int32_T c3_i1;
  int32_T c3_i10;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  int32_T c3_i2;
  int32_T c3_i3;
  int32_T c3_i4;
  int32_T c3_i5;
  int32_T c3_i6;
  int32_T c3_i7;
  int32_T c3_i8;
  int32_T c3_i9;
  int32_T c3_p;
  real32_T c3_miniBatch[2];
  c3_st.prev = c3_sp;
  c3_st.tls = c3_sp->tls;
  c3_b_st.prev = &c3_st;
  c3_b_st.tls = c3_st.tls;
  c3_c_st.prev = &c3_b_st;
  c3_c_st.tls = c3_b_st.tls;
  for (c3_i = 0; c3_i < 172800; c3_i++) {
    c3_b_r.f1[c3_i] = c3_varargin_1[c3_i];
  }

  chartInstance->c3_dataInputs[0] = c3_b_r;
  for (c3_i1 = 0; c3_i1 < 172800; c3_i1++) {
    chartInstance->c3_dataInputsSingle[0].f1[c3_i1] = (real32_T)
      chartInstance->c3_dataInputs[0].f1[c3_i1];
  }

  for (c3_i2 = 0; c3_i2 < 172800; c3_i2++) {
    chartInstance->c3_inMiniBatch[c3_i2] = chartInstance->c3_dataInputsSingle[0]
      .f1[c3_i2];
  }

  for (c3_i3 = 0; c3_i3 < 172800; c3_i3++) {
    chartInstance->c3_dataInputsSingle[0].f1[c3_i3] =
      chartInstance->c3_inMiniBatch[c3_i3];
  }

  c3_st.site = &c3_f_emlrtRSI;
  for (c3_i4 = 0; c3_i4 < 172800; c3_i4++) {
    chartInstance->c3_inMiniBatch[c3_i4] = chartInstance->c3_dataInputsSingle[0]
      .f1[c3_i4];
  }

  c3_b_st.site = &c3_f_emlrtRSI;
  c3_c_st.site = &c3_g_emlrtRSI;
  for (c3_p = 0; c3_p < 3; c3_p++) {
    c3_b_p = 1.0 + (real_T)c3_p;
    if (c3_b_p != (real_T)(int32_T)muDoubleScalarFloor(c3_b_p)) {
      emlrtIntegerCheckR2012b(c3_b_p, &c3_emlrtDCI, &c3_c_st);
    }

    c3_i5 = (int32_T)c3_b_p;
    if ((c3_i5 < 1) || (c3_i5 > 3)) {
      emlrtDynamicBoundsCheckR2012b(c3_i5, 1, 3, &c3_b_emlrtBCI, &c3_c_st);
    }

    c3_c_p = c3_i5 - 1;
    for (c3_i8 = 0; c3_i8 < 320; c3_i8++) {
      for (c3_i10 = 0; c3_i10 < 180; c3_i10++) {
        chartInstance->c3_plane[c3_i10 + 180 * c3_i8] =
          chartInstance->c3_inMiniBatch[(c3_i10 + 180 * c3_i8) + 57600 * c3_c_p];
      }
    }

    if (c3_b_p != (real_T)(int32_T)muDoubleScalarFloor(c3_b_p)) {
      emlrtIntegerCheckR2012b(c3_b_p, &c3_emlrtDCI, &c3_c_st);
    }

    c3_i11 = (int32_T)c3_b_p;
    if ((c3_i11 < 1) || (c3_i11 > 3)) {
      emlrtDynamicBoundsCheckR2012b(c3_i11, 1, 3, &c3_emlrtBCI, &c3_c_st);
    }

    c3_d_p = c3_i11 - 1;
    for (c3_i12 = 0; c3_i12 < 180; c3_i12++) {
      for (c3_i13 = 0; c3_i13 < 320; c3_i13++) {
        chartInstance->c3_inMiniBatchGroup[0].f1[(c3_i13 + 320 * c3_i12) + 57600
          * c3_d_p] = chartInstance->c3_plane[c3_i12 + 180 * c3_i13];
      }
    }
  }

  c3_st.site = &c3_f_emlrtRSI;
  c3_b_obj = c3_obj;
  memcpy(c3_obj->getInputDataPointer(0), chartInstance->c3_inMiniBatchGroup[0].
         f1, c3_obj->getLayerOutputSize(0, 0));
  c3_obj->predict(chartInstance);
  memcpy(c3_outMiniBatchGroup[0].f1, c3_obj->getLayerOutput(25, 0),
         c3_obj->getLayerOutputSize(25, 0));
  c3_st.site = &c3_f_emlrtRSI;
  for (c3_i6 = 0; c3_i6 < 2; c3_i6++) {
    c3_miniBatch[c3_i6] = c3_outMiniBatchGroup[0].f1[c3_i6];
  }

  for (c3_i7 = 0; c3_i7 < 2; c3_i7++) {
    c3_outdata[0].f1[c3_i7] = c3_miniBatch[c3_i7];
  }

  for (c3_i9 = 0; c3_i9 < 2; c3_i9++) {
    c3_varargout_1[c3_i9] = c3_outdata[0].f1[c3_i9];
  }
}

static void c3_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_b_out_1_predict, const char_T *c3_identifier,
  real32_T c3_y[2])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = const_cast<const char_T *>(c3_identifier);
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_out_1_predict),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_out_1_predict);
}

static void c3_b_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real32_T c3_y[2])
{
  int32_T c3_i;
  real32_T c3_fv[2];
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_fv, 0, 1, 0U, 1, 0U, 2, 1, 2);
  for (c3_i = 0; c3_i < 2; c3_i++) {
    c3_y[c3_i] = c3_fv[c3_i];
  }

  sf_mex_destroy(&c3_u);
}

static uint8_T c3_c_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_ros_line_follower_all, const
  char_T *c3_identifier)
{
  emlrtMsgIdentifier c3_thisId;
  uint8_T c3_y;
  c3_thisId.fIdentifier = const_cast<const char_T *>(c3_identifier);
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_ros_line_follower_all), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_ros_line_follower_all);
  return c3_y;
}

static uint8_T c3_d_emlrt_marshallIn(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_b_u;
  uint8_T c3_y;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b_u, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_b_u;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_chart_data_browse_helper(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance, int32_T c3_ssIdNumber, const mxArray **c3_mxData, uint8_T
  *c3_isValueTooBig)
{
  *c3_mxData = NULL;
  *c3_mxData = NULL;
  *c3_isValueTooBig = 0U;
  switch (c3_ssIdNumber) {
   case 4U:
    *c3_isValueTooBig = 1U;
    break;

   case 5U:
    sf_mex_assign(c3_mxData, sf_mex_create("mxData",
      *chartInstance->c3_out_1_predict, 1, 0U, 1U, 0U, 2, 1, 2), false);
    break;
  }
}

void c3_mynet_new0_ros_line_follower_all0::allocate()
{
  int32_T c3_idx;
  this->targetImpl->allocate(3, this->layers, this->numLayers, 0);
  for (c3_idx = 0; c3_idx < 26; c3_idx++) {
    this->layers[c3_idx]->allocate();
  }

  (static_cast<MWTensor<real32_T> *>(this->inputTensors[0]))->setData
    (this->layers[0]->getLayerOutput(0));
}

void c3_mynet_new0_ros_line_follower_all0::postsetup()
{
  this->targetImpl->postSetup();
}

c3_mynet_new0_ros_line_follower_all0::c3_mynet_new0_ros_line_follower_all0()
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

void c3_mynet_new0_ros_line_follower_all0::deallocate()
{
  int32_T c3_idx;
  this->targetImpl->deallocate();
  for (c3_idx = 0; c3_idx < 26; c3_idx++) {
    this->layers[c3_idx]->deallocate();
  }
}

void c3_mynet_new0_ros_line_follower_all0::setSize()
{
  int32_T c3_idx;
  for (c3_idx = 0; c3_idx < 26; c3_idx++) {
    this->layers[c3_idx]->propagateSize();
  }

  this->allocate();
  this->postsetup();
}

void c3_mynet_new0_ros_line_follower_all0::resetState()
{
}

void c3_mynet_new0_ros_line_follower_all0::setup()
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
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_data_scale.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_data_offset.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[2]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[1]
      ->getOutputTensor(0), 7, 7, 3, 64, 2, 2, 3, 3, 3, 3, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_conv1_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_conv1_b.bin",
      1);
    (static_cast<MWMaxPoolingLayer *>(this->layers[3]))->createMaxPoolingLayer<
      real32_T, real32_T>(this->targetImpl, this->layers[2]->getOutputTensor(0),
                          3, 3, 2, 2, 1, 1, 1, 1, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[4]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[3]
      ->getOutputTensor(0), 3, 3, 64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2a_branch2a_b.bin",
      1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[5]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[4]
      ->getOutputTensor(0), this->layers[3]->getOutputTensor(0), 3, 3, 64, 64, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[6]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[5]
      ->getOutputTensor(0), 3, 3, 64, 64, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2b_branch2a_b.bin",
      1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[7]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[6]
      ->getOutputTensor(0), this->layers[5]->getOutputTensor(0), 3, 3, 64, 64, 1,
      1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res2b_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[8]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[7]
      ->getOutputTensor(0), 3, 3, 64, 128, 2, 2, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3a_branch2a_b.bin",
      1);
    (static_cast<MWConvLayer *>(this->layers[9]))->createConvLayer
      (this->targetImpl, this->layers[7]->getOutputTensor(0), 1, 1, 64, 128, 2,
       2, 0, 0, 0, 0, 1, 1, 1,
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
       "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3a_branch1_w.bin",
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
       "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3a_branch1_b.bin",
       2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[10]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[8]
      ->getOutputTensor(0), this->layers[9]->getOutputTensor(0), 3, 3, 128, 128,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[11]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[10]
      ->getOutputTensor(0), 3, 3, 128, 128, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3b_branch2a_b.bin",
      0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[12]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[11]
      ->getOutputTensor(0), this->layers[10]->getOutputTensor(0), 3, 3, 128, 128,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res3b_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[13]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[12]
      ->getOutputTensor(0), 3, 3, 128, 256, 2, 2, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4a_branch2a_b.bin",
      0);
    (static_cast<MWConvLayer *>(this->layers[14]))->createConvLayer
      (this->targetImpl, this->layers[12]->getOutputTensor(0), 1, 1, 128, 256, 2,
       2, 0, 0, 0, 0, 1, 1, 1,
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
       "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4a_branch1_w.bin",
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
       "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4a_branch1_b.bin",
       1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[15]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[13]
      ->getOutputTensor(0), this->layers[14]->getOutputTensor(0), 3, 3, 256, 256,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[16]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[15]
      ->getOutputTensor(0), 3, 3, 256, 256, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4b_branch2a_b.bin",
      0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[17]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[16]
      ->getOutputTensor(0), this->layers[15]->getOutputTensor(0), 3, 3, 256, 256,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res4b_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[18]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[17]
      ->getOutputTensor(0), 3, 3, 256, 512, 2, 2, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5a_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5a_branch2a_b.bin",
      0);
    (static_cast<MWConvLayer *>(this->layers[19]))->createConvLayer
      (this->targetImpl, this->layers[17]->getOutputTensor(0), 1, 1, 256, 512, 2,
       2, 0, 0, 0, 0, 1, 1, 1,
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
       "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5a_branch1_w.bin",
       "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
       "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5a_branch1_b.bin",
       2);
    (static_cast<MWFusedConvReLULayer *>(this->layers[20]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[18]
      ->getOutputTensor(0), this->layers[19]->getOutputTensor(0), 3, 3, 512, 512,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5a_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5a_branch2b_b.bin",
      -1);
    (static_cast<MWFusedConvReLULayer *>(this->layers[21]))
      ->createFusedConvReLULayer(this->targetImpl, 1, this->layers[20]
      ->getOutputTensor(0), 3, 3, 512, 512, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5b_branch2a_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5b_branch2a_b.bin",
      0);
    (static_cast<MWFusedConvReLULayer *>(this->layers[22]))
      ->createFusedConvReLULayer(this->targetImpl, 2, this->layers[21]
      ->getOutputTensor(0), this->layers[20]->getOutputTensor(0), 3, 3, 512, 512,
      1, 1, 1, 1, 1, 1, 1, 1, 1,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5b_branch2b_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_res5b_branch2b_b.bin",
      -1);
    (static_cast<MWAvgPoolingLayer *>(this->layers[23]))->createAvgPoolingLayer<
      real32_T, real32_T>(this->targetImpl, this->layers[22]->getOutputTensor(0),
                          -1, -1, 1, 1, 0, 0, 0, 0, 0, "FLOAT", 1, 0);
    (static_cast<MWFCLayer *>(this->layers[24]))->createFCLayer(this->targetImpl,
      this->layers[23]->getOutputTensor(0), 512, 2,
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_new_fc_w.bin",
      "C:\\OneDrive\\OneDrive - MathWorks\\Shared with Everyone\\Internal\\Community\\GitHub\\ai-robotics-workshop\\work\\slprj\\_sfprj\\ros_line_"
      "follower_all\\_self\\sfun\\src\\cnn_mynet_new0_ros_line_follower_all0_new_fc_b.bin",
      1);
    (static_cast<MWOutputLayer *>(this->layers[25]))->createOutputLayer
      (this->targetImpl, this->layers[24]->getOutputTensor(0), -1);
    this->outputTensors[0] = this->layers[25]->getOutputTensor(0);
    this->setSize();
  }
}

void c3_mynet_new0_ros_line_follower_all0::predict
  (SFc3_ros_line_follower_allInstanceStruct *chartInstance)
{
  int32_T c3_idx;
  for (c3_idx = 0; c3_idx < 26; c3_idx++) {
    this->layers[c3_idx]->predict();
  }
}

void c3_mynet_new0_ros_line_follower_all0::cleanup()
{
  int32_T c3_idx;
  this->deallocate();
  for (c3_idx = 0; c3_idx < 26; c3_idx++) {
    this->layers[c3_idx]->cleanup();
  }

  if (this->targetImpl) {
    this->targetImpl->cleanup();
  }
}

real32_T *c3_mynet_new0_ros_line_follower_all0::getLayerOutput(int32_T
  c3_layerIndex, int32_T c3_portIndex)
{
  return this->targetImpl->getLayerOutput(this->layers, c3_layerIndex,
    c3_portIndex);
}

int32_T c3_mynet_new0_ros_line_follower_all0::getLayerOutputSize(int32_T
  c3_layerIndex, int32_T c3_portIndex)
{
  return this->layers[c3_layerIndex]->getOutputTensor(c3_portIndex)
    ->getNumElements() * sizeof(real32_T);
}

real32_T *c3_mynet_new0_ros_line_follower_all0::getInputDataPointer(int32_T
  c3_index)
{
  return (static_cast<MWTensor<real32_T> *>(this->inputTensors[c3_index]))
    ->getData();
}

real32_T *c3_mynet_new0_ros_line_follower_all0::getInputDataPointer()
{
  return (static_cast<MWTensor<real32_T> *>(this->inputTensors[0]))->getData();
}

real32_T *c3_mynet_new0_ros_line_follower_all0::getOutputDataPointer(int32_T
  c3_index)
{
  return (static_cast<MWTensor<real32_T> *>(this->outputTensors[c3_index]))
    ->getData();
}

real32_T *c3_mynet_new0_ros_line_follower_all0::getOutputDataPointer()
{
  return (static_cast<MWTensor<real32_T> *>(this->outputTensors[0]))->getData();
}

int32_T c3_mynet_new0_ros_line_follower_all0::getBatchSize()
{
  return this->inputTensors[0]->getBatchSize();
}

c3_mynet_new0_ros_line_follower_all0::~c3_mynet_new0_ros_line_follower_all0()
{
  int32_T c3_idx;
  this->cleanup();
  for (c3_idx = 0; c3_idx < 26; c3_idx++) {
    delete this->layers[c3_idx];
  }

  if (this->targetImpl) {
    delete this->targetImpl;
  }

  delete this->inputTensors[0];
}

static void init_dsm_address_info(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance)
{
}

static void init_simulink_io_address(SFc3_ros_line_follower_allInstanceStruct
  *chartInstance)
{
  chartInstance->c3_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c3_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c3_in_1 = (uint8_T (*)[172800])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_out_1_predict = (real32_T (*)[2])
    ssGetOutputPortSignal_wrapper(chartInstance->S, 1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c3_ros_line_follower_all_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1285296129U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3053502472U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3153549734U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2320451626U);
}

mxArray *sf_c3_ros_line_follower_all_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,1);
  mxSetCell(mxcell3p, 0, mxCreateString("dltargets.mkldnn.mkldnnApi"));
  return(mxcell3p);
}

mxArray *sf_c3_ros_line_follower_all_jit_fallback_info(void)
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

mxArray *sf_c3_ros_line_follower_all_updateBuildInfo_args_info(void)
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

static const mxArray *sf_get_sim_state_info_c3_ros_line_follower_all(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiAWYGJgYAPSHEDMxAABrFA+I1SMES7OAhdXAOKSyoJUkHhxUbJnCpDOS8wF8xN"
    "LKzzz0vLB5lswIMxnw2I+I5L5nFBxCPhgT5l+EQeQfgck/SxY9PMi6ReA8vNLS+IN4wuKUlMyk0"
    "ug4QQLL/Ldo+BAmX6I/REE/KOE5h8QP7M4PjG5JLMsNT7ZOL4ovzg+JzMvNT4tPycnvzy1KD4xJ"
    "wdhPggAABtmIZU="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_ros_line_follower_all_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "sBdq237Ng27zGzUJVb9MOv";
}

static void sf_opaque_initialize_c3_ros_line_follower_all(void *chartInstanceVar)
{
  initialize_params_c3_ros_line_follower_all
    ((SFc3_ros_line_follower_allInstanceStruct*) chartInstanceVar);
  initialize_c3_ros_line_follower_all((SFc3_ros_line_follower_allInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_ros_line_follower_all(void *chartInstanceVar)
{
  enable_c3_ros_line_follower_all((SFc3_ros_line_follower_allInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c3_ros_line_follower_all(void *chartInstanceVar)
{
  disable_c3_ros_line_follower_all((SFc3_ros_line_follower_allInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c3_ros_line_follower_all(void *chartInstanceVar)
{
  sf_gateway_c3_ros_line_follower_all((SFc3_ros_line_follower_allInstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_ros_line_follower_all(SimStruct*
  S)
{
  return get_sim_state_c3_ros_line_follower_all
    ((SFc3_ros_line_follower_allInstanceStruct *)sf_get_chart_instance_ptr(S));/* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_ros_line_follower_all(SimStruct* S, const
  mxArray *st)
{
  set_sim_state_c3_ros_line_follower_all
    ((SFc3_ros_line_follower_allInstanceStruct*)sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c3_ros_line_follower_all(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_ros_line_follower_allInstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ros_line_follower_all_optimization_info();
    }

    mdl_cleanup_runtime_resources_c3_ros_line_follower_all
      ((SFc3_ros_line_follower_allInstanceStruct*) chartInstanceVar);
    ((SFc3_ros_line_follower_allInstanceStruct*) chartInstanceVar)->
      ~SFc3_ros_line_follower_allInstanceStruct();
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c3_ros_line_follower_all(void *chartInstanceVar)
{
  mdl_start_c3_ros_line_follower_all((SFc3_ros_line_follower_allInstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_mdl_terminate_c3_ros_line_follower_all(void
  *chartInstanceVar)
{
  mdl_terminate_c3_ros_line_follower_all
    ((SFc3_ros_line_follower_allInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_ros_line_follower_all
    ((SFc3_ros_line_follower_allInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_ros_line_follower_all(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  sf_warn_if_symbolic_dimension_param_changed(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_ros_line_follower_all
      ((SFc3_ros_line_follower_allInstanceStruct*)sf_get_chart_instance_ptr(S));
    initSimStructsc3_ros_line_follower_all
      ((SFc3_ros_line_follower_allInstanceStruct*)sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c3_ros_line_follower_all_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [26] = {
    "eNrtWk9v3EQUd6JStRKtIoQ4ICSiXuBAqzahKnCANLvZdlH+wSYph0XW2H67HmLPuDPj3W6/ACf",
    "unPgGfId+gVbtoQhxR+LIR+CN19k4s/Zut1GrkB1Ljj32m+eZ3/u937xJ4iw0txw8ruL5z5rjXM",
    "TrJTwXneHxTt5eKJzD5xecT/L2L9iJpfEuESSWzsSDkRi+B8mjVFHOmqzDS80o64AA5qNtwoWq8",
    "iZpnEaUHTZS5mt/8kFI/bAV8jQK1rEvCXZYNEBvSap20U+dCvBVAyBQoeBpN2xEpDsasVD9Wgj+",
    "oUzjSVOQoFppooclt9JI0SSCjUfgN5lUBEcsj8fWUkRBTT2qnKaeqWwdGfI4iShhpbMNiWxBggA",
    "r2E8C/LmTKpyUaeaHRKh1CEkP5CY9zHxyBqZPKvGFRxlRXFASbcRRTXccH9tuhOPZ4gFEEwDBsa",
    "0LIIcJp0xVx7/VwJluMOJFUAcv7VZ7a8HDVAf/gEIfRCVunRrvgSBd2GGVH80A2XiURWvEknEzR",
    "WM4IOKuj/GTEFSyF5kjWwTjBHvYo8oMskk25Z6gPYS30lsaNzUzp6VMGg+DLaeZZd42ejApCiNv",
    "DZ/VSBTJSrM9nmxCD6LMa50oMtls6LXcTkoa7HEEWNO7OhtSRjHwuVmNs4CWhqtnGGS6s43CctL",
    "ST6XicQ3JW9/cHH89btZkCkSH+FCmAoJQCYhZBm+1t4BKHXs0xFGpbHhlxkOGTLNyZCdl9T4Xh4",
    "jJBBE5noKOaKVhLLsYS8yEfYlJM8lMx3KanU/8EAItMDSCLUwbtC3BRGppu4t516NqUAfpC5qUR",
    "DXFrEMZ2tCEGiSwzw4Z77OG4HEr1/ghvADINiIYZd111C8xaODXy0Kh17ObzvF69u4rrGdH/czr",
    "pwU/CyV+nMLV/O7lxcnfXcS7hbzfWqHfFeM7F4x+2m4Jz/d+r3343d8/H/z46/pvfz3bvnGa7z9",
    "ZnG39v5q3PzoS2lHi9Mb4qm3vF8Z1ocT/BwX/S3lbrgcPV1bvbHdX7jy+93j/2wPvy62d3tDf0p",
    "TxLhrjPXq+rBUfWZbxU/jNIC9MdJukw+Va+/+iMN6LU/C4nD8fHv9+c7r+76+ZfCjD64qBl27zV",
    "Lm33ERAQH1l8Pj1x7O8drr+w+//MGU+14z5XMvWeZdo9QDXX3UFly5qAbgdHkUcawMX9W48X2fl",
    "v+33/+63MIfze5X17G33c95yv9POb9Z1/azZ35ygp45hv3SG53HaeutN2//pzFYXfZy3vx5tfWo",
    "hjYKSKjh/jSVtp+ztGcXjyY3J9p8Z9pcWJq/7fxg81e3aV+0dBnXcQcPoZvn68hZR4QPcEMl2Cw",
    "tOCJb7VIXLuCkTA86gnW3hGInauC+JcTupBu17VN1PvTah1wX3uKK+vK53VDLkSVvftGWUiJ/ar",
    "uzoS2mFgS8h6rT1bqyN9WLbZ8yNBwyUy6B/s7wqwccgb3uuJwjzwxXiejc8ynKeT8HjqYHH03OB",
    "h89Z79YRDJYXR7zoW15oXvRn4MULA4cX5wKHgCji8k5HgsqxmHv9/LxcP+cXD1KqG3OLx+oID28",
    "WHX1m4PHsXOCB79yOP0ud8dzA4fn50VHpkwg0ElY/rV6U6qddT07qp2f1M9NPmycgV2yeVOJh+V",
    "HEw7P8MPCw/EA87L6tEg/LjyIeVj9MPGbgx0sDj5fnri6d7ffF84BH3+IB8vbr8WMO9rVWT0/ua",
    "2eqP+YhX/o2X07mi63HTuaLxQPxsPuXSjwsP4p42PXWxMPuXwrri92/mHjY+uPE3+Wsfph42PWl",
    "UK/b+mMMD8uPIh5WP0w8LD+K/19q+WHikfPjP5J7buo=",
    ""
  };

  static char newstr [1845] = "";
  newstr[0] = '\0';
  for (i = 0; i < 26; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c3_ros_line_follower_all(SimStruct *S)
{
  const char* newstr = sf_c3_ros_line_follower_all_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(440642834U));
  ssSetChecksum1(S,(1451746641U));
  ssSetChecksum2(S,(2655164509U));
  ssSetChecksum3(S,(776916698U));
}

static void mdlRTW_c3_ros_line_follower_all(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c3_ros_line_follower_all(SimStruct *S)
{
  SFc3_ros_line_follower_allInstanceStruct *chartInstance;
  chartInstance = (SFc3_ros_line_follower_allInstanceStruct *)utMalloc(sizeof
    (SFc3_ros_line_follower_allInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc3_ros_line_follower_allInstanceStruct));
  chartInstance = new (chartInstance) SFc3_ros_line_follower_allInstanceStruct;
  chartInstance->chartInfo.chartInstance = chartInstance;
  if (ssGetSampleTime(S, 0) == CONTINUOUS_SAMPLE_TIME && ssGetOffsetTime(S, 0) ==
      0 && ssGetNumContStates(ssGetRootSS(S)) > 0 &&
      !supportsLegacyBehaviorForPersistentVarInContinuousTime(S)) {
    sf_error_out_about_continuous_sample_time_with_persistent_vars(S);
  }

  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c3_ros_line_follower_all;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_ros_line_follower_all;
  chartInstance->chartInfo.mdlStart =
    sf_opaque_mdl_start_c3_ros_line_follower_all;
  chartInstance->chartInfo.mdlTerminate =
    sf_opaque_mdl_terminate_c3_ros_line_follower_all;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c3_ros_line_follower_all;
  chartInstance->chartInfo.enableChart =
    sf_opaque_enable_c3_ros_line_follower_all;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c3_ros_line_follower_all;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_ros_line_follower_all;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_ros_line_follower_all;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_ros_line_follower_all;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_ros_line_follower_all;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c3_ros_line_follower_all;
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
    chartInstance->c3_JITStateAnimation,
    chartInstance->c3_JITTransitionAnimation);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c3_ros_line_follower_all(chartInstance);
}

void c3_ros_line_follower_all_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c3_ros_line_follower_all(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_ros_line_follower_all(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_ros_line_follower_all(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_ros_line_follower_all_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
