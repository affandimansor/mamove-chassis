
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

ChassisMotor::ChassisMotor (uint8_t d0, uint8_t d1, uint8_t d2, MOWER::MotorIndex motorindex) : Motor(d0,d1,d2)//Motor(d0,d1,d2, LED_OUTport) 
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
  //mMotor1 = Motor1;		// Pass value of Motor1 to a member variable mMotor1. Default value is TRUE --> means object created is always considered Motor1
  /*
  setIOport(d0, d1, d2, LED_OUTport);	// This function needs to be called here because we use the Motor's constructor WITHOUT input parameter.
										// This function will assign all pins specified in the ChassisMotor's constructor as either an input or output pin of a motor
										// For the case that a Motor's constructor WITH input parameters is used, then this function should NOT be called
										// as the input and output pins of a motor will be defined in the Motor's constructor itself. See constructors in class Motor
  */
  
  Motorindex = motorindex;

}


ChassisMotor::~ChassisMotor (){ 

}


unsigned char ChassisMotor::calculateMotorSpeed(uint8_t a, uint8_t b, uint8_t joystickX, uint8_t joystickY)
{
	float maxVoltage, teta, radius, motorspeed_internal;	// Parameters used to calculate each motor's speed and to be passed into other functions.
															// Float's precision is needed, otherwise teta and radius values are always either 0(min) or max(1,57).
	radius = sqrtf(square(joystickX) + square(joystickY));	// Using pythagoras theorem to calculate the radius from the center of the joystick to the actual joystick's position
	teta = asin(joystickY/radius);							// Calculate the angle(in radians) between radius and x-axis of joystick movement --> see Notebook-Algorithm for turning maneuver 
	motorspeed_internal = a*sin(teta)*radius + b*radius;	// Calculate the motorspeed based on angle(teta in radians) and radius
	maxVoltage = (mPercentageMaxVoltage/100)*255;			// Maximum voltage is being restricted according to the mPercentageMaxVoltage. 
															// 255 is the value that will be translated into the maximum voltage by PWM.
	//readmaxVoltage = maxVoltage;
	// Mapping motorspeed for turning maneuver
	if (joystickY == 0 && joystickX == 0 || static_cast<char>(motorspeed_internal) == "nan") // For the case joystick is at the middle position
	{
		mMotorspeed = 0;
	}
	
	
	else if ((joystickY != 0 && joystickX == 0) || (joystickY != 0 && joystickX != 0) ) //For the case when forward/reverse OR smooth turn is needed
	{
		mMotorspeed = map(motorspeed_internal,0,260,0,255);	
	}
	
	else // For the case of straight and sharp turn maneuver.
	{
		// Sharp turn maneuver is the case when ((joystickY==0) && (joystickX!=0)) 
		mMotorspeed = map(motorspeed_internal,0,130,0,255);
	}
	readMotorspeedInternal = motorspeed_internal;
	readMotorSpeed = mMotorspeed;
	//mteta = teta;
	//mradius = radius;
	return mMotorspeed;
}



void ChassisMotor::setChassisDirection(unsigned char Motorspeed, int JoystickPosY, int JoystickPosX)
{
	MOWER::MotorDirection Directionsetting;	// Local variable to pass the motor direction into setMotorOperation() 
	
	if ((JoystickPosY > 130))
	{
		// For the case move forward and smooth turning maneuver
		Directionsetting = MOWER::FORWARD;
		// alternative-->setMotorOperation(motorspeed, MOWER::FORWARD);
	}
	
	else if (JoystickPosY < 120) 
	{
		// Reverse only allows for straight and smooth turning maneuver 
		// NO sharp turn can be done in backward movement
		Directionsetting = MOWER::REVERSE;
		// alternative-->setMotorOperation(motorspeed, MOWER::REVERSE);
	}
	
	else if	(((JoystickPosY > 120) && (Motorspeed !=0)) || ((JoystickPosY < 130) && (Motorspeed !=0)))
	{
		// For the case of sharp turn only. One motor spins in the OPPOSITE direction of the other motor 
		// Motorspeed is required so that the program can DIFFERENTIATE between this else if- and else-statement 
		// at the bottom of this function, when the JoystickPosY==125.
		if (JoystickPosX < 125)
		{
			if	(Motorindex == MOWER::MOTOR1) // Decide the spinning direction for motor 1
			{
				Directionsetting = MOWER::FORWARD;
			}
			
			else // Decide the spinning direction for motor 2
			{
				Directionsetting = MOWER::REVERSE;
			}																																			
		}
		
		else if (JoystickPosX > 125)
		{
			if	(Motorindex == MOWER::MOTOR1) // Decide the spinning direction for motor 1
			{
				Directionsetting = MOWER::REVERSE;
			}
			
			else // Decide the spinning direction for motor 2
			{
				Directionsetting = MOWER::FORWARD;
			}																																			
		}
	}
	
	else	// For the case when joystick at middle position --> JoystickPosY==125
	{
		Directionsetting = MOWER::NEUTRAL;
		// alternative-->setMotorOperation(motorspeed, MOWER::REVERSE);
	}
	
	// Passing the calculated motorspeed and determined motor's spinning direction to setMotorOperation()
	setMotorOperation(Motorspeed, Directionsetting, false);
}


