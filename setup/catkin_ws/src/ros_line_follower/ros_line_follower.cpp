//
// File: ros_line_follower.cpp
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
#include "ros_line_follower.h"
#include "ros_line_follower_private.h"

// Block signals (default storage)
B_ros_line_follower_T ros_line_follower_B;

// Block states (default storage)
DW_ros_line_follower_T ros_line_follower_DW;

// Real-time model
RT_MODEL_ros_line_follower_T ros_line_follower_M_ = RT_MODEL_ros_line_follower_T
  ();
RT_MODEL_ros_line_follower_T *const ros_line_follower_M = &ros_line_follower_M_;

// Forward declaration for local functions
static void ros_line_follow_SystemCore_step(boolean_T *varargout_1,
  SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension varargout_2_Layout_Dim
  [16], uint32_T *varargout_2_Layout_Dim_SL_Info_, uint32_T
  *varargout_2_Layout_Dim_SL_Inf_0, uint32_T *varargout_2_Layout_DataOffset,
  real32_T varargout_2_Data[128], uint32_T *varargout_2_Data_SL_Info_Curren,
  uint32_T *varargout_2_Data_SL_Info_Receiv);
static void rate_scheduler(void);

//
//   This function updates active task flag for each subrate.
// The function is called at model base rate, hence the
// generated code self-manages all its subrates.
//
static void rate_scheduler(void)
{
  // Compute which subrates run during the next base time step.  Subrates
  //  are an integer multiple of the base rate counter.  Therefore, the subtask
  //  counter is reset when it reaches its limit (zero means run).

  (ros_line_follower_M->Timing.TaskCounters.TID[1])++;
  if ((ros_line_follower_M->Timing.TaskCounters.TID[1]) > 1) {// Sample time: [0.1s, 0.0s] 
    ros_line_follower_M->Timing.TaskCounters.TID[1] = 0;
  }
}

