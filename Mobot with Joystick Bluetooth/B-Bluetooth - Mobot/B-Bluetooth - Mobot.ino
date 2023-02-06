///////////////////////////////////////////////////////////////////////////////////////////////
////////////                Keanu P. Berches - Mobot                       ////////////////////
////////////                   Arduino Uno, HC-05                           ///////////////////
////////////github: https://github.com/Keanu-Type/Arduino-Mobot-Version-one ///////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

//Motor( Speed, Duration); //change speed value from 0-250 and Duration(Delay) on how long it is on or off. if you want to turn off the Motor, default value is 0.

//NOTE: IF YOU ARE GOING TO USE SOFTWARESERIAL, USE DIFFERENT RX AND TX. 
//NOTE: USE VOLTAGE DIVIDER WITH 2.2K RESISTOR AND 4.7K RESISTOR(SEE DIAGRAM) FOR SOFTWARESERIAL
//      PROCEDURE WHEN USING:
//        CONSTRUCT THE CIRCUIT FIRST(SEE DIAGRAM). THEN POWER ON YOUR ARDUINO(BY BATTERY OR USB/LAPTOP). OPEN AND USE YOUR PHONE. DOWNLOAD BLUETOOTH SERIAL TERMINAL FROM PLAYSTORE AND INSTALL.
//        TURN ON YOUR BLUETOOTH AND SCAN FOR HC-05 THEN TRY TO CONNECT WITH IT. ENTER 1234(DEFAULT) IF PASSWORD IS ASKED. DO NOTE THAT IF IT IS SUCCESSFUL, IT WILL ONLY "PAIRED" WITH THE DEVICE. NOT "CONNECTED" YET
//        OPEN YOUR BLUETOOTH TERMINAL APP. FIND THE OPTION WHERE YOU CAN SEE YOUR BLUETOOTH PAIRED DEVICES AND FIND THE HC-05. IT SHOULD BE "CONNECTED" IF YOU CLICK IT.
//        NOW YOUR HC-05 IS CONNECTED

//----------SOFTWARE SERIAL--------------
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2,4); //Pin 2 = RX(connect Bluetooth TX), Pin 4 = TX(connect Bluetooth RX)
int direction;
//motor one
#define ledpin 13
int enA = 11; //int1 & int2
int Go1 = 10; //int1
int Back1 = 9;  //int2
// motor two
int enB = 3;  //int3 & int4
int Go2 = 5;  //int4
int Back2 = 6;  //int3

//===============================================================================================//
void setup() {
  //Ultrasonic and Servo;
  //Set all Motors 
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);
  BTSerial.begin(9600);
  Serial.begin(9600);
  pinMode(enA, OUTPUT); //POWER
  pinMode(enB, OUTPUT); //POWER
  pinMode(Go1, OUTPUT); //DIRECTION A MOTOR A
  pinMode(Back1, OUTPUT); //DIRECTION B MOTOR A
  pinMode(Back2, OUTPUT); //DIRECTION C MOTOR B 
  pinMode(Go2, OUTPUT); //DIRECTION C MOTOR B
}

//------MOTOR DIRECTION CONTROLLER------//
void MotorHighLow(int ENABLE, int DISABLE, int ENABLE2, int DISABLE2){
  digitalWrite( ENABLE,  HIGH);
  digitalWrite( DISABLE,  LOW);
  digitalWrite( ENABLE2, HIGH);
  digitalWrite( DISABLE2, LOW);
}
//------MOTOR ENGINGE FORWARD AND STOP-------//
void Motor(int speed, int duration){
    analogWrite(enA, speed);
    analogWrite(enB, speed);
    delay(duration);
}


;
//--------------------- MAIN SYSTEM LOOP------------------------------------//
void loop() {
  if (BTSerial.available()){
    char data = BTSerial.read();
    if (data=='U'){
      MotorHighLow(Go1, Back1, Go2, Back2); //MOTOR A FORWARD
      Motor(0, 200);        //STOP THE ENGINE
      Motor(55, 50);        //Engine ON
    }else if(data=='L'){
      MotorHighLow(Back2, Go2, Go1, Back1); //MOTOR GO LEFT
      Motor(0, 200);        //STOP THE ENGINE
      Motor(55, 50);        //Engine ON
    }else if(data=='R'){
      MotorHighLow(Back1, Go1, Go2, Back2);  //MOTOR GO RIGHT
      Motor(0, 200); //STOP THE ENGINE
      Motor(55, 50);        //Engine ON   
    }else if(data=='D'){
      MotorHighLow(Back2, Go2, Back1, Go1); //MOTOR GO DOWN
      Motor(0, 200); //STOP THE ENGINE
      Motor(55, 50);        //Engine ON  
    }else if(data=='S'){
      MotorHighLow(Back2, Go2, Back1, Go1); //STOP
      Motor(0,50);
      Motor(0,200);
    }
  }  
  //FORWARD
}