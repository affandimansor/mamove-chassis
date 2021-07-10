/* 
 * This is the cpp file of class CutterMotor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 25 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */

#include <Arduino.h>
#include "CutterMotor.h"

CutterMotor::CutterMotor (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_OUTport = 100) : Motor(d0,d1,d2, LED_OUTport) 
{ 
/* !!!IMPORTANT -> We need to explicitly call the base class's constructor that we want to use above.
					 Otherwise will get an error if the derived class's constructor has a different number 
					 of parameters as the base class's constructors. 
					 We need to TELL the compiler which one of the base class's constructors that we want to use
					 in this derived class.			 
  */
  // If the CutterMotor's constructor is called, the I/O ports that will be used by the motor are set up.
  // setIOport() is defined in Motor.cpp
  // For the case when LED is not required, then 'LED_OUTport'==100(default value).
  
  setCutterOperation(MOWER::NEUTRAL);	// When an object is created, the "Directionsetting" is set to "NEUTRAL"
}


CutterMotor::~CutterMotor (){ 

}
 
 
void CutterMotor::setCutterOperation(MOWER::MotorDirection Directionsetting)
{
	// This function doesn't neccessary needed. We can directly call setMotorOperation after create an object of class CutterMotor
	// It is written only just to demonstrate the usage of "extern".
	// This function only needs one parameter which is Directionsetting.
	// The variable 'CutterMotorSpeed' will be defined directly in the Receiver's class or sketch later.

	extern float CutterMotorSpeed;	  
	setMotorOperation(CutterMotorSpeed, Directionsetting, true);
}