/*** Old lines to calculate the motorspeed ***/
//void ChassisMotor::setChassisMotorOperation()	
//{
//------------------------------------------------------------------------------------------------------
	// +++ Define local variable used in this function +++
	//extern unsigned char JoystickPosX;	// Variable definition should come from an object of class Receiver
	//extern unsigned char JoystickPosY;	// Variable definition should come from an object of class Receiver
	
	/* Use local variables to hold the values from external variable because(JoystickPosX and-Y) these values will be manipulated in the following calculation.
	 * If these values are not being passed to local variables and manipulated for the calulation of Motor1's motorspeed, 
	 * then the original value of these external variables will indirectly be manipulated.
	 * Thus the value of JoystickPosX and-Y for Motor2 will be different than Motor1(which should not be the case) because its motorspeed calculation comes after the one for Motor1.
	 */
	//int joystickX = JoystickPosX;	// Use 'int' instead of 'unsigned char' because the calculation joystickX-125 below will produce nonsense result(131), when
	//int joystickY = JoystickPosY;	// either joystickX or -Y is zero.
									// 'char' cannot be used because it cannot hold -ve values greater than -125, 
									// thus the calulation joystickX/-Y will lead to a false result.
	/*
	// +++ Manipulate joystick's reading when it is at the middle position or untouched +++
	// Condition is needed because Joystick gives a value ranging from 125 to 127 when it is at the middle position or untouched
	if ((joystickX >=125) && (joystickX <=127))	
	{
		joystickX = 125;	//Set JoystickPosX to 125 when the joystick is untouched
		
	}
	
	if ((joystickY >=125) && (joystickY <=127))	// Condition is needed because Joystick gives a value ranging 
														// from 125 to 127 when it is at the middle position or untouched
	{
		joystickY = 125;	//Set JoystickPosY to 125 when the joystick is untouched
		
	}
	
	// +++ Determine the a and b coefficients to be used in the calculation for turning maneuver +++
	if (joystickX > 125)
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
	
	if (joystickX < 125)
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
	
	// +++ Manipulate the local variables joystickX and -Y +++
	// Set 125 as zero position for both X-and Y-positions
	joystickX = joystickX - 125;
	joystickY = joystickY - 125;
	
	// Convert -ve values into +ve values
	if (joystickX < 0)
	{	
	 joystickX = joystickX*(-1);
	}
	
	if (joystickY < 0)
	{
		joystickY = joystickY*(-1);
	}
	*/
	/*
	// +++ Calculate the motor speed +++
	//int radius, teta, motorspeed_internal;		// Parameters used to calculate each motor's speed and to be passed into other functions
	joyX = joystickX;
	joyY = joystickY;
	radius = sqrtf(square(joystickX) + square(joystickY));	// Using pythagoras theorem to calculate the radius from the center of the joystick to the actual joystick's position
	teta = asin(joystickY/radius);							// Calculate the angle(in radians) between radius and x-axis of joystick movement --> see Notebook-Algorithm for turning maneuver 
	int motorspeed_internal = a*sin(teta)*radius + b*radius;// Calculate the motorspeed based on angle(teta in radians) and radius
															// 'Integer' is used instead of 'float' just to save the runtime
	
	// Mapping motorspeed for turning maneuver
	if (joystickY == 0 && joystickX == 0) // For the case joystick is at middle position
	{
		mMotorspeed = 0;
	}
	
	else if (joystickY != 0 && joystickX != 0) //For the case when smooth turn is needed
	{
		mMotorspeed = map(motorspeed_internal,0,190,0,255);
	}
	
	else // For the case of straight and sharp turn maneuver.
	{
		// Sharp turn maneuver is the case when ((joystickY==0) && (joystickX!=0)) 
		mMotorspeed = map(motorspeed_internal,0,130,0,255);
	}
//----------------------------------------------------------------------------------------------------------------
	// Passing the calculated motorspeed to setMotorOperation()
	MOWER::MotorDirection Directionsetting;	// Local variable to pass the motor direction into setMotorOperation() 
	
	if ((JoystickPosY >= 125) && (mMotorspeed !=0))
	{
		// For the case move forward and smooth turning maneuver
		// or sharp turn only
		Directionsetting = MOWER::FORWARD;
		// alternative-->setMotorOperation(motorspeed, MOWER::FORWARD);
	}
	
	else if (JoystickPosY < 125) 
	{
		// Reverse only allows for straight and smooth turning maneuver 
		// NO sharp turn can be done in backward movement
		Directionsetting = MOWER::REVERSE;
		// alternative-->setMotorOperation(motorspeed, MOWER::REVERSE);
	}
	
	else	// For the case when joystick at middle position
	{
		Directionsetting = MOWER::NEUTRAL;
		// alternative-->setMotorOperation(motorspeed, MOWER::REVERSE);
	}
	
	setMotorOperation(mMotorspeed, Directionsetting, false);
	*/
//}

