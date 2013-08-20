#!/usr/bin/env python
import roslib
roslib.load_manifest('listener')
import rospy
from xhab.msg import LEDState


def talker2():
    pub = rospy.Publisher('/control/led', LEDState)
    rospy.init_node('control_led_level')
    msg = LEDState()
    #while not rospy.is_shutdown():
    msg.id = 2
    msg.value = 0
    #msg.direction = 1
    #msg.enable_hold = False
    #msg.steps_desired = 1000
    rospy.loginfo(msg)
    pub.publish(msg)
    rospy.sleep(1.0)


if __name__ == '__main__':
    try:
        talker2()
    except rospy.ROSInterruptException:
        pass
