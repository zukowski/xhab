#!/usr/bin/env python

import math
import time
import rospy #loads ros libraries
from std_msgs.msg import String, Int32, Float32 #used for sending mes data in ros
from lib_robotis import * #loads robitis libraries for servos
from findUSBDev import *
from array import *
from xhab.msg import DcMotor, PumpState, LEDState, LinWater, Stepper_Motor, CallBack, ArduinoState

pub = rospy.Publisher('/data/callback',CallBack)
msg = CallBack()

LED_State = array('i', [0,0,0,0,0,0])
Lin_Act_State = 1
Lin_Wat_State = 1
Pump_State = 0
Up_Val_State = 0
Down_Val_State = 0

def callback_led(data):
    msg.cid = data.id
    msg.mid = data.value
    pub.publish(msg)

    LED_State[data.id] = data.value

def callback_dc(data):
    msg.cid = 6
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)

def callback_lin(data):
    msg.cid = 8
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)
    
    if Lin_Act_State == 1:
        Lin_Act_State = 0
    else:
        Lin_Act_State = 1

def callback_linwater(data):
    msg.cid = 9
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)
 
    if Lin_Wat_State == 1:
        Lin_Wat_State = 0
    else:
        Lin_Wat_State = 1

def callback_stepper(data):
    msg.cid = 7
    msg.mid = 1
    pub.publish(msg)
    time.sleep(2)
    msg.mid = 0
    pub.publish(msg)

def callback_pump(data):
    msg.cid = 12
    msg.mid = data.pump_mode
    pub.publish(msg)

    Pump_State == data.pump_mode
 
    time.sleep(1)

    msg.cid = 11
    msg.mid = data.valve_1_mode
    pub.publish(msg)

    Up_Val_State = data.valve_1_mode

    time.sleep(1)

    msg.cid = 10
    msg.mid = data.valve_2_mode
    pub.publish(msg)

    Down_Val_State = data.valve_2_mode

def talker():
    pub_ard = rospy.Publisher('/data/arduino_states', ArduinoState)
    msg = ArduinoState()
    while not rospy.is_shutdown():
        msg.LED0State = LED_State[0]
        msg.LED1State = LED_State[1]
        msg.LED2State = LED_State[2]
        msg.LED3State = LED_State[3]
        msg.LED4State = LED_State[4]
        msg.LED5State = LED_State[5]
        msg.LinActState = Lin_Act_State
        msg.LinActWaterState = Lin_Wat_State
        msg.PumpState = Pump_State
        msg.UpStreamValveState = Up_Val_State
        msg.DownStreamValveState = Down_Val_State
        pub_ard.publish(msg)
        rospy.sleep(1)
    
def listener():
    rospy.init_node('fake_callbacks', anonymous=True)
    rospy.Subscriber('/control/led', LEDState, callback_led)
    rospy.Subscriber('/control/dc_motor', DcMotor, callback_dc)
    rospy.Subscriber('/control/linear_act', DcMotor, callback_lin)
    rospy.Subscriber('/control/linear_act_water', LinWater, callback_linwater)
    rospy.Subscriber('control/stepper_motor', Stepper_Motor, callback_stepper)
    rospy.Subscriber('/control/pump_state', PumpState, callback_pump)
    try:
        talker()
    except rospy.ROSInterruptException:
        pass
    rospy.spin

if __name__ == '__main__':
   listener()
