#!/usr/bin/env python
import roslib
roslib.load_manifest('listener')
import rospy
from std_msgs.msg import String
from xhab.msg import TrajectoryJointAngles


def talker():
    pub = rospy.Publisher('/control/arm/joint_angles', TrajectoryJointAngles)
    rospy.init_node('control_pub_joint_angles')
    msg = TrajectoryJointAngles()
    #while not rospy.is_shutdown():
    msg.step_number = 1 # step number
    msg.shoulder1_angle = 109.226373626
    msg.shoulder2_angle = 108.42954823
    msg.elbow1_angle = 202.373626374
    msg.elbow2_angle = 147.076923077
    msg.wrist_angle = 150

    rospy.loginfo(msg)
    pub.publish(msg)
    rospy.sleep(200.0)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
