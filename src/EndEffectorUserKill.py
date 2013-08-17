#!/usr/bin/env python
import math
import time
import rospy #loads ros libraries
from std_msgs.msg import Int32 #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *

#Set up global variables for servos
USBPaths = findUSBDev()
USB1 = USB2Dynamixel_Device(USBPaths[1])
ee = Robotis_Servo( USB1, 6 )


def callback(data): 
     ee.kill_cont_turn()
 
def listener():
    rospy.init_node('control_ee_user_kill', anonymous=True)
    rospy.Subscriber('/control/arm/ee_user_kill', Int32, callback)
    rospy.spin() 

if __name__ == '__main__':
   listener()
