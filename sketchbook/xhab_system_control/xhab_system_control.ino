/*
Total sketch file for controlling XHAB system using ROS.
To communicate with roscore need to run:
rosrun rosserial_python serial_node.py <dev path> <_baud:='rate' optional>
Creates 1 node that publishes to 1 topic: /data/sensor_data and 
subscribes to 5 topics:
/control/led
/control/dc_motor
/control/linear_act
/control/pump_state
/control/stepper_motor
publishes to 5 topics:
/data/arduino_states
/data/callback
/data/sensor_data
/data/ec_data
/data/ph_data
Last Modded:
Aug. 17 2013, Scott Mishra
*/

#include <Arduino.h>
#include <stdlib.h>
#include <ros.h> //Needed to talked to roscore and use ros functions
#include <xhab/LEDState.h> //Custom defined msg type for LED control
#include <xhab/DcMotor.h> //Custom defined msg type for Motor control
#include <xhab/Stepper_Motor.h> //Custom defined msg type for Motor control
#include <xhab/PumpState.h> //Custom defined msg type for Pump and valve control
#include <xhab/Stop_Motor.h> //custom defined msg type for stopping motors
#include <std_msgs/Int32.h> //std msg type in ros for int32
#include <std_msgs/Float32.h> // stf msg type in ros for float32
#include <std_msgs/String.h> //std msg type in ros for Strings
#include <xhab/pin_defs.h> //header file with all pin numbers defined
#include <xhab/SensorData.h> //Custom defined msg type for analog and digital sensor data collection
#include <xhab/LinWater.h> //Custom defined msg type for linear actuator for watering station
#include <xhab/CallBack.h> //Custom defined msg  type for arduino to confirm user commands
#include <xhab/ArduinoState.h> //Custom defined msg type for component states
#include <actionlib_tutorials/AveragingAction.h>

std_msgs::String error_msg;
xhab::CallBack callback_msg;

ros::NodeHandle nh;//ROS CORE  Contact;
ros::Publisher error_data("/data/error_msg", &error_msg);
ros::Publisher callback_data("/data/callback", &callback_msg);


long phReadInterval = 1000;
long previousMillisPH = 0;
int PHState = HIGH;
float PH_Val;
int counter_test = 0;
int waterStationCheck = 1;

int stop_received_array[] = {0, 0, 0};
int arduinoStateArray[11];

void led_command(const xhab::LEDState& light_cmd) {
  /* Callback function for the '/control/led' topic
  I* when msg is broadcast on this topic, led_command is
   * called and adjusts the brightness of the specified 
   * led board
   */
  int LEDPinNum = LEDPinNumber(light_cmd.id);
  switch(light_cmd.value) {
   case 0:
   //level 0 is all off
      digitalWrite( LEDPinNum, HIGH ); 
      digitalWrite( LEDPinNum+1, HIGH );
      break;
   case 1:
   //level 1 is lowest on
      digitalWrite( LEDPinNum, HIGH ); 
      digitalWrite( LEDPinNum+1, LOW );
      break;
   case 2:
   //level 2 is medium brightness      
      digitalWrite( LEDPinNum, LOW ); 
      digitalWrite( LEDPinNum+1, HIGH );
      break;
   case 3:
   //level 3 is high brightness
      digitalWrite( LEDPinNum, LOW ); 
      digitalWrite( LEDPinNum+1, LOW );
      break;
  }
  CheckLedPin(LEDPinNum); //Check pin ID's pin levels and call talker
}

int LEDPinNumber(int LEDId){
  /* LEDPinNumber return the LED board number
   * based on the LEDId passed to the function
   * all the LED_# are defined in the pin_defs.h
   * file.
   */
  switch(LEDId) {
      case 0:
         return LED_1;
      case 1:
         return LED_2;
      case 2:
         return LED_3;
      case 3:
         return LED_4;
      case 4:
         return LED_5;
      case 5:
         return LED_6;
      default:
         return LED_1;
    }
}

