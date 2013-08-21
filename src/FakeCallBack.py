#!/usr/bin/env python

import math
import time
import rospy #loads ros libraries
from std_msgs.msg import String, Int32, Float32 #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *
from xhab.msg import DcMotor, PumpState, LEDState, LinWater, Stepper_Motor, CallBack

pub = rospy.Publisher('/data/callback',CallBack)
msg = CallBack()

def callback_led(data):
    msg.cid = data.id
    msg.mid = data.value
    pub.publish(msg)

def callback_dc(data):
    msg.cid = 6
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)

def callback_lin(data):
    msg.cid = 8
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)

def callback_linwater(data):
    msg.cid = 9
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)
 
def callback_stepper(data):
    msg.cid = 7
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)

def callback_pump(data):
    msg.cid = 12
    msg.mid = data.pump_mode
    pub.publish(msg)
 
    time.sleep(1)

    msg.cid = 11
    msg.mid = data.valve_1_mode
    pub.publish(msg)

    time.sleep(1)
    msg.mid = data.valve_2_mode
    pub.publish(msg)

def listener():
    rospy.init_node('fake_callbacks', anonymous=True)
    rospy.Subscriber('/control/led', LEDState, callback_led)
    rospy.Subscriber('/control/dc_motor', DcMotor, callback_dc)
    rospy.Subscriber('/control/linear_act', DcMotor, callback_lin)
    rospy.Subscriber('/control/linear_act_water', LinWater, callback_linwater)
    rospy.Subscriber('control/stepper_motor', Stepper_Motor, callback_stepper)
    rospy.Subscriber('/control/pump_state', PumpState, callback_pump)
    #try:
    #    talker()
    rospy.spin()

if __name__ == '__main__':
   listener()
