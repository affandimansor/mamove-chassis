/* 
 * This is the h file of class CutterMotor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 25 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef CutterMotor_h
#define CutterMotor_h

#include <Arduino.h>
#include <Mower.h>
#include "Motor.h"

class CutterMotor : virtual public Motor		// This class will be derived from the base class Motor. It can use all functions from the class Motor
{
  // This class can use functions from the base class Motor.
  // No need to write again here those functions in Motor's class.
  // Just create an object from class CutterMotor in a sketch if want to use all functions defined&declared in class Motor.
  public:
  CutterMotor (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_OUTport);   //Constructor for a cutter motor with or without LED
  ~CutterMotor ();
  void setCutterOperation(MOWER::MotorDirection Directionsetting);		// Function is derived from the setMotorOperation() of class Motor

  private:
  
};


#endif
