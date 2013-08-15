#! /usr/bin/python

import threading
import time
import rospy
from std_msgs.msg import Int32 #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *

exitFlag = 0
threadLock = threading.Lock()

class myThread (threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print "Starting " + self.name
        threadLock.acquire()
        print_time( self.name, self.counter, 5)
        print "Exiting " + self.name
        threadLock.release()

class myThread2 (threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print "Starting " + self.name
        threadLock.acquire()
        print_time2( self.name, self.counter, 5)
        print "Exiting " + self.name
        threadLock.release()

def print_time(threadName, delay, counter):
    while counter:
        if exitFlag:
            thread.exit()
        time.sleep(delay)
        print "%s: %s" % (threadName, time.ctime(time.time()))
        counter -= 1

def print_time2(threadName, delay, counter):
    while counter:
        counter = int(raw_input("Enter Zero: "))

def callback(data):
    threads = []

    #Create new threads
    thread1 = myThread(1, "Thread-1", 1)
    thread2 = myThread2(2, "Thread-2", 2)
 
    #Start new Threads
    thread1.start()
    thread2.start()

    # Add threads to thread list
    threads.append(thread1)
    threads.append(thread2)

    #Wait for all threads to complete
    for t in threads:
        t.join()

    print"Exiting callback Thread"


def endEffectorListener():
    rospy.init_node('control_receive_ee_command', anonymous=True)
    rospy.Subscriber('/control/arm/end_effector', Int32, callback)
    rospy.spin() 

if __name__ == '__main__':
   #print str(ee.read_angle())
   endEffectorListener()
