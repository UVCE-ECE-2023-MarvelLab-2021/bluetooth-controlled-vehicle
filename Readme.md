# Bluetooth Controlled Vehicle
Bluetooth is a communication protocol used for wireless transfer of data between two devices that support this protocol. Here, a vehicle is controlled by transmitting commands to it remotely from a smartphone to a bluetooth module which communicates with a microcontroller placed on the vehicle. The microcontroller used here is an Arduino to which a bluetooth module "hc-05" is fitted to support the communication protocol.

## What is...
### 1. Bluetooth
<p>Bluetooth is a communication protocol used to transfer data via a 2.4GHz wireless link. It is used for short range, low power, low cost wireless communication between two devices that supports the protocol.</p>
<p>In order to communicate, two bluetooth devices must be connected to each other. If both devices have no information of each other, they must form a bond via an <strong>inquiry</strong> process during which information such as address of each device is shared with the other. Once connected, both devices can communicate with each other and automatically reestablish connection whenever the devices are powered on and are close enough.</p>
<p>Bluetooth can be used for serial communication between devices using single transmission and reception channel.</p>

### 2. HC-05
<p>HC-05 is a bluetooth module used for wireless communication between serial enabled devices. Since some microcontrollers such as Arduino Uno doesn't come with in-built bluetooth communication capability, additional bluetooth modules such as HC-05 is added to the microcontroller to facilitate bluetooth communication between the microcontroller and other bluetooth devices. Such modules relay the data transferred from a bluetooth device to the microcontroller via suitable protocol such as UART.</p>
</br>
<p align="left">
  <img src="images/hc051.jpg" alt="HC05" style="height:250px"/>
</p>
</br>

### 3. PWM
<p>Which stands for pulse width modulation is a process of varying the time for which a pulse remains ON. This way the average power delivered by a signal can be controlled. The longer the pulse remains ON compared to its OFF time, the higher the total power supplied to the load.</p>
<p>Duty cyle represents the proportion of ON time of a pulse to its total time period. It is represented in percentage.</p>
</br>
<p align="left">
  <img src="images/Duty_Cycle_Examples.png" alt="PWM examples" style="height:250px"/>
</p>
</br>
An Arduino uno has 6 PWM output pins (3,5,6,9,10,11) labeled with ~ sign. PWM signals can be given using the in-built function "analogWrite()" in Arduino IDE.
</br>

### 4. L298N
<p>L298N is a dual channel motor driver. The H bridge is used to control the direction of the motors by provding HIGH(1) and LOW(0) signals to the direction control pins (IN1,IN2,IN3,IN4).The speed can be controlled by proving PWM signals to these pins.</p>
<p align="left">
  <img src="images/l298n.avif" alt="L298N" style="height:250px"/>
</p>

## Components 
<ul>
<li>HC05 bluetooth module x 1</li>
<li>Arduino Uno X 1</li>
<li>DC motor(generic) X 4</li>
<li>Jumper wires(generic) X 1</li>
<li>L298N motor driver X 1</li>
<li>USB A to B cable X 1</li>
</ul>

## Software
<ul>
<li>Android Studio</li>
<li>Arduino IDE</li>
</ul>

## Android App
<p>An Android application was developed to send commands to Arduino via smartphone running Android OS. The application was successfully run on two devices -> SAMSUNG ON7 PRIME (2018) and SAMSUNG GALAXY A7(2018). The application has to be uploaded to the smartphone using Android Studio.</p>
<p><a href="https://developer.android.com/studio?gclid=Cj0KCQjw6pOTBhCTARIsAHF23fJyE-J0Kflu8HXbyOdM9hnISKiziOTw5KLgls7m0CaNfASfBH3aokgaAs9-EALw_wcB&gclsrc=aw.ds">Installing Android Studio</a></p>
<p><a href="https://github.com/baitMaker/bluetooth-comm-app-android">Android App source code</a></p>
<p><a href="https://medium.com/code-yoga/how-to-link-android-studio-with-github-312037a13b99">Install App from github</a></p>
<p><strong>Warning: </strong>Do the above at your own risk. Author not responsible for damages caused by following these actions.</p>


## Working
<p>The commands are displayed as interactive buttons in the application. Commands are send to the vehicle to perform desired action. The smartphone transfers the commands to the bluetooth module serially using bluetooth protocol. The commands are then conveyed to the microcontroller which in turn send appropriate PWM signals to the L298N motor driver which in turn drives the motors in the required direction and prescribed speed in order to execute the command.</p>

## Code
Code used to program the arduino
<details>
<summary>Click to expand code...</summary>
<p>

```c++
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

String msg = ""; // Store message from the app
String command = ""; // store command
String subCommand = ""; // store subcommand
String onOff = "off"; // store whether the vehicle is turned ON/OFF

/*
// here are the commands obtained from android application:
// 01on to turn the vehicle ON
// 01off to turn the vehicle OFF
// 02F to move the vehicle forward
// 02B to move the vehicle backward
// 02R to turn the vehicle right
// 02L to turn the vehicle left
// 02S to stop the vehicle
*/
void commandControl() {
  msg = String(receivedChars); // store the serial data obtained in msg
  Serial.println(msg);// for debugging 

  // derive the command and subcommand from msg
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
```

</p>
</details>

## Resources
<ul>
<li>Bluetooth: https://useoftechnology.com/what-is-bluetooth-indepth-explanation/</li>
<li>HC05: https://exploreembedded.com/wiki/Setting_up_Bluetooth_HC-05_with_Arduino</li>
<li>Arduino Serial communication: https://forum.arduino.cc/t/serial-input-basics-updated/382007</li>
<li>Bluetooth Android App: https://medium.com/swlh/create-custom-android-app-to-control-arduino-board-using-bluetooth-ff878e998aa8</li>
<li>PWM: https://create.arduino.cc/projecthub/muhammad-aqib/arduino-pwm-tutorial-ae9d71</li>
<li>L298N: https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/</li>
</ul>
