/* 
 * This is the cpp file of class CombineMotor.
 * Creator: Muhammad Affandi Bin Mansor, 3 April 2021
 * Author: Muhammad Affandi Bin Mansor
 */


#include <Arduino.h>
#include "CombineMotor.h"
#include "Mower.h"


CombineMotor::CombineMotor()
{}


CombineMotor::~CombineMotor()
{}

void CombineMotor::setChassisMotor(ChassisMotor *chassis1, ChassisMotor *chassis2)	// Assign the actual ChassisMotor's objects to the local pointer objects
{
	mChassisMotor1 = chassis1;
	mChassisMotor2 = chassis2;
}


void CombineMotor::setChassisLED(LED *forwardLED, LED *reverseLED)
{
	// Assign the actual LED's objects to the local pointer objects
	// Note that these LEDs are not the same as LED pointer object in the class Motor.
	// In the class Motor, the LED is specifically created for each motor. 
	// But here one LED represents M1&M2 for FORWARD movement, the other LED is for REVERSE
	mforwardLED = forwardLED;
	mreverseLED = reverseLED;
	
}

/*
void CombineMotor::setSwitchAutoForward(Switch *autoforwardSwitch)
{
	// Assign the actual switch object to the local pointer object
	mautoforwardSwitch = autoforwardSwitch;
}
*/

bool CombineMotor::autoForward(MOWER::ONOFF_Status autoforwardStatus) // Function determines the value of variable autoforwardStatus
{
	/*	i) The 2 following lines are not needed here since the status of autoforward switch comes directly from the reciever's payload
		and it will be passed as the parameter of this function
		ii) These 2 lines are needed only when we created a pointer object of autoforward switch
	*/
	//MOWER::ONOFF_Status autoforwardStatus;
	//autoforwardStatus = mautoforwardSwitch->getSwitchStatus();
	
	if (autoforwardStatus == MOWER::ON)
	{
		return true;
	}
	
	else
	{
		return false;
	}
}

void CombineMotor::moveJoystick(unsigned char JoystickPosX, unsigned char JoystickPosY)
{
	/* Use local variables to hold the values from external variable because(JoystickPosX and-Y) these values will be manipulated in the following calculation.
	 * If these values are not being passed to local variables and manipulated for the calulation of Motor1's motorspeed, 
	 * then the original value of these external variables will indirectly be manipulated.
	 * Thus the value of JoystickPosX and-Y for Motor2 will be different than Motor1(which should not be the case) because its motorspeed calculation comes after the one for Motor1.
	 */
	int joystickX = JoystickPosX;	// Use 'int' instead of 'unsigned char' because the calculation joystickX-125 below will produce nonsense result(131), when
	int joystickY = JoystickPosY;	// either joystickX or -Y is zero.
									// 'char' cannot be used because it cannot hold -ve values greater than -125, 
									// thus the calulation joystickX/-Y will lead to a false result.
	unsigned char a1, b1; 	// Coeffiecients will be used to calculate motorspeed for ChassisMotor1
	unsigned char a2, b2;	// Coeffiecients will be used to calculate motorspeed for ChassisMotor2
	// +++ Manipulate joystick's reading when it is at the middle position or untouched +++
	// Condition is needed because Joystick gives a value ranging from 123 to 127 when it is at the middle position or untouched
	if ((joystickX >=123) && (joystickX <=129))	
	{
		joystickX = 125;	//Set JoystickPosX to 125 when the joystick is untouched
		
	}
	
	if ((joystickY >=125) && (joystickY <=129))	// Condition is needed because Joystick gives a value ranging 
														// from 125 to 127 when it is at the middle position or untouched
	{
		joystickY = 125;	//Set JoystickPosY to 125 when the joystick is untouched
		
	}
	
	// +++ Determine the a and b coefficients to be used in the calculation for the turning maneuver +++
	/*** Old lines to determine the coefficients for the turning maneuver of motor1 and motor2 ***/
	/* NOTE!!! Please expand this line in order to see the old codes
	if (joystickX > 125)
	{
		// Coefficients used to calculate speed of Motor1 for turning RIGHT
		a1 = mturnCoeff[1];
		b1 = mturnCoeff[0];
		
		// Coefficients used to calculate speed of Motor2 for turning RIGHT
		a2 = mturnCoeff[0];
		b2 = mturnCoeff[1];
	}
	
	else if (joystickX < 125)
	{
		// Coefficients used to calculate speed of Motor1 for turning LEFT
		a1 = mturnCoeff[0];
		b1 = mturnCoeff[1];
		
		// Coefficients used to calculate speed of Motor2 for turning LEFT
		a2 = mturnCoeff[1];
		b2 = mturnCoeff[0];
	}
	
	else // For straight maneuver --> when joystickX == 125
	{
		a1 = mturnCoeff[1];
		b1 = mturnCoeff[1];
		
		a2 = mturnCoeff[1];
		b2 = mturnCoeff[1];
	}
		
	*/
	
	/* New lines to determine the coefficients for the turning maneuver*/
	
	if ((joystickX > 125) && (joystickY != 125))	// For smooth turn to the RIGHT (joystickX > 125) -->  At the same time joystickY != 125
	{
		// Coefficients used to calculate speed of Motor1 for turning RIGHT
		a1 = mturnCoeff[1];
		b1 = mturnCoeff[0];
		
		// Coefficients used to calculate speed of Motor2 for turning RIGHT
		a2 = mturnCoeff[0];
		b2 = mturnCoeff[1];
	}
	
	else if ((joystickX < 125) && (joystickY != 125))	// For smooth turn to the LEFT (joystickX < 125) -->  At the same time joystickY != 125
	{
		// Coefficients used to calculate speed of Motor1 for turning LEFT
		a1 = mturnCoeff[0];
		b1 = mturnCoeff[1];
		
		// Coefficients used to calculate speed of Motor2 for turning LEFT
		a2 = mturnCoeff[1];
		b2 = mturnCoeff[0];
	}
	
	else //(joystickX == 125 || joystickY == 125) // For straight maneuver --> When joystickX==125 and sharp turn --> When joystickY == 125
	{
		// Coefficients used to calculate speed of Motor1 and Motor2 for sharp turning LEFT/RIGHT
		// The coefficients for Motor2 are the same as Motor1 because we want the Motor2 to have the same speed as Motor1 but in OPPOSITE direction during the sharp turn.
		// This is required as to overcome the limitations of hardware(the motor), which doesn't have enough Trägheitsmoment when no current is applied to them. 
		// As a result, the motor doesn't really stop spinning when no current is applied to them, but instead it spins along with a random speed due 
		// to the friction force from the ground and the force applied by the chassis on them. 
		// !!! NOTE !!!: Here only the COEFFICIENTS to calculate the motor speed for Motor1 and Motor2 will be determined.
		//				 The direction of spinning for both motors will be determined by the setChassisDirection() in the class ChassisMotor, which will be called by setChassisMotorOperation() later.
		
		// Coefficients used to calculate speed of Motor1 for going straight and sharp turning RIGHT/LEFT
		a1 = mturnCoeff[1];
		b1 = mturnCoeff[1];
		
		// Coefficients used to calculate speed of Motor2 for going straight and sharp turning RIGHT/LEFT
		a2 = mturnCoeff[1];
		b2 = mturnCoeff[1];
	}
	

	// +++ Manipulate the local variables joystickX and -Y +++
	// Set 125 as the zero position for both X-and Y-positions
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
	
// +++++ Calculate motorspeed and determine direction of chassis's movement +++++
	mMotorSpeed1 = mChassisMotor1->calculateMotorSpeed(a1,b1,joystickX,joystickY);
	mMotorSpeed2 = mChassisMotor2->calculateMotorSpeed(a2,b2,joystickX,joystickY);
}

