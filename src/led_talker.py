#!/usr/bin/env python
import roslib
roslib.load_manifest('listener')
import rospy
from std_msgs.msg import String
#from xhab.msg import TrajectoryJointAngles


def talker():
    pub = rospy.Publisher('toggle_led', std_msgs::String)
    rospy.init_node('toggle_led_publish')
    msg = std_msgs::String()
    while not rospy.is_shutdown():
        n = raw_input('enter a 0 or a 1 ')
        msg = n.strip()
        pub.publish(msg)
        rospy.sleep(1)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
