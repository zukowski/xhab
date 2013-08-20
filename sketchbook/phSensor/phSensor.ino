#include <SoftwareSerial.h> //add the soft serial library
#define rxpin 17 //set the RX pin to pin 2
#define txpin 16 //set the TX pin to pin 3

SoftwareSerial myserial(rxpin, txpin); //enable the soft serial port

String inputstring = ""; //a string to hold incoming data from the PC
String sensorstring = ""; //a string to hold the data from the Atlas Scientific product
boolean input_stringcomplete = false; //have we received all the data from the PC
boolean sensor_stringcomplete = false; //have we received all the data from the Atlas Scientific
                                      //product
void setup(){ //set up the hardware
  Serial2.begin(9600); //set baud rate for the hardware serial port to 38400
  myserial.begin(9600); //set baud rate for software serial port to 38400
  inputstring.reserve(5); //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);//set aside some bytes for receiving data from Atlas Scientific
}                        //product

void serialEvent() { //if the hardware serial port receives a char
  char inchar = (char)Serial2.read(); //get the char we just received
  inputstring += inchar; //add it to the inputString
  if(inchar == '\r') {input_stringcomplete = true;} //if the incoming character is a <CR>,
}                                                    //set the flag

void loop(){ //here we go...
  if (input_stringcomplete){ //if a string from the PC has been received in its entierty
  myserial.print(inputstring); //send that string to the Atlas Scientific product
  inputstring = "";            //clear the string:
  input_stringcomplete = false; //reset the flag used to tell if we have received
  }                                //a completed string from the PC

  while (myserial.available()) {
    char inchar = (char)myserial.read();
    sensorstring += inchar;
    if (inchar == '\r') {sensor_stringcomplete = true;}
    }
  
  if (sensor_stringcomplete){
    Serial.print(sensorstring);
    sensorstring = "";
    sensor_stringcomplete = false;
    }
}

