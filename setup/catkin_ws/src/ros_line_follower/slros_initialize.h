#ifndef _SLROS_INITIALIZE_H_
#define _SLROS_INITIALIZE_H_

#include "slros_busmsg_conversion.h"
#include "slros_generic.h"

extern ros::NodeHandle * SLROSNodePtr;
extern const std::string SLROSNodeName;

// For Block ros_line_follower/Target Linear Velocity/Subscribe
extern SimulinkSubscriber<std_msgs::Float32, SL_Bus_ros_line_follower_std_msgs_Float32> Sub_ros_line_follower_3973;

// For Block ros_line_follower/Target Position from Line Detector
extern SimulinkSubscriber<std_msgs::Float32MultiArray, SL_Bus_ros_line_follower_std_msgs_Float32MultiArray> Sub_ros_line_follower_3799;

// For Block ros_line_follower/Vehicle Interface/Manual Stop/Subscribe
extern SimulinkSubscriber<std_msgs::Bool, SL_Bus_ros_line_follower_std_msgs_Bool> Sub_ros_line_follower_3981;

// For Block ros_line_follower/Vehicle Interface/Motor Cmd Publisher/Publish1
extern SimulinkPublisher<std_msgs::String, SL_Bus_ros_line_follower_std_msgs_String> Pub_ros_line_follower_2305;

void slros_node_init(int argc, char** argv);

#endif
