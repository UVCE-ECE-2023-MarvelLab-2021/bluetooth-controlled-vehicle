#include "pins.h"

void setup() {
  // setting PWM output pins for direction and speed control of dc motors
  pinMode(rf_pin,OUTPUT);
  pinMode(rr_pin,OUTPUT);
  pinMode(lf_pin,OUTPUT);
  pinMode(lr_pin,OUTPUT);
  Serial.begin(9600); // Communication rate of the Bluetooth Module
}

#include "handleSerial.h"

void loop() {
  recvWithEndMarker();//  receive and store serial data until /n character 
//  defined as the endmarker is obtained

  handleNewData();//  handle the serial input until /n character whenever obtained
//  includes setting the movement control of the bot

  moveCar();//  move the bot based on the controls set
  
  delay(10);
}

#include "vehicleCommands.h"

String msg = ""; // Store message in string
String command = "";
String subCommand = "";
String onOff = "off";

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
  msg = String(receivedChars); // store the serial data obtained in msg
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
