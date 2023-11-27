#ifndef _SLROS_BUSMSG_CONVERSION_H_
#define _SLROS_BUSMSG_CONVERSION_H_

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
#include <std_msgs/MultiArrayDimension.h>
#include <std_msgs/MultiArrayLayout.h>
#include <std_msgs/String.h>
#include "ros_line_follower_types.h"
#include "slros_msgconvert_utils.h"


void convertFromBus(std_msgs::Bool* msgPtr, SL_Bus_ros_line_follower_std_msgs_Bool const* busPtr);
void convertToBus(SL_Bus_ros_line_follower_std_msgs_Bool* busPtr, std_msgs::Bool const* msgPtr);

void convertFromBus(std_msgs::Float32* msgPtr, SL_Bus_ros_line_follower_std_msgs_Float32 const* busPtr);
void convertToBus(SL_Bus_ros_line_follower_std_msgs_Float32* busPtr, std_msgs::Float32 const* msgPtr);

void convertFromBus(std_msgs::Float32MultiArray* msgPtr, SL_Bus_ros_line_follower_std_msgs_Float32MultiArray const* busPtr);
void convertToBus(SL_Bus_ros_line_follower_std_msgs_Float32MultiArray* busPtr, std_msgs::Float32MultiArray const* msgPtr);

void convertFromBus(std_msgs::MultiArrayDimension* msgPtr, SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension const* busPtr);
void convertToBus(SL_Bus_ros_line_follower_std_msgs_MultiArrayDimension* busPtr, std_msgs::MultiArrayDimension const* msgPtr);

void convertFromBus(std_msgs::MultiArrayLayout* msgPtr, SL_Bus_ros_line_follower_std_msgs_MultiArrayLayout const* busPtr);
void convertToBus(SL_Bus_ros_line_follower_std_msgs_MultiArrayLayout* busPtr, std_msgs::MultiArrayLayout const* msgPtr);

void convertFromBus(std_msgs::String* msgPtr, SL_Bus_ros_line_follower_std_msgs_String const* busPtr);
void convertToBus(SL_Bus_ros_line_follower_std_msgs_String* busPtr, std_msgs::String const* msgPtr);


#endif
