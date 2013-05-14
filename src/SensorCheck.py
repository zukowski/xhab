#!/usr/bin/env python
import math
import time
import rospy #loads ros libraries
from std_msgs.msg import String #used for sending mes data in ros
from std_msgs.msg import Float32 #used for Float32 message data in ros
from lib_robotis import * #loads robitis libraries for servos
from xhab.msg import SensorData

def AnalogSensorCheck(msg):
    if(msg.fluid_lvl_data.bot_lvl == 0):
        print "Tank is Empty"
    elif(msg.fluid_lvl_data.mid_lvl == 0):
        print "Tank under half-full"
    else:
        print "Tank is full"
    if(msg.presure_data.side > 300):
        print "Side Valve Pressure is TOO HIGH"
    if(msg.pressure_data.back > 300):
        print "Back Valve Pressure is TOO HIGH"

def SerialSensorCheck(msg):
    print "Hi"


def listener():
    rospy.init_node('SensorCheck', anonymous=True)
    rospy.Subscriber('/data/sensors', SensorData, AnalogSensorCheck)
    rospy.Subscriber('/data/ph_sensor', Float32, SerialSensorCheck)
    rospy.spin() 
    
if __name__ == '__main__':
   listener()
