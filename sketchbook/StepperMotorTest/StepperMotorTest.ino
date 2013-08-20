#include <ArduinoHardware.h>
#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

void messageCb( const std_msgs::String& toggle_msg){
  bool set_led;
  if(toggle_msg.data == "0")
    set_led = HIGH;
  else
    set_led = LOW;
  
  //digitalWrite(13, HIGH-digitalRead(13));
  //LED's
  for(int i=22; i<32; i+=2) {  
    pinMode(i, OUTPUT);
    pinMode(i+1, OUTPUT);

   digitalWrite( i, set_led );
   digitalWrite( i+1, set_led );
  }
}

ros::Subscriber<std_msgs::String> sub("toggle_led", &messageCb );

void setup()
{
  Serial.begin(9600);

  // Ros_Serial stuff
  //nh.initNode();
  //nh.subscribe(sub);
  
  // Stepper Motor Pins
//  pinMode(10,OUTPUT);
//  pinMode(38,OUTPUT);
//  pinMode(39, OUTPUT);
//  digitalWrite(38, HIGH);
//  digitalWrite(39, HIGH);
//  analogWrite(10, 120);

  //Float sensor General I/O pin
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  pinMode(35, OUTPUT);
  digitalWrite(35, LOW);
  pinMode(37, OUTPUT);
  digitalWrite(37, LOW);

  pinMode(32,INPUT);
  digitalWrite(32, HIGH);
  pinMode(34,INPUT);
  digitalWrite(34, HIGH);
  pinMode(36,INPUT);
  digitalWrite(36, HIGH);
  
  //Analog
  pinMode(0, INPUT);  //vegetronic
  pinMode(1, INPUT);  //Side Pressure sensor
  pinMode(2, INPUT);  //back pressure sensor

//  for(int i=22; i<32; i+=2) {  //LED's
//    pinMode(i, OUTPUT);
//    pinMode(i+1, OUTPUT);
//   digitalWrite( i, HIGH );
//   digitalWrite( i+1, HIGH );
  }
}

void loop()
{
  // ROS_Serial stuff
  //nh.spinOnce();
  delay(1);
  
  //analogWrite(11, 128);
  int sensorValue1 = digitalRead(32);
  int sensorValue2 = digitalRead(34);
  int sensorValue3 = digitalRead(36);

  int sensorValue4 = analogRead(0);
  int sensorValue5 = analogRead(1);
  int sensorValue6 = analogRead(2);

  Serial.print("Vegetronic sensor: ");
  Serial.println(sensorValue4);

  Serial.print("Pressure sensors: ");
  Serial.print(sensorValue5);
  Serial.print(", ");
  Serial.println(sensorValue6);

  Serial.print("Level sensor: ");
  Serial.println(sensorValue1);
  Serial.print(", ");
  Serial.print(sensorValue2);
  Serial.print(", ");
  Serial.println(sensorValue3);
  delay(1000);
}