void CheckLedPin(int LEDId){
  int returnCheck = 4;
  int LEDNum = 0;
  int pin1 = digitalRead(LEDId);
  int pin2 = digitalRead(LEDId+1);
  
  if(pin1 == 0 && pin2 == 0){
      returnCheck = 3;
  }
  else if(pin1 == 1 && pin2 == 0){
      returnCheck = 2;
  }
  else if(pin1 == 0 && pin2 == 1){
      returnCheck = 1;
  }
  else if(pin1 == 1 && pin2 == 1){
      returnCheck = 0;
  }
  if(LEDId == 24)
     LEDNum = 0;
  else if(LEDId == 26)
     LEDNum = 1;
  else if(LEDId == 28)
     LEDNum = 2;
  else if(LEDId == 32)
     LEDNum = 3;
  else if(LEDId == 30)
     LEDNum = 4;
  else
     LEDNum = 5;
   
  callback_msg.cid = LEDNum;
  callback_msg.mid = returnCheck;
  callback_data.publish(&callback_msg);
}

int getLEDState(int LEDId){
  int returnCheck = 4;
  int pin1 = digitalRead(LEDId);
  int pin2 = digitalRead(LEDId+1);
  
  if(pin1 == 0 && pin2 == 0){
      returnCheck = 3;
  }
  else if(pin1 == 1 && pin2 == 0){
      returnCheck = 2;
  }
  else if(pin1 == 0 && pin2 == 1){
      returnCheck = 1;
  }
  else if(pin1 == 1 && pin2 == 1){
      returnCheck = 0;
  }
  return returnCheck;
}

void dcmotor_command(const xhab::DcMotor& dc_motor_msg){
  /* Callback function called when '/control/dc_motor' topic
   * has a msg broadcast on it. Rotates the DC Motor for 5 secs
   * or stops the motion on the DC Motor
   */
  callback_msg.cid = 6;
  callback_msg.mid = 1;
  callback_data.publish(&callback_msg);
  
  digitalWrite(ENABLE_HOLD,LOW);
  delay(1000);
  
  if(dc_motor_msg.direction == 0)
      digitalWrite(DC_MOTOR_DIR,LOW);
  else
      digitalWrite(DC_MOTOR_DIR,HIGH);
      
  analogWrite(DC_MOTOR_PWM,255);
  //delay(1000);
  listenForStop(dc_motor_msg.mode*1000,0);
  analogWrite(DC_MOTOR_PWM,1);
  digitalWrite(ENABLE_HOLD,HIGH);
  
  callback_msg.mid = 0;
  callback_data.publish(&callback_msg);
}

void listenForStop(int delayTime,int type){
  /* Listens for Stop Message to stop motor motion
   */
  int counter = 0;
  while(counter*10 < delayTime){
    delay(10);
    counter += 1;
    if(stop_received_array[type] == 1){
      stop_received_array[type] = 0;
      break;
    }
  }
}

void linear_act_command(const xhab::DcMotor& lin_act_msg){
  /* Callback function called when '/control/linear_act' topic
   * has a msg broadcast on it. Extends or retract the linear actuator
   */
  callback_msg.cid = 8;
  callback_msg.mid = 1;
  callback_data.publish(&callback_msg);
  
  if(lin_act_msg.direction == 0){
      digitalWrite(LIN_ACT_DIR,HIGH);//retracts linear act
      waterStationCheck = 1;
  }
  else{
      digitalWrite(LIN_ACT_DIR,LOW); //extends linear act
      waterStationCheck = 0; 
  }
  if(lin_act_msg.mode != 1){
      analogWrite(LIN_ACT_PWM,168);
      delay(lin_act_msg.mode);
      analogWrite(LIN_ACT_PWM,0);
  }
  else{
      analogWrite(LIN_ACT_PWM,0);
  }
  
  delay(500);
  callback_msg.mid = 0;
  callback_data.publish(&callback_msg);
}

void linear_act_water_command(const xhab::LinWater& lin_act_msg){
  /* Callback function called when '/control/linear_act' topic
   * has a msg broadcast on it. Extends or retract the linear actuator
   */
   callback_msg.cid = 9;
   callback_msg.mid = 1;
   callback_data.publish(&callback_msg);
   
   digitalWrite( LIN_ACT_WATER_ONE, lin_act_msg.pin_one );
   digitalWrite( LIN_ACT_WATER_TWO, lin_act_msg.pin_two );
   delay(lin_act_msg.mode);
   digitalWrite( LIN_ACT_WATER_ONE, LOW );
   digitalWrite( LIN_ACT_WATER_TWO, LOW );
   if(lin_act_msg.pin_one == 1 && lin_act_msg.pin_two == 0){
     waterStationCheck = 0;
   }
   else{
     waterStationCheck = 1;
   }
   delay(500);
   callback_msg.mid = 0;
   callback_data.publish(&callback_msg);
}

