//NOTE: IF YOU ARE GOING TO USE SOFTWARESERIAL, USE DIFFERENT RX AND TX.
//NOTE: HC-05 TX -> ARDUINO RX & HC-05 RX ->ARDUINO TX
//NOTE: USE VOLTAGE DIVIDER WITH 2.2K RESISTOR AND 4.7K RESISTOR(SEE DIAGRAM) FOR SOFTWARESERIAL
//      PROCEDURE WHEN USING:
//        CONSTRUCT THE CIRCUIT FIRST(SEE DIAGRAM). THEN POWER ON YOUR ARDUINO(BY BATTERY OR USB/LAPTOP). OPEN AND USE YOUR PHONE. DOWNLOAD BLUETOOTH SERIAL TERMINAL FROM PLAYSTORE AND INSTALL.
//        TURN ON YOUR BLUETOOTH AND SCAN FOR HC-05 THEN TRY TO CONNECT WITH IT. ENTER 1234(DEFAULT) IF PASSWORD IS ASKED. DO NOTE THAT IF IT IS SUCCESSFUL, IT WILL ONLY "PAIRED" WITH THE DEVICE. NOT "CONNECTED" YET
//        OPEN YOUR BLUETOOTH TERMINAL APP. FIND THE OPTION WHERE YOU CAN SEE YOUR BLUETOOTH PAIRED DEVICES AND FIND THE HC-05. IT SHOULD BE "CONNECTED" IF YOU CLICK IT.
//        NOW YOUR HC-05 IS CONNECTED
// KEANU P. BERCHES
// PSWD: KEANU

//I havent solve yet how to send Bluetooth Int data from HC-05 -> Android
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);  // For Software Serial, the Pin 10 will become RX(Connect HC-05 TX Here) and Pin 11 will become TX(Connect HC-05 RX here)
#define ledpin 13              //built-in LED in UNO
int X_Joy = A0;
int Y_Joy = A1;
int x_Ax, y_Ax;
int SW = 2;

int X_Axis = 0;
int Y_Axis = 0;
int SW_state = 0;
int X_Data;
int Y_Data;
#define ledpin 13  

void setup() {
  BTSerial.begin(9600);
  Serial.begin(9600); 
  pinMode(X_Joy, INPUT);
  pinMode(Y_Joy, INPUT);
  pinMode(SW, INPUT_PULLUP); 
  pinMode(ledpin, OUTPUT);    //LED
  digitalWrite(ledpin, LOW);  //L is OFF  
}

int convertsignals(int num){
  if(num>350){
    num = 2;
  }else if(num<-50){
    num = 0;    
  }else{
    num = 1;
  }
  return num;
 }

void joystick(int X, int Y){
  X_Axis = analogRead(X_Joy);
  Y_Axis = analogRead(Y_Joy);
  SW_state = digitalRead(SW);
   x_Ax = map(X_Axis, 0, 1023, -512, 512);
   y_Ax = map(Y_Axis, 0, 1023, -512, 512);
  X_Data = convertsignals(x_Ax);
  Y_Data = convertsignals(y_Ax);
  
}

void joystickdata(){
  joystick(X_Axis, Y_Axis);
  BTSerial.print(X_Data);
  BTSerial.print(" = X|Y= ");
  BTSerial.println(Y_Data);
  //This will output the actual data of the joystick.
  BTSerial.print(x_Ax);
  BTSerial.print(" =X|Y= ") ;
  BTSerial.println(y_Ax);
  BTSerial.println("-------------");

}
void loop() {
  if (BTSerial.available()) { //IF BLUETOOTH IS CONNECTED TO A DEVICE/ RUN THE CODE. ELSE NONE.
    char x = BTSerial.read(); //READ THE DATA THAT COULD BE RECEIVED FROM THE DEVICE. ONLY CHAR. ONLY 1 CHAR WILL BE RECEIVED PER LOOP IF YOU SENT A STRING
    if(x=='1'){
      digitalWrite(ledpin, HIGH);
    }else if(x=='0'){
      digitalWrite(ledpin, LOW);
    }
  }

  joystick(X_Axis, Y_Axis);
  joystickdata();


  if (Serial.available()) { //IF SERIAL IS AVAILABLE(WHICH IS ON)
    char c = Serial.read(); //THIS WILL READ WHAT WAS THE DATA THAT WAS SENT FROM DEVICE
    BTSerial.write(c); //THIS WILL OUTPUT CHAR
  }

  delay(500);
  //NOTE: SERIAL.AVAILABLE AND BTSERIAL.AVAILABLE RUNS AT THE SAME TIME
}