
/* 
 * This is the cpp file of class CutterMotor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 25 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */

#include <Arduino.h>
#include <math.h>
#include <Mower.h>

#include "ChassisMotor.h"

ChassisMotor::ChassisMotor (uint8_t d0, uint8_t d1, uint8_t d2, bool Motor1 = true, uint8_t LED_OUTport = 100) : Motor()//Motor(d0,d1,d2, LED_OUTport) 
{ 
  /* !!!IMPORTANT -> We need to explicitly call the base class's constructor that we want to use above.
					 Otherwise will get an error because the derived class's constructor has different number 
					 of parameters as the base class's constructors. 
					 We need to TELL the compiler which one of the base class's constructors that we want to use
					 in this derived class.			 
  */
  // If the ChassisMotor's constructor is called, the I/O ports that will be used by the motor is set up.
  // setIOport() is defined in Motor.cpp
  // For the case when LED is not required, then 'LED_OUTport'==100(default value).
  mMotor1 = Motor1;		// Pass value of Motor1 to a member variable mMotor1. Default value is TRUE --> means object created is always considered Motor1
  setIOport(d0, d1, d2, LED_OUTport);	// This function needs to be called here because we use the Motor's constructor WITHOUT input parameter.
										// This function will assign all pins specified in the ChassisMotor's constructor as either an input or output pin of a motor
										// For the case that a Motor's constructor WITH input parameters is used, then this function should NOT be called
										// as the input and output pins of a motor will be defined in the Motor's constructor itself. See constructors in class Motor
}


ChassisMotor::~ChassisMotor (){ 

}


void ChassisMotor::setChassisMotorOperation()
{
//------------------------------------------------------------------------------------------------------
	// Define local variable used in this function 
	extern unsigned char JoystickPosX;	// Variable definition should come from an object of class Receiver
	extern unsigned char JoystickPosY;	// Variable definition should come from an object of class Receiver
	
	if (JoystickPosX >= 125)
	{
		if (mMotor1 == true)	// Coefficients used to calculate speed of Motor1 for turning RIGHT
		{
			a = mturnCoeff[0];
			b = mturnCoeff[1];
		}
		
		else	// Coefficients used to calculate speed of Motor2 for turning RIGHT
		{
			a = mturnCoeff[1];
			b = mturnCoeff[0];
		}
	}
	
	else if (JoystickPosX < 125)
	{
		if (mMotor1 == true)	// Coefficients used to calculate speed of Motor1 for turning LEFT
		{
			a = mturnCoeff[1];
			b = mturnCoeff[0];
		}
		
		else	// Coefficients used to calculate speed of Motor2 for turning LEFT
		{
			a = mturnCoeff[0];
			b = mturnCoeff[1];
		}
	}
	
	// Calculate the motor speed
	radius = sqrtf(square(JoystickPosX) + square(JoystickPosY));	// Using pythagoras theorem to calculate the radius from the center of the joystick to the actual joystick's position
	teta = asin(JoystickPosY/radius);								// Calculate the angle(in radians) between radius and x-axis of joystick movement --> see Notebook-Algorithm for turning maneuver 
	motorspeed = a*sin(teta)*radius + b*radius;						// Calculate the motorspeed based on angle(teta in radians) and radius
																	// Motorspeed doesn't need to be mapped to 8bit because JoystickPosX&JoystickPosY are already in 8bit format

//----------------------------------------------------------------------------------------------------------------
	// Pass the calculated motorspeed to setMotorOperation()
	MOWER::MotorDirection Directionsetting;	// Local variable to pass the motor direction into setMotorOperation() 
	
	if (JoystickPosY >= 125)
	{
		Directionsetting = MOWER::FORWARD;
		// alternative-->setMotorOperation(motorspeed, MOWER::FORWARD);
	}
	
	else	// (JoystickPosY < 125)
	{
		Directionsetting = MOWER::REVERSE;
		// alternative-->setMotorOperation(motorspeed, MOWER::REVERSE);
	}
	
	setMotorOperation(motorspeed, Directionsetting, false);
}