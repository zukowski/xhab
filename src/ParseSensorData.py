#!/usr/bin/env python
import roslib
roslib.load_manifest('listener')
import rospy
from std_msgs.msg import Int32
from xhab.msg import SensorData

def talker():
    rospy.init_node('data_test', anonymous=True)
    rospy.Subscriber('/data/sensors', SensorData, callback)
    rospy.spin()
    
def callback(data): 
    pub = rospy.Publisher('/data/side_pressure', Int32 )
    msg = Int32()
    while not rospy.is_shutdown():
        msg.data = data.pressure_data.side_pressure
        rospy.loginfo(msg)
        pub.publish(msg)
        rospy.sleep(0.25)

if __name__ == '__main__':
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
