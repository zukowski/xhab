#!/usr/bin/env python
import rospy
import glob
from lib_robotis import *
# Find the differnt /dev/ttyUSB* attached to computer
# Then test each device to see what is attached and 
# return the devices as USB0 and USB1

def findUSBDev():
    finalPaths = ["" for x in range(2)]
    dirpath = "/dev/ttyUSB*"
    #Store path to USBDevices
    USBDevList =  glob.glob(dirpath)
    #Determin number of Devices
    numDev = len(USBDevList)
    devToCheck = [];

    for path in USBDevList:
        try:
            USBDev = USB2Dynamixel_Device(path)
        except:
            continue

        servosOnDev = find_servos(USBDev,10)
        if(len(servosOnDev) == 2):
            finalPaths[0] = path
        elif(len(servosOnDev) == 4):
            finalPaths[1] = path
        else:
            print "Edit XHAB Source code to take into account more USB2Dyanmixel Devices"

    return finalPaths
