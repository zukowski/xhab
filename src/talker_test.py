#!/usr/bin/env python
#omkar test code
import math
import time
import rospy #loads ros libraries
from std_msgs.msg import String #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from xhab.msg import TrajectoryJointAngles


def talker():
    pub = rospy.Publisher('/control/arm/joint_angles', TrajectoryJointAngles)
    rospy.init_node('control_pub_joint_angles')
    msg = TrajectoryJointAngles()
    while not rospy.is_shutdown():
	'''this needs to come from the joint_state topic'''
        msg.step_number = 1 # step number
        msg.shoulder1_angle = 100.
        msg.shoulder2_angle = 151.4
        msg.elbow1_angle = 50.
        msg.elbow2_angle = 100.
        msg.wrist_angle = -100.

        rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(200.0)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
