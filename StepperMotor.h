#ifndef StepperMotor
#define StepperMotor

const int stepPin = 33;
const int dirPin = 32;

const int resetPin = 26;
const int sleepPin = 25;

void motorSetup();
void motorDirChange();
void motorMove(int stops);
#endif
