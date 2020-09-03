#include <Arduino.h>
#include "StepperMotor.h"



void motorMove(int steeps)
{ 
  digitalWrite(sleepPin,HIGH);
  delayMicroseconds(5000); 
  
  for(int x = 0; x < (int)(steeps); x++) 
  {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(3000);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(3000);
  }
  delayMicroseconds(5000);
  digitalWrite(sleepPin,LOW);
  delayMicroseconds(5000); 
}

void motorDirChange()
{
  digitalWrite(dirPin, !digitalRead(dirPin));
  delayMicroseconds(5000); 
}

void motorSetup()
{
  pinMode(resetPin,OUTPUT);
  digitalWrite(resetPin,HIGH);
  
  pinMode(sleepPin,OUTPUT);
  digitalWrite(sleepPin,LOW);
  
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  digitalWrite(dirPin,HIGH);
}
