#!/usr/bin/env python
import roslib
roslib.load_manifest('listener')
import rospy
from std_msgs.msg import Int32


def talker2():
    pub = rospy.Publisher('/control/arm/end_effector', Int32)
    rospy.init_node('control_pub_ee_command')
    while not rospy.is_shutdown():
        n = raw_input('Enter 1, 2 or 0: ')
        msg = Int32(int(n.strip()))
        rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(1.0)


if __name__ == '__main__':
    try:
        talker2()
    except rospy.ROSInterruptException:
        pass
