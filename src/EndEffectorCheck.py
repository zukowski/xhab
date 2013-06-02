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

def talker():    
    pub = rospy.Publisher('/data/arm/end_effector_status', Int32)
    rospy.init_node('data_pub_ee_status')
    msg = Int32()
    msg.data = 1
    while not rospy.is_shutdown():
        ee_load = ee.read_load()
        if(ee.is_moving() && ee.read_address(0x20)==11):
            if(abs(ee_load) > 300):
                msg.data = 0
        elif(ee.is_moving()):
            if(abs(ee_load) > 1200):
                msg.data = 0
        else
            msg.data = 1
        rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(0.25)

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass

