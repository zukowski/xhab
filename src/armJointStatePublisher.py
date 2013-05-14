#!/usr/bin/env python
import roslib
roslib.load_manifest('listener')
import rospy
from std_msgs.msg import String
from findUSBDev import *
from xhab.msg import TrajectoryJointAngles

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
    global shoulder1
    global shoulder2
    global elbow1
    global elbow2
    global wrist
    pub = rospy.Publisher('/data/arm/joint_angles', TrajectoryJointAngles)
    rospy.init_node('data_pub_joint_angles')
    msg = TrajectoryJointAngles()
    while not rospy.is_shutdown():
        msg.step_number = 1 # step number
        msg.shoulder1_angle = math.degrees(shoulder1.read_angle());
        msg.shoulder2_angle = math.degrees(shoulder2.read_angle());
        msg.elbow1_angle = math.degrees(elbow1.read_angle());
        msg.elbow2_angle = math.degrees(elbow2.read_angle());
        msg.wrist_angle = math.degrees(wrist.read_angle());

        rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(0.25)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
