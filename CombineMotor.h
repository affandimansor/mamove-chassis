/* 
 * This is the h file of class CombineMotor.
 * This class represents the complete chassis with its LED indicator
 * Creator: Muhammad Affandi Bin Mansor, 3 April 2021
 * Author: Muhammad Affandi Bin Mansor
 */
 
#ifndef CombineMotor_h
#define CombineMotor_h

#include <Arduino.h>
#include "ChassisMotor.h"
#include "LED.h"
#include "Switch.h"

class CombineMotor
{
	public:
	CombineMotor();
	~CombineMotor();
	void setChassisMotorOperation(MOWER::ONOFF_Status autoforwardStatus);	// To be called in the Arduino sketch later
	void setChassisMotor(ChassisMotor *chassis1, ChassisMotor *chassis2);	// Assign the actual ChassisMotor's objects to the local pointer objects
	void setChassisLED(LED *forwardLED, LED *reverseLED);	// Assign the actual LED's objects to the local pointer objects
	//void setSwitchAutoForward(Switch *autoforwardSwitch);	// Asign the actual Switch's object to a local pointer object
	uint8_t SpeedM1, SpeedM2;
	
	
	private:
	ChassisMotor *mChassisMotor1;
	ChassisMotor *mChassisMotor2;
	LED *mforwardLED;
	LED *mreverseLED;
	//Switch *mautoforwardSwitch;	//Local object are not needed here since the status of autoforward switch comes directly from the reciever's payload 
	unsigned char mMotorSpeed1;	// Variable to hold the motorspeed for Motor1
	unsigned char mMotorSpeed2;	// Variable to hold the motorspeed for Motor2
	const unsigned char mautoforwardSpeed = 150;	// Chassis speed during auto forward operation. 255 is the maximum value.
	unsigned char mturnCoeff[2] = {0,1};	// Coeffiecients will be used to calculate the motorspeeds during the joystick's operation.
											// This array is better to be defined here. Defining this array in the class's constructor is complicated.
											
	//The first 2 following functions should be called by setChassisMotorOperation()
	bool autoForward(MOWER::ONOFF_Status autoforwardStatus);		// Chassis moves forward automatically at certain speed when the switch 'autoforward' is turned on
	void moveJoystick(unsigned char JoystickPosX, unsigned char JoystickPosY);	// Chassis will move according to the command from joystick
	void operateChassisLED(int JoystickPosY, unsigned char MotorSpeed1, unsigned char MotorSpeed2);	// Set which LED needs to be lighted up based on the joystick position's Y 
	
};

#endif