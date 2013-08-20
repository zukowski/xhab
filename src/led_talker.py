#!/usr/bin/env python
import roslib
#roslib.load_manifest('listener')
import rospy
from std_msgs.msg import String
from xhab.msg import Stepper_Motor  #DcMotor


def talker():
    pub = rospy.Publisher('/control/stepper_motor', Stepper_Motor)
    rospy.init_node('toggle_led_publish')
    msg = Stepper_Motor()
    msg.direction = 1
    #msg.mode = 10
    msg.steps_desired = 2736
    pub.publish(msg)
    rospy.sleep(1)


if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
