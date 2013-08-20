#!/usr/bin/env python

import math
import time
import rospy #loads ros libraries
from std_msgs.msg import String, Int32, Float32 #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *
from xhab.msg import DcMotor, PumpState, LEDState, LinWater, Stepper_Motor, CallBack


def callback_led(data):
    print "LED"
def callback_dc(data):
    print "LED"
def callback_lin(data):
    print "LED"
def callback_linwater(data):
    print "LED"
def callback_stepper(data):
    print "LED"
def callback_pump(data):
    print "LED"
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
