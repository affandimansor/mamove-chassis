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
  ChassisMotor (uint8_t d0, uint8_t d1, uint8_t d2, MOWER::MotorIndex motorindex);//, bool Motor1);   //Constructor for a chassis motor with or without LED
  ~ChassisMotor ();
  unsigned char calculateMotorSpeed(uint8_t a, uint8_t b, uint8_t joystickX, uint8_t joystickY);	// Function to calculate the speed of each motor. To be called in the class CombineMotor
  void setChassisDirection(unsigned char Motorspeed, int JoystickPosY, int JoystickPosX);	// Set the chassis movement based on the input from calculateMotorSpeed(), joystick's position Y and X
  //float readmaxVoltage;
  unsigned char readMotorSpeed;
  float readMotorspeedInternal;
  //void setChassisMotorOperation();		// Function calculates the turning maneuver and pass it to the setMotorOperation() of class Motor
  //void setChassisMotorOperation(float JoyX, float JoyY);		// Function calculates the turning maneuver and pass it to the setMotorOperation() of class Motor
    
  //float mradius;	//<-- Data type needs to be changed, 'float' might cause the code to run slow !!!!
  //float mteta;	//<-- Data type needs to be changed, 'float' might cause the code to run slow !!!!
  //int joyX;	//<-- Data type needs to be changed, 'float' might cause the code to run slow !!!!
  //int joyY;	//<-- Data type needs to be changed, 'float' might cause the code to run slow !!!!
  //unsigned char a,b;
  
  
  private:
  unsigned char mMotorspeed;
  MOWER::MotorIndex Motorindex;
  const float mPercentageMaxVoltage = 100;	// To control the maximum voltage allowed to flow into the motor. Given in percentage [%] 
											// This value will be divided with 100% at the point of use. See ChassisMotor.cpp file at Ln 46
											// Need to use float otherwise the calculation at Ln46 will only show zero.
};
#endif

