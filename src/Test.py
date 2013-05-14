#!/usr/bin/python
#
# Using robotis python library from Georgia Tech HRL to move dynamixel servos
# This is a test case and will be used to implement communication with ROS
# using ROS nodes and the roslib
#
######################################################################################
import math
import roslib
roslib.load_manifest('robotis')
import rospy
from robotis.ros_robotis import *
from lib_robotis import *
from findUSBDev import *

USBDevPath = findUSBDev()
USB0 = USB2Dynamixel_Device(USBDevPath[0])
USB1 = USB2Dynamixel_Device(USBDevPath[1])


shoulder1 = Robotis_Servo( USB0, 7)
shoulder2 = Robotis_Servo( USB0, 2)
elbow1 = Robotis_Servo( USB1, 3 )
elbow2 = Robotis_Servo( USB1, 4 )
wrist = Robotis_Servo( USB1, 5 )
ee = Robotis_Servo( USB1, 6 )

shAng1 = shoulder1.read_angle()
shAng2 = shoulder2.read_angle()
elAng1 = elbow1.read_angle()
elAng2 = elbow2.read_angle()
wrAng = wrist.read_angle()
eeAng =  ee.read_angle()

elEncode2 = elbow2.read_encoder();
print 'Shoulder1 angle is ' + str(math.degrees(shoulder1.read_angle()))
print 'Shoulder2 angle is ' + str(math.degrees(shoulder2.read_angle()))
print 'elbow2 angle is ' + str(math.degrees(elbow1.read_angle()))
print 'elbow2 angle is ' + str(math.degrees(elbow2.read_angle()))
print 'wrist angle is ' + str(math.degrees(wrist.read_angle()))
print 'EndEff angle is ' + str(math.degrees(ee.read_angle()))
#ee.init_cont_turn()
#ee.set_angvel(-11.)
n = raw_input("Please enter '1 or 0':")
while n.strip() != '1':
    print '---------------------------------------------'
    print 'Shoulder1 angle is ' + str(math.degrees(shoulder1.read_angle()))
    print 'Shoulder2 angle is ' + str(math.degrees(shoulder2.read_angle()))
    print 'elbow1 angle is ' + str(math.degrees(elbow1.read_angle()))
    print 'elbow2 angle is ' + str(math.degrees(elbow2.read_angle()))
    print 'wrist angle is ' + str(math.degrees(wrist.read_angle()))
    print 'EndEff angle is ' + str(math.degrees(ee.read_angle()))
    print ' '
    print 'Shoulder1 encoder is ' + str(shoulder1.read_encoder())
    print 'Shoulder2 encoder is ' + str(shoulder2.read_encoder())
    print 'elbow1 encoder is ' + str(elbow1.read_encoder())
    print 'elbow2 encoder is ' + str(elbow2.read_encoder())
    print 'wrist encoder is ' + str(wrist.read_encoder())
    print 'EndEff encoder is ' + str(ee.read_encoder())
    print '---------------------------------------------'
#    move = raw_input("Please enter motion: ")
#    move = float(move)
#    ee.move_angle(eeAng+move, blocking = False )
#    eeAng =  ee.read_angle()
#    print(str(eeAng))   
    n = raw_input("Please enter '1 or 0': ")
#ee.kill_cont_turn()
print str(math.degrees(shAng1+1.))
print str(math.degrees(shAng2+1.))
print str(math.degrees(elAng1+0.5))
print str(math.degrees(elAng2+0.5))

#shoulder1.move_angle( shAng1+1., blocking = False )
#shoulder2.move_angle( shAng2+1., blocking = True )
#elbow1.move_angle( elAng1+0.5, blocking = True )
#elbow2.move_angle( elAng2+0.5, blocking = True)


print 'Shoulder1 angle is ' + str(math.degrees(shoulder1.read_angle()))
print 'Shoulder2 angle is ' + str(math.degrees(shoulder2.read_angle()))
print 'elbow1 angle is ' + str(math.degrees(elbow1.read_angle()))
print 'elbow2 angle is ' + str(math.degrees(elbow2.read_angle()))
print 'wrist angle is ' + str(math.degrees(wrist.read_angle()))
print 'EndEff angle is ' + str(math.degrees(ee.read_angle()))
print
#print ee.read_encoder()
#rospy.spin()
#poller.stop() 
