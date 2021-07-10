/* 
 * This is the cpp file of class Motor.
 * This class is a subclass of the Chassis's class
 * Creator: Muhammad Affandi Bin Mansor, 24 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include "LED.h"
#include "Mower.h"


class Motor
{
  public:
  Motor(); 			// Default constructor
  Motor (uint8_t d0, uint8_t d1, uint8_t d2);   //Constructor for a motor controlled through the motor driver L298N
  Motor (uint8_t d2);	// Constructor for a motor that is NOT controlled by the motor driver L298N, e.g. cutter motor.
						// This kind of motor will be connected to a relay due to its high current operation.
  //Motor (uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_port);   // Constructor for a motor with a LED as status indicator
  ~Motor ();
  //void setIOport(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t LED_OUTport);	// Setup IOports when creating an object by using the default constructor
  void setMotorLED(LED *LED1);		// To be called if a motor needs an LED
  void setMotorOperation(unsigned char Motorspeed, MOWER::MotorDirection Directionsetting, bool blinkLED); // For the case when a motor is controlled through a motor driver, e.g. for chassis motors.
  void setMotorOperationRelay(MOWER::ONOFF_Status SwitchStatus, MOWER::MotorDirection Directionsetting, bool blinkLED);	// For the case when a motor is controlled through a relay instead of motor driver, e.g. for cutter motor.
  unsigned char getMotorStatus();
  unsigned char getMotorDirection();
  unsigned char getMotorLEDStatus();		// Get the status of the object mLED1
  
  private:
  unsigned char mMotorIn1;
  unsigned char mMotorIn2;
  unsigned char mMotorEnable;
  MOWER::MotorStatus mMotorState;			// Member variable to hold the motor state 
  MOWER::MotorDirection mMotorDirection;	// Member variable to hold the motor direction
  //LED mLED1;		// Create an object of class LED
  LED *mLED1;		// Create a pointer object of class LED. Actual object will be created in the Arduino IDE.
  bool museLED;		// Variable is used to indicate LED is being used along with a motor in another functions of this class
  void setMotorStatus(MOWER::MotorStatus Motorsetting, bool blinkLED);
  void setMotorDirection(MOWER::MotorDirection Directionsetting);	// This function will be called in setMotorOperation()
};


#endif
