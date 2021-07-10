/* 
 * This is the cpp file of class CutterMotor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 25 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */

#include <Arduino.h>
#include "CutterMotor.h"

CutterMotor::CutterMotor ( uint8_t d2) : Motor(d2) // Constructor for a cutter motor will pass the input parameter to a Motor's constructor that needs only one parameter.
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
  
  setCutterOperation(MOWER::OFF);	// When an object is created, the "Cutterswitch" is set to "OFF"
}


CutterMotor::~CutterMotor (){ 

}
 
 
void CutterMotor::setCutterOperation(MOWER::ONOFF_Status Cutterswitch)
{
	// This function doesn't neccessary needed. We can directly call setMotorOperation after create an object of class CutterMotor
	// It is written only just to demonstrate the usage of "extern".
	// This function only needs one parameter which is Cutterswitch's status.
	// The variable 'CutterMotorSpeed' is defined directly in the Receiver's class or sketch.
	MOWER::MotorDirection Directionsetting;
	// Old line --> extern unsigned char CutterMotorSpeed;	  
	// Old line --> if (Cutterswitch == MOWER::ON && CutterMotorSpeed !=0) 
	if (Cutterswitch == MOWER::ON) // Cutter is allowed to spin only in one direction, which is FORWARD
	{
		Directionsetting = MOWER::FORWARD;
	}
	
	else // For the case when Cutterswitch==MOWER::OFF and/or CutterMotorSpeed==0
	{
		Directionsetting = MOWER::NEUTRAL;
		// Old line --> CutterMotorSpeed = 0; 	// Set cutter motor's speed to zero
	}
	setMotorOperationRelay(Cutterswitch, Directionsetting, true);
}