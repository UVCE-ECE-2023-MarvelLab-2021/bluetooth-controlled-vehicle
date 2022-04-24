#pragma once

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