void CombineMotor::operateChassisLED(int JoystickPosY, unsigned char MotorSpeed1, unsigned char MotorSpeed2)
{	
	if (JoystickPosY >= 125)	// For forward movement
	{
		// Check at least one of both motorspeeds is not equal to zero.
		// If both motorspeeds are zero, then this program will jump to 'else'-->Joystick is at middle position, 
		// which means JoystickPosX and JoystickPosY==125.
		if((MotorSpeed1!=0) || (MotorSpeed2!=0))
		{
			mforwardLED->setLEDStatus(MOWER::ON);
			mreverseLED->setLEDStatus(MOWER::OFF);
		}
		else
		{
			mforwardLED->setLEDStatus(MOWER::OFF);
			mreverseLED->setLEDStatus(MOWER::OFF);
		}
	}
	
	else if (JoystickPosY < 125) // For reverse movement
	{
		mforwardLED->setLEDStatus(MOWER::OFF);
		mreverseLED->setLEDStatus(MOWER::ON);
	}
}



void CombineMotor::setChassisMotorOperation(MOWER::ONOFF_Status autoforwardStatus)	// To be called in the Arduino sketch later
{
//------------------------------------------------------------------------------------------------------

	// +++ Define local variable used in this function +++
	extern unsigned char JoystickPosX;	// Variable definition should come from an object of class Receiver
	extern unsigned char JoystickPosY;	// Variable definition should come from an object of class Receiver

// +++++ Decide on the mode of operation +++++	
	if (autoForward(autoforwardStatus) == true)	// Autoforward mode is activated
	{
		mMotorSpeed1 = mautoforwardSpeed;
		mMotorSpeed2 = mautoforwardSpeed;
		JoystickPosY = 150;	// Manipulate the variable JoystickPosY, so that the chassis will only move forward if this mode is activated
	}
	
	else	// Autoforward mode is deactivated --> Chassis is manually controlled through the joystick 
	{
		moveJoystick(JoystickPosX, JoystickPosY);
	}

// +++++ Assign the speed to each motor and determine its direction +++++
	mChassisMotor1->setChassisDirection(mMotorSpeed1, JoystickPosY, JoystickPosX);
	mChassisMotor2->setChassisDirection(mMotorSpeed2, JoystickPosY, JoystickPosX);
	
	operateChassisLED(JoystickPosY, mMotorSpeed1, mMotorSpeed2);
	
}




