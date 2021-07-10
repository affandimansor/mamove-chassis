/* 
 * This is the cpp file of class Joystick.
 * This class is a subclass of the Controller's class
 * Creator: Muhammad Affandi Bin Mansor, 22 January 2021
 * Author: NAME OF THE PERSON RESPONSIBLE TO WRITE THE CODE FOR THIS CLASS
 */
 
#ifndef Joystick_h
#define Joystick_h

#include <Arduino.h>

/* No need to use this define-Method to assign the Analog-Pins 
//------------------------------------------------------------------------------------------------
#define portPosX	A0		// Analog port as input for joystick's X-position
#define portPosY	A1		// Analog port as input for joystick's Y-position
//------------------------------------------------------------------------------------------------
*/

class Joystick
{
  public:
  Joystick (unsigned char AnalogPortX, unsigned char AnalogPortY);	// Both arguments can be like 0 to max available pins on the board.
												// The function analogRead() which will use those arguments knows that we are referring to A0, A1 etc. See 'Using "Analog Pins" as parameter in Notebook. 
												// Use 'unsigned char'(1byte) instead of 'float'(4byte) to reduce the lag of data transmission due to 
												// different processing time required by the CPU for different data types
  ~Joystick ();
  unsigned char getjoystickPosX();	// These functions give an access to the variable 'mjoystickPosX' and 'mjoystickPosY' from outside of this class.
  unsigned char getjoystickPosY();	// If a class that needs this variable use an 'extern' variable to store/access the same variable, then this get() are NOT needed.
							// The 'extern' variable of other class with exactly the same name as 'mjoystickPosX;mjoystickPosY' can access directly to these both variables.
							// But remember to include the .h file of this class in the other class that contains those extern variables.
							
  
  private:
  int mPinX;				// Variable to hold and pass the Analog-Pin for joystick's X-position to other member functions
  int mPinY;				// Variable to hold and pass the Analog-Pin for joystick's Y-position to other member functions
							// Both variables above need to be from the type 'integer' because they hold the value from Joystick up to 1023
  unsigned char mjoystickPosX;		// Class's member variable to hold the input analog value for X-position 
  unsigned char mjoystickPosY;		// Class's member variable to hold the input analog value for Y-position
  void setjoystickPosX();	// In this function where the mapping of joytick-X's values of 10-bit into Arduino 8-bit will take place. It will then be called by getjoystickPosX;
  void setjoystickPosY();	// In this function where the mapping of joystick-Y's values of 10-bit into Arduino 8-bit will take place.It will then be called by getjoystickPosY;
};


#endif