void pump_command(const xhab::PumpState& pump_msg){
  /* Callback function called when '/control/pump_state' topic
   * broadcasts a msg. Sets the mode for the pump and sets the
   * mode for the side and back valves
   */
  if(pump_msg.pump_mode == 1)
     digitalWrite(PUMP_MODE,HIGH);
  else
     digitalWrite(PUMP_MODE,LOW);
     
  callback_msg.cid = 12;
  callback_msg.mid = digitalRead(PUMP_MODE);
  callback_data.publish(&callback_msg);
  delay(500);
  
  if(pump_msg.valve_1_mode == 1)
     digitalWrite(SIDE_VALVE_MODE,HIGH);
  else
     digitalWrite(SIDE_VALVE_MODE,LOW);
  
  callback_msg.cid = 11;
  callback_msg.mid = digitalRead(SIDE_VALVE_MODE);
  callback_data.publish(&callback_msg);
  delay(500);
  
  if(pump_msg.valve_2_mode == 1)
     digitalWrite(BACK_VALVE_MODE,HIGH);
  else
     digitalWrite(BACK_VALVE_MODE,LOW); 
  
  callback_msg.cid = 10;
  callback_msg.mid = digitalRead(BACK_VALVE_MODE);
  callback_data.publish(&callback_msg);
     
}

void stepper_command(const xhab::Stepper_Motor& stepper_msg){
  /* Callback function called when '/control/stepper_motor' topic
   * broadcasts a msg.
   */
   
   callback_msg.cid = 7;
   if(waterStationCheck == 0){
     callback_msg.mid = 3;
   }
   else{
   callback_msg.mid = 1;
   callback_data.publish(&callback_msg);
   
   counter_test = 0;
   digitalWrite(ENABLE_HOLD,LOW);//turn on FETs
   delay(10);//ignore noise/debounce
   digitalWrite(STEP_DIR,stepper_msg.direction);//set direction
   delay(1);//setup time for DIR is 200ns; this is plenty
   while (counter_test < stepper_msg.steps_desired){
       //output 1kHz while pressed
       digitalWrite(STEP_PWM,HIGH);
       delay(10);
       digitalWrite(STEP_PWM,LOW);
       delay(10);
       counter_test += 1;
   }
   delay(100);//ignore noise/debounce
   digitalWrite(ENABLE_HOLD,HIGH);//turn off FETs
   counter_test = 1000;
   
   callback_msg.mid = 0;
   }
   callback_data.publish(&callback_msg);
}

int getPHvalue() {
 unsigned long currentMillisPH = millis();
 
   if(currentMillisPH - previousMillisPH > phReadInterval) {
      previousMillisPH = currentMillisPH;  
      if (PHState == HIGH)  {
         PHState = LOW;
         }
      else  {
         PHState = HIGH;
         delay(10);
         Serial1.print("R\r");
         while (Serial1.available() > 0) {
             // Serial1.parseFloat looks for the next valid float number
            // in the serial stream. In this case on hardware serial 1
            PH_Val = Serial1.parseFloat();
            // look for the carriage return. That's the end of your sentence:
            if (Serial1.read() == '\r') {
            return PH_Val;  // can be used for debug, pc display etc.
            }
         }
      }
   }
}

int getECvalue() {
  return 0; 
}
  
void stop_motor_command(const xhab::Stop_Motor& stop_motor_msg){
  stop_received_array[stop_motor_msg.motor_type] = stop_motor_msg.motor_mode;
}

int getLinActState(){
  int linActState = digitalRead(LIN_ACT_DIR);
  return linActState;
}

int getPumpState(){
  int pumpState = digitalRead(PUMP_MODE);
  return pumpState;
}

int getUpStreamState(){
  int upStreamState = digitalRead(SIDE_VALVE_MODE);
  return upStreamState;
}

int getDownStreamState(){
  int downStreamState = digitalRead(BACK_VALVE_MODE);
  return downStreamState;
}

