#!/usr/bin/env python
import roslib
import math
roslib.load_manifest('listener')
import rospy
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *
from xhab.msg import TrajectoryJointAngles

#Set up global variables for servos
USBPaths = findUSBDev()
USB0 = USB2Dynamixel_Device(USBPaths[0])
USB1 = USB2Dynamixel_Device(USBPaths[1])
shoulder1 = Robotis_Servo( USB0, 7 )
shoulder2 = Robotis_Servo( USB0, 2 )
elbow1 = Robotis_Servo( USB1, 3 )
elbow2 = Robotis_Servo( USB1, 4 )
wrist = Robotis_Servo( USB1, 5 )
ee = Robotis_Servo( USB1, 6 )

def talker():
    pub = rospy.Publisher('/data/arm/jointstates', TrajectoryJointAngles)
    rospy.init_node('arm_jointstate_pub')
    msg = TrajectoryJointAngles()
    while not rospy.is_shutdown():
        msg.shoulder1_angle = math.degrees(shoulder1.read_angle())
        msg.shoulder2_angle = math.degrees(shoulder2.read_angle())
        msg.elbow1_angle = math.degrees(elbow1.read_angle())
        msg.elbow2_angle = math.degrees(elbow2.read_angle())
        msg.wrist_angle = math.degrees(wrist.read_angle())

        rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(1.0)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
