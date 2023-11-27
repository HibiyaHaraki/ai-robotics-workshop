//
// File: ros_line_follower.h
//
// Code generated for Simulink model 'ros_line_follower'.
//
// Model version                  : 4.23
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Thu Apr  8 16:21:14 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objective: Execution efficiency
// Validation result: Not run
//
#ifndef RTW_HEADER_ros_line_follower_h_
#define RTW_HEADER_ros_line_follower_h_
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "rtwtypes.h"
#include "slros_initialize.h"
#include "ros_line_follower_types.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

// Block signals (default storage)
struct B_ros_line_follower_T {
  SL_Bus_ros_line_follower_std_msgs_Float32MultiArray In1;// '<S60>/In1'
  SL_Bus_ros_line_follower_std_msgs_Float32MultiArray b_varargout_2;
  SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension
    b_varargout_2_Layout_Dim[16];
  real32_T b_varargout_2_Data[128];
  char_T rtb_ComposeString_m[256];
  SL_Bus_ros_line_follower_std_msgs_String msg;
                                      // '<S62>/MATLAB Function -String Assign'
  char_T cv[31];
  char_T b_zeroDelimTopic[31];
  SL_Bus_ros_line_follower_std_msgs_Float32 In1_g;// '<S59>/In1'
  SL_Bus_ros_line_follower_std_msgs_Bool In1_d;// '<S66>/In1'
};

// Block states (default storage) for system '<Root>'
struct DW_ros_line_follower_T {
  ros_slroscpp_internal_block_S_T obj; // '<S65>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_p;// '<S3>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_e;// '<S58>/SourceBlock'
  ros_slroscpp_internal_block_P_T obj_o;// '<S70>/SinkBlock'
  boolean_T Delay_DSTATE;              // '<S61>/Delay'
  boolean_T Delay_DSTATE_b;            // '<S2>/Delay'
};

// Parameters (default storage)
struct P_ros_line_follower_T_ {
  real_T PIDController1_P;             // Mask Parameter: PIDController1_P
                                          //  Referenced by: '<S45>/Proportional Gain'

  SL_Bus_ros_line_follower_std_msgs_Float32MultiArray Out1_Y0;// Computed Parameter: Out1_Y0
                                                                 //  Referenced by: '<S60>/Out1'

  SL_Bus_ros_line_follower_std_msgs_Float32MultiArray Constant_Value;// Computed Parameter: Constant_Value
                                                                      //  Referenced by: '<S3>/Constant'

  SL_Bus_ros_line_follower_std_msgs_String Constant_Value_b;// Computed Parameter: Constant_Value_b
                                                               //  Referenced by: '<S67>/Constant'

  SL_Bus_ros_line_follower_std_msgs_Bool Out1_Y0_m;// Computed Parameter: Out1_Y0_m
                                                      //  Referenced by: '<S66>/Out1'

  SL_Bus_ros_line_follower_std_msgs_Bool Constant_Value_n;// Computed Parameter: Constant_Value_n
                                                             //  Referenced by: '<S65>/Constant'

  SL_Bus_ros_line_follower_std_msgs_Float32 Out1_Y0_m0;// Computed Parameter: Out1_Y0_m0
                                                          //  Referenced by: '<S59>/Out1'

  SL_Bus_ros_line_follower_std_msgs_Float32 Constant_Value_k;// Computed Parameter: Constant_Value_k
                                                                //  Referenced by: '<S58>/Constant'

  real_T velCmd_Value;                 // Expression: 0.1687898089171974
                                          //  Referenced by: '<S2>/velCmd'

  real_T velCmd1_Value;                // Expression: 0.15
                                          //  Referenced by: '<S2>/velCmd1'

  real_T Gain_Gain;                    // Expression: -1
                                          //  Referenced by: '<S5>/Gain'

  real32_T Constant3_Value;            // Computed Parameter: Constant3_Value
                                          //  Referenced by: '<S61>/Constant3'

  real32_T Constant2_Value;            // Computed Parameter: Constant2_Value
                                          //  Referenced by: '<S5>/Constant2'

  boolean_T Stop_Value;                // Expression: logical(0)
                                          //  Referenced by: '<S61>/Stop'

  boolean_T Stop1_Value;               // Expression: logical(1)
                                          //  Referenced by: '<S61>/Stop1'

  boolean_T SwitchControl_Value;       // Expression: switch_mode
                                          //  Referenced by: '<S64>/Switch Control'

  boolean_T Delay_InitialCondition;// Computed Parameter: Delay_InitialCondition
                                      //  Referenced by: '<S61>/Delay'

  boolean_T SwitchControl_Value_n;     // Expression: switch_mode
                                          //  Referenced by: '<S57>/Switch Control'

  boolean_T Delay_InitialCondition_c;
                                 // Computed Parameter: Delay_InitialCondition_c
                                    //  Referenced by: '<S2>/Delay'

};

// Real-time Model Data Structure
struct tag_RTM_ros_line_follower_T {
  const char_T *errorStatus;

  //
  //  Timing:
  //  The following substructure contains information regarding
  //  the timing information for the model.

  struct {
    struct {
      uint8_T TID[2];
    } TaskCounters;
  } Timing;
};

// Block parameters (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern P_ros_line_follower_T ros_line_follower_P;

#ifdef __cplusplus

}
#endif

// Block signals (default storage)
#ifdef __cplusplus

extern "C" {

#endif

  extern struct B_ros_line_follower_T ros_line_follower_B;

#ifdef __cplusplus

}
#endif

// Block states (default storage)
extern struct DW_ros_line_follower_T ros_line_follower_DW;

