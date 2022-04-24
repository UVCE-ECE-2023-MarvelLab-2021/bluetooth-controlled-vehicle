#pragma once

// Receive with an end-marker
const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
boolean newData = false;

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
