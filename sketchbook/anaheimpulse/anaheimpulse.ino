//generates 1ms pulse per button press
//sends pulse, directionality as STP,DIR signals
//to bigeasy driver
//because of debouncing, only allows a pulse every 0.2 sec
//last updated 1may by tjv
//assign pins names

//note: some of this code is leftover from anaheim but whatever
int STPouthi = 22;//lo->hi pulses
int STPoutlo = 24;//hi->lo pulses
int DIRoutpin = 23;
int STPreadpin= 52;//button shorts STPreadpin to GND
int DIRreadpin= 53;//switch shorts DIRreadpin to GND
int LEDpin = 13;
int ENpin = 26;//EN/EN_N to chip to hold or not
int PWMpin = 28;
void setup(){
  pinMode(STPouthi,OUTPUT);
  pinMode(STPoutlo,OUTPUT);
  pinMode(ENpin,OUTPUT);
  pinMode(PWMpin,OUTPUT);
  pinMode(LEDpin,OUTPUT);
  pinMode(DIRoutpin,OUTPUT);
  pinMode(29,OUTPUT);//just make this low for DIR in case using PWM
  digitalWrite(29,LOW);
  pinMode(DIRreadpin,INPUT);
  pinMode(STPreadpin,INPUT);
  digitalWrite(PWMpin,LOW);
  digitalWrite(ENpin,HIGH);//active low
  digitalWrite(STPouthi,LOW);//initilazie
  digitalWrite(LEDpin,LOW);
  digitalWrite(STPreadpin,HIGH);// enable 5V pullups
  digitalWrite(DIRreadpin,HIGH);
  digitalWrite(STPoutlo,HIGH);//ensure initiate to low
}
void loop(){
  if (digitalRead(STPreadpin) == LOW){
    digitalWrite(ENpin,LOW);//turn on FETs
    digitalWrite(LEDpin,HIGH);
    delay(100);//ignore noise/debounce
    digitalWrite(DIRoutpin, digitalRead(DIRreadpin));//set direction
    delay(1);//setup time for DIR is 200ns; this is plenty
    digitalWrite(STPouthi, HIGH);
    digitalWrite(STPoutlo,LOW);
    delay(1);//hold time for STP is 1us; this is plenty
    digitalWrite(STPouthi, LOW);
    digitalWrite(STPoutlo,HIGH);
    while (digitalRead(STPreadpin) == LOW){//output 1kHz while pressed
     digitalWrite(PWMpin,HIGH);
     delay(1);
     digitalWrite(PWMpin,LOW);
     delay(1);
    }
    delay(100);//ignore noise/debounce
    digitalWrite(ENpin,HIGH);//turn off FETs
    digitalWrite(LEDpin,LOW);
  }
}
