/* 
 * This is the h file of class ChassisMotor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 26 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef ChassisMotor_h
#define ChassisMotor_h

#include <Arduino.h>
#include "Motor.h"

class ChassisMotor : virtual public Motor		// This class will be derived from the base class Motor. It can use all functions from the class Motor
{
  // This class can use functions from the base class Motor.
  // No need to write again here those functions in Motor's class.
  // Just create an object from class ChassisMotor in a sketch if want to use all functions defined&declared in class Motor.
  public:
  ChassisMotor (uint8_t d0, uint8_t d1, uint8_t d2, bool Motor1, uint8_t LED_OUTport);   //Constructor for a chassis motor with or without LED
  ~ChassisMotor ();
  void setChassisMotorOperation();		// Function calculates the turning maneuver and pass it to the setMotorOperation() of class Motor
  //void setChassisMotorOperation(float JoyX, float JoyY);		// Function calculates the turning maneuver and pass it to the setMotorOperation() of class Motor
  float motorspeed;
  float radius;
  float teta;
  int a,b;
  
  
  private:
  bool mMotor1;
  int mturnCoeff[2] = {1,0};	// Coefficient to be used in calculation of the motor speed for the turning maneuver.
								// This array is better to be defined here. Defining this array in the class's constructor is complicated.
};


#endif