#ifdef __cplusplus

extern "C" {

#endif

  // Model entry point functions
  extern void ros_line_follower_initialize(void);
  extern void ros_line_follower_step(void);
  extern void ros_line_follower_terminate(void);

#ifdef __cplusplus

}
#endif

// Real-time Model object
#ifdef __cplusplus

extern "C" {

#endif

  extern RT_MODEL_ros_line_follower_T *const ros_line_follower_M;

#ifdef __cplusplus

}
#endif

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Scope' : Unused code path elimination
//  Block '<S57>/Numerical Unity' : Eliminate redundant signal conversion block
//  Block '<S64>/Numerical Unity' : Eliminate redundant signal conversion block


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'ros_line_follower'
//  '<S1>'   : 'ros_line_follower/Controller'
//  '<S2>'   : 'ros_line_follower/Target Linear Velocity'
//  '<S3>'   : 'ros_line_follower/Target Position from Line Detector'
//  '<S4>'   : 'ros_line_follower/Vehicle Interface'
//  '<S5>'   : 'ros_line_follower/Controller/Deep Learning Based Regressor'
//  '<S6>'   : 'ros_line_follower/Controller/P Controller'
//  '<S7>'   : 'ros_line_follower/Controller/Deep Learning Based Regressor/Extract Position'
//  '<S8>'   : 'ros_line_follower/Controller/P Controller/PID Controller1'
//  '<S9>'   : 'ros_line_follower/Controller/P Controller/PID Controller1/Anti-windup'
//  '<S10>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/D Gain'
//  '<S11>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Filter'
//  '<S12>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Filter ICs'
//  '<S13>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/I Gain'
//  '<S14>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Ideal P Gain'
//  '<S15>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Ideal P Gain Fdbk'
//  '<S16>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Integrator'
//  '<S17>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Integrator ICs'
//  '<S18>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/N Copy'
//  '<S19>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/N Gain'
//  '<S20>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/P Copy'
//  '<S21>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Parallel P Gain'
//  '<S22>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Reset Signal'
//  '<S23>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Saturation'
//  '<S24>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Saturation Fdbk'
//  '<S25>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Sum'
//  '<S26>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Sum Fdbk'
//  '<S27>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tracking Mode'
//  '<S28>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tracking Mode Sum'
//  '<S29>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tsamp - Integral'
//  '<S30>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tsamp - Ngain'
//  '<S31>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/postSat Signal'
//  '<S32>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/preSat Signal'
//  '<S33>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Anti-windup/Disabled'
//  '<S34>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/D Gain/Disabled'
//  '<S35>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Filter/Disabled'
//  '<S36>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Filter ICs/Disabled'
//  '<S37>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/I Gain/Disabled'
//  '<S38>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Ideal P Gain/Passthrough'
//  '<S39>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Ideal P Gain Fdbk/Disabled'
//  '<S40>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Integrator/Disabled'
//  '<S41>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Integrator ICs/Disabled'
//  '<S42>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/N Copy/Disabled wSignal Specification'
//  '<S43>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/N Gain/Disabled'
//  '<S44>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/P Copy/Disabled'
//  '<S45>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Parallel P Gain/Internal Parameters'
//  '<S46>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Reset Signal/Disabled'
//  '<S47>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Saturation/Passthrough'
//  '<S48>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Saturation Fdbk/Disabled'
//  '<S49>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Sum/Passthrough_P'
//  '<S50>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Sum Fdbk/Disabled'
//  '<S51>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tracking Mode/Disabled'
//  '<S52>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tracking Mode Sum/Passthrough'
//  '<S53>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tsamp - Integral/Disabled wSignal Specification'
//  '<S54>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/Tsamp - Ngain/Passthrough'
//  '<S55>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/postSat Signal/Forward_Path'
//  '<S56>'  : 'ros_line_follower/Controller/P Controller/PID Controller1/preSat Signal/Forward_Path'
//  '<S57>'  : 'ros_line_follower/Target Linear Velocity/Environment Controller'
//  '<S58>'  : 'ros_line_follower/Target Linear Velocity/Subscribe'
//  '<S59>'  : 'ros_line_follower/Target Linear Velocity/Subscribe/Enabled Subsystem'
//  '<S60>'  : 'ros_line_follower/Target Position from Line Detector/Enabled Subsystem'
//  '<S61>'  : 'ros_line_follower/Vehicle Interface/Manual Stop'
//  '<S62>'  : 'ros_line_follower/Vehicle Interface/Motor Cmd Publisher'
//  '<S63>'  : 'ros_line_follower/Vehicle Interface/Velocity to Wheel Cmds'
//  '<S64>'  : 'ros_line_follower/Vehicle Interface/Manual Stop/Environment Controller'
//  '<S65>'  : 'ros_line_follower/Vehicle Interface/Manual Stop/Subscribe'
//  '<S66>'  : 'ros_line_follower/Vehicle Interface/Manual Stop/Subscribe/Enabled Subsystem'
//  '<S67>'  : 'ros_line_follower/Vehicle Interface/Motor Cmd Publisher/Blank String Message'
//  '<S68>'  : 'ros_line_follower/Vehicle Interface/Motor Cmd Publisher/LRSpeed2String'
//  '<S69>'  : 'ros_line_follower/Vehicle Interface/Motor Cmd Publisher/MATLAB Function -String Assign'
//  '<S70>'  : 'ros_line_follower/Vehicle Interface/Motor Cmd Publisher/Publish1'

#endif                                 // RTW_HEADER_ros_line_follower_h_

//
// File trailer for generated code.
//
// [EOF]
//