void getArduinoState(int *stateArray){
  
  int waterStationState = 0;
  
  stateArray[0] = getLEDState(LED_1);
  stateArray[1] = getLEDState(LED_2);
  stateArray[2] = getLEDState(LED_3);
  stateArray[3] = getLEDState(LED_4);
  stateArray[4] = getLEDState(LED_5);
  stateArray[5] = getLEDState(LED_6);
  stateArray[6] = getLinActState();
  
  if(waterStationCheck == 1 && stateArray[6] == 1){
    waterStationState = 0;
  }
  else if(waterStationCheck == 1 && stateArray[6] == 0){
    waterStationState = 1;
  }
  else
    waterStationState = 0;
    
  stateArray[7] = waterStationState;
  stateArray[8] = getPumpState();
  stateArray[9] = getUpStreamState();
  stateArray[10] = getDownStreamState();
  
}

ros::Subscriber<xhab::LEDState> subLED("/control/led", led_command);
ros::Subscriber<xhab::DcMotor> subDCMotor("/control/dc_motor", dcmotor_command);
ros::Subscriber<xhab::DcMotor> subLinAct("/control/linear_act", linear_act_command);
ros::Subscriber<xhab::PumpState> subPump("/control/pump_state", pump_command);
ros::Subscriber<xhab::Stepper_Motor> subStepper("/control/stepper_motor",stepper_command);
ros::Subscriber<xhab::Stop_Motor> subStop("/control/stop",stop_motor_command);
ros::Subscriber<xhab::LinWater> subLinActWater("/control/linear_act_water",linear_act_water_command);

xhab::SensorData sensor_data_msg;
xhab::ArduinoState state_msg;
std_msgs::Float32 ph_data_msg;
std_msgs::Float32 ec_data_msg;
std_msgs::Int32 count_msg;

ros::Publisher sensor_data("/data/sensors", &sensor_data_msg);
ros::Publisher ph_data("/data/ph_sensor", &ph_data_msg);
ros::Publisher ec_data("/data/ec_sensor", &ec_data_msg);
ros::Publisher state_data("/data/arduino_states", &state_msg);

