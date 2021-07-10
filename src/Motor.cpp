/* 
 * This is the cpp file of class Motor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 24 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#include <Arduino.h>
#include <Mower.h>
#include "Motor.h"
#include "CutterMotor.h"
#include "ChassisMotor.h"
//#include "LED.h"  // Is required because the LEDStatus comes from an enumerator in LED class.
					// If it just for inheritance purpose, this LED library DOESN'T have to be included here. 

Motor::Motor(): mLED1(100) // mLED1(100) means we dont want to use LED --> I/0 port no. 100 is assigned as LED output
{};

Motor::Motor (uint8_t d0, uint8_t d1, uint8_t d2) : mLED1(100) // mLED1(100) means we dont want to use LED --> I/0 port no. 100 is assigned as LED output
{ 
  mMotorIn1 = d0;		// Assign the digital PWM port to a local mMotorIn1 variable
  mMotorIn2	= d1;		// Assign the digital PWM port to a local mMotorIn2 variable
  mMotorEnable = d2;	// Assign the digital PWM port to a local mMotorEnable variable
  museLED = false;		// Set variable to FALSE. Variable will be used in setMotorStatus
  
  pinMode(mMotorIn1, OUTPUT);					// Define mMotorIn1 as output port
  pinMode(mMotorIn2, OUTPUT);  					// Define mMotorIn2 as output port
  pinMode(mMotorEnable, OUTPUT);				// Define mMotorEnable as output port
  setMotorOperation(0,MOWER::NEUTRAL,false);	// Initialize motor's start condition
}


Motor::Motor (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_port) : mLED1(LED_port)
{ 
  // Constructor for object mLED1 is called by using method member initialization.
  // When calling the Motor's constructor, no need to write :mLED1,
  // instead just write everything in Motor's constructor. 
  // LED_port from the Motor's constructor will be passed by the compiler into the mLED1's constructor
  
  mMotorIn1 = d0;		// Assign the digital PWM port to a local mMotorIn1 variable
  mMotorIn2	= d1;		// Assign the digital PWM port to a local mMotorIn2 variable
  mMotorEnable = d2;	// Assign the digital PWM port to a local mMotorEnable variable
  museLED = true;		// Set variable to TRUE. Variable will be used in setMotorStatus
  
  pinMode(mMotorIn1, OUTPUT);					// Define mMotorIn1 as output port
  pinMode(mMotorIn2, OUTPUT);  					// Define mMotorIn2 as output port
  pinMode(mMotorEnable, OUTPUT);				// Define mMotorEnable as output port
  setMotorOperation(0,MOWER::NEUTRAL,false);	// Initialize motor's start condition
}


/*
Motor::Motor (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_port){ 
  // As alternative to set IOports by using setIOport in the Motor's constructor
  // after an object of class Motor has been defined in the .h file of the derived class.
  // Note: Here is not using the member initialization method to pass 'LED_port' to an object of class LED,
  //       that's why there is no ':mLED1(LED_port)' written at the constructor definition above (ln 43).
  
  setIOport(d0, d1, d2, LED_port);
  
}
*/

 
Motor::~Motor (){
  
}


void Motor::setIOport(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_OUTport=100)
{
	// This function will be inherited by the derived class(CutterMotor and ChassisMotor)
	// If this function is not available, then the derived classes need to create an object of class Motor
	// in order to assign the IOports to the class Motor <-- This is certainly not how the inheritance concept should be.
	mMotorIn1 = d0;				// Assign the digital PWM port to a local mMotorIn1 variable
	mMotorIn2 = d1;				// Assign the digital PWM port to a local mMotorIn2 variable
	mMotorEnable = d2;			// Assign the digital PWM port to a local mMotorEnable variable	
	
	if (LED_OUTport != 100)		// Default value of LED_OUTport is 100, which means the object of Motor's derived class doesn't want to use LED. 
	{
		LED mLED1(LED_OUTport);	// Create an object of class LED and assign the output port. This is not the same private mLED1 object declared in the .h file
		museLED = true;			// Set variable to TRUE
	}
	
	else		// LED_OUTport==100(default value) --> means no LED is required by the object of Motor's derived class
	{
		museLED = false;
	}
	
	pinMode(mMotorIn1, OUTPUT);					// Define mMotorIn1 as output port
	pinMode(mMotorIn2, OUTPUT);  				// Define mMotorIn2 as output port
	pinMode(mMotorEnable, OUTPUT);				// Define mMotorEnable as output port
	setMotorOperation(0,MOWER::NEUTRAL,false);	// Initialize motor's start condition
}


void Motor::setMotorDirection(MOWER::MotorDirection Directionsetting)	
{	
	// Set motor direction based on input.
	// This function should be called by setMotorSpeed.
	
	if (Directionsetting == MOWER::REVERSE)	
	{	
		digitalWrite(mMotorIn1, LOW);
		digitalWrite(mMotorIn2, HIGH); 
	}
	
	else	// When motor should run in forward direction or neutral position--> Directionsetting == MOWER::REVERSE or Directionsetting == MOWER::NEUTRAL
	{
		
		digitalWrite(mMotorIn1, HIGH);
		digitalWrite(mMotorIn2, LOW);
	}
	
	mMotorDirection = Directionsetting;	// Assign the input parameter to a local variable, 
										// so that we can display the motor direction when needed. 
}


void Motor::setMotorStatus(MOWER::MotorStatus Motorsetting, bool blinkLED)
{
  mMotorState = Motorsetting; // Set the value of Motorsetting to mMotorState
  if (museLED == true)	// To set the LED on/off if the motor does need a LED 
  {
	if (mMotorState == MOWER::RUN)
	{
		if (blinkLED == true)
		{
			mLED1.setBlinkLED();
		}
		else
		{
			mLED1.setLEDStatus(MOWER::ON);   // Turn on LED. This function should be defined as public in the class LED
		}
	}
	
	else	// mMotorState == MOWER::MotorStatus::STOP)
	{
		mLED1.setLEDStatus(MOWER::OFF);	// Turn off LED. This function should be defined as public in the class LED
	}
  }
  
  /*else{
	  // For the case when LED is not required.
	  // Basically here just assign the value Motorsetting to mMotorState again
	  // The same code as the first line of this function is written again in case else-statement is needed
	  mMotorState = Motorsetting; 
  }*/
}


void Motor::setMotorOperation(float Motorspeed, MOWER::MotorDirection Directionsetting, bool blinkLED)
{	
	// This function determines the speed and direction of motor.
	setMotorDirection(Directionsetting);
	analogWrite(mMotorEnable, Motorspeed);	// Assign the input value as the PWM output on mMotorIn1
	float mMotorSpeed = Motorspeed;
	
	if (Motorspeed > 0)
	{
		// Set directly the MotorStatus to RUN
		// No need to write MOWER::MotorStatus::RUN, 
		// since we already defined from which enumerator(MotorStatus) in the namespace MOWER the input for setMotorStatus() should be
		// See the definition of setMotorStatus() at line 66
		setMotorStatus(MOWER::RUN, blinkLED);	
	}
	
	else
	{
		setMotorStatus(MOWER::STOP, blinkLED);	// Set directly the MotorStatus to STOP if Motorspeed < 0.
	}
}


int Motor::getMotorStatus()
{
  return mMotorState;
}

int Motor::getMotorDirection()
{
	return mMotorDirection;
}

int Motor::getMotorLEDStatus()
{
	return mLED1.getLEDStatus();
}
