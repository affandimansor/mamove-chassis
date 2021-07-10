/* 
 * This is the cpp file of class Motor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 24 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include "LED.h"
#include "Mower.h"


class Motor
{
  public:
  Motor(); 			// Default constructor
  Motor (uint8_t d0, uint8_t d1, uint8_t d2);   //Constructor for a motor without LED
  Motor (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_port);   // Constructor for a motor with a LED as status indicator
  ~Motor ();
  void setIOport(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_OUTport);	// Setup IOports when creating an object by using the default constructor
  void setMotorOperation(float Motorspeed, MOWER::MotorDirection Directionsetting, bool blinkLED);
  int getMotorStatus();
  int getMotorDirection();
  int getMotorLEDStatus();		// Get the status of the object mLED1
  
  private:
  int mMotorIn1;
  int mMotorIn2;
  int mMotorEnable;
  MOWER::MotorStatus mMotorState;			// Member variable to hold the motor state 
  MOWER::MotorDirection mMotorDirection;	// Member variable to hold the motor direction
  LED mLED1;		// Create an object of class LED
  bool museLED;		// Variable is used to indicate LED is being used along with a motor in another functions of this class
  void setMotorStatus(MOWER::MotorStatus Motorsetting, bool blinkLED);
  void setMotorDirection(MOWER::MotorDirection Directionsetting);	// This function will be called in setMotorOperation()
};


#endif
