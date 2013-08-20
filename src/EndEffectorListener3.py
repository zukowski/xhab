#! /usr/bin/python

import threading
import time
import rospy
from std_msgs.msg import Int32 #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *

#Set up global variables for servos
try:
    USBPaths = findUSBDev()
    USB1 = USB2Dynamixel_Device(USBPaths[1])
    ee = Robotis_Servo( USB1, 6 )
except:
    print "No Serovs Detected"

exitFlag = 0
threadLock = threading.Lock()
init_load = 0

class myThread (threading.Thread):
    def __init__(self, threadID, name, data):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.data = data

    def run(self):
        print "Starting " + self.name
        threadLock.acquire()
        start_ee_spin( self.name, self.data)
        print "Exiting " + self.name
        threadLock.release()

class myThread2 (threading.Thread):
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.daemon= True
        
    def run(self):
        print "Starting " + self.name
        threadLock.acquire()
        check_for_stop( self.name)
        print "Exiting " + self.name
        threadLock.release()
        
def start_ee_spin(threadName, data):
     print "Inside Start_ee_Spin" 
     if int(data.data) == 1:
         if ee.is_moving() == False:
           ee.init_cont_turn()
         ee.set_angvel(-11.)
     elif int(data.data) == 2:
         if ee.is_moving() == False:
           ee.init_cont_turn()
         ee.set_angvel(11.)
     else:
         ee.kill_cont_turn()
     init_load = abs(ee.read_load())
     print abs(ee.read_load())
     if(abs(ee.read_load()) > init_load + 10 and ee.is_moving()):
         ee.kill_cont_turn()
         ee_mode = 0
         print "Killed Spin"
     print "Out of Loop"

def check_for_stop(threadName):
    stime = time.gmtime().tm_sec
    print "Spawned Thread: " + threadName
    load_ok = 1
    time.sleep(0.25)
    init_load = abs(ee.read_load())
    while load_ok:
        if(abs(abs(ee.read_load())-init_load) > 50 and ee.is_moving()):
            load_ok = 0
            print "Load Killed Spin"
        if(abs(stime - time.gmtime().tm_sec) > 5):
            load_ok = 0
            print "Time Killed Spin"

def callback(data):
    threads = []

    #Create new threads
    thread1 = myThread(1, "Thread-Spin", data)
    thread2 = myThread2(2, "Thread-Check")

    #Start new Threads
    thread1.start()
    thread2.start()

    # Add threads to thread list
    threads.append(thread1)
    threads.append(thread2)

    #Wait for all threads to complete
    for t in threads:
        t.join()
    ee.kill_cont_turn()
    print"Exiting callback Thread"


def endEffectorListener():
    rospy.init_node('control_receive_ee_command', anonymous=True)
    rospy.Subscriber('/control/arm/end_effector', Int32, callback)
    rospy.spin() 

if __name__ == '__main__':
   #print str(ee.read_angle())
   endEffectorListener()
