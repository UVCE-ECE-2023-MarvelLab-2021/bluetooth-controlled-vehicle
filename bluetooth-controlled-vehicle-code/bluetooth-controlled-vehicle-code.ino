#include "pinsUsed.h"

int pos = 0; // Servo pose
String msg = ""; // Store message in string

// Receive with an end-marker
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false;

//Move the RC car
String command = "";
String subCommand = "";
String onOff = "off";


void setup() {
  // setting PWM output pins for direction and speed control of dc motors
  pinMode(rf_pin,OUTPUT);
  pinMode(rr_pin,OUTPUT);
  pinMode(lf_pin,OUTPUT);
  pinMode(lr_pin,OUTPUT);
  Serial.begin(9600); // Communication rate of the Bluetooth Module
}

void loop() {
  recvWithEndMarker();//  receive and store serial data until /n character 
//  defined as the endmarker is obtained

  handleNewData();//  handle the serial input until /n character whenever obtained
//  includes setting the movement control of the bot

  moveCar();//  move the bot based on the controls set
  
  delay(10);
}

// handles serial data
void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0'; // terminate the string
            ndx = 0;
            newData = true;
        }
    }
}

void handleNewData() {
  if (newData == true) {
    Serial.println(receivedChars);
    commandControl();
    newData = false;
  }
}


// here are the commands obtained from android application:
// 01on
// 01off
// 02F
// 02B
// 02R
// 02L
// 02S
void commandControl() {
  // Control Servo in Arduino board
  msg = String(receivedChars);
  Serial.println(msg);
  if(msg.substring(0,2)=="01"){
    onOff = msg.substring(2);
  }
  else if(msg.substring(0,2)=="04"){
    botSpeed = msg.substring(2,msg.length()).toInt();
  }
  else if(msg.substring(0,2) == "02"){
    command = msg.substring(0,2);
    subCommand = msg.substring(2,msg.length());
  }
  msg = "";
}

void moveCar() {
  if(onOff == "on"){
    if(command == "02"){
      if(subCommand == "F"){
        moveForward();
      }
      else if(subCommand == "B"){
        moveBackward();
      }
      else if(subCommand == "R"){
        goRight();
      }
      else if(subCommand == "L"){
        goLeft();
      }
      else if(subCommand == "S"){
        stopBot();
      }
    }
  }
  else{
    stopBot();
  }
}

void moveForward(){ 
  Serial.println("Forward...at "+String(botSpeed));
  analogWrite(rf_pin,botSpeed);
  analogWrite(rr_pin,0);
  analogWrite(lf_pin,botSpeed);
  analogWrite(lr_pin,0);
}
void moveBackward(){ 
  Serial.println("Reverse...at "+String(botSpeed));
  analogWrite(rf_pin,0);
  analogWrite(rr_pin,botSpeed);
  analogWrite(lf_pin,0);
  analogWrite(lr_pin,botSpeed);
}
void goRight(){ 
  Serial.println("Right...at "+String(botSpeed));
  analogWrite(rf_pin,0);
  analogWrite(rr_pin,botSpeed);
  analogWrite(lf_pin,botSpeed);
  analogWrite(lr_pin,0);
}
void goLeft(){ 
  Serial.println("Left...at "+String(botSpeed));
  analogWrite(rf_pin,botSpeed);
  analogWrite(rr_pin,0);
  analogWrite(lf_pin,0);
  analogWrite(lr_pin,botSpeed);
}
void stopBot(){ 
  Serial.println("Stopped");
  analogWrite(rf_pin,0);
  analogWrite(rr_pin,0);
  analogWrite(lf_pin,0);
  analogWrite(lr_pin,0);
}