void setup() {  
  Serial.begin(9600); //set baudrate for hardware
  Serial1.begin(38400); //ser baudrate for RX/TX 1
  
  int LedArray[] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6};
  
  for(int i=0; i<6; i+=1) {
      /* Sets the pins for the LED boards and make sure they are intialized
       * in the OFF state.!!!NOTE!!! HIGH = 0 and LOW = 1 to the boards
       */  
      pinMode(LedArray[i], OUTPUT);
      pinMode(LedArray[i]+1, OUTPUT);
      digitalWrite(LedArray[i], HIGH);     
      digitalWrite(LedArray[i]+1, HIGH);  
  }
  
  //Set up Dc Motor Control
  pinMode(DC_MOTOR_DIR,OUTPUT);//DC Motor Dir
  pinMode(DC_MOTOR_PWM,OUTPUT);//DC Motor Speed
  digitalWrite(DC_MOTOR_DIR,HIGH);//CW Spin
  //Set up Linear Act
  pinMode(LIN_ACT_DIR,OUTPUT); //Lin. Act. Dir
  pinMode(LIN_ACT_PWM,OUTPUT); //Lin. Act. Turn Mode
  digitalWrite(LIN_ACT_DIR,LOW); //Defaults Lin. Act. Dir to in
  //Set up Linear Act 2
  pinMode(LIN_ACT_WATER_ONE,OUTPUT); //Lin. Act. One
  pinMode(LIN_ACT_WATER_TWO,OUTPUT); //Lin. Act. Two
  //Set up Stepper Motor
  pinMode(ENABLE_HOLD,OUTPUT);
  pinMode(STEP_PWM,OUTPUT);
  pinMode(STEP_DIR,OUTPUT);
  pinMode(29,OUTPUT);//just make this low for DIR in case using PWM
  digitalWrite(29,LOW);
  digitalWrite(STEP_PWM,LOW);
  digitalWrite(ENABLE_HOLD,HIGH);//active low 
  
  //Set up Pump Pins
  pinMode(PUMP_MODE,OUTPUT);
  pinMode(SIDE_VALVE_MODE,OUTPUT);
  pinMode(BACK_VALVE_MODE,OUTPUT);  
  
  //Set up Sensors
  pinMode(TOP_LEVEL_READ,INPUT);
  pinMode(TOP_LEVEL_OUT,OUTPUT);
  pinMode(MID_LEVEL_READ,INPUT);
  pinMode(MID_LEVEL_OUT,OUTPUT);
  pinMode(BOTTOM_LEVEL_READ,INPUT);
  
  pinMode(BOTTOM_LEVEL_OUT,OUTPUT);
  digitalWrite(TOP_LEVEL_OUT,LOW);
  digitalWrite(TOP_LEVEL_READ,HIGH);
  digitalWrite(MID_LEVEL_OUT,LOW);
  digitalWrite(MID_LEVEL_READ,HIGH);
  digitalWrite(BOTTOM_LEVEL_OUT,LOW); 
  digitalWrite(BOTTOM_LEVEL_READ,HIGH); 
  
  //initialize Actuators
  //Watering Station
   digitalWrite( LIN_ACT_WATER_ONE,LOW );
   digitalWrite( LIN_ACT_WATER_TWO, HIGH );
   delay(5000);
   digitalWrite( LIN_ACT_WATER_ONE, LOW );
   digitalWrite( LIN_ACT_WATER_TWO, LOW );
  //Moisture Sensor
  digitalWrite(LIN_ACT_DIR,HIGH);//retracts linear act
  analogWrite(LIN_ACT_PWM,168);
  delay(5000);
  analogWrite(LIN_ACT_PWM,0);
  
  //initialize Arduino Node
  nh.initNode();
  //start publisher for sensor data
  nh.advertise(sensor_data);
  //start publisher for ph data
  nh.advertise(ph_data);
  //start publisher for ec data
  nh.advertise(ec_data);
  //start publisher for error msg
  nh.advertise(error_data);
  //start publisher for callback msg
  nh.advertise(callback_data);
  //start publisher for arduino state messages
  nh.advertise(state_data);
  //init LED Control Node
  nh.subscribe(subLED);
  //init DCMotor Node
  nh.subscribe(subDCMotor);
  //init Linear Act. Node
  nh.subscribe(subLinAct);
  //init Pump Node
  nh.subscribe(subPump);
  //init Stepper Motor
  nh.subscribe(subStepper);
  //init Stop Motor
  nh.subscribe(subStop);
  //init Lin Act Water
  nh.subscribe(subLinActWater);
}

void loop() {
  
  sensor_data_msg.fluid_lvl_data.top_lvl = !digitalRead(TOP_LEVEL_READ);
  sensor_data_msg.fluid_lvl_data.mid_lvl = digitalRead(MID_LEVEL_READ);
  sensor_data_msg.fluid_lvl_data.bot_lvl = digitalRead(BOTTOM_LEVEL_READ);
  sensor_data_msg.moisture_data = analogRead(VEGETRONIX_READ);
  sensor_data_msg.pressure_data.side_pressure = analogRead(SIDE_PRESSURE_READ);
  sensor_data_msg.pressure_data.back_pressure = analogRead(BACK_PRESSURE_READ);
  
  sensor_data.publish(&sensor_data_msg);
  
  ph_data_msg.data = getPHvalue();
  ph_data.publish(&ph_data_msg);
  
  ec_data_msg.data = getECvalue();
  ec_data.publish(&ec_data_msg);
  
  getArduinoState(arduinoStateArray);
  state_msg.LED0State = arduinoStateArray[0];
  state_msg.LED1State = arduinoStateArray[1];
  state_msg.LED2State = arduinoStateArray[2];
  state_msg.LED3State = arduinoStateArray[3];
  state_msg.LED4State = arduinoStateArray[4];
  state_msg.LED5State = arduinoStateArray[5];
  state_msg.LinActState = arduinoStateArray[6];
  state_msg.LinActWaterState = arduinoStateArray[7];
  state_msg.PumpState = arduinoStateArray[8];
  state_msg.UpStreamValveState = arduinoStateArray[9];
  state_msg.DownStreamValveState = arduinoStateArray[10];
  
  state_data.publish(&state_msg);
  //spin Node
  nh.spinOnce();
  delay(2000);
}
