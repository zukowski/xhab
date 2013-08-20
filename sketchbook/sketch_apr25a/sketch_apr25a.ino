//generates 1ms pulse per button press

//sends pulse, directionality as STP,DIR signals

//to bigeasy driver

//because of debouncing, only allows a pulse every 0.2 sec



//assign pins names

int STPoutpin = 22;//pulse to big easy to increment step

int DIRoutpin = 23;//high or low to select direction

//int ENoutpin  = 24;//enable/disables FET outputs

int STPreadpin= 52;//button shorts STPreadpin to GND

int DIRreadpin= 53;//switch shorts DIRreadpin to GND

int LEDpin    = 13;



void setup(){

  pinMode(LEDpin,OUTPUT);

  pinMode(STPoutpin,OUTPUT);

  pinMode(DIRoutpin,OUTPUT);

  pinMode(DIRreadpin,INPUT);

  pinMode(STPreadpin,INPUT);

 // pinMode(ENoutpin,OUTPUT);

  digitalWrite(STPreadpin,HIGH);// enable 5V input pullups

  digitalWrite(DIRreadpin,HIGH);

  digitalWrite(STPoutpin,LOW);//ensure initiate to low

  //digitalWrite(ENoutpin,HIGH);//disable FETs

  digitalWrite(LEDpin,HIGH);//"POR" check

  delay(200);

  digitalWrite(LEDpin,LOW);//"POR" check

  delay(200);

  digitalWrite(LEDpin,HIGH);//"POR" check

  delay(200);

  digitalWrite(LEDpin,LOW);//"POR" check

}



void loop(){

  if (digitalRead(STPreadpin) == LOW){

    digitalWrite(LEDpin,HIGH);

   // digitalWrite(ENoutpin,LOW);//enable FETs

    delay(100);//ignore button noise/debounce

    digitalWrite(DIRoutpin, digitalRead(DIRreadpin));//set direction

    delay(1);//setup time for DIR is 200ns; this is plenty

    digitalWrite(STPoutpin, HIGH);

    delay(1);//hold time for STP is 1us; this is plenty

    digitalWrite(STPoutpin, LOW);
    
    delay(100);

    //digitalWrite(ENoutpin,HIGH);//disable FETs

    while (digitalRead(STPreadpin) == LOW){

     //do nothing until button released 

    }

    delay(100);//ignore noise/debounce

    digitalWrite(LEDpin,LOW);

  }

}
