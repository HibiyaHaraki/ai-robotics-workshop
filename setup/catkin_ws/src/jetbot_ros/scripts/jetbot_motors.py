#!/usr/bin/env python
import rospy
import time
import re

from Adafruit_MotorHAT import Adafruit_MotorHAT
from std_msgs.msg import String

ref_time = 0;

def watchdog(event):
        global ref_time
        if event.current_real - ref_time  > rospy.Duration.from_sec(1):
                all_stop()
        
# avoid error in use of float()
def is_float(n):
	try:
		float(n)
	except ValueError:
		try:
			int(n)
		except ValueError:
			return 0
		else:
			return int(n)
	else:
		return float(n)


# sets motor speed between [-1.0, 1.0]
def set_speed(motor_ID, value):
	max_pwm = 115.0
	speed = int(min(max(abs(value * max_pwm), 0), max_pwm))

	if motor_ID == 1:
		motor = motor_left
	elif motor_ID == 2:
		motor = motor_right
	else:
		rospy.logerror('set_speed(%d, %f) -> invalid motor_ID=%d', motor_ID, value, motor_ID)
		return
	
	motor.setSpeed(speed)

	if value > 0:
		motor.run(Adafruit_MotorHAT.FORWARD)
	else:
		motor.run(Adafruit_MotorHAT.BACKWARD)


# stops all motors
def all_stop():
	motor_left.setSpeed(0)
	motor_right.setSpeed(0)

	motor_left.run(Adafruit_MotorHAT.RELEASE)
	motor_right.run(Adafruit_MotorHAT.RELEASE)

def shutdownhook():
        all_stop()

# directional commands (degree, speed)
def on_cmd_dir(msg):
        global ref_time
        ref_time = rospy.Time.now()
	rospy.loginfo(rospy.get_caller_id() + ' cmd_dir=%s', msg.data)

# raw L/R motor commands (speed, speed)
def on_cmd_raw(msg):
        global ref_time
        ref_time = rospy.Time.now()
	rospy.loginfo(rospy.get_caller_id() + ' cmd_raw=%s', msg.data)
    	raw_cmd_param = re.split('[,| ]', msg.data) # "speed [-1.0, 1.0]" -> ["speed","-1.0","1.0"]

	if raw_cmd_param[0] != "speed[":
		rospy.logerror(rospy.get_caller_id() + ' invalid cmd_str=%s', msg.data)
	else:
		set_speed(motor_left_ID,   is_float(raw_cmd_param[1]))
		set_speed(motor_right_ID,  is_float(raw_cmd_param[2]))
    	# 10/2/2019 tokamoto end


# simple string commands (left/right/forward/backward/stop)
def on_cmd_str(msg):
        global ref_time
        ref_time = rospy.Time.now()
	rospy.loginfo(rospy.get_caller_id() + ' cmd_str=%s', msg.data)

	if msg.data.lower() == "left":
		set_speed(motor_left_ID,  -1.0)
		set_speed(motor_right_ID,  1.0) 
	elif msg.data.lower() == "right":
		set_speed(motor_left_ID,   1.0)
		set_speed(motor_right_ID, -1.0) 
	elif msg.data.lower() == "forward":
		set_speed(motor_left_ID,   1.0)
		set_speed(motor_right_ID,  1.0)
	elif msg.data.lower() == "backward":
		set_speed(motor_left_ID,  -1.0)
		set_speed(motor_right_ID, -1.0)  
	elif msg.data.lower() == "stop":
		all_stop()
	else:
		rospy.logerror(rospy.get_caller_id() + ' invalid cmd_str=%s', msg.data)


# initialization
if __name__ == '__main__':

	# setup motor controller
	motor_driver = Adafruit_MotorHAT(i2c_bus=1)

	motor_left_ID = 1
	motor_right_ID = 2

	motor_left = motor_driver.getMotor(motor_left_ID)
	motor_right = motor_driver.getMotor(motor_right_ID)

	# stop the motors as precaution
	all_stop()

	# setup ros node
	rospy.init_node('jetbot_motors')
	
        ref_time = rospy.Time.now()
	rospy.Subscriber('~cmd_dir', String, on_cmd_dir)
	rospy.Subscriber('~cmd_raw', String, on_cmd_raw)
	rospy.Subscriber('~cmd_str', String, on_cmd_str)
        rospy.Timer(rospy.Duration.from_sec(0.2), watchdog)
        rospy.on_shutdown(shutdownhook)

	# start running
	rospy.spin()

	# stop motors before exiting
	all_stop()

