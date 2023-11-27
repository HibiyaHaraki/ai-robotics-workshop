//
// File: ros_line_follower_types.h
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
#ifndef RTW_HEADER_ros_line_follower_types_h_
#define RTW_HEADER_ros_line_follower_types_h_
#include "rtwtypes.h"

// Model Code Variants
#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_Float32_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_Float32_

// MsgType=std_msgs/Float32
struct SL_Bus_ros_line_follower_std_msgs_Float32
{
  real32_T Data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ROSVariableLengthArrayInfo_

struct SL_Bus_ROSVariableLengthArrayInfo
{
  uint32_T CurrentLength;
  uint32_T ReceivedLength;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension_

// MsgType=std_msgs/MultiArrayDimension
struct SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension
{
  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=Label_SL_Info:TruncateAction=warn 
  uint8_T Label[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Label
  SL_Bus_ROSVariableLengthArrayInfo Label_SL_Info;
  uint32_T Size;
  uint32_T Stride;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_MultiArrayLayout_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_MultiArrayLayout_

// MsgType=std_msgs/MultiArrayLayout
struct SL_Bus_ros_line_follower_std_msgs_MultiArrayLayout
{
  // MsgType=std_msgs/MultiArrayDimension:IsVarLen=1:VarLenCategory=data:VarLenElem=Dim_SL_Info:TruncateAction=warn 
  SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension Dim[16];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Dim
  SL_Bus_ROSVariableLengthArrayInfo Dim_SL_Info;
  uint32_T DataOffset;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_Float32MultiArray_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_Float32MultiArray_

// MsgType=std_msgs/Float32MultiArray
struct SL_Bus_ros_line_follower_std_msgs_Float32MultiArray
{
  // MsgType=std_msgs/MultiArrayLayout
  SL_Bus_ros_line_follower_std_msgs_MultiArrayLayout Layout;

  // IsVarLen=1:VarLenCategory=data:VarLenElem=Data_SL_Info:TruncateAction=warn
  real32_T Data[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Data
  SL_Bus_ROSVariableLengthArrayInfo Data_SL_Info;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_Bool_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_Bool_

// MsgType=std_msgs/Bool
struct SL_Bus_ros_line_follower_std_msgs_Bool
{
  boolean_T Data;
};

#endif

#ifndef DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_String_
#define DEFINED_TYPEDEF_FOR_SL_Bus_ros_line_follower_std_msgs_String_

// MsgType=std_msgs/String
struct SL_Bus_ros_line_follower_std_msgs_String
{
  // PrimitiveROSType=string:IsVarLen=1:VarLenCategory=data:VarLenElem=Data_SL_Info:TruncateAction=warn 
  uint8_T Data[128];

  // IsVarLen=1:VarLenCategory=length:VarLenElem=Data
  SL_Bus_ROSVariableLengthArrayInfo Data_SL_Info;
};

#endif

#ifndef struct_ros_slroscpp_internal_block_S_T
#define struct_ros_slroscpp_internal_block_S_T

struct ros_slroscpp_internal_block_S_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                // struct_ros_slroscpp_internal_block_S_T

#ifndef struct_ros_slroscpp_internal_block_P_T
#define struct_ros_slroscpp_internal_block_P_T

struct ros_slroscpp_internal_block_P_T
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
};

#endif                                // struct_ros_slroscpp_internal_block_P_T

// Parameters (default storage)
typedef struct P_ros_line_follower_T_ P_ros_line_follower_T;

// Forward declaration for rtModel
typedef struct tag_RTM_ros_line_follower_T RT_MODEL_ros_line_follower_T;

#endif                                 // RTW_HEADER_ros_line_follower_types_h_

//
// File trailer for generated code.
//
// [EOF]
//