static void ros_line_follow_SystemCore_step(boolean_T *varargout_1,
  SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension varargout_2_Layout_Dim
  [16], uint32_T *varargout_2_Layout_Dim_SL_Info_, uint32_T
  *varargout_2_Layout_Dim_SL_Inf_0, uint32_T *varargout_2_Layout_DataOffset,
  real32_T varargout_2_Data[128], uint32_T *varargout_2_Data_SL_Info_Curren,
  uint32_T *varargout_2_Data_SL_Info_Receiv)
{
  *varargout_1 = Sub_ros_line_follower_3799.getLatestMessage
    (&ros_line_follower_B.b_varargout_2);
  memcpy(&varargout_2_Layout_Dim[0],
         &ros_line_follower_B.b_varargout_2.Layout.Dim[0], sizeof
         (SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension) << 4U);
  *varargout_2_Layout_Dim_SL_Info_ =
    ros_line_follower_B.b_varargout_2.Layout.Dim_SL_Info.CurrentLength;
  *varargout_2_Layout_Dim_SL_Inf_0 =
    ros_line_follower_B.b_varargout_2.Layout.Dim_SL_Info.ReceivedLength;
  *varargout_2_Layout_DataOffset =
    ros_line_follower_B.b_varargout_2.Layout.DataOffset;
  memcpy(&varargout_2_Data[0], &ros_line_follower_B.b_varargout_2.Data[0],
         sizeof(real32_T) << 7U);
  *varargout_2_Data_SL_Info_Curren =
    ros_line_follower_B.b_varargout_2.Data_SL_Info.CurrentLength;
  *varargout_2_Data_SL_Info_Receiv =
    ros_line_follower_B.b_varargout_2.Data_SL_Info.ReceivedLength;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(static_cast<real_T>(u0_0), static_cast<real_T>(u1_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

// Model step function
void ros_line_follower_step(void)
{
  SL_Bus_ros_line_follower_std_msgs_Bool b_varargout_2;
  SL_Bus_ros_line_follower_std_msgs_Float32 b_varargout_2_0;
  real_T rtb_EnvironmentSwitch;
  real_T rtb_ProportionalGain;
  real_T vl;
  int32_T i;
  uint32_T b_varargout_2_Data_SL_Info_Curr;
  uint32_T b_varargout_2_Data_SL_Info_Rece;
  uint32_T b_varargout_2_Layout_DataOffset;
  uint32_T b_varargout_2_Layout_Dim_SL_I_0;
  uint32_T b_varargout_2_Layout_Dim_SL_Inf;
  boolean_T b_varargout_1;
  boolean_T b_varargout_1_0;
  boolean_T b_varargout_1_1;
  if (ros_line_follower_M->Timing.TaskCounters.TID[1] == 0) {
    // Outputs for Atomic SubSystem: '<S61>/Subscribe'
    // MATLABSystem: '<S65>/SourceBlock' incorporates:
    //   Inport: '<S66>/In1'

    b_varargout_1 = Sub_ros_line_follower_3981.getLatestMessage(&b_varargout_2);

    // Outputs for Enabled SubSystem: '<S65>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S66>/Enable'

    if (b_varargout_1) {
      ros_line_follower_B.In1_d = b_varargout_2;
    }

    // End of Outputs for SubSystem: '<S65>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<S61>/Subscribe'

    // Outputs for Atomic SubSystem: '<S2>/Subscribe'
    // MATLABSystem: '<S58>/SourceBlock' incorporates:
    //   Inport: '<S59>/In1'

    b_varargout_1_0 = Sub_ros_line_follower_3973.getLatestMessage
      (&b_varargout_2_0);

    // Outputs for Enabled SubSystem: '<S58>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S59>/Enable'

    if (b_varargout_1_0) {
      ros_line_follower_B.In1_g = b_varargout_2_0;
    }

    // End of Outputs for SubSystem: '<S58>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<S2>/Subscribe'

    // Switch: '<S57>/Environment Switch' incorporates:
    //   Constant: '<S2>/velCmd'
    //   Constant: '<S2>/velCmd1'
    //   Constant: '<S57>/Switch Control'
    //   Delay: '<S2>/Delay'
    //   Switch: '<S2>/Switch'

    if (ros_line_follower_P.SwitchControl_Value_n) {
      rtb_EnvironmentSwitch = ros_line_follower_P.velCmd_Value;
    } else if (ros_line_follower_DW.Delay_DSTATE_b) {
      // Switch: '<S2>/Switch'
      rtb_EnvironmentSwitch = ros_line_follower_B.In1_g.Data;
    } else {
      rtb_EnvironmentSwitch = ros_line_follower_P.velCmd1_Value;
    }

    // End of Switch: '<S57>/Environment Switch'

    // Outputs for Atomic SubSystem: '<Root>/Target Position from Line Detector' 
    // MATLABSystem: '<S3>/SourceBlock' incorporates:
    //   Inport: '<S60>/In1'

    ros_line_follow_SystemCore_step(&b_varargout_1_1,
      ros_line_follower_B.b_varargout_2_Layout_Dim,
      &b_varargout_2_Layout_Dim_SL_Inf, &b_varargout_2_Layout_Dim_SL_I_0,
      &b_varargout_2_Layout_DataOffset, ros_line_follower_B.b_varargout_2_Data,
      &b_varargout_2_Data_SL_Info_Curr, &b_varargout_2_Data_SL_Info_Rece);

    // Outputs for Enabled SubSystem: '<S3>/Enabled Subsystem' incorporates:
    //   EnablePort: '<S60>/Enable'

    if (b_varargout_1_1) {
      memcpy(&ros_line_follower_B.In1.Layout.Dim[0],
             &ros_line_follower_B.b_varargout_2_Layout_Dim[0], sizeof
             (SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension) << 4U);
      ros_line_follower_B.In1.Layout.Dim_SL_Info.CurrentLength =
        b_varargout_2_Layout_Dim_SL_Inf;
      ros_line_follower_B.In1.Layout.Dim_SL_Info.ReceivedLength =
        b_varargout_2_Layout_Dim_SL_I_0;
      ros_line_follower_B.In1.Layout.DataOffset =
        b_varargout_2_Layout_DataOffset;
      memcpy(&ros_line_follower_B.In1.Data[0],
             &ros_line_follower_B.b_varargout_2_Data[0], sizeof(real32_T) << 7U);
      ros_line_follower_B.In1.Data_SL_Info.CurrentLength =
        b_varargout_2_Data_SL_Info_Curr;
      ros_line_follower_B.In1.Data_SL_Info.ReceivedLength =
        b_varargout_2_Data_SL_Info_Rece;
    }

    // End of MATLABSystem: '<S3>/SourceBlock'
    // End of Outputs for SubSystem: '<S3>/Enabled Subsystem'
    // End of Outputs for SubSystem: '<Root>/Target Position from Line Detector' 

    // Gain: '<S45>/Proportional Gain' incorporates:
    //   Constant: '<S5>/Constant2'
    //   DataTypeConversion: '<S7>/Data Type Conversion'
    //   Gain: '<S5>/Gain'
    //   Sum: '<S5>/Sum1'
    //   Trigonometry: '<S5>/Atan2'

    rtb_ProportionalGain = rt_atan2d_snf(ros_line_follower_P.Gain_Gain *
      ros_line_follower_B.In1.Data[0], static_cast<real_T>
      (ros_line_follower_P.Constant2_Value) - ros_line_follower_B.In1.Data[1]) *
      ros_line_follower_P.PIDController1_P;

    // MATLAB Function: '<S4>/Velocity to Wheel Cmds'
    // MATLAB Function 'Vehicle Interface/Velocity to Wheel Cmds': '<S63>:1'
    // '<S63>:1:3' d = 0.05125*2;
    // '<S63>:1:4' r = 0.03;
    // '<S63>:1:6' if abs(vAng) > 2
    if (fabs(rtb_ProportionalGain) > 2.0) {
      // '<S63>:1:7' vl = -d*vAng/2;
      vl = -0.1025 * rtb_ProportionalGain / 2.0;

      // '<S63>:1:8' vr =  d*vAng/2;
      rtb_EnvironmentSwitch = 0.1025 * rtb_ProportionalGain / 2.0;
    } else {
      // '<S63>:1:9' else
      // '<S63>:1:10' vl = vLin - d*vAng/2;
      rtb_ProportionalGain = 0.1025 * rtb_ProportionalGain / 2.0;
      vl = rtb_EnvironmentSwitch - rtb_ProportionalGain;

      // '<S63>:1:11' vr = vLin + d*vAng/2;
      rtb_EnvironmentSwitch += rtb_ProportionalGain;
    }

    // Switch: '<S64>/Environment Switch' incorporates:
    //   Constant: '<S61>/Stop'
    //   Constant: '<S61>/Stop1'
    //   Constant: '<S64>/Switch Control'
    //   Delay: '<S61>/Delay'
    //   Switch: '<S61>/Switch1'

    // '<S63>:1:13' wl = vl / r;
    // '<S63>:1:14' wr = vr / r;
    // '<S63>:1:15' wlCmd = funcl(wl);
    // '<S63>:1:20' wCmd = min(max(w*0.1,-1),1);
    // '<S63>:1:16' wrCmd = funcr(wr);
    // '<S63>:1:23' wCmd = min(max(w*0.096,-1),1);
    // '<S63>:1:17' cmd = [wlCmd,wrCmd];
    if (ros_line_follower_P.SwitchControl_Value) {
      b_varargout_1_1 = ros_line_follower_P.Stop_Value;
    } else if (ros_line_follower_DW.Delay_DSTATE) {
      // Switch: '<S61>/Switch1'
      b_varargout_1_1 = ros_line_follower_B.In1_d.Data;
    } else {
      b_varargout_1_1 = ros_line_follower_P.Stop1_Value;
    }

    // End of Switch: '<S64>/Environment Switch'

    // Switch: '<S61>/Switch' incorporates:
    //   Constant: '<S61>/Constant3'
    //   MATLAB Function: '<S4>/Velocity to Wheel Cmds'

    if (b_varargout_1_1) {
      vl = ros_line_follower_P.Constant3_Value;
      rtb_EnvironmentSwitch = ros_line_follower_P.Constant3_Value;
    } else {
      vl = fmin(fmax(vl / 0.03 * 0.1, -1.0), 1.0);
      rtb_EnvironmentSwitch = fmin(fmax(rtb_EnvironmentSwitch / 0.03 * 0.096,
        -1.0), 1.0);
    }

    // End of Switch: '<S61>/Switch'

    // ComposeString: '<S68>/Compose String'
    snprintf(&ros_line_follower_B.rtb_ComposeString_m[0], 256U,
             "speed[ %+1.4f,%+1.4f ]", vl, rtb_EnvironmentSwitch);

    // StringToASCII: '<S68>/String to ASCII' incorporates:
    //   ComposeString: '<S68>/Compose String'

    strncpy(&ros_line_follower_B.cv[0],
            &ros_line_follower_B.rtb_ComposeString_m[0], 31U);

    // MATLAB Function: '<S62>/MATLAB Function -String Assign' incorporates:
    //   Constant: '<S67>/Constant'
    //   StringToASCII: '<S68>/String to ASCII'

    //  assignStringInput - Assign a string in a ROS message to specified input string 
    //
    //  MSG = assignStringInput(blankMsg, STR) assigns the input string, STR, to 
    //   a string field in the ROS message, blankMsg, and outputs the updated
    //   ROS message.
    //   Inputs
    //     blankMsg: A bus for a 'std_msgs/String' message. This is
    //         used to initialize the output.
    //     str: An array of uint8 that will be assigned to the 'Data' field
    //         in blankMsg. The entire array is assumed to be a valid sequence of 
    //         character ASCII values.
    //
    //   Outputs:
    //     msg: A bus for a 'std_msgs/String' message, with the 'Data'
    //         field set to a string.
    // MATLAB Function 'Vehicle Interface/Motor Cmd Publisher/MATLAB Function -String Assign': '<S69>:1' 
    //    Copyright 2015 The MathWorks, Inc.
    //  Note: The datatype of 'msg' has been explicitly set to the appropriate
    //  Simulink bus type ("Bus: SL_Bus_robotROSMessageUsageExample_std_msgs_String").  
    //
    //  If the model name is changed, the datatype needs to be changed as well:
    //    1) Click "Edit Data" in the Editor toolstrip to open "Ports and Data Manager" 
    //    2) Select "msg". From the "Type" dropdown, select "--- Refresh data types ---" 
    //    3) Set datatype to "Bus: SL_Bus_<modelname>_std_msgs_String"
    // '<S69>:1:30' msg = blankMsg;
    ros_line_follower_B.msg = ros_line_follower_P.Constant_Value_b;

    //  msg (std_msgs/String) consists of
    //            Data : array of type uint8
    //    Data_SL_Info : struct with fields CurrentLength, ReceivedLength
    // '<S69>:1:35' strLength = length(str);
    // '<S69>:1:36' msg.Data(1:strLength) = uint8(str);
    for (i = 0; i < 31; i++) {
      ros_line_follower_B.msg.Data[i] = static_cast<uint8_T>
        (ros_line_follower_B.cv[i]);
    }

    // '<S69>:1:37' msg.Data_SL_Info.CurrentLength = uint32(strLength);
    ros_line_follower_B.msg.Data_SL_Info.CurrentLength = 31U;

    // End of MATLAB Function: '<S62>/MATLAB Function -String Assign'

    // Outputs for Atomic SubSystem: '<S62>/Publish1'
    // MATLABSystem: '<S70>/SinkBlock'
    Pub_ros_line_follower_2305.publish(&ros_line_follower_B.msg);

    // End of Outputs for SubSystem: '<S62>/Publish1'

    // Outputs for Atomic SubSystem: '<S61>/Subscribe'
    // Update for Delay: '<S61>/Delay' incorporates:
    //   Logic: '<S61>/OR'
    //   MATLABSystem: '<S65>/SourceBlock'

    ros_line_follower_DW.Delay_DSTATE = (ros_line_follower_DW.Delay_DSTATE ||
      b_varargout_1);

    // End of Outputs for SubSystem: '<S61>/Subscribe'

    // Outputs for Atomic SubSystem: '<S2>/Subscribe'
    // Update for Delay: '<S2>/Delay' incorporates:
    //   Logic: '<S2>/OR'
    //   MATLABSystem: '<S58>/SourceBlock'

    ros_line_follower_DW.Delay_DSTATE_b = (ros_line_follower_DW.Delay_DSTATE_b ||
      b_varargout_1_0);

    // End of Outputs for SubSystem: '<S2>/Subscribe'
  }

  rate_scheduler();
}

// Model initialize function
void ros_line_follower_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // block I/O
  (void) memset((static_cast<void *>(&ros_line_follower_B)), 0,
                sizeof(B_ros_line_follower_T));

  // states (dwork)
  (void) memset(static_cast<void *>(&ros_line_follower_DW), 0,
                sizeof(DW_ros_line_follower_T));

  {
    int32_T i;
    char_T b_zeroDelimTopic_1[23];
    char_T b_zeroDelimTopic[20];
    char_T b_zeroDelimTopic_0[15];
    static const char_T tmp[19] = { '/', 'l', 'i', 'n', 'e', '_', 'f', 'o', 'l',
      'l', 'o', 'w', 'e', 'r', '/', 's', 't', 'o', 'p' };

    static const char_T tmp_0[30] = { '/', 'l', 'i', 'n', 'e', '_', 'f', 'o',
      'l', 'l', 'o', 'w', 'e', 'r', '/', 'l', 'i', 'n', 'e', 'a', 'r', '_', 'v',
      'e', 'l', 'o', 'c', 'i', 't', 'y' };

    static const char_T tmp_1[14] = { '/', 'd', 'e', 't', 'e', 'c', 't', 'i',
      'o', 'n', '_', 'p', 'o', 's' };

    static const char_T tmp_2[22] = { '/', 'j', 'e', 't', 'b', 'o', 't', '_',
      'm', 'o', 't', 'o', 'r', 's', '/', 'c', 'm', 'd', '_', 'r', 'a', 'w' };

    // InitializeConditions for Delay: '<S61>/Delay'
    ros_line_follower_DW.Delay_DSTATE =
      ros_line_follower_P.Delay_InitialCondition;

    // InitializeConditions for Delay: '<S2>/Delay'
    ros_line_follower_DW.Delay_DSTATE_b =
      ros_line_follower_P.Delay_InitialCondition_c;

    // SystemInitialize for Atomic SubSystem: '<S61>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S65>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S66>/Out1' incorporates:
    //   Inport: '<S66>/In1'

    ros_line_follower_B.In1_d = ros_line_follower_P.Out1_Y0_m;

    // End of SystemInitialize for SubSystem: '<S65>/Enabled Subsystem'

    // Start for MATLABSystem: '<S65>/SourceBlock'
    ros_line_follower_DW.obj.matlabCodegenIsDeleted = false;
    ros_line_follower_DW.obj.isInitialized = 1;
    for (i = 0; i < 19; i++) {
      b_zeroDelimTopic[i] = tmp[i];
    }

    b_zeroDelimTopic[19] = '\x00';
    Sub_ros_line_follower_3981.createSubscriber(&b_zeroDelimTopic[0], 1);
    ros_line_follower_DW.obj.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S65>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S61>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<S2>/Subscribe'
    // SystemInitialize for Enabled SubSystem: '<S58>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S59>/Out1' incorporates:
    //   Inport: '<S59>/In1'

    ros_line_follower_B.In1_g = ros_line_follower_P.Out1_Y0_m0;

    // End of SystemInitialize for SubSystem: '<S58>/Enabled Subsystem'

    // Start for MATLABSystem: '<S58>/SourceBlock'
    ros_line_follower_DW.obj_e.matlabCodegenIsDeleted = false;
    ros_line_follower_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 30; i++) {
      ros_line_follower_B.b_zeroDelimTopic[i] = tmp_0[i];
    }

    ros_line_follower_B.b_zeroDelimTopic[30] = '\x00';
    Sub_ros_line_follower_3973.createSubscriber
      (&ros_line_follower_B.b_zeroDelimTopic[0], 1);
    ros_line_follower_DW.obj_e.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S58>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<S2>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Target Position from Line Detector' 
    // SystemInitialize for Enabled SubSystem: '<S3>/Enabled Subsystem'
    // SystemInitialize for Outport: '<S60>/Out1' incorporates:
    //   Inport: '<S60>/In1'

    ros_line_follower_B.In1 = ros_line_follower_P.Out1_Y0;

    // End of SystemInitialize for SubSystem: '<S3>/Enabled Subsystem'

    // Start for MATLABSystem: '<S3>/SourceBlock'
    ros_line_follower_DW.obj_p.matlabCodegenIsDeleted = false;
    ros_line_follower_DW.obj_p.isInitialized = 1;
    for (i = 0; i < 14; i++) {
      b_zeroDelimTopic_0[i] = tmp_1[i];
    }

    b_zeroDelimTopic_0[14] = '\x00';
    Sub_ros_line_follower_3799.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    ros_line_follower_DW.obj_p.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S3>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Target Position from Line Detector' 

    // SystemInitialize for Atomic SubSystem: '<S62>/Publish1'
    // Start for MATLABSystem: '<S70>/SinkBlock'
    ros_line_follower_DW.obj_o.matlabCodegenIsDeleted = false;
    ros_line_follower_DW.obj_o.isInitialized = 1;
    for (i = 0; i < 22; i++) {
      b_zeroDelimTopic_1[i] = tmp_2[i];
    }

    b_zeroDelimTopic_1[22] = '\x00';
    Pub_ros_line_follower_2305.createPublisher(&b_zeroDelimTopic_1[0], 1);
    ros_line_follower_DW.obj_o.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S70>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<S62>/Publish1'
  }
}

// Model terminate function
void ros_line_follower_terminate(void)
{
  // Terminate for Atomic SubSystem: '<S61>/Subscribe'
  // Terminate for MATLABSystem: '<S65>/SourceBlock'
  if (!ros_line_follower_DW.obj.matlabCodegenIsDeleted) {
    ros_line_follower_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S65>/SourceBlock'
  // End of Terminate for SubSystem: '<S61>/Subscribe'

  // Terminate for Atomic SubSystem: '<S2>/Subscribe'
  // Terminate for MATLABSystem: '<S58>/SourceBlock'
  if (!ros_line_follower_DW.obj_e.matlabCodegenIsDeleted) {
    ros_line_follower_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S58>/SourceBlock'
  // End of Terminate for SubSystem: '<S2>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Target Position from Line Detector' 
  // Terminate for MATLABSystem: '<S3>/SourceBlock'
  if (!ros_line_follower_DW.obj_p.matlabCodegenIsDeleted) {
    ros_line_follower_DW.obj_p.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S3>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Target Position from Line Detector' 

  // Terminate for Atomic SubSystem: '<S62>/Publish1'
  // Terminate for MATLABSystem: '<S70>/SinkBlock'
  if (!ros_line_follower_DW.obj_o.matlabCodegenIsDeleted) {
    ros_line_follower_DW.obj_o.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S70>/SinkBlock'
  // End of Terminate for SubSystem: '<S62>/Publish1'
}

//
// File trailer for generated code.
//
// [EOF]
//
