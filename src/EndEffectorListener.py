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
     print 'I am in callback '
     if int(data.data) == 1:
        if ee.is_moving() == False:
           ee.init_cont_turn()
        ee.set_angvel(-11.)
     elif int(data.data) == 2:
        if ee.is_moving() == False:
           ee.init_cont_turn()
        ee.set_angvel(11.)
     else:
        ee.kill_cont_turn()
     
def endEffectorListener():
    rospy.init_node('control_receive_ee_command', anonymous=True)
    rospy.Subscriber('/control/arm/end_effector', Int32, callback)
    rospy.spin() 
    
if __name__ == '__main__':
   print str(ee.read_angle())
   endEffectorListener()

