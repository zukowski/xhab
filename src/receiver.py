#!/usr/bin/env python
import math
import time
import rospy #loads ros libraries
from std_msgs.msg import String #used for sending mes data in ros
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

def callback(data): 
     #Move each of the arm joints to recieved angle
     shoulder1.move_angle( math.radians( float( data.shoulder1_angle ) ) , blocking = False )
     shoulder2.move_angle( math.radians( float( data.shoulder2_angle ) ) , blocking = True )
     elbow1.move_angle( math.radians( float( data.elbow1_angle ) ) , blocking = True )
     elbow2.move_angle( math.radians(float( data.elbow2_angle ) ) , blocking = True )
     wrist.move_angle( wrist.read_angle() + math.radians( float( data.wrist_angle ) ) , blocking = True )
 
def listener():
    rospy.init_node('control_receive_arm_angles', anonymous=True)
    rospy.Subscriber('/control/arm/joint_angles', TrajectoryJointAngles, callback)
    rospy.spin() 
    
if __name__ == '__main__':
   listener()

